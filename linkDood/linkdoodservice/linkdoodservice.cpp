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
#include "linkdoodtypes.h"

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
        qDebug() << " create LinkDoodService parent !!!  ";
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

    registerDoodDataTypes();

    initSdk();

    initDBusConnection();
}

void LinkDoodService::login(const QString &server,
                            const QString &userId,
                            const QString &password)
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
    m_pIMClient->getAuth()->login(user.toStdString(),
                                  password.toStdString(),
                                  server.toStdString(),
                                  std::bind(&LinkDoodService::onLoginResult,this,std::placeholders::_1,std::placeholders::_2));
    // emit loginSucceeded();
}

void LinkDoodService::logout()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pIMClient != NULL)
    {
        m_pIMClient->getAuth()->logout();
    }
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

void LinkDoodService::onContactListChanged(int oper,ContactList contacts)
{
    qDebug() << Q_FUNC_INFO <<"contact size:" << contacts.size();
    emit contactListChanged(oper,contacts);
}

void LinkDoodService::onChatListChanged(const Chat_UIList &chats)
{
    qDebug() << Q_FUNC_INFO << "chats size3:" << chats.size();
    emit chatListChanged(chats);
    emit testSignal("test zhangp!!!");
}

void LinkDoodService::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();

//     const Chat_UIList chats;
//     emit chatListChanged(chats);
}

void LinkDoodService::onLoginOnFailed(int errCode)
{
    qDebug() << Q_FUNC_INFO;
    QString err;
    switch(errCode)
    {
     case -1:
        err = "网络连接超时";
        break;
    case -11:
       err = "have Login";
       break;
    case 101:
       err = "yonghubucunzai";
       break;
    case 112:
       err = "zhanghaomimabupipei";
       break;
    case 113:
       err = "zhanghaoyijingdenglu";
       break;
    default:
       err = "weizhicuowu";
       break;
    }

    emit loginFailed(err);
}

void LinkDoodService::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << loginout;
    emit loginoutRelust(loginout);
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
    initConnects();
}

void LinkDoodService::initConnects()
{
    qDebug() << Q_FUNC_INFO ;
    QObject::connect(this,SIGNAL(loginOnSucceeded()),this,SLOT(onLoginSucceeded()));
    QObject::connect(this,SIGNAL(loginOnFailed(int)),this,SLOT(onLoginOnFailed(int)));

    QObject::connect(m_pAuth.get(),SIGNAL(loginoutRelust(bool)),this,SLOT(onLoginoutRelust(bool)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(chatListChanged(const Chat_UIList&)),this,SLOT(onChatListChanged(const Chat_UIList&)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactListChanged(int,ContactList)),this,SLOT(onContactListChanged(int,ContactList)));
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
    qDebug() << Q_FUNC_INFO << info.code() << userId;
    if(info.code() == 0)
    {
        qDebug() << Q_FUNC_INFO << "loginSucceeded";
       emit loginOnSucceeded();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "loginFailed = " << info.code();
        emit loginOnFailed(info.code());
    }
}
