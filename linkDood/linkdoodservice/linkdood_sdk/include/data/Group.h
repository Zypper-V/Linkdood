#pragma once
#include "TinyGroup.h"

namespace service {
	struct _Group__isset {
		_Group__isset(void) :brief(false), bulletin(false), extend(false), creater_id(false), create_time(false), related_groupid(false), related_entid(false), member_nums(false), info(false){}
		bool brief;
		bool bulletin;
		bool extend;
		bool creater_id;
		bool create_time;
		bool related_groupid;
		bool related_entid;
		bool member_nums;
		bool info;
	};

	class Group {
	public:
		Group(void) :creater_id(0), create_time(0), related_groupid(0), related_entid(0), member_nums(0){}
		virtual ~Group(void){}
		virtual void init(){}
		void __set_brief(const std::string& val){
			brief = val;
			__isset.brief = true;
		}
		void __set_bulletin(const std::string& val){
			bulletin = val;
			__isset.bulletin = true;
		}
		void __set_extend(const std::string& val){
			extend = val;
			__isset.extend = true;
		}
		void __set_creater_id(const int64 val){
			creater_id = val;
			__isset.creater_id = true;
		}
		void __set_create_time(const int64 val){
			create_time = val;
			__isset.create_time = true;
		}
		void __set_related_groupid(const int64 val){
			related_groupid = val;
			__isset.related_groupid = true;
		}
		void __set_related_entid(const int64 val){
			related_entid = val;
			__isset.related_entid = true;
		}
		void __set_member_nums(const int val){
			member_nums = val;
			__isset.member_nums = true;
		}
		void __set_info(const TinyGroup val){
			info = val;
			__isset.info = true;
		}
		bool operator == (const Group& rhs)const{
			if (__isset.brief != rhs.__isset.brief)
				return false;
			else if (__isset.brief  && !(brief == rhs.brief))
				return false;
			if (__isset.bulletin != rhs.__isset.bulletin)
				return false;
			else if (__isset.bulletin && !(bulletin == rhs.bulletin))
				return false;
			if (__isset.extend != rhs.__isset.extend)
				return false;
			else if (__isset.extend && !(extend == rhs.extend))
				return false;
			if (__isset.creater_id != rhs.__isset.creater_id)
				return false;
			else if (__isset.creater_id && !(creater_id == rhs.creater_id))
				return false;
			if (__isset.create_time != rhs.__isset.create_time)
				return false;
			else if (__isset.create_time && !(create_time == rhs.create_time))
				return false;
			if (__isset.related_groupid != rhs.__isset.related_groupid)
				return false;
			else if (__isset.related_groupid && !(related_groupid == rhs.related_groupid))
				return false;
			if (__isset.related_entid != rhs.__isset.related_entid)
				return false;
			else if (__isset.related_entid && !(related_entid == rhs.related_entid))
				return false;
			if (__isset.member_nums != rhs.__isset.member_nums)
				return false;
			else if (__isset.member_nums && !(member_nums == rhs.member_nums))
				return false;
			if (__isset.info != rhs.__isset.info)
				return false;
			else if (__isset.info && !(info == rhs.info))
				return false;
			return true;
		}
	public:
		std::string brief;    //群简介
		std::string bulletin; //群公告
		std::string extend;   //群扩展字段
		int64 creater_id;      //创建者ID
		int64 create_time;     //创建时间
		int64 related_groupid; //关联群ID
		int64 related_entid;   //关联企业ID，存在此ID则属于企业群
		int member_nums;       //群成员数量
		TinyGroup info;        //群信息
		_Group__isset __isset;
	};
}
