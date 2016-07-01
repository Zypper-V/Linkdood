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
#include "ISearchService.h"

#include<sstream>
#include<string>

#include <QDebug>
#include <iostream>
#include <QRegExp>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QSettings>
#include <QUuid>

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

int LinkDoodService::getAppLoginStatus()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = dataPath()+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    return settings.value("Status",0).toInt();
}

void LinkDoodService::setAppLoginStatus(const int status)
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = dataPath()+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("Status",status);
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

    //如果已经是登录状态主动拉取一次联系人
    int code= getAppLoginStatus();
    if(code == 1){
        //TODO
    }
}

void LinkDoodService::login(const QString &server,
                            const QString &userId,
                            const QString &password)
{
     qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->login(server,userId,password);
    }
//    QString user("0086");

//    QByteArray ba = userId.toLatin1();
//    const char *s = ba.data();
//    while(*s && *s>='0' && *s<='9') s++;
//    bool isNum = *s ? false:true;

//    if(isNum && !userId.startsWith("0086"))
//    {
//        user = user+userId;
//    }else
//    {
//       user = userId;
//    }
//    qDebug() << Q_FUNC_INFO << server << userId << password;
//    m_pIMClient->getAuth()->login(user.toStdString(),
//                                  password.toStdString(),
//                                  server.toStdString(),
//                                  std::bind(&LinkDoodService::onLoginResult,this,std::placeholders::_1,std::placeholders::_2));
    // emit loginSucceeded();
}

void LinkDoodService::changepassword(QString oldpsw, QString newpsw)
{
    qDebug() << Q_FUNC_INFO;
   if(m_pAuth != NULL){
       m_pAuth->changepassword(oldpsw,newpsw);
   }
}

void LinkDoodService::logout()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL)
    {
        m_pAuth->logout();
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

QString LinkDoodService::createMsgId()
{
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    qDebug() << "Uuid:" << strId;
    return strId;
}

void LinkDoodService::updateContactInfo(QString userId, QString operStar, QString remark)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pContactObserver != NULL){
        m_pContactObserver->updateContactInfo(userId,operStar,remark);
    }
}

void LinkDoodService::getContactInfo(QString userId, Msg msg)
{
    qDebug() << Q_FUNC_INFO << "xxxxxxxxxxxxxxxxxxxxxxxxx";
    service::IMClient::getClient()->getContact()->getContactInfo(userId.toLongLong(),std::bind(&LinkDoodService::_getContactInfo,this,std::placeholders::_1,std::placeholders::_2,msg));
}

void LinkDoodService::getContactList()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pContactObserver != NULL){
        m_pContactObserver->getContactList();
    }
}

void LinkDoodService::onOnlineChanged(QString id, QString deviceType)
{
    qDebug() << Q_FUNC_INFO;
   emit contactOnlineChanged(id, deviceType);
}

QString LinkDoodService::UserId()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        return m_pAuth->UserId();
    }
    return "";
}

QString LinkDoodService::userName()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        return m_pAuth->userName();
    }
    return "";
}
void LinkDoodService::getChatList()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
    {
        qDebug() << Q_FUNC_INFO << "dfffffdggffffffffffffff";
        m_pChatObserver->getChatList();
    }
}

void LinkDoodService::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->getUnReadMessages();
    }
}

void LinkDoodService::entryChat(const QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->entryChat(targetId);
    }
}

void LinkDoodService::exitChat(const QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->exitChat(targetId);
    }
}

void LinkDoodService::getAccountInfo()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->getAccountInfo();
    }
}

void LinkDoodService::updateAccountInfo(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->updateAccountInfo(user);
    }
}

void LinkDoodService::removeChat(QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->removeChat(targetid);
    }
}

void LinkDoodService::setMessageRead(QString targetid, QString msgid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->setMessageRead(targetid,msgid);
    }
}

void LinkDoodService::sendMessage(Msg msg)
{

    qDebug() << Q_FUNC_INFO << "msg.msgid = " << msg.msgid;
    qDebug() << Q_FUNC_INFO << "msg.body = " << msg.body;
    qDebug() << Q_FUNC_INFO << "msg.msgtype = " << msg.msgtype;
    qDebug() << Q_FUNC_INFO << "msg.targetid = " << msg.targetid;
    qDebug() << Q_FUNC_INFO << "msg.fromid = " << msg.fromid;
    qDebug() << Q_FUNC_INFO << "msg.time = " << msg.time;
    getContactInfo(msg.targetid,msg);
//    if(m_pChatObserver != NULL){
//            m_pChatObserver->sendMessage(msg);
//    }
}

void LinkDoodService::getMessages(const QString &targetid, const QString & msgid, const int& count, const int& flag)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->getMessages(targetid,msgid,count,flag);
    }
}

void LinkDoodService::deleteMessage(QString targetid,QStringList msgs)
{
    qDebug() << Q_FUNC_INFO;
    std::vector<QString> list;
    for(auto msg:msgs){
        list.push_back(msg);
    }
    if(m_pChatObserver != NULL){
        m_pChatObserver->deleteMessage(targetid,list);
    }
}

void LinkDoodService::getSonOrgs(QString orgid)
{
    qDebug() << Q_FUNC_INFO<<orgid;
    if(m_pEnterpriseControler !=NULL){
        m_pEnterpriseControler->getSonOrgs(orgid);
    }
}
void LinkDoodService::getOnlineStates(QStringList& userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pEnterpriseControler!=NULL){
        m_pEnterpriseControler->getOnlineStates(userid);
    }
}

void LinkDoodService::getOrgUserInfo(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pEnterpriseControler!=NULL){
        m_pEnterpriseControler->getOrgUserInfo(userid);
    }
}
void LinkDoodService::getLoginHistory()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->getLoginHistory();
    }
}

void LinkDoodService::setLoginInfo(int flag, QString userid, QString username, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->setLoginInfo(flag,userid,username,avatar);
    }
}

void LinkDoodService::uploadAvatar(QString path)
{
     qDebug() << Q_FUNC_INFO;
     if(m_pChatObserver != NULL)
         m_pChatObserver->uploadAvatar(path);
}

void LinkDoodService::uploadFile(QString path, QString property)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->uploadFile(path, property);
}

void LinkDoodService::downloadFile(QString path, QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->downloadFile(path, url, property);
}

void LinkDoodService::uploadImage(QString thumbimg, QString srcimg, QString property)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->uploadImage(thumbimg, srcimg, property);
}

void LinkDoodService::downloadImage(QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->downloadImage(url, property);
}

bool LinkDoodService::decryptFile(QString encryptkey, QString srcpath, QString destpath)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->decryptFile(encryptkey, srcpath, destpath);
}

void LinkDoodService::getFileList(int64 targetid, int64 fileid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->getFileList(targetid, fileid, count, flag);
}

void LinkDoodService::onGetSonOrgsResult(int code, OrgList orglist, OrgUserList orguserlist)
{
    qDebug() << Q_FUNC_INFO << "xxxxxxxxx";
    emit getSonOrgsResult(code,orglist,orguserlist);
}

void LinkDoodService::onGetOnlineStatesResult(QOnlineStateList onlinestatelist)
{
    qDebug() << Q_FUNC_INFO;
    emit getOnlineStatesResult(onlinestatelist);
}

void LinkDoodService::onGetorgUserInfoResult(int code, OrgUser orguser)
{
    qDebug() << Q_FUNC_INFO;
    emit getOrgUserInfoResult(code,orguser);
}

void LinkDoodService::onChangePasswordResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit changePasswordResult(result);
}

void LinkDoodService::onContactInfoChanged(int oper, Contact user)
{
    qDebug() << Q_FUNC_INFO<< "333333333333333333333333333333";
    emit contactInfoChanged(oper,user);
}


void LinkDoodService::onContactListChanged(int oper,ContactList contacts)
{
    qDebug() << Q_FUNC_INFO <<"contact size111111111111111111:" << contacts.size();
    emit contactListChanged(oper,contacts);
}

void LinkDoodService::onChatListChanged(Chat_UIList chats)
{
    qDebug() << Q_FUNC_INFO << "11111111111111111111111chats size3:" << chats.size();
    emit chatListChanged(chats);
}

void LinkDoodService::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();
}

void LinkDoodService::onLoginFailed(int errCode)
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
    case 1303:
        err="首次登录，请激活帐号";
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

void LinkDoodService::onChatMessageNotice(Msg msg)
{
    qDebug() << Q_FUNC_INFO ;
    emit chatMessageNotice(msg);
}

void LinkDoodService::onChatSendMessageResult(bool code, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO ;
    emit sendMessageResult(code,QString::number(sendTime),QString::number(msgId));
}

void LinkDoodService::onChatGetMessagesResult(bool code, int64 sessionId, MsgList msgList)
{
    qDebug() << Q_FUNC_INFO << msgList.size();
    emit getMessagesResult(code,QString::number(sessionId),msgList);
}

void LinkDoodService::onChatRemoveChatResult(bool code)
{
     qDebug() << Q_FUNC_INFO ;
     emit removeChatResult(code);
}

void LinkDoodService::onChatDeleteMessagesResult(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit deleteMessagesResult(code);
}

void LinkDoodService::onGetLoginHistoryResult(LoginInfoList list)
{
    qDebug() << Q_FUNC_INFO;
    emit getLoginHistoryResult(list);
}

void LinkDoodService::onLoginResultObserver(int code, QString userID)
{
    qDebug() << Q_FUNC_INFO;
    emit loginResultObserver(code,userID);
}

void LinkDoodService::onAccountInfoChanged(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    emit accountInfoChanged(user);
}

void LinkDoodService::onChatUploadAvatar(QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadAvatarResult(orgijson, thumbjson, code);
}

void LinkDoodService::onChatUploadFile(int64 tagetid, QString jasoninfo, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadFileResult(QString::number(tagetid), jasoninfo, code);
}

void LinkDoodService::onChatFileProgress(int32 extra_req, int32 process, QString info)
{
    qDebug() << Q_FUNC_INFO;
    emit fileProgressResult(extra_req, process, info);
}

void LinkDoodService::onChatDownloadFile(service::ErrorInfo &info, QString localpath, int64 tagetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadFileResult(info.code(), localpath, QString::number(tagetid));
}

void LinkDoodService::onChatupLoadImage(int64 tagetid, QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadImageResult(QString::number(tagetid), orgijson, thumbjson, code);
}

void LinkDoodService::onChatDownloadImage(service::ErrorInfo &info, QString localpath, int64 tagetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadImageResult(info.code(), localpath, QString::number(tagetid));
}

void LinkDoodService::onChatGetFileList(service::ErrorInfo &info, std::vector<FileInfo> files)
{
    qDebug() << Q_FUNC_INFO;
    FileInfoList msgList;
    MsgFileInfo fileInfo;
    for(auto msg:files)
    {
        fileInfo.fileid = QString::number(msg.fileid);
        fileInfo.userid = QString::number(msg.userid);
        fileInfo.targetid = QString::number(msg.targetid);
        fileInfo.size = msg.size;
        fileInfo.time = msg.time;
        fileInfo.path = QString::fromStdString(msg.path);
        fileInfo.name = QString::fromStdString(msg.name);
        fileInfo.url = QString::fromStdString(msg.url);
        fileInfo.encrypt_key = QString::fromStdString(msg.encrypt_key);
        msgList.push_back(fileInfo);
    }

    emit getFileListResult(info.code(), msgList);
}

void LinkDoodService::onSessionMessageNotice(QString targetId,QString msgId,QString lastMsg,
                                             QString time ,QString name,QString avater,QString unreadmsg)
{
    qDebug() << Q_FUNC_INFO;
    emit sessionMessageNotice(targetId, msgId, lastMsg,time,name,avater,unreadmsg);
}

LinkDoodService::~LinkDoodService()
{
    qDebug() << Q_FUNC_INFO <<"sdfdsgdgdfhfghfjg";
    setAppLoginStatus(0);
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
        qDebug() << Q_FUNC_INFO <<"dggsdgsdhgdfdfhdfhgf";
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
    m_pEnterpriseControler = std::make_shared<EnterpriseControler>();
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
    QObject::connect(m_pChatObserver.get(),SIGNAL(getMessagesBack(bool,int64,MsgList)),this,
                     SLOT(onChatGetMessagesResult(bool,int64,MsgList)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(removeChatBack(bool)),this,
                     SLOT(onChatRemoveChatResult(bool)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(chatMessageNotice(Msg)),this,
                     SLOT(onChatMessageNotice(Msg)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(sessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)),this,
                     SLOT(onSessionMessageNotice(QString,QString,QString,QString, QString,QString,QString)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(deleteMessagesBack(int)),this,
                     SLOT(onChatDeleteMessagesResult(int)));

    QObject::connect(m_pChatObserver.get(), SIGNAL(uploadAvatarBack(std::string,std::string,int)), this, SLOT(onChatUploadAvatar(QString,QString,int)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(uploadFileBack(std::string,std::string,int)), this, SLOT(onChatUploadFile(QString,QString,int)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(fileProgressBack(std::string,std::string,int)), this, SLOT(onChatFileProgress(QString,QString,int)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(downloadFileBack(std::string,std::string,int)), this, SLOT(onChatDownloadFile(QString,QString,int)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(uploadImageBack(std::string,std::string,int)), this, SLOT(onChatupLoadImage(QString,QString,int)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(downloadImageBack(std::string,std::string,int)), this, SLOT(onChatDownloadImage(QString,QString,int)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(getFileListBack(std::string,std::string,int)), this, SLOT(onChatGetFileList(QString,QString,int)));





    QObject::connect(m_pEnterpriseControler.get(),SIGNAL(getSonOrgsResult(int ,OrgList ,OrgUserList )),this,
                     SLOT(onGetSonOrgsResult(int,OrgList,OrgUserList )));
    QObject::connect(m_pEnterpriseControler.get(),SIGNAL(getOnlineStatesResult(QOnlineStateList)),this,
                     SLOT(onGetOnlineStatesResult(QOnlineStateList)));
    QObject::connect(m_pEnterpriseControler.get(),SIGNAL(getOrgUserInfoResult(int,OrgUser)),this,
                     SLOT(onGetorgUserInfoResult(int,OrgUser)));


    QObject::connect(m_pAuth.get(),SIGNAL(getLoginHistoryResult(LoginInfoList)),this,
                     SLOT(onGetLoginHistoryResult(LoginInfoList)));
    QObject::connect(m_pAuth.get(),SIGNAL(loginSucceeded()),this,
                     SLOT(onLoginSucceeded()));
    QObject::connect(m_pAuth.get(),SIGNAL(loginFailed(int)),this,
                     SLOT(onLoginFailed(int)));
    QObject::connect(m_pAuth.get(),SIGNAL(changePasswordResult(QString)),this,
                     SLOT(onChangePasswordResult(QString)));

    QObject::connect(m_pAuth.get(),SIGNAL(loginoutRelust(bool)),this,
                     SLOT(onLoginoutRelust(bool)));
    QObject::connect(m_pAuth.get(),SIGNAL(loginResultObserver(int,QString)),this,
                     SLOT(onLoginResultObserver(int,QString)));
    QObject::connect(m_pAuth.get(),SIGNAL(accountInfoChanged(Contact)),this,
                     SLOT(onAccountInfoChanged(Contact)));

    QObject::connect(m_pChatObserver.get(),SIGNAL(chatListChanged(Chat_UIList)),this,
                     SLOT(onChatListChanged(Chat_UIList)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactListChanged(int,ContactList)),this,
                     SLOT(onContactListChanged(int,ContactList)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactInfoChanged(int,Contact)),this,
                     SLOT(onContactInfoChanged(int,Contact)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactOnlineChanged(QString,QString)),this,SLOT(onOnlineChanged(QString,QString)));
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

void LinkDoodService::onSrvGetContactInfoResult(service::ErrorInfo &info, service::User &user)
{
     qDebug() << Q_FUNC_INFO << info.code() << user.name.c_str();
     emit srvGetContactInfo(user);
}

void LinkDoodService::_getContactInfo(service::ErrorInfo &info, service::User &user, Msg msg)
{

    msg.name = QString::fromStdString(user.name);
    msg.thumb_avatar = QString::fromStdString(user.thumb_avatar);
    qDebug() << Q_FUNC_INFO << "sfdsffffffffffffffffffffffffffffffff" <<  msg.name;
    if(m_pChatObserver != NULL){
        m_pChatObserver->sendMessage(msg);
    }
    //emit sessionMessageNotice(msg.targetid,msg.msgid,msg.body,msg.time,msg.name,msg.thumb_avatar);
}




