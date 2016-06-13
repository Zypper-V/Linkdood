#pragma once

#include "../data/packet.h"
#include "../data/ErrorInfo.hpp"

#include <functional>
#include <memory>
#include <string>

namespace service {
	namespace sdk{
		class SdkChannel;
	}

	class ISearchService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化ISearchService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief searchFromNet
		* @description: 从网络进行查找
		* @param[in] key 传入关键字
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void searchFromNet(
			const std::string& key, std::function<void(ErrorInfo& info,SearchResult& res)> await) = 0;

		/************************************************************************
		* @brief searchFromLocal
		* @description: 从本地数据库进行查找
		* @param[in] key 传入关键字
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void searchFromLocal(
			const std::string& key, std::function<void(ErrorInfo& info, SearchResult& res)> await) = 0;

		/************************************************************************
		* @brief getUserInfo
		* @description: 从本地数据库进行查找
		* @param[in] userid 传入用户ID
		* @param[inout] await 传入接收调用结果的回调函数
		************************************************************************/
		virtual void getUserInfo(
			const int64 userid, std::function<void(ErrorInfo& info, User& user)> await) = 0;

	};

	std::shared_ptr<ISearchService> getSearchInstance(void);
}