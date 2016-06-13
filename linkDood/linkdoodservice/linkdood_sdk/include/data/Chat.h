#pragma once

#include "User.h"

//聊天类型
enum ChatType{
	BUDDY_CHAT = 1,       //好友聊天
	GROUP_CHAT = 2,       //群组聊天
	SYSTEM_MSG = 3,       //系统消息
	STRANGER_CHAT = 4,    //陌生人聊天
	ENT_USER_CHAT = 5,    //企业成员聊天
	PHONE_CHAT            //我的设备
};

namespace service {
	class Chat : public User {
	public:
		Chat(void) :msg_type(0),chat_type(0),oper_type(0),sub_type(0),unread_count(0),last_msgid(0),msg_time(0){}
		virtual ~Chat(void){}
		void init(void){}
		bool operator == (const Chat& rhs)const {
			if (msg_type != rhs.msg_type)
				return false;
			if (chat_type != rhs.chat_type)
				return false;
			if (oper_type != rhs.oper_type)
				return false;
			if (sub_type != rhs.sub_type)
				return false;
			if (unread_count != rhs.unread_count)
				return false;
			if (last_msgid != rhs.last_msgid)
				return false;
			if (msg_time != rhs.msg_time)
				return false;
			if (last_msg != rhs.last_msg)
				return false;
			return true;
		}
	public:
		int msg_type;		 //	消息类型;1：HTML, 2:TEXT, 3：AUDIO, 4：POSITION, 5：IMG, 6：FILE, 7：CARD,  8：TIP
		int chat_type;	     //  聊天类型
		int oper_type;       //  活动类型
		int sub_type;        //  子操作类型标示,置顶等其他操作
		int unread_count;    //未读消息数量
		int64 last_msgid;    //最后一条消息ID
		int64 msg_time;      //消息时间
		std::string last_msg;//最后一条消息
	};
}