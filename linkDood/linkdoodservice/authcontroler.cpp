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

void AuthControler::logout()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getAuth()->logout();
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


