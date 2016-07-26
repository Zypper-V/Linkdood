#include "cdoodchatmanagermodel.h"
#include "cdoodchatitem.h"
#include <QDebug>

CDoodChatManagerModel::CDoodChatManagerModel(QObject *parent):
    CDoodListModel(parent)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodChatManagerModel*>();
    mLastMsgId="0";
    mTotalUnreadMsgCount = 0;
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

void CDoodChatManagerModel::addItemToListViewModel(Msg msg,QString textMsgContent)
{
    if(msg.localid == "" ||msg.localid == "0"){
        msg.localid = msg.msgid;
    }
    if(!m_pChatMap.contains(msg.localid)) {

        QDateTime msgDate = QDateTime::fromString(msg.time, "yyyy-MM-dd hh:mm:ss");
        judgeAddTimeTip(msgDate);

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
        pChatItem->setLoading(true);
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
        }
        else if(msg.msgtype.toInt() == MSG_TYPE_IMG){
            msg.body = "file://"+msg.thumb_url;
            pChatItem->setBody(msg.body);
            pChatItem->setTar_thumbAvatar(msg.thumb_url);
            pChatItem->setTextMsg(msg.main_url);
        }
        else{
            pChatItem->setBody(msg.body);
        }
        addItem(pChatItem);
        m_pChatMap[msg.localid] = pChatItem;
        updateItemNameAndAvatar(msg.localid,msg.fromid);
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

    QMap<QString, CDoodChatItem*>::const_iterator i = m_pChatMap.constBegin();
    while (i != m_pChatMap.constEnd()) {
        removeItem(m_pChatMap[i.key()]);
        delete m_pChatMap[i.key()];
        m_pChatMap.remove(i.key());
        ++i;
    }
    m_pChatMap.clear();
}

void CDoodChatManagerModel::removeItemById(QString id)
{
    CDoodChatItem* item = m_pChatMap[id];
    if(item != NULL){
        removeItem(item);
        delete item;
        m_pChatMap[id] = 0;
    }
}

void CDoodChatManagerModel::analyzeMsg(MsgList msgList)
{
    qDebug() << Q_FUNC_INFO;
    int i= 0,size = msgList.size();
    for(;i<size;++i){
        addItemToListViewModel(msgList.at(i));
    }
}

void CDoodChatManagerModel::updateAvatar(QString id,QString avater)
{
    qDebug()<<Q_FUNC_INFO<<"avater:"<<avater;
    QList<CDoodChatItem*> list = m_pChatMap.values();
    for(int i =0;i<list.size();++i){
        CDoodChatItem* item = list.at(i);
        if(item->fromId() == id){
            item->setContactThumbAvatar(avater);
        }
    }

}

void CDoodChatManagerModel::updateUnreadMsg(QString lastMsgId, int count)
{
    mTotalUnreadMsgCount = count;
    mLastMsgId =  lastMsgId;
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
    return mLastMsgId;
}

int CDoodChatManagerModel::unReadMsgCount()
{
    return mTotalUnreadMsgCount;
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
        return;
    }
    QDateTime lastMsgTime = m_pChatMap.last()->time();

    int64 TimeDistance = lastMsgTime.secsTo(dateTime);
    if (qFabs(TimeDistance) >= 60 * 2)
    {
        CDoodChatItem* item = new CDoodChatItem(this);
        item->setMsgType(QString::number(MSG_TYPE_TIP));
        item->setLocalId(QString::number(dateTime.toMSecsSinceEpoch()));
        item->setBody(Common::dealTime(dateTime.toMSecsSinceEpoch(),2));
        addItem(item);
        m_pChatMap[item->localId()] = item;
    }
}
