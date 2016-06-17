#include "cdoodcontactmanager.h"


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
}

void CDoodContactManager::initConnect()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_pClient, SIGNAL(contactListChanged(int, ContactList)), this, SLOT(onContactListChanged(int, ContactList)));
}

