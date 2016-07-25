/*
* This file is part of LinkDoodClient
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       Zhang Peng <zhangpeng@syberos.com>
*
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

#ifndef LINKDOODCLIENT_H
#define LINKDOODCLIENT_H

#include <QObject>
#include  "linkdoodtypes.h"

class LinkDoodClient : public QObject
{
    Q_OBJECT
public:
    explicit LinkDoodClient(QObject *parent = 0);

    ~LinkDoodClient();

signals:
    void loginSucceeded();
    void getVerifyImgResult(QString,QString);
    void changePasswordResult(QString);
    void connectChanged(QString);
    void chatListChanged(const Chat_UIList& chats);
    void loginFailed(QString err);
    void contactListChanged(int oper,ContactList contacts);
    void loginoutRelust(bool loginout);
    void anthAvatarChanged(QString avatar);
    //系统消息推送
    void sysMessageNotice(IMSysMsg sysMsg);
    void getSysMessagesResult(int code, IMSysMsgList sysMsgList);

    //获取组织返回
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(int code,OrgUser orguser);
    void text();

    void groupListChanged(GroupList);
    void groupAvatarChanged(QString groupid,QString avatar);
    void memberAvatarChanged(QString userid,QString avatar);
    void groupInfoChanged(QString operType,Group group);
    void groupLeaderChanged(QString userid,QString user_name,QString groupid,QString group_name);
    void memberInfoChanged(QString groupid,Member member);
    void memberListChanged(QString operType,QString groupid,MemberList members);
    void createGroupResult(QString result);
    void addGroupResult(QString result);
    void removeGroupResult(QString result);
    void transferGroupResult(QString result);
    void setGroupSetResult(QString result);
    void setGroupInfoResult(QString result);
    void getGroupSetResult(QString result,QString verify_type,QString is_allow);
    void getGroupInfoResult(QString result,Group group);
    void inviteMemberResult(QString result);
    void removeMemberResult(QString result);
    void setMemberInfoResult(QString result);
    void getMemberInfoResult(QString result,Member member);
    void getMemberListResult(QString result,MemberList memberList);
    void getGroupFileListResult(FileInfoList fileInfoList);
    void deleteGroupFileResilt(QString result);
    void getGroupMemberListReslut(int code, QString id, MemberList list);
    //servie重启信号
    void serviceRestart();

    //联系人信息更新
    void contactInfoChanged(int oper,Contact user);
    //监听联系人信息更新
    void contactOnlineChanged(QString id,QString deviceText);
    void elsewhereLogin(QString tip);

    //会话列表头像更新
    void chatAvatarChanged(QString id,QString avatar);
    //监听离线消息通知
    void offlineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void chatMessageNotice(Msg msg);
    //发送消息返回
    void sendMessageResult(bool code,QString sendTime,QString msgId);
    //获取消息结果返回
    void getMessagesResult(bool code,QString sessionId,MsgList msgList);
    //移除会话结果返回
    void removeChatResult(bool);
    //移除消息结果返回
    void deleteMessagesResult(int code);
    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);
    //推送用户信息
    void accountInfoChanged(Contact user);
    //会话列表(通知栏)新消息更新通知
    void sessionMessageNotice(QString,QString,QString,QString,QString,QString,QString);

    //上传头像返回
    void uploadAvatarResult(QString orgijson, QString thumbjson, int code);
    //上传文件返回
    void uploadFileResult(QString tagetid, QString jasoninfo, int code);
    //文件进度返回
    void fileProgressResult(int extra_req, int process, QString info,QString localId,QString targetId);

    //下载文件返回
    void downloadFileResult(int code, QString localpath, QString tagetid);
    //上传图片返回
    void uploadImageResult(QString tagetid, QString orgijson, QString thumbjson, int code);
    //下载图片返回
    void downloadImageResult(int code, QString jasoninfo, QString tagetid);
    //获取文件列表返回
    void getFileListResult(int code, FileInfoList fileList);
    //获取联发系人返回
    void getUserInfoResult(int code, Contact contact);
    //从网络获取联系人返回
    void searchFromNetResult(int code, ContactList user, ContactList group);
    //从网络获取联系人返回
    void searchFromLocalResult(int code, ContactList user, ContactList group);
    //更新联系人信息返回
    void updateContactInfoResult(int code);
    //添加联系人返回
    void addContactResult(int code);
    //删除联系人返回
    int removeContactResult(int code);



public slots:
    QString installPath();

    //唯一标识Id
    QString createMsgId();

    //进入会话UI
    void entryChat(const QString targetId);
    //离开会话UI
    void exitChat(const QString targetId);

    // 从配置文件读取登录状态
     int getAppLoginStatus();
    //向配置文件写入登录状态
    void setAppLoginStatus(const int status);
    //登录
    void login(const QString &server,
               const QString &userId,
               const QString &password);
    void getVerifyImg( QString userid,QString code);
    void changepassword(QString oldpsw,QString newpsw);
    //用户信息UserId
    QString UserId();
    QString userName();
    QString userType(QString userId);
    //更新联系人信息
     void updateContactInfo(QString userId,QString operStar,QString remark="");
     //改变联系人状态
     void onOnlineChanged(QString id, QString deviceType);
     void onElsewhereLogin(QString tip);

    //获取账户信息
    void getAccountInfo(void);
    //更新用户信息
    void updateAccountInfo(Contact user);
    //退出登录
    void logout();
    //移除会话
    void removeChat(QString targetid);
    //设置消息已读
    void setMessageRead(QString targetid, QString msgid);
    //获取未读消息列表
    void getUnReadMessages(void);
    //获取会话列表
    void getChatList();
    //删除消息
    void deleteMessage(QString targetid, QStringList msgs);
    //发送消息
    void sendMessage(Msg msg);
    //获取消息
    void getMessages(const QString &targetid, const QString & msgid, const int& count, const int& flag);
    //获取登录历史记录
    void getLoginHistory(void);
    //设置登录信息
    void setLoginInfo(int flag, QString userid, QString username, QString avatar);
    //获取会话列表
    void getContactList();

    //上传头像
    void uploadAvatar(QString path);
    //上传文件
    void uploadAndSendFileMsg(Msg msg);
    //下载文件
    void downloadFile(QString path, QString url, QString json,QString localId,QString targetId);
    //上传照片
    void uploadAndSendImageMsg(Msg);
    //下载图片
    void downloadImage(QString url, QString property);
    //解密文件
    bool decryptFile(QString encryptkey, QString srcpath, QString destpath);
    //获取文件列表
    void getFileList(int64 targetid, int64 fileid, int count, int flag);
    //用户信息
    void getUserInfo(QString userId);
    //从网络获取联系人
    void searchFromNet(QString key);
    //从本地获取联系人
    void searchFromLocal(QString key);
    //添加联系人
    void addContact(QString userid, QString remark, QString info);
    //删除联系人
    void removeContact(QString userid);


    /*****************start Enterprise**************************/
   void getSonOrgs(QString orgid);
   void getOnlineStates(QStringList& userid);
   void getOrgUserInfo(QString userid);
   /*****************end Enterprise**************************/

   void createGroup(QString level, QString name, MemberList memberList);
   void addGroup(QString groupid, QString verify_info);
   void removeGroup(QString type, QString groupid);
   void transferGroup(QString groupid, QString userid);
   void setGroupSet(QString groupid, QString verify_type, QString is_allow);
   void setGroupInfo(Group group);
   void getGroupSet(QString groupid);
   void getGroupInfo(QString groupid);
   void inviteMember(QString groupid,MemberList memberList);
   void removeMember(QString groupid, QString userid);
   void setMemberInfo(Member member);
   void getMemberInfo(QString groupid,QString userid);
   void getMemberList(QString groupid);
   void getGroupList();
   void getGroupFileList(QString groupid);
   void deleteGroupFile(QStringList fileIdList);

   void getSysMessages(int type,int count,QString msgid,int flag);
   void setSysMessagRead(int type, QString msg);
   void response(IMSysMsgRespInfo info);

private slots:
    void onLoginoutRelust(bool loginout);
    void onLoginSucceeded();
    void onGetVerifyImgResult(QString code,QString img);
    void onChatListChanged(const Chat_UIList& chats);
    void onContactListChanged(int oper,ContactList contacts);
    void onLoginFailed(QString err);
    void onChangePasswordResult(QString result);
    void onConnectChanged(QString flag);
    void onAnthAvatarChanged(QString avatar);
    //系统消息推送
    void onSysMessageNotice(IMSysMsg sysMsg);
    void onGetSysMessages(int code, IMSysMsgList sysMsgList);

    //获取组织返回
    void onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser orguser);

    void onGroupListChanged(GroupList groupList);
    void onGroupAvatarChanged(QString groupid,QString avatar);
    void onMemberAvatarChanged(QString userid,QString avatar);
    void onGroupInfoChanged(QString operType,Group group);
    void onGroupLeaderChanged(QString userid,QString user_name,QString groupid,QString group_name);
    void onMemberInfoChanged(QString groupid,Member member);
    void onMemberListChanged(QString operType,QString groupid,MemberList memberList);
    void onCreateGroupResult(QString result);
    void onAddGroupResult(QString result);
    void onRemoveGroupResult(QString result);
    void onTransferGroupResult(QString result);
    void onSetGroupSetResult(QString result);
    void onSetGroupInfoResult(QString result);
    void onGetGroupSetResult(QString result,QString verify_type,QString is_allow);
    void onGetGroupInfoResult(QString result,Group group);
    void onInviteMemberResult(QString result);
    void onRemoveMemberResult(QString result);
    void onSetMemberInfoResult(QString result);
    void onGetMemberInfoResult(QString result,Member member);
    void onGetMemberListResult(QString result,MemberList memberList);
    void onGetGroupFileListResult(FileInfoList fileInfoList);
    void onDeleteGroupFileResult(QString result);
    void onGetGroupMemberListReslut(int code, QString id, MemberList list);
    //servie重启信号
    void onServiceRestart();
    //联系人信息更新
    void onContactInfoChanged(int oper,Contact user);

    //会话列表头像更新
    void onChatAvatarChanged(QString id,QString avatar);
    //监听离线消息通知
    void onChatOfflineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void onChatMessageNotice(Msg msg);
    //发送消息返回
    void onChatSendMessageResult(bool code,QString sendTime,QString msgId);
    //移除消息结果返回
    void onChatDeleteMessagesResult(int code);
    //获取消息结果返回
    void onChatGetMessagesResult(bool code,QString sessionId,MsgList msgList);
    //移除会话结果返回
    void onChatRemoveChatResult(bool code);
    //获取登录历史记录
    void onGetLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void onLoginResultObserver(int code,QString userID);
    //推送用户信息
    void onAccountInfoChanged(Contact user);
    //会话列表(通知栏)新消息更新通知
    void onSessionMessageNotice(QString,QString,QString,QString,QString,QString,QString);
    //上传头像返回
    void onChatUploadAvatar(QString orgijson, QString thumbjson, int code);
    //上传文件返回
    void onChatUploadFile(int64 tagetid, QString jasoninfo, int code);
    //文件进度
    void onChatFileProgress(int extra_req, int process, QString info,QString localId,QString targetId);

    //下载文件返回
    void onChatDownloadFile(int code, QString localpath, QString tagetid);
    //上传图片返回
    void onChatupLoadImage(int64 tagetid, QString orgijson, QString thumbjson, int code);
    //下载图片返回
    void onChatDownloadImage(int code, QString localpath, int64 tagetid);
    //获取文件列表返回
    void onChatGetFileList(int code, FileInfoList fileList);
    //获取用户信息返回
    void onGetUserInfo(int code, Contact contact);
    //从网络获取联系人返回
    void onSearchFromNetResult(int code, ContactList user, ContactList group);
    //从网络获取联系人返回
    void onSearchFromLocalResult(int code, ContactList user, ContactList group);
    //更新联系人信息返回
    void onUpdateContactInfoResult(int code);
    //添加联系人返回
    void onAddContactResult(int code);
    //删除联系人返回
    void onRemoveContactResult(int code);

private:
    void initDBusConnect();
};
#endif // LINKDOODCLIENT_H
