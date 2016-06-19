#include "linkdoodclient.h"
#include "linkdoodconst.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>
#include <QDBusPendingReply>
#include <QDBusInterface>


LinkDoodClient::LinkDoodClient(QObject *parent) :
    QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    registerDoodDataTypes();

    initDBusConnect();
}

LinkDoodClient::~LinkDoodClient()
{

}

QString LinkDoodClient::installPath()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = manager.call("installPath");
    reply.waitForFinished();

    QString sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }

    return sTmp;
}

void LinkDoodClient::login(const QString &server,
                           const QString &userId,
                           const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("login", server, userId, password);
}

void LinkDoodClient::logout()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("logout");
}

void LinkDoodClient::removeChat(int64 targetid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("removeChat",targetid);
}

void LinkDoodClient::setMessageRead(int64 targetid, int64 msgid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setMessageRead",targetid,msgid);
}

void LinkDoodClient::sendMessage(const Msg& msg)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());

    QVariant v;
    v.setValue(msg);

    manager.call("sendMessage",v);
}

void LinkDoodClient::getMessages(int64 targetid, int64 msgid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getMessages",targetid,msgid,count,flag);
}

void LinkDoodClient::getEnterpriseSonOrgs(int64 orgid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getEnterpriseSonOrgs",orgid);
}

void LinkDoodClient::getLoginHistory()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getLoginHistory");
}

void LinkDoodClient::setLoginInfo(int flag, QString userid, QString username, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setLoginInfo",flag,userid,username,avatar);
}

void LinkDoodClient::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << loginout;
    emit loginoutRelust(loginout);
}

void LinkDoodClient::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();
}

void LinkDoodClient::onChatListChanged(const Chat_UIList &chats)
{
    qDebug() << Q_FUNC_INFO;
    emit chatListChanged(chats);
}

void LinkDoodClient::onContactListChanged(int oper, ContactList contacts)
{
    qDebug() << Q_FUNC_INFO;
    emit contactListChanged(oper,contacts);
}

void LinkDoodClient::onLoginFailed(QString err)
{
    qDebug() << Q_FUNC_INFO;
    emit loginFailed(err);
}

void LinkDoodClient::onGetEnterpriseSonOrgsResult(int code, OrgList orgList, OrgUserList orguserList)
{
    qDebug() << Q_FUNC_INFO;
    emit getEnterpriseSonOrgsResult(code,orgList,orguserList);
}

void LinkDoodClient::onChatAvatarChanged(int64 id, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    emit chatAvatarChanged(id,avatar);
}

void LinkDoodClient::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit offlineMsgNotice(msgList);
}

void LinkDoodClient::onChatMessageNotice(Msg &msg)
{
    qDebug() << Q_FUNC_INFO;
    emit newMessageNotice(msg);
}

void LinkDoodClient::onChatSendMessageResult(bool code, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO;
    emit sendMessageResult(code,sendTime,msgId);
}

void LinkDoodClient::onChatGetMessagesResult(bool code, int64 sessionId, MsgList &msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit getMessagesResult(code,sessionId,msgList);
}

void LinkDoodClient::onChatRemoveChatResult(bool code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatResult(code);
}

void LinkDoodClient::onGetLoginHistoryResult(LoginInfoList list)
{
    qDebug() << Q_FUNC_INFO;
    emit getLoginHistoryResult(list);
}

void LinkDoodClient::onLoginResultObserver(int code, QString userID)
{
    qDebug() << Q_FUNC_INFO;
    emit loginResultObserver(code,userID);
}

void LinkDoodClient::initDBusConnect()
{
    qDebug() << Q_FUNC_INFO;

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatAvatarChanged",
                                          this, SLOT(onChatAvatarChanged(int64,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "offlineMsgNotice",
                                          this, SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "newMessageNotice",
                                          this, SLOT(onChatMessageNotice(Msg&)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "sendMessageResult",
                                          this, SLOT(onChatSendMessageResult(bool,int64,int64)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getMessagesResult",
                                          this, SLOT(onChatGetMessagesResult(bool,int64,MsgList&)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "removeChatResult",
                                          this, SLOT(onChatRemoveChatResult(bool)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginoutRelust",
                                          this, SLOT(onLoginoutRelust(bool)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginFailed",
                                          this, SLOT(onLoginFailed(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "contactListChanged",
                                          this, SLOT(onContactListChanged(int,ContactList)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginSucceeded",
                                          this, SLOT(onLoginSucceeded()));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatListChanged",
                                          this, SLOT(onChatListChanged(Chat_UIList)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginResultObserver",
                                          this, SLOT(onLoginResultObserver(int,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getLoginHistoryResult",
                                          this, SLOT(onGetLoginHistoryResult(LoginInfoList)));
}
