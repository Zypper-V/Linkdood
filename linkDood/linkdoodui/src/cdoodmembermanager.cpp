#include "cdoodmembermanager.h"
#include "cdoodmemberitem.h"


CDoodMemberManager::CDoodMemberManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;

    qRegisterMetaType<CDoodMemberManager*>();
    initConnect();
}

CDoodMemberManager::~CDoodMemberManager()
{

}

QString CDoodMemberManager::getMyId()
{
    QString fileName = QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    QString id;
    id = settings.value("myId","").toString();
    return id;
}

QString CDoodMemberManager::isTip() const
{
    return mIsTip;
}

QString CDoodMemberManager::setIsTip(const QString data)
{
    if(mIsTip == data) {
        return data;
    }
    mIsTip=data;
    emit isTipChanged();
    return mIsTip;
}

QString CDoodMemberManager::my_Type() const
{
    return mMy_Type;
}

QString CDoodMemberManager::setMy_Type(const QString data)
{
    if(mMy_Type == data) {
        return data;
    }
    mMy_Type=data;
    emit my_TypeChanged();
    return mMy_Type;
}

bool CDoodMemberManager::isMyself(QString id)
{
    if(id==mMy_Id){
        return true;
    }
    return false;
}

bool CDoodMemberManager::isMember(QString id)
{
    CDoodMemberItem *item = memberListMap.value(id);
    if(item!=NULL){
        return true;
    }
    item=groupLeaderListMap.value(id);
    if(item!=NULL){
        return true;
    }
    item=groupAdminListMap.value(id);
    if(item!=NULL){
        return true;
    }
    return false;
}

void CDoodMemberManager::judgeTip(QString hisType)
{
    qDebug() << Q_FUNC_INFO<<mMy_Type<<"sssssssss"<<hisType;
    if(mMy_Type.toInt()>hisType.toInt()){
        qDebug() << Q_FUNC_INFO<<mMy_Type<<"sssssssss"<<hisType;
        setIsTip("1");
    }
    else{
        setIsTip("");
    }
    //    setMy_Type("3");
    //    setIsTip("1");
}

void CDoodMemberManager::removeMember(QString groupid, QString memberid)
{
    qDebug() << Q_FUNC_INFO;
    removeMemberItem(memberid);
    m_pClient->removeMember(groupid,memberid);
}

void CDoodMemberManager::setMemberInfo(QString groupid, QString memberid, QString operate, QString remark)
{
    mTempMember.id=memberid;
    mTempMember.groupid=groupid;
    if(operate=="管理员设置"){
        mTempMember.remark="";
        if(remark=="2"){
            mTempMember.member_type="2";
        }
        else{
            mTempMember.member_type="1";
        }
    }
    if(operate=="修改备注"){
        if(remark.size()>16){
            emit wordsOutOfLimited();
            return;
        }
        mTempMember.member_type=="";
        mTempMember.remark=remark;
    }
    m_pClient->setMemberInfo(mTempMember);
}

void CDoodMemberManager::onGetMemberListResult(QString result, MemberList memberList)
{
    qDebug() << Q_FUNC_INFO <<"gao";
    if(result=="获取成员列表成功"){
        clearMemberList();
        mMy_Id=getMyId();
        setMy_Type("1");
        qDebug() << Q_FUNC_INFO<<memberList.size()<<"chengyuanchengyuan";
        for(size_t i=0;i<memberList.size();i++)
        {
            mGroupid=memberList[0].groupid;
            qDebug() << Q_FUNC_INFO<<memberList[i].name<<memberList[i].team<<memberList[i].member_type;
            addMember(memberList[i]);
            emit itemCountChanged();
        }

        emit getMemberListResult("获取成员列表成功");
    }
    else{
        emit getMemberListResult("获取成员列表失败");
    }


}

void CDoodMemberManager::onRemoveMemberResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<result;
    if(result=="移除群成员成功"){

    }
}

void CDoodMemberManager::onSetMemberInfoResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<result;
    if(result=="设置成员信息成功"){

    }
}

void CDoodMemberManager::onMemberInfoChanged(QString groupid, Member member)
{
    qDebug() << Q_FUNC_INFO<<groupid;
    if(groupid==mGroupid){
        if(member.member_type=="0"){
            CDoodMemberItem *item = memberListMap.value(member.id);
            if(item!=NULL){
                member.member_type=item->member_type();
            }
            item=groupAdminListMap.value(member.id);
            if(item!=NULL){
                member.member_type=item->member_type();
            }
            item=groupLeaderListMap.value(member.id);
            if(item!=NULL){
                member.member_type=item->member_type();
            }
        }
        if(member.member_type!="0"){
            removeMemberItem(member.id);
            addMember(member);
        }
    }

}

void CDoodMemberManager::onMemberAvatarChanged(QString userid, QString avatar)
{
    qDebug() << Q_FUNC_INFO<<"sss";
    CDoodMemberItem *item = memberListMap.value(userid);
    if(item!=NULL){
        item->setThumbAvatar(avatar);
    }
    item=groupAdminListMap.value(userid);
    if(item!=NULL){
        item->setThumbAvatar(avatar);
    }
    item=groupLeaderListMap.value(userid);
    if(item!=NULL){
        item->setThumbAvatar(avatar);
    }
}

void CDoodMemberManager::onGroupLeaderChanged(QString userid, QString username, QString groupid, QString groupname)
{
    qDebug() << Q_FUNC_INFO<<"sss";
    if(groupid==mGroupid){
        QList<CDoodMemberItem*>  itemList = groupLeaderListMap.values();
        if(itemList.size()!=0){
            Member mem;
            mem.name=itemList[0]->name();
            mem.id=itemList[0]->id();
            if(mem.id==mMy_Id){
                setMy_Type("1");
            }
            mem.thumbAvatar=itemList[0]->thumbAvatar();
            mem.gender=itemList[0]->gender();
            mem.groupid=itemList[0]->groupid();
            mem.remark=itemList[0]->remark();
            mem.member_type="1";
            mem.team=itemList[0]->team();
            removeItem(itemList.value(0));
            addMember(mem);
            qDebug() << Q_FUNC_INFO<<"sss";

        }
        CDoodMemberItem *item = memberListMap.value(userid);
        if(item!=NULL){
            Member mem;
            mem.name=item->name();
            mem.id=item->id();
            if(userid==mMy_Id){
                setMy_Type("3");
            }
            mem.thumbAvatar=item->thumbAvatar();
            mem.gender=item->gender();
            mem.groupid=item->groupid();
            mem.remark=item->remark();
            mem.member_type="3";
            mem.team=item->team();
            removeItem(item);
            addMember(mem);
            qDebug() << Q_FUNC_INFO<<"sss";
        }
        item=groupAdminListMap.value(userid);
        if(item!=NULL){
            Member mem;
            mem.name=item->name();
            mem.id=item->id();
            if(userid==mMy_Id){
                setMy_Type("3");
            }
            mem.thumbAvatar=item->thumbAvatar();
            mem.gender=item->gender();
            mem.groupid=item->groupid();
            mem.remark=item->remark();
            mem.member_type="3";
            mem.team=item->team();
            removeItem(item);
            addMember(mem);
            qDebug() << Q_FUNC_INFO<<"sss";
        }
    }
}
void CDoodMemberManager::clearMemberList()
{
    qDebug() << Q_FUNC_INFO;
    QList<CDoodMemberItem*>  itemList = memberListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    memberListMap.clear();

    itemList = groupLeaderListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    groupLeaderListMap.clear();

    itemList = groupAdminListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    groupAdminListMap.clear();
    setMy_Type("1");
}
void CDoodMemberManager::addMember(Member mem)
{
    //TODO
    CDoodMemberItem *tmpItem = new CDoodMemberItem(this);
    CDoodMemberItem *groupLeaderItem = NULL;
    CDoodMemberItem *groupAdminItem=NULL;

    tmpItem->setId(mem.id);
    tmpItem->setGender(mem.gender);
    tmpItem->setName(mem.name);
    tmpItem->setThumbAvatar(mem.thumbAvatar);
    tmpItem->setMember_type(mem.member_type);
    tmpItem->setSection(mem.team);
    tmpItem->setTeam(mem.team);
    tmpItem->setGroupid(mem.groupid);
    tmpItem->setRemark(mem.remark);
    if(mem.member_type == "3"){
        groupLeaderItem = new CDoodMemberItem(this);
        groupLeaderItem->setId(mem.id);
        groupLeaderItem->setGender(mem.gender);
        groupLeaderItem->setName(mem.name);
        groupLeaderItem->setThumbAvatar(mem.thumbAvatar);
        groupLeaderItem->setMember_type(mem.member_type);
        groupLeaderItem->setRemark(mem.remark);
        groupLeaderItem->setGroupid(mem.groupid);
        groupLeaderItem->setTeam(mem.team);
        groupLeaderItem->setSection("群主");
        if(mMy_Id==mem.id){
            setMy_Type("3");
            mMy_sec=mem.team;
            qDebug() << Q_FUNC_INFO<<"niuniuniu"<<my_Type();
        }
        insertItem(0,groupLeaderItem);

        groupLeaderListMap[mem.id] = groupLeaderItem;
    }


    if(mem.member_type == "2"){
        groupAdminItem = new CDoodMemberItem(this);

        groupAdminItem->setId(mem.id);
        groupAdminItem->setGender(mem.gender);
        groupAdminItem->setName(mem.name);
        groupAdminItem->setThumbAvatar(mem.thumbAvatar);
        groupAdminItem->setMember_type(mem.member_type);
        groupAdminItem->setRemark(mem.remark);
        groupAdminItem->setGroupid(mem.groupid);
        groupAdminItem->setTeam(mem.team);
        groupAdminItem->setSection("管理员");
        if(mMy_Id==mem.id){
            setMy_Type("2");
        }
        insertItem(groupLeaderListMap.size(),groupAdminItem);

        groupAdminListMap[mem.id] = groupAdminItem;
    }
    if(mem.member_type=="1"){
        insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
        memberListMap[mem.id] = tmpItem;
    }
}
int CDoodMemberManager::indexOfSection(QString sectnion)
{
    int index = groupAdminListMap.size()+groupLeaderListMap.size();
    for(;index < itemCount();++index){
        CDoodMemberItem *tmpItem = (CDoodMemberItem *)itemOfIndex(index);
        if(tmpItem->sectionKey() == sectnion||tmpItem->sectionKey()=="#"){
            return index;
        }
        else if(tmpItem->sectionKey()[0]>sectnion[0]&&sectnion!="#"){
            return index;
        }
    }
    return index;
}
void CDoodMemberManager::modifyMember(Member member)
{
    //TODO
    CDoodMemberItem *tmpItem = memberListMap.value(member.id);
    if(member.member_type!=""){
        tmpItem->setMember_type(member.member_type);
    }
    if(member.remark!=""){
        tmpItem->setRemark(member.remark);
    }
    tmpItem->setGroupid(member.groupid);
    tmpItem->setSection(member.team);

    CDoodMemberItem* item = groupAdminListMap.value(tmpItem->id(),NULL);
    if(item != NULL && member.member_type == "1"){
        removeItem(indexOf(item));
        groupAdminListMap.remove(member.id);
        delete item;
    }
    else if(item != NULL && member.member_type == "3"){
        removeItem(indexOf(item));
        groupAdminListMap.remove(member.id);
        delete item;
        QList<CDoodMemberItem*>  itemList = groupLeaderListMap.values();
        for(int i= 0;i< itemList.size();i++){
            removeItem(itemList.value(i));
            delete itemList.value(i);
        }
        groupLeaderListMap.clear();
        CDoodMemberItem* groupLeaderItem = new CDoodMemberItem(this);
        groupLeaderItem->setId(member.id);
        groupLeaderItem->setGender(member.gender);
        groupLeaderItem->setName(member.name);
        groupLeaderItem->setMember_type(member.member_type);
        groupLeaderItem->setThumbAvatar(member.thumbAvatar);
        groupLeaderItem->setRemark(member.remark);
        groupLeaderItem->setGroupid(member.groupid);
        groupLeaderItem->setSection("群主");
        insertItem(groupLeaderListMap.size(),groupLeaderItem);
        groupLeaderListMap[member.id] = groupLeaderItem;
        if(mMy_Id==member.id){
            setMy_Type("3");
            qDebug() << Q_FUNC_INFO<<"niuniuniu"<<my_Type();
        }

    }

    else if(item == NULL && member.member_type == "2"){
        CDoodMemberItem*groupAdminItem = new CDoodMemberItem(this);

        groupAdminItem->setId(member.id);
        groupAdminItem->setGender(member.gender);
        groupAdminItem->setName(member.name);
        groupAdminItem->setThumbAvatar(member.thumbAvatar);
        groupAdminItem->setMember_type(member.member_type);
        groupAdminItem->setRemark(member.remark);
        groupAdminItem->setGroupid(member.groupid);
        groupAdminItem->setSection("管理员");
        insertItem(groupAdminListMap.size(),groupAdminItem);
        groupAdminListMap[member.id] = groupAdminItem;
        if(mMy_Id==member.id){
            setMy_Type("2");
        }
    }
    CDoodMemberItem *item1 = groupLeaderListMap.value(tmpItem->id(),NULL);
    if(item1 == NULL && member.member_type == "3"){
        QList<CDoodMemberItem*>  itemList = groupLeaderListMap.values();
        for(int i= 0;i< itemList.size();i++){
            removeItem(itemList.value(i));
            delete itemList.value(i);
        }
        groupLeaderListMap.clear();
        CDoodMemberItem* groupLeaderItem = new CDoodMemberItem(this);
        groupLeaderItem->setId(member.id);
        groupLeaderItem->setGender(member.gender);
        groupLeaderItem->setName(member.name);
        groupLeaderItem->setMember_type(member.member_type);
        groupLeaderItem->setThumbAvatar(member.thumbAvatar);
        groupLeaderItem->setRemark(member.remark);
        groupLeaderItem->setGroupid(member.groupid);
        groupLeaderItem->setSection("群主");
        insertItem(groupLeaderListMap.size(),groupLeaderItem);
        groupLeaderListMap[member.id] = groupLeaderItem;
        if(mMy_Id==member.id){
            setMy_Type("3");
        }

    }
}

void CDoodMemberManager::removeMemberItem(QString memberid)
{
    //TODO
    CDoodMemberItem *item = groupAdminListMap.value(memberid,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        groupAdminListMap.remove(memberid);
        delete item;
    }
    item = memberListMap.value(memberid,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        memberListMap.remove(memberid);
        delete item;
    }
    item=groupLeaderListMap.value(memberid,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        groupLeaderListMap.remove(memberid);
        delete item;
    }
}
void CDoodMemberManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(getMemberListResult(QString, MemberList)), this, SLOT(onGetMemberListResult(QString, MemberList)));
    connect(m_pClient, SIGNAL(removeMemberResult(QString)), this, SLOT(onRemoveMemberResult(QString)));
    connect(m_pClient, SIGNAL(setMemberInfoResult(QString)), this, SLOT(onSetMemberInfoResult(QString)));
    connect(m_pClient, SIGNAL(memberInfoChanged(QString,Member)), this, SLOT(onMemberInfoChanged(QString,Member)));
    connect(m_pClient, SIGNAL(memberAvatarChanged(QString,QString)), this, SLOT(onMemberAvatarChanged(QString,QString)));
    connect(m_pClient, SIGNAL(groupLeaderChanged(QString,QString,QString,QString)), this, SLOT(onGroupLeaderChanged(QString,QString,QString,QString)));

}


