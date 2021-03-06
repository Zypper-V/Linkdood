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
    Q_PROPERTY(QString tip READ tip WRITE setTip NOTIFY tipChanged)


public:
    explicit CDoodEnterpriseManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodEnterpriseManager();
    bool isOrg() const;
    Q_INVOKABLE bool setIsOrg(const bool &data);

    QString tip() const;
    Q_INVOKABLE QString setTip(const QString &data);

    Q_INVOKABLE void setFarOrg();
    Q_INVOKABLE void getFarOrgs();
    Q_INVOKABLE void getSonOrgs(QString orgid);
    Q_INVOKABLE void getOnlineStates(QStringList& userid);
    Q_INVOKABLE void getOrgUserInfo(QString userid);
    Q_INVOKABLE void selectMember(QString id);
    Q_INVOKABLE void clearMember();
    Q_INVOKABLE void changeMember(MemberList memberList);

signals:
    void isOrgChanged();
    void tipChanged();
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void farOrgResult(QString id,QString name);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(QString thumbAvatar);
private slots:
    void onGetSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetOrgUserInfoResult(int code,OrgUser orguser);
    void onText();
private:
    bool mIsOrg;
    QString mTip;
    void initConnect();
    int  indexOfSection(QString section);
    QMap<QString, CDoodEnterPriseItem*> enterListMap;
    std::vector<QString> m_member;
    MemberList m_memberList;
    LinkDoodClient *m_pClient;
    int isFarOrg;
};
#endif // CDOODENTERPRISEMANAGER_H
