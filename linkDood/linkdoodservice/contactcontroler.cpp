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
#include "ISearchService.h"
#include "linkdoodservice.h"

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

void ContactControler::getContactInfo(QString userid)
{
    service::IMClient::getClient()->getContact()->getContactInfo(userid.toLongLong(),std::bind(&ContactControler::_getContactInfo,this,std::placeholders::_1,std::placeholders::_2));
}

void ContactControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setContactObserver(this);
}

void ContactControler::onListChanged(int operType, std::vector<service::Contact> &users)
{

    ContactList contacts;
    for(auto i: users){
        Contact user;
        qDebug()<< Q_FUNC_INFO<<"name:"<<i.name.c_str()<<"team:"<<i.team<<"pingyin:"<<QString::fromStdString(i.pinyin);
        user.avatar = QString::fromStdString(i.avatar);

        user.name  = QString::fromStdString(i.name);
        user.extends  = QString::fromStdString(i.extends);
        user.id  = QString::number(i.id);
        user.isStar  = i.isStar;
        user.isVip  = i.isVip;
        user.pinyin  = QString::fromStdString(i.pinyin);
        user.remark  = QString::fromStdString(i.remark);
        if(user.remark !=""){
            user.name  = QString::fromStdString(i.name);
        }
        user.server  = QString::fromStdString(i.server);
        user.thumbAvatar  = QString::fromStdString(i.thumb_avatar);
        user.timeZone  = i.time_zone;
        user.gender = genderConvert(i.gender);
        user.team   = i.team;
        if(!IS_MSG_APP(i.id))
        {
            contacts.push_back(user);
        }
    }
    emit contactListChanged(operType,sort(contacts));

    std::vector<int64> list;
    for(int i =0;i<contacts.size();++i){
        list.push_back(contacts.at(i).id.toLongLong());
    }
    service::IMClient::getClient()->getContact()->getContactOnline(list,std::bind(&ContactControler::_getContactOnline,this,std::placeholders::_1));
}

void ContactControler::onAvatarChanged(int64 userid, std::string avatar)
{    
    if(avatar.size() == 0)
        return;
    qDebug() << Q_FUNC_INFO<<userid;
    emit chatAvatarChanged(QString::number(userid), QString::fromStdString(avatar));
}


void ContactControler::onContactInfoChanged(int operType, service::User &users)
{
    service::Contact& contact = dynamic_cast<service::Contact&>(users);
    qDebug() << Q_FUNC_INFO << "team:" << contact.team<< "name:"<< contact.name.c_str() << "isStar:"<<contact.isStar;
    Contact user;

    user.id = QString::number(contact.id);
    user.name = QString::fromStdString(contact.name);
    if(contact.__isset.isStar){
        user.isStar = contact.isStar;
    }

    if(contact.__isset.isVip){
        user.isVip = contact.isVip;
    }
    if(contact.__isset.remark && contact.remark !=""){
        user.remark  = QString::fromStdString(contact.remark);
        user.name  = user.remark;
    }
    if(contact.__isset.pinyin){
        user.pinyin  = QString::fromStdString(contact.pinyin);
    }

    if(contact.__isset.server){
        user.server  = QString::fromStdString(contact.server);
    }

    if(contact.__isset.team){
        user.team  = contact.team;
    }
    if(contact._user_isset.extends){
        user.extends = QString::fromStdString(contact.extends);
    }
    if(contact._user_isset.gender){
        user.gender = genderConvert(contact.gender);
    }
    if(contact._user_isset.thumb_avatar){
        user.thumbAvatar  = QString::fromStdString(contact.thumb_avatar);
    }
    if(contact._user_isset.time_zone){
        user.timeZone     = contact.time_zone;
    }
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
    emit contactOnlineChanged(QString::number(status.userID), device,status.flag);
}

void ContactControler::searchFromNet(QString &key)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getSearch()->searchFromNet(key.toStdString(),std::bind(&ContactControler::_searchFromNet,this,std::placeholders::_1,std::placeholders::_2));
}

void ContactControler::searchFromLocal(QString &key)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getSearch()->searchFromLocal(key.toStdString(),std::bind(&ContactControler::_searchFromLocal,this,std::placeholders::_1,std::placeholders::_2));
}

void ContactControler::addContact(QString userid, QString remark, QString info)
{
    qDebug() << Q_FUNC_INFO << "uuuuuuuuuuuuuuuuuuuuuususerid:" << userid;
    service::IMClient::getClient()->getContact()->addContact(userid.toLongLong(), remark.toStdString(), info.toStdString(), std::bind(&ContactControler::_addContact,this,std::placeholders::_1));
}

void ContactControler::removeContact(QString userid)
{
    qDebug() << Q_FUNC_INFO<<userid;
    service::IMClient::getClient()->getContact()->removeContact(userid.toLongLong(), std::bind(&ContactControler::_removeContact, this, std::placeholders::_1));
}

void ContactControler::getVerifyType(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getContact()->getVerifyType(userid.toLongLong(), std::bind(&ContactControler::_getVerifyType, this, std::placeholders::_1, std::placeholders::_2));
}

ContactList ContactControler::sort(const ContactList &contactList)
{
    ContactList list;
    ContactList unTeamList;

    for(auto item:contactList){
        if(item.team == 35){
            unTeamList.insert(list.size(),item);
        }else{
            list.insert(list.size(),item);
        }
    }
    qSort(list.begin(),list.end(),CmpByTeam);
    for(auto item:unTeamList){
        list.push_back(item);
    }
    return list;
}

void ContactControler::_updateContactInfo(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO << "44444444444444444444444444444";
    emit updateContactInfoBack(info.code());
}

void ContactControler::_searchFromNet(service::ErrorInfo& info, SearchResult& res)
{
    qDebug() << Q_FUNC_INFO;
    ContactList user;
    ContactList group;
    Contact contact;
    for(int i = 0; i < res.users.size(); i++)
    {
        contact.id = QString::number(res.users[i].id);
        if(LinkDoodService::instance()->UserId() == contact.id)
        {
            continue;    //搜索到自己不在界面显示
        }
//        if(IS_MSG_APP(res.users[i].id)){
//             continue;
//        }
        contact.gender = QString::number(res.users[i].gender);
        qDebug() << Q_FUNC_INFO << "LinkDoodService::instance()->UserId():" << LinkDoodService::instance()->UserId() << "userid:" << contact.id << "   gender:" << contact.gender;
        contact.timeZone = res.users[i].time_zone;
        contact.name = QString::fromStdString(res.users[i].name);
        contact.avatar = QString::fromStdString(res.users[i].avatar);
        contact.extends = QString::fromStdString(res.users[i].extends);
        contact.thumbAvatar = QString::fromStdString(res.users[i].thumb_avatar);
        user.push_back(contact);
    }
    for(int i = 0; i < res.groups.size(); i++)
    {
        contact.gender = QString::number(res.groups[i].gender);
        contact.timeZone = res.groups[i].time_zone;
        contact.id = QString::number(res.groups[i].id);
        contact.name = QString::fromStdString(res.groups[i].name);
        contact.avatar = QString::fromStdString(res.groups[i].avatar);
        contact.extends = QString::fromStdString(res.groups[i].extends);
        contact.thumbAvatar = QString::fromStdString(res.groups[i].thumb_avatar);
        group.push_back(contact);
    }
    emit searchFromNetBack(info.code(), user, group);
}

void ContactControler::_searchFromLocal(service::ErrorInfo& info, SearchResult& res)
{
    qDebug() << Q_FUNC_INFO;
    ContactList user;
    ContactList group;
    Contact contact;
    for(int i = 0; i < res.users.size(); i++)
    {
        if(IS_MSG_APP(res.users[i].id)){
             continue;
        }
        contact.gender = QString::number(res.users[i].gender);
        contact.timeZone = res.users[i].time_zone;
        contact.id = QString::number(res.users[i].id);
        contact.name = QString::fromStdString(res.users[i].name);
        contact.avatar = QString::fromStdString(res.users[i].avatar);
        contact.extends = QString::fromStdString(res.users[i].extends);
        contact.thumbAvatar = QString::fromStdString(res.users[i].thumb_avatar);
        user.push_back(contact);
    }
    for(int i=0;i<res.orgusers.size();i++){
        qDebug()<<Q_FUNC_INFO<<"ssssssss";
        contact.id = QString::number(res.orgusers[i]->id);
        contact.name=QString::fromStdString(res.orgusers[i]->name);
        contact.gender = QString::number(res.orgusers[i]->gender);
        contact.timeZone = res.orgusers[i]->time_zone;
        contact.avatar = QString::fromStdString(res.orgusers[i]->avatar);
        contact.thumbAvatar = QString::fromStdString(res.orgusers[i]->thumb_avatar);
        contact.pinyin="组织成员";
        qDebug()<<Q_FUNC_INFO<<"ssssssss:"<<contact.id<<contact.name;
        user.push_back(contact);
    }
    for(int i = 0; i < res.groups.size(); i++)
    {
        contact.gender = QString::number(res.groups[i].gender);
        contact.timeZone = res.groups[i].time_zone;
        contact.id = QString::number(res.groups[i].id);
        contact.name = QString::fromStdString(res.groups[i].name);
        contact.avatar = QString::fromStdString(res.groups[i].avatar);
        contact.extends = QString::fromStdString(res.groups[i].extends);
        contact.thumbAvatar = QString::fromStdString(res.groups[i].thumb_avatar);
        group.push_back(contact);
    }
    emit searchFromLocalBack(info.code(), user, group);
}

void ContactControler::_addContact(service::ErrorInfo info)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<info.code();
    emit addContactBack(info.code());
}

void ContactControler::_removeContact(service::ErrorInfo info)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<info.code();
    emit removeContactBack(info.code());
}

void ContactControler::_getVerifyType(service::ErrorInfo info, ContactVerifyType verify)
{
    qDebug()<<Q_FUNC_INFO<<"code:"<<info.code() << "verify.userid:" << verify.userid <<"  verify.type:" << verify.type;
    emit getVerifyTypeBack(info.code(), QString::number(verify.userid), verify.type);
}

void ContactControler::_getContactInfo(service::ErrorInfo &info, service::User &user)
{
    qDebug()<<Q_FUNC_INFO;
    service::Contact& contact = dynamic_cast<service::Contact&>(user);
    Contact item;
    item.name = QString::fromStdString(contact.name);
    item.remark = QString::fromStdString(contact.remark);
    item.id   = QString::number(user.id);

    emit getContactInfo(item);
}

void ContactControler::_getContactOnline(std::vector<OnlineState> &statusList)
{
    qDebug()<<Q_FUNC_INFO;
    for(int i =0;i<statusList.size();++i){
        QString device("");
        OnlineState status = statusList.at(i);
        if(status.flag == 1)
        {
            if(status.deviceType == 1)
                device = "[电脑]";
            else if(status.deviceType == 2)
                device = "[手机]";
        }
        emit contactOnlineChanged(QString::number(status.userID), device,status.flag);
    }
}

bool CmpByTeam(const Contact first, const Contact second)
{
    if(first.team == 35){
        return false;
    }
    return  first.team <= second.team;
}



