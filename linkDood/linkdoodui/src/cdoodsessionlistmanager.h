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

class CDoodSessionListItem;

class CDoodSessionListManager : public CDoodListModel
{
    Q_OBJECT
    Q_PROPERTY(int unreadCount READ unreadCount WRITE setUnreadCount NOTIFY unreadCountChanged)
public:
    explicit CDoodSessionListManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodSessionListManager();

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

    int  unreadCount()const;
    //count 负数：未读数减少
    void setUnreadCount(int count);
signals:
    void unreadCountChanged();

    void chatListChanged(const Chat_UIList& chats);
private slots:
    void onChatListChanged(const Chat_UIList& chats);
    //会话列表(通知栏)新消息更新通知
    void onSessionMessageNotice(QString targetId,
                                QString msgId,
                                QString lastMsg,
                                QString time,
                                QString name,
                                QString avater,
                                QString unreadmsg);
private:
    void initConnect();

private:
    LinkDoodClient *m_pClient;
    int mUnreadCount;
    QMap<QString, CDoodSessionListItem*> sessionListMap;

};
#endif // CDOODSESSIONLISTMANAGER_H
