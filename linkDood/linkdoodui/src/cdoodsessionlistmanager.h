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

class CDoodSessionListManager : public CDoodListModel
{
    Q_OBJECT

public:
    explicit CDoodSessionListManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodSessionListManager();

    //获取会话列表
    Q_INVOKABLE void getChatList();

    Q_INVOKABLE QString getHeaderColor(const QString &id);

    Q_INVOKABLE QString getSubName(const QString &name);

    Q_INVOKABLE bool checkFileExists(const QString &path);

signals:
    void chatListChanged(const Chat_UIList& chats);
private slots:
    void onChatListChanged(const Chat_UIList& chats);
private:
    void initConnect();

    LinkDoodClient *m_pClient;
};
#endif // CDOODSESSIONLISTMANAGER_H
