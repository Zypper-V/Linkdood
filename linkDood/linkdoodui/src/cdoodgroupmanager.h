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
    Q_PROPERTY(QString verify_type READ verify_type WRITE setVerify_type NOTIFY verify_typeChanged)
    Q_PROPERTY(QString is_allow READ is_allow WRITE setIs_allow NOTIFY is_allowChanged)
    Q_PROPERTY(bool isGroupLeader READ isGroupLeader WRITE setIsGroupLeader NOTIFY isGroupLeaderChanged)
    Q_PROPERTY(bool isCreateGroup READ isCreateGroup WRITE setIsCreateGroup NOTIFY isCreateGroupChanged)
    Q_PROPERTY(QString memberCount READ memberCount WRITE setMemberCount NOTIFY memberCountChanged)

public:
    explicit CDoodGroupManager(LinkDoodClient *client = 0, QObject *parent = 0);
    void getGroupInfoFromList(QString groupId,QString&name,QString&avatar);
    Member getMemberItemById(QString id);

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

    QString verify_type() const;
    Q_INVOKABLE QString setVerify_type(const QString &data);

    QString is_allow() const;
    Q_INVOKABLE QString setIs_allow(const QString &data);

    QString memberCount() const;
    Q_INVOKABLE QString setMemberCount(const QString &data);



    bool isGroupLeader() const;
    Q_INVOKABLE bool setIsGroupLeader(const bool &data);

    bool isCreateGroup() const;
    Q_INVOKABLE bool setIsCreateGroup(const bool &data);

    Q_INVOKABLE QString findName(QString groupid);
    Q_INVOKABLE void getMemberList(QString groupid);
    Q_INVOKABLE void clearGroupList();
    Q_INVOKABLE void selectmember(QString id);
    Q_INVOKABLE QString getSize(QString type,QString size1,QString size2);
    Q_INVOKABLE void selectMemberName(QString id,QString name);
    Q_INVOKABLE MemberList returnmember();
    Q_INVOKABLE void createGroup(QString name);
    Q_INVOKABLE void getGroupInfo(QString id);
    Q_INVOKABLE void removeGroup(QString operate,QString groupid);
    Q_INVOKABLE void inviteMember();
    Q_INVOKABLE void clearMemberCount();
    Q_INVOKABLE void addGroup(QString groupid,QString info);
    Q_INVOKABLE void getGroupList();
    Q_INVOKABLE void setGroupInfo(int type,QString remark);
    Q_INVOKABLE void getGroupSet(QString groupid);
    Q_INVOKABLE void setGroupSet(int type,QString remark);
    Q_INVOKABLE void uploadGroupAvatar(QString path);

    Q_INVOKABLE void transMessage(QString localId);

    Q_INVOKABLE void getGroupFileList(QString groupid);
    Q_INVOKABLE void transferGroup(QString groupid,QString userid);

    QString getMyId();
private slots:
    void onSetGroupInfoResult(QString result);
    void onCreateGroupResult(QString);
    void onGroupListChanged(GroupList groupList);
    void onGetGroupInfoResult(QString result,Group group);
    void onGroupInfoChanged(QString type,Group gp);
    void onGroupLeaderChanged(QString userid,QString username,QString groupid,QString groupname);
    void onRemoveGroupResult(QString result);
    void onTransferGroupResult(QString result);
    void onInviteMemberResult(QString result);
    void onAddGroupResult(QString result);
    void onGetGroupFileListResult(FileInfoList fileInfoList);
    void onSetGroupSetResult(QString result);
    void onGetGroupSetResult(QString result,QString verify_type,QString is_allow);
    void onUploadGroupAvatarResult(QString thum_url,QString src_url);
    void onGroupAvatarChanged(QString id,QString avatar);
    void onGroupMemberExit(QString GroupId);
signals:
    void idChanged();
    void nameChanged();
    void thumbAvatarChanged();
    void createrIdChanged();
    void briefChanged();
    void bulletinChanged();
    void verify_typeChanged();
    void is_allowChanged();
    void memberCountChanged();
    void isGroupLeaderChanged();
    void isCreateGroupChanged();

    void createGroupResult(QString result);
    void getGroupInfoResult();
    void removeGroupResult(QString result);
    void getGroupFileListResult();
    void inviteMemberResult(QString result);
    void addGroupResult(QString result);
    void transferGroupResult(QString result);
    void transMessageSelectContactList(QList<QString>list,QString localId);
    void uploadGroupAvatarResult();
    void wordsOutOfLimited(QString tip);
    void groupRemoveOrExitResult(QString groupId);
    void noMemberInvited(QString tip);
    void newGroupToChat(QString id,QString name);
private:
    QString mId;
    QString mName;
    QString mThumbAvatar;
    QString mCreaterId;
    QString mBrief;
    QString mButtletin;
    QString mVerify_type;
    QString mIs_allow;
    QString mMemberCount;
    QString mTemp_verify;
    QString mTemp_allow;
    int mType;
    QString mTemp;
    bool mIsGroupLeader;
    bool mIsCreateGroup;
    int mGetGroupInfo;
    bool mNewGroupInfo;
    QString mNewGroupId;

    void initConnect();
    int  indexOfSection(QString sectnion);//从map开头找第一个section相同item位置
    LinkDoodClient *m_pClient;
    QMap<QString, CDoodGroupItem*> groupListMap;
    MemberList m_memberList;
    linkdoodui_Workspace* m_pUiManager;
};

#endif // CDOODGROUPMANAGER_H
