#include "IMClient.h"
#include "IEnterpriseService.h"
#include <enterprisecontroler.h>
#include<iostream>
#include<sstream>
#include<string>


EnterpriseControler::EnterpriseControler(QObject *parent):QObject(parent)
{
}

EnterpriseControler::~EnterpriseControler()
{
}




void EnterpriseControler::getSonOrgs(QString orgid)
{
    int64 org_id;
    std::stringstream str(orgid.toStdString());
    str >> org_id;
    service::IMClient::getClient()->getEnterprise()->getSonOrgs(org_id,
        std::bind(&EnterpriseControler::_getSonOrgs,this,std::placeholders::_1,
        std::placeholders::_2,std::placeholders::_3));
}
void EnterpriseControler::_getSonOrgs(service::ErrorInfo &info, std::vector<service::Org> orgs, std::vector<service::OrgUser> orgusers)
{
    qDebug() << Q_FUNC_INFO;
    OrgList orgList;
    OrgUserList orgUserList;
    for(auto org:orgs){
        orgList.insert(orgList.size(),orgToQorg(org));
    }
    for(auto orgUser:orgusers){
        orgUserList.insert(orgUserList.size(),orguserToQorguser(orgUser));
    }
    emit getSonOrgsResult(info.code(),orgList,orgUserList);
}



void EnterpriseControler::getOnlineStates(QStringList &userid)
{
    std::vector<int64> Ids;
    for(auto i :userid)
    {
        int64  id;
        std::stringstream str(i.toStdString());
        str>>id;
        Ids.push_back(id);
    }
    service::IMClient::getClient()->getEnterprise()->getOnlineStates(Ids,
        std::bind(&EnterpriseControler::_getOnlineStates,this,
        std::placeholders::_1));
}
void EnterpriseControler::_getOnlineStates(std::vector<OnlineState> &states)
{
    qDebug() << Q_FUNC_INFO;
    QOnlineStateList onlinestatelist;
    for(auto i:states){
        QOnlineState  onlinestate;
        onlinestate.userid=QString::number(i.userID);
        onlinestate.connectId=QString::number(i.connectID);
        onlinestate.deviceType=QString::number(i.deviceType);
        onlinestate.flag=QString::number(i.flag);
        onlinestatelist.insert(onlinestatelist.size(),onlinestate);
    }
    emit getOnlineStatesResult(onlinestatelist);
}




void EnterpriseControler::getOrgUserInfo(QString userid)
{
    int64 id;
    std::stringstream str(userid.toStdString());
    str >>id;
    service::IMClient::getClient()->getEnterprise()->getOrgUserInfo(id,
       std::bind(&EnterpriseControler::_getOrgUserInfo,this,
       std::placeholders::_1,std::placeholders::_2));
}
void EnterpriseControler::_getOrgUserInfo(service::ErrorInfo &info, service::OrgUser &orguser)
{
    qDebug() << Q_FUNC_INFO;
    OrgUser Qorguser;
    Qorguser= orguserToQorguser(orguser);
    emit getOrgUserInfoResult(info.code(),Qorguser);
}




Org EnterpriseControler::orgToQorg(service::Org org)
{
    Org Qorg;
    Qorg.avatar       =QString::fromStdString(org.avatar);
    Qorg.thumbAvatar  =QString::fromStdString(org.thumb_avatar);
    Qorg.extends      =QString::fromStdString(org.extends);
    Qorg.org_code     =QString::fromStdString(org.org_code);
    Qorg.name         =QString::fromStdString(org.name);
    Qorg.branch_id    =QString::number(org.id);
    Qorg.ent_id       =QString::number(org.ent_id);
    Qorg.ishidden     =QString::number(org.ishidden);
    Qorg.leaf         =QString::number(org.leaf);
    Qorg.level        =QString::number(org.level);
    Qorg.order_num    =QString::number(org.order_num);
    Qorg.id           =QString::number(org.id);
    Qorg.parent_id    =QString::number(org.parent_id);
    Qorg.sonorg_count =QString::number(org.sonorg_count);
    Qorg.sonuser_count=QString::number(org.sonuser_count);
    return Qorg;
}

OrgUser EnterpriseControler::orguserToQorguser(service::OrgUser orguser)
{
    OrgUser Qorguser;
    Qorguser.ent_id       =QString::number(orguser.ent_id);
    Qorguser.order_num    =QString::number(orguser.order_num);
    Qorguser.org_id       =QString::number(orguser.org_id);
    Qorguser.role_id      =QString::number(orguser.role_id);
    Qorguser.neworg_id    =QString::number(orguser.org_id);
    Qorguser.id           =QString::number(orguser.id);
    Qorguser.gender       =QString::number(orguser.gender);
    Qorguser.timeZone     =QString::number(orguser.time_zone);
    Qorguser.avatar       =QString::fromStdString(orguser.avatar);
    Qorguser.thumbAvatar  =QString::fromStdString(orguser.thumb_avatar);
    Qorguser.name         =QString::fromStdString(orguser.name);
    Qorguser.extends      =QString::fromStdString(orguser.extends);
    Qorguser.duty         =QString::fromStdString(orguser.duty);
    Qorguser.email        =QString::fromStdString(orguser.email);
    Qorguser.phone        =QString::fromStdString(orguser.phone);
    Qorguser.orgname      =QString::fromStdString(orguser.orgname);
    Qorguser.pinyin       =QString::fromStdString(orguser.pinyin);
    return Qorguser;
}
