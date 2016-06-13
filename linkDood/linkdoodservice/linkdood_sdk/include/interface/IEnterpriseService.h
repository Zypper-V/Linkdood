#pragma once

#include "../data/SDKTypes.h"
#include "../data/ErrorInfo.hpp"
#include "../data/Org.h"
#include "../data/packet.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

namespace service{

	namespace sdk{
		class SdkChannel;
	}
	class IEnterpriseService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化IEnterpriseService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(
			std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief getSonOrgs
		* @description: 获取子组织
		* @param[in] orgid 传入组织id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getSonOrgs(
			int64 orgid, std::function<void(ErrorInfo& info, std::vector<Org> orgs,std::vector<OrgUser> orgusers)> await) = 0;

		/************************************************************************
		* @brief getOnlineStates
		* @description: 获取在线状态
		* @param[in] users 传入用户id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getOnlineStates(
			std::vector<int64> users, std::function<void(std::vector<OnlineState>& states)>await) = 0;

		/************************************************************************
		* @brief getOrgUserInfo
		* @description: 获取组织用户信息
		* @param[in] userid  传入用户id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getOrgUserInfo(
			int64 userid, std::function<void(ErrorInfo& info, OrgUser& orguser)>await) = 0;

	};

	std::shared_ptr<IEnterpriseService> getEnterpriseInstance(void);
}