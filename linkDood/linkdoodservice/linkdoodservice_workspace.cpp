#include "linkdoodservice_workspace.h"
#include "linkdoodservice.h"

#include <QDebug>
#include <QThread>

linkdoodservice_Workspace::linkdoodservice_Workspace()
    : CWorkspace()
{
    qDebug() << Q_FUNC_INFO<<"lixinnnnnnnnnnnnnssnnsnsnssn";
    LinkDoodService::createService();

}

void linkdoodservice_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    Q_UNUSED(params)

    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }
}

