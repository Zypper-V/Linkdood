#include "cdoodlocalsearchmanager.h"
#include"cdoodcontactitem.h"

CDoodLocalSearchManager::CDoodLocalSearchManager(LinkDoodClient *client, QObject *parent):
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodLocalSearchManager*>();
    connect(m_pClient, SIGNAL(searchFromLocalResult(int,ContactList, ContactList)), this, SLOT(onSearchFromLocal(int,ContactList, ContactList)));
}

void CDoodLocalSearchManager::searchFromLocal(QString key)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->searchFromLocal(key);
}

void CDoodLocalSearchManager::contactListClear()
{
    for(QMap<QString, CDoodContactItem*>::iterator it = m_contactListMap.begin(); it != m_contactListMap.end(); it++)
    {
        removeItem(m_contactListMap[it.key()]);
        delete m_contactListMap[it.key()];
    }
    reset();
    setSearchKeyCount(0);
    m_contactListMap.clear();
}

int CDoodLocalSearchManager::searchKeyCount() const
{
    return mSearchKeyCount;
}

int CDoodLocalSearchManager::setSearchKeyCount(const int &data)
{
    if(mSearchKeyCount==data){
        return data;
    }
    mSearchKeyCount=data;
    emit searchKeyCountChanged();
    return mSearchKeyCount;
}

void CDoodLocalSearchManager::onSearchFromLocal(int code, ContactList user, ContactList group)
{
    qDebug() << Q_FUNC_INFO;
    if(code != 0)
        return;
    int i = 0;
    bool flag1=false;
    bool flag2=false;
    bool flag3=false;
    reset();
    setSearchKeyCount(0);
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
        tmpItem->setUserOrGroup(QString::number(1)); //这里用1表示好友，用2表示群
        if(user[i].pinyin=="组织成员"){
            tmpItem->setSearchKey("组织成员");
            flag1=true;
        }
        else{
            tmpItem->setSearchKey("联系人");
            flag2=true;
        }
        insertItem(itemCount(),tmpItem);
        m_contactListMap[user[i].id] = tmpItem;
    }
    if(flag1){
        setSearchKeyCount(1);
    }
    if(flag2){
        setSearchKeyCount(1);
    }
    if(flag1&&flag2){
        setSearchKeyCount(2);
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
        tmpItem->setSearchKey("群组");
        flag3=true;
        insertItem(itemCount(),tmpItem);
        m_contactListMap[group[j].id] = tmpItem;
    }
    if(flag3){
        int i;
        i=searchKeyCount();
        i++;
        setSearchKeyCount(i);
    }
}
