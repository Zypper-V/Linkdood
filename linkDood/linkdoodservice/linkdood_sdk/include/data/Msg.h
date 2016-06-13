#pragma once
#include "SDKTypes.h"

#include <vector>
#include <string>
#include <memory>

namespace service {

	enum MSG_TYPE{
		MSG_TYPE_HTML = 1,
		MSG_TYPE_TEXT,
		MSG_TYPE_AUDIO,
		MSG_TYPE_POSITION,
		MSG_TYPE_IMG,
		MSG_TYPE_FILE,
		MSG_TYPE_CARD,
		MSG_TYPE_TIP
	};
	class Msg {
	public:
		Msg(void) :msgtype(0), msgid(0), targetid(0), fromid(0), toid(0), 
			localid(0), active_type(0), related_msgid(0),time(0){}
		virtual ~Msg(void){}
		virtual void inti(void){}
		bool operator == (const Msg & rhs)const{
			if (msgtype != rhs.msgtype)
				return false;
			if (msgid != rhs.msgid)
				return false;
			if (targetid != rhs.targetid)
				return false;
			if (fromid != rhs.fromid)
				return false;
			if (toid != rhs.toid)
				return false;
			if (localid != rhs.localid)
				return false;
			if (related_users != rhs.related_users)
				return false;
			if (limit_range != rhs.limit_range)
				return false;
			if (body != rhs.body)
				return false;
			if (active_type != rhs.active_type)
				return false;
			if (related_msgid != rhs.related_msgid)
				return false;
			if (time != rhs.time)
				return false;
			return true;
		}
	public:
		int msgtype;    //消息类型
		int active_type;//消息事件属性 1.阅后即焚 2 有问必答 3 活动
		int64 msgid;    //消息ID
		int64 targetid; //会话者ID（群或用户等）
		int64 fromid;   //发送者ID
		int64 toid;     //接收者ID
		int64 localid;  //本地ID
		int64 related_msgid; //关联消息ID
		int64 time;    //发送时间
		std::string body;//消息内容
		std::vector<int64> related_users;//秘聊时相关的用户ID
		std::vector<int64> limit_range; //@人员列表
	};

	class MsgText : public Msg {
	public:
		MsgText(void){}
		void inti(void){}
		bool operator == (const MsgText& rhs)const {
			if (msg_properties != rhs.msg_properties)
				return false;
			return true;
		}
	public:
		std::string msg_properties;
	};

	class MsgFile : public Msg {
	public:
		MsgFile(void){}
		void init(void){}
		bool operator == (const MsgFile& rhs)const{
			if (states != rhs.states)
				return false;
			if (size != rhs.size)
				return false;
			if (fileid != rhs.fileid)
				return false;
			if (file_name != rhs.file_name)
				return false;
			if (file_path != rhs.file_path)
				return false;
			if (url != rhs.url)
				return false;
			if (encrypt_key != rhs.encrypt_key)
				return false;
			if (encrypt_user != rhs.encrypt_user)
				return false;
			return true;
		}
	public:
		int states;
		int64 size;  //文件大小
		int64 fileid;//文件ID
		int64 encrypt_user;//加密者ID
		std::string file_name;//文件名
		std::string file_path;//文件本地路径
		std::string encrypt_key;//加密KEY
		std::string url;//文件URL
	};

	class MsgImg : public Msg {
	public:
		MsgImg(){}
		void init(void){}
		bool operator == (const MsgImg& rhs)const{
			if (width != rhs.width)
				return false;
			if (height != rhs.height)
				return false;
			if (file_name != rhs.file_name)
				return false;
			if (thumb_url != rhs.thumb_url)
				return false;
			if (main_url != rhs.main_url)
				return false;
			if (encrypt_key != rhs.encrypt_key)
				return false;
			if (encrypt_user != rhs.encrypt_user)
				return false;
			return true;
		}
	public:
		int width;   //图像宽度
		int height;  //图像高度
		int64 encrypt_user;  //加密者ID
		std::string thumb_url; //缩略图URL
		std::string main_url;  //大图URL
		std::string encrypt_key;//加密KEY
		std::string file_name;   //文件名
	};

	typedef std::shared_ptr<Msg> MsgPtr;

	template<typename T>
	T& msgCast(Msg& val){ return dynamic_cast<T&>(val); }

	template <typename T>
	std::shared_ptr<T> msgPointCast(MsgPtr val){ return std::dynamic_pointer_cast<T>(val); }
	
}