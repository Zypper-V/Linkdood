#pragma once
#include "User.h"
#include <string>

namespace service {
	struct _Member__isset {
		_Member__isset(void) :groupid(false), team(false), member_type(false), remark(false){}
		bool groupid;
		bool team;
		bool member_type;
		bool remark;
	};

	class Member : public User {
	public:
		Member(void) :team(0),member_type(0){}
		virtual ~Member(void){}
		virtual void init(){}
		void __set_groupid(const int64 val){
			groupid = val;
			__isset.groupid = true;
		}
		void __set_team(const int val){
			team = val;
			__isset.team = true;
		}
		void __set_member_type(const int8 val){
			member_type = val;
			__isset.member_type = true;
		}
		void __set_remark(const std::string& val){
			remark = val;
			__isset.remark = true;
		}
		bool operator == (const Member& rhs)const{
			if (__isset.groupid != rhs.__isset.groupid)
				return false;
			else if (__isset.groupid && !(team == rhs.groupid))
				return false;
			if (__isset.team != rhs.__isset.team)
				return false;
			else if (__isset.team && !(team == rhs.team))
				return false;
			if (__isset.member_type != rhs.__isset.member_type)
				return false;
			else if (__isset.member_type && !(member_type == rhs.member_type))
				return false;
			if (__isset.remark != rhs.__isset.remark)
				return false;
			else if (__isset.remark && !(remark == rhs.remark))
				return false;
			return true;
		}
	public:
		int64 groupid;     //群id
		int team;          //分组
		int8 member_type;  //成员类型：1.普通 2.管理员 3.超级管理员
		std::string remark;//群备注
		_Member__isset __isset;
	};
}
