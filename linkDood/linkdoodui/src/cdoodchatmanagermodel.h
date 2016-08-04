#ifndef CDOODCHATMANAGERMODEL_H
#define CDOODCHATMANAGERMODEL_H

#include <QObject>
#include <QMimeData>
#include <QDebug>
#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QTextBlock>
#include <QTextFormat>
#include <QQuickTextDocument>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"
#include "common.h"

class CDoodChatItem;

class CDoodChatManagerModel : public CDoodListModel
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString chatType READ chatType WRITE setChatType NOTIFY chatTypeChanged)

public:
    explicit CDoodChatManagerModel(QObject *parent = 0);

    void updateGroupMems(MemberList list);

    int msgCount();
    void addHistoryMsgToListView(MsgList msgList);
    void addItemToListViewModel(Msg msg,QString textMsgContent="",bool isHistory = false);
    void modifyItemToListViewModel(Msg msg,bool isLoading=false,int progress=0);
    void clearList();
    void removeItemById(QString id);
    void analyzeHistoryMsg(MsgList msgList);
    void updateAvatar(QString id,QString avater);
    void updateLastMsgId(QString lastMsgId);
    void setAccountId(QString id);
    void updateAccountUserInfo(QString id,QString name,QString avatar);
    void updateItemNameAndAvatar(QString localId,QString userId);
    void updateItemData(QString userId,QString name,QString avater);
    bool msgIsExitById(QString id);

    QString lastMsgId();
    QString firstMsgId();
    int  groupMemsCount();
    void addChatItemtoMap(CDoodChatItem* chatItem);
    CDoodChatItem* itemById(QString id);

    ~CDoodChatManagerModel();

    QString id()const;
    QString name()const;
    QString avatar()const;
    QString chatType() const;
    QString setChatType(const QString &data);

    void   setAvatar(const QString &data);
    void   setId(const QString&id);
    void   setName(const QString&name);


signals:
    void idChanged();
    void nameChanged();
    void chatTypeChanged();
    void avatarChanged();
    void reqestUserInfo(QString uerId);
    void downloadImage(QString targetId,QString localId,QString url,QString enkey);
protected:
    void judgeAddTimeTip(QDateTime date);
    bool isJudageShowTime(QDateTime date);
public:
    int     mNeedNewMsgCount;
    QString mNeedNewMsgLastId;
private:
    QMap<QString, CDoodChatItem*> m_pChatMap;
    MemberList mGroupMemList;

    QString mId;
    QString mName;
    QString m_sBeginMsgId;
    QString m_sTargetid;
    QString mChatType;

    QString mAvatar;
    QString mAccountUserId;
    QString mAccountAvater;
    QString mAccountName;

};

#endif // CDOODCHATMANAGERMODEL_H
