#ifndef CDOODADDCONTACTMANAGER_H
#define CDOODADDCONTACTMANAGER_H

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodContactItem;
class CDoodAddContactManager : public CDoodListModel
{
    Q_OBJECT
public:
    explicit CDoodAddContactManager(LinkDoodClient *client = 0, QObject *parent = 0);

    //从网络获取联系人
    Q_INVOKABLE void searchFromNet(QString key);
    //添加联系人
    Q_INVOKABLE void addContact(QString userid, QString remark, QString info);
    Q_INVOKABLE void contactListClear();
    Q_INVOKABLE void getVerifyType(QString userid);


signals:
    void searchFromNetResult(int size);
    void getVerifyResult(int code, QString userid, int type);
private slots:
    //从网络获取联系人
    void onSearchFromNet(int code, ContactList user, ContactList group);
    //添加联系人返回
    void onAddContact(int code);
    void onGetVerifyType(int code, QString userid, int type);


private:
    void initConnect();

    LinkDoodClient *m_pClient;
    QMap<QString, CDoodContactItem*> m_contactListMap;
};

#endif // CDOODADDCONTACTMANAGER_H
