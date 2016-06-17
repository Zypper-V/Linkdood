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
    void contactListChanged(int oper,ContactList contacts);
private slots:
    void onContactListChanged(int oper,ContactList contacts);
private:
    void initConnect();

    LinkDoodClient *m_pClient;

};

#endif // CDOODCONTACTMANAGER_H
