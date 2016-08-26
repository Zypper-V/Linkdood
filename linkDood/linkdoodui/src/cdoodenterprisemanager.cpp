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

QString CDoodEnterpriseManager::tip() const
{
    return mTip;
}

QString CDoodEnterpriseManager::setTip(const QString &data)
{
    if(mTip==data){
        return data;
    }
    mTip=data;
    emit tipChanged();
    return mTip;
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
        enterListMap.clear();
        setIsOrg(false);
        setTip("正在同步服务器数据,请稍等...");
        m_pClient->getSonOrgs("0");
    }
}

void CDoodEnterpriseManager::getSonOrgs(QString orgid)
{
    qDebug() << Q_FUNC_INFO<<orgid;
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

void CDoodEnterpriseManager::selectMember(QString id)
{
    qDebug() << Q_FUNC_INFO<<"ssssssssssssss:"<<id;
    CDoodEnterPriseItem *tmpItem = enterListMap.value(id);
    if(tmpItem!=NULL){
        if(tmpItem->isChoose()==""){
            m_member.push_back(id);
            qDebug() << Q_FUNC_INFO<<"ssss1";
            tmpItem->setIsChoose("123");
//            enterListMap[id]->setIsChoose("123");
        }
        else{
            qDebug() << Q_FUNC_INFO<<"ssss2";
            tmpItem->setIsChoose("");
//            enterListMap[id]->setIsChoose("");
        }
    }

}

void CDoodEnterpriseManager::clearMember()
{
    for(size_t i=0;i<m_member.size();++i){
        CDoodEnterPriseItem *tmpItem = enterListMap.value(m_member[i]);
        tmpItem->setIsChoose("");
    }
    m_member.clear();
}

void CDoodEnterpriseManager::changeMember(MemberList memberList)
{
    m_memberList=memberList;
}


void CDoodEnterpriseManager::onGetSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist)
{
    qDebug() << Q_FUNC_INFO <<"hahahahahaahhha" << orglist.size()<<code;
//    if(code<0){
//       setIsOrg(false);
//       setTip("正在同步服务器数据,请稍后再试...");
//       return;
//    }
    if(code==0){
        qDebug() << Q_FUNC_INFO <<"11";
        reset();
        if(isFarOrg==1){
            qDebug() << Q_FUNC_INFO <<"22";
            if(orglist.size()!=0){
                qDebug() << Q_FUNC_INFO <<"33";
                isFarOrg=0;
                setIsOrg(true);
                emit farOrgResult(orglist[0].id,orglist[0].name);
                return;
            }
            else{
                setIsOrg(false);
                setTip("正在同步服务器数据,请稍后再试...");
                //setTip("暂未加入任何组织");
                return;
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
                for(int j=0;j<m_memberList.size();++j){
                    if(m_memberList[j].id==orguserlist[i].id){
                        item->setIsChoose("123");
                    }
                }
//                CDoodEnterPriseItem *item1 = enterListMap.value(orguserlist[i].id,NULL);
//                if(item1 != NULL){
//                    item->setIsChoose(enterListMap[orguserlist[i].id]->isChoose());
//                }
//                else{
//                    enterListMap[orguserlist[i].id] = item;
//                }
                enterListMap[orguserlist[i].id] = item;
                addItem(item);
            }
            for(size_t i=0;i<orglist.size();++i){
                CDoodEnterPriseItem *item = new CDoodEnterPriseItem(this);
                item->setId(orglist[i].id);
                item->setName(orglist[i].name);
                item->setThumbAvatar("qrc:/res/collectivel_icon.png");
                addItem(item);
            }
            emit getSonOrgsResult(code,orglist,orguserlist);
        }
    }
}

void CDoodEnterpriseManager::onGetOnlineStatesResult(QOnlineStateList onlinestatelist)
{
    qDebug() << Q_FUNC_INFO;
    emit getOnlineStatesResult(onlinestatelist);
}

void CDoodEnterpriseManager::onGetOrgUserInfoResult(int code,OrgUser orguser)
{
    qDebug() << Q_FUNC_INFO<<orguser.thumbAvatar;
    if(code==0){
        emit getOrgUserInfoResult(orguser.thumbAvatar);
    }
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
    connect(m_pClient, SIGNAL(getOrgUserInfoResult(int,OrgUser)),this,SLOT(onGetOrgUserInfoResult(int,OrgUser)));
    connect(m_pClient, SIGNAL(text()),this,SLOT(onText()));
}

int CDoodEnterpriseManager::indexOfSection(QString section)
{

}
