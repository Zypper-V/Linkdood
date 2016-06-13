#pragma once
#include "../data/ErrorInfo.hpp"
#include "../data/Group.h"
#include"../data/packet.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>
namespace service{

	namespace sdk{
		class SdkChannel;
	}
	class IGroupService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化GroupService类
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief createGroup
		* @description: 创建群
		* @param[in] level 传入群等级
		* @param[in] name 传入群名称
		* @param[in] members   传入群成员
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void createGroup(
			int level, std::string& name, std::vector<int64>& members, std::function<void(ErrorInfo& info, int64 &res)> await) = 0;

		/************************************************************************
		* @brief addGroup
		* @description: 加群
		* @param[in] groupid 传入群id
		* @param[in] verify_info 传入验证信息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void addGroup(
			int64 groupid, std::string& verify_info, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief removeGroup
		* @description: 解散群
		* @param[in] type 传入操作类型
		* @param[in] groupid 传入群id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void removeGroup(
			int type, int64 groupid, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief transferGroup
		* @description: 转让群
		* @param[in] groupid 传入群id
		* @param[in] userid 传入新群主的id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void transferGroup(
			int64 groupid, int64 userid, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief setGroupSet
		* @description: 设置群设置
		* @param[in] groupid 传入群id
		* @param[in] verify_type 传入验证类型
		* @param[in] is_allow 传入是否允许成员邀请用户
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void setGroupSet(
			int64 groupid, int8 verify_type, int8 is_allow, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief setGroupInfo
		* @description: 设置群信息
		* @param[in] group 传入群信息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void setGroupInfo(
			Group group, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief getGroupList
		* @description: 获取群列表
		************************************************************************/
		virtual void getGroupList(void) = 0;

		/************************************************************************
		* @brief getGroupSet
		* @description: 获取群设置
		* @param[in] groupid 传入群id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getGroupSet(
			int64 groupid, std::function<void(ErrorInfo& info,int8 verify_type,int8 is_allow)> await) = 0;

		/************************************************************************
		* @brief getGroupInfo
		* @description: 获取群信息
		* @param[in] groupid 传入群id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getGroupInfo(
			int64 groupid, std::function<void(ErrorInfo& info,Group group)> await) = 0;

		/************************************************************************
		* @brief inviteMember
		* @description: 邀请群成员
		* @param[in] groupid 传入群id
		* @param[in] members 传入成员名单
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void inviteMember(
			int64 groupid,std::vector<int64> members,std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief removeMember
		* @description: 移除群成员
		* @param[in] groupid 传入群id
		* @param[in] userid 传入需要移除的成员id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void removeMember(
			int64 groupid, int64 userid, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief setMemberInfo
		* @description: 设置群成员信息
		* @param[in] member 传入成员信息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void setMemberInfo(
			User& member, std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief getMemberInfo
		* @description: 获取群成员信息
		* @param[in] groupid 传入群id
		* @param[in] userid 传入成员id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getMemberInfo(
			int64 groupid,int64 userid, std::function<void(ErrorInfo& info,User& member)> await) = 0;

		/************************************************************************
		* @brief getMemberList
		* @description: 获取群成员列表
		* @param[in] groupid 传入群id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getMemberList(
			int64 groupid, std::function<void(ErrorInfo& info, std::vector<std::shared_ptr<User> > members)> await) = 0;

		/************************************************************************
		* @brief getGroupFileList
		* @description: 获取群文件列表
		* @param[in] groupid 传入群id
		* @param[in] beginid 传入起始id
		* @param[in] count 传入数量
		* @param[in] flag 传入偏移标志0为向上1为向下
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getGroupFileList(
			int64 groupid,int64 beginid,int count,int8 flag, std::function<void(ErrorInfo& info, std::vector<FileInfo> fileInfos)> await) = 0;

		/************************************************************************
		* @brief deleteGroupFile
		* @description: 删除群文件
		* @param[in] files 传入群文件id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void deleteGroupFile(
			std::vector<int64>files, std::function<void(ErrorInfo& info)> await) = 0;

	};
	std::shared_ptr<IGroupService> getGroupInstance(void);
}