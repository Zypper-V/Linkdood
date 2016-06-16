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
public slots:
    QString installPath();

    void login(const QString &server,
               const QString &userId,
               const QString &password);

private slots:
    void onLoginSucceeded();
    void onChatListChanged(const Chat_UIList& chats);

    void onTestSignal(const QString &str);
private:
    void initDBusConnect();
};

#endif // LINKDOODCLIENT_H
