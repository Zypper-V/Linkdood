#include "cdoodchatmanagermodel.h"
#include "cdoodchatitem.h"
#include <QDebug>
#include <QUuid>
CDoodChatManagerModel::CDoodChatManagerModel(QObject *parent):
    CDoodListModel(parent)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodChatManagerModel*>();
    mNeedNewMsgLastId="0";
    mNeedNewMsgCount = 0;
    mAvatar = "";
    mAccountAvater = "";
    mAccountName = "";
    mAccountUserId = "";
    mGroupSize = 0;
}

QString CDoodChatManagerModel::getLastMsgid()
{
    if(_list->count()>0){
        QString msgid;
        msgid=qobject_cast<CDoodChatItem*>(_list->at(_list->count()-1))->msgId();
        qDebug() << Q_FUNC_INFO<<msgid;
        return msgid;
    }
    qDebug() << Q_FUNC_INFO<<"msgid";
    return "";
}

QString CDoodChatManagerModel::bigImageExisted(QString localId)
{
    CDoodChatItem* item = m_pChatMap.value(localId,NULL);
    if(item != NULL){
        QFileInfo file(item->mImageMainUrl);
        QString path = QString::fromStdString(APP_DATA_PATH)+m_pClient->UserId()+"/image/bigimage/"+file.fileName();
        if(file.exists(path)){
            return path;
        }else{
            file.setFile(item->mImageThumbUrl);
            path = QString::fromStdString(APP_DATA_PATH)+m_pClient->UserId()+"/image/bigimage/"+file.fileName();
            if(file.exists(path)){
                return path;
            }
        }
    }

    return "";
}

bool CDoodChatManagerModel::fileExistAtLocal(QString fullPath)
{
    if(fullPath.startsWith("file://")){
        fullPath.remove("file://");
    }
    QFileInfo file(fullPath);
    bool ret = file.exists();
    return ret;
}

int CDoodChatManagerModel::imageWidth(QString path)
{
    if(path.startsWith("file://")){
        path.remove("file://");
    }
    QImage img(path);
    return img.width();
}

int CDoodChatManagerModel::imageHeight(QString path)
{
    if(path.startsWith("file://")){
        path.remove("file://");
    }
    QImage img(path);
    return img.height();
}

void CDoodChatManagerModel::reloadImageMsg()
{
    QList<CDoodChatItem*> model = m_pChatMap.values();

    int len = model.length();
    for(int i =0;i<len;++i){
        CDoodChatItem* item = model.at(i);
        if(item != NULL &&item->msgType() == "5"){
            item->setIsImageChange();
        }
    }
}
void CDoodChatManagerModel::updateGroupMems(MemberList list)
{
    int len = list.size();
    qDebug()<<Q_FUNC_INFO<<"size:"<<list.size();
    if(list.size()>0){
        mGroupMemList.clear();
    }
    for(int i = 0;i<len;++i){
        Member mem = list.at(i);
        if(mem.thumbAvatar != "" && !mem.thumbAvatar.startsWith("/data")){
            mem.thumbAvatar = QString::fromStdString(APP_DATA_PATH)+"public/head/"+mem.thumbAvatar;
        }
        mGroupMemList.push_back(mem);
    }
    mGroupSize = list.size();
    QList<CDoodChatItem*> msgList = m_pChatMap.values();
    for(int i =0;i<msgList.size();++i){
        CDoodChatItem* item = msgList.at(i);
        if((item != NULL && item->name() == item->fromId())||item != NULL && item->contactThumbAvatar() == ""){
            for(int j=0;j<mGroupMemList.size();++j){
                if(mGroupMemList.at(j).id == item->fromId()){
                    item->setName(mGroupMemList.at(j).name);
                    if(mGroupMemList.at(j).thumbAvatar != ""){
                        item->setContactThumbAvatar(mGroupMemList.at(j).thumbAvatar);
                    }
                    break;
                }
            }
        }
    }
    emit nameChanged();
}

void CDoodChatManagerModel::updateGroupSize(int size)
{
    if(size>0){
        mGroupSize = size;
        emit nameChanged();
    }
}

int CDoodChatManagerModel::msgCount()
{
    return m_pChatMap.size();
}

void CDoodChatManagerModel::addHistoryMsgToListView(MsgList msgList)
{
    qDebug()<<Q_FUNC_INFO<<"msg size:"<<msgList.size();
    int len = msgList.size();
    bool isUpdate = false;
    if(msgList.size() <= 0){
        return;
    }

    for(int i = 0; i<len;++i){

        Msg msg = msgList.at(i);
        if(/*msg.msgtype.toInt() == MSG_TYPE_IMG || */msg.fromid =="0"||msg.fromid == ""){
            continue;
        }
        if(msg.localid == "" ||msg.localid == "0"){
            msg.localid = createLocalId();
        }

        if(msg.msgtype.toInt() == MEDIA_MSG_REVOKE && msgIsExitById(msg.revokeMsgId)){
            QStringList msgs;
            msgs.push_back(msg.revokeMsgId);
            emit deleteMessage(id(),msgs);
            removeItemByMsgId(msg.revokeMsgId);
        }

        if(!m_pChatMap.contains(msg.localid)&&!msgIsExitById(msg.msgid)) {

            QDateTime msgDate = QDateTime::fromString(msg.time, "yyyy-MM-dd hh:mm:ss");
            bool bShow = isJudageShowTime(msgDate);
            isUpdate = true;
            qDebug()<< Q_FUNC_INFO<<"msgTime:"<<msg.time;
            CDoodChatItem *pChatItem = new CDoodChatItem(this);
            pChatItem->setLocalId(msg.localid);
            pChatItem->setMsgType(msg.msgtype);
            pChatItem->setActiveType(msg.activeType);
            pChatItem->setMsgId(msg.msgid);
            pChatItem->setTargetId(msg.targetid);
            pChatItem->setFromId(msg.fromid);
            pChatItem->setToId(msg.toid);
            pChatItem->setName(msg.name);
            pChatItem->setTime(msgDate);
            pChatItem->setShowTime(bShow);
            pChatItem->setLoading(false);
            pChatItem->setContactThumbAvatar(msg.thumb_avatar);
            pChatItem->setIsMyselft(mAccountUserId == msg.fromid);
            if(msg.msgtype.toInt() == MSG_TYPE_FILE){
                pChatItem->setFileSize(msg.f_size.toLongLong());
                pChatItem->setProgress(0);
                pChatItem->setThumbAvatar(msg.f_url);
                pChatItem->setTar_thumbAvatar(msg.encrypt_user);
                pChatItem->setTextMsg(msg.filename);
                pChatItem->setBody(msg.encrypt_key);
                pChatItem->setFilePath("");
                pChatItem->mFileUrl = msg.f_url;
            }
            else if(msg.msgtype.toInt() == MSG_TYPE_IMG){
                if(msg.body != ""&& fileExistAtLocal(msg.body)){
                    msg.body = "file://"+msg.body;
                }else{
                    msg.body = "qrc:/res/control/defaultimage.png";
                }
                pChatItem->setBody(msg.body);
                pChatItem->setTar_thumbAvatar(msg.thumb_url);
                pChatItem->setTextMsg(msg.main_url);
                pChatItem->setBodyBig(msg.main_url);
                pChatItem->mImageMainUrl = msg.main_url;
                pChatItem->mImageThumbUrl = msg.thumb_url;
                pChatItem->setEncrypt_key(msg.encrypt_key);

            }else if(msg.msgtype.toInt() == MEDIA_MSG_REVOKE){
                pChatItem->setMsgType(QString::number(MSG_TYPE_TIP));
                if(msg.fromid == mAccountUserId){
                    pChatItem->setBody("您撤回了一条消息");
                }else{
                    pChatItem->setBody(msg.body+"撤回了一条消息");
                }
            }
            else{
                pChatItem->setBody(msg.body);
            }

            //addItem(pChatItem);
            qint64 pos = indexOfNewItem(pChatItem->time());
            if(pos>=0 &&pos<= m_pChatMap.size()){
                insertItem(pos,pChatItem);
            }

            m_pChatMap[msg.localid] = pChatItem;
            updateItemNameAndAvatar(msg.localid,msg.fromid);
            pChatItem->mEnkey = msg.encrypt_key;
            pChatItem->mEnkeyUser = msg.encrypt_user;
            if(msg.msgtype.toInt() == MSG_TYPE_IMG){
                if(msg.body == "qrc:/res/control/defaultimage.png"|| !fileExistAtLocal(msg.body)){
                    pChatItem->setLoading(true);
                    emit downloadImage(id(),msg.localid,msg.thumb_url,msg.encrypt_key);
                }
            }
        }
    }
    if(isUpdate){
        emit updateDataFinished();
    }
    if(_list->count()>0){
        QString msgid;
        msgid=qobject_cast<CDoodChatItem*>(_list->at(_list->count()-1))->msgId();
        emit setMsgRead(msgid);
    }
}

void CDoodChatManagerModel::addItemToListViewModel(Msg msg,QString textMsgContent,bool isHistory)
{
    if(msg.fromid ==""||msg.fromid =="0"){
        return;
    }
    if(msg.localid == "" ||msg.localid == "0"){
        msg.localid = createLocalId();
    }
    if(msg.msgtype.toInt() == MEDIA_MSG_REVOKE && msgIsExitById(msg.revokeMsgId)){
        QStringList msgs;
        msgs.push_back(msg.revokeMsgId);
        emit deleteMessage(id(),msgs);
        removeItemByMsgId(msg.revokeMsgId);
    }
    if(!m_pChatMap.contains(msg.localid)&&!msgIsExitById(msg.msgid)) {

        QDateTime msgDate = QDateTime::fromString(msg.time, "yyyy-MM-dd hh:mm:ss");
        bool bShow = isJudageShowTime(msgDate);

        qDebug()<< Q_FUNC_INFO<<"msgTime:"<<msg.time;
        CDoodChatItem *pChatItem = new CDoodChatItem(this);
        pChatItem->setLocalId(msg.localid);
        pChatItem->setMsgType(msg.msgtype);
        pChatItem->setActiveType(msg.activeType);
        pChatItem->setMsgId(msg.msgid);
        pChatItem->setTargetId(msg.targetid);
        pChatItem->setFromId(msg.fromid);
        pChatItem->setToId(msg.toid);
        pChatItem->setName(msg.name);
        pChatItem->setTime(msgDate);
        pChatItem->setShowTime(bShow);
        pChatItem->setLoading(!isHistory);
        pChatItem->setContactThumbAvatar(msg.thumb_avatar);
        pChatItem->setIsMyselft(mAccountUserId == msg.fromid);
        if(msg.fromName != ""){
            pChatItem->setName(msg.fromName);
        }
        if(msg.msgtype.toInt() == MSG_TYPE_FILE){
            pChatItem->setFileSize(msg.f_size.toLongLong());
            pChatItem->setProgress(0);
            pChatItem->setThumbAvatar(msg.f_url);
            pChatItem->setTar_thumbAvatar(msg.encrypt_user);
            pChatItem->setTextMsg(msg.filename);
            pChatItem->setBody(msg.encrypt_key);
            pChatItem->setFilePath(msg.body);

            pChatItem->mFileUrl = msg.f_url;
        }
        else if(msg.msgtype.toInt() == MSG_TYPE_IMG){
            if(msg.thumb_url != "")
                msg.body = "file://"+msg.thumb_url;
            else{
                msg.body = "qrc:/res/control/defaultimage.png";
            }
            pChatItem->setBodyBig(msg.main_url);
            pChatItem->setBody(msg.body);
            pChatItem->setTar_thumbAvatar(msg.thumb_url);
            pChatItem->setTextMsg(msg.main_url);
            pChatItem->setEncrypt_key(msg.encrypt_key);
            pChatItem->setEnkeyUser(msg.encrypt_user);
            pChatItem->mImageMainUrl = msg.main_url;
            pChatItem->mImageThumbUrl = msg.thumb_url;
        }else if(msg.msgtype.toInt() == MEDIA_MSG_REVOKE){
            pChatItem->setMsgType(QString::number(MSG_TYPE_TIP));
            if(msg.fromid == mAccountUserId){
                pChatItem->setBody("您撤回了一条消息");
            }else{
                pChatItem->setBody(msg.body+"撤回了一条消息");
            }

        }
        else{
            pChatItem->setBody(msg.body);
        }
        qint64 pos = indexOfNewItem(pChatItem->time());
        if(pos>=0 &&pos<= m_pChatMap.size()){
            insertItem(pos,pChatItem);
        }

        m_pChatMap[msg.localid] = pChatItem;
        updateItemNameAndAvatar(msg.localid,msg.fromid);

        pChatItem->mEnkey = msg.encrypt_key;
        pChatItem->mEnkeyUser = msg.encrypt_user;

        emit updateDataFinished();
    }
}
void CDoodChatManagerModel::modifyItemToListViewModel(Msg msg,bool isLoading,int progress)
{
    CDoodChatItem * item = m_pChatMap[msg.localid];
    if(item != NULL){
        if(msg.msgid !=""){
            item->setMsgId(msg.msgid);
        }
        if(msg.name !=""){
            item->setName(msg.name);
        }
        if(msg.thumb_avatar !=""){
            item->setTar_thumbAvatar(msg.thumb_avatar);
        }
        item->setLoading(isLoading);
        item->setProgress(progress);
    }
}

void CDoodChatManagerModel::clearList()
{
    if(m_pChatMap.size() <= 0)
        return;

    QMap<QString, CDoodChatItem*>::iterator i = m_pChatMap.begin();
    while (i != m_pChatMap.end()) {
        CDoodChatItem* item = m_pChatMap[i.key()];
        if(item != NULL){
            removeItem(item);
            delete item;
        }
        ++i;
    }
    m_pChatMap.clear();
}

void CDoodChatManagerModel::removeItemById(QString id)
{
    CDoodChatItem* item = m_pChatMap.value(id,NULL);
    if(item != NULL){
        removeItem(item);
        delete item;
        m_pChatMap.remove(id);
    }
}

void CDoodChatManagerModel::removeItemByMsgId(QString msgId)
{
    CDoodChatItem* item = NULL;
    for(int i = 0;i<_list->size();++i){
        CDoodChatItem* cur = (CDoodChatItem*)_list->at(i);
        if(cur != NULL && cur->msgId() == msgId){
            item = cur;
            break;
        }
    }
    if(item != NULL){
        removeItem(item);
        m_pChatMap.remove(item->localId());
        delete item;
    }
}

void CDoodChatManagerModel::removeItemsByFromId(QString fromId)
{
    QList<CDoodChatItem*> list = m_pChatMap.values();
    QStringList msgs;
    int len = list.size();
    for(int i =0;i<len;i++){
        CDoodChatItem* item = list.at(i);
        if(item != NULL && item->fromId() == fromId){
            removeItem(item);
            msgs.push_back(item->msgId());
            m_pChatMap.remove(item->localId());
            delete item;
        }
    }
    if(msgs.size()>0){
        emit deleteMessage(id(),msgs);
    }

}

void CDoodChatManagerModel::deleteAllMessage()
{
    QList<CDoodChatItem*> list = m_pChatMap.values();
    QStringList msgs;
    int len = list.size();
    for(int i =0;i<len;i++){
        CDoodChatItem* item = list.at(i);
        if(item != NULL){
            msgs.push_back(item->msgId());
        }
    }
    if(msgs.size()>0){
        emit deleteMessage(id(),msgs);
    }
}

void CDoodChatManagerModel::analyzeHistoryMsg(MsgList msgList)
{
    qDebug() << Q_FUNC_INFO;
    addHistoryMsgToListView(msgList);
}

void CDoodChatManagerModel::updateAvatar(QString id,QString avater)
{
    //    qDebug()<<Q_FUNC_INFO<<"avater:"<<avater;
    QList<CDoodChatItem*> list = m_pChatMap.values();
    for(int i =0;i<list.size();++i){
        CDoodChatItem* item = list.at(i);
        if(item->fromId() == id){
            item->setContactThumbAvatar(avater);
        }
    }

}

void CDoodChatManagerModel::updateLastMsgId(QString lastMsgId)
{
    mNeedNewMsgLastId =  lastMsgId;
}

void CDoodChatManagerModel::setAccountId(QString id)
{
    mAccountUserId = id;
}

void CDoodChatManagerModel::updateAccountUserInfo(QString id, QString name, QString avatar)
{
    if(id != ""){
        mAccountUserId = id;
    }
    if(name !=""){
        mAccountName = name;
    }
    if(avatar != ""){
        mAccountAvater = avatar;
    }
}

void CDoodChatManagerModel::updateItemNameAndAvatar(QString localId,QString userId)
{
    QString tmp = chatType();
    if(chatType()=="1"){
        CDoodChatItem* item = m_pChatMap.value(localId,NULL);
        if(item != NULL){
            if(item->fromId() == mAccountUserId){
                item->setContactThumbAvatar(mAccountAvater);
                item->setName(mAccountName);
            }else{
                item->setContactThumbAvatar(avatar());
                if(item->name() == item->fromId()){
                    item->setName(name());
                }
            }
        }
    }else if(chatType()=="2"){
        CDoodChatItem* item = m_pChatMap.value(localId,NULL);
        //emit reqestUserInfo(item->fromId());
        if(item != NULL){
            if(item->fromId() == mAccountUserId){
                item->setContactThumbAvatar(mAccountAvater);
                item->setName(mAccountName);
            }else{
                int size = mGroupMemList.size();
                if(size == 0){
                    //emit reqestUserInfo(item->fromId());
                }else{
                    for(int i=0;i<size;++i){
                        Member mem = mGroupMemList.at(i);
                        if(mem.id == item->fromId()){
                            item->setContactThumbAvatar(mem.thumbAvatar);
                            if(item->name() ==item->fromId()){
                                item->setName(mem.name);
                            }
                            updateGroupChatInfo(mem.id,mem.name,mem.thumbAvatar);
                            return;
                        }
                    }
                }
            }
        }
    }else if(chatType() == "6"){
        CDoodChatItem* item = m_pChatMap.value(localId,NULL);
        if(item != NULL){
            if(!item->contactThumbAvatar().startsWith("qrc")){
                item->setContactThumbAvatar(mAccountAvater);
                item->setName(mAccountName);
            }else{
                item->setName("我的电脑");
            }
        }
    }
}

void CDoodChatManagerModel::updateItemData(QString userId,QString name,QString avater)
{
    QList<CDoodChatItem*>list = m_pChatMap.values();
    for(int i=0;i<list.size();i++){
        CDoodChatItem* item = list.at(i);
        if(item != NULL){
            if(item->fromId() == userId){
                if(item->name() != name && name !=""){
                    item->setName(name);
                }
                if(item->thumbAvatar() != avater && avater !=""){
                    item->setContactThumbAvatar(avater);
                }
            }
        }
    }
}

bool CDoodChatManagerModel::msgIsExitById(QString msgId)
{
    if(msgId == "" || msgId =="0"){
        return false;
    }
    QList<CDoodChatItem*>list = m_pChatMap.values();
    for(int i=0;i<list.size();++i){
        CDoodChatItem* item = list.at(i);
        if(item != NULL){
            if(item->msgId() == msgId){
                return true;
            }
        }
    }
    return false;
}

void CDoodChatManagerModel::updateGroupChatInfo(QString userId, QString name, QString thum)
{
    QList<CDoodChatItem*> list = m_pChatMap.values();
    for(int i =0;i<list.size();++i){
        CDoodChatItem* item = list.at(i);
        if(item != NULL && item->fromId() == userId){
            if(name != ""){
                item->setName(name);
            }
            item->setContactThumbAvatar(thum);
        }
    }
}

int CDoodChatManagerModel::indexOfNewItem(QDateTime date)
{
    qDebug()<<Q_FUNC_INFO<<"date:"<< date.toMSecsSinceEpoch();

    if(_list==NULL || _list->size() ==0){
        return 0;
    }

    int index = 0;
    int len = _list->size();
    qint64 time = date.toMSecsSinceEpoch();

    for(int i = len-1;i>=0;--i){
        CDoodChatItem* item = (CDoodChatItem*) _list->at(i);
        if(item !=NULL){
            qint64 curItemTime = item->time().toMSecsSinceEpoch();
            if(curItemTime<=time){
                index = i+1;
                break;
            }
        }
    }
    return index;
}

void CDoodChatManagerModel::addGroupMems(MemberList mems)
{
    if(mems.size()<=0){
        return;
    }
    if(mems[0].groupid == id()){
        for(int i =0;i<mems.size();++i){
            mGroupMemList.push_back(mems[i]);
        }
    }
}

QString CDoodChatManagerModel::getChatName()
{
    return mName;
}

CDoodChatItem *CDoodChatManagerModel::itemById(QString id)
{
    QMap<QString, CDoodChatItem*>::iterator it = m_pChatMap.find(id);
    if(it == m_pChatMap.end())
        return NULL;
    else
        return it.value();
}

CDoodChatManagerModel::~CDoodChatManagerModel()
{
    qDebug() << Q_FUNC_INFO;
    clearList();
}

QString CDoodChatManagerModel::draft()
{
    return mDraft;
}

void CDoodChatManagerModel::setDraft(QString data)
{
    mDraft = data;
    emit draftChanged();
}

void CDoodChatManagerModel::exitChat()
{
    if(mDraft != ""&& mDraft != "\n"){
        emit draftChanged("[草稿]"+mDraft);
    }else{
        emit draftChanged("");
    }
}

QString CDoodChatManagerModel::id() const
{
    qDebug() << Q_FUNC_INFO;
    return mId;
}

void CDoodChatManagerModel::setId(const QString &id)
{
    qDebug() << Q_FUNC_INFO;
    mId = id;
    emit idChanged();
}

QString CDoodChatManagerModel::chatType() const
{
    return mChatType;
}

QString CDoodChatManagerModel::setChatType(const QString &data)
{
    if(mChatType == data) {
        return data;
    }
    mChatType = data;
    emit chatTypeChanged();
    return mChatType;
}

QString CDoodChatManagerModel::lastMsgId()
{
    CDoodChatItem* item = m_pChatMap.last();
    if(item != NULL){
        return item->msgId();
    }
    return "0";
}

QString CDoodChatManagerModel::firstMsgId()
{
    if(m_pChatMap.size() == 0){
        return "0";
    }
    CDoodChatItem* item = m_pChatMap.first();
    if(item != NULL){
        return item->msgId();
    }
    return "0";
}

int CDoodChatManagerModel::groupMemsCount()
{
    return mGroupMemList.size();
}

QString CDoodChatManagerModel::createLocalId()
{
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    qDebug() << "Uuid:" << strId;
    return strId;
}

void CDoodChatManagerModel::addChatItemtoMap(CDoodChatItem *chatItem)
{
    if(chatItem != NULL){
        addItem(chatItem);
        m_pChatMap[chatItem->localId()] = chatItem;
    }
}

void CDoodChatManagerModel::setAvatar(const QString &data)
{
    if(data !=""&& data != mAvatar){
        mAvatar = data;
        emit avatarChanged();
    }
}

QString CDoodChatManagerModel::name() const
{
    qDebug() << Q_FUNC_INFO;
    QString tmp = mName;
    if(chatType() == "2" && mGroupSize>0){
        tmp +="("+QString::number(mGroupSize)+")";
    }
    return tmp;
}

QString CDoodChatManagerModel::avatar() const
{
    return mAvatar;
}

void CDoodChatManagerModel::setName(const QString &name)
{
    qDebug() << Q_FUNC_INFO;
    mName = name;
    emit nameChanged();
    QList<CDoodChatItem*> list = m_pChatMap.values();
    for(int i = 0;i<list.size();++i){
        CDoodChatItem* item = list.at(i);
        if(item != NULL){
            if(item->fromId() == id() && chatType() == "1"){
                item->setName(name);
                if(item->contactThumbAvatar() ==""){
                    item->setContactThumbAvatar(avatar());
                }
            }
        }

    }
}

void CDoodChatManagerModel::judgeAddTimeTip(QDateTime dateTime)
{

    if(m_pChatMap.size()<= 0){
        return ;
    }
    QDateTime lastMsgTime = m_pChatMap.last()->time();

    int64 TimeDistance = lastMsgTime.secsTo(dateTime);
    if (qFabs(TimeDistance) >= 60 * 2)
    {
        QString  date = Common::dealTime(dateTime.toMSecsSinceEpoch(),2);
        if(date != ""){
            CDoodChatItem* item = new CDoodChatItem(this);
            item->setMsgType(QString::number(MSG_TYPE_TIME));
            item->setLocalId(QString::number(dateTime.toMSecsSinceEpoch()));
            item->setBody(date);
            addItem(item);
            m_pChatMap[item->localId()] = item;
        }

    }
}

bool CDoodChatManagerModel::isJudageShowTime(QDateTime date)
{
    if(m_pChatMap.size() <= 0){
        return true;
    }else{
        CDoodChatItem* last = (CDoodChatItem*)_list->at(_list->size() -1);
        QDateTime lastMsgTime = last->time();
        QString tmp = Common::dealTime(lastMsgTime.toMSecsSinceEpoch(),1);
        int64 timeDistance = lastMsgTime.secsTo(date);
        if(qFabs(timeDistance) >= 60 * 3 && last->timeText() != tmp){//60 * 5
            return true;
        }
    }
    return false;
}
