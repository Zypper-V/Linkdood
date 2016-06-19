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

    QString msgtype;
    // 消息类型
    QString activeType;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    QString msgid;
    // 消息 ID
    QString targetid; // 会话者 ID (群或用户等)
    QString fromid;
    // 发送者 ID
    QString toid;
    // 接收者 ID
    QString localid; // 本地 ID
    QString relatedMsgid; // 关联消息 ID
    QString time;
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
    QString msgProperties;
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
    QString id;//id
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

//Contact
class Contact{
public:
    explicit Contact();
    void toImContact(QVariantMap map);
    void init();

public:

    QString gender; //性别:1男2女0保密
    int timeZone;//时区
    QString id;//id
    QString name; //名称
    QString avatar;//原图图像
    QString extends;//扩展字段
    QString thumbAvatar;//缩略图

    int isStar;	       //星标好友：1.星标好友，2.不是星标
    int isVip;            //V标好友： 1.V标好友,  2.不是V标
    QString pinyin;	   //名称拼音
    QString remark;    //备注
    QString server;    //服务器
};
Q_DECLARE_METATYPE(Contact)
QDBusArgument &operator << (QDBusArgument &argument, const Contact &contact);
const QDBusArgument &operator >> (const QDBusArgument &argument, Contact &contact);

typedef QList<Contact> ContactList;
Q_DECLARE_METATYPE (ContactList);
//Org
class Org{
public:
    explicit Org();
    void toImOrg(QVariantMap map);
    void init();

public:
    QString id;//id
    QString name; //名称
    QString avatar;//原图图像
    QString extends;//扩展字段
    QString thumbAvatar;//缩略图

    QString level;
    QString sonorg_count;
    QString leaf;
    QString ishidden;
    QString sonuser_count;
    QString parent_id;
    QString ent_id;
    QString order_num;
    QString branch_id;
    QString org_code;
};
Q_DECLARE_METATYPE(Org)
QDBusArgument &operator << (QDBusArgument &argument, const Org &org);
const QDBusArgument &operator >> (const QDBusArgument &argument, Org &org);

typedef QList<Org> OrgList;
Q_DECLARE_METATYPE (OrgList);
//OrgUser
class OrgUser{
public:
    explicit OrgUser();
    void toImOrgUser(QVariantMap map);
    void init();

public:
    QString id;//id
    QString name; //名称
    QString gender;//性别:1男2女0保密
    QString timeZone;//时区
    QString avatar;//原图图像
    QString extends;//扩展字段
    QString thumbAvatar;//缩略图

    QString order_num;
    QString ent_id;
    QString org_id;
    QString role_id;
    QString neworg_id;
    QString duty;
    QString email;
    QString phone;
    QString orgname;
    QString pinyin;
};
Q_DECLARE_METATYPE(OrgUser)
QDBusArgument &operator << (QDBusArgument &argument, const OrgUser &orguser);
const QDBusArgument &operator >> (const QDBusArgument &argument, OrgUser &orguser);

typedef QList<OrgUser> OrgUserList;
Q_DECLARE_METATYPE (OrgUserList);

//IMOfflineMsg text
class IMOfflineMsg{
public:
    explicit IMOfflineMsg(/*Msg& m*/);
    void init();

public:
    int     offlineType;  /*1未读消息 2设备已读消息*/
    int     count;      //数量
    MsgText msg;
    //Msg* msg;
    //QSharedPointer<Msg> msg;
};
Q_DECLARE_METATYPE(IMOfflineMsg)
QDBusArgument &operator << (QDBusArgument &argument, const IMOfflineMsg &offlineMsg);
const QDBusArgument &operator >> (const QDBusArgument &argument, IMOfflineMsg &offlineMsg);

typedef QList<IMOfflineMsg> IMOfflineMsgList;
Q_DECLARE_METATYPE (IMOfflineMsgList);

inline void registerDoodDataTypes() {
    qDebug() << Q_FUNC_INFO;
    qDBusRegisterMetaType<Msg>();
    qDBusRegisterMetaType<MsgList>();
    qRegisterMetaType<MsgList>("MsgList");

    qDBusRegisterMetaType<Chat_UI>();
    qDBusRegisterMetaType<Chat_UIList>();
    qRegisterMetaType<Chat_UIList>("Chat_UIList");

    qDBusRegisterMetaType<Contact>();
    qDBusRegisterMetaType<ContactList>();
    qRegisterMetaType<ContactList>("ContactList");

    qDBusRegisterMetaType<IMOfflineMsg>();
    qDBusRegisterMetaType<IMOfflineMsgList>();
    qRegisterMetaType<IMOfflineMsgList>("IMOfflineMsgList");
}
#endif // LINKDOODTYPES_H


