#pragma once
#include "User.h"

namespace service {
	struct _TinyGroup__isset {
		_TinyGroup__isset(void):level(false),pinyin(false),server(false),createrid(false){}
		bool level;
		bool pinyin;
		bool server;
		bool createrid;
	};

	class TinyGroup : public User {
	public:
		TinyGroup(void):level(0){}
		virtual ~TinyGroup(void){}
		virtual void init(){}
		void __set_level(const int val){
			level = val;
			__isset.level = true;
		}
		void __set_createrid(const int64 val){
			createrid = val;
			__isset.createrid = true;
		}
		void __set_pinyin(const std::string& val){
			pinyin = val;
			__isset.pinyin = true;
		}
		void __set_server(const std::string& val){
			server = val;
			__isset.server = true;
		}
		bool operator == (const TinyGroup& rhs)const{
			if (__isset.level != rhs.__isset.level)
				return false;
			else if (__isset.level && !(level == rhs.level))
				return false;
			if (__isset.pinyin != rhs.__isset.pinyin)
				return false;
			else if (__isset.pinyin && !(pinyin == rhs.pinyin))
				return false;
			if (__isset.server != rhs.__isset.server)
				return false;
			else if (__isset.server && !(server == rhs.server))
				return false;
			if (__isset.createrid != rhs.__isset.createrid)
				return false;
			else if (__isset.createrid && !(createrid == rhs.createrid))
				return false;
			return true;
		}
	public:
		int level;  //群等级（1,2,3,4)1是临时群，2是普通群
		int64 createrid;//创建者ID
		std::string pinyin;//名称拼音
		std::string server;//服务器
		_TinyGroup__isset __isset;
	};
}
