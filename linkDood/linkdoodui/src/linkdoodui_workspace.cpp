#include "linkdoodui_workspace.h"
#include "cdoodlistmodel.h"
#include "cdoodloginmanager.h"
#include "cdoodsessionlistmanager.h"
#include "cdoodcontactmanager.h"
#include "linkdoodclient.h"
#include "cdoodchatmanager.h"
#include "cdoodchatmanagermodel.h"
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
#include "cdoodcontactitem.h"
#include "ctxteditor.h"

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
    qRegisterMetaType<QList<QString> >("QList<QString>");
    qmlRegisterType<CTxtEditor>("com.syberos.filemanager",1,0,"CTxtEditor");
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
    m_pChatManagerModel = QSharedPointer<CDoodChatManagerModel>(new CDoodChatManagerModel(m_pClient.data()));
    if (!m_pChatManagerModel.data()) {
        qDebug() << Q_FUNC_INFO << "m_pChatManager init error !!!";
    }
    m_pUserDataManager = QSharedPointer<CDoodUserDataManage>(new CDoodUserDataManage(m_pClient.data()));
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
    QObject::connect(m_pSysmsgManager.data(),SIGNAL(removeSysMsg(QString,QString)),m_pSessionListManager.data(),SLOT(onRemoveSysMsg(QString,QString)));
    QObject::connect(m_pMemberManager.data(),SIGNAL(groupMemsChanged(QString,int)),this,SLOT(onGroupMemsChanged(QString,int)));
    QObject::connect(m_pChatManager.data(),SIGNAL(chatPageChanged()),this,SLOT(onChatPageChanged()));
    QObject::connect(m_pChatManager.data(),SIGNAL(updateSessionPageMsgReaded(QString)),this,SLOT(onUpdateSessionPageMsgReaded(QString)));
    QObject::connect(m_pGroupManager.data(),SIGNAL(transMessageSelectContactList(QList<QString>,QString)),this,SLOT(onTransMessageSelectContactList(QList<QString>,QString)));
    QObject::connect(m_pGroupManager.data(),SIGNAL(groupRemoveOrExitResult(QString)),this,SLOT(onGroupRemoveOrExitResult(QString)));
    QObject::connect(m_pContactManager.data(),SIGNAL(removeContactOper(QString)),this,SLOT(onRemoveContactOper(QString)));
    QObject::connect(this,SIGNAL(switchLoginByUrl()),m_pLoginManager.data(),SLOT(onSwitchLoginByUrl()));
    QObject::connect(this,SIGNAL(switchChatPageByUrl()),m_pLoginManager.data(),SLOT(onSwitchChatPageByUrl()));

    m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QObject::connect(m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    m_view->engine()->rootContext()->setContextProperty("loginManager", m_pLoginManager.data());
    m_view->engine()->rootContext()->setContextProperty("sessionListManager", m_pSessionListManager.data());
    m_view->engine()->rootContext()->setContextProperty("contactManager", m_pContactManager.data());
    m_view->engine()->rootContext()->setContextProperty("chatManager", m_pChatManager.data());
    m_view->engine()->rootContext()->setContextProperty("chatManagerModel", m_pChatManagerModel.data());
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
    if(option == CWorkspace::URL){
        m_pLoginManager->setIsStartupByUrl(true);
    }else{
        m_pLoginManager->setIsStartupByUrl(false);
    }
    qApp->runService("linkdoodservice", QStringList());
    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
       m_pLoginManager->getLoginHistory();
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

    scheme = scheme.toLower();
    path   = path.toLower();
    if (scheme == "linkdood") {
        if (path == "showlinkdood") {
            //linkDood:showLinkDood?id=xxx&pwd=xxx
            QString id = query.queryItemValue("id");
            QString pwd = query.queryItemValue("pwd");

            m_pLoginManager->text("url:"+id+":"+pwd);
            //showLinkDood(id, pwd);
            showLinkDoodByUrl(id);
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

void linkdoodui_Workspace::showLinkDood( QString &id,  QString &pwd)
{
    qDebug() << Q_FUNC_INFO << __LINE__ << id << " " << pwd;

    int appStatus    = m_pLoginManager->getAppLoginStatus();
    QString userHist = m_pLoginManager->getLoginPhoneId();
    if(appStatus == 1){
        QStringList info = m_pLoginManager->loginInfoByUrl().split(":");
        if(info.size()== 2){
            if(id == info.at(0)){
                emit switchChatPageByUrl();
                return;
            }else{
                m_pLoginManager->setLoginInfoByUrl(id+":"+"123456");
                m_pLoginManager->setLoginPhoneId(id);
                emit switchLoginByUrl();
                qDebug()<<Q_FUNC_INFO<<"login 3";
            }
        }else{
            m_pLoginManager->setLoginInfoByUrl(id+":"+"123456");
            m_pLoginManager->setLoginPhoneId(id);
            emit switchLoginByUrl();
            qDebug()<<Q_FUNC_INFO<<"login 4";
        }

    }else{
        if(!m_pLoginManager.isNull()){
            QString srv = m_pLoginManager->getLoginServiceId();
            if(srv == ""){
                m_pLoginManager->setLoginServiceId("10.17.60.42");
                srv = "10.17.60.42";
            }
            QStringList info = m_pLoginManager->loginInfoByUrl().split(":");
            if(info.size()== 2){
                pwd = info.at(1);
                id = (id ==info.at(0)?id:info.at(0));
                m_pLoginManager->login(srv,id+":7",pwd);

                qDebug()<<Q_FUNC_INFO<<"login 1";
            }else{
                m_pLoginManager->login(srv,id+":7","123456");
                pwd = "123456";
                qDebug()<<Q_FUNC_INFO<<"login 2";
            }
            m_pLoginManager->setLoginInfoByUrl(id+":"+pwd);
            m_pLoginManager->setLoginPhoneId(id);
        }
    }
}

void linkdoodui_Workspace::showLinkDoodByUrl(QString id)
{
    //srv
    QString srv = m_pLoginManager->getLoginServiceId();
    if(srv == ""){
        m_pLoginManager->setLoginServiceId("10.17.60.42");
        srv = "10.17.60.42";
    }

    //last login info
    QStringList lastAct = m_pLoginManager->loginInfoByUrl().split(":");
    QString oldId(""),oldPwd("123456");
    if(lastAct.size() == 2){
        oldId = lastAct.at(0);
        oldPwd = lastAct.at(1);
    }
    //current pwd
    QString pwd("123456");
    if(id == oldId){
        pwd = oldPwd;
    }
    //set config
    m_pLoginManager->setLoginInfoByUrl(id+":"+pwd);
    m_pLoginManager->setLoginPhoneId(id);

    // app server status
    int appStatus = m_pLoginManager->getAppLoginStatus();
    if(appStatus != 1){//offline
        m_pLoginManager->login(srv,id+":7",pwd);
    }else if(oldId == id){//same user
        emit switchChatPageByUrl();
    }else{//diff user
        emit switchLoginByUrl();
    }
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
    m_view->engine()->rootContext()->setContextProperty("chatManagerModel", m_pChatManager->chatModel());
    if(!m_pChatManager.isNull()){
        m_pChatManager->startPushChatPage();
    }
}

void linkdoodui_Workspace::onTransMessageSelectContactList(QList<QString> list,QString localId)
{
    qDebug()<<Q_FUNC_INFO;
    QString targetName(""),th("");
    if(!m_pChatManager.isNull()){
        for(int i = 0;i<list.size();++i){

            QStringList values = list.at(i).split(":");
            QString id = values.at(0),name = values.at(1);
            //fromat id:name
            if(!m_pContactManager.isNull()){
                CDoodContactItem* item = m_pContactManager->itemById(id);
                if(item != NULL){
                    targetName = item->name();
                    th = item->thumbAvatar();
                }else{
                    targetName = name;
                }
            }
            m_pChatManager->transforMessage(id,targetName,th,localId);
        }
    }
    if(!m_pContactManager.isNull()){
        m_pContactManager->clearMember();
    }
}

void linkdoodui_Workspace::onGroupRemoveOrExitResult(QString groupId)
{
    if(!m_pSessionListManager.isNull()){
        m_pSessionListManager->removeChatItem(groupId);
    }
    if(!m_pChatManager.isNull()){
        m_pChatManager->removeChat(groupId);
    }
}

void linkdoodui_Workspace::onUpdateSessionPageMsgReaded(QString targetId)
{
    if(!m_pSessionListManager.isNull()){
        m_pSessionListManager->clickChatItem(targetId);
    }
}

void linkdoodui_Workspace::onGroupMemsChanged(QString groupid, int size)
{
    if(!m_pChatManager.isNull()){
        m_pChatManager->groupMemsChanged(groupid,size);
    }
}

void linkdoodui_Workspace::onRemoveContactOper(QString id)
{
    if(!m_pSessionListManager.isNull()){
        m_pSessionListManager->removeChatItem(id);
    }
    if(!m_pChatManager.isNull()){
        m_pChatManager->removeChat(id);
    }
}

