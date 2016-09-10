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

QString CDoodMemberManager::memberSize() const
{
    return mMemberSize;
}

QString CDoodMemberManager::setMemberSize(const QString data)
{
    if(mMemberSize==data){
        return data;
    }
    mMemberSize=data;
    emit memberSizeChanged();
    if(data != ""){
        emit groupMemsChanged(mGroupid,data.toInt());
    }
    return mMemberSize;
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

void CDoodMemberManager::getMemberInfo(QString groupid, QString memberid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getMemberInfo(groupid,memberid);
}

void CDoodMemberManager::setMemberInfo(QString groupid, QString memberid, QString operate, QString remark)
{
    qDebug() << Q_FUNC_INFO<<operate;
    mTempMember.id=memberid;
    mTempMember.groupid=groupid;
    mTempMember.member_type="";
    mTempMember.remark="";
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
        if(remark.toStdString().substr(0,1)==" "){
            emit wordsOutOfLimited("群名片首字符不能为空格");
            return;
        }
        if(remark.size()>22){
            emit wordsOutOfLimited("群名片字数不能超过16");
            return;
        }
        qDebug() << Q_FUNC_INFO<<remark;
        mTempMember.member_type=="";
        mTempMember.remark=remark;
    }
    m_pClient->setMemberInfo(mTempMember);
}

QString CDoodMemberManager::groupId()
{
    return mGroupid;
}

void CDoodMemberManager::selectMember(QString id)
{
    CDoodMemberItem *tmpItem = memberListMap.value(id);
    if(tmpItem!=NULL){
        if(tmpItem->isChoose()==""){
            m_TipMember.push_back(id);
            tmpItem->setIsChoose("123");
        }
        else{
            tmpItem->setIsChoose("");
            for(size_t i=0;i<m_TipMember.size();++i){
                if(m_TipMember[i]==id){
                    m_TipMember.erase(m_TipMember.begin()+i);
                }
            }
        }
    }
    tmpItem = groupAdminListMap.value(id);
    if(tmpItem!=NULL){
        if(tmpItem->isChoose()==""){
            tmpItem->setIsChoose("123");
        }
        else{
            tmpItem->setIsChoose("");
        }
    }
    tmpItem = groupLeaderListMap.value(id);
    if(tmpItem!=NULL){
        if(tmpItem->isChoose()==""){
            tmpItem->setIsChoose("123");
        }
        else{
            tmpItem->setIsChoose("");
        }
    }
}

void CDoodMemberManager::clearMember()
{
    for(size_t i=0;i<m_TipMember.size();++i){
        CDoodMemberItem *tmpItem = memberListMap.value(m_TipMember[i]);
        if(tmpItem!=NULL){
            tmpItem->setIsChoose("");
        }
        tmpItem = groupAdminListMap.value(m_TipMember[i]);
        if(tmpItem!=NULL){
            tmpItem->setIsChoose("");
        }
        tmpItem = groupLeaderListMap.value(m_TipMember[i]);
        if(tmpItem!=NULL){
            tmpItem->setIsChoose("");
        }

    }
    m_TipMember.clear();
}

QList<QString> CDoodMemberManager::getTipMember()
{
    return m_TipMember;
}

QString CDoodMemberManager::getTipName()
{
    CDoodMemberItem *tmpItem =NULL;
    QString name;
    for(size_t i=0;i<m_TipMember.size();++i){
        tmpItem=memberListMap.value(m_TipMember[i]);
        if(tmpItem!=NULL){
            name=name+"@"+tmpItem->remark()+"\x1D";
        }
    }
    return name;
}

void CDoodMemberManager::onGetThePresentGroupid(QString groupid)
{
   m_ThePresentGroupid=groupid;
   clearMemberList();
}

void CDoodMemberManager::onGetMemberListResult(QString result, MemberList memberList)
{   
    if(result=="获取成员列表成功"){
        if(memberList.size()>0){
            if(memberList[0].groupid==m_ThePresentGroupid){
                setMemberSize(QString::number(memberList.size()));
                mMy_Id=getMyId();
                setMy_Type("1");
                for(size_t i=0;i<memberList.size();i++)
                {
                    mGroupid=memberList[0].groupid;
                    addMember(memberList[i]);
                    emit itemCountChanged();
                }
                emit getMemberListResult("获取成员列表成功");
            }
        }
    }
    else{
        emit getMemberListResult("获取成员列表失败");
    }
}

void CDoodMemberManager::onGetMemberInfoResult(QString result, Member member)
{
    qDebug() << Q_FUNC_INFO<<result;
    emit getMemberInfoResult(member.name);
}

void CDoodMemberManager::onRemoveMemberResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<result;
    if(result=="移除群成员成功"){
        int size;
        size=memberSize().toInt()-1;
        setMemberSize(QString::number(size));
    }
    emit removeMemberResult(result);
}

void CDoodMemberManager::onSetMemberInfoResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<result;
    if(result=="设置成员信息成功"){

    }
}

void CDoodMemberManager::onMemberInfoChanged(QString groupid, Member member)
{
    qDebug() << Q_FUNC_INFO<<groupid<<"  "<<member.remark<<" "<<member.team<<" "<<member.name;
    if(groupid==mGroupid){
        CDoodMemberItem *item = memberListMap.value(member.id);
        if(item!=NULL){
            qDebug() << Q_FUNC_INFO<<member.id;
            if(member.team==""){
                qDebug() << Q_FUNC_INFO<<item->team();
                member.team=item->team();
            }
            if(member.thumbAvatar==""){
                qDebug() << Q_FUNC_INFO<<item->thumbAvatar();
                member.thumbAvatar=item->thumbAvatar();
            }
            if(member.remark==""||member.remark=="#"){
                qDebug() << Q_FUNC_INFO<<item->remark();
                member.remark=item->remark();
                member.team=item->team();
            }
            if(member.member_type=="0"){
                member.member_type=item->member_type();
            }
            emit setMemberInfoResult(member.id,member.remark,member.member_type);
        }
        removeMemberItem(member.id);
        addMember(member);
    }

}

void CDoodMemberManager::onMemberAvatarChanged(QString userid, QString avatar)
{
    //    qDebug() << Q_FUNC_INFO<<userid;
    CDoodMemberItem *item = memberListMap.value(userid,NULL);
    if(item!=NULL){
        item->setThumbAvatar(avatar);
    }
    item=groupAdminListMap.value(userid,NULL);
    if(item!=NULL){
        item->setThumbAvatar(avatar);
    }
    item=groupLeaderListMap.value(userid,NULL);
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
            groupLeaderListMap.remove(mem.id);
            //            addMember(mem);
            qDebug() << Q_FUNC_INFO<<"sss";

        }
        CDoodMemberItem *item=groupAdminListMap.value(userid,NULL);
        if(item!=NULL){
            //            Member mem;
            //            mem.name=item->name();
            //            mem.id=item->id();
            //            if(userid==mMy_Id){
            //                setMy_Type("3");
            //            }
            //            mem.thumbAvatar=item->thumbAvatar();
            //            mem.gender=item->gender();
            //            mem.groupid=item->groupid();
            //            mem.remark=item->remark();
            //            mem.member_type="3";
            //            mem.team=item->team();
            removeItem(item);
            groupAdminListMap.remove(userid);
            //            addMember(mem);
            qDebug() << Q_FUNC_INFO<<"sss";
        }
        item = memberListMap.value(userid,NULL);
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
            memberListMap.remove(userid);
            addMember(mem);
            qDebug() << Q_FUNC_INFO<<"sss";
        }
    }
}

void CDoodMemberManager::onMemberListChanged(QString operType, QString GroupId, MemberList memberlist)
{
    qDebug() << Q_FUNC_INFO<<"sss";
    if(operType=="32"||operType=="33"){
        for(size_t i=0;i<memberlist.size();++i){
            qDebug() << Q_FUNC_INFO<<"sss1"<<memberlist[i].id<<memberlist[i].name;
            CDoodMemberItem *item = memberListMap.value(memberlist[i].id,NULL);

            if(item!=NULL){
                qDebug() << Q_FUNC_INFO<<"sss2";
                if(item->groupid()==GroupId){
                    qDebug() << Q_FUNC_INFO<<"sss3";
                    removeMemberItem(memberlist[i].id);
                    int size;
                    size=memberSize().toInt()-1;
                    setMemberSize(QString::number(size));
                }
            }
            item=groupAdminListMap.value(memberlist[i].id,NULL);
            if(item!=NULL){
                if(memberlist[i].groupid==GroupId){
                    removeMemberItem(memberlist[i].id);
                    int size;
                    size=memberSize().toInt()-1;
                    setMemberSize(QString::number(size));
                }
            }
        }
    }
    if(operType=="1"){
        if(GroupId==mGroupid){
            for(size_t i=0;i<memberlist.size();++i){
                addMember(memberlist[i]);
                emit itemCountChanged();
            }
            int size;
            size=memberSize().toInt()+memberlist.size();
            setMemberSize(QString::number(size));
        }
    }
}
void CDoodMemberManager::clearMemberList()
{
    qDebug() << Q_FUNC_INFO;
    QList<CDoodMemberItem*>  itemList = memberListMap.values();
    qDebug() << Q_FUNC_INFO<<itemList.size();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    memberListMap.clear();

    itemList = groupLeaderListMap.values();
    qDebug() << Q_FUNC_INFO<<itemList.size();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    groupLeaderListMap.clear();

    itemList = groupAdminListMap.values();
    qDebug() << Q_FUNC_INFO<<itemList.size();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    groupAdminListMap.clear();
    reset();
    setMy_Type("1");
    setMemberSize("");
    mGroupid="";
}
void CDoodMemberManager::addMember(Member mem)
{
    //TODO
    CDoodMemberItem *item = memberListMap.value(mem.id,NULL);
    if(item!=NULL){
        return;
    }
    item=groupLeaderListMap.value(mem.id,NULL);
    if(item!=NULL){
        return;
    }
    item=groupAdminListMap.value(mem.id,NULL);
    if(item!=NULL){
        return;
    }
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
    //    if(mem.member_type=="1"){
    insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
    memberListMap[mem.id] = tmpItem;
    //    }
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
    connect(m_pClient, SIGNAL(getThePresentGroupid(QString)), this, SLOT(onGetThePresentGroupid(QString)));
    connect(m_pClient, SIGNAL(getMemberListResult(QString, MemberList)), this, SLOT(onGetMemberListResult(QString, MemberList)));
    connect(m_pClient, SIGNAL(removeMemberResult(QString)), this, SLOT(onRemoveMemberResult(QString)));
    connect(m_pClient, SIGNAL(setMemberInfoResult(QString)), this, SLOT(onSetMemberInfoResult(QString)));
    connect(m_pClient, SIGNAL(memberInfoChanged(QString,Member)), this, SLOT(onMemberInfoChanged(QString,Member)));
    connect(m_pClient, SIGNAL(memberAvatarChanged(QString,QString)), this, SLOT(onMemberAvatarChanged(QString,QString)));
    connect(m_pClient, SIGNAL(groupLeaderChanged(QString,QString,QString,QString)), this, SLOT(onGroupLeaderChanged(QString,QString,QString,QString)));
    connect(m_pClient, SIGNAL(memberListChanged(QString,QString,MemberList)), this, SLOT(onMemberListChanged(QString,QString,MemberList)));
    connect(m_pClient, SIGNAL(getMemberInfoResult(QString,Member)), this, SLOT(onGetMemberInfoResult(QString,Member)));

}


