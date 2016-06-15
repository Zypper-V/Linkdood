#include<contactcontroler.h>
#include<iostream>
#include<QDebug>

#include "IMClient.h"
#include "IContactService.h"
#include "INotifyService.h"

ContactControler::ContactControler()
{

}

ContactControler::~ContactControler()
{

}

void ContactControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setContactObserver(this);
}

void ContactControler::onListChanged(int operType, std::vector<service::Contact> &users)
{
    qDebug() << Q_FUNC_INFO;
}

void ContactControler::onAvatarChanged(int64 userid, std::string avatar)
{
    qDebug() << Q_FUNC_INFO;
}

void ContactControler::onContactInfoChanged(int operType, service::User &users)
{
    qDebug() << Q_FUNC_INFO;
}

void ContactControler::onOnlineChanged(OnlineState &status)
{
    qDebug() << Q_FUNC_INFO;
}


