#include "cdoodenterprisemanager.h"

#include <QMetaType>
#include <QDebug>

CDoodEnterpriseManager::CDoodEnterpriseManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodEnterpriseManager*>();
    initConnect();
    CDoodContactItem *item1 = new CDoodContactItem(this);
    item1->setId("2");
    item1->setName("vrvbj");
    item1->setIsOrg(true);
    addItem(item1);
    CDoodContactItem *item2 = new CDoodContactItem(this);
    item2->setId("3");
    item2->setName("vrvxa");
    item2->setIsOrg(true);
    addItem(item2);
}
CDoodEnterpriseManager::~CDoodEnterpriseManager()
{

}

void CDoodEnterpriseManager::getSonOrgs(QString orgid)
{
    qDebug() << Q_FUNC_INFO << "wawawawawawawaw";
    reset();
    if(orgid == "1") {
        CDoodContactItem *item1 = new CDoodContactItem(this);
        item1->setId("2");
        item1->setName("vrvbj");
        item1->setIsOrg(true);
        addItem(item1);
        CDoodContactItem *item2 = new CDoodContactItem(this);
        item2->setId("3");
        item2->setName("vrvxa");
        item2->setIsOrg(true);
        addItem(item2);
    } else if(orgid == "2" || orgid == "3") {
        CDoodContactItem *item1 = new CDoodContactItem(this);
        item1->setId("4");
        item1->setName("developer");
        item1->setIsOrg(true);
        addItem(item1);
        CDoodContactItem *item2 = new CDoodContactItem(this);
        item2->setId("5");
        item2->setName("marketing");
        item2->setIsOrg(true);
        addItem(item2);
    }
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


void CDoodEnterpriseManager::onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist)
{
     qDebug() << Q_FUNC_INFO <<"hahahahahaahhha" << orglist[0].name;


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

void CDoodEnterpriseManager::initConnect()
{
    connect(m_pClient, SIGNAL(getSonOrgsResult(int,OrgList,OrgUserList)), this, SLOT(onGetSonOrgsResult(int, OrgList,OrgUserList)));
    connect(m_pClient, SIGNAL(getOnlineStatesResult(QOnlineStateList)), this, SLOT(onGetOnlineStatesResult(QOnlineStateList)));
    connect(m_pClient, SIGNAL(getOrgUserInfoResult(int,OrgUser)), this, SLOT(onGetorgUserInfoResult(int,OrgUser)));
}
