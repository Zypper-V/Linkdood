#include "cdoodgroupmanager.h"
#include "cdoodgroupitem.h"
#include <QDebug>
#include <QMetaType>

CDoodGroupManager::CDoodGroupManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO<<"22222222222222222222222222";
    qRegisterMetaType<CDoodGroupManager*>();
    initConnect();
    mGetGroupInfo=0;
    m_pUiManager = (linkdoodui_Workspace*)parent;
}

void CDoodGroupManager::getGroupInfoFromList(QString groupId, QString &name, QString &avatar)
{
    if(groupId != ""){
        CDoodGroupItem* item = groupListMap.value(groupId,NULL);
        if(item != NULL){
            name = item->name();
            avatar = item->thumbAvatar();
        }
    }
}

Member CDoodGroupManager::getMemberItemById(QString id)
{
    int len = m_memberList.length();
    Member mem;
    for(int i =0;i<len;i++){
        if(id == m_memberList.at(i).id){
            return m_memberList.at(i);
        }
    }
    return mem;
}

QString CDoodGroupManager::id() const
{
    return mId;
}

QString CDoodGroupManager::setId(const QString &data)
{
    if(mId==data){
        return data;
    }
    mId=data;
    emit idChanged();
    return mId;
}

QString CDoodGroupManager::name() const
{
    return mName;
}

QString CDoodGroupManager::setName(const QString &data)
{
    if(mName==data){
        return data;
    }
    mName=data;
    emit nameChanged();
    return mName;
}

QString CDoodGroupManager::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodGroupManager::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar==data){
        return data;
    }
    mThumbAvatar=data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

QString CDoodGroupManager::createrId() const
{
    return mCreaterId;
}

QString CDoodGroupManager::setCreaterId(const QString &data)
{
    if(mCreaterId==data){
        return data;
    }
    mCreaterId=data;
    emit createrIdChanged();
    return mCreaterId;
}

QString CDoodGroupManager::brief() const
{
    return mBrief;
}

QString CDoodGroupManager::setBrief(const QString &data)
{
    if(mBrief==data){
        return data;
    }
    mBrief=data;
    emit briefChanged();
    return mBrief;
}

QString CDoodGroupManager::bulletin() const
{
    return  mButtletin;
}

QString CDoodGroupManager::setBulletin(const QString &data)
{
    if(mButtletin==data){
        return data;
    }
    mButtletin=data;
    emit bulletinChanged();
    return mButtletin;
}

QString CDoodGroupManager::verify_type() const
{
    return mVerify_type;
}

QString CDoodGroupManager::setVerify_type(const QString &data)
{
    if(mVerify_type==data){
        return data;
    }
    mVerify_type=data;
    emit verify_typeChanged();
    return mVerify_type;
}

QString CDoodGroupManager::is_allow() const
{
    return mIs_allow;
}

QString CDoodGroupManager::setIs_allow(const QString &data)
{
    if(mIs_allow==data){
        return data;
    }
    mIs_allow=data;
    emit is_allowChanged();
    return mIs_allow;
}

bool CDoodGroupManager::isGroupLeader() const
{
    return mIsGroupLeader;
}

bool CDoodGroupManager::setIsGroupLeader(const bool &data)
{
    if(mIsGroupLeader==data){
        return data;
    }
    mIsGroupLeader=data;
    emit isGroupLeaderChanged();
    return mIsGroupLeader;
}

bool CDoodGroupManager::isCreateGroup() const
{
    return mIsCreateGroup;
}

bool CDoodGroupManager::setIsCreateGroup(const bool &data)
{
    if(mIsCreateGroup==data){
        return data;
    }
    mIsCreateGroup=data;
    emit isCreateGroupChanged();
    return mIsCreateGroup;
}

QString CDoodGroupManager::findName(QString groupid)
{
    if(groupid !=""){
        CDoodGroupItem* item =  groupListMap.value(groupid);
        if(item != NULL){
            return item->name();
        }
    }
    return "";
}

void CDoodGroupManager::getMemberList(QString groupid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getMemberList(groupid);
}

void CDoodGroupManager::onGroupListChanged(GroupList groupList)
{
    clearGroupList();
    qDebug() << Q_FUNC_INFO<<"okokokokok";
    Group historygroup;
    foreach (historygroup, groupList) {
        if(!groupListMap.contains(historygroup.id)) {
            CDoodGroupItem *tmpItem = new CDoodGroupItem(this);
            tmpItem->setId(historygroup.id);
            tmpItem->setName(historygroup.name);
            tmpItem->setThumbAvatar(historygroup.thumbAvatar);
            tmpItem->setSection(historygroup.pinyin);
            insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
            groupListMap[historygroup.id] = tmpItem;
        }
    }
}

void CDoodGroupManager::onGetGroupInfoResult(QString result,Group group)
{
    if(mGetGroupInfo==1){
        if(result=="获取群信息成功"){
            qDebug() << Q_FUNC_INFO<<"okokokokok"<<group.id;
            qDebug() << Q_FUNC_INFO<<"okokokokok"<<group.createrid;
            qDebug() << Q_FUNC_INFO<<"okokokokok"<<getMyId();
            if(group.createrid==getMyId())
            {
                setIsGroupLeader(true);
            }
            else{
                setIsGroupLeader(false);
            }
            setId(group.id);
            setName(group.name);
            setBrief(group.brief);
            setBulletin(group.bulletin);
            setThumbAvatar(group.thumbAvatar);
            emit getGroupInfoResult();
            mGetGroupInfo=0;
        }
    }
}

void CDoodGroupManager::onGroupInfoChanged(QString type, Group gp)
{
    //群解散,被踢出群
    if(type=="31"||type=="32"){
        CDoodGroupItem *item = groupListMap.value(gp.id,NULL);
        if(item != NULL){
            removeItem(indexOf(item));
            groupListMap.remove(gp.id);
            delete item;
        }
        return;
    }
    qDebug() << Q_FUNC_INFO<<"okokokokok"<<gp.name<<"    "<<"gp.pinyin:"<<gp.pinyin<<"1111";
    if(!groupListMap.contains(gp.id)) {
        CDoodGroupItem *tmpItem = new CDoodGroupItem(this);
        tmpItem->setId(gp.id);
        tmpItem->setName(gp.name);
        tmpItem->setThumbAvatar(gp.thumbAvatar);
        tmpItem->setSection(gp.pinyin);
        insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
        groupListMap[gp.id] = tmpItem;
    }
    else{
        CDoodGroupItem *tmpItem = groupListMap.value(gp.id);
        if(gp.id==mId){
            setBrief(gp.brief);
            setBulletin(gp.bulletin);
            setName(gp.name);
            setId(gp.id);
//            setThumbAvatar(gp.thumbAvatar);
        }
        tmpItem->setId(gp.id);
        tmpItem->setName(gp.name);
        tmpItem->setThumbAvatar(gp.thumbAvatar);
        tmpItem->setSection(gp.pinyin);
        removeItem(indexOf(tmpItem));
        insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
        groupListMap[gp.id] = tmpItem;
    }
}

void CDoodGroupManager::onRemoveGroupResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    if(result=="成功"){
        CDoodGroupItem *item = groupListMap.value(mId,NULL);
        if(item != NULL){
            removeItem(indexOf(item));
            groupListMap.remove(mId);
            delete item;
        }
    }
    emit removeGroupResult(result);
    emit groupRemoveOrExitResult(mId);
}

void CDoodGroupManager::onTransferGroupResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<"ssss"<<result;
    if(result=="转让群成功"){
    setIsGroupLeader(false);
    }

}

void CDoodGroupManager::onInviteMemberResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit inviteMemberResult(result);
}

void CDoodGroupManager::onAddGroupResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit addGroupResult(result);
}

void CDoodGroupManager::onGetGroupFileListResult(FileInfoList fileInfoList)
{
    qDebug() << Q_FUNC_INFO<<"sssssssss"<<fileInfoList.size();
    emit getGroupFileListResult();

}

void CDoodGroupManager::onSetGroupSetResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<result;
    if(result=="设置成功"){
        setVerify_type(mTemp_verify);
        setIs_allow(mTemp_allow);
    }
}

void CDoodGroupManager::onGetGroupSetResult(QString result, QString verify_type, QString is_allow)
{
    qDebug() << Q_FUNC_INFO<<result<<verify_type<<is_allow;
    setVerify_type(verify_type);
    setIs_allow(is_allow);
}

void CDoodGroupManager::onUploadGroupAvatarResult(QString thum_url, QString src_url)
{
    qDebug() << Q_FUNC_INFO<<thum_url<<":111:"<<src_url;
    Group group;
    group.id=mId;
    mType=1;
    group.thumbAvatar=thum_url;
    group.avatar=src_url;
    m_pClient->setGroupInfo(group);
    emit uploadGroupAvatarResult();
}

void CDoodGroupManager::onGroupAvatarChanged(QString id, QString avatar)
{
    qDebug() << Q_FUNC_INFO<<avatar;
    if(groupListMap.contains(id)){
        CDoodGroupItem *tmpItem = groupListMap.value(id);
        tmpItem->setThumbAvatar(avatar);
    }
    if(id==mId){
        setThumbAvatar(avatar);
    }
}
void CDoodGroupManager::clearGroupList()
{
    qDebug() << Q_FUNC_INFO;
    QList<CDoodGroupItem*>  itemList = groupListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    groupListMap.clear();
}

void CDoodGroupManager::selectmember(QString id)
{
    qDebug() << Q_FUNC_INFO<<"dianjidianji";
    int flag=0;
    for(size_t i=0;i<m_memberList.size();++i){
        if(m_memberList[i].id==id){
            flag=1;
            m_memberList.erase(m_memberList.begin()+i);
        }
    }
    if(flag==0){
        Member mem;
        mem.id=id;
        m_memberList.push_back(mem);
    }
    qDebug() << Q_FUNC_INFO<<m_memberList.size();
}

void CDoodGroupManager::createGroup(QString name)
{
    m_pClient->createGroup("2",name,m_memberList);
    m_memberList.clear();
}

void CDoodGroupManager::getGroupInfo(QString id)
{
    qDebug()<<Q_FUNC_INFO;
    mGetGroupInfo=1;
    m_pClient->getGroupInfo(id);
}

void CDoodGroupManager::removeGroup(QString groupid)
{
    qDebug()<<Q_FUNC_INFO;
    if(isGroupLeader()){
        m_pClient->removeGroup("1",groupid);
    }
    else {
        m_pClient->removeGroup("2",groupid);
    }
}

void CDoodGroupManager::inviteMember()
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->inviteMember(mId,m_memberList);
    m_memberList.clear();
}

void CDoodGroupManager::addGroup(QString groupid)
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->addGroup(groupid,"");
}

void CDoodGroupManager::getGroupList()
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->getGroupList();
}

void CDoodGroupManager::setGroupInfo(int type, QString remark)
{
    Group group;
    group.id=mId;
    mType=type;
    mTemp=remark;
    if(type==1){
       //TODO::avatar
    }
    if(type==2){
        group.name=remark;
        if(remark.size()>16){
            emit wordsOutOfLimited();
            return;
        }
    }
    if(type==3){
        group.brief=remark;
    }
    if(type==4){
        group.bulletin=remark;
    }
    m_pClient->setGroupInfo(group);
}

void CDoodGroupManager::getGroupSet(QString groupid)
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->getGroupSet(groupid);
}

void CDoodGroupManager::setGroupSet(int type, QString remark)
{
    QString verify_type;
    QString is_allow;
    if(type==1){
        verify_type=remark;
        is_allow=mIs_allow;
    }
    else{
        is_allow=remark;
        verify_type=mVerify_type;
    }
    mTemp_allow=is_allow;
    mTemp_verify=verify_type;
    m_pClient->setGroupSet(mId,verify_type,is_allow);
}
void CDoodGroupManager::uploadGroupAvatar(QString path)
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->uploadGroupAvatar(path);

}

void CDoodGroupManager::transMessage(QString localId)
{
    QList<QString> list;
    for(int i=0;i<m_memberList.size();++i){
        list.push_back(m_memberList.at(i).id);
    }
    qDebug()<<Q_FUNC_INFO<<"transMessageSelectContactList:"<<list.size();
    emit transMessageSelectContactList(list,localId);

}

void CDoodGroupManager::getGroupFileList(QString groupid)
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->getGroupFileList(groupid);
}

void CDoodGroupManager::transferGroup(QString groupid, QString userid)
{
    qDebug()<<Q_FUNC_INFO;
    m_pClient->transferGroup(groupid,userid);
}

QString CDoodGroupManager::getMyId()
{
    QString fileName = QString::fromStdString(APP_DATA_PATH)+"config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    QString id;
    id = settings.value("myId","").toString();
    return id;
}

void CDoodGroupManager::onSetGroupInfoResult(QString result)
{
    qDebug() << Q_FUNC_INFO<<result;
    if(result=="设置群信息成功"){
        if(mType==1){
           //TODO::avatar
        }
        if(mType==2){
            setName(mTemp);
        }
        if(mType==3){
            setBrief(mTemp);
        }
        if(mType==4){
            setBulletin(mTemp);
        }
    }
}

void CDoodGroupManager::onCreateGroupResult(QString result)
{
    qDebug() << Q_FUNC_INFO;
    emit createGroupResult(result);
}
void CDoodGroupManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient,SIGNAL(groupListChanged(GroupList)),this,SLOT(onGroupListChanged(GroupList)));
    connect(m_pClient,SIGNAL(createGroupResult(QString)),this,SLOT(onCreateGroupResult(QString)));
    connect(m_pClient,SIGNAL(getGroupInfoResult(QString,Group)),this,SLOT(onGetGroupInfoResult(QString,Group)));
    connect(m_pClient,SIGNAL(groupInfoChanged(QString,Group)),this,SLOT(onGroupInfoChanged(QString,Group)));
    connect(m_pClient,SIGNAL(removeGroupResult(QString)),this,SLOT(onRemoveGroupResult(QString)));
    connect(m_pClient,SIGNAL(inviteMemberResult(QString)),this,SLOT(onInviteMemberResult(QString)));
    connect(m_pClient,SIGNAL(addGroupResult(QString)),this,SLOT(onAddGroupResult(QString)));
    connect(m_pClient,SIGNAL(getGroupFileListResult(FileInfoList)),this,SLOT(onGetGroupFileListResult(FileInfoList)));
    connect(m_pClient,SIGNAL(transferGroupResult(QString)),this,SLOT(onTransferGroupResult(QString)));
    connect(m_pClient,SIGNAL(setGroupInfoResult(QString)),this,SLOT(onSetGroupInfoResult(QString)));
    connect(m_pClient,SIGNAL(getGroupSetResult(QString,QString,QString)),this,SLOT(onGetGroupSetResult(QString,QString,QString)));
    connect(m_pClient,SIGNAL(setGroupSetResult(QString)),this,SLOT(onSetGroupSetResult(QString)));
    connect(m_pClient,SIGNAL(uploadGroupAvatarResult(QString,QString)),this,SLOT(onUploadGroupAvatarResult(QString,QString)));
    connect(m_pClient,SIGNAL(groupAvatarChanged(QString,QString)),this,SLOT(onGroupAvatarChanged(QString,QString)));
}

int CDoodGroupManager::indexOfSection(QString sectnion)
{
    int index = 0;
    //    if(sectnion=="#"){
    //        return itemCount();
    //    }
    for(;index < itemCount();++index){
        CDoodGroupItem *tmpItem = (CDoodGroupItem *)itemOfIndex(index);
        if(tmpItem->sectionKey() == sectnion||tmpItem->sectionKey()=="#"){
            return index;
        }
        else if(tmpItem->sectionKey()[0]>sectnion[0]&&sectnion!="#"){
            return index;
        }
    }

    return index;
}
