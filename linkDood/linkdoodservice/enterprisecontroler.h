#ifndef ENTERPRISECONTROLER_H
#define ENTERPRISECONTROLER_H

#endif // ENTERPRISECONTROLER_H
#include<QObject>
#include<IEnterpriseService.h>
#include<IEnterpriseObserver.h>
#include "INotifyService.h"
#include "linkdoodtypes.h"
class EnterpriseControler:public QObject,public IEnterpriseObserver
{
    Q_OBJECT
public:
    void init();
    EnterpriseControler(QObject *parent = 0);
    ~EnterpriseControler();
    void onUpdateRootFinished();
    //调用底层接口并通过回调获取结果
    void getSonOrgs(QString orgid);
    void _getSonOrgs(service::ErrorInfo info, std::vector<service::Org> orgs, std::vector<service::OrgUser> orgusers);

    void getOnlineStates(QStringList& userid);
    void _getOnlineStates(std::vector<OnlineState>& states);

    void getOrgUserInfo(QString userid);
    void _getOrgUserInfo(service::ErrorInfo& info, service::OrgUser& orguser);

//signals:
//    //
//    void getSonOrgsResultIn(service::ErrorInfo &info, std::vector<service::Org> orgs, std::vector<service::OrgUser> orgusers);
//    void getOnlineStatesResultIn(std::vector<OnlineState>& states);
//    void getOrgUserInfoResultIn(ErrorInfo& info, OrgUser& orguser);

//protected slots:
//    //
//    void onGetSonOrgsResultIn(service::ErrorInfo &info, std::vector<service::Org> orgs, std::vector<service::OrgUser> orgusers);
//    void onGetOnlineStatesResultIn(std::vector<OnlineState>& states);
//    void onGetOrgUserInfoResultIn(ErrorInfo& info, OrgUser& orguser);
signals:
    //将结果抛给linkdoodservice层
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(int code,OrgUser orguser);

//private:
//    void initConnects();
public:
    Org orgToQorg(service::Org org);
    OrgUser orguserToQorguser(service::OrgUser orguser);

};
