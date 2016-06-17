#include "cdoodcontactmanager.h"
#include"cdoodcontactitem.h"


CDoodContactManager::CDoodContactManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodContactManager*>();
    initConnect();
//        QList <QObject* > itemlist;

//            CDoodContactItem *tmpItem = new CDoodContactItem(this);
//            tmpItem->setName("武汉研发中心");
//            itemlist.append(tmpItem);

//            CDoodContactItem *tmpItem1 = new CDoodContactItem(this);
//            tmpItem1->setName("内部测试");
//            itemlist.append(tmpItem1);

//            CDoodContactItem *tmpItem2 = new CDoodContactItem(this);
//            tmpItem2->setName("张总");
//            itemlist.append(tmpItem2);

//            CDoodContactItem *tmpItem3 = new CDoodContactItem(this);
//            tmpItem3->setName("刑警大队");
//            itemlist.append(tmpItem3);

//            CDoodContactItem *tmpItem4 = new CDoodContactItem(this);
//            tmpItem4->setName("科信部");
//            itemlist.append(tmpItem4);

//        beginInsertRows(QModelIndex(), _list->count(), itemlist.size() - 1);
//        for(int i = 0; i < itemlist.size(); ++i) {
//            qDebug() << " ----CDoodContactItem list " << i;
//            _list->append(itemlist.at(i));
//            connect(itemlist.at(i), SIGNAL(destroyed()), this, SLOT(removeDestroyedItem()));
//        }
//        endInsertRows();
//        emit itemCountChanged();
}

CDoodContactManager::~CDoodContactManager()
{

}

void CDoodContactManager::onContactListChanged(int oper, ContactList contacts)
{
    qDebug() << Q_FUNC_INFO << "conactListSize" << contacts.size();
    QList <QObject* > itemlist;
    for(size_t i=0;i<contacts.size();i++)
    {
        CDoodContactItem *tmpItem = new CDoodContactItem(this);
        tmpItem->setName(contacts[i].name);
        tmpItem->setThumbAvatar(contacts[i].thumbAvatar);
        qDebug() << Q_FUNC_INFO << "contacts avatar111:" << contacts[i].thumbAvatar;
        itemlist.append(tmpItem);
    }
    beginInsertRows(QModelIndex(), _list->count(), itemlist.size() - 1);
    for(int i = 0; i < itemlist.size(); ++i) {
        qDebug() << " ----CDoodContactItem list " << i;
        _list->append(itemlist.at(i));
        connect(itemlist.at(i), SIGNAL(destroyed()), this, SLOT(removeDestroyedItem()));
    }
    endInsertRows();
    emit itemCountChanged();
}

void CDoodContactManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(contactListChanged(int, ContactList)), this, SLOT(onContactListChanged(int, ContactList)));
}

