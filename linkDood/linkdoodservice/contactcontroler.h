#ifndef CONTACTCONTROLER_H
#define CONTACTCONTROLER_H

#endif // CONTACTCONTROLER_H
#include<IContactObserver.h>
class ContactControler:public IContactObserver
{
public:

    ContactControler();
    ~ContactControler();
    void onListChanged(int operType, std::vector<service::Contact>& users);
    void onAvatarChanged(int64 userid, std::string avatar);
    void onContactInfoChanged(int operType, service::User& users);
    void onOnlineChanged(OnlineState& status);
};
