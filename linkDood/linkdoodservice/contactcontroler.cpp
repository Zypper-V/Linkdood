#include<contactcontroler.h>
#include<iostream>
#include<QDebug>
#include <QMetaType>

#include "IMClient.h"
#include "IContactService.h"
#include "INotifyService.h"
#include "Contact.h"

ContactControler::ContactControler(QObject *parent):QObject(parent)
{
   QObject::connect(this,SIGNAL(svrListChanged(int,ContactList )),
                    this,SLOT(onContactListChanged(int,ContactList)));
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
    ContactList contacts;

    emit svrListChanged(operType,contacts);
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

void ContactControler::onContactListChanged(int oper, ContactList contactList)
{
    qDebug() << Q_FUNC_INFO << "contact size:"<< contactList.size();
    emit contactListChanged(oper,contactList);
}


