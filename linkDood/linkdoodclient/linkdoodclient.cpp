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
    initDBusConnect();
}

LinkDoodClient::~LinkDoodClient()
{

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

void LinkDoodClient::initDBusConnect()
{
    qDebug() << Q_FUNC_INFO;
}
