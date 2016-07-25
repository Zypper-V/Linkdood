#ifndef CDOODENTERPRISEMANAGER_H
#define CDOODENTERPRISEMANAGER_H


#include <QObject>
#include <QtQuick/QQuickView>
#include "linkdoodclient.h"
#include "cdoodlistmodel.h"
#include "cdoodenterpriseitem.h"
class CDoodEnterpriseManager: public CDoodListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isOrg READ isOrg WRITE setIsOrg NOTIFY isOrgChanged)

public:
    explicit CDoodEnterpriseManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodEnterpriseManager();
    bool isOrg() const;
    Q_INVOKABLE bool setIsOrg(const bool &data);

    Q_INVOKABLE void setFarOrg();
    Q_INVOKABLE void getFarOrgs();
    Q_INVOKABLE void getSonOrgs(QString orgid);
    Q_INVOKABLE void getOnlineStates(QStringList& userid);
    Q_INVOKABLE void getOrgUserInfo(QString userid);

signals:
    void isOrgChanged();
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void getFarOrgResult(QString id,QString name);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(int code,OrgUser& orguser);
private slots:
    void onGetSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser& orguser);
    void onText();
private:
    bool mIsOrg;
    void initConnect();
    QMap<QString, CDoodEnterPriseItem*> enterListMap;
    LinkDoodClient *m_pClient;
    int isFarOrg;
};
#endif // CDOODENTERPRISEMANAGER_H
