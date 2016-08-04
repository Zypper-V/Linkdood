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

    //    itemList = appListMap.values();
    //    for(int i= 0;i< itemList.size();i++){
    //        removeItem(itemList.value(i));
    //        delete itemList.value(i);
    //    }
    //    appListMap.clear();
}

void CDoodContactManager::getContactInfo(QString userId)
{
    m_pClient->getContactInfo(userId);
}

bool CDoodContactManager::isFriend(QString id)
{
    QMap<QString, CDoodContactItem*>::iterator it = contactListMap.find(id);
    if(it == contactListMap.end())
        return false;
    return true;
}

QString CDoodContactManager::findName(QString userId)
{
    if(userId !=""){
        CDoodContactItem* item =  contactListMap.value(userId);
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
            qDebug() << Q_FUNC_INFO<<"ssss1";
        }
        else{
            qDebug() << Q_FUNC_INFO<<"ssss2";
            tmpItem->setIsChoose("");
        }
    }
    //    tmpItem->clearIsChoose("");
    CDoodContactItem *item = starContactListMap.value(id);
    if(item != NULL){
        if(item->isChoose()==""){
            item->setIsChoose("1");
        }
        else{
            item->setIsChoose("");
        }
        //        item->clearIsChoose("");
    }
}

void CDoodContactManager::clearMember()
{
    for(size_t i=0;i<m_member.size();++i){
        CDoodContactItem *tmpItem = contactListMap.value(m_member[i]);
        tmpItem->setIsChoose("");
        CDoodContactItem *item = starContactListMap.value(tmpItem->id(),NULL);
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
            item = starContactListMap.value(userid);
            if(item != NULL){
                item->setThumbAvatar(avatar);
            }
        }
    }
}

void CDoodContactManager::onContactListChanged(int oper, ContactList contacts)
{

    for(size_t i=0;i<contacts.size();i++)
    {
        qDebug() << Q_FUNC_INFO << "avater:"<<contacts[i].thumbAvatar;
        if(!contactListMap.contains(contacts[i].id)){
            addContact(contacts[i]);

        }else{
            modifyContact(contacts[i]);
        }
    }
    emit itemCountChanged();
}

void CDoodContactManager::addContact(Contact user)
{
    //TODO
    CDoodContactItem *tmpItem = new CDoodContactItem(this);
    CDoodContactItem *starItem = NULL;

    QString temp;
    temp.sprintf("%c",user.team);

    qDebug() << Q_FUNC_INFO<<"================pingyin:"<<user.pinyin<<"avater:"<<user.avatar<<"th:"<<user.thumbAvatar<<"name:"<<user.name;
    tmpItem->setId(user.id);
    tmpItem->setGender(user.gender);
    tmpItem->setName(user.name);
    tmpItem->setThumbAvatar(user.thumbAvatar);
    tmpItem->setIsStar(QString::number(user.isStar));
    tmpItem->setSection(temp);

    if(user.isStar == 1){
        starItem = new CDoodContactItem(this);

        starItem->setId(user.id);
        starItem->setGender(user.gender);
        starItem->setName(user.name);
        starItem->setThumbAvatar(user.thumbAvatar);
        starItem->setIsStar(QString::number(user.isStar));
        starItem->setSection("v标好友");

        //插入v标末尾
        insertItem(starContactListMap.size()+appListMap.size(),starItem);

        starContactListMap[user.id] = starItem;
    }

    insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
    contactListMap[user.id] = tmpItem;
}

void CDoodContactManager::modifyContact(Contact user)
{
    qDebug()<<Q_FUNC_INFO<<"userName:"<<user.name<<"isSar:"<<user.isStar;
    //TODO
    CDoodContactItem *tmpItem = contactListMap.value(user.id);
    if(tmpItem ==NULL){
        return;
    }
    if(user.isStar != tmpItem->isStar().toInt()){
        if(user.isStar != 1){
            CDoodContactItem *item = starContactListMap.value(tmpItem->id(),NULL);
            if(item != NULL){
                removeItem(indexOf(item));
                starContactListMap.remove(user.id);
                delete item;
            }
            tmpItem->setIsStar("0");
        }else{
            CDoodContactItem* starItem = new CDoodContactItem(this);
            starItem->setId(user.id);
            starItem->setGender(tmpItem->gender());
            starItem->setName(tmpItem->name());
            starItem->setThumbAvatar(tmpItem->thumbAvatar());
            starItem->setIsStar(QString::number(user.isStar));
            starItem->setSection("v标好友");
            //插入v标末尾
            insertItem(starContactListMap.size()+appListMap.size(),starItem);
            starContactListMap[user.id] = starItem;
            tmpItem->setIsStar("1");
        }
    }
    if(user.name != tmpItem->name() &&(user.name != "")){

        //handle
        if(user.team >0){
            QString temp;
            temp.sprintf("%c",user.team);
            if(temp != ""){

                int index = indexofTeam(temp);

                CDoodContactItem* item = new CDoodContactItem(this);
                item->setId(user.id);
                item->setGender(tmpItem->gender());
                item->setName(user.name);
                item->setThumbAvatar(tmpItem->thumbAvatar());
                item->setIsStar(QString::number(user.isStar));
                item->setSection(temp);
                insertItem(index,item);

                delete takeItemAt(indexOf(tmpItem));
                contactListMap[user.id] = item;
                item = starContactListMap.value(user.id);
                if(item != NULL){
                    item->setName(user.name);
                }
            }
        }else{
            tmpItem->setName(user.name);
            CDoodContactItem*  item = starContactListMap.value(user.id);
            if(item != NULL){
                item->setName(user.name);
            }
        }
    }
    if(user.thumbAvatar != tmpItem->thumbAvatar() &&(user.thumbAvatar != "")){
        if(user.thumbAvatar !="" && user.thumbAvatar.endsWith("head/")){
            return ;
        }
        tmpItem->setThumbAvatar(user.thumbAvatar);
        if(tmpItem->isStar() == "1"){
            CDoodContactItem *item = starContactListMap.value(tmpItem->id(),NULL);
            if(item != NULL){
                item->setThumbAvatar(user.thumbAvatar);
            }
        }
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
}

void CDoodContactManager::onContactInfoChanged(int oper, Contact user)
{
    qDebug() << Q_FUNC_INFO;
    switch(oper){
    case 1://add
        addContact(user);
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
    QList<CDoodContactItem *> list = contactListMap.values();
    int len = list.size();
    int index = 0;

    qSort(list.begin(),list.end(),CmpByTeam);
    bool find = false;
    for(index=0;index<len;++index){
        CDoodContactItem * item = list.at(index);
        if(item->sectionKey() == team){
            find = true;
            break;
        }
    }
    if(find){
        return starContactListMap.size()+appListMap.size()+index;
    }else{
        if(team == "#"){
            return list.size()+starContactListMap.size()+appListMap.size();
        }else{
            for(index = 0;index<len;++index){
                CDoodContactItem * item = list.at(index);
                if(item->sectionKey() > team){
                    return index+starContactListMap.size()+appListMap.size();
                }
            }
        }
    }
}

CDoodContactItem *CDoodContactManager::itemById(QString id)
{
    return contactListMap.value(id,NULL);
}

