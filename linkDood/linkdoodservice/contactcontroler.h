#ifndef CONTACTCONTROLER_H
#define CONTACTCONTROLER_H

#include<IContactObserver.h>
#include<QObject>
#include "Contact.h"
#include "linkdoodtypes.h"

bool CmpByTeam(const Contact first,const Contact second);
class ContactControler:public QObject,public IContactObserver
{
    Q_OBJECT
public:

    ContactControler(QObject *parent = 0);
    ~ContactControler();

    //获取会话列表
    void getContactList();
    //更新联系人信息
    void updateContactInfo(QString userId,QString operStar,QString remark="");

    void getContactInfo(QString userid);

    void init();
    void onListChanged(int operType, std::vector<service::Contact>& users);
    void onAvatarChanged(int64 userid, std::string avatar);
    void onContactInfoChanged(int operType, service::User& users);
    void onOnlineChanged(OnlineState& status);
    void searchFromNet(QString& key);
    void searchFromLocal(QString& key);
    //添加联系人
    void addContact(QString userid, QString remark, QString info);
    //删除联系人
    void removeContact(QString userid);
    //获取验证方式
    void getVerifyType(QString userid);


signals:
    //transparent onListChanged signal
    void contactListChanged(int oper,ContactList contactList);
    void chatAvatarChanged(QString userid, QString avatar);
    //联系人信息更新
    void contactInfoChanged(int oper,Contact user);
    void contactOnlineChanged(QString id, QString deviceType,int flag);
    void searchFromNetBack(int code, ContactList user, ContactList group);
    void searchFromLocalBack(int code, ContactList user, ContactList group);
    void updateContactInfoBack(int code);
    void addContactBack(int code);
    void removeContactBack(int code);
    void getVerifyTypeBack(int code, QString userid, int type);
    void getContactInfo(Contact contact);
private:
    ContactList sort(const ContactList& contactList);
    //更新联系人信息
    void _updateContactInfo(service::ErrorInfo&info);
    void _searchFromNet(service::ErrorInfo& info, SearchResult& res);
    void _searchFromLocal(service::ErrorInfo& info, SearchResult& res);
    void _addContact(service::ErrorInfo info);
    void _removeContact(service::ErrorInfo info);
    void _getVerifyType(service::ErrorInfo info, ContactVerifyType verify);
    void _getContactInfo(service::ErrorInfo&info, service::User&contact);
    void _getContactOnline(std::vector<OnlineState>& status);
};
#endif // CONTACTCONTROLER_H
