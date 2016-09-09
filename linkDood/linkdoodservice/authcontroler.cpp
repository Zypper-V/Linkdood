#include "authcontroler.h"
#include<iostream>
#include<QDebug>

#include "IMClient.h"
#include "IAuthService.h"
#include "INotifyService.h"
#include "LoginInfo.hpp"
#include "Account.h"
#include "linkdoodservice.h"
#include<QDateTime>


AuthControler::AuthControler(QObject *parent)
    :QObject(parent)
{
    init();
    m_net=new CNetworkManager();
    initConnects();
}

void AuthControler::login(const QString &server, const QString &userId, const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    service::IMClient::getClient()->getAuth()->login(userId.toStdString(),
                                                     password.toStdString(),
                                                     server.toStdString(),
                                                     std::bind(&AuthControler::_loginResult,this,std::placeholders::_1,std::placeholders::_2));
}

void AuthControler::autoLogin(QString userid, QString service)
{
    qDebug() << Q_FUNC_INFO<<userid<<service;
    int64 id=userid.toLongLong();
    std::string ser=service.toStdString();

    int64 code=service::IMClient::getClient()->getAuth()->login(id,ser,std::bind(&AuthControler::_loginResult,this,std::placeholders::_1,std::placeholders::_2));
    qDebug() << Q_FUNC_INFO<<"sssssssssssssssssssssssssssssss:"<<code;
}

void AuthControler::getVerifyImg(QString userid, QString code)
{
    qDebug() << Q_FUNC_INFO<<userid<<code;
    service::IMClient::getClient()->getAuth()->verifyImgCode(userid.toStdString(),code.toStdString(),
                                                             std::bind(&AuthControler::_getVerifyImg,this,std::placeholders::_1,std::placeholders::_2));
}

void AuthControler::_getVerifyImg(service::ErrorInfo info, std::string img)
{
    qDebug() << Q_FUNC_INFO<<info.code()<<img.c_str();
    if(img!=""){
        img="file://"+img;
    }
    emit getVerifyImgResult(QString::number(info.code()),QString::fromStdString(img));
}

void AuthControler::changepassword(QString oldpsw, QString newpsw)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getAuth()->changePassword(oldpsw.toStdString(),newpsw.toStdString(),
                                                              std::bind(&AuthControler::_changepassword,this,std::placeholders::_1));
}

void AuthControler::_changepassword(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<info.code();
    if(info.code()==0){
        emit changePasswordResult("修改成功");
    }
    else if(info.code()==543){
        emit changePasswordResult("旧密码不正确");
    }
    else{
        emit changePasswordResult("修改失败");
    }
}

void AuthControler::logout()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = LinkDoodService::instance()->dataPath()+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("myId","");
    settings.setValue("myName","");
    service::IMClient::getClient()->getAuth()->logout();
}

//void AuthControler::getUserInfo(QString &userId,QString& name,QString& avater)
//{
//    qDebug() << Q_FUNC_INFO;
//    userId = QString::number(mpUserInfo->id);
//    name   = QString::fromStdString(mpUserInfo->name);
//    avater = QString::fromStdString(mpUserInfo->thumb_avatar);
//}

QString AuthControler::UserId()
{
    //qDebug() << Q_FUNC_INFO <<"Id:" << mpUserInfo->id;
    QString fileName = LinkDoodService::instance()->dataPath()+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    QString myId = settings.value("myId","").toString();
    qDebug() << Q_FUNC_INFO << myId;
    return myId;

    //return QString::number(mpUserInfo->id);
}

QString AuthControler::userName()
{
    //qDebug() << Q_FUNC_INFO <<"userName:" << mpUserInfo->name.c_str();

    QString fileName = LinkDoodService::instance()->dataPath()+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    QString myName = settings.value("myName","").toString();
    qDebug() << Q_FUNC_INFO << "sfdgxdfgxfhfgxh:"<<myName;
    return myName;
    //return QString::fromStdString(mpUserInfo->name);
}

void AuthControler::getLoginHistory()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getAuth()->getLoginHistory(
                std::bind(&AuthControler::_getLoginHistory,this,
                          std::placeholders::_1));
}

void AuthControler::setLoginInfo(int flag, QString userid, QString username, QString avatar)
{
    qDebug() << Q_FUNC_INFO<<userid;
    service::IMClient::getClient()->getAuth()->setLoginInfo(
                flag,userid.toLongLong(),"",
                avatar.toStdString(),username.toStdString());
}

void AuthControler::getAccountInfo()
{
    service::IMClient::getClient()->getAuth()->getAccountInfo();
}

void AuthControler::updateAccountInfo(Contact user)
{
    qDebug() << Q_FUNC_INFO << "ssssssssssssss:" << user.name;
    service::Account item;
    if(user.avatar != ""){
        item.__set_avatar(user.avatar.toStdString());
    }
    if(user.thumbAvatar != ""){
        item.__set_thumb_avatar(user.thumbAvatar.toStdString());
    }
    if(user.name != ""){
        item.__set_name(user.name.toStdString());
    }
    item.__set_id(user.id.toLongLong());

    if(user.gender != ""){
        if(user.gender == "保密"){
            item.__set_gender(0);
        }
        if(user.gender == "男"){
            item.__set_gender(1);
        }
        if(user.gender == "女"){
            item.__set_gender(2);
        }
        //item.__set_birthday(QDateTime::currentMSecsSinceEpoch());
    }
    if(user.nick_id != ""){
        item.__set_nick_id(user.nick_id.toStdString());
    }
    if(user.birthday != ""){
        item.__set_birthday(user.birthday.toLongLong());
    }
    qDebug() << Q_FUNC_INFO << "end:" << user.name;

    service::IMClient::getClient()->getAuth()->updateAccountInfo(item,std::bind(&AuthControler::_updateAccountInfo,this,std::placeholders::_1));
}

void AuthControler::init()
{
   // mpUserInfo = std::make_shared<service::User>();
    service::IMClient::getClient()->getNotify()->setAuthObserver(this);
}

//void AuthControler::login(const QString &server, const QString &userId, const QString &password)
//{
//    qDebug() << Q_FUNC_INFO << server << userId << password;
//    service::IMClient::getClient()->getAuth()->login(userId.toStdString(),
//                                  password.toStdString(),
//                                  server.toStdString(),
//                                  std::bind(&AuthControler::_loginResult,this,std::placeholders::_1,std::placeholders::_2));
//}

void AuthControler::onConnectChanged(int flag)
{
    qDebug() << Q_FUNC_INFO<<"lixinlixinlixinlixinlixin"<<flag;
    if(flag==0){
        emit connectChanged("");
    }
    else{
        emit connectChanged("服务器连接中...");
    }
}

void AuthControler::onLoginResultObserver(service::ErrorInfo& info, int64 userid)
{
    qDebug() << Q_FUNC_INFO << "chengcy0000000000000" << info << userid;
    emit loginResultObserver(info.code(),QString::number(userid));
}

void AuthControler::onDBUpdateFinished(int val)
{
    qDebug() << Q_FUNC_INFO<<val<<"     "<<"pspspspspspspspspspspspspspspspsps";
}

void AuthControler::onLogoutChanged(service::ErrorInfo& info)
{
    qDebug() << Q_FUNC_INFO << "loginout_code:" << info.code();

    if(info.code() == 0 ||info.code() == 1304||info.code()<0)
    {
        emit loginoutRelust(true);
    }else
    {
        emit loginoutRelust(false);
    }
}

void AuthControler::onAccountInfoChanged(service::User& info)
{
    qDebug() << Q_FUNC_INFO;

    QString fileName = LinkDoodService::instance()->dataPath()+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("myName",QString::fromStdString(info.name));
    settings.setValue("myId",QString::number(info.id));
    //emit loginResultObserver(0,QString::number(info.id));
    //推送用户信息
    service::Account& account = dynamic_cast<service::Account&>(info);
    Contact user;
    qDebug()<<Q_FUNC_INFO<<"name:"<<account.name.c_str()<<"gender:"<<account.gender<<"phone:"<<account.phone.c_str()<<"link_id:"<<account.nick_id.c_str();
    if((account.__isset.nick_id||account.nick_id != "") && (account.nick_id != "#")){
        QString tmp = QString::fromStdString(account.nick_id);
        QStringList list = tmp.split("/");
        if(list.size() == 2){
             user.nick_id = list.at(0);
        }else{
            user.nick_id = tmp;
        }
        qDebug()<<Q_FUNC_INFO<<"ssssssssssssssssssssss1";
    }

    if(account._user_isset.avatar){
        user.avatar = QString::fromStdString(account.avatar);
        qDebug()<<Q_FUNC_INFO<<"ssssssssssssssssssssss1";
    }
    if(account._user_isset.thumb_avatar){
        user.thumbAvatar = QString::fromStdString(account.thumb_avatar);
        qDebug()<<Q_FUNC_INFO<<"ssssssssssssssssssssss2";
    }

    if(account._user_isset.name){
        user.name = QString::fromStdString(account.name);
        qDebug()<<Q_FUNC_INFO<<"ssssssssssssssssssssss3";
    }

    if(account._user_isset.gender){
        user.gender = genderConvert(account.gender);
        qDebug()<<Q_FUNC_INFO<<"ssssssssssssssssssssss4";
    }
    user.id = QString::number(info.id);
    if(account.__isset.email && account.email != "#"){
        user.email = QString::fromStdString(account.email);
    }
    if(account.__isset.phone && account.phone != "#"){

        user.phone = QString::fromStdString(account.phone);
        if(user.phone.startsWith("0086")){
            user.phone.remove("0086");
        }
    }
    if(account.__isset.birthday){
        if(account.birthday > 0){
            qDebug()<<Q_FUNC_INFO<<"birthDay:"<<account.birthday;
            //QDateTime time = QDateTime::fromMSecsSinceEpoch(account.birthday);
            user.birthday = QString::number(account.birthday);
        }
    }
    emit accountInfoChanged(user);
}

void AuthControler::onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey)
{
    qDebug() << Q_FUNC_INFO;
}

void AuthControler::onPasswordRuleChanged(service::ErrorInfo& info, int16 rule)
{

}

void AuthControler::onAvatarChanged(std::string avatar)
{
    qDebug() << Q_FUNC_INFO << "avatar:" << avatar.c_str();
    if(!avatar.empty()){
        emit anthAvatarChanged(QString::fromStdString(avatar));
    }
}

void AuthControler::setPrivateSetting(IMPrivateSetting imps)
{
    qDebug() << Q_FUNC_INFO;
    PrivateSetting ps;
    ps.allow_birthday = imps.allow_birthday;
    ps.allow_phone = imps.allow_phone;
    ps.allow_email = imps.allow_email;
    ps.verifytype = imps.verifytype;
    ps.vip_noticetype = imps.vip_noticetype;
    ps.at_noticetype = imps.at_noticetype;
    ps.global_noticetype = imps.global_noticetype;

    service::IMClient::getClient()->getAuth()->setPrivateSetting(ps, std::bind(&AuthControler::onSetPrivateSetting, this, std::placeholders::_1));
}

void AuthControler::getPrivateSetting()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getAuth()->getPrivateSetting(std::bind(&AuthControler::onGetPrivateSetting, this, std::placeholders::_1, std::placeholders::_2));
}

void AuthControler::onNetworkStatusChanged(bool connected, CNetworkManager::NetworkType type)
{
    qDebug() << Q_FUNC_INFO<<"sssssssssssxinxinxinxinxinxinxin";
    if(connected){
        emit connectChanged("");
    }
    else{
        emit connectChanged("网络连接中...");
    }

}

void AuthControler::onSetPrivateSetting(int code)
{
    qDebug() << Q_FUNC_INFO << "code:" << code;
    emit setPrivateSettingResult(code);
}

void AuthControler::onGetPrivateSetting(int code, PrivateSetting ps)
{
    qDebug() << Q_FUNC_INFO << "code:" << code;
    IMPrivateSetting imps;
    imps.allow_birthday = ps.allow_birthday;
    imps.allow_phone = ps.allow_phone;
    imps.allow_email = ps.allow_email;
    imps.verifytype = ps.verifytype;
    imps.vip_noticetype = ps.vip_noticetype;
    imps.at_noticetype = ps.at_noticetype;
    imps.global_noticetype = ps.global_noticetype;

    emit getPrivateSettingResult(code, imps);
}

void AuthControler::initConnects()
{
    qDebug() << Q_FUNC_INFO<<"chushihuachushihua";
    QObject::connect(m_net,SIGNAL(networkStatusChanged(bool,CNetworkManager::NetworkType)),this,SLOT(onNetworkStatusChanged(bool, CNetworkManager::NetworkType)));

}

void AuthControler::_getLoginHistory(std::vector<service::LoginInfo> list)
{
    qDebug() << Q_FUNC_INFO;
    LoginInfoList historyList;

    for(auto item:list)
    {
        LoginInfo loginItem;
        loginItem.account  = QString::fromStdString(item.account);
        loginItem.name     = QString::fromStdString(item.name);
        loginItem.server   = QString::fromStdString(item.server);
        loginItem.userIcon = QString::fromStdString(item.user_icon);
        loginItem.areaNum  = QString::fromStdString(item.area_num);

        loginItem.isAutoLogin = item.isAutoLogin;
        loginItem.status = item.status;
        loginItem.isRemberPass = item.isRemberPass;
        loginItem.userId = item.userId;
        loginItem.lastLoginTime = item.last_login_time;

        historyList.insert(historyList.size(),loginItem);
        qDebug() << Q_FUNC_INFO<<loginItem.userId<<"time:"<<item.last_login_time;
    }
    emit getLoginHistoryResult(historyList);
}

void AuthControler::_loginResult(service::ErrorInfo &info, long long userId)
{
    qDebug() << Q_FUNC_INFO << info.code() << userId;
    if(info.code() == 0 )
    {
        QString fileName = LinkDoodService::instance()->dataPath()+ "config.ini";
        QSettings settings(fileName, QSettings::IniFormat);
        settings.setValue("myId",QString::number(userId));
        emit loginSucceeded(QString::number(userId));

        emit loginResultObserver(0,QString::number(userId));
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "loginFailed = " << info.code();
        emit loginFailed(info.code());
    }
}

void AuthControler::_updateAccountInfo(service::ErrorInfo &info)
{
    //TODO
}


