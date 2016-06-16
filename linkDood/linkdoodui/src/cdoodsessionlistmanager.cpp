#include "cdoodsessionlistmanager.h"

#include <QMetaType>
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

void CDoodSessionListManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
}
