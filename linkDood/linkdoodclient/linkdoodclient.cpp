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

void LinkDoodClient::changepassword(QString oldpsw, QString newpsw)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("changepassword",oldpsw,newpsw);
}

void LinkDoodClient::getUserInfo(QString &userId, QString &name, QString &avater)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("getUserInfo", userId, name, avater);
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

void LinkDoodClient::uploadFile(QString path, QString property)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("uploadFile", path, property);
}

void LinkDoodClient::downloadFile(QString path, QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("downloadFile", path, url, property);
}

void LinkDoodClient::uploadImage(QString thumbimg, QString srcimg, QString property)
{
    qDebug() << Q_FUNC_INFO;
    QDBusInterface manager(DBUS_DOOD_SERVICE,
                           DBUS_DOOD_PATH,
                           DBUS_DOOD_INTERFACE,
                           QDBusConnection::sessionBus());
    manager.call("uploadImage", thumbimg, srcimg, property);
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



void LinkDoodClient::onGetSonOrgsResult(int code, OrgList orglist, OrgUserList orguserlist)
{
    qDebug() << Q_FUNC_INFO;
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

void LinkDoodClient::onContactInfoChanged(int oper, Contact user)
{
    qDebug() << Q_FUNC_INFO;
    emit contactInfoChanged(oper,user);
}

void LinkDoodClient::onChatAvatarChanged(int64 id, QString avatar)
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

void LinkDoodClient::onChatFileProgress(int extra_req, int process, QString info)
{
    qDebug() << Q_FUNC_INFO;
    emit fileProgressResult(extra_req, process, info);
}

void LinkDoodClient::onChatDownloadFile(int code, QString localpath, int64 tagetid)
{
    qDebug() << Q_FUNC_INFO;
    emit downloadFileResult(code, localpath, QString::number(tagetid));
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

void LinkDoodClient::onChatGetFileList(int code, std::vector<MsgFileInfo> files)
{
    qDebug() << Q_FUNC_INFO;
    FileInfoList fileList;
    for(auto msg:files)
    {
        fileList.push_back(msg);
    }
    emit getFileListResult(code, fileList);
}

void LinkDoodClient::initDBusConnect()
{
    qDebug() << Q_FUNC_INFO;

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "sessionMessageNotice",
                                          this, SLOT(onSessionMessageNotice(QString,QString,QString,QString,QString,QString,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "deleteMessagesResult",
                                          this, SLOT(onChatDeleteMessagesResult(int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatAvatarChanged",
                                          this, SLOT(onChatAvatarChanged(int64,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "offlineMsgNotice",
                                          this, SLOT(onChatOfflineMsgNotice(IMOfflineMsgList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "chatMessageNotice",
                                          this, SLOT(onChatMessageNotice(Msg)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "sendMessageResult",
                                          this, SLOT(onChatSendMessageResult(bool,int64,int64)));
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
                                          this, SLOT(onChatFileProgress(int32,int32,QString)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "downloadFileResult",
                                          this, SLOT(onChatDownloadFile(int,QString, int64)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "uploadImageResult",
                                          this, SLOT(onChatupLoadImage(int64,QString,QString,int)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "downloadImageResult",
                                          this, SLOT(onChatDownloadImage(int,QString,int64)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getFileListResult",
                                          this, SLOT(onChatGetFileList(int,std::vector<MsgFileInfo>)));


    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginoutRelust",
                                          this, SLOT(onLoginoutRelust(bool)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "changePasswordResult",
                                          this, SLOT(onChangePasswordResult(QString)));

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
                                          DBUS_DOOD_INTERFACE, "chatListChanged",
                                          this, SLOT(onChatListChanged(Chat_UIList)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "loginResultObserver",
                                          this, SLOT(onLoginResultObserver(int,QString)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getLoginHistoryResult",
                                          this, SLOT(onGetLoginHistoryResult(LoginInfoList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getSonOrgsResult",
                                          this, SLOT(onGetSonOrgsResult(int, OrgList,OrgUser)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getOnlineStatesResult",
                                          this, SLOT(onGetOnlineStatesResult(QOnlineStateList)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "getorgUserInfoResult",
                                          this, SLOT(onGetorgUserInfoResult(int,OrgUse)));
    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "accountInfoChanged",
                                          this, SLOT(onAccountInfoChanged(Contact)));

    QDBusConnection::sessionBus().connect(DBUS_DOOD_SERVICE, DBUS_DOOD_PATH,
                                          DBUS_DOOD_INTERFACE, "contactInfoChanged",
                                          this, SLOT(onContactInfoChanged(int,Contact)));


}
