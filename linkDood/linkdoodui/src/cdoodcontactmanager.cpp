#include "cdoodcontactmanager.h"
#include"cdoodcontactitem.h"


CDoodContactManager::CDoodContactManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodContactManager*>();
    initConnect();
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
    }
    contactListMap.clear();

    itemList = starContactListMap.values();
    for(int i= 0;i< itemList.size();i++){
        removeItem(itemList.value(i));
    }
    starContactListMap.clear();
}

void CDoodContactManager::updateContactInfo(QString userId, QString operStar, QString remark)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->updateContactInfo(userId,operStar,remark);
}

void CDoodContactManager::onContactListChanged(int oper, ContactList contacts)
{
    qDebug() << Q_FUNC_INFO << "conactListSize" << contacts.size();
    for(size_t i=0;i<contacts.size();i++)
    {
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

    tmpItem->setId(user.id);
    tmpItem->setGender(user.gender);
    tmpItem->setName(user.name);
    tmpItem->setThumbAvatar(user.thumbAvatar);
    tmpItem->setIsStar(QString::number(user.isStar));
    tmpItem->setSection(user.pinyin);

    if(user.isStar == 1){
        starItem = new CDoodContactItem(this);

        starItem->setId(user.id);
        starItem->setGender(user.gender);
        starItem->setName(user.name);
        starItem->setThumbAvatar(user.thumbAvatar);
        starItem->setIsStar(QString::number(user.isStar));
        starItem->setSection("v标好友");

        //插入v标末尾
        insertItem(starContactListMap.size(),starItem);

        starContactListMap[user.id] = starItem;
    }

    insertItem(indexOfSection(tmpItem->sectionKey()),tmpItem);
    contactListMap[user.id] = tmpItem;
}

void CDoodContactManager::modifyContact(Contact user)
{
    //TODO
    CDoodContactItem *tmpItem = contactListMap.value(user.id);
    tmpItem->setId(user.id);
    tmpItem->setGender(user.gender);
    tmpItem->setName(user.name);
    tmpItem->setThumbAvatar(user.thumbAvatar);
    tmpItem->setSection("");
    tmpItem->setIsStar(QString::number(user.isStar));

    CDoodContactItem *item = starContactListMap.value(tmpItem->id(),NULL);
    if(item != NULL && user.isStar == 2){
        removeItem(indexOf(item));
        starContactListMap.remove(user.id);
    }else if(item == NULL && user.isStar == 1){

        CDoodContactItem* starItem = new CDoodContactItem(this);
        starItem->setId(user.id);
        starItem->setGender(user.gender);
        starItem->setName(user.name);
        starItem->setThumbAvatar(user.thumbAvatar);
        starItem->setIsStar(QString::number(user.isStar));
        starItem->setSection("v标好友");
        //插入v标末尾
        insertItem(starContactListMap.size(),starItem);
        starContactListMap[user.id] = starItem;
    }else{
        //TODO
    }
}

void CDoodContactManager::removeContact(Contact user)
{
    //TODO
    CDoodContactItem *item = starContactListMap.value(user.id,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        starContactListMap.remove(user.id);
    }
    item = contactListMap.value(user.id,NULL);
    if(item != NULL){
        removeItem(indexOf(item));
        contactListMap.remove(user.id);
    }
}

void CDoodContactManager::onContactInfoChanged(int oper, Contact user)
{
    qDebug() << Q_FUNC_INFO;
    switch(oper){
    case 1://add
        addContact(user);
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

void CDoodContactManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(contactListChanged(int, ContactList)), this, SLOT(onContactListChanged(int, ContactList)));
    connect(m_pClient, SIGNAL(contactInfoChanged(int, Contact)), this, SLOT(onContactInfoChanged(int, Contact)));
    connect(m_pClient, SIGNAL(contactOnlineChanged(QString , QString)), this, SLOT(onContactOnlineChanged(QString , QString)));
}

int CDoodContactManager::indexOfSection(QString sectnion)
{
    int index = starContactListMap.size();
    for(;index < itemCount();++index){
        CDoodContactItem *tmpItem = (CDoodContactItem *)itemOfIndex(index);
        if(tmpItem->sectionKey() == sectnion){
            return index;
        }
    }
    return index;
}

