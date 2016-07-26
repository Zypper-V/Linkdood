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
    void addItemToListViewModel(Msg msg,QString textMsgContent="");
    void modifyItemToListViewModel(Msg msg,bool isLoading=false,int progress=0);
    void clearList();
    void removeItemById(QString id);
    void analyzeMsg(MsgList msgList);
    void updateAvatar(QString id,QString avater);
    void updateUnreadMsg(QString lastMsgId,int count);
    void setAccountId(QString id);
    void updateAccountUserInfo(QString id,QString name,QString avatar);
    void updateItemNameAndAvatar(QString localId,QString userId);
    void updateItemData(QString userId,QString name,QString avater);
    CDoodChatItem* itemById(QString id);

    ~CDoodChatManagerModel();

    QString id()const;
    QString name()const;
    QString avatar()const;
    QString chatType() const;
    QString setChatType(const QString &data);
    QString lastMsgId();
    int     unReadMsgCount();

    void   setAvatar(const QString &data);
    void   setId(const QString&id);
    void   setName(const QString&name);


signals:
    void idChanged();
    void nameChanged();
    void chatTypeChanged();
    void avatarChanged();
protected:
    void judgeAddTimeTip(QDateTime date);

private:
    QMap<QString, CDoodChatItem*> m_pChatMap;
    MemberList mGroupMemList;

    QString mId;
    QString mName;
    QString m_sBeginMsgId;
    QString m_sTargetid;
    QString mChatType;
    int     mTotalUnreadMsgCount;
    QString mLastMsgId;
    QString mAvatar;

    QString mAccountUserId;
    QString mAccountAvater;
    QString mAccountName;
};

#endif // CDOODCHATMANAGERMODEL_H
