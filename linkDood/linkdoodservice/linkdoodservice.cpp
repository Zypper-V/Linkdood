#include "linkdoodservice.h"
#include "linkdoodconst.h"
#include "csystempackagemanager.h"
#include "IMClient.h"
#include "IAuthService.h"
#include "INotifyService.h"
#include "IChatService.h"
#include "LoginInfo.hpp"
#include "Account.h"
#include "chatcontroler.h"
#include "contactcontroler.h"

#include <QDebug>
#include <iostream>
#include <QRegExp>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>

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

    initDBusConnection();
}

void LinkDoodService::login(const QString &server,
                            const QString &userId,
                            const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    m_pIMClient->getAuth()->login(userId.toStdString(),
                                  password.toStdString(),
                                  server.toStdString(),
                                  std::bind(&LinkDoodService::onLoginResult,this,std::placeholders::_1,std::placeholders::_2));
}

void LinkDoodService::getChatList()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pIMClient != NULL)
    {
        m_pIMClient->getChat()->getChatList();
    }
}

void LinkDoodService::getUnReadMessages()
{

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
    qDebug() << Q_FUNC_INFO << "m_client->initret:" << ret;
    if(ret)
    {
       initObserver();
    }

//    login("vrv","008615829282366","chengcy2015");
}

void LinkDoodService::initObserver()
{
    qDebug() << Q_FUNC_INFO;

    m_pAuth            = std::make_shared<AuthControler>();
    m_pContactObserver = std::make_shared<ContactControler>();
    m_pChatObserver    = std::make_shared<ChatControler>();
    m_pAuth->init();
    m_pChatObserver->init();
    m_pContactObserver->init();
}

void LinkDoodService::initDBusConnection()
{
    qDebug() << Q_FUNC_INFO;
    QDBusConnection bus = QDBusConnection::sessionBus();
    bool bSuccess = false;
    bSuccess = QDBusConnection::sessionBus().registerService(DBUS_DOOD_SERVICE);
    qDebug() << "--- registerService = " << bSuccess;

    bSuccess = bus.registerObject(DBUS_DOOD_PATH, this,
                                  QDBusConnection::ExportAllContents);
    qDebug() << "--- registerObject = " << bSuccess;
}

void LinkDoodService::onLoginResult(service::ErrorInfo &info, int64 userId)
{
    qDebug() << Q_FUNC_INFO;

    qDebug() << Q_FUNC_INFO << "loginResultCode:" << info.code();
    if(info.code() == 0)
    {
        emit signalLoginSucceeded();
       // getChatList();
    }
    else
    {
        emit signalLoginFailed(info.code());
    }
}
