#pragma once

#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"
#include "../data/SysMsg.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

namespace service{

	namespace sdk{
		class SdkChannel;
	}
	class ISysMsgService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化ISysMsgService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(
			std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief response
		* @description: 回应
		* @param[in] userid 传入消息回应信息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void response(
			SysMsgRespInfo info,std::function<void(ErrorInfo& info)> await) = 0;

		/************************************************************************
		* @brief setMessagRead
		* @description: 设置消息已读
		* @param[in] type 传入操作类型1 好友请求验证框已读|2 好友请求返回框已读| 3 设置验证请求消息已读|4 设置群验证响应消息已读                      
		* @param[in] msgs 传入消息id
		************************************************************************/
		virtual void setMessagRead(
			int type,std::vector<int64> msgs) = 0;

		/************************************************************************
		* @brief getMessages
		* @description: 获取消息
		* @param[in] type  传入响应消息类型 0 全部 1 加好友请求 2 加好友响应 3 加群请求 4 加群
		* @param[in] count 传入数量
		* @param[in] msgid 传入消息id
		* @param[in] flag   传入偏移标志 0 向上偏移 1 向下偏移 
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getMessages(
			int type,int count,int64 msgid,int flag, std::function<void(ErrorInfo info,std::vector<SysMsg> sysmsgs)>await) = 0;	

		/************************************************************************
		* @brief removeMessages
		* @description: 删除消息消息
		* @param[in] type  传入响应消息类型 0 全部 1 加好友请求 2 加好友响应 3 加群请求 4 加群响应
		* @param[in] msgs 传入要删除的消息id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void removeMessages(
			int type, std::vector<int64> msgs, std::function<void(ErrorInfo info)> await) = 0;
	};

	std::shared_ptr<ISysMsgService> getSysMsgInstance(void);
}