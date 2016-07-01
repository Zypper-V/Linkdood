#include<contactcontroler.h>
#include<iostream>
#include<QDebug>
#include <QMetaType>
#include <QtAlgorithms>
#include "IMClient.h"
#include "IContactService.h"
#include "INotifyService.h"
#include "Contact.h"
#include "IDRangeJuge.hpp"

ContactControler::ContactControler(QObject *parent):QObject(parent)
{
}

ContactControler::~ContactControler()
{

}

void ContactControler::getContactList()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getContact()->getContactList();
}

void ContactControler::updateContactInfo(QString userId, QString operStar, QString remark)
{
    qDebug() << Q_FUNC_INFO;
    service::Contact user;

    user.__set_id(userId.toLongLong());
    if(operStar != ""){
        user.__set_isStar(operStar.toInt());
    }
    if(remark != ""){
        user.__set_remark(remark.toStdString());
    }
    service::IMClient::getClient()->getContact()->updateContactInfo(user,
                      std::bind(&ContactControler::_updateContactInfo,this,std::placeholders::_1));
}

void ContactControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setContactObserver(this);
}

void ContactControler::onListChanged(int operType, std::vector<service::Contact> &users)
{
    qDebug() << Q_FUNC_INFO << "oper:" << operType << "222222222222222contactSize:" << users.size();
    ContactList contacts;
    for(auto i: users){
       Contact user;

       user.avatar = QString::fromStdString(i.avatar);
       user.name  = QString::fromStdString(i.name);
       user.extends  = QString::fromStdString(i.extends);
       user.id  = QString::number(i.id);
       user.isStar  = i.isStar;
       user.isVip  = i.isVip;
       user.pinyin  = QString::fromStdString(i.pinyin);
       user.remark  = QString::fromStdString(i.remark);
       user.server  = QString::fromStdString(i.server);
       user.thumbAvatar  = QString::fromStdString(i.thumb_avatar);
       user.timeZone  = i.time_zone;
       user.gender = genderConvert(i.gender);
      if(!IS_MSG_APP(i.id))
      {
         contacts.push_back(user);
      }
    }
    emit contactListChanged(operType,contacts);
}

void ContactControler::onAvatarChanged(int64 userid, std::string avatar)
{
    qDebug() << Q_FUNC_INFO;
}

void ContactControler::onContactInfoChanged(int operType, service::User &users)
{
    service::Contact& contact = dynamic_cast<service::Contact&>(users);
    qDebug() << Q_FUNC_INFO << "operType:" << operType<< "name:"<< contact.name.c_str() << "isStar:"<<contact.isStar;
    Contact user;

    user.isStar = contact.isStar;
    user.extends = QString::fromStdString(contact.extends);
    user.gender = genderConvert(contact.gender);
    user.id = QString::number(contact.id);
    user.isVip = contact.isVip;
    user.name  = QString::fromStdString(contact.name);
    user.pinyin  = QString::fromStdString(contact.pinyin);
    user.remark  = QString::fromStdString(contact.remark);
    user.server  = QString::fromStdString(contact.server);
    user.thumbAvatar  = QString::fromStdString(contact.thumb_avatar);
    user.timeZone     = contact.time_zone;

    qDebug() << Q_FUNC_INFO << "end ssssssssssssssssssssssoperType:" << operType<< "name:"<< contact.name.c_str() << "isStar:"<<contact.isStar;
    emit contactInfoChanged(operType,user);
}

void ContactControler::onOnlineChanged(OnlineState &status)
{
    qDebug() << Q_FUNC_INFO<< "5555555555555555555555555555555";
    QString device("");

    if(status.flag == 1)
    {
        if(status.deviceType == 1)
            device = "[电脑]";
        else if(status.deviceType == 2)
            device = "[手机]";
    }
    emit contactOnlineChanged(QString::number(status.userID), device);
}

ContactList ContactControler::sort(const ContactList &contactList)
{
    //
    ContactList starList;
    ContactList otherList;
    ContactList list;

    for(auto item:contactList){
        if(item.isStar == 1){
            starList.insert(starList.size(),item);
        }else{
            otherList.insert(otherList.size(),item);
        }
    }

    qSort(starList.begin(),starList.end(),CmpByTeam);
    qSort(otherList.begin(),otherList.end(),CmpByTeam);

    for(auto item:starList){
        list.insert(list.size(),item);
    }

    for(auto item:otherList){
        list.insert(list.size(),item);
    }
    return list;
}

void ContactControler::_updateContactInfo(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO << "44444444444444444444444444444";
}

bool CmpByTeam(const Contact first, const Contact second)
{
    return  first.pinyin.at(0).toUpper() <= second.pinyin.at(0).toUpper();
}



