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
    Q_PROPERTY(int loginStatus READ loginStatus)
    Q_PROPERTY(int nVerifyImgCount READ nVerifyImgCount WRITE setNVerifyImgCount NOTIFY nVerifyImgCountChanged)
    Q_PROPERTY(QString verifyImg READ verifyImg WRITE setVerifyImg NOTIFY verifyImgChanged)
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(bool windowFocus READ windowFocus WRITE setWindowFocus NOTIFY windowFocusChanged)
public:
    explicit CDoodLoginManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodLoginManager();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void changepassword(QString oldpsw,QString newpsw);
    Q_INVOKABLE void login(const QString &server,
                           const QString &userId,
                           const QString &password);
    Q_INVOKABLE void autoLogin(QString id,QString service);
    Q_INVOKABLE void getVerifyImg( QString userid,
                            QString code);

    Q_INVOKABLE void openUrl(QString url);
    // 从配置文件读取登录状态
//    Q_INVOKABLE void autoLoginLastAccount();
    Q_INVOKABLE int getAppLoginStatus();
    //向配置文件写入登录状态
    Q_INVOKABLE void setAppLoginStatus(const int status);

    Q_INVOKABLE void setLoginPhone(QString phone);
    Q_INVOKABLE void setLoginService(QString service);
    Q_INVOKABLE QString getLoginPhone();
    Q_INVOKABLE QString getLoginService();
    Q_INVOKABLE void setLoginPhoneId(QString id);
    Q_INVOKABLE void setLoginServiceId(QString service);
    Q_INVOKABLE QString getLoginPhoneId();
    Q_INVOKABLE QString getLoginServiceId();



//    Q_INVOKABLE void setLastLoginAccount(QString service,QString id,QString psw);
//    Q_INVOKABLE void getLastLoginAccount(QString& service,QString& id,QString& psw);

    //用户信息UserId    
    Q_INVOKABLE QString verifyImg();
    Q_INVOKABLE void setVerifyImg(QString verifyImg);

    Q_INVOKABLE int nVerifyImgCount();
    Q_INVOKABLE void setNVerifyImgCount(int count);

    Q_INVOKABLE QString userId();
    Q_INVOKABLE void setUserId(QString userId);

    bool windowFocus() const;
    Q_INVOKABLE bool setWindowFocus(const bool &windowFocus);

    Q_INVOKABLE bool checkFirstWordIsSpace(const QString &text);
    //获取登录历史记录
    Q_INVOKABLE void getLoginHistory(void);

    //设置登录信息
    Q_INVOKABLE void setLoginInfo(int flag, QString userid, QString username, QString avatar);
    Q_INVOKABLE int loginStatus();
signals:
    void loginStatusChanged();
    void autoLogin();
    void getVerifyImgResult(QString result);
    void loginSucceeded();
    void loginFailed(QString err);
    void loginoutRelust(bool loginout);
    void changePasswordResult(QString result);
    void elsewhereLogin(QString tip);
    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);
    void windowFocusChanged();
    void userIdChanged();
    void verifyImgChanged();
    void nVerifyImgCountChanged();

    //servie重启信号
    void serviceRestart();
    void getLoginHistoryResult(QString userid,QString service);
private slots:
    void onElsewhereLogin(QString tip);
    void onLoginSucceeded();
    void onGetVerifyImgResult(QString code,QString img);
    void onLoginFailed(QString err);
    void onLoginoutRelust(bool loginout);
    void onChangePasswordResult(QString result);
    //获取登录历史记录
    void onGetLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void onLoginResultObserver(int code,QString userID);

    //servie重启信号
    void onServiceRestart();
private:
    void initConnect();
    int mLoginCount;
    int mNVerifyImgCount;
    QString mVerifyImg;
    QString mUserId;
    bool m_bWindowFocus;
    QString mVerifyId;
    LinkDoodClient *m_pClient;
};

#endif // CDOODLOGINMANAGER_H
