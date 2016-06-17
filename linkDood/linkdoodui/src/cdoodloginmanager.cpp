#include "cdoodloginmanager.h"

#include <QMetaType>
#include <QDebug>

CDoodLoginManager::CDoodLoginManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodLoginManager*>();
    initConnect();
}

CDoodLoginManager::~CDoodLoginManager()
{

}

void CDoodLoginManager::logout()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->logout();
}

void CDoodLoginManager::login(const QString &server,
                              const QString &userId,
                              const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    m_pClient->login(server, userId, password);
//    m_pClient->installPath();
}

bool CDoodLoginManager::checkFirstWordIsSpace(const QString &text)
{
    return text.startsWith(" ");
}

void CDoodLoginManager::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();
}

void CDoodLoginManager::onLoginFailed(QString err)
{
    qDebug() << Q_FUNC_INFO << "login err:" << err;
    emit loginFailed(err);
}

void CDoodLoginManager::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO;
    emit loginoutRelust(loginout);
}

void CDoodLoginManager::initConnect()
{
    connect(m_pClient, SIGNAL(loginoutRelust(bool)), this, SLOT(onLoginoutRelust(bool)));
    connect(m_pClient, SIGNAL(loginSucceeded()), this, SLOT(onLoginSucceeded()));
    connect(m_pClient, SIGNAL(loginFailed(QString)), this, SLOT(onLoginFailed(QString)));
}
