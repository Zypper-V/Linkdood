#include "cdoodcontactmanager.h"
#include"cdoodcontactitem.h"
#include <QtAlgorithms>

CDoodContactManager::CDoodContactManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodContactManager*>();
    initConnect();

    appListMap.clear();

    CDoodContactItem *tmpItem = new CDoodContactItem(this);
    tmpItem->setName("我的电脑");
    tmpItem->setId(QString::number(COMPUTER_CHAT));
    tmpItem->setSection("app");
    addItemBegin(tmpItem);
    appListMap[tmpItem->id()] = tmpItem;

    tmpItem = new CDoodContactItem(this);
    tmpItem->setName("系统消息");
    tmpItem->setId("3");
    tmpItem->setSection("app");
    addItem(tmpItem);
    appListMap["3"] = tmpItem;

    tmpItem = new CDoodContactItem(this);
    tmpItem->setName("群");
    tmpItem->setId("2");
    tmpItem->setSection("app");
    addItem(tmpItem);
    appListMap["2"] = tmpItem;


}

void CDoodContactManager::getContactInforFromList(QString id, QString &name, QString &avater)
{
    qDebug()<<Q_FUNC_INFO;
    if(id != ""){
        CDoodContactItem* item = contactListMap.value(id,NULL);
        if(item != NULL){
            avater =  item->thumbAvatar();
            name   = item->name();
            return;
        }
        item = starContactListMap.value(id,NULL);
        if(item != NULL){
            avater =  item->thumbAvatar();
            name   = item->name();
        }
    }
}

CDoodContactManager::~CDoodContactManager()
{

}

void CDoodContactManager::getContactList()
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->getContactList();
}

void CDoodContactManager::clearChatList()
{
    qDebug() << Q_FUNC_INFO;
    QList<CDoodContactItem*>  itemList = contactListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    contactListMap.clear();

    itemList = starContactListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
        delete itemList.value(i);
    }
    starContactListMap.clear();
}

void CDoodContactManager::getContactInfo(QString userId)
{
    m_pClient->getContactInfo(userId);
}

bool CDoodContactManager::isFriend(QString id)
{
    CDoodContactItem* item = contactListMap.value(id,NULL);
    if(item != NULL){
        return true;
    }else{
        item = starContactListMap.value(id,NULL);
        if(item != NULL){
            return true;
        }
    }
    return false;
}

QString CDoodContactManager::findName(QString userId)
{
    if(userId !=""){
        CDoodContactItem* item =  contactListMap.value(userId,NULL);
        if(item != NULL){
            return item->name();
        }
        item =  starContactListMap.value(userId,NULL);
        if(item != NULL){
            return item->name();
        }
    }
    return "";
}

void CDoodContactManager::updateContactInfo(QString userId, QString operStar, QString remark)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->updateContactInfo(userId,operStar,remark);
}

void CDoodContactManager::removeContact(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->removeContact(userid);
}

void CDoodContactManager::selectMember(QString id)
{
    qDebug() << Q_FUNC_INFO<<"ssssssssssssss";
    CDoodContactItem *tmpItem = contactListMap.value(id);
    if(tmpItem!=NULL){
        if(tmpItem->isChoose()==""){
            m_member.push_back(id);
            tmpItem->setIsChoose("1");
        }
        else{
            tmpItem->setIsChoose("");
        }
    }
    CDoodContactItem *item = starContactListMap.value(id);
    if(item != NULL){
        if(item->isChoose()==""){
            m_member.push_back(id);
            item->setIsChoose("1");
        }
        else{
            item->setIsChoose("");
        }
    }
}

void CDoodContactManager::clearMember()
{

    for(size_t i=0;i<m_member.size();++i){
        CDoodContactItem *tmpItem = contactListMap.value(m_member[i],NULL);
        if(tmpItem != NULL){
            tmpItem->setIsChoose("");
        }
        CDoodContactItem *item = starContactListMap.value(m_member[i],NULL);
        if(item != NULL){
            item->setIsChoose("");
        }
    }
    m_member.clear();
}

void CDoodContactManager::onAvatarChanged(QString userid, QString avatar)
{
    if(avatar != ""){
        CDoodContactItem *item = contactListMap.value(userid);
        if(item != NULL){
            item->setThumbAvatar(avatar);
        }
        item = starContactListMap.value(userid);
        if(item != NULL){
            item->setThumbAvatar(avatar);
        }
    }
}

void CDoodContactManager::onContactListChanged(int oper, ContactList contacts)
{
    bool isInit = contacts.size()>1;
    for(size_t i=0;i<contacts.size();i++)
    {
        CDoodContactItem* item =  itemById(contacts[i].id);
        if(item != NULL){
            modifyContact(contacts[i]);
        }else{
            addContact(contacts[i],isInit);
        }
    }
    emit itemCountChanged();
}

void CDoodContactManager::addContact(Contact user,bool isInit)
{
    //TODO
    CDoodContactItem *tmpItem = itemById(user.id);
    if(tmpItem != NULL){
        return;
    }
    tmpItem = new CDoodContactItem(this);
    QString temp;
    temp.sprintf("%c",user.team);

    if(user.thumbAvatar.endsWith("head/")){
        user.thumbAvatar = "";
    }
    tmpItem->setId(user.id);
    tmpItem->setGender(user.gender);
    tmpItem->setName(user.name);
    tmpItem->setThumbAvatar(user.thumbAvatar);
    tmpItem->setIsStar(QString::number(user.isStar));
    tmpItem->setSection(temp);

    if(user.isStar == 1){
        tmpItem->setSection("v标好友");
        //插入v标末尾
        insertItem(starContactListMap.size()+appListMap.size(),tmpItem);
        starContactListMap[user.id] = tmpItem;
    }
    else{
        if(isInit){
            insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
        }else{
            int index = indexofTeam(tmpItem->sectionKey());
            insertItem(index,tmpItem);
        }

        contactListMap[user.id] = tmpItem;
    }
}

void CDoodContactManager::modifyContact(Contact user)
{
    qDebug()<<Q_FUNC_INFO<<"userName:"<<user.name<<"isSar:"<<user.isStar;
    //TODO
    if(user.thumbAvatar.endsWith("head/")){
        user.thumbAvatar = "";
    }
    CDoodContactItem *tmpItem = itemById(user.id);
    if(tmpItem ==NULL){
        return;
    }
    if(user.isStar != tmpItem->isStar().toInt()){
        if(user.isStar != 1){
            removeItem(indexOf(tmpItem));
            starContactListMap.remove(user.id);
            tmpItem->setIsStar("0");

            QString temp;
            temp.sprintf("%c",user.team);
            tmpItem->setSection(temp);
            if(temp == "#"){
                addItem(tmpItem);
            }else{
                insertItem(indexofTeam(temp),tmpItem);
            }
            contactListMap[user.id] = tmpItem;
        }else{
            takeItemAt(indexOf(tmpItem));
            //插入v标末尾
            tmpItem->setIsStar(QString::number(user.isStar));
            tmpItem->setSection("v标好友");
            insertItem(starContactListMap.size()+appListMap.size(),tmpItem);
            starContactListMap[user.id] = tmpItem;
            contactListMap.remove(user.id);
        }
    }
    if(user.name != tmpItem->name() &&(user.name != "")){

        //handle
        tmpItem->setName(user.name);
        if(user.team >0){
            QString temp;
            temp.sprintf("%c",user.team);
            if(temp != ""){
                if(tmpItem->isStar() != "1"){
                    removeItem(indexOf(tmpItem));
                    tmpItem->setSection(temp);
                    if(temp == "#"){
                        addItem(tmpItem);
                    }else{
                        insertItem(indexofTeam(temp),tmpItem);
                    }

                }
            }
        }
    }
    if(user.thumbAvatar != tmpItem->thumbAvatar() &&(user.thumbAvatar != "")){
        if(user.thumbAvatar !="" && user.thumbAvatar.endsWith("head/")){
            return ;
        }
        tmpItem->setThumbAvatar(user.thumbAvatar);
    }
}

void CDoodContactManager::removeContact(Contact user)
{
    //TODO
    CDoodContactItem *item = starContactListMap.value(user.id,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        starContactListMap.remove(user.id);
        delete item;
    }
    item = contactListMap.value(user.id,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        contactListMap.remove(user.id);
        delete item;
    }
    emit removeContactOper(user.id);
}

void CDoodContactManager::onContactInfoChanged(int oper, Contact user)
{
    qDebug() << Q_FUNC_INFO;
    emit contactInfoChanged();
    switch(oper){
    case 1://add
        addContact(user,false);
        emit addContactReslut(user.id);
        break;
    case 2://modify
        modifyContact(user);
        break;
    case 3://delete
        removeContact(user);
        break;
    }

}

void CDoodContactManager::onContactOnlineChanged(QString id, QString deviceText)
{
    qDebug() << Q_FUNC_INFO;
    CDoodContactItem *item = starContactListMap.value(id,NULL);
    if(item != NULL){
        item->setOnlineStatus(deviceText);
    }
    item = contactListMap.value(id,NULL);
    if(item != NULL){
        item->setOnlineStatus(deviceText);
    }
}

void CDoodContactManager::onUpdateContactInfo(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit updateContactInfoResult(code);
}

void CDoodContactManager::onRemoveContact(int code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeContactResult(code);
}

void CDoodContactManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(chatAvatarChanged(QString,QString)), this, SLOT(onAvatarChanged(QString,QString)));
    connect(m_pClient, SIGNAL(contactListChanged(int, ContactList)), this, SLOT(onContactListChanged(int, ContactList)));
    connect(m_pClient, SIGNAL(contactInfoChanged(int, Contact)), this, SLOT(onContactInfoChanged(int, Contact)));
    connect(m_pClient, SIGNAL(contactOnlineChanged(QString , QString)), this, SLOT(onContactOnlineChanged(QString , QString)));
    connect(m_pClient, SIGNAL(updateContactInfoResult(int)), this, SLOT(onUpdateContactInfo(int)));
    connect(m_pClient, SIGNAL(removeContactResult(int)), this, SLOT(onRemoveContact(int)));
}

int CDoodContactManager::indexOfSection(QString sectnion)
{
    int index = starContactListMap.size()+appListMap.size();
    for(;index < itemCount();++index){
        CDoodContactItem *tmpItem = (CDoodContactItem *)itemOfIndex(index);
        if(tmpItem->sectionKey() == sectnion){
            return index;
        }
    }
    return index;
}

bool CmpByTeam(CDoodContactItem * first, CDoodContactItem * second)
{
    if(first->sectionKey() == "#"){
        return false;
    }
    return  first->sectionKey() <= second->sectionKey();
}

int CDoodContactManager::indexofTeam(QString team)
{

    int len = _list->size();
    if(len == 0 || team == "#"){
        return len;
    }
    int i = appListMap.size()+starContactListMap.size();
    for(;i<len;++i){
        CDoodContactItem * item  = (CDoodContactItem *)_list->at(i);
        if(item != NULL){
            if(item->sectionKey() >= team){
                return i;
            }
        }
    }
    return len;
//    QList<CDoodContactItem *> list = contactListMap.values();
//    int len = list.size();
//    int index = 0;

//    qSort(list.begin(),list.end(),CmpByTeam);
//    bool find = false;
//    for(index=0;index<len;++index){
//        CDoodContactItem * item = list.at(index);
//        if(item->sectionKey() == team){
//            find = true;
//            break;
//        }
//    }
//    if(find){
//        return starContactListMap.size()+appListMap.size()+index;
//    }else{
//        if(team == "#"){
//            return list.size()+starContactListMap.size()+appListMap.size();
//        }else{
//            for(index = 0;index<len;++index){
//                CDoodContactItem * item = list.at(index);
//                if(item->sectionKey() > team){
//                    return index+starContactListMap.size()+appListMap.size();
//                }
//            }
//        }
//    }
}

CDoodContactItem *CDoodContactManager::itemById(QString id)
{
    CDoodContactItem* item = contactListMap.value(id,NULL);
    if(item != NULL){
        return item;
    }
    return starContactListMap.value(id,NULL);
}

