#ifndef __LINKDOODUI_WORKSPACE__
#define __LINKDOODUI_WORKSPACE__

#include <QQuickView>
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <SyberosGuiCache>
#include <cgui_application.h>
#include <cworkspace.h>

#include <QScopedPointer>

using namespace SYBEROS;

class CDoodLoginManager;
class CDoodSessionListManager;
class LinkDoodClient;
class CDoodContactManager;
class CDoodChatManager;
class CDoodUserDataManage;
class CDoodEnterpriseManager;
class CDoodOrgManager;
class CDoodUserProfileManager;

class linkdoodui_Workspace : public CWorkspace
{
    Q_OBJECT

private:
    QQuickView *m_view;

public:
    linkdoodui_Workspace();

    // 应用启动结束时，回调此函数。根据传入的option，应用可以区分启动的方式。
    void onLaunchComplete(Option option, const QStringList& params);

    void openByUrl(const QUrl& url);

private:
    void showLinkDood(const QString &id, const QString &pwd);
    void setActiveWindow();

private:
    QSharedPointer<CDoodLoginManager> m_pLoginManager;
    QSharedPointer<CDoodSessionListManager> m_pSessionListManager;
    QSharedPointer<CDoodContactManager> m_pContactManager;
    QSharedPointer<CDoodChatManager> m_pChatManager;
    QSharedPointer<CDoodUserDataManage> m_pUserDataManager;
    QSharedPointer<CDoodEnterpriseManager> m_pEnterPriseManager;
    QSharedPointer<CDoodOrgManager> m_pOrgManager;
    QSharedPointer<LinkDoodClient> m_pClient;
    QSharedPointer<CDoodUserProfileManager> m_pUserProfileManager;

};


#endif //__LINKDOODUI_WORKSPACE__
