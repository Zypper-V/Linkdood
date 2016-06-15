#ifndef LINKDOODSERVICE_H
#define LINKDOODSERVICE_H

#include <QObject>
#include "authcontroler.h"

class CSystemPackageManager;

class LinkDoodService : public QObject
{
    Q_OBJECT

public:
    void static createService();
    static LinkDoodService* instance();
    QString installPath();
    QString dataPath();
    //
    void login(const QString& server,const QString& user,const QString& userPwd);

signals:
    void signalLoginSucceeded();
    void signalLoginFailed(int64 errCode);
public:
    static LinkDoodService* m_pInstance;

private:
    void initSdk();
    void onLoginResult(service::ErrorInfo& info,int64 userId);
    LinkDoodService(QObject *parent = 0);

    ~LinkDoodService();

private:
    CSystemPackageManager *m_pPackageManager;
    QString m_sInstallPath;

    std::shared_ptr<AuthControler>  m_pAuth;
    std::shared_ptr<service::IMClient> m_pIMClient;
};

#endif // LINKDOODSERVICE_H
