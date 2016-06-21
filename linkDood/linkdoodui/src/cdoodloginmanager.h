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
//    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)
//    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)
//    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

    Q_PROPERTY(bool windowFocus READ windowFocus WRITE setWindowFocus NOTIFY windowFocusChanged)

public:
    explicit CDoodLoginManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodLoginManager();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void login(const QString &server,
                           const QString &userId,
                           const QString &password);

    //用户信息UserId
    Q_INVOKABLE QString userId();
    //用户信息
    void getUserInfo(QString& userId,
                     QString& name,
                     QString& avater);

    Q_INVOKABLE bool checkFirstWordIsSpace(const QString &text);
     //获取登录历史记录
    Q_INVOKABLE void getLoginHistory(void);
    //设置登录信息
    Q_INVOKABLE void setLoginInfo(int flag, QString userid, QString username, QString avatar);

  //  Q_INVOKABLE QString userId();
    bool windowFocus() const;
    Q_INVOKABLE bool setWindowFocus(const bool &windowFocus);

//    QString user()const;
//    QString server()const;
//    QString password()const;
//    void setUser(QString user);
//    void setServer(QString server);
//    void setPassword(QString password);
signals:
    void loginSucceeded();
    void loginFailed(QString err);
    void loginoutRelust(bool loginout);
    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);
    void windowFocusChanged();

//    void userChanged();
//    void serverChanged();
//    void passwordChanged();
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
//    QString mUser;
//    QString mServer;
//    QString mPassword;

    bool m_bWindowFocus;

    LinkDoodClient *m_pClient;
};

#endif // CDOODLOGINMANAGER_H
