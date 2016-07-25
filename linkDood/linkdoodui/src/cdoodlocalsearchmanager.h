#ifndef CDOODLOCALSEARCHMANAGER_H
#define CDOODLOCALSEARCHMANAGER_H

#include "linkdoodclient.h"
#include "cdoodlistmodel.h"

class CDoodContactItem;
class CDoodLocalSearchManager : public CDoodListModel
{
    Q_OBJECT
public:
    CDoodLocalSearchManager(LinkDoodClient *client = 0, QObject *parent = 0);

    //从本地数据库进行查找
    Q_INVOKABLE void searchFromLocal(QString key);
    Q_INVOKABLE void contactListClear();

private slots:
    //从本地数据库进行查找
    void onSearchFromLocal(int code, ContactList user, ContactList group);

private:

    LinkDoodClient *m_pClient;
    QMap<QString, CDoodContactItem*> m_contactListMap;
};

#endif // CDOODLOCALSEARCHMANAGER_H
