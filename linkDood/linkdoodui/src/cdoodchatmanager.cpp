#include "cdoodchatmanager.h"
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
    connect(m_pClient,SIGNAL(getMessagesResult(bool,int64,MsgList&)),this,
            SLOT(onChatGetMessagesResult(bool,int64,MsgList&)));
    connect(m_pClient,SIGNAL(removeChatResult(bool)),this,
            SLOT(onChatRemoveChatResult(bool)));
/*    connect(m_pClient,SIGNAL(),this,
            SLOT())*/;
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

}

void CDoodChatManager::sendText(QString fromId,QString text)
{
    qDebug() << Q_FUNC_INFO << "send Text:" << text;
    MsgText msgText;
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

void CDoodChatManager::getMessages(int64 targetid, int64 msgid, int count, int flag)
{
     qDebug() << Q_FUNC_INFO;
     m_pClient->getMessages(targetid,msgid,count,flag);
}

void CDoodChatManager::removeChat(int64 targetid)
{
     qDebug() << Q_FUNC_INFO;
     m_pClient->removeChat(targetid);
}

void CDoodChatManager::setMessageRead(int64 targetid, int64 msgid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->setMessageRead(targetid,msgid);
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

void CDoodChatManager::onChatAvatarChanged(int64 id, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    emit chatAvatarChanged(id,avatar);
}

void CDoodChatManager::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit offlineMsgNotice(msgList);
}

void CDoodChatManager::onChatMessageNotice(Msg &msg)
{
    qDebug() << Q_FUNC_INFO;
    emit newMessageNotice(msg);
}

void CDoodChatManager::onChatSendMessageResult(bool code, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO;
    emit sendMessageResult(code,sendTime,msgId);
}

void CDoodChatManager::onChatGetMessagesResult(bool code, int64 sessionId, MsgList &msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit getMessagesResult(code,sessionId,msgList);
}

void CDoodChatManager::onChatRemoveChatResult(bool code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatResult(code);
}
