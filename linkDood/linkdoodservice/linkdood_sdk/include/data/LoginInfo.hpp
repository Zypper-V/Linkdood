#pragma once

#include "SDKTypes.h"
#include <string>
#include <vector>
namespace service {

#define KEEPPASSWD 2
#define AUTOLOGIN 4

    class LoginInfo
    {
    public:
		LoginInfo():isRemberPass(false), isAutoLogin(false), status(0), userId(0), last_login_time(0){};
		virtual ~LoginInfo(){};

		int32 status;
		int32 isRemberPass;              //是否记住密码
		int32 isAutoLogin;               //自动登录 
		int64 userId;                    //用户id
		int64 last_login_time;           //上次登陆时间
        std::string server;              //服务器
        std::string name;               //用户名
		std::string account;			//账号
        std::string user_icon;          //头像
        std::string area_num;           //国家码           
    };

}// namespace service
