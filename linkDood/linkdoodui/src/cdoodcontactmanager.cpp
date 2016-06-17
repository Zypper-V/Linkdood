#include "cdoodcontactmanager.h"


CDoodContactManager::CDoodContactManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodContactManager*>();
}

CDoodContactManager::~CDoodContactManager()
{

}

