/*
* This file is part of CDoodLoginManager
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
 * \file cdoodloginmanager.h
 * \brief 登陆管理
 */
#ifndef CDOODLOGINMANAGER_H
#define CDOODLOGINMANAGER_H

#include <QObject>
#include <QtQuick/QQuickView>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodLoginManager : public CDoodListModel
{
    Q_OBJECT
public:
    explicit CDoodLoginManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodLoginManager();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void login(const QString &server,
                           const QString &userId,
                           const QString &password);

    Q_INVOKABLE bool checkFirstWordIsSpace(const QString &text);
     //获取登录历史记录
    Q_INVOKABLE void getLoginHistory(void);
    //设置登录信息
    Q_INVOKABLE void setLoginInfo(int flag, QString userid, QString username, QString avatar);

    Q_INVOKABLE QString userId();
signals:
    void loginSucceeded();
    void loginFailed(QString err);
    void loginoutRelust(bool loginout);
    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);

private slots:
    void onLoginSucceeded();
    void onLoginFailed(QString err);
    void onLoginoutRelust(bool loginout);
    //获取登录历史记录
    void onGetLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void onLoginResultObserver(int code,QString userID);
private:
    void initConnect();

    QString mUserId;

    LinkDoodClient *m_pClient;
};

#endif // CDOODLOGINMANAGER_H
