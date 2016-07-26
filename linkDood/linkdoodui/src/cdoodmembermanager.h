#ifndef CDOODMEMBERMANAGER_H
#define CDOODMEMBERMANAGER_H


#include <QObject>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodMemberItem;
class CDoodMemberManager : public CDoodListModel
{

    Q_OBJECT
    Q_PROPERTY(QString isTip READ isTip WRITE setIsTip NOTIFY isTipChanged)
    Q_PROPERTY(QString my_Type READ my_Type WRITE setMy_Type NOTIFY my_TypeChanged)

public:
    explicit CDoodMemberManager(LinkDoodClient *client = 0, QObject *parent = 0);
    Q_INVOKABLE void clearMemberList();

    ~CDoodMemberManager();
    QString getMyId();

    QString isTip()const;
    Q_INVOKABLE QString   setIsTip(const QString data);

    QString my_Type()const;
    Q_INVOKABLE QString   setMy_Type(const QString data);

    Q_INVOKABLE bool isMyself(QString id);
    Q_INVOKABLE void judgeTip(QString hisType);
    Q_INVOKABLE void removeMember(QString groupid,QString memberid);
    Q_INVOKABLE void setMemberInfo(QString memberid,QString groupid,QString operate,QString remark);

private slots:
    void onGetMemberListResult(QString,MemberList);
    void onRemoveMemberResult(QString result);
    void onSetMemberInfoResult(QString result);
    void onMemberInfoChanged(QString groupid,Member member);
    void onMemberAvatarChanged(QString userid,QString avatar);
    void onGroupLeaderChanged(QString userid,QString username,QString groupid,QString groupname);
//    void onMemberListChanged();
signals:
    void isTipChanged();
    void my_TypeChanged();
    void getMemberListResult(QString result);

private:

    void initConnect();
    int  indexOfSection(QString sectnion);//从map开头找第一个section相同item位置
    QMap<QString, CDoodMemberItem*> memberListMap;
    QMap<QString, CDoodMemberItem*> groupLeaderListMap;
    QMap<QString, CDoodMemberItem*> groupAdminListMap;

    LinkDoodClient *m_pClient;

    void addMember(Member mem);
    void modifyMember(Member mem);
    void removeMemberItem(QString memberid);
    QString mIsTip;
    QString mMy_Id;
    QString mMy_Type;
    QString mMy_sec;
    QString mLeaderId;
    Member mTempMember;
    QString mGroupid;
};

#endif // CDOODMEMBERMANAGER_H
