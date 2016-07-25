#ifndef CDOODGROUPMANAGER_H
#define CDOODGROUPMANAGER_H
#include <QObject>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"
#include "linkdoodui_workspace.h"

class CDoodGroupItem;

class CDoodGroupManager: public CDoodListModel
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString createrId READ createrId WRITE setCreaterId NOTIFY createrIdChanged)
    Q_PROPERTY(QString brief READ brief WRITE setBrief NOTIFY briefChanged)
    Q_PROPERTY(QString bulletin READ bulletin WRITE setBulletin NOTIFY bulletinChanged)
    Q_PROPERTY(bool isGroupLeader READ isGroupLeader WRITE setIsGroupLeader NOTIFY isGroupLeaderChanged)
    Q_PROPERTY(bool isCreateGroup READ isCreateGroup WRITE setIsCreateGroup NOTIFY isCreateGroupChanged)

public:
    explicit CDoodGroupManager(LinkDoodClient *client = 0, QObject *parent = 0);
    void getGroupInfoFromList(QString groupId,QString&name,QString&avatar);
    QString id() const;
    Q_INVOKABLE QString setId(const QString &data);

    QString name() const;
    Q_INVOKABLE QString setName(const QString &data);

    QString thumbAvatar() const;
    Q_INVOKABLE  QString setThumbAvatar(const QString &data);

    QString createrId() const;
    QString setCreaterId(const QString &data);

    QString brief() const;
    Q_INVOKABLE QString setBrief(const QString &data);

    QString bulletin() const;
    Q_INVOKABLE QString setBulletin(const QString &data);

    bool isGroupLeader() const;
    Q_INVOKABLE bool setIsGroupLeader(const bool &data);

    bool isCreateGroup() const;
    Q_INVOKABLE bool setIsCreateGroup(const bool &data);

    Q_INVOKABLE QString findName(QString groupid);
    Q_INVOKABLE void getMemberList(QString groupid);
    Q_INVOKABLE void clearGroupList();
    Q_INVOKABLE void selectmember(QString id);
    Q_INVOKABLE void createGroup(QString name);
    Q_INVOKABLE void getGroupInfo(QString id);
    Q_INVOKABLE void removeGroup(QString groupid);
    Q_INVOKABLE void inviteMember();
    Q_INVOKABLE void addGroup(QString groupid);
    Q_INVOKABLE void getGroupList();

   Q_INVOKABLE void getGroupFileList(QString groupid);
   Q_INVOKABLE void transferGroup(QString groupid,QString userid);

    QString getMyId();
private slots:
    void onCreateGroupResult(QString);
    void onGroupListChanged(GroupList groupList);
    void onGetGroupInfoResult(QString result,Group group);
    void onGroupInfoChanged(QString type,Group gp);
    void onRemoveGroupResult(QString result);
    void onTransferGroupResult(QString result);
    void onInviteMemberResult(QString result);
    void onAddGroupResult(QString result);
    void onGetGroupFileListResult(FileInfoList fileInfoList);
signals:
    void idChanged();
    void nameChanged();
    void thumbAvatarChanged();
    void createrIdChanged();
    void briefChanged();
    void bulletinChanged();
    void isGroupLeaderChanged();
    void isCreateGroupChanged();

    void createGroupResult(QString result);
    void getGroupInfoResult();
    void removeGroupResult(QString result);
    void getGroupFileListResult();
    void inviteMemberResult(QString result);
    void addGroupResult(QString result);
private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mCreaterId;
    QString mBrief;
    QString mButtletin;
    bool mIsGroupLeader;
    bool mIsCreateGroup;
    int mGetGroupInfo;

    void initConnect();
    int  indexOfSection(QString sectnion);//从map开头找第一个section相同item位置
    LinkDoodClient *m_pClient;
    QMap<QString, CDoodGroupItem*> groupListMap;
    MemberList m_memberList;
    linkdoodui_Workspace* m_pUiManager;
};

#endif // CDOODGROUPMANAGER_H
