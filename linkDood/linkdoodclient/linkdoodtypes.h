#ifndef LINKDOODTYPES_H
#define LINKDOODTYPES_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <QtDBus/QtDBus>
#define int64 long long

enum MSG_TYPE{
MSG_TYPE_HTML = 1, //网页类型
MSG_TYPE_TEXT,//文本类型
MSG_TYPE_AUDIO,//音视频类型
MSG_TYPE_POSITION,//位置类型
MSG_TYPE_IMG,//图片类型
MSG_TYPE_FILE,//文件类型
MSG_TYPE_CARD,//名片类型
MSG_TYPE_TIP//提示类型
};


class Msg
{
public:
    explicit Msg();

    void toImMassage(QVariantMap map);

private:
    void init();

public:

    int msgtype;
    // 消息类型
    int active_type;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    int64 msgid;
    // 消息 ID
    int64 targetid; // 会话者 ID (群或用户等)
    int64 fromid;
    // 发送者 ID
    int64 toid;
    // 接收者 ID
    int64 localid; // 本地 ID
    int64 related_msgid; // 关联消息 ID
    int64 time;
    // 发送时间
    QString body;// 消息内容
   // QList<int64> related_users;// 秘聊时相关的用户 ID
   // QList<int64> limit_range; //@ 人员列表
};

// Msg
Q_DECLARE_METATYPE(Msg)
QDBusArgument &operator << (QDBusArgument &argument, const Msg &msg);
const QDBusArgument &operator >> (const QDBusArgument &argument, Msg &msg);
// ImMassageList
typedef QList<Msg> MsgList;
Q_DECLARE_METATYPE (MsgList);


#endif // LINKDOODTYPES_H
