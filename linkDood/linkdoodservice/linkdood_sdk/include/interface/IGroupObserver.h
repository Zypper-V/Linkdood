#pragma once
#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"
#include"../data/User.h"
#include"../data/Group.h"

#include <memory>
#include <vector>

namespace service {
	class Group;
}

class IGroupObserver {
public:
	/************************************************************************
	* @brief onListChanged
	* @description: 监听群列表刷新
	* @param[in] operType 传入操作类型
	* 0x01 包含此标识，清空ＵＩ列表插入下面列表项
	* 0x02　包含此标识，ＵＩ列表尾部添加下面列表项
	* 0x04 包含此标识，所有好友添加完毕
	* 0x08 包含此标识，从当前ＵＩ列表中更新下面列表项　不和其他标识组合
	* 0x10 包含此标识，从当前ＵＩ列表中删除下面列表项　不和其他标识组合
	* @param[in] users	  传入变更的群
	************************************************************************/
	virtual void onListChanged(std::vector<std::shared_ptr<service::User> >  group) = 0;

	/************************************************************************
	* @brief onGroupAvatarChanged
	* @description: 监听群头像更新
	* @param[in] avatar	  传入头像
	************************************************************************/
	virtual void onGroupAvatarChanged(int64 groupid,std::string avatar) = 0;

	/************************************************************************
	* @brief onMemberAvatarChanged
	* @description: 监听成员头像更新
	* @param[in] userid 传入成员ID
	* @param[in] avatar	  传入成员头像
	************************************************************************/
	virtual void onMemberAvatarChanged(int64 userid, std::string avatar) = 0;

	/************************************************************************
	* @brief onGroupInfoChanged
	* @description: 监听群信息更新
	* @param[in] operType 传入操作类型
	* @param[in] operType 传入群信息
	************************************************************************/
	virtual void onGroupInfoChanged(int8 operType,service::Group& group) = 0;

	/************************************************************************
	* @brief onGroupLeaderChanged
	* @description: 监听群主更新
	* @param[in] userid 传入新群主id
	* @param[in] user_name 传入新群主名称
	* @param[in] group_name 传入群名
	************************************************************************/
	virtual void onGroupLeaderChanged(int64 userid, std::string user_name,int64 groupid,std::string group_name) = 0;

	/************************************************************************
	* @brief onMemberInfoChanged
	* @description: 监听群成员信息更新
	* @param[in] info 传入成员信息
	************************************************************************/
	virtual void onMemberInfoChanged(int64 groupid, service::User& info) = 0;

	/************************************************************************
	* @brief onMemberListChanged
	* @description: 监听群成员列表更新
	* @param[in] operType 传入操作类型
	* 0x01 包含此标识，清空ＵＩ列表插入下面列表项
	* 0x02　包含此标识，ＵＩ列表尾部添加下面列表项
	* 0x04 包含此标识，所有好友添加完毕
	* 0x08 包含此标识，从当前ＵＩ列表中更新下面列表项　不和其他标识组合
	* 0x10 包含此标识，从当前ＵＩ列表中删除下面列表项　不和其他标识组合
	* @param[in] members	  传入变更的群成员
	************************************************************************/
	virtual void onMemberListChanged(int operType, int64 groupid, std::vector<std::shared_ptr<service::User> > members) = 0;
};