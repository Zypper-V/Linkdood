#pragma once
#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"
#include "../data/SDKTypes.h"

#include <memory>
#include <vector>

namespace service {
	class Contact;
}

class IContactObserver {
public:
	/************************************************************************
	* @brief onListChanged
	* @description: 监听联系人刷新
	* @param[in] operType 传入操作类型
	* 0x01 包含此标识，清空ＵＩ列表插入下面列表项
	* 0x02　包含此标识，ＵＩ列表尾部添加下面列表项
	* 0x04 包含此标识，所有好友添加完毕
	* 0x08 包含此标识，从当前ＵＩ列表中更新下面列表项　不和其他标识组合
	* 0x10 包含此标识，从当前ＵＩ列表中删除下面列表项　不和其他标识组合
	* @param[in] users	  传入变更的联系人
	************************************************************************/
	virtual void onListChanged(int operType, std::vector<service::Contact>& users) = 0;

	/************************************************************************
	* @brief onAvatarChanged
	* @description: 监听联系人头像更新
	* @param[in] userid 传入联系人ID
	* @param[in] avatar	  传入头像
	************************************************************************/
	virtual void onAvatarChanged(int64 userid, std::string avatar) = 0;

	/************************************************************************
	* @brief onContactInfoChanged
	* @description: 监听联系人信息更新
	* @param[in] operType 传入操作类型
	* @param[in] users	  传入联系人信息
	************************************************************************/
	virtual void onContactInfoChanged(int operType, service::User& users) = 0;

	/************************************************************************
	* @brief onOnlineChanged
	* @description: 监听联系人信息更新
	* @param[in] status 传入在线状态
	************************************************************************/
	virtual void onOnlineChanged(OnlineState& status) = 0;
};