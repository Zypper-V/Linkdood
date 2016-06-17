#ifndef AUTHCONTROLER_H
#define AUTHCONTROLER_H
#include <QObject>
#include <QString>
#include "IAuthObserver.h"
namespace service {
    class IMClient;
}
class AuthControler :public QObject, public IAuthObserver
{
    Q_OBJECT
public:
    AuthControler(QObject *parent = 0);

    void init(void);
    void onConnectChanged(int flag);
    void onLoginResultObserver(service::ErrorInfo& info, int64 userid);
    void onDBUpdateFinished(int val);
    void onLogoutChanged(service::ErrorInfo& info);
    void onAccountInfoChanged(service::User& info);
    void onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey);
    void onPasswordRuleChanged(service::ErrorInfo& info, int16 rule);
    void onAvatarChanged(std::string avatar);

 signals:
    void loginSucceeded(void);
    void loginFailed(int64 errCode);

    void loginoutRelust(bool succeeded);
    void loginoutSrvRelust(bool succeeded);
public slots:
    void onLoginoutResult(bool result);
};

#endif // AUTHCONTROLER_H
