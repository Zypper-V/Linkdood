#pragma once
#include "User.h"
#include <vector>
#include <string>
#include <memory>

namespace service{ class Msg; }

struct UserSetting{
	UserSetting() :isonline(0), issearchbybean(0), issearchbyphone(0), issearchbymail(0),
	isshareupdate(0), isnewmsgtip(0), ismultiservmsgtip(0), ismultiservfrdtip(0), ismultiservpersontip(0){}
	int8 isonline;				//否显示在线信息 0显示 1不显示 默认0
	int8 issearchbybean;		//豆豆号查找  0允许 1不允许 默认0
	int8 issearchbyphone;		//手机号查找  0显示 1不显示 默认0
	int8 issearchbymail;		//邮箱号查找 0显示 1不显示 默认0
	int8 isshareupdate;			//分享更新   0提示更新 1不提示更新 默认0
	int8 isnewmsgtip;			//新消息通知是否提醒0提醒 1不提醒 默认0
	int8 ismultiservmsgtip;		//多服务新消息通知是否提醒0不始终提示 1始终提示 默认0
	int8 ismultiservfrdtip;		//多服务设置V标好友始终提醒 0不始终提示 1始终提示 默认
	int8 ismultiservpersontip;	//多服务设置设置@相关人始终提醒0不始终提示 1始终提示 默认0
};

//好友验证方式返回
struct ContactVerifyType
{
	ContactVerifyType() :userid(0), type(0){}
	int64 userid;
	int8  type; //验证类型1需要验证信息:2:不允许任何人添加,3:允许任何人添加
};

struct  OnlineState
{
	OnlineState() :userID(0), connectID(0), deviceType(0), flag(0){}
	int64 userID;   //用户ID
	int64 connectID;
	int8 deviceType;  //在线设备类型
	int8 flag;        //在线状态
};

struct SearchResult {
	std::vector<service::User> users;
	std::vector<service::User> groups;
	std::vector<std::shared_ptr<service::User> > orgusers;
};

struct  MsgSearchProperty {
	MsgSearchProperty(void) :targetid(0), count(0), msgtype(0),
	start_time(0), end_time(0){}
	int msgtype; //消息类型
	int count;   //消息数量
	int64 targetid;//目标ID
	int64 start_time;//开始时间
	int64 end_time;  //结束时间
};

struct  MsgSearchResult{
	MsgSearchResult():count(0),flag(0),targetid(0){}
	int count;      //消息数量
	int8  flag;		//0x01男，0x02女, 0x08为群，0 非男非女为保密
	int64 targetid;	//目标id
	std::string name; //目标名称
	std::string avatar;//目标头像
};

struct FileInfo{
	FileInfo() :fileid(0),userid(0),targetid(0),size(0),time(0){}
	int64 fileid;                 //文件ID
	int64 userid;                 //发送者ID
	int64 targetid;               //目标ID,可以是群,也可以是用户
	int64 size;                   //文件大小
	int64 time;                   //上传时间
	std::string path;             //本地路径
	std::string name;             //文件名
	std::string url;              //文件url
	std::string encrypt_key;      //加密KEY
};

struct OfflineMsg
{
	OfflineMsg():offline_type(0),count(0){}
	int offline_type;  /*1未读消息 2设备已读消息*/
	int count;      //数量
	std::shared_ptr<service::Msg> msg;
};

struct UpdateInfo {
	UpdateInfo(void) :force(0), url(""), version(""), md5(""){}
	int force;							//	1强制升级 0建议升级
	std::string url;					//	更新包链接
	std::string version;				//	升级版本 V0.2.2
	std::string md5;					//  md5值
	std::vector<std::string> info;		//	升级信息
	std::vector<std::string> vip;		//	升级用户列表
};

struct PrivateSetting{
	PrivateSetting(void) :allow_phone(1), allow_email(1), allow_birthday(1),verifytype(0),vip_noticetype(0),
	at_noticetype(0),global_noticetype(0){}
	int allow_birthday;		//	生日可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
	int allow_phone;		//	电话可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
	int allow_email;		//	邮箱可见状态 1：所有人可见 2：仅好友可见 3：仅自己可见，默认1
	int verifytype;			//	验证方式 1：需要验证信息,2:不允许任何人添加,3:允许任何人添加，默认1
	int vip_noticetype;		//	V标消息通知类型 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1
	int at_noticetype;		//	@相关人提醒模式 1:表示始终有声音提醒，2：表示始终无声音提醒 3:不始终提醒，默认1
	int global_noticetype;	//	全局消息通知 1:通知详情，2：通知源，隐藏内容 3:完全隐藏，默认2
};

