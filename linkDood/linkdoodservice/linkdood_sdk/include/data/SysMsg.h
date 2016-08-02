#pragma once
#include "SDKTypes.h"
#include<string>
struct SysMsgRespInfo
{
	SysMsgRespInfo() :targetid(0),msgid(0),msgtype(0),opertype(0){}
	int64 targetid;//目标ID
	int64 msgid;   //消息ID
	int   msgtype; //消息类型
	int   opertype;//活动类型
	std::string info;//消息回复内容
};

struct SysMsg
{
	SysMsg():msgid(0),targetid(0),time(0),msgtype(0),isresponse(0),isread(0),opertype(0),subtype(0){}
	int64 msgid;       //消息ID
	int64 targetid;    //目标ID
	int64 time;        //时间
	int64 operUserid;  //操作者ID
	int   msgtype;     //消息类型
	int   isresponse;  //是否回应
	int   isread;      //是否已读
	int   opertype;    //活动类型
	int   subtype;     //子操作类型标示,置顶等其他操作
	std::string name;  //消息来源名称
	std::string operUser; //操作者名称
	std::string avatar;//消息来源头像
	std::string info;  //消息内容
};