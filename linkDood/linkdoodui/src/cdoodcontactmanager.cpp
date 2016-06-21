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

void CDoodContactManager::onContactListChanged(int oper, ContactList contacts)
{
    qDebug() << Q_FUNC_INFO << "conactListSize" << contacts.size();
    for(size_t i=0;i<contacts.size();i++)
    {
        if(!contactListMap.contains(contacts[i].id)){

            CDoodContactItem *tmpItem = new CDoodContactItem(this);
            tmpItem->setId(contacts[i].id);
            tmpItem->setGender(contacts[i].gender);
            tmpItem->setName(contacts[i].name);
            tmpItem->setThumbAvatar(contacts[i].thumbAvatar);
            qDebug() << Q_FUNC_INFO << "contacts avatar111:" << contacts[i].thumbAvatar;
            contactListMap[contacts[i].id] = tmpItem;
            addItem(tmpItem);
        }else{
            CDoodContactItem *tmpItem = contactListMap.value(contacts[i].id);
            tmpItem->setId(contacts[i].id);
            tmpItem->setGender(contacts[i].gender);
            tmpItem->setName(contacts[i].name);
            tmpItem->setThumbAvatar(contacts[i].thumbAvatar);
        }

    }
    emit itemCountChanged();
}

void CDoodContactManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(contactListChanged(int, ContactList)), this, SLOT(onContactListChanged(int, ContactList)));
}

