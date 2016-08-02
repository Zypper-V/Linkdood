#include "cdoodchatmanagermodel.h"
#include "cdoodchatitem.h"
#include <QDebug>

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
    emit nameChanged();
}

int CDoodChatManagerModel::msgCount()
{
    return m_pChatMap.size();
}

void CDoodChatManagerModel::addHistoryMsgToListView(MsgList msgList)
{
    qDebug()<<Q_FUNC_INFO<<"msg size:"<<msgList.size();
    int len = msgList.size();
    if(msgList.size() <= 0){
        return;
    }
    //判断消息插入位置
    bool bInsertHead = false;
    if(m_pChatMap.size() >0){

        QDateTime msgDate = QDateTime::fromString(msgList.at(0).time, "yyyy-MM-dd hh:mm:ss");
        int64 desc = msgDate.secsTo(m_pChatMap.last()->time());
        if(desc<0){
            bInsertHead = true;
        }
    }else{
        bInsertHead = false;
    }
    if(bInsertHead){

        for(int i = len-1; i>=0;--i){

            Msg msg = msgList.at(i);
            if(msg.localid == "" ||msg.localid == "0"){
                msg.localid = msg.msgid;
            }
            if(!m_pChatMap.contains(msg.localid)) {

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
                    if(msg.body != ""){
                        msg.body = "file:// "+msg.body;
                    }else{
                        msg.body = "qrc:/res/chat_tool_photo_normal.png";
                    }
                    pChatItem->setBody(msg.body);
                    pChatItem->setTar_thumbAvatar(msg.thumb_url);
                    pChatItem->setTextMsg(msg.main_url);

                    pChatItem->mImageMainUrl = msg.main_url;
                    pChatItem->mImageThumbUrl = msg.thumb_url;
                }
                else{
                    pChatItem->setBody(msg.body);
                }
                m_pChatMap[msg.localid] = pChatItem;
                addItemBegin(pChatItem);
                updateItemNameAndAvatar(msg.localid,msg.fromid);

                pChatItem->mEnkey = msg.encrypt_key;
                pChatItem->mEnkeyUser = msg.encrypt_user;

                if(msg.body == "qrc:/res/chat_tool_photo_normal.png" && msg.msgtype.toInt() == MSG_TYPE_IMG){
                    pChatItem->setLoading(true);
                    emit downloadImage(id(),msg.localid,msg.thumb_url,msg.encrypt_key);
                }

            }
        }
    }else{

        for(int i = 0; i<len;++i){

            Msg msg = msgList.at(i);
            if(msg.localid == "" ||msg.localid == "0"){
                msg.localid = msg.msgid;
            }
            if(!m_pChatMap.contains(msg.localid)) {

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
                    if(msg.body != ""){
                        msg.body = "file://"+msg.body;
                    }else{
                        msg.body = "qrc:/res/chat_tool_photo_normal.png";
                    }
                    pChatItem->setBody(msg.body);
                    pChatItem->setTar_thumbAvatar(msg.thumb_url);
                    pChatItem->setTextMsg(msg.main_url);

                    pChatItem->mImageMainUrl = msg.main_url;
                    pChatItem->mImageThumbUrl = msg.thumb_url;
                }
                else{
                    pChatItem->setBody(msg.body);
                }
                m_pChatMap[msg.localid] = pChatItem;
                addItem(pChatItem);
                updateItemNameAndAvatar(msg.localid,msg.fromid);
                pChatItem->mEnkey = msg.encrypt_key;
                pChatItem->mEnkeyUser = msg.encrypt_user;
                if(msg.body == "qrc:/res/chat_tool_photo_normal.png" && msg.msgtype.toInt() == MSG_TYPE_IMG){
                    pChatItem->setLoading(true);
                    emit downloadImage(id(),msg.localid,msg.thumb_url,msg.encrypt_key);
                }

            }
        }
    }
}

void CDoodChatManagerModel::addItemToListViewModel(Msg msg,QString textMsgContent,bool isHistory)
{
    if(msg.localid == "" ||msg.localid == "0"){
        msg.localid = msg.msgid;
    }
    if(!m_pChatMap.contains(msg.localid)) {

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
                msg.body = "qrc:/res/chat_tool_photo_normal.png";
            }
            pChatItem->setBody(msg.body);
            pChatItem->setTar_thumbAvatar(msg.thumb_url);
            pChatItem->setTextMsg(msg.main_url);

            pChatItem->mImageMainUrl = msg.main_url;
            pChatItem->mImageThumbUrl = msg.thumb_url;
        }
        else{
            pChatItem->setBody(msg.body);
        }
        addItem(pChatItem);
        m_pChatMap[msg.localid] = pChatItem;
        updateItemNameAndAvatar(msg.localid,msg.fromid);

        pChatItem->mEnkey = msg.encrypt_key;
        pChatItem->mEnkeyUser = msg.encrypt_user;
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
                item->setName(name());
            }
        }
    }else if(chatType()=="2"){
        CDoodChatItem* item = m_pChatMap.value(localId,NULL);
        if(item != NULL){
            if(item->fromId() == mAccountUserId){
                item->setContactThumbAvatar(mAccountAvater);
                item->setName(mAccountName);
            }else{
                int size = mGroupMemList.size();
                if(size == 0){
                    emit reqestUserInfo(item->fromId());
                }else{
                    for(int i=0;i<size;++i){
                        Member mem = mGroupMemList.at(i);
                        if(mem.id == item->fromId()){
                            item->setContactThumbAvatar(mem.thumbAvatar);
                            item->setName(mem.name);
                            return;
                        }
                    }
                }
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
    if(chatType() == "2" && mGroupMemList.size()>0){
        tmp +="("+QString::number(mGroupMemList.size())+")";
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
        QDateTime lastMsgTime = m_pChatMap.last()->time();
        int64 timeDistance = lastMsgTime.secsTo(date);
        if(qFabs(timeDistance) >= 2){//60 * 5
            return true;
        }else{
            QDateTime curentDate = QDateTime::currentDateTime();
            timeDistance = curentDate.secsTo(date);
            if(qFabs(timeDistance) >= 2){//60 * 5
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}
