#ifndef AUTHCONTROLER_H
#define AUTHCONTROLER_H

#include "IAuthObserver.h"
namespace service {
    class IMClient;
}
class AuthControler : public IAuthObserver
{
public:
    AuthControler();
    void init(std::string  dataPath,std::string certPath);

    void onConnectChanged(int flag);
    void onLoginResultObserver(service::ErrorInfo& info, int64 userid);
    void onDBUpdateFinished(int val);
    void onLogoutChanged(service::ErrorInfo& info);
    void onAccountInfoChanged(service::User& info);
    void onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey);
    void onPasswordRuleChanged(service::ErrorInfo& info, int16 rule);
    void onAvatarChanged(std::string avatar);
private:
    void onSerLogin(service::ErrorInfo& err, int64 userid);
private:
    std::shared_ptr<service::IMClient> m_client;
};

#endif // AUTHCONTROLER_H
