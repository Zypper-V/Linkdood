#include "authcontroler.h"
#include<iostream>
#include<QDebug>

#include "IMClient.h"
#include "IAuthService.h"
#include "INotifyService.h"
#include "LoginInfo.hpp"
#include "Account.h"
#include "linkdoodservice.h"

AuthControler::AuthControler(QObject *parent)
    :QObject(parent)
{
    init();
}

void AuthControler::login(const QString &server, const QString &userId, const QString &password)
{
    QString user("0086");

    QByteArray ba = userId.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;
    bool isNum = *s ? false:true;

    if(isNum && !userId.startsWith("0086"))
    {
        user = user+userId;
    }else
    {
       user = userId;
    }
    qDebug() << Q_FUNC_INFO << server << userId << password;
    service::IMClient::getClient()->getAuth()->login(user.toStdString(),
                                  password.toStdString(),
                                  server.toStdString(),
                                  std::bind(&AuthControler::_loginResult,this,std::placeholders::_1,std::placeholders::_2));
}

void AuthControler::logout()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getAuth()->logout();
}

void AuthControler::getUserInfo(QString &userId,QString& name,QString& avater)
{
    qDebug() << Q_FUNC_INFO;
    userId = QString::number(mpUserInfo->id);
    name   = QString::fromStdString(mpUserInfo->name);
    avater = QString::fromStdString(mpUserInfo->thumb_avatar);
}

QString AuthControler::UserId()
{
    return QString::number(mpUserInfo->id);
}

QString AuthControler::userName()
{
    return QString::fromStdString(mpUserInfo->name);
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
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getAuth()->setLoginInfo(
                flag,userid.toLongLong(),username.toStdString(),
                avatar.toStdString());
}

void AuthControler::init()
{
    mpUserInfo = std::make_shared<service::User>();
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
        qDebug() << Q_FUNC_INFO;
}

void AuthControler::onLoginResultObserver(service::ErrorInfo& info, int64 userid)
{
     qDebug() << Q_FUNC_INFO << "chengcy0000000000000" << info << userid;
     emit loginResultObserver(info.code(),QString::number(userid));
}

void AuthControler::onDBUpdateFinished(int val)
{
    qDebug() << Q_FUNC_INFO;
}

void AuthControler::onLogoutChanged(service::ErrorInfo& info)
{
    qDebug() << Q_FUNC_INFO << "code:" << info.code();
    if(info.code() == 0)
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
     qDebug()<<"name:"<<info.name.c_str()<<"sex:"<<info.gender;
     mpUserInfo->__set_avatar(info.avatar);
     mpUserInfo->__set_gender(info.gender);
     mpUserInfo->__set_extends(info.extends);
     mpUserInfo->__set_id(info.id);
     mpUserInfo->__set_name(info.name);
     mpUserInfo->__set_thumb_avatar(info.thumb_avatar);
     mpUserInfo->__set_time_zone(info.time_zone);

     emit loginResultObserver(0,QString::number(info.id));
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
    }
    emit getLoginHistoryResult(historyList);
}

void AuthControler::_loginResult(service::ErrorInfo &info, long long userId)
{
    qDebug() << Q_FUNC_INFO << info.code() << userId;
    if(info.code() == 0)
    {
        qDebug() << Q_FUNC_INFO << "loginSucceeded";
       emit loginSucceeded();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "loginFailed = " << info.code();
        emit loginFailed(info.code());
    }
}


