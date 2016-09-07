/*
* This file is part of CDoodSessionListManager
*
* Copyright (C) 2014 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
*
* Authors:
*       zhangpeng <zhangpeng@syberos.com>
*
* This software, including documentation, is protected by copyright controlled
* by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
*/

/*!
 * \file cdoodsessionlistManager.h
 * \brief 会话列表管理
 */
#ifndef CDOODSESSIONLISTMANAGER_H
#define CDOODSESSIONLISTMANAGER_H

#include <QObject>
#include <QtQuick/QQuickView>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"
#include "linkdoodui_workspace.h"

class CDoodSessionListItem;

class CDoodSessionListManager : public CDoodListModel
{
    Q_OBJECT
    Q_PROPERTY(int unreadCount READ unreadCount WRITE setUnreadCount NOTIFY unreadCountChanged)
public:
    explicit CDoodSessionListManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodSessionListManager();
    Q_INVOKABLE void removeNitification(QString targetId);
    //获取会话列表
    Q_INVOKABLE void getChatList();
    //清空会话列表
    Q_INVOKABLE void clearChatList();

    Q_INVOKABLE QString getHeaderColor(const QString &id);

    Q_INVOKABLE QString getSubName(const QString &name);

    Q_INVOKABLE bool checkFileExists(const QString &path);
    //删除列表项
    Q_INVOKABLE void removeChatItem(QString id);

    Q_INVOKABLE void clickChatItem(QString id);

    Q_INVOKABLE void entrySysMsgPage();
    Q_INVOKABLE void exitSysMsgPage();

    int  unreadCount()const;
    //count 负数：未读数减少
    void setUnreadCount(int count);
signals:
    void unreadCountChanged();

    void chatListChanged(const Chat_UIList& chats);

private slots:
    void onTipMe(QString groupid);
    void onAvatarChanged(QString targetId,QString avatar);
    void onChatListChanged(const Chat_UIList& chats);
    void onGetUserInfo(int code, Contact contact);
    void onGetGroupInfo(QString code, Group group);
    //会话列表(通知栏)新消息更新通知
    void onSessionMessageNotice(QString targetId,
                                QString msgId,
                                QString lastMsg,
                                QString time,
                                QString name,
                                QString avater,
                                QString unreadmsg);
    //监听离线消息通知
    void onOfflineMsgNotice(IMOfflineMsgList msgList);
    void onDraftChanged(QString id, QString avater,QString name,QString chatType,QString draft);

    //系统消息推送
    void onSysMessageNotice(IMSysMsg sysMsg);
    void onRemoveSysMsg(QString msgtype,QString msgid);
    void onGroupInfoChanged(QString type,Group gp);
    void onGetOrgUserInfoResult(int code,OrgUser orguser);
private:
    void initConnect();
    void addSysMessage(IMSysMsg sysMsg);

private:
    LinkDoodClient *m_pClient;
    int  mUnreadCount;
    bool mIsSysMsgPage;
    QMap<QString, CDoodSessionListItem*> sessionListMap;
    linkdoodui_Workspace* m_pUiManager;
    QString updateItemInfor(QString targetId,QString name,  QString avater);
    int indexOfNewItem(qint64 date);
    void insertItemByTime(CDoodSessionListItem* item);
};
#endif // CDOODSESSIONLISTMANAGER_H
