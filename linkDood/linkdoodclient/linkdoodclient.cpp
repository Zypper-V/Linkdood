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

void LinkDoodClient::initDBusConnect()
{
    qDebug() << Q_FUNC_INFO;

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginoutRelust",
                                          this, SLOT(onLoginoutRelust(bool)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginFailed",
                                          this, SLOT(onLoginFailed(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "contactListChanged",
                                          this, SLOT(onContactListChanged(ContactList)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginSucceeded",
                                          this, SLOT(onLoginSucceeded()));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatListChanged",
                                          this, SLOT(onChatListChanged(Chat_UIList)));
}
