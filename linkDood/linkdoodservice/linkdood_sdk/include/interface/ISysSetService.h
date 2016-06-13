#pragma once
#include "../data/SDKTypes.h"
#include "../data/ErrorInfo.hpp"

#include <memory>
#include <functional>
#include <string>
#include <vector>

namespace service{

	namespace sdk{
		class SdkChannel;
	}
	class ISysSetService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化ISysSetService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(
			std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief setSysSet
		* @description: 设置系统设置
		* @param[in] type 传入操作类型
		* @param[in] info  传入接收结果回调
		************************************************************************/
		virtual void setSysSet(
			int type,std::string info, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief getSysSet
		* @description: 获取系统设置
		* @param[in] info  传入接收结果回调
		************************************************************************/
		virtual void getSysSet(
			std::function<void(ErrorInfo& info,std::string setinfo)> await) = 0;
	};

	std::shared_ptr<ISysSetService> getSysSetInstance(void);
}