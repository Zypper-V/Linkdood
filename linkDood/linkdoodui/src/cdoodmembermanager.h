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
    Q_PROPERTY(QString memberSize READ memberSize WRITE setMemberSize NOTIFY memberSizeChanged)

public:
    explicit CDoodMemberManager(LinkDoodClient *client = 0, QObject *parent = 0);
    Q_INVOKABLE void clearMemberList();

    ~CDoodMemberManager();
    QString getMyId();

    QString isTip()const;
    Q_INVOKABLE QString   setIsTip(const QString data);

    QString my_Type()const;
    Q_INVOKABLE QString   setMy_Type(const QString data);

    Q_INVOKABLE QString memberSize()const;
    Q_INVOKABLE QString   setMemberSize(const QString data);

    Q_INVOKABLE bool isMyself(QString id);
    Q_INVOKABLE bool isMember(QString id);
    Q_INVOKABLE void judgeTip(QString hisType);
    Q_INVOKABLE void removeMember(QString groupid,QString memberid);
    Q_INVOKABLE void getMemberInfo(QString groupid,QString memberid);
    Q_INVOKABLE void setMemberInfo(QString memberid,QString groupid,QString operate,QString remark);
    Q_INVOKABLE QString groupId();
private slots:
    void onGetMemberListResult(QString,MemberList);
    void onGetMemberInfoResult(QString result,Member member);
    void onRemoveMemberResult(QString result);
    void onSetMemberInfoResult(QString result);
    void onMemberInfoChanged(QString groupid,Member member);
    void onMemberAvatarChanged(QString userid,QString avatar);
    void onGroupLeaderChanged(QString userid,QString username,QString groupid,QString groupname);
    void onMemberListChanged(QString operType,QString GroupId,MemberList memberlist);
signals:
    void isTipChanged();
    void my_TypeChanged();
    void memberSizeChanged();
    void getMemberListResult(QString result);
    void wordsOutOfLimited(QString tip);
    void groupMemsChanged(QString groupid,int size);
    void getMemberInfoResult(QString name);
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
    QString mMemberSize;
    QString mMy_sec;
    QString mLeaderId;
    Member mTempMember;
    QString mGroupid;
    QString m_ThePresentGroupid;
};

#endif // CDOODMEMBERMANAGER_H
