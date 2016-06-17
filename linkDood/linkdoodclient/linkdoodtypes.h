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

//MsgText
class MsgText:public Msg{
public:
    explicit MsgText();

    void toImMassage(QVariantMap map);

    void init();

public:
    QString msg_properties;
};
Q_DECLARE_METATYPE(MsgText)
QDBusArgument &operator << (QDBusArgument &argument, const MsgText &msg);
const QDBusArgument &operator >> (const QDBusArgument &argument, MsgText &msg);
// ImMassageList
typedef QList<MsgText> MsgTextList;

//Chat_UI
class Chat_UI
{
public:
    explicit Chat_UI();

    void toImChat(QVariantMap map);

    void init();

public:

    int gender; //性别:1男2女0保密
    int time_zone;//时区
    int64 id;//id
    QString name; //名称
    QString avatar;//原图图像
    QString extends;//扩展字段
    QString thumb_avatar;//缩略图

    int     msg_type;		 //	消息类型;1：HTML, 2:TEXT, 3：AUDIO, 4：POSITION, 5：IMG, 6：FILE, 7：CARD,  8：TIP
    int     chat_type;	     //  聊天类型
    int     oper_type;       //  活动类型
    int     sub_type;        //  子操作类型标示,置顶等其他操作
    int     unread_count;    //未读消息数量
    int64   last_msgid;    //最后一条消息ID
    QString msg_time;      //消息时间
    QString last_msg;//最后一条消息
};

// Chat_UI
Q_DECLARE_METATYPE(Chat_UI)
QDBusArgument &operator << (QDBusArgument &argument, const Chat_UI &chat);
const QDBusArgument &operator >> (const QDBusArgument &argument, Chat_UI &chat);
// ImMassageList
typedef QList<Chat_UI> Chat_UIList;
Q_DECLARE_METATYPE (Chat_UIList);

inline void registerDoodDataTypes() {
    qDebug() << Q_FUNC_INFO;
    qDBusRegisterMetaType<Msg>();
    qDBusRegisterMetaType<MsgList>();
    qRegisterMetaType<MsgList>("MsgList");

    qDBusRegisterMetaType<Chat_UI>();
    qDBusRegisterMetaType<Chat_UIList>();
    qRegisterMetaType<Chat_UIList>("Chat_UIList");
}
#endif // LINKDOODTYPES_H


