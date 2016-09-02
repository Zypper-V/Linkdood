#ifndef __LINKDOODUI_WORKSPACE__
#define __LINKDOODUI_WORKSPACE__

#include <QQuickView>
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <SyberosGuiCache>
#include <cgui_application.h>
#include <cworkspace.h>
#include "cdoodchatmanagermodel.h"

#include <QScopedPointer>

using namespace SYBEROS;

class CDoodLoginManager;
class CDoodSessionListManager;
class LinkDoodClient;
class CDoodContactManager;
class CDoodChatManager;
class CDoodChatManagerModel;
class CDoodUserDataManage;
class CDoodEnterpriseManager;
class CDoodOrgManager;
class CDoodUserProfileManager;
class CDoodEmojiManager;
class CDoodAddContactManager;
class CDoodGroupManager;
class CDoodMemberManager;
class CDoodFriendVerificationManager;
class CDoodSysMsgManager;
class CDoodLocalSearchManager;
class CDoodFileViewManager;

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
    void getGroupInfoFromList(QString groupId,QString&name,QString&avatar);
    void getContactInforFromList(QString id,QString& name,QString& avater);
signals:
    void switchLoginByUrl();
    void switchChatPageByUrl();
private:
    void showLinkDood( QString &id,  QString &pwd);
    void showLinkDoodByUrl( QString id);
    void setActiveWindow();
protected slots:
    void onChatPageChanged();
    void onTransMessageSelectContactList(QList<QString>list,QString localId);
    void onGroupRemoveOrExitResult(QString groupId);
    void onUpdateSessionPageMsgReaded(QString targetId);
    void onGroupMemsChanged(QString groupid,int size);
    void onRemoveContactOper(QString id);
private:
    QSharedPointer<CDoodLoginManager> m_pLoginManager;
    QSharedPointer<CDoodSessionListManager> m_pSessionListManager;
    QSharedPointer<CDoodContactManager> m_pContactManager;
    QSharedPointer<CDoodChatManager> m_pChatManager;
    QSharedPointer<CDoodChatManagerModel> m_pChatManagerModel;
    QSharedPointer<CDoodUserDataManage> m_pUserDataManager;
    QSharedPointer<CDoodEnterpriseManager> m_pEnterPriseManager;
    QSharedPointer<CDoodOrgManager> m_pOrgManager;
    QSharedPointer<CDoodEmojiManager> m_pEmojiManager;
    QSharedPointer<CDoodEmojiManager> m_pDyEmojiManager;
    QSharedPointer<CDoodGroupManager> m_pGroupManager;
    QSharedPointer<CDoodMemberManager> m_pMemberManager;
    QSharedPointer<LinkDoodClient> m_pClient;
    QSharedPointer<CDoodUserProfileManager> m_pUserProfileManager;
    QSharedPointer<CDoodAddContactManager> m_pAddContactManager;
    QSharedPointer<CDoodFriendVerificationManager> m_pFriendVerificationManager;
    QSharedPointer<CDoodSysMsgManager> m_pSysmsgManager;
    QSharedPointer<CDoodLocalSearchManager> m_pLocalSearchManager;
    QSharedPointer<CDoodFileViewManager> m_pFileViewManager;

    CDoodChatManagerModel* m_pChatModel;
    void initConnects();
};


#endif //__LINKDOODUI_WORKSPACE__
