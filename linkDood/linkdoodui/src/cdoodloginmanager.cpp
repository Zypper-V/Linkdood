#include "cdoodloginmanager.h"

#include <QMetaType>
#include <QDebug>

CDoodLoginManager::CDoodLoginManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client),mLoginCount(0),mNVerifyImgCount(0)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodLoginManager*>();
    initConnect();

}

void CDoodLoginManager::text(QString param)
{
    emit textPareams(param);
}

QString CDoodLoginManager::lastLoginAccountName()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName =QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return  settings.value("lastLoginAccountName","").toString();
}

void CDoodLoginManager::setLastLoginAccountName(QString accountName)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName =QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    accountName.remove(":1");
    accountName.remove(":7");
    settings.setValue("lastLoginAccountName",accountName);
}

QString CDoodLoginManager::lastLoginAccountUserId()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName =QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return  settings.value("lastLoginAccountUserId","").toString();
}

void CDoodLoginManager::setLastLoginAccountUserId(QString userId)
{
    QString fileName =QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("lastLoginAccountUserId",userId);
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
    if(newpsw.size()<6){
        emit illegalPassword("新密码长度不能低于6位");
        return;
    }
    if(newpsw.size()>32){
        emit illegalPassword("新密码长度不能高于32位");
        return;
    }
    for(int i=0;i<newpsw.size();i++){
        if(newpsw.toStdString().substr(i,1)==" "){
            emit illegalPassword("密码中不能含有空格");
            return;
        }
    }

    m_pClient->changepassword(oldpsw, newpsw);
}

void CDoodLoginManager::login(const QString &server,
                              const QString &userId,
                              const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    std::string id;
    id=userId.toStdString();
    mVerifyId=QString::fromStdString((id.substr(0,id.size()-2)));
    m_pClient->login(server, userId, password);

    setLastLoginAccountName(userId);
}

void CDoodLoginManager::loginByUrl()
{
    QStringList info = loginInfoByUrl().split(":");
    if(info.size() == 2){
        m_pClient->login(getLoginServiceId(),info.at(0)+":7",info.at(1));
    }
}

void CDoodLoginManager::autoLogin(QString id, QString service)
{
    qDebug() << Q_FUNC_INFO<<id<<service;
    m_pClient->autoLogin(id,service);
}

void CDoodLoginManager::getVerifyImg(QString userid, QString code)
{
    qDebug() << Q_FUNC_INFO<<userid<<code<<"ssssssssssssssssss";
    m_pClient->getVerifyImg(mVerifyId,code);
}

void CDoodLoginManager::openUrl(QString url)
{
//    QWebView *view = new QWebView(parent);
//    view->load(QUrl(url));
//    view->show();
//    qDebug()<<Q_FUNC_INFO<<"open url code:"<<code;
}

//void CDoodLoginManager::autoLoginLastAccount()
//{
//    QString service;
//    QString id;
//    QString psw;
//    getLastLoginAccount(service,id,psw);
//    qDebug() << Q_FUNC_INFO<<service<<id<<psw;
//    m_pClient->login(service, id, psw);
//    emit autoLogin();
//}

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

void CDoodLoginManager::setLoginInfoByUrl(QString loginInfo)
{
    QString fileName = QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("loginInfo",loginInfo);
}

QString CDoodLoginManager::loginInfoByUrl()
{
    QString fileName = QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("loginInfo","").toString();
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

void CDoodLoginManager::setLoginPhoneId(QString id)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("PhoneId",id);
}

void CDoodLoginManager::setLoginServiceId(QString service)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("ServiceId",service);
}

QString CDoodLoginManager::getLoginPhoneId()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("PhoneId","").toString();
}

QString CDoodLoginManager::getLoginServiceId()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("ServiceId","").toString();
}

bool CDoodLoginManager::isStartupByUrl()
{

    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    bool value = settings.value("startupByUrl",false).toBool();
    qDebug() << Q_FUNC_INFO<<":"<<value;
    return value;
}

void CDoodLoginManager::setIsStartupByUrl(bool isByUrl)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("startupByUrl",isByUrl);
}

//void CDoodLoginManager::setLastLoginAccount(QString service, QString id, QString psw)
//{
//    qDebug() << Q_FUNC_INFO;
//    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
//    QSettings settings(fileName, QSettings::IniFormat);
//    settings.setValue("LastService",service);
//    settings.setValue("LastId",id);
//    settings.setValue("LastPsw",psw);
//}

//void CDoodLoginManager::getLastLoginAccount(QString &service, QString &id, QString &psw)
//{
//    qDebug() << Q_FUNC_INFO;
//    QString fileName = "/data/data/com.vrv.linkDood/config.ini";
//    QSettings settings(fileName, QSettings::IniFormat);
//    service=settings.value("LastService","").toString();
//    id=settings.value("LastId","").toString();
//    psw=settings.value("LastPsw","").toString();
//}

QString CDoodLoginManager::verifyImg()
{
    qDebug() << Q_FUNC_INFO;
    return mVerifyImg;
}

void CDoodLoginManager::setVerifyImg(QString verifyImg)
{
    qDebug() << Q_FUNC_INFO;
    mVerifyImg=verifyImg;
    emit verifyImgChanged();
}

int CDoodLoginManager::nVerifyImgCount()
{
    qDebug() << Q_FUNC_INFO;
    return mNVerifyImgCount;
}

void CDoodLoginManager::setNVerifyImgCount(int count)
{
    qDebug() << Q_FUNC_INFO;
    mNVerifyImgCount=count;
    emit nVerifyImgCountChanged();
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

void CDoodLoginManager::onSwitchLoginByUrl()
{
    emit switchLoginByUrl();
}

void CDoodLoginManager::onSwitchChatPageByUrl()
{
    emit switchChatPageByUrl();
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
    mLoginCount=0;
    setNVerifyImgCount(0);
    emit loginSucceeded();
    setAppLoginStatus(1);

    setLoginInfo(4,m_pClient->UserId(),lastLoginAccountName(),"");
    setLastLoginAccountUserId(m_pClient->UserId());
}

void CDoodLoginManager::onGetVerifyImgResult(QString code, QString img)
{
    qDebug() << Q_FUNC_INFO<<code<<img<<"sssssss";
    setVerifyImg(img);
    setNVerifyImgCount(++mNVerifyImgCount);
    if(code=="0"){
        mLoginCount=0;
        emit getVerifyImgResult("","验证成功,请重新登录");
    }
    else if(code=="103")
    {
        emit getVerifyImgResult("1","验证码输入错误,请重新输入");
    }
    else if(code=="104"){
        emit getVerifyImgResult("1","");
    }
    else if(code=="11100"){
        mLoginCount=0;
        emit getVerifyImgResult("","无法回避的内部错误,服务无法找到");
    }
    else{
        mLoginCount=0;
        emit getVerifyImgResult("","未知错误");
    }




}

void CDoodLoginManager::onLoginFailed(QString err)
{
    qDebug() << Q_FUNC_INFO << "login err:" << err;
    if(err=="帐号密码不匹配"){
        mLoginCount++;
    }
    if(err=="输入错误次数过多,请输入验证码"){
        getVerifyImg(mVerifyId,"");
    }
    emit loginFailed(err);
}

void CDoodLoginManager::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << "loginout:" << loginout;
    emit loginoutRelust(loginout);
    if(isStartupByUrl()){
        emit siwtchLoginout();
    }
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
        int last = 0;
        QString lastId = QString::number(list[last].userId);
        QString iniUserId = lastLoginAccountUserId();

        if(iniUserId != "" && lastId != iniUserId){

            for(int i=0;i<list.size();++i){
                if(iniUserId.toLongLong() == list.at(i).userId){
                    emit getLoginHistoryResult(iniUserId,list[i].server);
                    return;
                }
            }
        }else{
          emit getLoginHistoryResult(lastId,list[last].server);
        }

    }
    else{
        emit getLoginHistoryResult("","");
    }
    for(size_t i=0;i<list.size();++i)
    {
        QString name;
        QString id;
        name=list[i].name;
        id=QString::number(list[i].userId);
        qDebug()<< Q_FUNC_INFO<<"lasthistroty:"<<id;
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
    connect(m_pClient, SIGNAL(getVerifyImgResult(QString,QString)), this, SLOT(onGetVerifyImgResult(QString,QString)));
    connect(m_pClient, SIGNAL(changePasswordResult(QString)), this, SLOT(onChangePasswordResult(QString)));
    connect(m_pClient, SIGNAL(loginoutRelust(bool)), this, SLOT(onLoginoutRelust(bool)));
    connect(m_pClient, SIGNAL(loginSucceeded()), this, SLOT(onLoginSucceeded()));
    connect(m_pClient, SIGNAL(loginResultObserver(int,QString)), this, SLOT(onLoginResultObserver(int,QString)));
    connect(m_pClient, SIGNAL(loginFailed(QString)), this, SLOT(onLoginFailed(QString)));
    connect(m_pClient, SIGNAL(getLoginHistoryResult(LoginInfoList)), this, SLOT(onGetLoginHistoryResult(LoginInfoList)));
    connect(m_pClient, SIGNAL(serviceRestart()), this, SLOT(onServiceRestart()));

}
