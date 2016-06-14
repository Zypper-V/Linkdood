#include "authcontroler.h"
#include<QCoreApplication>
#include<iostream>
#include<QDebug>

#include "IMClient.h"
#include "IAuthService.h"
#include "INotifyService.h"
#include "LoginInfo.hpp"
#include "Account.h"
#include "linkdoodservice.h"

AuthControler::AuthControler()
{

}
void AuthControler::init(void)
{
   m_client =  service::IMClient::getClient();
   QString appPath = QCoreApplication::applicationDirPath();
   std::string cerPath(appPath.toStdString());
   cerPath +="linkdood.crt";

   m_client->init(appPath.toStdString(),cerPath);
   m_client->getNotify()->setAuthObserver(this);
   //logining
   m_client->getAuth()->login("008615829282366","chengcy2015","vrv"
         ,std::bind(&AuthControler::onSerLogin,this,std::placeholders::_1, std::placeholders::_2));
}
void AuthControler::onSerLogin(service::ErrorInfo& err, int64 userid)
{
    if(err.code()==0)
    {
        qDebug()<<"linkdood login success.";
        m_client->getAuth()->getAccountInfo();
    }
}
void AuthControler::onConnectChanged(int flag)
{
        qDebug()<<"AuthControler::onConnectChanged";
}

void AuthControler::onLoginResultObserver(service::ErrorInfo& info, int64 userid)
{
     //qDebug()<<"AuthControler::onLoginResultObserver";
     qDebug() << Q_FUNC_INFO;
}

void AuthControler::onDBUpdateFinished(int val)
{
    qDebug()<<"AuthControler::onDBUpdateFinished";
}

void AuthControler::onLogoutChanged(service::ErrorInfo& info)
{
    qDebug()<<"AuthControler::onLogoutChanged";
}

void AuthControler::onAccountInfoChanged(service::User& info)
{
     qDebug()<<"name:"<<info.name.c_str()<<"sex:"<<info.gender;
}

void AuthControler::onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey)
{
    qDebug()<<"AuthControler::onClientKeyChanged";
}

void AuthControler::onPasswordRuleChanged(service::ErrorInfo& info, int16 rule)
{

}

void AuthControler::onAvatarChanged(std::string avatar)
{

}
