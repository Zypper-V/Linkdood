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
#include "linkdoodclient.h"

class CDoodLoginManager : public CDoodListModel
{
    Q_OBJECT

public:
    explicit CDoodLoginManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodLoginManager();

    Q_INVOKABLE void login(const QString &server,
                           const QString &userId,
                           const QString &password);

    Q_INVOKABLE bool checkFirstWordIsSpace(const QString &text);

private:
    LinkDoodClient *m_pClient;
};

#endif // CDOODLOGINMANAGER_H
