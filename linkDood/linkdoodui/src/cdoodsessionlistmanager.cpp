#include "cdoodsessionlistmanager.h"
#include "cdoodsessionlistitem.h"


#include <QMetaType>
#include <QFile>
#include <QDebug>

CDoodSessionListManager::CDoodSessionListManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodSessionListManager*>();
    initConnect();
    mUnreadCount = 0;
    mIsSysMsgPage = 0;
    m_pUiManager = (linkdoodui_Workspace*)parent;
}

CDoodSessionListManager::~CDoodSessionListManager()
{
}

void CDoodSessionListManager::getChatList()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getChatList();
}
void CDoodSessionListManager::removeNitification(QString targetId)
{
    m_pClient->removeNitification(targetId);
}
void CDoodSessionListManager::clearChatList()
{
    qDebug() << Q_FUNC_INFO;
    QList<CDoodSessionListItem*>  itemList = sessionListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    sessionListMap.clear();
    mUnreadCount = 0;
}

QString CDoodSessionListManager::getHeaderColor(const QString &id)
{
    qDebug() << Q_FUNC_INFO << id;

    QStringList oColorList;

    oColorList << "#9e8dbe" << "#6ed1d1" << "#88b4e8" << "#d98374" << "#95a7bf" <<
                  "#e3c676" << "#477e99" << "#a6d3d6" << "#a1887f" << "#b4c17b" <<
                  "#88cfee" << "#d7a373" << "#66ae96" << "#cc7eb0" << "#81aba9" <<
                  "#c6b36f" << "#84b9cb" << "#3d9ac6" << "#b18c6f" << "#e6ccb8" <<
                  "#7b76a6" << "#b3ad9f" << "#51c79f" << "#e3a16f" << "#89c3eb" <<
                  "#a69bbd" << "#a89e95" << "#5b7e91" << "#f6b1aa" << "#6fc5d4";


    int nId = id.left(6).toInt()%30;
    qDebug() << "nId = " << nId;
    QString sColor = oColorList.at(nId);
    qDebug() << "sColor = " << sColor;

    return sColor;
}

QString CDoodSessionListManager::getSubName(const QString &name)
{
    qDebug() << Q_FUNC_INFO << name;
    return name.right(2);
}

bool CDoodSessionListManager::checkFileExists(const QString &path)
{
    if(path.contains("qrc")){
        return true;
    }else if(path != "" &&path.contains(".")){
        QFileInfo file(path);
        return file.exists();
    }
    return false;
}

void CDoodSessionListManager::removeChatItem(QString id)
{
    qDebug() << Q_FUNC_INFO;
    CDoodSessionListItem *tmpItem  = sessionListMap.value(id,NULL);
    if(tmpItem != NULL){
        removeItem(tmpItem);
        m_pClient->removeChat(id);
        sessionListMap.remove(id);
        if(tmpItem->unReadMsgCount()>0){
            setUnreadCount(-tmpItem->unReadMsgCount());
        }
        delete tmpItem;
    }
}

void CDoodSessionListManager::clickChatItem(QString id)
{
    CDoodSessionListItem *tmpItem  = sessionListMap.value(id);
    if(tmpItem != NULL){
        tmpItem->setTipMe("");
        qDebug() <<Q_FUNC_INFO<<"tmpItem->tipMe():"<<tmpItem->tipMe();
        tmpItem->setUnReadCount("0");
        if(tmpItem->unReadMsgCount()>0){
            setUnreadCount(-tmpItem->unReadMsgCount());
            tmpItem->setUnreadMsgCOunt(0);
        }
        qDebug() <<Q_FUNC_INFO << "total:"<<mUnreadCount;
    }
}

void CDoodSessionListManager::entrySysMsgPage()
{
    qDebug()<<Q_FUNC_INFO;
    mIsSysMsgPage = true;
    QString path = APP_DATA_PATH;
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("isSysPage",true);
}

void CDoodSessionListManager::exitSysMsgPage()
{
    qDebug()<<Q_FUNC_INFO;
    mIsSysMsgPage = false;
    QString path = APP_DATA_PATH;
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("isSysPage",false);
}

int CDoodSessionListManager::unreadCount() const
{
    qDebug() << Q_FUNC_INFO << "mUnreadCount:" << mUnreadCount;
    return mUnreadCount;
}

void CDoodSessionListManager::setUnreadCount(int count)
{
    qDebug() << Q_FUNC_INFO << "mUnreadCount:" << mUnreadCount;
    mUnreadCount += count;
    if(mUnreadCount<0){
        mUnreadCount = 0;
    }
    emit unreadCountChanged();
}

void CDoodSessionListManager::onTipMe(QString groupid)
{
    CDoodSessionListItem *item = sessionListMap.value(groupid);
    if(item != NULL){
        item->setTipMe("1");
    }
}

void CDoodSessionListManager::onAvatarChanged(QString targetId, QString avatar)
{
    //    qDebug() << Q_FUNC_INFO <<targetId;
    if(avatar != ""){
        CDoodSessionListItem *item = sessionListMap.value(targetId);
        if(item != NULL){
            item->setThumbAvatar(avatar);
        }
    }

}

void CDoodSessionListManager::onChatListChanged(const Chat_UIList &chats)
{
    qDebug() << Q_FUNC_INFO << "zhangp **** chat size4 = " << chats.size();
    Chat_UI historysession;
    foreach (historysession, chats) {
        if(!sessionListMap.contains(historysession.id)) {
            CDoodSessionListItem *tmpItem = new CDoodSessionListItem(this);
            tmpItem->setId(historysession.id);
            tmpItem->setLastMsg(historysession.last_msg);
            tmpItem->setName(historysession.name);
            tmpItem->setMsgTime(historysession.msg_time);
            tmpItem->setChatType(m_pClient->userType(historysession.id));
            tmpItem->setLastMsgid(QString::number(historysession.last_msgid));
            if(historysession.unread_count!=0){
                if(historysession.unread_count<100){
                    tmpItem->setUnReadCount(QString::number(historysession.unread_count));
                }
                else{
                    tmpItem->setUnReadCount("99+");
                }
                tmpItem->setUnreadMsgCOunt(historysession.unread_count);
                setUnreadCount(historysession.unread_count);
            }
            tmpItem->setThumbAvatar(historysession.thumb_avatar);
            qDebug() << Q_FUNC_INFO << "session unreadcount.......:" << QString::number(historysession.unread_count);
            //addItemBegin(item);
            insertItemByTime(tmpItem);
            sessionListMap[historysession.id] = tmpItem;
            updateItemInfor(historysession.id,tmpItem->name(),tmpItem->thumbAvatar());
        }
    }
}

void CDoodSessionListManager::onGetUserInfo(int code, Contact contact)
{
    Q_UNUSED(code);

    CDoodSessionListItem* item = sessionListMap.value(contact.id,NULL);
    if(item != NULL)
    {
        item->setName(contact.name);
        if(contact.avatar != ""){
            item->setThumbAvatar(contact.avatar);
        }
    }

}

void CDoodSessionListManager::onGetGroupInfo(QString code, Group group)
{
    Q_UNUSED(code);

    CDoodSessionListItem* item = sessionListMap.value(group.id,NULL);
    if(item != NULL)
    {
        item->setName(group.name);
        if(group.thumbAvatar != "" && !group.thumbAvatar.startsWith("/data")){
            group.thumbAvatar =QString::fromStdString(APP_DATA_PATH)+"public/head/"+ group.thumbAvatar;
            item->setThumbAvatar(group.thumbAvatar);
        }
    }
}

QString CDoodSessionListManager::updateItemInfor(QString targetId,QString name,QString avater)
{
    if(targetId == m_pClient->UserId()){
        CDoodSessionListItem* item = sessionListMap.value(targetId,NULL);
        if(item != NULL){
            item->setName("我的电脑");
            item->setThumbAvatar("");
            item->setChatType(QString::number(COMPUTER_CHAT));
            return QString::number(COMPUTER_CHAT);
        }
    }
    QString chatType = m_pClient->userType(targetId);
    if(name == "" ||avater == ""){

        if(chatType=="1"){
            QString name1(""),avater1("");
            m_pUiManager->getContactInforFromList(targetId,name1,avater1);
            if(name1 !=""){
                CDoodSessionListItem* item = sessionListMap.value(targetId,NULL);
                if(item != NULL){
                    item->setName(name1);
                    item->setThumbAvatar(avater1);
                }
            }else{
                m_pClient->getUserInfo(targetId);
                //m_pClient->getOrgUserInfo(targetId);
            }
        }else if(chatType=="2"){
            QString name1(""),avater1("");
            m_pUiManager->getGroupInfoFromList(targetId,name1,avater1);
            if(name1 != ""){
                CDoodSessionListItem* item = sessionListMap.value(targetId,NULL);
                if(item != NULL){
                    item->setName(name1);
                    item->setThumbAvatar(avater1);
                }
            }else{
                m_pClient->getGroupInfo(targetId);
            }
        }
    }

    return chatType;
}

void CDoodSessionListManager::onSessionMessageNotice(QString targetId, QString msgId, QString lastMsg, QString time,
                                                     QString name, QString avater,QString unreadmsg)
{
    qDebug() << Q_FUNC_INFO<<"1111111111111111111111111111"<<unreadmsg;

    qDebug() << Q_FUNC_INFO << "targetID:" << targetId << " msgId:" << msgId << " lastMsg:" << lastMsg << " time:" << time << " name:" << name << " avater:" << avater << " unreadMsg:" << unreadmsg;
    QString chatType = m_pClient->userType(targetId);
    if(sessionListMap.contains(targetId)){
        CDoodSessionListItem* item = sessionListMap.value(targetId);
        if(item != NULL){
            item->setLastMsg(lastMsg);
            item->setMsgTime(time);
            item->setLastMsgid(msgId);
            item->setChatType(chatType);
            QString URC=item->unReadCount();
            if(unreadmsg=="1"){//未读数+1
                int count;
                if(URC!="")
                {
                    if(URC!="99+"){
                        count=URC.toInt()+1;
                    }
                    else{
                        count=100;
                    }
                }
                else
                {
                    count=1;
                }
                if(count>99){
                    item->setUnReadCount("99+");
                }
                else{
                    item->setUnReadCount(QString::number(count));
                }
                item->setUnreadMsgCOunt(count);
                int index = indexOf(item);
                if(index>0 && index <itemCount()){
                    item = (CDoodSessionListItem*)takeItemAt(index);
                    //addItemBegin(item);
                    insertItemByTime(item);
                }
                setUnreadCount(1);
            }
        }
    }else
    {
        CDoodSessionListItem *tmpItem = new CDoodSessionListItem(this);
        tmpItem->setId(targetId);
        tmpItem->setLastMsg(lastMsg);
        tmpItem->setName(name);
        tmpItem->setMsgTime(time);
        tmpItem->setThumbAvatar(avater);
        tmpItem->setMsgType(QString::number(MSG_TYPE_TEXT));
        tmpItem->setChatType(chatType);
        if(unreadmsg=="1"){
            tmpItem->setUnReadCount("1");
            setUnreadCount(1);
            tmpItem->setUnreadMsgCOunt(1);
        }
        tmpItem->setLastMsgid(msgId);
        //addItemBegin(item);
        insertItemByTime(tmpItem);
        sessionListMap[targetId] = tmpItem;
        qDebug() << Q_FUNC_INFO << "name:" << name;
    }
    updateItemInfor(targetId,name, avater);
}

void CDoodSessionListManager::onOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO << "msgList.size() = " << msgList.size();
    IMOfflineMsg offMsg;
    foreach(offMsg, msgList)
    {
        qDebug() << Q_FUNC_INFO << " offlineType:" << offMsg.offlineType << " count:" << offMsg.count << " msgId:" << offMsg.msgId << " body:" << offMsg.body << " targetId:" << offMsg.targetId << " fromId:" << offMsg.fromId << " name:" << offMsg.name;

        if(sessionListMap.contains(offMsg.targetId))
        {
            CDoodSessionListItem *item = sessionListMap.value(offMsg.targetId);
            item->setLastMsg(offMsg.body);
            item->setMsgTime(offMsg.time);
            item->setLastMsgid(offMsg.msgId);
            item->setName(offMsg.name);
            item->setChatType(m_pClient->userType(offMsg.targetId));
            QString URC=item->unReadCount();
            if(offMsg.offlineType == 1)
            {//未读数+1
                int count;
                if(URC!="")
                    count=URC.toInt() + offMsg.count;
                else
                    count=offMsg.count;
                if(count >99){
                    item->setUnReadCount("99+");
                }else{
                    item->setUnReadCount(QString::number(count));
                }

                item->setUnreadMsgCOunt(count);
                int index = indexOf(item);
                if(index>0 && index <itemCount())
                {
                    item = (CDoodSessionListItem*)takeItemAt(index);
                    //addItemBegin(item);
                    insertItemByTime(item);
                }
                setUnreadCount(offMsg.count);
            }
            updateItemInfor(offMsg.targetId,offMsg.name,item->thumbAvatar());
        }
        else
        {
            CDoodSessionListItem *tmpItem = new CDoodSessionListItem(this);
            tmpItem->setId(offMsg.targetId);
            tmpItem->setLastMsg(offMsg.body);
            tmpItem->setMsgTime(offMsg.time);
            tmpItem->setName(offMsg.name);
            tmpItem->setMsgType(QString::number(MSG_TYPE_TEXT));
            tmpItem->setChatType(m_pClient->userType(offMsg.targetId));
            if(offMsg.offlineType == 1)
            {
                if(offMsg.count >99){
                    tmpItem->setUnReadCount("99+");
                }else{
                    tmpItem->setUnReadCount(QString::number(offMsg.count));
                }
                setUnreadCount(offMsg.count);
                tmpItem->setUnreadMsgCOunt(offMsg.count);
            }
            tmpItem->setLastMsgid(offMsg.msgId);
            //addItemBegin(item);
            insertItemByTime(tmpItem);

            sessionListMap[offMsg.targetId] = tmpItem;
            updateItemInfor(offMsg.targetId,offMsg.name,"");
        }
    }
}

void CDoodSessionListManager::onDraftChanged(QString id, QString avater,QString name,QString chatType,QString draft)
{
    CDoodSessionListItem* item = sessionListMap.value(id,NULL);
    if(item == NULL && draft == ""){
        return;
    }
    if(item == NULL){
        item = new CDoodSessionListItem(this);
        item->setChatType(chatType);
        item->setId(id);
        item->setName(name);
        item->setLastMsg("");
        item->setThumbAvatar(avater);
        item->setLastMsgid("0");
        sessionListMap[id] = item;
        addItemBegin(item);
    }
    //QString time = QString::number( QDateTime::currentMSecsSinceEpoch());
    //item->setMsgTime(time);
    draft.replace("height=\"36\"","height=\"24\"");
    draft.replace("width=\"36\"","width=\"24\"");
    item->setDraft(draft);
}

void CDoodSessionListManager::onSysMessageNotice(IMSysMsg sysMsg)
{
    qDebug() << Q_FUNC_INFO;
    //
    addSysMessage(sysMsg);
    qDebug()<<Q_FUNC_INFO<<"name:"<<sysMsg.name<<"info:"<<sysMsg.info;
}

void CDoodSessionListManager::onRemoveSysMsg(QString msgtype, QString msgid)
{
    if(sessionListMap.contains(SYSMSG_ID)){
        CDoodSessionListItem*item = sessionListMap.value(SYSMSG_ID);
        if(msgtype=="0"||msgid==item->lastMsgid()){
            removeItem(item);
        }
    }

}

void CDoodSessionListManager::onGroupInfoChanged(QString type, Group gp)
{
    Q_UNUSED(type);

    CDoodSessionListItem*item =  sessionListMap.value(gp.id);
    if(item != NULL){
        item->setName(gp.name);
        if(gp.thumbAvatar != ""){
            item->setThumbAvatar(gp.thumbAvatar);
        }
    }
}

void CDoodSessionListManager::onGetOrgUserInfoResult(int code, OrgUser orguser)
{
    Q_UNUSED(code);

    CDoodSessionListItem*item =  sessionListMap.value(orguser.id,NULL);
    if(item != NULL){
        item->setName(orguser.name);
    }
}

void CDoodSessionListManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient,SIGNAL(tipMe(QString)),this,SLOT(onTipMe(QString)));
    connect(m_pClient,SIGNAL(getOrgUserInfoResult(int,OrgUser)),this,SLOT(onGetOrgUserInfoResult(int,OrgUser)));
    connect(m_pClient,SIGNAL(groupInfoChanged(QString,Group)),this,SLOT(onGroupInfoChanged(QString,Group)));
    connect(m_pClient,SIGNAL(chatAvatarChanged(QString,QString)),this,SLOT(onAvatarChanged(QString,QString)));
    connect(m_pClient, SIGNAL(sysMessageNotice(IMSysMsg)), this, SLOT(onSysMessageNotice(IMSysMsg)));
    connect(m_pClient, SIGNAL(chatListChanged(const Chat_UIList &)), this, SLOT(onChatListChanged(const Chat_UIList &)));
    connect(m_pClient, SIGNAL(sessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)), this, SLOT(onSessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)));
    connect(m_pClient,SIGNAL(offlineMsgNotice(IMOfflineMsgList)), this, SLOT(onOfflineMsgNotice(IMOfflineMsgList)));
    connect(m_pClient,SIGNAL(getUserInfoResult(int,Contact)), this, SLOT(onGetUserInfo(int,Contact)));
    connect(m_pClient,SIGNAL(getGroupInfoResult(QString,Group)), this, SLOT(onGetGroupInfo(QString,Group)));
}

void CDoodSessionListManager::addSysMessage(IMSysMsg sysMsg)
{
    if(sessionListMap.contains(SYSMSG_ID)){
        CDoodSessionListItem*item = sessionListMap.value(SYSMSG_ID);

        item->setId(SYSMSG_ID);
        item->setChatType(SYSMSG_ID);
        item->setLastMsg(sysMsg.info);
        item->setLastMsgid(sysMsg.msgid);
        item->setMsgTime(sysMsg.time);
        qDebug() << Q_FUNC_INFO << "sysMsg.isread:" << sysMsg.time;
        if(!mIsSysMsgPage && sysMsg.isread == "0"){
            int count = item->unReadMsgCount()+1;
            item->setUnReadCount(QString::number(count));
            setUnreadCount(1);
            item->setUnreadMsgCOunt(count);
        }
        removeItem(item);
        //addItemBegin(item);
        insertItemByTime(item);

    }else{
        CDoodSessionListItem*item = new CDoodSessionListItem(this);
        item->setId(SYSMSG_ID);
        item->setChatType(SYSMSG_ID);
        item->setLastMsg(sysMsg.info);
        item->setLastMsgid(sysMsg.msgid);
        item->setMsgTime(sysMsg.time);
        item->setName("系统消息");

        if(!mIsSysMsgPage && sysMsg.isread == "0"){
            int count = item->unReadMsgCount()+1;
            item->setUnReadCount(QString::number(count));
            setUnreadCount(1);
            item->setUnreadMsgCOunt(count);
        }

        //addItemBegin(item);
        insertItemByTime(item);
        sessionListMap[SYSMSG_ID] = item;
    }
}

int CDoodSessionListManager::indexOfNewItem(qint64 time)
{

    if(sessionListMap.size() ==0){
        return 0;
    }

    int index = 0;
    QList<CDoodSessionListItem*> list = sessionListMap.values();
    int len = list.size();

    for(int i = 0;i<len;++i){
        CDoodSessionListItem* item =  list.at(i);
        if(item !=NULL){
            qint64 curItemTime = item->dateTime();
            if(curItemTime<=time){
                index = i;
                break;
            }
        }
    }
    return index;
}

void CDoodSessionListManager::insertItemByTime(CDoodSessionListItem* item)
{
    qDebug() << Q_FUNC_INFO << item->msgTime() << item->dateTime()
             << item->name() << item->lastMsg();

    if (itemCount() == 0)
    {
        addItem(item);
        return;
    }

    QList<QObject*> *list = getList();
    int i = 0;
    for (i = 0; i < list->size(); i++)
    {
        CDoodSessionListItem* tmpItem =
                dynamic_cast<CDoodSessionListItem*>(list->at(i));
        if (tmpItem != NULL)
        {
            if(item->dateTime() >= tmpItem->dateTime())
            {
                break;
            }
        }
    }
    insertItem(i, item);
}
