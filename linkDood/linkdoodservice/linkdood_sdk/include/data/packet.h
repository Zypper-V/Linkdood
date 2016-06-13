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


