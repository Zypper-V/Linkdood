#ifndef CDOODENTERPRISEMANAGER_H
#define CDOODENTERPRISEMANAGER_H


#include <QObject>
#include <QtQuick/QQuickView>
#include "linkdoodclient.h"
#include "cdoodlistmodel.h"
#include "cdoodorgitem.h"
class CDoodEnterpriseManager: public CDoodListModel
{
    Q_OBJECT

public:
    explicit CDoodEnterpriseManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodEnterpriseManager();
    Q_INVOKABLE void getSonOrgs(QString orgid);
    Q_INVOKABLE void getOnlineStates(QStringList& userid);
    Q_INVOKABLE void getOrgUserInfo(QString userid);

signals:
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(int code,OrgUser& orguser);
private slots:
    void onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser& orguser);
private:
    void initConnect();
    QMap<QString, CDoodOrgItem*> orgListMap;
    LinkDoodClient *m_pClient;
};
#endif // CDOODENTERPRISEMANAGER_H
