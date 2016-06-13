#pragma once
#include "User.h"

namespace service {
	struct _Account__isset{
		_Account__isset(void) :birthday(false),nick_id(false),phone(false),email(false){}
		bool birthday;
		bool nick_id;
		bool phone;
		bool email;
	};

	class Account : public User {
	public:
		Account() :birthday(0){}
		~Account(){}
		void init(){}
		void __set_birthday(const int64 val){
			birthday = val;
			__isset.birthday = true;
		}
		void __set_nick_id(const std::string val){
			nick_id = val;
			__isset.nick_id = true;
		}
		void __set_phone(const std::string val){
			phone = val;
			__isset.phone = true;
		}
		void __set_email(const std::string val){
			email = val;
			__isset.email = true;
		}
		bool operator == (const Account& rhs)const{
			if (__isset.birthday != rhs.__isset.birthday)
				return false;
			else if (__isset.birthday && !(birthday == rhs.birthday))
				return false;
			if (__isset.email != rhs.__isset.email)
				return false;
			else if (__isset.email && !(email == rhs.email))
				return false;
			if (__isset.nick_id != rhs.__isset.nick_id)
				return false;
			else if (__isset.nick_id && !(nick_id == rhs.nick_id))
				return false;
			if (__isset.phone != rhs.__isset.phone)
				return false;
			else if (__isset.phone && !(phone == rhs.phone))
				return false;
			return true;
		}
	public:
		int64 birthday;                //ÉúÈÕ
		std::string nick_id;           //¶¹¶¹ºÅ
		std::string phone;             //ÊÖ»úºÅ
		std::string email;             //ÓÊÏäºÅ
		_Account__isset __isset;
	};
}
