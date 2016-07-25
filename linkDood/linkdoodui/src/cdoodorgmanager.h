#ifndef CDOODORGMANAGER_H
#define CDOODORGMANAGER_H

#include <QObject>
#include "cdoodlistmodel.h"
#include "cdoodorgitem.h"

class CDoodOrgManager : public CDoodListModel
{
    Q_OBJECT
public:
    explicit CDoodOrgManager(QObject *parent = 0);
    Q_INVOKABLE void resetOrgList();
    Q_INVOKABLE void addOrg(QString id, const QString &name);
    Q_INVOKABLE void selectOrg(QString id);
};

#endif // CDOODORGMANAGER_H
