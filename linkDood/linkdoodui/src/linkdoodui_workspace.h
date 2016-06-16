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

class linkdoodui_Workspace : public CWorkspace
{
    Q_OBJECT

private:
    QQuickView *m_view;

public:
    linkdoodui_Workspace();

    // 应用启动结束时，回调此函数。根据传入的option，应用可以区分启动的方式。
    void onLaunchComplete(Option option, const QStringList& params);

private:
    QSharedPointer<CDoodLoginManager> m_pLoginManager;
    QSharedPointer<CDoodSessionListManager> m_pSessionListManager;

    QSharedPointer<LinkDoodClient> m_pClient;
};


#endif //__LINKDOODUI_WORKSPACE__
