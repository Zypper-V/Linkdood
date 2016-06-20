#ifndef CDOODCHATITEM_H
#define CDOODCHATITEM_H

#include <QObject>
#define int64 long long

class CDoodChatItem : public QObject
{
    Q_OBJECT

public:
    explicit CDoodChatItem(QObject *parent = 0);

signals:

public slots:
private:
    QString mMsgtype;// 消息类型
    QString mActiveType;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    QString mMsgid;// 消息 ID
    QString mTargetid; // 会话者 ID (群或用户等)
    QString mFromid;// 接收者 ID
    QString mToid;// 发送者 ID
    QString mLocalid; // 本地 ID
    QString mRelatedMsgid; // 关联消息 ID
    QString mTime;// 发送时间
    QString mBody;// 消息内容
    QString msgProperties;
};

#endif // CDOODCHATITEM_H
