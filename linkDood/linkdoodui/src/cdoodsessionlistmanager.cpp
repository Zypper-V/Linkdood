#include "cdoodsessionlistmanager.h"
#include "cdoodsessionlistitem.h"


#include <QMetaType>
#include <QFile>
#include <QDebug>

CDoodSessionListManager::CDoodSessionListManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodSessionListManager*>();
    initConnect();
}

CDoodSessionListManager::~CDoodSessionListManager()
{

}

void CDoodSessionListManager::getChatList()
{
    qDebug() << Q_FUNC_INFO;
    //    m_pClient->
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

bool CDoodSessionListManager::checkFileExists(const QString &path)
{
    qDebug() << Q_FUNC_INFO << path;
    QString tmp = path;
    if (tmp.contains("file://")) {
        tmp.remove("file://");
    } else if (tmp.contains("qrc:")) {
        return true;
    }
    bool bExists = QFile(tmp).exists();
    qDebug() << Q_FUNC_INFO << bExists;
    return bExists;
}

void CDoodSessionListManager::onChatListChanged(const Chat_UIList &chats)
{
    qDebug() << Q_FUNC_INFO << "zhangp **** chat size4 = " << chats.size();
    Chat_UI historysession;
    foreach (historysession, chats) {
        if(!sessionListMap.contains(historysession.id)) {
            CDoodSessionListItem *tmpItem = new CDoodSessionListItem(this);
            tmpItem->setId(historysession.id);
            tmpItem->setLastMsg(historysession.last_msg);
            tmpItem->setName(historysession.name);
            tmpItem->setMsgTime(historysession.msg_time);
            tmpItem->setThumbAvatar(historysession.thumb_avatar);
            qDebug() << Q_FUNC_INFO << "chat avatar111:" << historysession.thumb_avatar;
            addItem(tmpItem);
            sessionListMap[historysession.id] = tmpItem;
        }
    }
}

void CDoodSessionListManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(chatListChanged(const Chat_UIList &)), this, SLOT(onChatListChanged(const Chat_UIList &)));
}
