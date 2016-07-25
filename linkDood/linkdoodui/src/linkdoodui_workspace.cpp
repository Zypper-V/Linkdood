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
#include "cdooduserprofilemanager.h"
#include "cdoodemojimanager.h"
#include "cdoodaddcontactmanager.h"
#include "cdoodgroupmanager.h"
#include "cdoodmembermanager.h"
#include "cdoodfriendverificationmanager.h"
#include "cdoodsysmsgmanager.h"
#include "cdoodlocalsearchmanager.h"
#include "cdoodfileviewmanager.h"

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

    m_pFileViewManager = QSharedPointer<CDoodFileViewManager>(new CDoodFileViewManager(m_pClient.data()));
    if (!m_pFileViewManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pFileViewManager init error !!!";
    }

    m_pLoginManager = QSharedPointer<CDoodLoginManager>(new CDoodLoginManager(m_pClient.data()));
    if (!m_pLoginManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pLoginManager init error !!!";
    }

    m_pSessionListManager = QSharedPointer<CDoodSessionListManager>(new CDoodSessionListManager(m_pClient.data(),this));
    if (!m_pSessionListManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pSessionListManager init error !!!";
    }

    m_pContactManager = QSharedPointer<CDoodContactManager>(new CDoodContactManager(m_pClient.data()));
    if (!m_pContactManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pContactManager init error !!!";
    }

    m_pUserProfileManager = QSharedPointer<CDoodUserProfileManager>(new CDoodUserProfileManager(m_pClient.data()));
    if (!m_pUserProfileManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pUserProfileManager init error !!!";
    }

    m_pChatManager = QSharedPointer<CDoodChatManager>(new CDoodChatManager(m_pClient.data()));
    if (!m_pChatManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pChatManager init error !!!";
    }
    m_pUserDataManager = QSharedPointer<CDoodUserDataManage>(new CDoodUserDataManage());
    if (!m_pUserDataManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pUserDataManager init error !!!";
    }
    m_pEnterPriseManager = QSharedPointer<CDoodEnterpriseManager>(new CDoodEnterpriseManager(m_pClient.data()));
    if (!m_pEnterPriseManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pEnterPriseManager init error !!!";
    }

    m_pOrgManager = QSharedPointer<CDoodOrgManager>(new CDoodOrgManager());
    if (!m_pOrgManager.data()) {
        qDebug() << Q_FUNC_INFO << "m_pEnterPriseManager init error !!!";
    }

    m_pEmojiManager = QSharedPointer<CDoodEmojiManager>(new CDoodEmojiManager(m_pClient.data()));
    if (!m_pEmojiManager.data()) {
        qDebug() << Q_FUNC_INFO << "CDoodEmojiManager init error !!!";
    }

    m_pGroupManager = QSharedPointer<CDoodGroupManager>(new CDoodGroupManager(m_pClient.data(),this));
    if (!m_pGroupManager.data()) {
        qDebug() << Q_FUNC_INFO << "CDoodGroupManager init error !!!";
    }

    m_pMemberManager = QSharedPointer<CDoodMemberManager>(new CDoodMemberManager(m_pClient.data()));
    if (!m_pMemberManager.data()) {
        qDebug() << Q_FUNC_INFO << "CDoodMemberManager init error !!!";
    }

    m_pDyEmojiManager = QSharedPointer<CDoodEmojiManager>(new CDoodEmojiManager(m_pClient.data(), 1));
    if (!m_pDyEmojiManager.data()) {
        qDebug() << Q_FUNC_INFO << "CDoodEmojiManager dynomic init error !!!";
    }
    m_pAddContactManager = QSharedPointer<CDoodAddContactManager>(new CDoodAddContactManager(m_pClient.data()));
    if(!m_pAddContactManager.data()){
        qDebug() << Q_FUNC_INFO << "CDoodAddContactManager init error !!!";
    }
    m_pFriendVerificationManager = QSharedPointer<CDoodFriendVerificationManager>(new CDoodFriendVerificationManager());
    if(!m_pFriendVerificationManager.data()){
        qDebug() << Q_FUNC_INFO << "CDoodFriendVerificationManager init error !!!";
    }
    m_pSysmsgManager = QSharedPointer<CDoodSysMsgManager>(new CDoodSysMsgManager(m_pClient.data()));
    if(!m_pSysmsgManager.data()){
        qDebug() << Q_FUNC_INFO << "CDoodSysMsgManager init error !!!";
    }

    m_pLocalSearchManager = QSharedPointer<CDoodLocalSearchManager>(new CDoodLocalSearchManager(m_pClient.data()));
    if(!m_pLocalSearchManager.data()){
        qDebug() << Q_FUNC_INFO << "m_pLocalSearchManager init error !!!";
    }


    QObject::connect(m_pChatManager.data(),SIGNAL(ChatPageChanged()),this,SLOT(onChatPageChanged()));

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    m_view->engine()->rootContext()->setContextProperty("loginManager", m_pLoginManager.data());
    m_view->engine()->rootContext()->setContextProperty("sessionListManager", m_pSessionListManager.data());
    m_view->engine()->rootContext()->setContextProperty("contactManager", m_pContactManager.data());
    m_view->engine()->rootContext()->setContextProperty("chatManager", m_pChatManager.data());
    m_view->engine()->rootContext()->setContextProperty("userdataManager", m_pUserDataManager.data());
    m_view->engine()->rootContext()->setContextProperty("enterpriseManager", m_pEnterPriseManager.data());
    m_view->engine()->rootContext()->setContextProperty("orgManager", m_pOrgManager.data());
    m_view->engine()->rootContext()->setContextProperty("userProfileManager", m_pUserProfileManager.data());
    m_view->engine()->rootContext()->setContextProperty("userEmojiManager", m_pEmojiManager.data());
    m_view->engine()->rootContext()->setContextProperty("groupManager", m_pGroupManager.data());
    m_view->engine()->rootContext()->setContextProperty("memberManager", m_pMemberManager.data());
    m_view->engine()->rootContext()->setContextProperty("userDyEmojiManager", m_pDyEmojiManager.data());
    m_view->engine()->rootContext()->setContextProperty("addContactManager", m_pAddContactManager.data());
    m_view->engine()->rootContext()->setContextProperty("friendVericationManager", m_pFriendVerificationManager.data());
    m_view->engine()->rootContext()->setContextProperty("sysmsgManager", m_pSysmsgManager.data());
    m_view->engine()->rootContext()->setContextProperty("localSearchManager", m_pLocalSearchManager.data());

    m_view->engine()->rootContext()->setContextProperty("chatManagerModel", m_pChatManager->chatModel());
    m_view->engine()->rootContext()->setContextProperty("fileViewManager", m_pFileViewManager.data());
    m_view->engine()->rootContext()->setContextProperty("chatManagerModel", m_pChatModel);

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

void linkdoodui_Workspace::getGroupInfoFromList(QString groupId, QString &name, QString &avatar)
{
    if(!m_pGroupManager.isNull()){
        m_pGroupManager->getGroupInfoFromList(groupId,name,avatar);
    }
}

void linkdoodui_Workspace::getContactInforFromList(QString id, QString& name, QString& avater)
{
    qDebug()<<Q_FUNC_INFO;
    if(!m_pContactManager.isNull()){
        m_pContactManager->getContactInforFromList(id,name,avater);
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

void linkdoodui_Workspace::onChatPageChanged()
{
    qDebug() << Q_FUNC_INFO;
    if(!m_pChatManager.isNull()){
        m_pChatModel = m_pChatManager->chatModel();

    }
    m_view->engine()->rootContext()->setContextProperty("chatManagerModel", m_pChatManager->chatModel());
}

