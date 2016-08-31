#include<iostream>
#include<QDebug>
#include "IMClient.h"
#include "INotifyService.h"
#include "IGroupService.h"
#include "FileUtils.h"
#include "IFileService.h"
#include<groupcontroler.h>
#include "ISearchService.h"


void GroupControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setGroupObserver(this);
}

void GroupControler::createGroup(QString level, QString name, MemberList memberList)
{

    std::vector<int64> members;
    for(auto i: memberList){
        int64 member;
        member=i.id.toLongLong();
        members.push_back(member);
    }
    std::string Name=name.toStdString();
    qDebug() << Q_FUNC_INFO<<name<<"        qunmingcehnguqnmingcheng";
    service::IMClient::getClient()->getGroup()->createGroup(level.toInt(),Name,members,
                                                            std::bind(&GroupControler::_createGroup,this,std::placeholders::_1,
                                                                      std::placeholders::_2));
}

void GroupControler::_createGroup(service::ErrorInfo &info, long long &res)
{
    qDebug() << Q_FUNC_INFO<<"2222222......"<<info.code();
    if(info.code()==0){
        emit createGroupResult(QString::number(res));
    }
    else if(info.code()==303){
        emit createGroupResult("创建群失败(群数量超过限制)");
    }
    else{
        emit createGroupResult("创建群失败");
    }

}

void GroupControler::addGroup(QString groupid, QString verify_info)
{
    qDebug() << Q_FUNC_INFO<<"2222222"<<groupid;
    std::string verify=verify_info.toStdString();
    service::IMClient::getClient()->getGroup()->addGroup(groupid.toLongLong(),verify,
                                                         std::bind(&GroupControler::_addGroup,this,std::placeholders::_1));
}

void GroupControler::_addGroup(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<"2222222"<<info.code();
    switch (info.code()) {
    case 0:
        emit addGroupResult("请求已发出，等待对方处理");
        break;
    case 333:
        emit addGroupResult("您已在该群中");
        break;
    case 323:
        emit addGroupResult("该群不允许任何人添加");
        break;
    case 307:
        emit addGroupResult("该群已不存在");
        break;
    case 310:
        emit addGroupResult("该群成员已满");
        break;
    default:
        emit addGroupResult("操作失败");
        break;
    }
}

void GroupControler::removeGroup(QString type, QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getGroup()->removeGroup(type.toInt(),groupid.toLongLong(),
                                                            std::bind(&GroupControler::_removeGroup,this,std::placeholders::_1));
}

void GroupControler::_removeGroup(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<"ssssssssssssssss"<<info.code();
    if(info.code()==0){
        emit removeGroupResult("成功");
    }
    else{
        emit removeGroupResult("操作失败");
    }
}

void GroupControler::transferGroup(QString groupid, QString userid)
{
    service::IMClient::getClient()->getGroup()->transferGroup(groupid.toLongLong(),userid.toLongLong(),
                                                              std::bind(&GroupControler::_transferGroup,this,std::placeholders::_1));
}

void GroupControler::_transferGroup(service::ErrorInfo &info)
{
    qDebug()<<Q_FUNC_INFO<<info.code();
    if(info.code()==0){
        emit transferGroupResult("转让群成功");
    }
    else if(info.code()==303){
        emit transferGroupResult("该用户拥有的群数量已经超过限制");
    }
    else{
        emit transferGroupResult("转让群失败");
    }
}

void GroupControler::setGroupSet(QString groupid, QString verify_type, QString is_allow)
{
    int8 verify;
    int8 allow;
    if(verify_type=="不允许加群"){
        verify=1;
    }
    else if(verify_type=="需要验证"){
        verify=2;
    }
    else{
        verify=3;
    }
    if(is_allow=="允许邀请"){
        allow=1;
    }
    else{
        allow=2;
    }
    service::IMClient::getClient()->getGroup()->setGroupSet(groupid.toLongLong(),verify,allow,
                                                            std::bind(&GroupControler::_setGroupSet,this,std::placeholders::_1));
}

void GroupControler::_setGroupSet(service::ErrorInfo &info)
{
    if(info.code()==0){
        emit setGroupSetResult("设置成功");
    }
    else{
        emit setGroupSetResult("设置失败");
    }
}

void GroupControler::setGroupInfo(Group group)
{
    service::Group gp;
    gp.info.id=group.id.toLongLong();
    if(group.brief!=""){
        gp.__set_brief(group.brief.toStdString());
    }
    if(group.bulletin!=""){
        gp.__set_bulletin(group.bulletin.toStdString());
    }
    if(group.name!=""){
        gp.info.__set_name(group.name.toStdString());
    }
    if(group.avatar!=""&&group.thumbAvatar!=""){
        gp.info.__set_avatar(group.avatar.toStdString());
        gp.info.__set_thumb_avatar(group.thumbAvatar.toStdString());
    }
    if(group.extend!=""){
        gp.__set_extend(group.extend.toStdString());
    }
    service::IMClient::getClient()->getGroup()->setGroupInfo(gp,std::bind(&GroupControler::_setGroupInfo,this,
                                                                          std::placeholders::_1));
}

void GroupControler::_setGroupInfo(service::ErrorInfo &info)
{
    if(info.code()==0){
        emit setGroupInfoResult("设置群信息成功");
    }
    else{
        emit setGroupInfoResult("设置群信息失败");
    }
}

void GroupControler::getGroupSet(QString groupid)
{
    qDebug() << Q_FUNC_INFO<<"1111111111"<<groupid;
    service::IMClient::getClient()->getGroup()->getGroupSet(groupid.toLongLong(),
                                                            std::bind(&GroupControler::_getGroupSet,this,std::placeholders::_1,
                                                                      std::placeholders::_2,std::placeholders::_3));
}

void GroupControler::_getGroupSet(service::ErrorInfo &info, int8 verify_type, int8 is_allow)
{
    if(info.code()==0){
        QString verify;
        QString allow;
        if(verify_type==3){
            verify="允许任何人加群";
        }
        else if(verify_type==1){
            verify="不允许加群";
        }
        else{
            verify="需要验证";
        }
        if(is_allow==1){
            allow="允许邀请";
        }
        else{
            allow="不允许邀请";
        }
        emit getGroupSetResult("获取群设置成功",verify,allow);
    }
    else{
        emit getGroupSetResult("获取群设置失败","","");
    }
}

void GroupControler::getGroupInfo(QString groupid)
{
    qDebug() << Q_FUNC_INFO<<"1111111111";
    int64 id=groupid.toLongLong();
    service::IMClient::getClient()->getGroup()->getGroupInfo(id,std::bind(&GroupControler::_getGroupInfo,
                                                                          this,std::placeholders::_1,std::placeholders::_2));
}

void GroupControler::_getGroupInfo(service::ErrorInfo &info, service::Group group)
{
    qDebug() << Q_FUNC_INFO<<"22222222222"<<info.code();
    if(info.code()==0){
        Group gp;
        if(group.info.avatar!=""){
            gp.avatar="/data/data/com.vrv.linkDood/public/head/"+QString::fromStdString(group.info.avatar);
        }
        qDebug() << Q_FUNC_INFO<<gp.avatar<<"ssssssssssssssssssssssss";
        gp.createrid=QString::number(group.creater_id);
        QDateTime DateTime;
        DateTime.setMSecsSinceEpoch(group.create_time);
        gp.create_time=DateTime.toString("MM月dd日") +QString::fromLocal8Bit(" ")+DateTime.toString("HH:mm");
        gp.extend=QString::fromStdString(group.extend);
        gp.id=QString::number(group.info.id);
        gp.level=QString::number(group.info.level);
        gp.name=QString::fromStdString(group.info.name);
        gp.pinyin=QString::fromStdString(group.info.pinyin);
        gp.server=QString::fromStdString(group.info.server);
        if(group.info.thumb_avatar!=""){
            gp.thumbAvatar="/data/data/com.vrv.linkDood/public/head/"+QString::fromStdString(group.info.thumb_avatar);
        }
        qDebug() << Q_FUNC_INFO<<"22222222222"<<gp.thumbAvatar<<gp.name;
        gp.timeZone=QString::number(group.info.time_zone);
        gp.brief=QString::fromStdString(group.brief);
        gp.bulletin=QString::fromStdString(group.bulletin);
        if(gp.brief=="#"){
            gp.brief="";
        }
        qDebug() << Q_FUNC_INFO<<"33333333333"<<gp.brief<<gp.bulletin;
        qDebug() << Q_FUNC_INFO<<"member_num:"<<group.member_nums;
        emit getGroupInfoResult("获取群信息成功",gp);
    }
}

void GroupControler::inviteMember(QString groupid, MemberList memberList)
{
    std::vector<int64> members;
    for(auto i: memberList){
        int64 member;
        member=i.id.toLongLong();
        members.push_back(member);
    }
    service::IMClient::getClient()->getGroup()->inviteMember(groupid.toLongLong(),members,
                                                             std::bind(&GroupControler::_inviteMember,this,
                                                                       std::placeholders::_1));
}

void GroupControler::_inviteMember(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<info.code();
    if(info.code()==0){
        emit inviteMemberResult("邀请成员成功");
    }
    else{
        emit inviteMemberResult("邀请成员失败");
    }
}

void GroupControler::removeMember(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO<<"1111111111:"<<groupid<<"sss"<<userid;
    service::IMClient::getClient()->getGroup()->removeMember(groupid.toLongLong(),userid.toLongLong(),
                                                             std::bind(&GroupControler::_removeMember,this,
                                                                       std::placeholders::_1));
}

void GroupControler::_removeMember(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<"1111111111:"<<info.code();
    if(info.code()==0){
        emit removeMemberResult("移除群成员成功");
    }
    else{
        emit removeMemberResult("移除群成员失败");
    }
}

void GroupControler::getGroupList()
{
    service::IMClient::getClient()->getGroup()->getGroupList();
}

void GroupControler::setMemberInfo(Member member)
{
    qDebug() << Q_FUNC_INFO<<member.id<<member.groupid<<member.member_type<<member.remark;
    service::Member mem;
    int64 id=member.id.toLongLong();
    int64 groupid=member.groupid.toLongLong();
    mem.id=id;
    mem.__set_groupid(groupid);
    std::string remark=member.remark.toStdString();
    int member_type=member.member_type.toInt();
    if(member.remark!=""){
        mem.__set_remark(remark);
    }
    if(member.member_type!=""){
        mem.__set_member_type(member_type);
    }
    if(member.remark==""&&member.member_type==""){
        mem.__set_remark("");
    }
    service::IMClient::getClient()->getGroup()->setMemberInfo(mem,std::bind(&GroupControler::_setMemberInfo,this,
                                                                            std::placeholders::_1));
}

void GroupControler::_setMemberInfo(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<info.code();
    if(info.code()==0){
        emit setMemberInfoResult("设置成员信息成功");
    }
    else{
        emit setMemberInfoResult("设置成员信息失败");
    }
}

void GroupControler::getMemberInfo(QString groupid, QString userid)
{
    qDebug() << Q_FUNC_INFO<<groupid<<" "<<userid;
    //    service::IMClient::getClient()->getGroup()->getMemberInfo(groupid.toLongLong(),userid.toLongLong(),
    //                                                              std::bind(&GroupControler::_getMemberInfo,this,
    //                                                                        std::placeholders::_1,std::placeholders::_2));
    service::IMClient::getClient()->getSearch()->getUserInfo(userid.toLongLong(), std::bind(&GroupControler::_getMemberInfo, this, std::placeholders::_1, std::placeholders::_2));
}

void GroupControler::_getMemberInfo(service::ErrorInfo& info, service::User& member)
{
    qDebug() << Q_FUNC_INFO<<info.code();
    if(info.code()==0){
        //        service::Member mem=dynamic_cast<service::Member&>(member);
        Member m;
        m.name=QString::fromStdString(member.name);
        //        m.avatar=QString::fromStdString(mem.avatar);
        //        if(mem.gender==0){
        //            m.gender="保密";
        //        }
        //        if(mem.gender==1){
        //            m.gender="男";
        //        }
        //        if(mem.gender==2){
        //            m.gender="女";
        //        }
        //        m.groupid=QString::number(mem.groupid);
        //        m.id=QString::number(mem.id);
        //        m.member_type=QString::number(mem.member_type);
        //        m.name=QString::fromStdString(mem.name);
        //        m.remark=QString::fromStdString(mem.remark);
        //        m.team=QString::number(mem.team);
        //        m.thumbAvatar=QString::fromStdString(mem.thumb_avatar);
        emit getMemberInfoResult("获取成员信息成功",m);
    }
    else{
        Member m;
        emit getMemberInfoResult("获取成员信息失败",m);
    }
}

void GroupControler::getMemberList(QString groupid)
{
    qDebug() << Q_FUNC_INFO <<"getliebiaoliebiao"<<groupid;
    int64 id=groupid.toLongLong();
    service::IMClient::getClient()->getGroup()->getMemberList(id,std::bind(&GroupControler::_getMemberList,
                                                                           this,std::placeholders::_1,std::placeholders::_2,groupid));
}

void GroupControler::_getMemberList(service::ErrorInfo &info, std::vector<std::shared_ptr<service::User> > members,QString groupId)
{
    qDebug() << Q_FUNC_INFO <<"size:"<<members.size()<<"groupId:"<<groupId;
    MemberList memberList;
    if(info.code()==0){
        if(members.size() >0){
            memberList=MemberToQMemberList(members);
            emit getGroupMemberListReslut(info.code(),groupId,memberList);
        }
        emit getMemberListResult("获取成员列表成功",memberList);

    }
}

void GroupControler::getGroupFileList(QString groupid)
{
    service::IMClient::getClient()->getGroup()->getGroupFileList(groupid.toLongLong(),0,100,1,std::bind(&GroupControler::_getGroupFileList,
                                                                                                        this,std::placeholders::_1,std::placeholders::_2));
}

void GroupControler::_getGroupFileList(service::ErrorInfo &info, std::vector<FileInfo> fileInfos)
{
    FileInfoList fileInfoList;
    if(info.code()==0){
        for(auto i: fileInfos){
            MsgFileInfo msgFileInfo;
            msgFileInfo.encrypt_key=QString::fromStdString(i.encrypt_key);
            msgFileInfo.fileid=QString::number(i.fileid);
            msgFileInfo.name=QString::fromStdString(i.name);
            msgFileInfo.path=QString::fromStdString(i.path);
            msgFileInfo.size=QString::number(i.size);
            msgFileInfo.targetid=QString::number(i.targetid);
            msgFileInfo.url=QString::fromStdString(i.url);
            msgFileInfo.userid=QString::number(i.userid);
            QDateTime DateTime;
            DateTime.setMSecsSinceEpoch(i.time);
            msgFileInfo.time=DateTime.toString("MM月dd日");
            fileInfoList.push_back(msgFileInfo);
        }
    }
    emit getGroupFileListResult(fileInfoList);
}

void GroupControler::deleteGroupFile(QStringList fileList)
{
    qDebug() << Q_FUNC_INFO;
    std::vector<int64> files;
    for(auto i:fileList){
        int64 file;
        file=i.toLongLong();
        files.push_back(file);
    }
    service::IMClient::getClient()->getGroup()->deleteGroupFile(files,std::bind(&GroupControler::_deleteGroupFile,
                                                                                this,std::placeholders::_1));
}

void GroupControler::_deleteGroupFile(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO;
    if(info.code()==0){
        emit deleteGroupFileResult("删除成功");
    }
    else{
        emit deleteGroupFileResult("删除失败");
    }
}

void GroupControler::uploadGroupAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO << "path:" << path;
    service::IMClient::getClient()->getFile()->uploadAvatar(path.toStdString(), std::bind(&GroupControler::_uploadGroupAvatar, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void GroupControler::_uploadGroupAvatar(std::string orgijson, std::string thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO <<code;
    if(code==0){
        std::string src = "";
        std::string thum="";
        thum =utils::FileUtils::getImgUrl(thumbjson, src);
        utils::FileUtils::getImgUrl(orgijson, src);
        emit uploadGroupAvatarResult(QString::fromStdString(thum),QString::fromStdString(src));
    }
    else{
        qDebug() << Q_FUNC_INFO <<code;
    }
}
void GroupControler::onListChanged(std::vector<std::shared_ptr<service::User> > group)
{
    qDebug() << Q_FUNC_INFO<<group.size();
    GroupList groupList;
    for(auto i:group){
        std::shared_ptr<service::TinyGroup> tg = std::dynamic_pointer_cast<service::TinyGroup>(i);
        Group gp;
        gp.avatar=QString::fromStdString(tg->avatar);
        gp.createrid=QString::number(tg->createrid);
        qDebug() << Q_FUNC_INFO<<"wwwwwwwwww :"<<gp.createrid;
        //        QDateTime DateTime;
        //        DateTime.setMSecsSinceEpoch(gro->create_time);
        //        group.create_time=DateTime.toString("MM月dd日") +QString::fromLocal8Bit(" ")+DateTime.toString("HH:mm");
        gp.extend=QString::fromStdString(tg->extends);
        gp.id=QString::number(tg->id);
        gp.level=QString::number(tg->level);
        gp.name=QString::fromStdString(tg->name);
        std::string str;
        str=tg->pinyin.substr(0,1);
        str[0]=str[0]-32;
        if(str[0]<'A'||str[0]>'Z'){
            str[0]='#';
        }

        gp.pinyin=QString::fromStdString(str);
        qDebug() << Q_FUNC_INFO<<gp.pinyin<<"zhelizheliezheli";
        gp.server=QString::fromStdString(tg->server);
        gp.thumbAvatar=QString::fromStdString(tg->thumb_avatar);

        qDebug() << Q_FUNC_INFO<<"wwwwwwwwww"<<gp.thumbAvatar;
        gp.timeZone=QString::number(tg->time_zone);
        groupList.push_back(gp);
    }
    emit groupListChanged(groupList);
}

void GroupControler::onGroupAvatarChanged(long long groupid, std::string avatar)
{
    if(avatar!=""){
        qDebug() << Q_FUNC_INFO<<groupid;
        emit groupAvatarChanged(QString::number(groupid),QString::fromStdString(avatar));
    }
}

void GroupControler::onMemberAvatarChanged(long long userid, std::string avatar)
{
    if(avatar!=""){
        qDebug() << Q_FUNC_INFO<<userid<<avatar.c_str();
        emit memberAvatarChanged(QString::number(userid),QString::fromStdString(avatar));
    }
}

void GroupControler::onGroupInfoChanged(int8 operType, service::Group &group)
{
    qDebug() << Q_FUNC_INFO;
    Group gp;
    gp.id=QString::number(group.info.id);
    std::string str=group.info.pinyin.substr(0,1);
    str[0]=str[0]-32;
    if(str[0]<'A'||str[0]>'Z'){
        str[0]='#';
    }
    gp.pinyin=QString::fromStdString(str);
    gp.createrid=QString::number(group.info.createrid);
    gp.thumbAvatar=QString::fromStdString(group.info.thumb_avatar);
    gp.avatar=QString::fromStdString(group.info.avatar);
    qDebug() << Q_FUNC_INFO<<"gp.createrid"<<gp.createrid;
    gp.brief=QString::fromStdString(group.brief);
    gp.bulletin=QString::fromStdString(group.bulletin);
    gp.level=QString::number(group.info.level);
    gp.member_nums=QString::number(group.member_nums);
    gp.name=QString::fromStdString(group.info.name);
    emit groupInfoChanged(QString::number(operType),gp);
}

void GroupControler::onGroupLeaderChanged(long long userid, std::string user_name, long long groupid, std::string group_name)
{
    qDebug() << Q_FUNC_INFO;
    emit groupLeaderChanged(QString::number(userid),QString::fromStdString(user_name),QString::number(groupid),QString::fromStdString(group_name));
}

void GroupControler::onMemberInfoChanged(long long groupid, service::User &info)
{
    qDebug() << Q_FUNC_INFO;
    service::Member mem=dynamic_cast<service::Member&>(info);
    Member member;
    if(mem.gender==0){
        member.gender="保密";
    }
    else if(mem.gender==1){
        member.gender="男";
    }
    else{
        member.gender="女";
    }
    member.groupid=QString::number(mem.groupid);
    qDebug() << Q_FUNC_INFO<<groupid<<"sssss:"<<mem.team;
    member.id=QString::number(mem.id);
    qDebug() << Q_FUNC_INFO<<member.id;
    member.member_type=QString::number(mem.member_type);
    qDebug() << Q_FUNC_INFO<<member.member_type;
    member.name=QString::fromStdString(mem.name);
    qDebug() << Q_FUNC_INFO<<member.name;
    member.remark=QString::fromStdString(mem.remark);
    qDebug() << Q_FUNC_INFO<<member.remark;
    std::string str="";
    if(mem.team!=0){
        char c=mem.team-32;
        char sz[5] = {c};
        str=sz;
        if(str.length()>0){
            if(str[0]<'A'||str[0]>'Z'){
                str[0]='#';
            }
        }
        member.team=QString::fromStdString(str);
    }
    if(mem.thumb_avatar!=""){
        member.thumbAvatar="/data/data/com.vrv.linkDood/public/head/"+QString::fromStdString(mem.thumb_avatar);
    }
    qDebug() << Q_FUNC_INFO<<member.thumbAvatar<<"sssssssss";
    emit memberInfoChanged(QString::number(groupid),member);
}

void GroupControler::onMemberListChanged(int operType, long long groupid, std::vector<std::shared_ptr<service::User> > members)
{
    qDebug() << Q_FUNC_INFO<<members.size()<<"operType:"<<operType<<"groupid:"<<groupid;
    QString curGgroupId = QString::number(groupid);
    if(operType!=8&&operType!=32&&operType!=33&&operType!=1){
        return;
    }
    if(members.size()<1){
        return;
    }
    MemberList memberList;
    memberList=MemberToQMemberList(members);
    if(operType==8){
        emit getMemberListResult("获取成员列表成功",memberList);
        emit getGroupMemberListReslut(0,curGgroupId,memberList);
    }
    else{
        emit memberListChanged(QString::number(operType),curGgroupId,memberList);
    }
}

MemberList GroupControler::MemberToQMemberList(std::vector<std::shared_ptr<service::User> > members)
{
    MemberList memberList;
    for(auto i: members){
        if(i == NULL){
            continue;
        }
        Member member;
        std::shared_ptr<service::Member> mem = std::dynamic_pointer_cast<service::Member>(i);
        if(mem == NULL){
            continue;
        }
        member.avatar=QString::fromStdString(mem->avatar);
        if(mem->gender==1){
            member.gender="男";
        }
        else if(mem->gender==2){
            member.gender="女";
        }
        else{
            member.gender="保密";
        }
        member.groupid=QString::number(mem->groupid);
        member.id=QString::number(mem->id);
        member.member_type=QString::number(mem->member_type);
        member.name=QString::fromStdString(mem->name);
        member.remark=QString::fromStdString(mem->remark);
        if(member.remark=="#"){
            member.remark=member.name;
        }
        std::string str="";
        char c=mem->team;
        char sz[5] = {c};
        str=sz;
        if(str.length()>0){
            if(str[0]<'A'||str[0]>'Z'){
                str[0]='#';
            }
        }
        member.team=QString::fromStdString(str);
        if(mem->thumb_avatar!=""){
            member.thumbAvatar="/data/data/com.vrv.linkDood/public/head/"+QString::fromStdString(mem->thumb_avatar);
        }
        memberList.push_back(member);
    }
    return memberList;
}

