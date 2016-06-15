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
 * \file cportalloginmanager.h
 * \brief 登陆管理
 */
#ifndef CDOODLOGINMANAGER_H
#define CDOODLOGINMANAGER_H

#include <QObject>

#include "cdoodlistmodel.h"

class CDoodLoginManager : public CDoodListModel
{
    Q_OBJECT

public:
    explicit CDoodLoginManager(QObject *parent = 0);

    ~CDoodLoginManager();

    // 功能		:	登录
    // 返回		:	NULL
    // 返回值    :	void
    // 参数		:
    // 		1.  server	服务器地址
    // 		1.  userId	登录ID
    // 		2.  password	登录密码
    Q_INVOKABLE void login(const QString &server,
                           const QString &userId,
                           const QString &password);

    Q_INVOKABLE bool checkFirstWordIsSpace(const QString &text);

};

#endif // CDOODLOGINMANAGER_H
