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
#include "IContactService.h"
#include "IEnterpriseService.h"

#include<sstream>
#include<string>

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

void LinkDoodService::getContactInfo(int64 userId)
{
    qDebug() << Q_FUNC_INFO;
    long long id = userId;
    if(m_pIMClient != NULL){
       m_pIMClient->getContact()->getContactInfo(id,
                            std::bind(&LinkDoodService::onSrvGetContactInfoResult,this,std::placeholders::_1,std::placeholders::_2));
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
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->getUnReadMessages();
    }
}

void LinkDoodService::removeChat(int64 targetid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->removeChat(targetid);
    }
}

void LinkDoodService::setMessageRead(int64 targetid, int64 msgid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->setMessageRead(targetid,msgid);
    }
}

void LinkDoodService::sendMessage(Msg& msg)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->sendMessage(msg);
    }
}

void LinkDoodService::getMessages(int64 targetid, int64 msgid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->getMessages(targetid,msgid,count,flag);
    }
}

void LinkDoodService::getEnterpriseSonOrgs(int64 orgid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pIMClient != NULL){
        m_pIMClient->getEnterprise()->getSonOrgs(orgid,
                    std::bind(&LinkDoodService::onGetEnterpriseSonOrgsResult,this,
                              std::placeholders::_1,
                              std::placeholders::_2,
                              std::placeholders::_3));
    }
}

void LinkDoodService::onGetEnterpriseSonOrgs(service::ErrorInfo &info, std::vector<service::Org> orgs, std::vector<service::OrgUser> orgusers)
{
    qDebug() << Q_FUNC_INFO;

    OrgList orgList;
    OrgUserList orgUserList;
    for(auto org:orgs){
        orgList.insert(orgList.size(),orgToQorg(org));
    }

    for(auto orgUser:orgusers){
        orgUserList.insert(orgUserList.size(),orguserToQorguser(orgUser));
    }

    emit getEnterpriseSonOrgsResult(info.code(),orgList,orgUserList);

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
}

void LinkDoodService::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();
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
        err = "帐号已经登录，不能重复登录";
        break;
    case 101:
        err = "用户不存在";
        break;
    case 112:
        err = "帐号密码不匹配";
        break;
    case 113:
        err = "帐号已经登录";
        break;
    default:
        err = "登录失败";
        break;
    }

    emit loginFailed(err);
}

void LinkDoodService::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << loginout;
    emit loginoutRelust(loginout);
}

void LinkDoodService::onGetContactInfoResult(service::User &user)
{
    qDebug() << Q_FUNC_INFO ;
}

void LinkDoodService::onChatAvatarChanged(int64 id, QString avatar)
{
    qDebug() << Q_FUNC_INFO ;
    emit chatAvatarChanged(id,avatar);
}

void LinkDoodService::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO ;
    emit offlineMsgNotice(msgList);
}

void LinkDoodService::onChatMessageNotice(Msg &msg)
{
    qDebug() << Q_FUNC_INFO ;
    emit newMessageNotice(msg);
}

void LinkDoodService::onChatSendMessageResult(bool code, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO ;
    emit sendMessageResult(code,sendTime,msgId);
}

void LinkDoodService::onChatGetMessagesResult(bool code, int64 sessionId, MsgList &msgList)
{
    qDebug() << Q_FUNC_INFO ;
    emit getMessagesResult(code,sessionId,msgList);
}

void LinkDoodService::onChatRemoveChatResult(bool code)
{
     qDebug() << Q_FUNC_INFO ;
     emit removeChatResult(code);
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

    QObject::connect(m_pChatObserver.get(),SIGNAL(avatarChangedBack(int64,QString)),this,
                     SLOT(onChatAvatarChanged(int64,QString)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(offlineMsgNoticeBack(IMOfflineMsgList)),this,
                     SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(sendMessageBack(bool,int64,int64)),this,
                     SLOT(onChatSendMessageResult(bool,int64,int64)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(getMessagesBack(bool,int64,MsgList&)),this,
                     SLOT(onChatGetMessagesResult(bool,int64,MsgList&)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(removeChatBack(bool)),this,
                     SLOT(onChatRemoveChatResult(bool)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(messageNoticeBack(Msg&)),this,
                     SLOT(onChatMessageNotice(Msg&)));

    QObject::connect(this,SIGNAL(getEnterpriseSonOrgsCallBack(service::ErrorInfo&,std::vector<service::Org>,std::vector<service::OrgUser>)),this,
                     SLOT(onGetEnterpriseSonOrgs(service::ErrorInfo&,std::vector<service::Org>,std::vector<service::OrgUser>)));


    QObject::connect(this,SIGNAL(loginOnSucceeded()),this,
                     SLOT(onLoginSucceeded()));
    QObject::connect(this,SIGNAL(loginOnFailed(int)),this,
                     SLOT(onLoginOnFailed(int)));

    QObject::connect(m_pAuth.get(),SIGNAL(loginoutRelust(bool)),this,
                     SLOT(onLoginoutRelust(bool)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(chatListChanged(const Chat_UIList&)),this,
                     SLOT(onChatListChanged(const Chat_UIList&)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactListChanged(int,ContactList)),this,
                     SLOT(onContactListChanged(int,ContactList)));
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

void LinkDoodService::onGetEnterpriseSonOrgsResult(service::ErrorInfo &info, std::vector<service::Org> orgs, std::vector<service::OrgUser> orgusers)
{
    qDebug() << Q_FUNC_INFO;
    emit getEnterpriseSonOrgsCallBack(info,orgs,orgusers);
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

void LinkDoodService::onSrvGetContactInfoResult(service::ErrorInfo &info, service::User &user)
{
     qDebug() << Q_FUNC_INFO << info.code() << user.name.c_str();
     emit srvGetContactInfo(user);
}

Org LinkDoodService::orgToQorg(service::Org org)
{
    Org Qorg;
    Qorg.avatar       =QString::fromStdString(org.avatar);
    Qorg.thumbAvatar  =QString::fromStdString(org.thumb_avatar);
    Qorg.extends      =QString::fromStdString(org.extends);
    Qorg.org_code     =QString::fromStdString(org.org_code);
    Qorg.name         =QString::fromStdString(org.name);
    Qorg.branch_id    =QString::number(org.id);
    Qorg.ent_id       =QString::number(org.ent_id);
    Qorg.ishidden     =QString::number(org.ishidden);
    Qorg.leaf         =QString::number(org.leaf);
    Qorg.level        =QString::number(org.level);
    Qorg.order_num    =QString::number(org.order_num);
    Qorg.id           =QString::number(org.id);
    Qorg.parent_id    =QString::number(org.parent_id);
    Qorg.sonorg_count =QString::number(org.sonorg_count);
    Qorg.sonuser_count=QString::number(org.sonuser_count);
    return Qorg;
}

OrgUser LinkDoodService::orguserToQorguser(service::OrgUser orguser)
{
    OrgUser Qorguser;
    Qorguser.ent_id       =QString::number(orguser.ent_id);
    Qorguser.order_num    =QString::number(orguser.order_num);
    Qorguser.org_id       =QString::number(orguser.org_id);
    Qorguser.role_id      =QString::number(orguser.role_id);
    Qorguser.neworg_id    =QString::number(orguser.org_id);
    Qorguser.id           =QString::number(orguser.id);
    Qorguser.gender       =QString::number(orguser.gender);
    Qorguser.timeZone     =QString::number(orguser.time_zone);
    Qorguser.avatar       =QString::fromStdString(orguser.avatar);
    Qorguser.thumbAvatar  =QString::fromStdString(orguser.thumb_avatar);
    Qorguser.name         =QString::fromStdString(orguser.name);
    Qorguser.extends      =QString::fromStdString(orguser.extends);
    Qorguser.duty         =QString::fromStdString(orguser.duty);
    Qorguser.email        =QString::fromStdString(orguser.email);
    Qorguser.phone        =QString::fromStdString(orguser.phone);
    Qorguser.orgname      =QString::fromStdString(orguser.orgname);
    Qorguser.pinyin       =QString::fromStdString(orguser.pinyin);
    return Qorguser;
}
