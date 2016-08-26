#ifndef GROUPCONTROLER_H
#define GROUPCONTROLER_H
#include<IGroupObserver.h>
#include<QObject>
#include "Group.h"
#include "TinyGroup.h"
#include "Member.h"
#include "linkdoodtypes.h"
class GroupControler :public QObject, public IGroupObserver
{
    Q_OBJECT
public:
    void init();
    void createGroup(QString level, QString name, MemberList memberList);
    void _createGroup(service::ErrorInfo& info, int64 &res);
    void addGroup(QString groupid, QString verify_info);
    void _addGroup(service::ErrorInfo& info);
    void removeGroup(QString type, QString groupid);
    void _removeGroup(service::ErrorInfo& info);
    void transferGroup(QString groupid, QString userid);
    void _transferGroup(service::ErrorInfo& info);
    void setGroupSet(QString groupid, QString verify_type, QString is_allow);
    void _setGroupSet(service::ErrorInfo& info);
    void setGroupInfo(Group group);
    void _setGroupInfo(service::ErrorInfo& info);
    void getGroupSet(QString groupid);
    void _getGroupSet(service::ErrorInfo& info,int8 verify_type,int8 is_allow);
    void getGroupInfo(QString groupid);
    void _getGroupInfo(service::ErrorInfo& info,service::Group group);
    void inviteMember(QString groupid,MemberList memberList);
    void _inviteMember(service::ErrorInfo& info);
    void removeMember(QString groupid, QString userid);
    void _removeMember(service::ErrorInfo& info);
    void getGroupList();
    void setMemberInfo(Member member);
    void _setMemberInfo(service::ErrorInfo& info);
    void getMemberInfo(QString groupid,QString userid);
    void _getMemberInfo(service::ErrorInfo& info,service::User& member);
    void getMemberList(QString groupid);
    void _getMemberList(service::ErrorInfo& info, std::vector<std::shared_ptr<service::User> > members,QString groupid);
    void getGroupFileList(QString groupid);
    void _getGroupFileList(service::ErrorInfo& info, std::vector<FileInfo> fileInfos);
    void deleteGroupFile(QStringList fileList);
    void _deleteGroupFile(service::ErrorInfo& info);
    void uploadGroupAvatar(QString path);
    void _uploadGroupAvatar(std::string orgijson, std::string thumbjson, int code);


    void getGroupMemsList(QString groupid);
    void _getGroupMemsList(service::ErrorInfo& info, std::vector<std::shared_ptr<service::User> > members,QString groupid);

    void onListChanged(std::vector<std::shared_ptr<service::User> >  group);
    void onGroupAvatarChanged(int64 groupid,std::string avatar);
    void onMemberAvatarChanged(int64 userid, std::string avatar);
    void onGroupInfoChanged(int8 operType,service::Group& group);
    void onGroupLeaderChanged(int64 userid, std::string user_name,int64 groupid,std::string group_name);
    void onMemberInfoChanged(int64 groupid, service::User& info);
    void onMemberListChanged(int operType, int64 groupid, std::vector<std::shared_ptr<service::User> > members);
signals:
    void groupListChanged(GroupList groupList);
    void groupAvatarChanged(QString groupid,QString avatar);
    void memberAvatarChanged(QString userid,QString avatar);
    void groupInfoChanged(QString operType,Group group);
    void groupLeaderChanged(QString userid,QString user_name,QString groupid,QString group_name);
    void memberInfoChanged(QString groupid,Member member);
    void memberListChanged(QString operType,QString groupid,MemberList memberList);


    void createGroupResult(QString result);
    void addGroupResult(QString result);
    void removeGroupResult(QString result);
    void transferGroupResult(QString result);
    void setGroupSetResult(QString result);
    void setGroupInfoResult(QString result);
    void getGroupSetResult(QString result,QString verify_type,QString is_allow);
    void getGroupInfoResult(QString result,Group group);
    void inviteMemberResult(QString result);
    void removeMemberResult(QString result);
    void setMemberInfoResult(QString result);
    void getMemberInfoResult(QString result,Member member);
    void getGroupMemberListReslut(int code,QString id,MemberList list);
    void getMemberListResult(QString result,MemberList memberList);
    void getGroupFileListResult(FileInfoList fileInfoList);
    void deleteGroupFileResult(QString result);
    void uploadGroupAvatarResult(QString thum_url,QString src_url);
private:
    MemberList MemberToQMemberList(std::vector<std::shared_ptr<service::User> > members);
};
























#endif // GROUPCONTROLER_H
