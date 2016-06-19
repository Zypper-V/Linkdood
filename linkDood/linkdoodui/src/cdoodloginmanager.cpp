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
    getLoginHistory();
}

bool CDoodLoginManager::checkFirstWordIsSpace(const QString &text)
{
    return text.startsWith(" ");
}

void CDoodLoginManager::getLoginHistory()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getLoginHistory();
}

void CDoodLoginManager::setLoginInfo(int flag, QString userid, QString username, QString avatar)
{
     qDebug() << Q_FUNC_INFO;
     m_pClient->setLoginInfo(flag,userid,username,avatar);
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

void CDoodLoginManager::onGetLoginHistoryResult(LoginInfoList list)
{
    qDebug() << Q_FUNC_INFO << "LoginHistorySize:" << list.size();
}

void CDoodLoginManager::onLoginResultObserver(int code, QString userID)
{
      qDebug() << Q_FUNC_INFO << "user:" << userID;
      emit loginResultObserver(code,userID);
}

void CDoodLoginManager::initConnect()
{
    connect(m_pClient, SIGNAL(loginoutRelust(bool)), this, SLOT(onLoginoutRelust(bool)));
    connect(m_pClient, SIGNAL(loginSucceeded()), this, SLOT(onLoginSucceeded()));
    connect(m_pClient, SIGNAL(loginResultObserver(int,QString)), this, SLOT(onLoginResultObserver(int,QString)));
    connect(m_pClient, SIGNAL(loginFailed(QString)), this, SLOT(onLoginFailed(QString)));
    connect(m_pClient, SIGNAL(getLoginHistoryResult(LoginInfoList)), this, SLOT(onGetLoginHistoryResult(LoginInfoList)));
}
