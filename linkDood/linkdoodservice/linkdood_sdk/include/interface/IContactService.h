#pragma once

#include "../data/SDKTypes.h"
#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

namespace service{

	namespace sdk{
		class SdkChannel;
	}
	class IContactService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化AuthService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(
			std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief addContact
		* @description: 添加联系人
		* @param[in] userid 传入联系人ID
		* @param[in] remark 传入联系人备注，可以为空
		* @param[in] info   传入验证信息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void addContact(
			const int64 userid, const std::string& remark, const std::string& info, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief getVerifyType
		* @description: 获取联系人验证方式
		* @param[in] userid 传入联系人ID
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getVerifyType(
			const int64 userid, std::function<void(ErrorInfo&, ContactVerifyType&)> await) = 0;

		/************************************************************************
		* @brief removeContact
		* @description: 删除联系人
		* @param[in] userid 传入联系人ID
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void removeContact(
			const int64 userid, std::function<void(ErrorInfo&)> await) = 0;

		/************************************************************************
		* @brief updateContactInfo
		* @description: 更新联系人信息（星标&V标&备注）
		* @param[in] info 传入联系人信息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void updateContactInfo(
			User& info, std::function<void(ErrorInfo&)> await) = 0;

		/************************************************************************
		* @brief getContactList
		* @description: 获取联系人列表
		************************************************************************/
		virtual void getContactList(void) = 0;

		/************************************************************************
		* @brief getContactOnline
		* @description: 获取联系人在线状态
		* @param[in] users 传入联系人集合 如果为空则查所有联系人状态
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getContactOnline(
			std::vector<int64> users, std::function<void(std::vector<OnlineState>& status)> await) = 0;

		/************************************************************************
		* @brief getContactInfo
		* @description: 获取联系人信息
		* @param[in] users 传入联系人集合 如果为空则查所有联系人状态
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getContactInfo(
			const int64 userid, std::function<void(ErrorInfo&, User&)> await) = 0;

		/************************************************************************
		* @brief getContactExtendInfo
		* @description: 获取联系人扩展信息
		* @param[in] userid 传入联系人id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getContactExtendInfo(
			const int64 userid, std::function<void(ErrorInfo&, User&)> await) = 0;
	};

	std::shared_ptr<IContactService> getContactInstance(void);
}