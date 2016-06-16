#include "cdoodsessionlistmanager.h"
#include "cdoodsessionlistitem.h"


#include <QMetaType>
#include <QDebug>

CDoodSessionListManager::CDoodSessionListManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodSessionListManager*>();
    initConnect();

    QList <QObject* > itemlist;

        CDoodSessionListItem *tmpItem = new CDoodSessionListItem(this);
        tmpItem->setId("10380360");
        tmpItem->setName("武汉研发中心");
        tmpItem->setMsgTime("2016-05-06 17:33:42");
        tmpItem->setLastMsg("撤回了一条消息");
        itemlist.append(tmpItem);

        CDoodSessionListItem *tmpItem1 = new CDoodSessionListItem(this);
        tmpItem1->setId("10380361");
        tmpItem1->setName("内部测试");
        tmpItem1->setMsgTime("2016-05-06 17:33:42");
        tmpItem1->setLastMsg("安卓");
        itemlist.append(tmpItem1);

        CDoodSessionListItem *tmpItem2 = new CDoodSessionListItem(this);
        tmpItem2->setId("10380362");
        tmpItem2->setName("张总");
        tmpItem2->setMsgTime("2016-05-06 17:33:42");
        tmpItem2->setLastMsg("很多人不会");
        itemlist.append(tmpItem2);

        CDoodSessionListItem *tmpItem3 = new CDoodSessionListItem(this);
        tmpItem3->setId("10380363");
        tmpItem3->setName("刑警大队");
        tmpItem3->setMsgTime("2016-05-06 17:33:42");
        tmpItem3->setLastMsg("开始工作");
        itemlist.append(tmpItem3);

        CDoodSessionListItem *tmpItem4 = new CDoodSessionListItem(this);
        tmpItem4->setId("10392913");
        tmpItem4->setName("科信部");
        tmpItem4->setMsgTime("2016-05-06 17:33:42");
        tmpItem4->setLastMsg("集团公司党组成员、副总经理刘石泉一行到深圳公司江西科创中心指导工作");
        itemlist.append(tmpItem4);

    beginInsertRows(QModelIndex(), _list->count(), itemlist.size() - 1);
    for(int i = 0; i < itemlist.size(); ++i) {
        qDebug() << " ----CDoodSessionListItem list " << i;
        _list->append(itemlist.at(i));
        connect(itemlist.at(i), SIGNAL(destroyed()), this, SLOT(removeDestroyedItem()));
    }
    endInsertRows();
    emit itemCountChanged();
}

CDoodSessionListManager::~CDoodSessionListManager()
{

}

void CDoodSessionListManager::getChatList()
{
    qDebug() << Q_FUNC_INFO;
}

QString CDoodSessionListManager::getHeaderColor(const QString &id)
{
    qDebug() << Q_FUNC_INFO << id;

    QStringList oColorList;

    oColorList << "#9e8dbe" << "#6ed1d1" << "#88b4e8" << "#d98374" << "#95a7bf" <<
                  "#e3c676" << "#477e99" << "#a6d3d6" << "#a1887f" << "#b4c17b" <<
                  "#88cfee" << "#d7a373" << "#66ae96" << "#cc7eb0" << "#81aba9" <<
                  "#c6b36f" << "#84b9cb" << "#3d9ac6" << "#b18c6f" << "#e6ccb8" <<
                  "#7b76a6" << "#b3ad9f" << "#51c79f" << "#e3a16f" << "#89c3eb" <<
                  "#a69bbd" << "#a89e95" << "#5b7e91" << "#f6b1aa" << "#6fc5d4";


    int nId = id.left(6).toInt()%30;
    qDebug() << "nId = " << nId;
    QString sColor = oColorList.at(nId);
    qDebug() << "sColor = " << sColor;

    return sColor;
}

QString CDoodSessionListManager::getSubName(const QString &name)
{
    qDebug() << Q_FUNC_INFO << name;
    return name.right(2);
}

void CDoodSessionListManager::onChatListChanged(const Chat_UIList &chats)
{
     qDebug() << Q_FUNC_INFO << "chat size4:" << chats.size();
}

void CDoodSessionListManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
     connect(m_pClient, SIGNAL(chatListChanged(const Chat_UIList &)), this, SLOT(onChatListChanged(const Chat_UIList &)));
}
