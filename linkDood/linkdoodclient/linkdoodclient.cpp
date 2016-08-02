#include "linkdoodclient.h"
#include "linkdoodconst.h"
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>
#include <QDBusPendingReply>
#include <QDBusInterface>

LinkDoodClient::LinkDoodClient(QObject *parent) :
    QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    registerDoodDataTypes();

    initDBusConnect();
}

LinkDoodClient::~LinkDoodClient()
{

}

QString LinkDoodClient::installPath()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = manager.call("installPath");
    reply.waitForFinished();

    QString sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }

    return sTmp;
}

QString LinkDoodClient::createMsgId()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = manager.call("createMsgId");
    reply.waitForFinished();

    QString sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }

    return sTmp;
}

void LinkDoodClient::entryChat(const QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("entryChat",targetId);
}

void LinkDoodClient::exitChat(const QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("exitChat",targetId);
}

int LinkDoodClient::getAppLoginStatus()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<int> reply = manager.call("getAppLoginStatus");
    reply.waitForFinished();

    int sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }

    return sTmp;
}

void LinkDoodClient::setAppLoginStatus(const int status)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setAppLoginStatus",status);
}

void LinkDoodClient::login(const QString &server,
                           const QString &userId,
                           const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("login", server, userId, password);
}

void LinkDoodClient::autoLogin(QString id, QString service)
{
    qDebug() << Q_FUNC_INFO << id << service;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("autoLogin", id, service);
}

void LinkDoodClient::getVerifyImg(QString userid, QString code)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getVerifyImg",userid,code);
}

void LinkDoodClient::changepassword(QString oldpsw, QString newpsw)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("changepassword",oldpsw,newpsw);
}

QString LinkDoodClient::UserId()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = manager.call("UserId");
    reply.waitForFinished();

    QString sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }

    if(sTmp == ""){
        QString fileName = QString::fromStdString(APP_DATA_PATH)+"config.ini";
        QSettings settings(fileName, QSettings::IniFormat);
        sTmp = settings.value("myId","").toString();
    }
    return sTmp;
}

QString LinkDoodClient::userName()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = manager.call("userName");
    reply.waitForFinished();

    QString sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }

    if(sTmp == ""){
        QString fileName =QString::fromStdString(APP_DATA_PATH)+"config.ini";
        QSettings settings(fileName, QSettings::IniFormat);
        sTmp = settings.value("myName","").toString();
    }
    return sTmp;
}

QString LinkDoodClient::userType(QString userId)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = manager.call("userType",userId);
    reply.waitForFinished();

    QString sTmp;
    if (!reply.isError()) {
        sTmp = reply;
    } else {
        qDebug() << reply.error();
    }
    return sTmp;
}

void LinkDoodClient::updateContactInfo(QString userId, QString operStar, QString remark)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("updateContactInfo",userId,operStar,remark);
}

void LinkDoodClient::onOnlineChanged(QString id, QString deviceType)
{
    emit contactOnlineChanged(id,deviceType);
}

void LinkDoodClient::onElsewhereLogin(QString tip)
{
    qDebug() << Q_FUNC_INFO<<"zhezhezhezhezhezhe";
    emit elsewhereLogin(tip);
}

void LinkDoodClient::getAccountInfo()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getAccountInfo");
}

void LinkDoodClient::updateAccountInfo(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("updateAccountInfo",QVariant::fromValue<Contact>(user));
}

void LinkDoodClient::logout()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("logout");
}

void LinkDoodClient::removeChat(QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("removeChat",targetid);
}

void LinkDoodClient::setMessageRead(QString targetid, QString msgid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setMessageRead",targetid,msgid);
}

void LinkDoodClient::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getUnReadMessages");
}

void LinkDoodClient::getChatList()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getChatList");
}

void LinkDoodClient::deleteMessage(QString targetid, QStringList msgs)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("deleteMessage",targetid,QVariant::fromValue<QStringList>(msgs));
}

void LinkDoodClient::sendMessage(Msg msg)
{
    qDebug() << Q_FUNC_INFO << msg.fromid << ":" << msg.targetid << ":" << msg.body;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());

    //QVariant v;
    // v.setValue(msg);

    manager.call("sendMessage",QVariant::fromValue<Msg>(msg));
}

void LinkDoodClient::getMessages(const QString &targetid, const QString & msgid, const int& count, const int& flag)
{
    qDebug() << Q_FUNC_INFO << targetid;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getMessages",targetid,msgid,count,flag);
}


void LinkDoodClient::getSonOrgs(QString orgid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getSonOrgs",orgid);
}
void LinkDoodClient::getOnlineStates(QStringList &userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getOnlineStates",userid);
}

void LinkDoodClient::getOrgUserInfo(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getOrgUserInfo",userid);
}

void LinkDoodClient::createGroup(QString level, QString name, MemberList memberList)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("createGroup",level,name,QVariant::fromValue<MemberList>(memberList));
}

void LinkDoodClient::addGroup(QString groupid, QString verify_info)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("addGroup",groupid,verify_info);
}

void LinkDoodClient::removeGroup(QString type, QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("removeGroup",type,groupid);
}

void LinkDoodClient::transferGroup(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("transferGroup",groupid,userid);
}

void LinkDoodClient::setGroupSet(QString groupid, QString verify_type, QString is_allow)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setGroupSet",groupid,verify_type,is_allow);
}

void LinkDoodClient::setGroupInfo(Group group)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setGroupInfo",QVariant::fromValue<Group>(group));
}

void LinkDoodClient::getGroupSet(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getGroupSet",groupid);
}

void LinkDoodClient::getGroupInfo(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getGroupInfo",groupid);
}

void LinkDoodClient::inviteMember(QString groupid, MemberList memberList)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("inviteMember",groupid,QVariant::fromValue<MemberList>(memberList));
}

void LinkDoodClient::removeMember(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("removeMember",groupid,userid);
}

void LinkDoodClient::setMemberInfo(Member member)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setMemberInfo",QVariant::fromValue<Member>(member));
}

void LinkDoodClient::getMemberInfo(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getMemberInfo",groupid,userid);
}

void LinkDoodClient::getMemberList(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getMemberList",groupid);
}

void LinkDoodClient::getGroupList()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getGroupList");
}

void LinkDoodClient::getGroupFileList(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getGroupFileList",groupid);
}

void LinkDoodClient::deleteGroupFile(QStringList fileIdList)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("deleteGroupFile",fileIdList);
}

void LinkDoodClient::uploadGroupAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("uploadGroupAvatar",path);
}

void LinkDoodClient::getSysMessages(int type, int count, QString msgid, int flag)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getSysMessages", type, count, msgid, flag);
}

void LinkDoodClient::setSysMessagRead(int type, QString msg)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setSysMessageRead", type, msg);
}

void LinkDoodClient::response(IMSysMsgRespInfo info)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("response",QVariant::fromValue<IMSysMsgRespInfo>(info));
}

void LinkDoodClient::setPrivateSetting(IMPrivateSetting ps)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setPrivateSetting", QVariant::fromValue<IMPrivateSetting>(ps));
}

void LinkDoodClient::getPrivateSetting()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getPrivateSetting");
}
void LinkDoodClient::getLoginHistory()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getLoginHistory");
}

void LinkDoodClient::setLoginInfo(int flag, QString userid, QString username, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("setLoginInfo",flag,userid,username,avatar);
}

void LinkDoodClient::getContactList()
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getContactList");
}

void LinkDoodClient::uploadAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("uploadAvatar", path);
}

void LinkDoodClient::uploadAndSendFileMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("uploadAndSendFileMsg",QVariant::fromValue<Msg>(msg));
}

void LinkDoodClient::downloadFile(QString path, QString url, QString json,QString localId,QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("downloadFile", path, url, json,localId,targetId);
}

void LinkDoodClient::uploadAndSendImageMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("uploadAndSendImageMsg", QVariant::fromValue<Msg>(msg));
}

void LinkDoodClient::downloadImage(QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("downloadImage", url, property);
}

void LinkDoodClient::downloadHistoryImage(QString url, QString property, QString targetid, QString localid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("downloadHistoryImage",url, property, targetid, localid);
}

bool LinkDoodClient::decryptFile(QString encryptkey, QString srcpath, QString destpath)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    QDBusPendingReply<bool> reply = manager.call("decryptFile", encryptkey, srcpath, destpath);

    if (!reply.isError())
        return true;
    else
    {
        qDebug() << reply.error();
        return false;
    }
}

void LinkDoodClient::getFileList(int64 targetid, int64 fileid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getFileList", targetid, fileid, count, flag);
}

void LinkDoodClient::getUserInfo(QString userId)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getUserInfo", userId);
}

void LinkDoodClient::searchFromNet(QString key)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("searchFromNet", key);
}

void LinkDoodClient::searchFromLocal(QString key)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("searchFromLocal", key);
}

void LinkDoodClient::addContact(QString userid, QString remark, QString info)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("addContact", userid, remark, info);
}

void LinkDoodClient::removeContact(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("removeContact", userid);
}

void LinkDoodClient::getVerifyType(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getVerifyType", userid);
}

void LinkDoodClient::onLoginoutRelust(bool loginout)
{
    qDebug() << Q_FUNC_INFO << loginout;
    emit loginoutRelust(loginout);
}

void LinkDoodClient::onLoginSucceeded()
{
    qDebug() << Q_FUNC_INFO;
    emit loginSucceeded();
}

void LinkDoodClient::onGetVerifyImgResult(QString code, QString img)
{
    qDebug()<<Q_FUNC_INFO;
    emit getVerifyImgResult(code,img);
}

void LinkDoodClient::onChatListChanged(const Chat_UIList &chats)
{
    qDebug() << Q_FUNC_INFO;
    emit chatListChanged(chats);
}

void LinkDoodClient::onContactListChanged(int oper, ContactList contacts)
{
    qDebug() << Q_FUNC_INFO;
    emit contactListChanged(oper,contacts);
}

void LinkDoodClient::onLoginFailed(QString err)
{
    qDebug() << Q_FUNC_INFO;
    emit loginFailed(err);
}

void LinkDoodClient::onChangePasswordResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit changePasswordResult(result);
}

void LinkDoodClient::onConnectChanged(QString flag)
{
    qDebug() << Q_FUNC_INFO;
    emit connectChanged(flag);
}

void LinkDoodClient::onAnthAvatarChanged(QString avatar)
{
    emit anthAvatarChanged(avatar);
}

void LinkDoodClient::onSysMessageNotice(IMSysMsg sysMsg)
{
    qDebug()<<Q_FUNC_INFO;
    qDebug() << Q_FUNC_INFO << "  msgid:" << sysMsg.msgid << "   targetid:" << sysMsg.targetid << "  time:" << sysMsg.time << "   msgtypeText:" << sysMsg.msgtypeText << "   respons:" << sysMsg.respons << "   name:" << sysMsg.name << "   avatar:" << sysMsg.avatar << "   info:" << sysMsg.info << " isRead:" << sysMsg.isread;
    emit sysMessageNotice(sysMsg);
}

void LinkDoodClient::onGetSysMessages(int code, IMSysMsgList sysMsgList)
{
    qDebug()<<Q_FUNC_INFO;
    emit getSysMessagesResult(code, sysMsgList);
}



void LinkDoodClient::onGetSonOrgsResult(int code, OrgList orglist, OrgUserList orguserlist)
{
    qDebug() << Q_FUNC_INFO;
    emit text();
    emit getSonOrgsResult(code,orglist,orguserlist);
}

void LinkDoodClient::onGetOnlineStatesResult(QOnlineStateList onlinestatelist)
{
    qDebug() << Q_FUNC_INFO;
    emit getOnlineStatesResult(onlinestatelist);
}

void LinkDoodClient::onGetorgUserInfoResult(int code, OrgUser orguser)
{
    qDebug() << Q_FUNC_INFO;
    emit getOrgUserInfoResult(code,orguser);
}

void LinkDoodClient::onGroupListChanged(GroupList groupList)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupListChanged(groupList);
}
void LinkDoodClient::onGroupAvatarChanged(QString groupid, QString avatar)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupAvatarChanged(groupid,avatar);
}

void LinkDoodClient::onMemberAvatarChanged(QString userid, QString avatar)
{
    qDebug()<<Q_FUNC_INFO;
    emit memberAvatarChanged(userid,avatar);
}

void LinkDoodClient::onGroupInfoChanged(QString operType, Group group)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupInfoChanged(operType,group);
}

void LinkDoodClient::onGroupLeaderChanged(QString userid, QString user_name, QString groupid, QString group_name)
{
    qDebug()<<Q_FUNC_INFO;
    emit groupLeaderChanged(userid,user_name,groupid,group_name);
}

void LinkDoodClient::onMemberInfoChanged(QString groupid, Member member)
{
    qDebug()<<Q_FUNC_INFO;
    emit memberInfoChanged(groupid,member);
}

void LinkDoodClient::onMemberListChanged(QString operType, QString groupid, MemberList memberList)
{
    qDebug()<<Q_FUNC_INFO;
    emit memberListChanged(operType,groupid,memberList);
}

void LinkDoodClient::onCreateGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit createGroupResult(result);
}

void LinkDoodClient::onAddGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit addGroupResult(result);
}

void LinkDoodClient::onRemoveGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit removeGroupResult(result);
}

void LinkDoodClient::onTransferGroupResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit transferGroupResult(result);
}

void LinkDoodClient::onSetGroupSetResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit setGroupSetResult(result);
}

void LinkDoodClient::onSetGroupInfoResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit setGroupInfoResult(result);
}

void LinkDoodClient::onGetGroupSetResult(QString result, QString verify_type, QString is_allow)
{
    qDebug()<<Q_FUNC_INFO;
    emit getGroupSetResult(result,verify_type,is_allow);
}

void LinkDoodClient::onGetGroupInfoResult(QString result, Group group)
{
    qDebug()<<Q_FUNC_INFO;
    emit getGroupInfoResult(result,group);
}

void LinkDoodClient::onInviteMemberResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit inviteMemberResult(result);
}

void LinkDoodClient::onRemoveMemberResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit removeMemberResult(result);
}

void LinkDoodClient::onSetMemberInfoResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit setMemberInfoResult(result);
}

void LinkDoodClient::onGetMemberInfoResult(QString result, Member member)
{
    qDebug()<<Q_FUNC_INFO;
    emit getMemberInfoResult(result,member);
}

void LinkDoodClient::onGetMemberListResult(QString result, MemberList memberList)
{
    qDebug()<<Q_FUNC_INFO;
    emit getMemberListResult(result,memberList);
}
void LinkDoodClient::onGetGroupFileListResult(FileInfoList fileInfoList)
{
    qDebug()<<Q_FUNC_INFO;
    emit getGroupFileListResult(fileInfoList);
}

void LinkDoodClient::onDeleteGroupFileResult(QString result)
{
    qDebug()<<Q_FUNC_INFO;
    emit deleteGroupFileResilt(result);
}
void LinkDoodClient::onGetGroupMemberListReslut(int code, QString id, MemberList list)
{
    emit getGroupMemberListReslut( code, id, list);
}

void LinkDoodClient::onUploadGroupAvatarResult(QString thum_url, QString src_url)
{
    qDebug()<<Q_FUNC_INFO;
    emit uploadGroupAvatarResult(thum_url,src_url);
}


void LinkDoodClient::onServiceRestart()
{
    qDebug() << Q_FUNC_INFO;
    emit serviceRestart();
}

void LinkDoodClient::onContactInfoChanged(int oper, Contact user)
{
    qDebug() << Q_FUNC_INFO;
    emit contactInfoChanged(oper,user);
}

void LinkDoodClient::onChatAvatarChanged(QString id, QString avatar)
{
    qDebug() << Q_FUNC_INFO;
    emit chatAvatarChanged(id,avatar);
}

void LinkDoodClient::onChatOfflineMsgNotice(IMOfflineMsgList msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit offlineMsgNotice(msgList);
}

void LinkDoodClient::onChatMessageNotice(Msg msg)
{
    qDebug() << Q_FUNC_INFO<<"qqqqqqqqqqqqqqqqqqqqqqqq";
    emit chatMessageNotice(msg);
}

void LinkDoodClient::onChatSendMessageResult(bool code, QString sendTime, QString msgId)
{
    qDebug() << Q_FUNC_INFO;
    emit sendMessageResult(code,sendTime,msgId);
}

void LinkDoodClient::onChatDeleteMessagesResult(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit deleteMessagesResult(code);
}

void LinkDoodClient::onChatGetMessagesResult(bool code, QString sessionId, MsgList msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit getMessagesResult(code,sessionId,msgList);
}

void LinkDoodClient::onChatRemoveChatResult(bool code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatResult(code);
}

void LinkDoodClient::onGetLoginHistoryResult(LoginInfoList list)
{
    qDebug() << Q_FUNC_INFO;
    emit getLoginHistoryResult(list);
}

void LinkDoodClient::onLoginResultObserver(int code, QString userID)
{
    qDebug() << Q_FUNC_INFO;
    emit loginResultObserver(code,userID);
}

void LinkDoodClient::onAccountInfoChanged(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    emit accountInfoChanged(user);
}

void LinkDoodClient::onSessionMessageNotice(QString targetId, QString msgId,QString lastMsg,
                                            QString time,QString name, QString avater,QString unreadmsg)
{
    qDebug() << Q_FUNC_INFO;
    emit sessionMessageNotice(targetId,msgId,lastMsg,time,name,avater,unreadmsg);
}

void LinkDoodClient::onChatUploadAvatar(QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadAvatarResult(orgijson, thumbjson, code);
}

void LinkDoodClient::onChatUploadFile(int64 tagetid, QString jasoninfo, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadFileResult(QString::number(tagetid), jasoninfo, code);
}

void LinkDoodClient::onChatFileProgress(int extra_req, int process, QString info,QString localId,QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    emit fileProgressResult(extra_req, process, info,localId,targetId);
}

void LinkDoodClient::onTransMessageFinishBack(int code, QString targetId)
{
    emit transMessageFinishBack(code,targetId);
}

void LinkDoodClient::onUploadFileBackUrl(QString targetId, QString localId, QString fileUrl, QString enkey)
{
    emit uploadFileBackUrl(targetId,localId,fileUrl,enkey);
}

void LinkDoodClient::onUploadImgeBackUrl(QString targetId, QString localId, QString mainUrl, QString thumbUrl, QString enkey)
{
    emit uploadImgeBackUrl(targetId,localId,mainUrl,thumbUrl,enkey);
}

void LinkDoodClient::onChatDownloadFile(int code, QString localpath, QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadFileResult(code, localpath, targetid);
}

void LinkDoodClient::onChatupLoadImage(int64 tagetid, QString orgijson, QString thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO;
    emit uploadImageResult(QString::number(tagetid), orgijson, thumbjson, code);
}

void LinkDoodClient::onChatDownloadImage(int code, QString localpath, long long tagetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadImageResult(code, localpath, QString::number(tagetid));
}

void LinkDoodClient::onDownloadHistoryImage(int code, QString localpath, QString targetid, QString localid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadHistoryImageResult(code, localpath, targetid, localid);
}

void LinkDoodClient::onChatGetFileList(int code, FileInfoList fileList)
{
    qDebug() << Q_FUNC_INFO;
    emit getFileListResult(code, fileList);
}

void LinkDoodClient::onGetUserInfo(int code, Contact contact)
{
    qDebug() << Q_FUNC_INFO;
    emit getUserInfoResult(code, contact);
}

void LinkDoodClient::onSearchFromNetResult(int code, ContactList user, ContactList group)
{
    qDebug() << Q_FUNC_INFO;
    emit searchFromNetResult(code, user, group);
}

void LinkDoodClient::onSearchFromLocalResult(int code, ContactList user, ContactList group)
{
    qDebug() << Q_FUNC_INFO;
    emit searchFromLocalResult(code, user, group);
}

void LinkDoodClient::onUpdateContactInfoResult(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit updateContactInfoResult(code);
}

void LinkDoodClient::onAddContactResult(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit addContactResult(code);
}

void LinkDoodClient::onRemoveContactResult(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeContactResult(code);
}

void LinkDoodClient::onGetVerifyTypeResult(int code, QString userid, int type)
{
    qDebug() << Q_FUNC_INFO;
    emit getVerifyTypeResult(code, userid, type);
}

void LinkDoodClient::onSetPrivateSetting(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit setPrivateSettingResult(code);
}

void LinkDoodClient::onGetPrivateSetting(int code, IMPrivateSetting ps)
{
    qDebug() << Q_FUNC_INFO;
    emit getPrivateSettingResult(code, ps);
}

void LinkDoodClient::initDBusConnect()
{
    qDebug() << Q_FUNC_INFO;

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "transMessageFinishBack",
                                          this, SLOT(onTransMessageFinishBack(int,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadFileBackUrl",
                                          this, SLOT(onUploadFileBackUrl(QString,QString,QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadImgeBackUrl",
                                          this, SLOT(onUploadImgeBackUrl(QString,QString,QString,QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "sessionMessageNotice",
                                          this, SLOT(onSessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "deleteMessagesResult",
                                          this, SLOT(onChatDeleteMessagesResult(int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatAvatarChanged",
                                          this, SLOT(onChatAvatarChanged(QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "offlineMsgNotice",
                                          this, SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatMessageNotice",
                                          this, SLOT(onChatMessageNotice(Msg)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "sendMessageResult",
                                          this, SLOT(onChatSendMessageResult(bool,QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getMessagesResult",
                                          this, SLOT(onChatGetMessagesResult(bool,QString,MsgList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "removeChatResult",
                                          this, SLOT(onChatRemoveChatResult(bool)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadAvatarResult",
                                          this, SLOT(onChatUploadAvatar(QString,QString,int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadFileResult",
                                          this, SLOT(onChatUploadFile(long long,QString,int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "fileProgressResult",
                                          this, SLOT(onChatFileProgress(int,int,QString,QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "downloadFileResult",
                                          this, SLOT(onChatDownloadFile(int,QString, QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadImageResult",
                                          this, SLOT(onChatupLoadImage(int64,QString,QString,int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "downloadImageResult",
                                          this, SLOT(onChatDownloadImage(int,QString,int64)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "downloadHistoryImageResult",
                                          this, SLOT(onDownloadHistoryImage(int,QString,QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getFileListResult",
                                          this, SLOT(onChatGetFileList(int,FileInfoList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getUserInfoResult", this, SLOT(onGetUserInfo(int, Contact)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "searchFromNetResult", this, SLOT(onSearchFromNetResult(int,ContactList, ContactList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "searchFromLocalResult", this, SLOT(onSearchFromLocalResult(int,ContactList, ContactList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "updateContactInfoResult", this, SLOT(onUpdateContactInfoResult(int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE,"addContactResult", this, SLOT(onAddContactResult(int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE,"removeContactResult", this, SLOT(onRemoveContactResult(int)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE,"getVerifyTypeResult", this, SLOT(onGetVerifyTypeResult(int,QString,int)));


    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginoutRelust",
                                          this, SLOT(onLoginoutRelust(bool)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "changePasswordResult",
                                          this, SLOT(onChangePasswordResult(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "connectChanged",
                                          this, SLOT(onConnectChanged(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginFailed",
                                          this, SLOT(onLoginFailed(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "contactListChanged",
                                          this, SLOT(onContactListChanged(int,ContactList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH, DBUS_DOOD_INTERFACE, "contactOnlineChanged", this, SLOT(onOnlineChanged(QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginSucceeded",
                                          this, SLOT(onLoginSucceeded()));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getVerifyImgResult",
                                          this, SLOT(onGetVerifyImgResult(QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatListChanged",
                                          this, SLOT(onChatListChanged(Chat_UIList)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginResultObserver",
                                          this, SLOT(onLoginResultObserver(int,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "elsewhereLogin",
                                          this, SLOT(onElsewhereLogin(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getLoginHistoryResult",
                                          this, SLOT(onGetLoginHistoryResult(LoginInfoList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getSonOrgsResult",
                                          this, SLOT(onGetSonOrgsResult(int, OrgList,OrgUserList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getOnlineStatesResult",
                                          this, SLOT(onGetOnlineStatesResult(QOnlineStateList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getorgUserInfoResult",
                                          this, SLOT(onGetorgUserInfoResult(int,OrgUse)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "groupListChanged",
                                          this, SLOT(onGroupListChanged(GroupList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "groupAvatarChanged",
                                          this, SLOT(onGroupAvatarChanged(QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "memberAvatarChanged",
                                          this, SLOT(onMemberAvatarChanged(QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "groupInfoChanged",
                                          this, SLOT(onGroupInfoChanged(QString,Group)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "groupLeaderChanged",
                                          this, SLOT(onGroupLeaderChanged(QString,QString,QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "memberInfoChanged",
                                          this, SLOT(onMemberInfoChanged(QString,Member)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "memberListChanged",
                                          this, SLOT(onMemberListChanged(QString,QString,MemberList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "createGroupResult",
                                          this, SLOT(onCreateGroupResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "addGroupResult",
                                          this, SLOT(onAddGroupResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "removeGroupResult",
                                          this, SLOT(onRemoveGroupResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "transferGroupResult",
                                          this, SLOT(onTransferGroupResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "setGroupSetResult",
                                          this, SLOT(onSetGroupSetResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "setGroupInfoResult",
                                          this, SLOT(onSetGroupInfoResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getGroupSetResult",
                                          this, SLOT(onGetGroupSetResult(QString,QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getGroupInfoResult",
                                          this, SLOT(onGetGroupInfoResult(QString,Group)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "inviteMemberResult",
                                          this, SLOT(onInviteMemberResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "removeMemberResult",
                                          this, SLOT(onRemoveMemberResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "setMemberInfoResult",
                                          this, SLOT(onSetMemberInfoResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getMemberInfoResult",
                                          this, SLOT(onGetMemberInfoResult(QString,Member)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getMemberListResult",
                                          this, SLOT(onGetMemberListResult(QString,MemberList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getGroupFileListResult",
                                          this, SLOT(onGetGroupFileListResult(FileInfoList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "deleteGroupFileResult",
                                          this, SLOT(onDeleteGroupFileResult(QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadGroupAvatarResult",
                                          this, SLOT(onUploadGroupAvatarResult(QString,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getGroupMemberListReslut",
                                          this, SLOT(onGetGroupMemberListReslut(int,QString,MemberList)));


    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "accountInfoChanged",
                                          this, SLOT(onAccountInfoChanged(Contact)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "contactInfoChanged",
                                          this, SLOT(onContactInfoChanged(int,Contact)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "serviceRestart",
                                          this, SLOT(onServiceRestart()));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "sysMessageNotice",
                                          this, SLOT(onSysMessageNotice(IMSysMsg)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getSysMessageResult", this, SLOT(onGetSysMessages(int,IMSysMsgList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "anthAvatarChanged",
                                          this, SLOT(onAnthAvatarChanged(QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,DBUS_DOOD_INTERFACE, "setPrivateSettingResult",this, SLOT(onSetPrivateSetting(int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,DBUS_DOOD_INTERFACE, "getPrivateSettingResult",this, SLOT(onGetPrivateSetting(int,IMPrivateSetting)));
}
