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
#include "sysmsgcontroler.h"
#include "IDRangeJuge.hpp"
#include "FileUtils.h"

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

QString LinkDoodService::userType(QString userId)
{
    int64 id = userId.toLongLong();
    if(IS_MSG_USER(id)){
        return "1";
    }else if(IS_MSG_GROUP(id)){
        return "2";
    }else if(IS_MSG_APP(id)){
        return "3";
    }
    return "1";
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
    m_pPackageManager = NULL;
    registerDoodDataTypes();

    initSdk();

    initDBusConnection();

    //如果已经是登录状态主动拉取一次联系人
    //    int code= getAppLoginStatus();
    //    if(code == 1){
    //非正常启动，跳转到登录界面
    setAppLoginStatus(2);
    emit serviceRestart();
    //    }
    QDir path(APP_SAVE_DATA_PATH);
    if(!path.exists()){
        path.mkdir(APP_SAVE_DATA_PATH);
    }
}

void LinkDoodService::login(const QString &server,
                            const QString &userId,
                            const QString &password)
{
    qDebug() << Q_FUNC_INFO;
    //initControl();
    if(m_pAuth != NULL){
        m_pAuth->login(server,userId,password);
    }
}

void LinkDoodService::autoLogin(QString id, QString service)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->autoLogin(id,service);
    }
}

void LinkDoodService::getVerifyImg(QString userid, QString code)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_pAuth->getVerifyImg(userid,code);
    }
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

void LinkDoodService::getContactInfo(QString userId)
{
    if(m_pContactObserver != NULL){
        m_pContactObserver->getContactInfo(userId);
    }
}

//void LinkDoodService::getContactInfo(int64 userId)
//{
//    qDebug() << Q_FUNC_INFO;
//    long long id = userId;
//    if(m_pIMClient != NULL){
//        m_pIMClient->getContact()->getContactInfo(id,
//                                                  std::bind(&LinkDoodService::onSrvGetContactInfoResult,this,std::placeholders::_1,std::placeholders::_2));
//    }
//}

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

void LinkDoodService::onUpdateContactInfo(int code)
{
    emit updateContactInfoResult(code);
}

void LinkDoodService::onOnlineChanged(QString id, QString deviceType,int flag)
{
    qDebug() << Q_FUNC_INFO;
    if(id==m_userid&&flag==(-1)){
        setAppLoginStatus(0);
        emit elsewhereLogin("您的帐号已在别处登录");
    }
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
    //getContactInfo(msg.targetid,msg);
    if(m_pChatObserver != NULL){
        m_pChatObserver->sendMessage(msg);
    }
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

void LinkDoodService::uploadAndSendFileMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->uploadAndSendFileMsg(msg);
}

void LinkDoodService::downloadFile(QString path, QString url, QString json,QString localId,QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->downloadFile(path, url, json,localId,targetId);
}

void LinkDoodService::cancelDonwloadFile(QString id)
{
    if(m_pChatObserver != NULL){
        m_pChatObserver->cancelDonwloadFile(id);
    }
}

void LinkDoodService::uploadAndSendImageMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->uploadAndSendImageMsg(msg);
}

void LinkDoodService::downloadImage(QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    //if(m_pChatObserver != NULL)
    //  m_pChatObserver->downloadImage(url, property);
}

void LinkDoodService::downloadMainImage(QString main_url, QString encryptkey, QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL){
        m_pChatObserver->downloadMainImage(main_url,encryptkey,targetId);
    }
}

void LinkDoodService::downloadHistoryImage(QString url, QString property, QString targetid, QString localid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->downloadHistoryImage(url, property, targetid, localid);
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

void LinkDoodService::getUserInfo(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pChatObserver != NULL)
        m_pChatObserver->getUserInfo(userid);
}

void LinkDoodService::searchFromNet(QString key)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pContactObserver != NULL)
        m_pContactObserver->searchFromNet(key);
}

void LinkDoodService::searchFromLocal(QString key)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pContactObserver != NULL)
        m_pContactObserver->searchFromLocal(key);
}

void LinkDoodService::addContact(QString userid, QString remark, QString info)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pContactObserver != NULL)
        m_pContactObserver->addContact(userid, remark, info);
}

void LinkDoodService::removeContact(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pContactObserver != NULL)
        m_pContactObserver->removeContact(userid);
}

void LinkDoodService::getVerifyType(QString userid)
{
    qDebug() << Q_FUNC_INFO << "userid:" << userid;
    if(m_pContactObserver != NULL)
        m_pContactObserver->getVerifyType(userid);
}

void LinkDoodService::createGroup(QString level, QString name, MemberList memberList)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->createGroup(level,name,memberList);
}

void LinkDoodService::addGroup(QString groupid, QString verify_info)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->addGroup(groupid,verify_info);
}

void LinkDoodService::removeGroup(QString type, QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->removeGroup(type,groupid);
}

void LinkDoodService::transferGroup(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->transferGroup(groupid,userid);
}

void LinkDoodService::setGroupSet(QString groupid, QString verify_type, QString is_allow)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->setGroupSet(groupid,verify_type,is_allow);
}

void LinkDoodService::setGroupInfo(Group group)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->setGroupInfo(group);
}

void LinkDoodService::getGroupSet(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->getGroupSet(groupid);
}

void LinkDoodService::getGroupInfo(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->getGroupInfo(groupid);
}

void LinkDoodService::inviteMember(QString groupid, MemberList memberList)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->inviteMember(groupid,memberList);
}

void LinkDoodService::removeMember(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->removeMember(groupid,userid);
}

void LinkDoodService::setMemberInfo(Member member)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->setMemberInfo(member);
}

void LinkDoodService::getMemberInfo(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->getMemberInfo(groupid,userid);
}

void LinkDoodService::getMemberList(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->getMemberList(groupid);
}

void LinkDoodService::getGroupList()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->getGroupList();
}

void LinkDoodService::getGroupFileList(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->getGroupFileList(groupid);
}

void LinkDoodService::deleteGroupFile(QStringList fileIdList)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->deleteGroupFile(fileIdList);

}

void LinkDoodService::uploadGroupAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pGroupControler!=NULL)
        m_pGroupControler->uploadGroupAvatar(path);
}

void LinkDoodService::getSysMessages(int type, int count, QString msgid, int flag)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pSysMsg != NULL)
        m_pSysMsg->getSysMessages(type, count, msgid, flag);
}

void LinkDoodService::setSysMessagRead(int type, QString msg)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pSysMsg != NULL)
        m_pSysMsg->setSysMessagRead(type, msg);
}

void LinkDoodService::response(IMSysMsgRespInfo info)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pSysMsg != NULL)
        m_pSysMsg->response(info);
}

void LinkDoodService::removeSysMessage(QString type,QString msgid)
{
    qDebug()<<Q_FUNC_INFO<<msgid;
    if(m_pSysMsg!=NULL){
        m_pSysMsg->removeSysMessage(type,msgid);
    }
}

void LinkDoodService::setPrivateSetting(IMPrivateSetting ps)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL)
        m_pAuth->setPrivateSetting(ps);
}

void LinkDoodService::getPrivateSetting()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL)
        m_pAuth->getPrivateSetting();
}

void LinkDoodService::onSysMessageNotice(IMSysMsg sysMsg)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << Q_FUNC_INFO << "  msgid:" << sysMsg.msgid << "   targetid:" << sysMsg.targetid << "  time:" << sysMsg.time << "   msgtypeText:" << sysMsg.msgtypeText << "   respons:" << sysMsg.respons << "   name:" << sysMsg.name << "   avatar:" << sysMsg.avatar << "   info:" << sysMsg.info << "   operUser:" << sysMsg.operUser << "   isRead:" << sysMsg.isread;

    emit sysMessageNotice(sysMsg);
}

void LinkDoodService::onGetSysMessages(int code, IMSysMsgList sysMsgList)
{
    qDebug() << Q_FUNC_INFO;
    emit getSysMessageResult(code, sysMsgList);
}

void LinkDoodService::onRemoveSysMessageResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit removeSysMessageResult(result);
}

void LinkDoodService::onGetContactInfoResult(Contact contact)
{
    qDebug()<<Q_FUNC_INFO<<"user:"<<contact.remark;
    emit getContactInfoResult(contact);
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

void LinkDoodService::onAnthAvatarChanged(QString avatar)
{
    emit anthAvatarChanged(avatar);
}

void LinkDoodService::onChangePasswordResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit changePasswordResult(result);
}

void LinkDoodService::onGetVerifyImgResult(QString code, QString img)
{
    qDebug()<<Q_FUNC_INFO;
    emit getVerifyImgResult(code,img);
}

void LinkDoodService::onConnectChanged(QString flag)
{
    qDebug() << Q_FUNC_INFO;
    emit connectChanged(flag);
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

void LinkDoodService::onLoginSucceeded(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth != NULL){
        m_userid=m_pAuth->UserId();
    }
    emit loginSucceeded();
}

void LinkDoodService::onLoginFailed(int errCode)
{
    qDebug() << Q_FUNC_INFO<<errCode<<"cuowucuowucuowucuowucuowu";
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
    case 117:
        err="输入错误次数过多,请输入验证码";
        break;
    case 1102:
        err="输入错误次数过多,请输入验证码";
        break;
    case 1303:
        err="首次登录，请激活帐号";
        break;
    case 1308:
        err="账号已锁定";
        break;
    default:
        err = "登录失败(code: "+QString::number(errCode)+")";
        break;
    }

    emit loginFailed(err);
}

void LinkDoodService::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << loginout;
    unInitSdk();
    emit loginoutRelust(loginout);
}

void LinkDoodService::onUploadImageProgess(QString targetId, QString localId, int progress)
{
    emit uploadImageProgess(targetId,localId,progress);
}

void LinkDoodService::onChatAvatarChanged(QString id, QString avatar)
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

void LinkDoodService::onChatSendMessageResult(bool code, int64 sendTime, QString msgId)
{
    qDebug() << Q_FUNC_INFO ;
    emit sendMessageResult(code,QString::number(sendTime),msgId);
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
    qDebug() << Q_FUNC_INFO<<code<<"wwwwwwwwwwwwwwwwwww";
    emit loginResultObserver(code,userID);
}

void LinkDoodService::onAccountInfoChanged(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    if(m_pAuth!= NULL){
        m_pAuth->setLoginInfo(6,user.id,user.name,user.avatar);
    }
    emit accountInfoChanged(user);
}

void LinkDoodService::onChatUploadAvatar(QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
    if(code == 0)
    {
        Contact contact;
        std::string src = "";
        contact.thumbAvatar = QString::fromStdString(utils::FileUtils::getImgUrl(thumbjson.toStdString(), src));
        contact.avatar = QString::fromStdString(src);
        updateAccountInfo(contact);
    }

    emit uploadAvatarResult(orgijson, thumbjson, code);
}

void LinkDoodService::onChatUploadFile(int64 tagetid, QString jasoninfo, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadFileResult(QString::number(tagetid), jasoninfo, code);
}

void LinkDoodService::onChatFileProgress(int extra_req, int process, QString info,QString localId,QString targetId)

{
    qDebug() << Q_FUNC_INFO;
    emit fileProgressResult(extra_req, process, info,localId,targetId);
}

void LinkDoodService::onDownloadFileCancelId(QString id, QString cancelId)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadFileCancelId(id,cancelId);
}

void LinkDoodService::onChatDownloadFile(int code , QString localpath, QString tagetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadFileResult(code, localpath, tagetid);
}

void LinkDoodService::onChatupLoadImage(int64 tagetid, QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadImageResult(QString::number(tagetid), orgijson, thumbjson, code);
}

void LinkDoodService::onDownloadMainImageResult(QString main_url, QString localpath)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadMainImageResult(main_url,localpath);
}

void LinkDoodService::onChatDownloadImage(service::ErrorInfo &info, QString localpath, int64 tagetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadImageResult(info.code(), localpath, QString::number(tagetid));
}

void LinkDoodService::onDownloadHistoryImage(int code, QString localpath, QString targetid, QString localid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadHistoryImageResult(code, localpath, targetid, localid);
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

void LinkDoodService::onGetUserInfoResult(int code, Contact contact)
{
    emit getUserInfoResult(code, contact);
}
void LinkDoodService::onSearchFromNet(int code, ContactList user, ContactList group)
{
    qDebug() << Q_FUNC_INFO;
    emit searchFromNetResult(code, user, group);

}

void LinkDoodService::onSearchFromLocal(int code, ContactList user, ContactList group)
{
    qDebug() << Q_FUNC_INFO;
    emit searchFromLocalResult(code, user, group);
}

void LinkDoodService::onAddContact(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit addContactResult(code);
}

void LinkDoodService::onRemoveContact(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeContactResult(code);
}

void LinkDoodService::onGetVerifyType(int code, QString userid, int type)
{
    qDebug() << Q_FUNC_INFO;
    emit getVerifyTypeResult(code, userid, type);
}

void LinkDoodService::onUploadFileBackUrl(QString targetId, QString localId, QString fileUrl, QString enkey)
{
    emit uploadFileBackUrl(targetId,localId,fileUrl,enkey);
}

void LinkDoodService::onUploadImgeBackUrl(QString targetId, QString localId, QString mainUrl, QString thumbUrl, QString enkey)
{
    emit uploadImgeBackUrl(targetId,localId,mainUrl,thumbUrl,enkey);
}

void LinkDoodService::onTransMessageFinishBack(int code, QString targetId)
{
    emit transMessageFinishBack(code,targetId);
}

void LinkDoodService::onSessionMessageNotice(QString targetId,QString msgId,QString lastMsg,
                                             QString time ,QString name,QString avater,QString unreadmsg)
{
    qDebug() << Q_FUNC_INFO;
    emit sessionMessageNotice(targetId, msgId, lastMsg,time,name,avater,unreadmsg);
}

void LinkDoodService::onGroupListChanged(GroupList groupList)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupListChanged(groupList);
}

void LinkDoodService::onGroupAvatarChanged(QString groupid, QString avatar)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupAvatarChanged(groupid,avatar);
}

void LinkDoodService::onMemberAvatarChanged(QString userid, QString avatar)
{
    emit memberAvatarChanged(userid,avatar);
}

void LinkDoodService::onGroupInfoChanged(QString operType, Group group)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupInfoChanged(operType,group);
}

void LinkDoodService::onGroupLeaderChanged(QString userid, QString user_name, QString groupid, QString group_name)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupLeaderChanged(userid,user_name,groupid,group_name);
}

void LinkDoodService::onMemberInfoChanged(QString groupid, Member member)
{
    qDebug()<<Q_FUNC_INFO;
    emit memberInfoChanged(groupid,member);
}

void LinkDoodService::onMemberListChanged(QString operType, QString groupid, MemberList memberList)
{
    qDebug()<<Q_FUNC_INFO;
    emit memberListChanged(operType,groupid,memberList);
}

void LinkDoodService::onCreateGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit createGroupResult(result);
}

void LinkDoodService::onAddGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit addGroupResult(result);
}

void LinkDoodService::onRemoveGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit removeGroupResult(result);
}

void LinkDoodService::onTransferGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit transferGroupResult(result);
}

void LinkDoodService::onSetGroupSetResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit setGroupSetResult(result);
}

void LinkDoodService::onSetGroupInfoResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit setGroupInfoResult(result);
}

void LinkDoodService::onGetGroupSetResult(QString result, QString verify_type, QString is_allow)
{
    qDebug()<<Q_FUNC_INFO;
    emit getGroupSetResult(result,verify_type,is_allow);
}

void LinkDoodService::onGetGroupInfoResult(QString result, Group group)
{
    qDebug()<<Q_FUNC_INFO;
    emit getGroupInfoResult(result,group);
}

void LinkDoodService::onInviteMemberResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit inviteMemberResult(result);
}

void LinkDoodService::onRemoveMemberResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit removeMemberResult(result);
}

void LinkDoodService::onSetMemberInfoResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit setMemberInfoResult(result);
}

void LinkDoodService::onGetMemberInfoResult(QString result, Member member)
{
    qDebug()<<Q_FUNC_INFO;
    emit getMemberInfoResult(result,member);
}

void LinkDoodService::onGetGroupMemberListReslut(int code, QString id, MemberList list)
{
    emit getGroupMemberListReslut( code, id, list);
}

void LinkDoodService::onGetMemberListResult(QString result, MemberList memberList)
{
    qDebug()<<Q_FUNC_INFO<<"xinxinxinxin";
    //    if(memberList.size()==0){
    //        qDebug()<<Q_FUNC_INFO<<"kongdekongdekongdekongde"<<m_groupId;
    //        m_pGroupControler->getMemberList(m_groupId);
    //    }
    //    else{
    //       emit getMemberListResult(result,memberList);
    //    }
    emit getMemberListResult(result,memberList);
}

void LinkDoodService::onGetGroupFileListResult(FileInfoList fileInfoList)
{
    emit getGroupFileListResult(fileInfoList);
}

void LinkDoodService::onDeleteGroupFileResult(QString result)
{
    emit deleteGroupFileResult(result);
}

void LinkDoodService::onUploadGroupAvatarResult(QString thum_url, QString src_url)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadGroupAvatarResult(thum_url,src_url);
}

void LinkDoodService::onSetPrivateSetting(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit setPrivateSettingResult(code);
}

void LinkDoodService::onGetPrivateSetting(int code, IMPrivateSetting ps)
{
    qDebug() << Q_FUNC_INFO;
    emit getPrivateSettingResult(code, ps);
}

LinkDoodService::~LinkDoodService()
{
    qDebug() << Q_FUNC_INFO <<"sdfdsgdgdfhfghfjg";
    setAppLoginStatus(0);
}

void LinkDoodService::initSdk()
{
    qDebug() << Q_FUNC_INFO;
    if(m_pPackageManager == NULL){
        m_pPackageManager = new CSystemPackageManager(this);
        qDebug() << Q_FUNC_INFO<<"m_pPackageManager";
    }

    m_sInstallPath = m_pPackageManager->packageInfo(LINKDOOD_SOPID)->installPath();
    qDebug() << Q_FUNC_INFO << "installPath = " << m_sInstallPath;

    QString crtPath = installPath();
    crtPath += "/crt/";
    m_pIMClient =  service::IMClient::getClient();
    qDebug() << Q_FUNC_INFO<<"dataPath:"<<dataPath() <<"cert:"<<crtPath;

    std::string appDataPath =dataPath().toStdString();
    std::string appCrtPath =crtPath.toStdString();
    qDebug() << Q_FUNC_INFO << "m_client->init before11111111111111:" << (m_pIMClient!= NULL);
    bool ret = m_pIMClient->init(appDataPath,appCrtPath);
    qDebug() << Q_FUNC_INFO << "m_client->initret:" << ret;
    if(ret)
    {
        qDebug() << Q_FUNC_INFO <<"init sdk";
        initObserver();
    }

    //    login("vrv","008615829282366","chengcy2015");
}

void LinkDoodService::unInitSdk()
{
    qDebug()<<Q_FUNC_INFO;
    return;
    m_pIMClient->getNotify()->removeAuthObserver(m_pAuth.get());
    m_pIMClient->getNotify()->removeChatObserver(m_pChatObserver.get());
    m_pIMClient->getNotify()->removeContactObserver(m_pContactObserver.get());
    m_pIMClient->getNotify()->removeGroupObserver(m_pGroupControler.get());
    m_pIMClient->getNotify()->removeEnterpriseObserver(m_pEnterpriseControler.get());
    m_pIMClient->getNotify()->removeSysMsgObserver(m_pSysMsg.get());
}

void LinkDoodService::initControl()
{
    qDebug()<<Q_FUNC_INFO;
    m_pAuth->init();
    m_pChatObserver->init();
    m_pContactObserver->init();
    m_pGroupControler->init();
    m_pEnterpriseControler->init();
    m_pSysMsg->init();
}

void LinkDoodService::initObserver()
{
    qDebug() << Q_FUNC_INFO;
    //    m_pSysMsg          = std::make_shared<SysMsgControler>();
    //    m_pAuth            = std::make_shared<AuthControler>();
    //    m_pContactObserver = std::make_shared<ContactControler>();
    //    m_pChatObserver    = std::make_shared<ChatControler>();
    //    m_pEnterpriseControler = std::make_shared<EnterpriseControler>();
    //    m_pGroupControler      =std::make_shared<GroupControler>();

    m_pSysMsg.reset(new SysMsgControler);
    m_pAuth.reset(new AuthControler);
    m_pContactObserver.reset(new ContactControler);
    m_pChatObserver.reset(new ChatControler);
    m_pEnterpriseControler.reset(new EnterpriseControler);
    m_pGroupControler.reset(new GroupControler);

    initControl();
    initConnects();

}

void LinkDoodService::initConnects()
{
    qDebug() << Q_FUNC_INFO ;
    QObject::connect(m_pChatObserver.get(),SIGNAL(downloadFileCancelId(QString,QString)),this,
                     SLOT(onDownloadFileCancelId(QString,QString)));

    QObject::connect(m_pChatObserver.get(),SIGNAL(uploadImageProgess(QString,QString,int)),this,
                     SLOT(onUploadImageProgess(QString,QString,int)));

    QObject::connect(m_pChatObserver.get(),SIGNAL(transMessageFinishBack(int,QString)),this,
                     SLOT(onTransMessageFinishBack(int,QString)));

    QObject::connect(m_pChatObserver.get(),SIGNAL(uploadFileBackUrl(QString,QString,QString,QString)),this,
                     SLOT(onUploadFileBackUrl(QString,QString,QString,QString)));

    QObject::connect(m_pChatObserver.get(),SIGNAL(uploadImgeBackUrl(QString,QString,QString,QString,QString)),this,
                     SLOT(onUploadImgeBackUrl(QString,QString,QString,QString,QString)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(chatAvatarChanged(QString,QString)),this,
                     SLOT(onChatAvatarChanged(QString,QString)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(chatAvatarChanged(QString,QString)),this,SLOT(onChatAvatarChanged(QString,QString)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(offlineMsgNoticeBack(IMOfflineMsgList)),this,
                     SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    QObject::connect(m_pChatObserver.get(),SIGNAL(sendMessageBack(bool,int64,QString)),this,
                     SLOT(onChatSendMessageResult(bool,int64,QString)));
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

    QObject::connect(m_pChatObserver.get(), SIGNAL(uploadAvatarBack(QString,QString,int)), this, SLOT(onChatUploadAvatar(QString,QString,int)));

    QObject::connect(m_pChatObserver.get(), SIGNAL(fileProgressBack(int,int,QString,QString,QString)), this, SLOT(onChatFileProgress(int,int,QString,QString,QString)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(downloadFileBack(int,QString,QString)), this, SLOT(onChatDownloadFile(int,QString,QString)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(downloadMainImageResult(QString,QString)), this, SLOT(onDownloadMainImageResult(QString,QString)));
    QObject::connect(m_pChatObserver.get(), SIGNAL(getUserInfoBack(int,Contact)), this, SLOT(onGetUserInfoResult(int,Contact)));

    QObject::connect(m_pChatObserver.get(), SIGNAL(downloadHistoryImageResult(int,QString,QString,QString)), this, SLOT(onDownloadHistoryImage(int,QString,QString,QString)));


    QObject::connect(m_pEnterpriseControler.get(),SIGNAL(getSonOrgsResult(int ,OrgList ,OrgUserList )),this,
                     SLOT(onGetSonOrgsResult(int,OrgList,OrgUserList )));
    QObject::connect(m_pEnterpriseControler.get(),SIGNAL(getOnlineStatesResult(QOnlineStateList)),this,
                     SLOT(onGetOnlineStatesResult(QOnlineStateList)));
    QObject::connect(m_pEnterpriseControler.get(),SIGNAL(getOrgUserInfoResult(int,OrgUser)),this,
                     SLOT(onGetorgUserInfoResult(int,OrgUser)));


    QObject::connect(m_pAuth.get(),SIGNAL(getLoginHistoryResult(LoginInfoList)),this,
                     SLOT(onGetLoginHistoryResult(LoginInfoList)));
    QObject::connect(m_pAuth.get(),SIGNAL(loginSucceeded(QString)),this,
                     SLOT(onLoginSucceeded(QString)));
    QObject::connect(m_pAuth.get(),SIGNAL(loginFailed(int)),this,
                     SLOT(onLoginFailed(int)));
    QObject::connect(m_pAuth.get(),SIGNAL(changePasswordResult(QString)),this,
                     SLOT(onChangePasswordResult(QString)));
    QObject::connect(m_pAuth.get(),SIGNAL(connectChanged(QString)),this,
                     SLOT(onConnectChanged(QString)));
    QObject::connect(m_pAuth.get(),SIGNAL(getVerifyImgResult(QString,QString)),this,
                     SLOT(onGetVerifyImgResult(QString,QString)));

    QObject::connect(m_pAuth.get(),SIGNAL(loginoutRelust(bool)),this,
                     SLOT(onLoginoutRelust(bool)));
    QObject::connect(m_pAuth.get(),SIGNAL(loginResultObserver(int,QString)),this,
                     SLOT(onLoginResultObserver(int,QString)));
    QObject::connect(m_pAuth.get(),SIGNAL(accountInfoChanged(Contact)),this,
                     SLOT(onAccountInfoChanged(Contact)));
    QObject::connect(m_pAuth.get(),SIGNAL(anthAvatarChanged(QString)),this,
                     SLOT(onAnthAvatarChanged(QString)));
    QObject::connect(m_pAuth.get(),SIGNAL(setPrivateSettingResult(int)),this, SLOT(onSetPrivateSetting(int)));
    QObject::connect(m_pAuth.get(),SIGNAL(getPrivateSettingResult(int,IMPrivateSetting)),this, SLOT(onGetPrivateSetting(int,IMPrivateSetting)));


    QObject::connect(m_pChatObserver.get(),SIGNAL(chatListChanged(Chat_UIList)),this,
                     SLOT(onChatListChanged(Chat_UIList)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactListChanged(int,ContactList)),this,
                     SLOT(onContactListChanged(int,ContactList)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactInfoChanged(int,Contact)),this,
                     SLOT(onContactInfoChanged(int,Contact)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(contactOnlineChanged(QString,QString,int)),this,SLOT(onOnlineChanged(QString,QString,int)));
    QObject::connect(m_pContactObserver.get(),SIGNAL(updateContactInfoBack(int)), this, SLOT(onUpdateContactInfo(int)));
    QObject::connect(m_pContactObserver.get(), SIGNAL(searchFromNetBack(int,ContactList, ContactList)),this,SLOT(onSearchFromNet(int, ContactList, ContactList)));
    QObject::connect(m_pContactObserver.get(), SIGNAL(searchFromLocalBack(int,ContactList, ContactList)),this,SLOT(onSearchFromLocal(int, ContactList, ContactList)));
    QObject::connect(m_pContactObserver.get(), SIGNAL(addContactBack(int)), this,SLOT(onAddContact(int)));
    QObject::connect(m_pContactObserver.get(), SIGNAL(removeContactBack(int)), this, SLOT(onRemoveContact(int)));
    QObject::connect(m_pContactObserver.get(), SIGNAL(getVerifyTypeBack(int,QString,int)), this, SLOT(onGetVerifyType(int,QString,int)));
    QObject::connect(m_pContactObserver.get(), SIGNAL(getContactInfo(Contact)), this, SLOT(onGetContactInfoResult(Contact)));


    //SysMsgControler
    QObject::connect(m_pSysMsg.get(),SIGNAL(removeSysMessageResult(QString)),this,SLOT(onRemoveSysMessageResult(QString)));
    QObject::connect(m_pSysMsg.get(),SIGNAL(sysMessageNotice(IMSysMsg)),this,SLOT(onSysMessageNotice(IMSysMsg)));
    QObject::connect(m_pSysMsg.get(), SIGNAL(getSysMessagesReult(int,IMSysMsgList)), this, SLOT(onGetSysMessages(int,IMSysMsgList)));

    QObject::connect(m_pGroupControler.get(),SIGNAL(groupListChanged(GroupList)),this,SLOT(onGroupListChanged(GroupList)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(groupAvatarChanged(QString,QString)),this,SLOT(onGroupAvatarChanged(QString,QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(memberAvatarChanged(QString,QString)),this,SLOT(onMemberAvatarChanged(QString,QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(groupInfoChanged(QString,Group)),this,SLOT(onGroupInfoChanged(QString,Group)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(groupLeaderChanged(QString,QString,QString,QString)),this,SLOT(onGroupLeaderChanged(QString,QString,QString,QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(memberInfoChanged(QString,Member)),this,SLOT(onMemberInfoChanged(QString,Member)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(memberListChanged(QString,QString,MemberList)),this,SLOT(onMemberListChanged(QString,QString,MemberList)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(createGroupResult(QString)),this,SLOT(onCreateGroupResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(addGroupResult(QString)),this,SLOT(onAddGroupResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(removeGroupResult(QString)),this,SLOT(onRemoveGroupResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(transferGroupResult(QString)),this,SLOT(onTransferGroupResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(setGroupSetResult(QString)),this,SLOT(onSetGroupSetResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(setGroupInfoResult(QString)),this,SLOT(onSetGroupInfoResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(getGroupSetResult(QString,QString,QString)),this,SLOT(onGetGroupSetResult(QString,QString,QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(getGroupInfoResult(QString,Group)),this,SLOT(onGetGroupInfoResult(QString,Group)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(inviteMemberResult(QString)),this,SLOT(onInviteMemberResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(removeMemberResult(QString)),this,SLOT(onRemoveMemberResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(setMemberInfoResult(QString)),this,SLOT(onSetMemberInfoResult(QString)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(getMemberInfoResult(QString,Member)),this,SLOT(onGetMemberInfoResult(QString,Member)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(getMemberListResult(QString,MemberList)),this,SLOT(onGetMemberListResult(QString,MemberList)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(getGroupMemberListReslut(int,QString,MemberList)),this,SLOT(onGetGroupMemberListReslut(int,QString,MemberList)));
    QObject::connect(m_pGroupControler.get(),SIGNAL(uploadGroupAvatarResult(QString,QString)),this,SLOT(onUploadGroupAvatarResult(QString,QString)));

    QObject::connect(m_pSysMsg.get(),SIGNAL(systemMessageNotice(QString,int64)),m_pChatObserver.get(),SLOT(onSystemMessageNotice(QString,int64)));
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

    msg.targetName = msg.name = QString::fromStdString(user.name);
    msg.thumb_avatar = QString::fromStdString(user.thumb_avatar);
    if(m_pChatObserver != NULL){
        m_pChatObserver->sendMessage(msg);
    }
}
void LinkDoodService::getGroupMemsList(QString groupid)
{
    qDebug()<<Q_FUNC_INFO;
    if(m_pGroupControler != NULL){
        m_pGroupControler->getMemberList(groupid);
    }
}




