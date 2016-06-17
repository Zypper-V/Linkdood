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
    qDebug() << Q_FUNC_INFO << "oper:" << operType << "contactSize:" << users.size();
    ContactList contacts;
    for(auto i: users){
       Contact user;
       user.avatar = QString::fromStdString(i.avatar);
       user .name  = QString::fromStdString(i.name);
       user .extends  = QString::fromStdString(i.extends);
       user .id  = QString::number(i.id);
       user .isStar  = i.isStar;
       user .isVip  = i.isVip;
       user .pinyin  = QString::fromStdString(i.pinyin);
       user .remark  = QString::fromStdString(i.remark);
       user .server  = QString::fromStdString(i.server);
       user .thumbAvatar  = QString::fromStdString(i.thumb_avatar);
       user .timeZone  = i.time_zone;

      if(i.gender == 0){
        user.gender = QObject::tr("保密");
      }else if(i.gender == 1){
        user.gender = QObject::tr("男");
      }else if(i.gender == 2){
        user.gender = QObject::tr("女");
      }

       contacts.push_back(user);
    }
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


