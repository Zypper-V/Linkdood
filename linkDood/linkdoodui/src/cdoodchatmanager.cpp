#include "cdoodchatmanager.h"
#include "cdoodchatitem.h"

#include <QDebug>

void CDoodChatManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient,SIGNAL(chatAvatarChanged(int64,QString)),this,
            SLOT(onChatAvatarChanged(int64,QString)));
    connect(m_pClient,SIGNAL(offlineMsgNotice(IMOfflineMsgList)),this,
            SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    connect(m_pClient,SIGNAL(newMessageNotice(Msg&)),this,
            SLOT(onChatMessageNotice(Msg&)));
    connect(m_pClient,SIGNAL(sendMessageResult(bool,int64,int64)),this,
            SLOT(onChatSendMessageResult(bool,int64,int64)));
    connect(m_pClient,SIGNAL(getMessagesResult(bool,QString,MsgList)),this,
            SLOT(onChatGetMessagesResult(bool,QString,MsgList)));
    connect(m_pClient,SIGNAL(removeChatResult(bool)),this,
            SLOT(onChatRemoveChatResult(bool)));
    connect(m_pClient,SIGNAL(deleteMessagesResult(int)),this,
            SLOT(onChatDeleteMessagesResult(int)));

    /*    connect(m_pClient,SIGNAL(),this,
            SLOT())*/;
}

void CDoodChatManager::analyticalMessage(MsgList list)
{
    qDebug() << Q_FUNC_INFO << "size = " << list.size();

    if(list.size() <= 0) {
        return;
    }

    QList <QObject* > msglist;
    for(int i = 0; i < list.size(); ++i) {
        if(!m_oChatMap.contains(list.at(i).msgid)) {
            CDoodChatItem *pChatItem = new CDoodChatItem(this);
            pChatItem->setMsgType(list.at(i).msgtype);
            pChatItem->setActiveType(list.at(i).activeType);
            pChatItem->setMsgId(list.at(i).msgid);
            pChatItem->setTargetId(list.at(i).targetid);
            pChatItem->setFromId(list.at(i).fromid);
            pChatItem->setToId(list.at(i).toid);
            pChatItem->setTime(QDateTime::fromString(list.at(i).time, "yyyy-MM-dd hh:mm:ss"));
            pChatItem->setBody(list.at(i).body);

//            if(i == 0) {
//                pChatItem->setShowTime(true);
//            } else {
//                if(i - 1 >= 0) {
//                    pChatItem->setShowTime(checkTimeIsShow(p->lastMessageTime,pChatItem->sendTime()));
//                }
//            }

            msglist.append(pChatItem);
            m_oChatMap[list.at(i).msgid] = pChatItem;
            m_oLastMessageTime = QDateTime::fromString(list.at(i).time, "yyyy-MM-dd hh:mm:ss");
        }
    }

    if (msglist.size() <= 0) {
        return;
    }

    int nBeginIndexAndSize = 0;
    int nEndIndex = nBeginIndexAndSize + msglist.size() - 1;

    qDebug() << "Dood === nBeginIndex = " << nBeginIndexAndSize;
    qDebug() << "Dood === nEndIndex = " << nEndIndex;

#if 0
    beginInsertRows(QModelIndex(), nBeginIndexAndSize, nEndIndex);

    for(int i = msglist.size()-1; i>=0 ; --i) {
        _list->insert(nBeginIndexAndSize, msglist.at(i));
    }

    endInsertRows();
#else
    for(int i = msglist.size()-1; i>=0 ; --i) {
        addItemBegin(msglist.at(i));
    }
#endif
    emit itemCountChanged();
    m_sBeginMsgId = list.at(list.size() - 1).msgid;
}

CDoodChatManager::CDoodChatManager(LinkDoodClient *client, QObject *parent):
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodChatManager*>();
    initConnect();
}

CDoodChatManager::~CDoodChatManager()
{
    exitChat("");
}

void CDoodChatManager::sendText(QString fromId,QString text)
{
    qDebug() << Q_FUNC_INFO << "send Text:" << text;
    Msg msgText;
    msgText.body = text;
    msgText.msgtype = MSG_TYPE_TEXT;
    msgText.targetid = id();
    msgText.toid = id();
    msgText.fromid = fromId;

    sendMessage(msgText);
}

void CDoodChatManager::sendMessage(Msg &msg)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->sendMessage(msg);
}

void CDoodChatManager::getMessages(QString targetid, QString msgid, int count, int flag)
{
     qDebug() << Q_FUNC_INFO;
     m_pClient->getMessages(targetid,m_sBeginMsgId,count,1);
}

void CDoodChatManager::removeChat(QString targetid)
{
     qDebug() << Q_FUNC_INFO;
     m_pClient->removeChat(targetid);
}

void CDoodChatManager::setMessageRead(QString targetid, QString msgid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->setMessageRead(targetid,"0");
}

void CDoodChatManager::getUnReadMessages()
{
     qDebug() << Q_FUNC_INFO;
     m_pClient->getUnReadMessages();
}

void CDoodChatManager::deleteMessage(QString targetid, QStringList msgs)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->deleteMessage(targetid,msgs);
}

QString CDoodChatManager::id() const
{
    qDebug() << Q_FUNC_INFO;
    return mId;
}

void CDoodChatManager::setId(const QString &id)
{
    qDebug() << Q_FUNC_INFO;
    mId = id;
    emit idChanged();
}

QString CDoodChatManager::name() const
{
    qDebug() << Q_FUNC_INFO;
    return mName;
}

void CDoodChatManager::setName(const QString &name)
{
    qDebug() << Q_FUNC_INFO;
    mName = name;
    emit nameChanged();
}

void CDoodChatManager::entryChat(const QString &targetid)
{
    qDebug() << Q_FUNC_INFO << targetid;
}

void CDoodChatManager::exitChat(const QString &targetid)
{
    qDebug() << Q_FUNC_INFO << targetid;
}

void CDoodChatManager::deleteMessageListItem()
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodChatManager::showChatPage(QString chatName,
                                    QString targetid,
                                    QString chatType,
                                    QString icon)
{
    qDebug() << Q_FUNC_INFO;
    emit sendShowChatPage(chatName, targetid, chatType, icon);
}

void CDoodChatManager::initChatState()
{
    qDebug() << Q_FUNC_INFO;
    m_sBeginMsgId = "";
}

void CDoodChatManager::onChatAvatarChanged(int64 id, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    emit chatAvatarChanged(id,avatar);
}

void CDoodChatManager::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO << msgList.size();
    emit offlineMsgNotice(msgList);
}

void CDoodChatManager::onChatMessageNotice(Msg &msg)
{
    qDebug() << Q_FUNC_INFO << "newMessage:" << msg.body;
    emit newMessageNotice(msg);
}

void CDoodChatManager::onChatSendMessageResult(bool code, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO;
    emit sendMessageResult(code,sendTime,msgId);
}

void CDoodChatManager::onChatGetMessagesResult(bool code, QString sessionId, MsgList msgList)
{
    qDebug() << Q_FUNC_INFO << code << sessionId << msgList.size();

}

void CDoodChatManager::onChatRemoveChatResult(bool code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatResult(code);
}

void CDoodChatManager::onChatDeleteMessagesResult(int code)
{

}
