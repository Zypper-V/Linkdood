#ifndef AUTHCONTROLER_H
#define AUTHCONTROLER_H
#include <QObject>
#include <QString>
#include "IAuthObserver.h"
#include "linkdoodtypes.h"
#include "LoginInfo.hpp"
#include "cnetworkmanager.h"
#include "packet.h"

namespace service {
    class IMClient;
    class User;
}
class AuthControler :public QObject, public IAuthObserver
{
    Q_OBJECT
public:
    AuthControler(QObject *parent = 0);
    //登录
    void login(const QString &server,
               const QString &userId,
               const QString &password);
    //
    void autoLogin(QString userid,QString service);
    void getVerifyImg( QString userid,QString code);
    void _getVerifyImg(service::ErrorInfo info,std::string img);
    void changepassword(QString oldpsw,QString newpsw);
    void _changepassword(service::ErrorInfo& info);
    void logout();
    //用户信息
    //void getUserInfo(QString& userId,QString& name,QString& avater);
    //用户信息UserId
    QString UserId();
    QString userName();
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

    /**********************************
    * @brief getAccountInfo
    * @description: 获取账户信息
    ************************************/
    void getAccountInfo(void);

    /************************************
    * @brief updateAccountInfo
    * @description: 更新用户信息
    * @param[in] user 传入用户信息
    *************************************/
    void updateAccountInfo(Contact user);

    void init(void);
    void onConnectChanged(int flag);
    void onLoginResultObserver(service::ErrorInfo& info, int64 userid);
    void onDBUpdateFinished(int val);
    void onLogoutChanged(service::ErrorInfo& info);
    void onAccountInfoChanged(service::User& info);
    void onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey);
    void onPasswordRuleChanged(service::ErrorInfo& info, int16 rule);
    void onAvatarChanged(std::string avatar);

    void setPrivateSetting(IMPrivateSetting ps);
    void getPrivateSetting();

 protected slots:
    void onNetworkStatusChanged(bool connected, CNetworkManager::NetworkType type);
    void onSetPrivateSetting(int code);
    void onGetPrivateSetting(int code, PrivateSetting ps);

    //void login(const QString &server, const QString &userId, const QString &password);
 signals:
    void loginSucceeded(QString userid);
    void loginFailed(int code);
    void changePasswordResult(QString result);
    void getVerifyImgResult(QString code,QString img);
    void connectChanged(QString flag);
    void anthAvatarChanged(QString avatar);
    void loginoutRelust(bool succeeded);
    //登录成功自动推送
    void loginResultObserver(int code,QString userID);
    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);
    //推送用户信息
    void accountInfoChanged(Contact user);

    void setPrivateSettingResult(int code);
    void getPrivateSettingResult(int code, IMPrivateSetting ps);
private:
    void initConnects();
    void _getLoginHistory(std::vector<service::LoginInfo> list);
    void _loginResult(service::ErrorInfo& info,int64 userId);
    void _updateAccountInfo(service::ErrorInfo& info);
private:
  // std::shared_ptr<service::User> mpUserInfo;
   CNetworkManager* m_net;
   QString m_account;
};

#endif // AUTHCONTROLER_H
