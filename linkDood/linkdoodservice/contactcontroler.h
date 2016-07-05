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

    void init();
    void onListChanged(int operType, std::vector<service::Contact>& users);
    void onAvatarChanged(int64 userid, std::string avatar);
    void onContactInfoChanged(int operType, service::User& users);
    void onOnlineChanged(OnlineState& status);
signals:
    //transparent onListChanged signal
    void contactListChanged(int oper,ContactList contactList);
    //联系人信息更新
    void contactInfoChanged(int oper,Contact user);
    void contactOnlineChanged(QString id, QString deviceType,int flag);
private:
    ContactList sort(const ContactList& contactList);
    //更新联系人信息
    void _updateContactInfo(service::ErrorInfo&info);
};
#endif // CONTACTCONTROLER_H
