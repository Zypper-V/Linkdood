#pragma  once
#include "Contact.h"
namespace service {
	struct _EntExtendInfo__isset {
		_EntExtendInfo__isset(void) :sex(false), orgname(false), phonenum(false), porgname(false),
		postcode(false), address(false), fax(false), duty(false), enmail(false), enmobile(false),
		enname(false){}
		bool sex;			/*性别*/
		bool orgname;		/*组织名*/
		bool phonenum;		/*手机号*/
		bool porgname;		/*父组织结点名称*/
		bool postcode;		/*邮政编码*/
		bool address;		/*地址*/
		bool fax;			/*传真*/
		bool duty;			/*职位*/
		bool enmail;		/*电子邮件*/
		bool enmobile;		/*手机号*/
		bool enname;		/*在企业组织中的名称*/
	};
	class EntExtendInfo : public Contact{
	public:
		EntExtendInfo():sex(0){}
		~EntExtendInfo(){}
		void init(){}
		void _set_sex(const int32 val){
			sex = val;
			__isset.sex = true;
		}
		void _set_orgname(const std::string val){
			orgname = val;
			__isset.orgname = true;
		}
		void _set_phonenum(const std::string val){
			phonenum = val;
			__isset.phonenum = true;
		}
		void _set_porgname(const std::string val){
			porgname = val;
			__isset.porgname = true;
		}
		void _set_postcode(const std::string val){
			postcode = val;
			__isset.postcode = true;
		}
		void _set_address(const std::string val){
			address = val;
			__isset.address = true;
		}
		void _set_fax(const std::string val){
			fax = val;
			__isset.fax = true;
		}
		void _set_duty(const std::string val){
			duty = val;
			__isset.duty = true;
		}
		void _set_enmail(const std::string val){
			enmail = val;
			__isset.enmail = true;
		}
		void _set_enmobile(const std::string val){
			enmobile = val;
			__isset.enmobile = true;
		}
		void _set_enname(const std::string val){
			enname = val;
			__isset.enname = true;
		}
	public:
		int32		sex;			/*性别*/
		std::string orgname;		/*组织名*/
		std::string phonenum;		/*手机号*/
		std::string porgname;		/*父组织结点名称*/
		std::string postcode;		/*邮政编码*/
		std::string address;		/*地址*/
		std::string fax;			/*传真*/
		std::string duty;			/*职位*/
		std::string enmail;			/*电子邮件*/
		std::string enmobile;		/*手机号*/
		std::string enname;			/*在企业组织中的名称*/
		_EntExtendInfo__isset __isset;
	};
}