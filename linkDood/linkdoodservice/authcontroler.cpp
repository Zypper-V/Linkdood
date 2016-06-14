#include "authcontroler.h"
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
void AuthControler::init(std::string  dataPath,std::string certPath)
{
    qDebug() << Q_FUNC_INFO;

   m_client =  service::IMClient::getClient();
   m_client->init(dataPath,certPath);
   m_client->getNotify()->setAuthObserver(this);

    qDebug() << Q_FUNC_INFO << "cerPath = " << certPath.c_str() << "dataPAth" << dataPath.c_str();

   m_client->getAuth()->login("008615829282366","chengcy2015","vrv"
         ,std::bind(&AuthControler::onSerLogin,this,std::placeholders::_1, std::placeholders::_2));
}

void AuthControler::onSerLogin(service::ErrorInfo& err, int64 userid)
{
    qDebug() << Q_FUNC_INFO;
    if(err.code()==0)
    {
        qDebug()<<"linkdood login success.";
        m_client->getAuth()->getAccountInfo();
    }
}
void AuthControler::onConnectChanged(int flag)
{
        qDebug() << Q_FUNC_INFO;
}

void AuthControler::onLoginResultObserver(service::ErrorInfo& info, int64 userid)
{
     qDebug() << Q_FUNC_INFO;
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
