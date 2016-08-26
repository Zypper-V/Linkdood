#include "cdoodorgmanager.h"
#include"cdoodcontactitem.h"
#include <QDebug>

CDoodOrgManager::CDoodOrgManager(QObject *parent) : CDoodListModel(parent)
{
    //    CDoodOrgItem *item = new CDoodOrgItem(this);
    //    item->setId("1");
    //    item->setName("北信源");
    //    addItem(item);
}

void CDoodOrgManager::resetOrgList()
{
    qDebug() << Q_FUNC_INFO;
    reset();
}

void CDoodOrgManager::addOrg(QString id, const QString &name)
{
    qDebug()<<"CDoodOrgManager::addOrg id:"<<id;
    qDebug()<<"CDoodOrgManager::addOrg name:"<<name;
    CDoodOrgItem *item = new CDoodOrgItem(this);
    if(_list->count()>0){
        if(qobject_cast<CDoodOrgItem*>(_list->at(_list->count()-1))->id()==id){
            return;
        }
    }
    item->setId(id);
    item->setName(name);
    addItem(item);
    if(_list->count()>1){
        qobject_cast<CDoodOrgItem*>(_list->at(_list->count()-2))->setSelect("");
        qobject_cast<CDoodOrgItem*>(_list->at(_list->count()-1))->setSelect("ss");
    }
    if(_list->count()==1){
        qobject_cast<CDoodOrgItem*>(_list->at(_list->count()-1))->setSelect("ss");
    }

}

void CDoodOrgManager::selectOrg(QString id)
{
    qDebug()<<"CDoodOrgManager::selectOrg id:"<<id;
    qDebug()<<"CDoodOrgManager::selectOrg _list->count():"<<_list->count();
    for(int i = _list->count(); i > 1; i--) {
        qDebug()<<"CDoodOrgManager::selectOrg i:"<<i;

        if(id == (qobject_cast<CDoodOrgItem*>(_list->at(i-1)))->id()) {
            break;
        }
        removeItem(_list->at(i-1));
    }
    qobject_cast<CDoodOrgItem*>(_list->at(_list->count()-1))->setSelect("ss");
}
