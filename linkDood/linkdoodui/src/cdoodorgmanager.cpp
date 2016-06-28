#include "cdoodorgmanager.h"
#include <QDebug>

CDoodOrgManager::CDoodOrgManager(QObject *parent) : CDoodListModel(parent)
{
//    CDoodOrgItem *item = new CDoodOrgItem(this);
//    item->setId("1");
//    item->setName("vrv");
//    addItem(item);
}

void CDoodOrgManager::addOrg(QString id, const QString &name)
{
    qDebug()<<"CDoodOrgManager::addOrg id:"<<id;
    qDebug()<<"CDoodOrgManager::addOrg name:"<<name;
    CDoodOrgItem *item = new CDoodOrgItem(this);
    item->setId(id);
    item->setName(name);
    addItem(item);
}

void CDoodOrgManager::selectOrg(QString id)
{
    qDebug()<<"CDoodOrgManager::selectOrg id:"<<id;
    qDebug()<<"CDoodOrgManager::selectOrg _list->count():"<<_list->count();
    for(int i = _list->count(); i > 1; i--) {
        qDebug()<<"CDoodOrgManager::selectOrg i:"<<i;

        if(id.toInt() == i) {
            break;
        }
        removeItem(_list->at(i-1));
    }
}
