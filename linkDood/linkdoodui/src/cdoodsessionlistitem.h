#ifndef CDOODSESSIONLISTITEM_H
#define CDOODSESSIONLISTITEM_H

#include <QObject>
#define int64 long long
class CDoodSessionListItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString draft READ draft WRITE setDraft NOTIFY draftChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString msgType READ msgType WRITE setMsgType NOTIFY msgTypeChanged)
    Q_PROPERTY(QString chatType READ chatType WRITE setChatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QString operType READ operType WRITE setOperType NOTIFY operTypeChanged)
    Q_PROPERTY(QString subType READ subType WRITE setSubType NOTIFY subTypeChanged)
    Q_PROPERTY(QString unReadCount READ unReadCount WRITE setUnReadCount NOTIFY unReadCountChanged)
    Q_PROPERTY(QString lastMsgid READ lastMsgid WRITE setLastMsgid NOTIFY lastMsgidChanged)
    Q_PROPERTY(QString msgTime READ msgTime WRITE setMsgTime NOTIFY msgTimeChanged)
    Q_PROPERTY(QString lastMsg READ lastMsg WRITE setLastMsg NOTIFY lastMsgChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)


public:
    explicit CDoodSessionListItem(QObject *parent = 0);

    void setUnreadMsgCOunt(int count);
    int  unReadMsgCount();
    qint64 dateTime();

    QString id() const;
    QString setId(const QString &data);

    void    setDraft(QString data);
    QString draft();

    QString name() const;
    Q_INVOKABLE QString setName(const QString &data);

    QString msgType() const;
    QString setMsgType(const QString &data);

    QString chatType() const;
    QString setChatType(const QString &data);

    QString operType() const;
    QString setOperType(const QString &data);

    QString subType() const;
    QString setSubType(const QString &data);

    QString unReadCount() const;
    QString setUnReadCount(const QString &data);

    QString lastMsgid() const;
    QString setLastMsgid(const QString &data);

    QString msgTime() const;
    QString setMsgTime(const QString &data);

    QString lastMsg() const;
    QString setLastMsg(QString data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);



signals:
    void draftChanged();
    void idChanged();
    void nameChanged();
    void msgTypeChanged();
    void chatTypeChanged();
    void operTypeChanged();
    void subTypeChanged();
    void unReadCountChanged();
    void lastMsgidChanged();
    void msgTimeChanged();
    void lastMsgChanged();
    void thumbAvatarChanged();


public slots:

private:
    QString mId;
    QString mName;
    QString mMsgType;
    QString mChatType;
    QString mOperType;
    QString mSubType;
    QString mUnReadCount;
    QString mLastMsgid;
    QString mMsgTime;
    QString mLastMsg;
    QString mThumbAvatar;
    int     mUnreadMsgCount;
    QString mdraft;
};
#endif // CDOODSESSIONLISTITEM_H
