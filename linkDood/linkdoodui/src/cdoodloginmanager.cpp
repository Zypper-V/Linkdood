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
    qDebug() << Q_FUNC_INFO;
    QString fileName ="/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("Status",0);
}

void CDoodLoginManager::changepassword(QString oldpsw, QString newpsw)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->changepassword(oldpsw, newpsw);
}

void CDoodLoginManager::login(const QString &server,
                              const QString &userId,
                              const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    m_pClient->login(server, userId, password);
    //    m_pClient->installPath();
    //getLoginHistory();
}

int CDoodLoginManager::getAppLoginStatus()
{
    qDebug() << Q_FUNC_INFO << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
    return m_pClient->getAppLoginStatus();
}

void CDoodLoginManager::setAppLoginStatus(const int status)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->setAppLoginStatus(status);
}
void CDoodLoginManager::setLoginPhone(QString phone)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("Phone",phone);
}
void CDoodLoginManager::setLoginService(QString service)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("Service",service);
}

QString CDoodLoginManager::getLoginPhone()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("Phone","").toString();
}

QString CDoodLoginManager::getLoginService()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("Service","").toString();
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

int CDoodLoginManager::loginStatus()
{
    return getAppLoginStatus();
}

void CDoodLoginManager::onElsewhereLogin(QString tip)
{
    emit elsewhereLogin(tip);
}

QString CDoodLoginManager::userId()
{
    qDebug() << Q_FUNC_INFO;
    //mUserId = m_pClient->UserId();
    QString fileName = QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    mUserId = settings.value("myId","").toString();
    qDebug()<<Q_FUNC_INFO<<"sddfdfhfhdfh:" << mUserId;
    return mUserId;
}

void CDoodLoginManager::setUserId(QString userId)
{
    mUserId = m_pClient->UserId();
    emit userIdChanged();
}

bool CDoodLoginManager::windowFocus() const
{
    return m_bWindowFocus;
}

bool CDoodLoginManager::setWindowFocus(const bool &windowFocus)
{
    if(windowFocus) {
        //        clearNotifications();
        //        clearBadge();
    }

    m_bWindowFocus = windowFocus;
    emit windowFocusChanged();
    return windowFocus;
}

//QString CDoodLoginManager::user() const
//{
//    qDebug() << Q_FUNC_INFO;
//    return mUser;
//}

//QString CDoodLoginManager::server() const
//{
//    return mServer;
//}

//QString CDoodLoginManager::password() const
//{
//    return mPassword;
//}

//void CDoodLoginManager::setUser(QString user)
//{
//    mUser = user;
//    emit userChanged();
//}

//void CDoodLoginManager::setServer(QString server)
//{
//    mServer = server;
//    emit serverChanged();
//}

//void CDoodLoginManager::setPassword(QString password)
//{
//    mPassword = password;
//    emit passwordChanged();
//}

void CDoodLoginManager::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();
    setAppLoginStatus(1);
}

void CDoodLoginManager::onLoginFailed(QString err)
{
    qDebug() << Q_FUNC_INFO << "login err:" << err;
    emit loginFailed(err);
}

void CDoodLoginManager::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << "loginout:" << loginout;
    emit loginoutRelust(loginout);
}

void CDoodLoginManager::onChangePasswordResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit changePasswordResult(result);
}

void CDoodLoginManager::onGetLoginHistoryResult(LoginInfoList list)
{
    qDebug() << Q_FUNC_INFO << "LoginHistorySize:" << list.size();
    if(list.size()>0){
        //setUser(list[0].name);
        //setServer(list[0].areaNum);
    }
}

void CDoodLoginManager::onLoginResultObserver(int code, QString userID)
{
    qDebug() << Q_FUNC_INFO << "user:" << userID;
    mUserId = userID;
    emit loginResultObserver(code,userID);
}

void CDoodLoginManager::onServiceRestart()
{
    qDebug() << Q_FUNC_INFO<<"0000000000000000000000000";
    emit serviceRestart();
}

void CDoodLoginManager::initConnect()
{
    connect(m_pClient, SIGNAL(elsewhereLogin(QString)), this, SLOT(onElsewhereLogin(QString)));
    connect(m_pClient, SIGNAL(changePasswordResult(QString)), this, SLOT(onChangePasswordResult(QString)));
    connect(m_pClient, SIGNAL(loginoutRelust(bool)), this, SLOT(onLoginoutRelust(bool)));
    connect(m_pClient, SIGNAL(loginSucceeded()), this, SLOT(onLoginSucceeded()));
    connect(m_pClient, SIGNAL(loginResultObserver(int,QString)), this, SLOT(onLoginResultObserver(int,QString)));
    connect(m_pClient, SIGNAL(loginFailed(QString)), this, SLOT(onLoginFailed(QString)));
    connect(m_pClient, SIGNAL(getLoginHistoryResult(LoginInfoList)), this, SLOT(onGetLoginHistoryResult(LoginInfoList)));
    connect(m_pClient, SIGNAL(serviceRestart()), this, SLOT(onServiceRestart()));

}
