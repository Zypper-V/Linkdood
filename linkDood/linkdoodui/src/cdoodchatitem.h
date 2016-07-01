#ifndef CDOODCHATITEM_H
#define CDOODCHATITEM_H

#include <QObject>
#include <QDateTime>

#define int64 long long

class CDoodChatItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString msgType READ msgType WRITE setMsgType NOTIFY msgTypeChanged)
    Q_PROPERTY(QString activeType READ activeType WRITE setActiveType NOTIFY activeTypeChanged)
    Q_PROPERTY(QString msgId READ msgId WRITE setMsgId NOTIFY msgIdChanged)
    Q_PROPERTY(QString targetId READ targetId WRITE setTargetId NOTIFY targetIdChanged)
    Q_PROPERTY(QString fromId READ fromId WRITE setFromId NOTIFY fromIdChanged)
    Q_PROPERTY(QString toId READ toId WRITE setToId NOTIFY toIdChanged)
    Q_PROPERTY(QDateTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString thumbAvatar READ thumbAvatar WRITE setThumbAvatar NOTIFY thumbAvatarChanged)
    Q_PROPERTY(QString tar_thumbAvatar READ tar_thumbAvatar WRITE setTar_thumbAvatar NOTIFY tar_thumbAvatarChanged)




public:

    explicit CDoodChatItem(QObject *parent = 0);

    QString name() const;
    QString setName(const QString &data);

    QString thumbAvatar() const;
    QString setThumbAvatar(const QString &data);

    QString tar_thumbAvatar() const;
    QString setTar_thumbAvatar(const QString &data);

    QString msgType() const;
    QString setMsgType(const QString &data);

    QString activeType() const;
    QString setActiveType(const QString &data);

    QString msgId() const;
    QString setMsgId(const QString &data);

    QString targetId() const;
    QString setTargetId(const QString &data);

    QString fromId() const;
    QString setFromId(const QString &data);

    QString toId() const;
    QString setToId(const QString &data);

    QDateTime time() const;
    QDateTime setTime(const QDateTime &data);

    QString body() const;
    QString setBody(const QString &data);


signals:
    void thumbAvatarChanged();
    void tar_thumbAvatarChanged();
    void msgTypeChanged();
    void activeTypeChanged();
    void msgIdChanged();
    void targetIdChanged();
    void fromIdChanged();
    void toIdChanged();
    void timeChanged();
    void bodyChanged();
    void nameChanged();


private:
    QString mName;
    QString mThumbAvatar;
    QString mTar_thumbAvatar;
    QString mMsgType;// 消息类型
    QString mActiveType;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    QString mMsgId;// 消息 ID
    QString mTargetId; // 会话者 ID (群或用户等)
    QString mFromId;// 发送者 ID
    QString mToId;// 发送者 ID
    QDateTime mTime;// 发送时间
    QString mBody;// 消息内容
};

#endif // CDOODCHATITEM_H
