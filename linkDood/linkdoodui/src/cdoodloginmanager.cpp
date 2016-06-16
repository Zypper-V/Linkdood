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
    if (m_pClient) {
        delete m_pClient;
        m_pClient = 0;
    }
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

void CDoodLoginManager::initConnect()
{
    connect(m_pClient, SIGNAL(loginSucceeded()), this, SLOT(onLoginSucceeded()));
}
