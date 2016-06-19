#ifndef AUTHCONTROLER_H
#define AUTHCONTROLER_H
#include <QObject>
#include <QString>
#include "IAuthObserver.h"
#include "linkdoodtypes.h"
#include "LoginInfo.hpp"

namespace service {
    class IMClient;
}
class AuthControler :public QObject, public IAuthObserver
{
    Q_OBJECT
public:
    AuthControler(QObject *parent = 0);

    void logout();

    /***************************************
    * @brief getLoginHistory
    * @description: 获取登录历史记录
    ******************************************/
    void getLoginHistory(void);

    /******************************************
    * @brief setLoginInfo
    * @description: 设置登录信息
    * @param[in] flag 传入登录属性 记住密码 flag=2;自动登录 flag=6
    * @param[in] userid 传入用户ID
    * @param[in] username 传入用户名
    * @param[in] avatar	  传入用户头像
    *************************************************/
    void setLoginInfo(int flag, QString userid, QString username, QString avatar);

    void init(void);
    void onConnectChanged(int flag);
    void onLoginResultObserver(service::ErrorInfo& info, int64 userid);
    void onDBUpdateFinished(int val);
    void onLogoutChanged(service::ErrorInfo& info);
    void onAccountInfoChanged(service::User& info);
    void onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey);
    void onPasswordRuleChanged(service::ErrorInfo& info, int16 rule);
    void onAvatarChanged(std::string avatar);

protected slots:
    //void login(const QString &server, const QString &userId, const QString &password);
 signals:
    void loginSucceeded(void);
    void loginFailed(int64 code);

    void loginoutRelust(bool succeeded);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);
    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
private:
    void _getLoginHistory(std::vector<service::LoginInfo> list);
};

#endif // AUTHCONTROLER_H
