#ifndef CONTACTCONTROLER_H
#define CONTACTCONTROLER_H

#endif // CONTACTCONTROLER_H
#include<IContactObserver.h>
#include<QObject>
#include "Contact.h"

class ContactControler:public IContactObserver,public QObject
{
public:

    ContactControler(QObject *parent = 0);
    ~ContactControler();
    void init();
    void onListChanged(int operType, std::vector<service::Contact>& users);
    void onAvatarChanged(int64 userid, std::string avatar);
    void onContactInfoChanged(int operType, service::User& users);
    void onOnlineChanged(OnlineState& status);
signals:
    void contactListChanged(int operType, std::vector<service::Contact>& users);
};
