#include "cdoodloginmanager.h"

#include <QMetaType>
#include <QDebug>

CDoodLoginManager::CDoodLoginManager(QObject *parent) :
    CDoodListModel(parent)
{
    qDebug() << Q_FUNC_INFO;
    qRegisterMetaType<CDoodLoginManager*>();
}

CDoodLoginManager::~CDoodLoginManager()
{

}

void CDoodLoginManager::login(const QString &server,
                              const QString &userId,
                              const QString &password)
{
    qDebug() << Q_FUNC_INFO << server << userId << password;
}

bool CDoodLoginManager::checkFirstWordIsSpace(const QString &text)
{
    return text.startsWith(" ");
}
