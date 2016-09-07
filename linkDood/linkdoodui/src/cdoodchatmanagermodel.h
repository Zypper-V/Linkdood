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
    Q_PROPERTY(QString draft READ draft WRITE setDraft NOTIFY draftChanged)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString chatType READ chatType WRITE setChatType NOTIFY chatTypeChanged)

public:
    explicit CDoodChatManagerModel(QObject *parent = 0);
    Q_INVOKABLE QString getLastMsgid();
    Q_INVOKABLE QString bigImageExisted(QString localId);
    Q_INVOKABLE bool    fileExistAtLocal(QString fullPath);

    Q_INVOKABLE int imageWidth(QString path);
    Q_INVOKABLE int imageHeight(QString path);

    void reloadImageMsg();
    void updateGroupMems(MemberList list);
    void updateGroupSize(int size);
    int msgCount();
    void addHistoryMsgToListView(MsgList msgList);
    void addItemToListViewModel(Msg msg,QString textMsgContent="",bool isHistory = false);

    void modifyItemToListViewModel(Msg msg,bool isLoading=false,int progress=0);
    void clearList();
    void removeItemById(QString id);
    void removeItemByMsgId(QString msgId);
    void removeItemsByFromId(QString fromId);
    void deleteAllMessage();
    void analyzeHistoryMsg(MsgList msgList);
    void updateAvatar(QString id,QString avater);
    void updateLastMsgId(QString lastMsgId);
    void setAccountId(QString id);
    void updateAccountUserInfo(QString id,QString name,QString avatar);
    void updateItemNameAndAvatar(QString localId,QString userId);
    void updateItemData(QString userId,QString name,QString avater);
    bool msgIsExitById(QString id);
    void updateGroupChatInfo(QString userId,QString name,QString thum);
    int  indexOfNewItem(QDateTime date);
    void addGroupMems(MemberList mems);
    QString getChatName();

    QString lastMsgId();
    QString firstMsgId();
    int  groupMemsCount();
    void addChatItemtoMap(CDoodChatItem* chatItem);
    CDoodChatItem* itemById(QString id);

    ~CDoodChatManagerModel();

    QString draft();
    Q_INVOKABLE void setDraft(QString data);
    Q_INVOKABLE void exitChat();

    QString id()const;
    QString name()const;
    QString avatar()const;
    QString chatType() const;
    QString setChatType(const QString &data);

    void   setAvatar(const QString &data);
    void   setId(const QString&id);
    void   setName(const QString&name);


signals:
    void draftChanged(QString draft);
    void draftChanged();
    void idChanged();
    void nameChanged();
    void chatTypeChanged();
    void avatarChanged();
    void reqestUserInfo(QString uerId);
    void downloadImage(QString targetId,QString localId,QString url,QString enkey);
    void updateDataFinished();
    void setMsgRead(QString msgid);
    void deleteMessage(QString targetId,QStringList msgs);
protected:
    void judgeAddTimeTip(QDateTime date);
    bool isJudageShowTime(QDateTime date);
public:
    int     mNeedNewMsgCount;
    QString mNeedNewMsgLastId;
    int     mGroupSize;
    QString createLocalId();
private:
    QMap<QString, CDoodChatItem*> m_pChatMap;
    MemberList mGroupMemList;
    LinkDoodClient *m_pClient;

    QString mId;
    QString mName;
    QString m_sBeginMsgId;
    QString m_sTargetid;
    QString mChatType;

    QString mAvatar;
    QString mAccountUserId;
    QString mAccountAvater;
    QString mAccountName;
    QString mDraft;

};

#endif // CDOODCHATMANAGERMODEL_H
