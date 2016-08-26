#ifndef LINKDOODTYPES_H
#define LINKDOODTYPES_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <QtDBus/QtDBus>


#define int64 long long
//表情匹配符
#define EMOJI_IMAGE   "[4f072095e2574b66aa0c6c09acfb3f3e]"
#define EMOJI_REG       "(\\[4f072095e2574b66aa0c6c09acfb3f3e\\](.*?)\\[4f072095e2574b66aa0c6c09acfb3f3e\\])"
#define SYSMSG_ID      "-5"
enum ImageSize{
    THUMP_PIC_WIDTH   =  400,
    THUMP_PIC_HEIGHT  =  300,
    BIG_PIC_WIDTH      =     1920,
    BIG_PIC_HEIGHT      =    1080
};
#define COMPUTER_CHAT 6
enum MSG_TYPE{
    MSG_TYPE_HTML = 1, //网页类型
    MSG_TYPE_TEXT,//文本类型
    MSG_TYPE_AUDIO,//音视频类型
    MSG_TYPE_POSITION,//位置类型
    MSG_TYPE_IMG,//图片类型
    MSG_TYPE_FILE,//文件类型
    MSG_TYPE_CARD,//名片类型
    MSG_TYPE_TIP,//提示类型
    MEDIA_MSG_MULTIMSG = 13,//组合消息
    MEDIA_MSG_VIDEO = 14,	//视频消息
    MEDIA_MSG_REVOKE = 18,	//撤回消息
    MEDIA_MSG_DYNAMIC_EMOJI = 19,//动态表情
    MEDIA_MSG_RED_PARKET = 88,	//红包
    MEDIA_MSG_SUPER = 0xFF,
    MSG_TYPE_TIME = 100
};

#define APP_DATA_PATH "/data/data/com.vrv.linkDood/"
#define APP_SAVE_FILE_APTH "/home/user/tiangongyuanyuan/file"
#define APP_SAVE_IAMGE_APTH "/home/user/tiangongyuanyuan/image"
#define  APP_SAVE_DATA_PATH "/home/user/tiangongyuanyuan"
//IMSysMsgRespInfo
class IMSysMsgRespInfo
{
public:
    explicit IMSysMsgRespInfo();
    virtual ~IMSysMsgRespInfo(){}
    void toIMSysMsgRespInfo(QVariantMap map);

    QString targetid;//目标ID
    QString msgid;   //消息ID
    int     msgtype; //消息类型
    int     opertype;//活动类型
    QString info;//消息回复内容
};
Q_DECLARE_METATYPE(IMSysMsgRespInfo)
QDBusArgument &operator << (QDBusArgument &argument, const IMSysMsgRespInfo &info);
const QDBusArgument &operator >> (const QDBusArgument &argument, IMSysMsgRespInfo &info);
//
typedef QList<IMSysMsgRespInfo> IMSysMsgRespInfoList;
Q_DECLARE_METATYPE (IMSysMsgRespInfoList);

//IMSysMsg
class IMSysMsg
{
public:
    explicit IMSysMsg();
    virtual ~IMSysMsg(){}
    void toIMSysMsg(QVariantMap map);


    bool    isShowButton;  //是否显示按钮
    QString msgid;         //消息ID
    QString targetid;      //目标ID
    QString time;          //时间
    QString msgtypeText;   //消息类型
    QString name;          //消息来源名称
    QString avatar;        //消息来源头像
    QString respons;       //响应
    QString info;          //消息内容
    QString msgType;
    QString operUser;      //操作人名字
    QString isread;        //是否已读  ０未读，１已读 isRead.

};
Q_DECLARE_METATYPE(IMSysMsg)
QDBusArgument &operator << (QDBusArgument &argument, const IMSysMsg &info);
const QDBusArgument &operator >> (const QDBusArgument &argument, IMSysMsg &info);
//
typedef QList<IMSysMsg> IMSysMsgList;
Q_DECLARE_METATYPE (IMSysMsgList);

//LoginInfo
class LoginInfo{
public:

    explicit LoginInfo();
    virtual ~LoginInfo(){}
    void toImLoginInfo(QVariantMap map);

    int64 status;
    int64 isRemberPass;        //是否记住密码
    int64 isAutoLogin;         //自动登录
    int64 userId;              //用户id
    int64 lastLoginTime;     //上次登陆时间
    QString server;            //服务器
    QString name;               //用户名
    QString account;			//账号
    QString userIcon;          //头像
    QString areaNum;           //国家码
};
Q_DECLARE_METATYPE(LoginInfo)
QDBusArgument &operator << (QDBusArgument &argument, const LoginInfo &info);
const QDBusArgument &operator >> (const QDBusArgument &argument, LoginInfo &info);
//
typedef QList<LoginInfo> LoginInfoList;
Q_DECLARE_METATYPE (LoginInfoList);

//Msg
class Msg
{
public:
    explicit Msg();
    virtual ~Msg(){}
    void toImMassage(QVariantMap map);

    void init();

public:

    QString name;//名称
    QString thumb_avatar;//缩略图
    QString msgtype;
    // 消息类型
    QString activeType;// 消息事件属性 1. 阅后即焚 2 有问必答 3 活动
    QString
    msgid;
    // 消息 ID
    QString targetid; // 会话者 ID (群或用户等)
    QString targetName;
    QString fromid;
    // 发送者 ID
    QString toid;
    // 接收者 ID
    QString localid; // 本地 ID
    QString relatedMsgid; // 关联消息 ID
    QString time;
    // 发送时间
    QString body;// 消息内容
    QString msgProperties;

    QString f_state;
    QString f_id;
    QString f_size;
    QString encrypt_user;
    QString encrypt_key;
    QString f_path;
    QString f_url;
    QString filename;

    QString i_width;
    QString i_height;
    QString thumb_url;
    QString fromName;
    QString main_url;
    bool    isTransMsg;
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
    QString nick_id;
    QString email;
    QString phone;
    QString birthday;
    int     team;
};
Q_DECLARE_METATYPE(Contact)
QDBusArgument &operator << (QDBusArgument &argument, const Contact &contact);
const QDBusArgument &operator >> (const QDBusArgument &argument, Contact &contact);

typedef QList<Contact> ContactList;
Q_DECLARE_METATYPE (ContactList);
//Group
class Group{
public:
    explicit Group();
    void toImGroup(QVariantMap map);
    void init();

public:

    QString timeZone;//时区
    QString id;//id
    QString name; //名称
    QString avatar;//原图图像
    QString thumbAvatar;//缩略图

    QString level;  //群等级（1,2,3,4)1是临时群，2是普通群
    QString pinyin;//名称拼音
    QString server;//服务器

    QString brief;    //群简介
    QString bulletin; //群公告
    QString extend;   //群扩展字段
    QString createrid;//创建者ID
    QString create_time;     //创建时间
    QString related_groupid; //关联群ID
    QString related_entid;   //关联企业ID，存在此ID则属于企业群
    QString member_nums;       //群成员数量
};
Q_DECLARE_METATYPE(Group)
QDBusArgument &operator << (QDBusArgument &argument, const Group &group);
const QDBusArgument &operator >> (const QDBusArgument &argument, Group &group);

typedef QList<Group> GroupList;
Q_DECLARE_METATYPE (GroupList);
//Member
class Member{
public:
    explicit Member();
    void toImMember(QVariantMap map);
    void init();

public:

    QString id;//id
    QString name; //名称
    QString gender;//性别:1男2女0保密
    QString avatar;//原图图像
    QString thumbAvatar;//缩略图

    QString groupid;     //群id
    QString team;          //分组
    QString member_type;  //成员类型：1.普通 2.管理员 3.超级管理员
    QString remark;//群备注
};
Q_DECLARE_METATYPE(Member)
QDBusArgument &operator << (QDBusArgument &argument, const Member &member);
const QDBusArgument &operator >> (const QDBusArgument &argument, Member &member);

typedef QList<Member> MemberList;
Q_DECLARE_METATYPE (MemberList);
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
// QOnlineState
class QOnlineState{
public:
    explicit QOnlineState();
    void toImQOnlineState(QVariantMap map);
    void init();

public:
    QString userid;//用户id
    QString connectId; //关联id
    QString deviceType;//在线设备类型
    QString flag;//在线状态
};
Q_DECLARE_METATYPE(QOnlineState)
QDBusArgument &operator << (QDBusArgument &argument, const QOnlineState &onlinestate);
const QDBusArgument &operator >> (const QDBusArgument &argument, QOnlineState &onlinestate);

typedef QList<QOnlineState> QOnlineStateList;
Q_DECLARE_METATYPE (QOnlineStateList);

//IMOfflineMsg text
class IMOfflineMsg{
public:
    explicit IMOfflineMsg(/*Msg& m*/);
    void toImOfflineMsg(QVariantMap map);
    void init();

public:
    int     offlineType;  /*1未读消息 2设备已读消息*/
    int     count;      //数量
    QString msgId;
    QString body;
    QString targetId;
    QString fromId;
    QString time;
    QString name;
};
Q_DECLARE_METATYPE(IMOfflineMsg)
QDBusArgument &operator << (QDBusArgument &argument, const IMOfflineMsg &offlineMsg);
const QDBusArgument &operator >> (const QDBusArgument &argument, IMOfflineMsg &offlineMsg);

typedef QList<IMOfflineMsg> IMOfflineMsgList;
Q_DECLARE_METATYPE (IMOfflineMsgList);

inline QString genderConvert(int sex){
    QString cur("保密");

    switch (sex) {
    case 1:
        cur = "男";
        break;
    case 2:
        cur = "女";
        break;
    default:
        break;
    }
    return cur;
}

inline int genderConvert(QString sex){
    if(sex == "保密"){
        return 0;
    }
    if(sex == "男"){
        return 1;
    }
    if(sex == "女"){
        return 2;
    }
    return 0;
}
//MsgFileInfo
class MsgFileInfo{
public:
    explicit MsgFileInfo();
    void toImMsgFileInfo(QVariantMap map);
    void init();

    QString fileid;                 //文件ID
    QString userid;                 //发送者ID
    QString username;               //发送者名称
    QString targetid;               //目标ID,可以是群,也可以是用户
    QString size;                   //文件大小
    QString time;                   //上传时间
    QString path;                   //本地路径
    QString name;                   //文件名
    QString url;                    //文件url
    QString encrypt_key;            //加密KEY
};

Q_DECLARE_METATYPE(MsgFileInfo)
QDBusArgument &operator << (QDBusArgument &argument, const MsgFileInfo &fileInfo);
const QDBusArgument &operator >> (const QDBusArgument &argument, MsgFileInfo &fileInfo);

class IMPrivateSetting{
public:
    IMPrivateSetting() :allow_phone(0), allow_email(0), allow_birthday(0),verifytype(0),vip_noticetype(0),
    at_noticetype(0),global_noticetype(0){}
    int allow_birthday;		//	生日可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
    int allow_phone;		//	电话可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
    int allow_email;		//	邮箱可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
    int verifytype;			//	验证方式 1：需要验证信息,2:不允许任何人添加,3:允许任何人添加，默认1
    int vip_noticetype;		//	V标消息通知类型 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1
    int at_noticetype;		//	@相关人提醒模式 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1
    int global_noticetype;	//	全局消息通知 1:通知详情，2：通知源，隐藏内容 3:完全隐藏，默认2
};
Q_DECLARE_METATYPE(IMPrivateSetting)
QDBusArgument &operator << (QDBusArgument &argument, const IMPrivateSetting &priset);
const QDBusArgument &operator >> (const QDBusArgument &argument, IMPrivateSetting &priset);

typedef QList<MsgFileInfo> FileInfoList;
Q_DECLARE_METATYPE (FileInfoList);

inline void registerDoodDataTypes() {
    qDebug() << Q_FUNC_INFO;
    qDBusRegisterMetaType<Msg>();
    qDBusRegisterMetaType<MsgList>();
    qRegisterMetaType<MsgList>("MsgList");

    qDBusRegisterMetaType<Chat_UI>();
    qDBusRegisterMetaType<Chat_UIList>();
    qRegisterMetaType<Chat_UIList>("Chat_UIList");

    qDBusRegisterMetaType<int64>();
    qRegisterMetaType<int64>("int64");

    qDBusRegisterMetaType<Contact>();
    qDBusRegisterMetaType<ContactList>();
    qRegisterMetaType<ContactList>("ContactList");

    qDBusRegisterMetaType<Group>();
    qDBusRegisterMetaType<GroupList>();
    qRegisterMetaType<GroupList>("GroupList");

    qDBusRegisterMetaType<MsgFileInfo>();
    qDBusRegisterMetaType<FileInfoList>();
    qRegisterMetaType<FileInfoList>("FileInfoList");

    qDBusRegisterMetaType<Member>();
    qDBusRegisterMetaType<MemberList>();
    qRegisterMetaType<MemberList>("MemberList");

    qDBusRegisterMetaType<IMOfflineMsg>();
    qDBusRegisterMetaType<IMOfflineMsgList>();
    qRegisterMetaType<IMOfflineMsgList>("IMOfflineMsgList");

    qDBusRegisterMetaType<LoginInfo>();
    qDBusRegisterMetaType<LoginInfoList>();
    qRegisterMetaType<LoginInfoList>("LoginInfoList");

    qDBusRegisterMetaType<Org>();
    qDBusRegisterMetaType<OrgList>();
    qRegisterMetaType<OrgList>("OrgList");

    qDBusRegisterMetaType<OrgUser>();
    qDBusRegisterMetaType<OrgUserList>();
    qRegisterMetaType<OrgUserList>("OrgUserList");
    qDBusRegisterMetaType<IMSysMsg>();
    qDBusRegisterMetaType<IMSysMsgList>();
    qRegisterMetaType<IMSysMsgList>("IMSysMsgList");

    qDBusRegisterMetaType<IMSysMsgRespInfo>();
    qDBusRegisterMetaType<IMSysMsgRespInfoList>();
    qRegisterMetaType<IMSysMsgRespInfoList>("IMSysMsgRespInfoList");

    qDBusRegisterMetaType<IMPrivateSetting>();
    qRegisterMetaType<IMPrivateSetting>("IMPrivateSetting");
}
#endif // LINKDOODTYPES_H


