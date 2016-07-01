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
}

CDoodSessionListManager::~CDoodSessionListManager()
{
}

void CDoodSessionListManager::getChatList()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getChatList();
}

void CDoodSessionListManager::clearChatList()
{
    qDebug() << Q_FUNC_INFO;
    QList<CDoodSessionListItem*>  itemList = sessionListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
    }
    sessionListMap.clear();
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
    qDebug() << Q_FUNC_INFO << path;
    QString tmp = path;
    if (tmp.contains("file://")) {
        tmp.remove("file://");
    } else if (tmp.contains("qrc:")) {
        return true;
    }
    bool bExists = QFile(tmp).exists();
    qDebug() << Q_FUNC_INFO << bExists;
    return bExists;
}

void CDoodSessionListManager::removeChatItem(QString id)
{
    qDebug() << Q_FUNC_INFO;
    CDoodSessionListItem *tmpItem  = sessionListMap.value(id);
    if(tmpItem != NULL){
        removeItem(tmpItem);
        m_pClient->removeChat(id);
        sessionListMap.remove(id);
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
            if(historysession.unread_count!=0){
                tmpItem->setUnReadCount(QString::number(historysession.unread_count));
            }
            tmpItem->setThumbAvatar(historysession.thumb_avatar);
            qDebug() << Q_FUNC_INFO << "session unreadcount.......:" << QString::number(historysession.unread_count);
            addItem(tmpItem);
            sessionListMap[historysession.id] = tmpItem;
        }
    }
}

void CDoodSessionListManager::onSessionMessageNotice(QString targetId, QString msgId, QString lastMsg, QString time,
                                                     QString name, QString avater,QString unreadmsg)
{
    qDebug() << Q_FUNC_INFO<<"1111111111111111111111111111"<<unreadmsg;

    if(sessionListMap.contains(targetId)){
        CDoodSessionListItem* item = sessionListMap.value(targetId);
        if(item != NULL){
            item->setLastMsg(lastMsg);
            item->setMsgTime(time);
            item->setLastMsgid(msgId);
            QString URC=item->unReadCount();
            if(unreadmsg=="1"){//未读数+1
                int count;
                if(URC!="")
                {
                    count=URC.toInt()+1;
                }
                else
                {
                    count=1;
                }
                item->setUnReadCount(QString::number(count));
                int index = indexOf(item);
                if(index>0 && index <itemCount()){
                    item = (CDoodSessionListItem*)takeItemAt(index);
                    addItemBegin(item);
                }
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
        if(unreadmsg=="1"){
            tmpItem->setUnReadCount("1");
        }
        tmpItem->setLastMsgid(msgId);
        addItemBegin(tmpItem);
        sessionListMap[targetId] = tmpItem;
        qDebug() << Q_FUNC_INFO << "name:" << name;
    }
}

void CDoodSessionListManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(chatListChanged(const Chat_UIList &)), this, SLOT(onChatListChanged(const Chat_UIList &)));
    connect(m_pClient, SIGNAL(sessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)), this, SLOT(onSessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)));
}
