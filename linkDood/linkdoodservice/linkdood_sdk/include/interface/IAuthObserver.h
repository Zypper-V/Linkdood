#pragma once
#include "../data/ErrorInfo.hpp"
#include "../data/SDKTypes.h"
#include <memory>

namespace service {
	class User;
}
class IAuthObserver {
public:
	/************************************************************************
	* @brief onConnectChanged
	* @description: 监听网络连接状态
	* @param[in] flag 传入-1断线重连，0重连成功
	************************************************************************/
	virtual void onConnectChanged(int flag) = 0;

	/************************************************************************
	* @brief onLoginResultObserver
	* @description: 监听重新登录结果
	* @param[in] info 传入登录结果 
	* @param[in] userid 传入登录者用户ID
	************************************************************************/
	virtual void onLoginResultObserver(service::ErrorInfo& info, int64 userid) = 0;

	/************************************************************************
	* @brief onDBUpdateFinished
	* @description: 监听数据库升级完成推送
	* @param[in] val 传入1完成
	************************************************************************/
	virtual void onDBUpdateFinished(int val) = 0;

	/************************************************************************
	* @brief onLogoutChanged
	* @description: 监听登出结果
	* @param[in] info 传入结果
	************************************************************************/
	virtual void onLogoutChanged(service::ErrorInfo& info) = 0;

	/************************************************************************
	* @brief onAccountInfoChanged
	* @description: 监听用户信息修改
	* @param[in] info 传入结果
	************************************************************************/
	virtual void onAccountInfoChanged(service::User& info) = 0;

	/************************************************************************
	* @brief onClientKeyChanged
	* @description: 监听客户端KEY
	* @param[in] clientKey 传入Key
	************************************************************************/
	virtual void onClientKeyChanged(service::ErrorInfo& info, std::string& clientKey) = 0;

	/************************************************************************
	* @brief onPasswordRuleChanged
	* @description: 监听密码复杂度
	* @param[in] rule 传入密码规则
	************************************************************************/
	virtual void onPasswordRuleChanged(service::ErrorInfo& info, int16 rule) = 0;

	/************************************************************************
	* @brief onAvatarChanged
	* @description: 监听头像更新
	* @param[in] avatar 传入下载好的头像文件名
	************************************************************************/
	virtual void onAvatarChanged(std::string avatar) = 0;

};