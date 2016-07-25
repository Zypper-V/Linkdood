#pragma once
#include "../data/packet.h"
#include <memory>
#include <functional>
#include <string>
namespace service {
	namespace sdk { class SdkChannel; }

	class IUpdateService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化IUpdateService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief checkUpdate
		* @description: 检测更新
		* @param[in] cur_ver 传入当前版本信息
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void checkUpdate(const std::string& cur_ver, std::function<void(UpdateInfo& info, int code)> await)=0;

		/************************************************************************
		* @brief dataRecovery
		* @description: 新老数据恢复
		* @param[in] dbpath 传入数据库路径
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void dataRecovery(const std::string& dbpath, std::function<void(int code)> await) = 0;
	};

	std::shared_ptr<IUpdateService> getUpdateInstance(void);
}