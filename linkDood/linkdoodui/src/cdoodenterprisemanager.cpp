#include "cdoodenterprisemanager.h"

#include <QMetaType>
#include <QDebug>

CDoodEnterpriseManager::CDoodEnterpriseManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << Q_FUNC_INFO<<"haohaohaohaohaohaohaoa";
    qRegisterMetaType<CDoodEnterpriseManager*>();
    initConnect();
    isFarOrg=1;
}
CDoodEnterpriseManager::~CDoodEnterpriseManager()
{

}

bool CDoodEnterpriseManager::isOrg() const
{
    return mIsOrg;
}

bool CDoodEnterpriseManager::setIsOrg(const bool &data)
{
    if(mIsOrg==data){
        return data;
    }
    mIsOrg=data;
    emit isOrgChanged();
    return mIsOrg;
}

void CDoodEnterpriseManager::setFarOrg()
{
    qDebug() << Q_FUNC_INFO;
    reset();
    setIsOrg(false);
    isFarOrg=1;
}

void CDoodEnterpriseManager::getFarOrgs()
{
    qDebug() << Q_FUNC_INFO;
    if(isFarOrg==1){
        reset();
        m_pClient->getSonOrgs("0");
    }
}

void CDoodEnterpriseManager::getSonOrgs(QString orgid)
{
    m_pClient->getSonOrgs(orgid);
}
void CDoodEnterpriseManager::getOnlineStates(QStringList& userid)
{
    qDebug() << Q_FUNC_INFO << userid;
    m_pClient->getOnlineStates(userid);
}
void CDoodEnterpriseManager::getOrgUserInfo(QString userid)
{
    qDebug() << Q_FUNC_INFO << userid;
    m_pClient->getOrgUserInfo(userid);
}


void CDoodEnterpriseManager::onGetSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist)
{
    qDebug() << Q_FUNC_INFO <<"hahahahahaahhha" << orglist.size();
    if(code==0){
        reset();
        if(isFarOrg==1){
            if(orglist.size()!=0){
                isFarOrg=0;
                setIsOrg(true);
                emit getFarOrgResult(orglist[0].id,orglist[0].name);
            }
            else{
                setIsOrg(false);
            }
        }
        else{
            for(size_t i=0;i<orguserlist.size();++i){
                CDoodEnterPriseItem *item = new CDoodEnterPriseItem(this);
                item->setId(orguserlist[i].id);
                item->setName(orguserlist[i].name);
                item->setGender(orguserlist[i].gender);
                item->setOrder_num(orguserlist[i].order_num);
                item->setThumbAvatar("qrc:/res/moren_icon.png");
                addItem(item);
            }
            for(size_t i=0;i<orglist.size();++i){
                CDoodEnterPriseItem *item = new CDoodEnterPriseItem(this);
                item->setId(orglist[i].id);
                item->setName(orglist[i].name);
                item->setThumbAvatar("qrc:/res/collectivel_icon.png");
                addItem(item);
            }
        }
    }
    emit getSonOrgsResult(code,orglist,orguserlist);
}

void CDoodEnterpriseManager::onGetOnlineStatesResult(QOnlineStateList onlinestatelist)
{
    qDebug() << Q_FUNC_INFO;
    emit getOnlineStatesResult(onlinestatelist);
}

void CDoodEnterpriseManager::onGetorgUserInfoResult(int code,OrgUser& orguser)
{
    qDebug() << Q_FUNC_INFO;
    emit getOrgUserInfoResult(code,orguser);
}

void CDoodEnterpriseManager::onText()
{
    qDebug() << Q_FUNC_INFO;
}

void CDoodEnterpriseManager::initConnect()
{
    qDebug() << Q_FUNC_INFO<<"haohaohaohaohaohaohaoaho111";
    connect(m_pClient, SIGNAL(getSonOrgsResult(int,OrgList,OrgUserList)),this,SLOT(onGetSonOrgsResult(int,OrgList,OrgUserList)));
    connect(m_pClient, SIGNAL(getOnlineStatesResult(QOnlineStateList)),this,SLOT(onGetOnlineStatesResult(QOnlineStateList)));
    connect(m_pClient, SIGNAL(getOrgUserInfoResult(int,OrgUser)),this,SLOT(onGetorgUserInfoResult(int,OrgUser)));
    connect(m_pClient, SIGNAL(text()),this,SLOT(onText()));
}

int CDoodEnterpriseManager::indexOfSection(QString section)
{

}
