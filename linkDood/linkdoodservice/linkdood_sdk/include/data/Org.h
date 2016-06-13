#pragma once
#include "User.h"
#include <string>

namespace service {
	struct _Org__isset {
		_Org__isset(void) :level(false), sonorg_count(false), leaf(false), ishidden(false), sonuser_count(false), parent_id(false), ent_id(false), order_num(false), branch_id(false), org_code(false){}
		bool level;
		bool sonorg_count;
		bool leaf;
		bool ishidden;
		bool sonuser_count;
		bool parent_id;
		bool ent_id;
		bool order_num;
		bool branch_id;
		bool org_code;
	};
	struct _OrgUser__isset {
		_OrgUser__isset(void) :ent_id(false), org_id(false), role_id(false), duty(false), email(false), phone(false), order_num(false), neworg_id(false), orgname(false), extend(false), pinyin(false){}
		bool ent_id;
		bool org_id;
		bool role_id;
		bool duty;
		bool email;
		bool phone;
		bool order_num;
		bool neworg_id;
		bool orgname;
		bool extend;
		bool pinyin;
	};
	class Org : public User {
	public:
		Org(void) :level(0), sonorg_count(0), leaf(0), ishidden(0), sonuser_count(0), parent_id(0), ent_id(0), order_num(0), branch_id(0){}
		virtual ~Org(void){}
		virtual void init(){}
		void __set_level(const int val){
			level = val;
			__isset.level = true;
		}
		void __set_sonorg_count(const int64 val){
			sonorg_count = val;
			__isset.sonorg_count = true;
		}
		void __set_leaf(const int val){
			leaf = val;
			__isset.leaf = true;
		}
		void __set_ishidden(const int val){
			ishidden = val;
			__isset.ishidden = true;
		}
		void __set_sonuser_count(const int64 val){
			sonuser_count = val;
			__isset.sonuser_count = true;
		}
		void __set_parent_id(const int64 val){
			parent_id = val;
			__isset.parent_id = true;
		}
		void __set_ent_id(const int64 val){
			ent_id = val;
			__isset.ent_id = true;
		}
		void __set_order_num(const int64 val){
			order_num = val;
			__isset.order_num = true;
		}
		void __set_branch_id(const int64 val){
			branch_id = val;
			__isset.branch_id = true;
		}
		void __set_org_code(const std::string& val){
			org_code = val;
			__isset.org_code = true;
		}
		bool operator == (const Org& rhs)const{
			if (__isset.level != rhs.__isset.level)
				return false;
			else if (__isset.level && !(level == rhs.level))
				return false;
			if (__isset.sonorg_count != rhs.__isset.sonorg_count)
				return false;
			else if (__isset.sonorg_count && !(sonorg_count == rhs.sonorg_count))
				return false;
			if (__isset.leaf != rhs.__isset.leaf)
				return false;
			else if (__isset.leaf && !(leaf == rhs.leaf))
				return false;
			if (__isset.ishidden != rhs.__isset.ishidden)
				return false;
			else if (__isset.ishidden && !(ishidden == rhs.ishidden))
				return false;
			if (__isset.sonuser_count != rhs.__isset.sonuser_count)
				return false;
			else if (__isset.sonuser_count && !(sonuser_count == rhs.sonuser_count))
				return false;
			if (__isset.parent_id != rhs.__isset.parent_id)
				return false;
			else if (__isset.parent_id && !(parent_id == rhs.parent_id))
				return false;
			if (__isset.ent_id != rhs.__isset.ent_id)
				return false;
			else if (__isset.ent_id && !(ent_id == rhs.ent_id))
				return false;
			if (__isset.order_num != rhs.__isset.order_num)
				return false;
			else if (__isset.order_num && !(order_num == rhs.order_num))
				return false;
			if (__isset.branch_id != rhs.__isset.branch_id)
				return false;
			else if (__isset.branch_id && !(branch_id == rhs.branch_id))
				return false;
			if (__isset.org_code != rhs.__isset.org_code)
				return false;
			else if (__isset.org_code && !(org_code == rhs.org_code))
				return false;
			return true;
		}
	public:
		int level;
		int64 sonorg_count;
		int leaf;
		int ishidden;
		int64 sonuser_count;
		int64 parent_id;
		int64 ent_id;
		int64 order_num;
		int64 branch_id;
		std::string org_code;
		_Org__isset __isset;
	};
	class OrgUser : public User {
	public:
		OrgUser(void) :ent_id(0), org_id(0), role_id(0), order_num(0), neworg_id(0){}
		virtual ~OrgUser(void){}
		virtual void init(){}
		void __set_ent_id(const int64 val){
			ent_id = val;
			__isset.ent_id = true;
		}
		void __set_org_id(const int64 val){
			org_id = val;
			__isset.org_id = true;
		}
		void __set_role_id(const int64 val){
			role_id = val;
			__isset.role_id = true;
		}
		void __set_neworg_id(const int64 val){
			neworg_id = val;
			__isset.neworg_id = true;
		}
		void __set_order_num(const int64 val){
			order_num = val;
			__isset.order_num = true;
		}
		void __set_duty(const std::string& val){
			duty = val;
			__isset.duty = true;
		}
		void __set_email(const std::string& val){
			email = val;
			__isset.email = true;
		}
		void __set_phone(const std::string& val){
			phone = val;
			__isset.phone = true;
		}
		void __set_orgname(const std::string& val){
			orgname = val;
			__isset.orgname = true;
		}
		void __set_extend(const std::string& val){
			extend = val;
			__isset.extend = true;
		}
		void __set_pinyin(const std::string& val){
			pinyin = val;
			__isset.pinyin = true;
		}
		bool operator == (const OrgUser& rhs)const{
			if (__isset.ent_id != rhs.__isset.ent_id)
				return false;
			else if (__isset.ent_id && !(ent_id == rhs.ent_id))
				return false;
			if (__isset.org_id != rhs.__isset.org_id)
				return false;
			else if (__isset.org_id && !(org_id == rhs.org_id))
				return false;
			if (__isset.role_id != rhs.__isset.role_id)
				return false;
			else if (__isset.role_id && !(role_id == rhs.role_id))
				return false;
			if (__isset.duty != rhs.__isset.duty)
				return false;
			else if (__isset.duty && !(duty == rhs.duty))
				return false;
			if (__isset.email != rhs.__isset.email)
				return false;
			else if (__isset.email && !(email == rhs.email))
				return false;
			if (__isset.phone != rhs.__isset.phone)
				return false;
			else if (__isset.phone && !(phone == rhs.phone))
				return false;
			if (__isset.order_num != rhs.__isset.order_num)
				return false;
			else if (__isset.order_num && !(order_num == rhs.order_num))
				return false;
			if (__isset.neworg_id != rhs.__isset.neworg_id)
				return false;
			else if (__isset.neworg_id && !(neworg_id == rhs.neworg_id))
				return false;
			if (__isset.orgname != rhs.__isset.orgname)
				return false;
			else if (__isset.orgname && !(orgname == rhs.orgname))
				return false;
			if (__isset.extend != rhs.__isset.extend)
				return false;
			else if (__isset.extend && !(extend == rhs.extend))
				return false;
			if (__isset.pinyin != rhs.__isset.pinyin)
				return false;
			else if (__isset.pinyin && !(extend == rhs.pinyin))
				return false;
			return true;
		}
	public:
		int64 order_num;
		int64 ent_id;
		int64 org_id;
		int64 role_id;
		int64 neworg_id;
		std::string duty;
		std::string email;
		std::string phone;
		std::string orgname;
		std::string extend;
		std::string pinyin;
		_OrgUser__isset __isset;
	};
}