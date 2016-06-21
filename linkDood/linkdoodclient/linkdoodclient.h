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
    void chatListChanged(const Chat_UIList& chats);
    void loginFailed(QString err);
    void contactListChanged(int oper,ContactList contacts);
    void loginoutRelust(bool loginout);

    //获取组织返回
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(int code,OrgUser orguser);
    //会话列表头像更新
    void chatAvatarChanged(int64 id,QString avatar);
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
    //会话列表(通知栏)新消息更新通知
    void sessionMessageNotice(QString,QString,QString,QString,QString,QString);
public slots:
    QString installPath();

    //唯一标识Id
    QString msgId();

    //进入会话UI
    void entryChat(const QString targetId);
    //离开会话UI
    void exitChat(const QString targetId);

    // 从配置文件读取登录状态
    void getAppLoginStatus(int& status);
    //向配置文件写入登录状态
    void setAppLoginStatus(const int status);
    //登录
    void login(const QString &server,
               const QString &userId,
               const QString &password);

    //用户信息
    void getUserInfo(QString& userId,
                     QString& name,
                     QString& avater);
    //用户信息UserId
    QString UserId();
    //退出登录
    void logout();
    //移除会话
    void removeChat(QString targetid);
    //设置消息已读
    void setMessageRead(QString targetid, QString msgid);
    //获取未读消息列表
    void getUnReadMessages(void);
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

    /*****************start Enterprise**************************/
   void getSonOrgs(QString orgid);
   void getOnlineStates(QStringList& userid);
   void getOrgUserInfo(QString userid);
   /*****************end Enterprise**************************/
private slots:
    void onLoginoutRelust(bool loginout);
    void onLoginSucceeded();
    void onChatListChanged(const Chat_UIList& chats);
    void onContactListChanged(int oper,ContactList contacts);
    void onLoginFailed(QString err);

    //获取组织返回
    void onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser orguser);
    //会话列表头像更新
    void onChatAvatarChanged(int64 id,QString avatar);
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
    //会话列表(通知栏)新消息更新通知
    void onSessionMessageNotice(QString,QString,QString,QString,QString,QString);
private:
    void initDBusConnect();
};

#endif // LINKDOODCLIENT_H
