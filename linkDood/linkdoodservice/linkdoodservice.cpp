#include "linkdoodservice.h"
#include "csystempackagemanager.h"
#include "IMClient.h"
#include "IAuthService.h"
#include "INotifyService.h"
#include "LoginInfo.hpp"
#include "Account.h"

#include <QDebug>
#include <iostream>
#define LINKDOOD_SOPID "com.vrv.linkDood"

LinkDoodService* LinkDoodService::m_pInstance = 0;

void LinkDoodService::createService()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_pInstance) {
        qDebug() << " create LinkDoodService !!!";
        m_pInstance = new LinkDoodService();
    } else {
        qDebug() << "alreadly create LinkDoodService !!!";
    }
}

LinkDoodService *LinkDoodService::instance()
{
    qDebug() << Q_FUNC_INFO;
    return m_pInstance;
}

QString LinkDoodService::installPath()
{
    qDebug() << Q_FUNC_INFO << " = " << m_sInstallPath;
    return m_sInstallPath;
}

QString LinkDoodService::dataPath()
{
    qDebug() << Q_FUNC_INFO;
    return "/data/data/com.vrv.linkDood/";
}

LinkDoodService::LinkDoodService(QObject *parent) :
    QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    initSdk();
}

void LinkDoodService::login(const QString& server,const QString& user,const QString& userPwd)
{
    qDebug() << Q_FUNC_INFO;
    m_pIMClient->getAuth()->login(user.toStdString(),userPwd.toStdString(),
                 server.toStdString(),std::bind(&LinkDoodService::onLoginResult,this,std::placeholders::_1,std::placeholders::_2));
}

LinkDoodService::~LinkDoodService()
{

}

void LinkDoodService::initSdk()
{
    qDebug() << Q_FUNC_INFO;
    m_pPackageManager = new CSystemPackageManager();
    m_sInstallPath = m_pPackageManager->packageInfo(LINKDOOD_SOPID)->installPath();
    qDebug() << Q_FUNC_INFO << "installPath = " << m_sInstallPath;

    QString crtPath = installPath();
    crtPath += "/crt/linkdood.crt";
    m_pIMClient =  service::IMClient::getClient();
    bool ret = m_pIMClient->init(dataPath().toStdString(),crtPath.toStdString());
    qDebug() << Q_FUNC_INFO << "m_client->init ret:" << ret;
    if(ret)
    {
        m_pAuth = std::make_shared<AuthControler>();
        m_pAuth->init();
    }

    login("vrv","008615829282366","chengcy2015");
}

void LinkDoodService::onLoginResult(service::ErrorInfo &info, int64 userId)
{
    qDebug() << Q_FUNC_INFO;
    if(info.code() == 0)
    {
        qDebug() << Q_FUNC_INFO << "login ok";
    }
    else
    {

    }
}
