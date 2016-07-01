#ifndef CDOODCONTACTMANAGER_H
#define CDOODCONTACTMANAGER_H

#include <QObject>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodContactItem;
class CDoodContactManager : public CDoodListModel
{

    Q_OBJECT

public:
    explicit CDoodContactManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodContactManager();
    //获取会话列表
    Q_INVOKABLE void getContactList();
    //清空列表
    Q_INVOKABLE void clearChatList();

    //更新联系人信息
    Q_INVOKABLE void updateContactInfo(QString userId,QString operStar,QString remark="");
signals:
    void contactListChanged(int oper,ContactList contacts);
private slots:
    void onContactListChanged(int oper,ContactList contacts);
    //联系人信息更新
    void onContactInfoChanged(int oper,Contact user);
private:

    void initConnect();
    int  indexOfSection(QString sectnion);//从map开头找第一个section相同item位置
    QMap<QString, CDoodContactItem*> contactListMap;
    QMap<QString, CDoodContactItem*> starContactListMap;//v标好友

    LinkDoodClient *m_pClient;

    void addContact(Contact user);
    void modifyContact(Contact user);
    void removeContact(Contact user);
};

#endif // CDOODCONTACTMANAGER_H
