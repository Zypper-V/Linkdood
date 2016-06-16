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
//                                  std::bind(&AuthControler::onLoginResult,this,std::placeholders::_1,std::placeholders::_2));
//}

void AuthControler::onConnectChanged(int flag)
{
        qDebug() << Q_FUNC_INFO;
}

void AuthControler::onLoginResultObserver(service::ErrorInfo& info, int64 userid)
{
     qDebug() << Q_FUNC_INFO << info << userid;
}

void AuthControler::onDBUpdateFinished(int val)
{
    qDebug() << Q_FUNC_INFO;
}

void AuthControler::onLogoutChanged(service::ErrorInfo& info)
{
    qDebug() << Q_FUNC_INFO;
}

void AuthControler::onAccountInfoChanged(service::User& info)
{
    qDebug() << Q_FUNC_INFO;
     qDebug()<<"name:"<<info.name.c_str()<<"sex:"<<info.gender;
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

void AuthControler::onLoginResult(service::ErrorInfo &info, int64 userId)
{
    qDebug() << Q_FUNC_INFO << "code:" << info.code() << userId;
    if(info.code() == 0)
    {
      //emit this->loginSucceeded();
    }else{
        //emit loginFailed(info.code());
    }
}
