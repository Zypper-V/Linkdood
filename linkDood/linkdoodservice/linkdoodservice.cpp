#include "linkdoodservice.h"

#include <QDebug>

LinkDoodService* LinkDoodService::m_pInstance = 0;

void LinkDoodService::createService()
{
    qDebug() << Q_FUNC_INFO;
    if (!m_pInstance) {
        qDebug() << " create LinkDoodService !!!";
        m_pInstance = new LinkDoodService();
    } else {
        qDebug() << "alreadly create LinkDoodService !!!";
    }
}

LinkDoodService *LinkDoodService::instance()
{
    qDebug() << Q_FUNC_INFO;
    return m_pInstance;
}

LinkDoodService::LinkDoodService(QObject *parent) :
    QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
}

LinkDoodService::~LinkDoodService()
{

}
