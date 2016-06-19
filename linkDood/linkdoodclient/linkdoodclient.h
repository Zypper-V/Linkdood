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
    void getOrgUserInfoResult(int code,OrgUser& orguser);
    //会话列表头像更新
    void chatAvatarChanged(int64 id,QString avatar);
    //监听离线消息通知
    void offlineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void newMessageNotice(Msg& msg);
    //发送消息返回
    void sendMessageResult(bool code,int64 sendTime,int64 msgId);
    //获取消息结果返回
    void getMessagesResult(bool code,int64 sessionId,MsgList& msgList);
    //移除会话结果返回
    void removeChatResult(bool);

    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);
public slots:
    QString installPath();
    //登录
    void login(const QString &server,
               const QString &userId,
               const QString &password);
    //退出登录
    void logout();
    //移除会话
    void removeChat(int64 targetid);
    //设置消息已读
    void setMessageRead(int64 targetid, int64 msgid);
    //发送消息
    void sendMessage(const Msg& msg);
    //获取消息
    void getMessages(int64 targetid, int64 msgid, int count, int flag);
    //获取子组织
    void getEnterpriseSonOrgs(int64 orgid);
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
    void onGetorgUserInfoResult(int code,OrgUser& orguser);
    //会话列表头像更新
    void onChatAvatarChanged(int64 id,QString avatar);
    //监听离线消息通知
    void onChatOfflineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void onChatMessageNotice(Msg& msg);
    //发送消息返回
    void onChatSendMessageResult(bool code,int64 sendTime,int64 msgId);
    //获取消息结果返回
    void onChatGetMessagesResult(bool code,int64 sessionId,MsgList& msgList);
    //移除会话结果返回
    void onChatRemoveChatResult(bool code);
    //获取登录历史记录
    void onGetLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void onLoginResultObserver(int code,QString userID);
private:
    void initDBusConnect();
};

#endif // LINKDOODCLIENT_H
