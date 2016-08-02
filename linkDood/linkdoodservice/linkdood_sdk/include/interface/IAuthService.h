#pragma once

#include "../data/LoginInfo.hpp"
#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"

#include <functional>
#include <memory>
#include <string>

namespace service {
	namespace sdk{
		class SdkChannel;
	}
	class IAuthService {
	public:
		
		/************************************************************************
		* @brief init
		* @description: 初始化AuthService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

		//////////////////////////////////////////////////////////////////////////
		//	注册相关接口

		/************************************************************************
		* @brief getRegCode
		* @description: 获取注册验证码
		* @param[in] server 传入服务器地址，域名或IP均可
		* @param[in] account 传入注册账号 如果是手机账户格式为“0086158********”
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void getRegCode(
			const std::string& server, const std::string& account, std::function<void(ErrorInfo& info, int timeout/*超时*/)> await) = 0;

		/************************************************************************
		* @brief signup
		* @description: 注册用户
		* @param[in] regCode 传入服务器地址，域名或IP均可
		* @param[in] user    传入用户名，建议使用真实姓名
		* @param[in] pwd	 传入注册密码
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void signup(
			const std::string& regCode, const std::string user, const std::string& pwd, std::function<void(ErrorInfo& info)> await)=0;
		
		/************************************************************************
		* @brief getPasswordRule
		* @description: 获取密码复杂度
		************************************************************************/
		virtual void getPasswordRule(void)=0;

		//////////////////////////////////////////////////////////////////////////
		//	登录相关接口

		/************************************************************************
		* @brief getLoginHistory
		* @description: 获取登录历史记录
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void getLoginHistory(
			std::function<void(std::vector<LoginInfo>)> await)=0;

		/************************************************************************
		* @brief login
		* @description: 登录
		* @param[in] user 传入用户名 如果是手机账户格式为“0086158********”
		* @param[in] pwd 传入密码
		* @param[in] server 传入服务器地址，域名或IP均可
		* @param[inout] await 传入接收调用结果的回调函数
		* @return:	int64 返回当前执行的操作ID，用于取消该次执行
		************************************************************************/
		virtual int64 login(
			const std::string& user, const std::string& pwd, const std::string& server, std::function<void(ErrorInfo& err, int64 userid/*用户ID*/)> await)=0;
		
		/************************************************************************
		* @brief login
		* @description: 自动登录（不用填密码）
		* @param[in] userid 传入用户ID 
		* @param[in] server 传入服务器地址，域名或IP均可
		* @param[inout] await 传入接收调用结果的回调函数
		* @return:	int64 返回当前执行的操作ID，用于取消该次执行
		************************************************************************/
		virtual int64 login(const int64 userid, const std::string& server, std::function<void(ErrorInfo& err, int64 userid/*用户ID*/)> await) = 0;
		
		/************************************************************************
		* @brief logout
		* @description: 登出
		************************************************************************/
		virtual void logout(void)=0;

		/************************************************************************
		* @brief abortLogin
		* @description: 取消登录
		* @param[in] operateid 传入对应登录操作的ID
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void abortLogin(
			const int64 operateid, std::function<void(ErrorInfo& err)> await)=0;

		/************************************************************************
		* @brief verifyImgCode
		* @description: 验证登录验证码或者获取下一张验证码
		* @param[in] account 传入登录账号
		* @param[in] code	 传入验证码内容 code为空则获取下一张验证码
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void verifyImgCode(
			const std::string& account, const std::string& code, std::function<void(ErrorInfo& err, std::string& img/*下一张验证图片*/)> await)=0;

		/************************************************************************
		* @brief setLoginInfo
		* @description: 设置登录信息
		* @param[in] flag    传入登录属性 是否记住密码和是否自动登录的按位或
		* @param[in] userid  传入用户ID
		* @param[in] account 传入用户账号
		* @param[in] avatar	 传入用户头像
		* @param[in] name    传入用户名称
		************************************************************************/
		virtual void setLoginInfo(
			int flag, int64 userid, std::string account, std::string avatar, std::string name) = 0;

		/************************************************************************
		* @brief getSecUrl
		* @description: 获取安全中心URL
		* @param[in] server 传入企业服务器
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void getSecUrl(
			const std::string& server, std::function<void(ErrorInfo& err, std::string url)> await) = 0;

		//////////////////////////////////////////////////////////////////////////
		//	账号相关接口
		/************************************************************************
		* @brief getAccountInfo
		* @description: 获取账户信息
		************************************************************************/
		virtual void getAccountInfo(void) = 0;

		/************************************************************************
		* @brief updateAccountInfo
		* @description: 更新用户信息
		* @param[in] user 传入用户信息
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void updateAccountInfo(
			User& user, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief changePassword
		* @description: 修改密码
		* @param[in] oldPw 传入旧密码
		* @param[in] newPw 传入新密码
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void changePassword(
			const std::string& oldPw, const std::string& newPw, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief setSetting
		* @description: 设置账号设置项
		* @param[in] flag 传入设置项属性
		* @param[in] type 传入设置项类型
		* @param[inout] await 传入接收调用结果的回调函数
		*
		*  type = 1: 设置是否显示在线信息 flag: 0显示 1不显示 默认0
		*  type = 3: 设置豆豆号查找 flag: 0允许 1不允许 默认0
		*  type = 4: 设置手机号查找 flag: 0允许 1不允许 默认0
		*  type = 5: 设置邮箱号查找 flag: 0允许 1不允许 默认0
		*  type = 6: 设置分享更新   flag: 0提示更新 1不提示更新 默认0
		*  type = 7: 新消息通知是否提醒 flag: 0提醒 1不提醒 默认0
		*  type = 12: 多服务新消息通知是否提醒 flag: 0不始终提示 1始终提示 默认0
		*  type = 13: 多服务设置V标好友始终提醒 flag: 0不始终提示 1始终提示 默认0
		*  type = 14: 多服务设置设置@相关人始终提醒 flag: 0不始终提示 1始终提示 默认0
		************************************************************************/
		virtual void setSetting(
			int8 flag, int type, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief getSetting
		* @description: 获取账号设置项
		* @param[in] type 传入获取的设置项类型
		* type为1，则返回值为value_i64第一位 如果type=0,返回所有字段，每个字段所占的位于type向对应
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void getSetting(
			int type, std::function<void(ErrorInfo&, UserSetting&)> await) = 0;

		/************************************************************************
		* @brief setPrivateSetting
		* @description: 设置隐私设置
		* @param[in] PrivateSetting 传入设置的隐私设置项
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void setPrivateSetting(PrivateSetting ps, std::function<void(int code)> await) = 0;

		/************************************************************************
		* @brief getPrivateSetting
		* @description: 获取隐私设置
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void getPrivateSetting(std::function<void(int, PrivateSetting&)> await) = 0;

		/************************************************************************
		* @brief getClientKey
		* @description: 获取CLIENTKEY
		************************************************************************/
		virtual void getClientKey(void)=0;

	};

	std::shared_ptr<IAuthService> getAuthInstance(void);
}