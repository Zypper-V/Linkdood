#include "cdoodaddcontactmanager.h"
#include"cdoodcontactitem.h"

CDoodAddContactManager::CDoodAddContactManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodAddContactManager*>();
    initConnect();
}

void CDoodAddContactManager::searchFromNet(QString key)
{
    qDebug() << Q_FUNC_INFO << "searchText:" << key;
    m_pClient->searchFromNet(key);
}

void CDoodAddContactManager::addContact(QString userid, QString remark, QString info)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->addContact(userid, remark, info);
}

void CDoodAddContactManager::onSearchFromNet(int code, ContactList user, ContactList group)
{
    qDebug() << Q_FUNC_INFO;
    emit searchFromNetResult(user.size() + group.size());

    if(code != 0)
        return;
    int i = 0;
    reset();
    contactListClear();
    for(; i < user.size(); i++)
    {
        qDebug() << "user gender:" << user[i].gender << "    timeZone:" << user[i].timeZone << "   id:" << user[i].id << ",   name:" << user[i].name << "    avatar:" << user[i].avatar << "    extend:" << user[i].extends << "   thumbAvatar:" << user[i].thumbAvatar;
        CDoodContactItem *tmpItem = new CDoodContactItem(this);

        if(user[i].gender == "0")
        {
            tmpItem->setGender("保密");
        }
        else if(user[i].gender == "1")
        {
            tmpItem->setGender("男");
        }
        else if(user[i].gender == "2")
        {
            tmpItem->setGender("女");
        }
        tmpItem->setTimeZone(QString::number(user[i].timeZone));
        tmpItem->setId(user[i].id);
        tmpItem->setName(user[i].name);
        tmpItem->setAvatar(user[i].avatar);
        tmpItem->setExtend(user[i].extends);
        tmpItem->setThumbAvatar(user[i].thumbAvatar);
        tmpItem->setUserOrGroup(QString::number(1)); //这里用1表示联系人，用2表示群
        insertItem(itemCount(),tmpItem);
        m_contactListMap[user[i].id] = tmpItem;
    }
    for(int j = 0; j < group.size(); j++)
    {
        qDebug() << "group gender:" << group[j].gender << "    timeZone:" << group[j].timeZone << "   id:" << group[j].id << ",   name:" << group[j].name << "    avatar:" << group[j].avatar << "    extend:" << group[j].extends << "   thumbAvatar:" << group[j].thumbAvatar;

        CDoodContactItem *tmpItem = new CDoodContactItem(this);

        tmpItem->setGender(group[j].gender);
        tmpItem->setTimeZone(QString::number(group[j].timeZone));
        tmpItem->setId(group[j].id);
        tmpItem->setName(group[j].name);
        tmpItem->setAvatar(group[j].avatar);
        tmpItem->setExtend(group[j].extends);
        tmpItem->setThumbAvatar(group[j].thumbAvatar);
        tmpItem->setUserOrGroup(QString::number(2));
        insertItem(itemCount(),tmpItem);
        m_contactListMap[group[j].id] = tmpItem;
    }
}

void CDoodAddContactManager::onAddContact(int code)
{

}

void CDoodAddContactManager::initConnect()
{
    connect(m_pClient, SIGNAL(searchFromNetResult(int,ContactList, ContactList)), this, SLOT(onSearchFromNet(int,ContactList, ContactList)));
    connect(m_pClient, SIGNAL(addContactResult(int)), this, SLOT(onAddContact(int)));
}

void CDoodAddContactManager::contactListClear()
{
    for(QMap<QString, CDoodContactItem*>::iterator it = m_contactListMap.begin(); it != m_contactListMap.end(); it++)
    {
        removeItem(m_contactListMap[it.key()]);
        delete m_contactListMap[it.key()];
    }
    m_contactListMap.clear();

}

