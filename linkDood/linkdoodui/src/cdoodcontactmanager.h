#ifndef CDOODCONTACTMANAGER_H
#define CDOODCONTACTMANAGER_H

#include <QObject>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodContactManager : public CDoodListModel
{

    Q_OBJECT

public:
    explicit CDoodContactManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodContactManager();
   // Q_INVOKABLE QString getHeaderColor(const QString &id);

signals:

private slots:

private:
    LinkDoodClient *m_pClient;

};

#endif // CDOODCONTACTMANAGER_H
