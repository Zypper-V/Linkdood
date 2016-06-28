#include "linkdoodui_workspace.h"
#include "cdoodlistmodel.h"
#include "cdoodloginmanager.h"
#include "cdoodsessionlistmanager.h"
#include "cdoodcontactmanager.h"
#include "linkdoodclient.h"
#include "cdoodchatmanager.h"
#include "cdooduserdatamanage.h"
#include "cdoodenterprisemanager.h"
#include "cdoodorgmanager.h"
#include <QQmlContext>
#include <QUrl>
#include <QUrlQuery>
#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include <QDebug>

linkdoodui_Workspace::linkdoodui_Workspace()
    : CWorkspace()
{
    qmlRegisterType<CDoodListModel>("CDoodListModel", 1, 0, "CDoodListModel");

    m_pClient = QSharedPointer<LinkDoodClient>(new LinkDoodClient());
    if (!m_pClient.data()) {
        qDebug() << Q_FUNC_INFO << "m_pClient init error !!!";
    }

    m_pLoginManager = QSharedPointer<CDoodLoginManager>(new CDoodLoginManager(m_pClient.data()));
    if (!m_pLoginManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pLoginManager init error !!!";
    }

    m_pSessionListManager = QSharedPointer<CDoodSessionListManager>(new CDoodSessionListManager(m_pClient.data()));
    if (!m_pSessionListManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pSessionListManager init error !!!";
    }

    m_pContactManager = QSharedPointer<CDoodContactManager>(new CDoodContactManager(m_pClient.data()));
    if (!m_pContactManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pContactManager init error !!!";
    }

    m_pChatManager = QSharedPointer<CDoodChatManager>(new CDoodChatManager(m_pClient.data()));
    if (!m_pChatManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pChatManager init error !!!";
    }
    m_pUserDataManager = QSharedPointer<CDoodUserDataManage>(new CDoodUserDataManage());
    if (!m_pUserDataManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pUserDataManager init error !!!";
    }
    m_pEnterPriseManager = QSharedPointer<CDoodEnterpriseManager>(new CDoodEnterpriseManager());
    if (!m_pEnterPriseManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pEnterPriseManager init error !!!";
    }

    m_pOrgManager = QSharedPointer<CDoodOrgManager>(new CDoodOrgManager());
    if (!m_pOrgManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pEnterPriseManager init error !!!";
    }
    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    m_view->engine()->rootContext()->setContextProperty("loginManager", m_pLoginManager.data());
    m_view->engine()->rootContext()->setContextProperty("sessionListManager", m_pSessionListManager.data());
    m_view->engine()->rootContext()->setContextProperty("contactManager", m_pContactManager.data());
    m_view->engine()->rootContext()->setContextProperty("chatManager", m_pChatManager.data());
    m_view->engine()->rootContext()->setContextProperty("userdataManager", m_pUserDataManager.data());
    m_view->engine()->rootContext()->setContextProperty("enterpriseManager", m_pEnterPriseManager.data());
    m_view->engine()->rootContext()->setContextProperty("orgManager", m_pOrgManager.data());

    m_view->setSource(QUrl("qrc:/qml/main.qml"));
    m_view->showFullScreen();
}

void linkdoodui_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    Q_UNUSED(params)
    qDebug() << Q_FUNC_INFO;
    qApp->runService("linkdoodservice", QStringList());

    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        qDebug() << "Start by URL";
        openByUrl(QUrl(params.at(0)));
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }
}

void linkdoodui_Workspace::openByUrl(const QUrl &url)
{
    qDebug()<<Q_FUNC_INFO<<__LINE__<<url.toString();
    QString scheme = url.scheme();
    QString path = url.path();
    QUrlQuery query(url.query());
    if (scheme == "linkDood") {
        if (path == "showLinkDood") {
            //linkDood:showLinkDood?id=xxx&pwd=xxx
            QString id = query.queryItemValue("id");
            QString pwd = query.queryItemValue("pwd");
            showLinkDood(id, pwd);
            setActiveWindow();
        }
    } else {
        qDebug() << Q_FUNC_INFO << "not linkDood!!!!";
    }
}

void linkdoodui_Workspace::showLinkDood(const QString &id, const QString &pwd)
{
    qDebug() << Q_FUNC_INFO << __LINE__ << id << " " << pwd;
    // TODO
}

void linkdoodui_Workspace::setActiveWindow()
{
    qDebug() << Q_FUNC_INFO;
    m_view->requestActivate();
    m_view->raise();
    m_view->showFullScreen();
    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();
    native->setWindowProperty(m_view->handle(), "STATUSBAR_VISIBLE", "true");
    native->setWindowProperty(m_view->handle(), "STATUSBAR_STYLE", "transblack");
}

