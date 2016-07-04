#include "cdoodorgitem.h"

CDoodOrgItem::CDoodOrgItem(QObject *parent) : QObject(parent)
{

}

QString CDoodOrgItem::id() const
{
    return mId;
}

QString CDoodOrgItem::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodOrgItem::name() const
{
    return mName;
}

QString CDoodOrgItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodOrgItem::select() const
{
    return mSelect;
}

QString CDoodOrgItem::setSelect(const QString &data)
{
    if(mSelect == data) {
        return data;
    }
    mSelect = data;
    emit selectChanged();
    return mSelect;
}
