#ifndef CDOODCHATITEM_H
#define CDOODCHATITEM_H

#include <QObject>
#define int64 long long

class CDoodChatItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString msgType READ msgType WRITE setMsgType NOTIFY msgTypeChanged)
    Q_PROPERTY(QString activeType READ activeType WRITE setActiveType NOTIFY activeTypeChanged)
    Q_PROPERTY(QString msgId READ msgId WRITE setMsgId NOTIFY msgIdChanged)
    Q_PROPERTY(QString targetId READ targetId WRITE setTargetId NOTIFY targetIdChanged)
    Q_PROPERTY(QString fromId READ fromId WRITE setFromId NOTIFY fromIdChanged)
    Q_PROPERTY(QString toId READ toId WRITE setToId NOTIFY toIdChanged)
    Q_PROPERTY(QString localId READ localId WRITE setLocalId NOTIFY localIdChanged)
    Q_PROPERTY(QString relatedMsgId READ relatedMsgId WRITE setRelatedMsgId NOTIFY relatedMsgIdChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString sgProperties READ sgProperties WRITE setSgProperties NOTIFY sgPropertiesChanged)

public:

    explicit CDoodChatItem(QObject *parent = 0);

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

    QString localId() const;
    QString setLocalId(const QString &data);

    QString relatedMsgId() const;
    QString setRelatedMsgId(const QString &data);

    QString time() const;
    QString setTime(const QString &data);

    QString body() const;
    QString setBody(const QString &data);

    QString sgProperties() const;
    QString setSgProperties(const QString &data);


signals:
    void msgTypeChanged();
    void activeTypeChanged();
    void msgIdChanged();
    void targetIdChanged();
    void fromIdChanged();
    void toIdChanged();
    void localIdChanged();
    void relatedMsgIdChanged();
    void timeChanged();
    void bodyChanged();
    void sgPropertiesChanged();

private:
    QString mMsgYype;// 消息类型
    QString mActiveType;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    QString mMsgId;// 消息 ID
    QString mTargetId; // 会话者 ID (群或用户等)
    QString mFromId;// 接收者 ID
    QString mToId;// 发送者 ID
    QString mLocalId; // 本地 ID
    QString mRelatedMsgId; // 关联消息 ID
    QString mTime;// 发送时间
    QString mBody;// 消息内容
    QString msgProperties;
};

#endif // CDOODCHATITEM_H
