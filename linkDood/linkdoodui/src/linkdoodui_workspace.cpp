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
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }
}

