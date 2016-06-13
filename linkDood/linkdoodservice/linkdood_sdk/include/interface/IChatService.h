#pragma once

#include "../data/Msg.h"
#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"
#include "../data/SDKTypes.h"

#include <functional>
#include <memory>
#include <string>


namespace service {
	namespace sdk{
		class SdkChannel;
	}
	class IChatService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化ChatService类
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief getChatList
		* @description: 获取会话列表
		************************************************************************/
		virtual void getChatList(void) = 0;

		/************************************************************************
		* @brief removeChat
		* @description: 移除会话
		* @param[in] targetid 传入会话对应的ID，群或者人
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void removeChat(int64 targetid, std::function<void(ErrorInfo&)> await) = 0;

		/************************************************************************
		* @brief sendMessage
		* @description: 发送消息
		* @param[in] msg 传入消息
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void sendMessage(Msg& msg, std::function<void(ErrorInfo&, int64/*发送时间*/,int64/*消息ID*/)> await) = 0;

		/************************************************************************
		* @brief deleteMessage
		* @description: 删除消息
		* @param[in] targetid 传入会话对应的ID，群或者人
		* @param[in] msgs 传入要删除的消息ID集合
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void deleteMessage(int64 targetid, std::vector<int64> msgs, std::function<void(ErrorInfo&)> await) = 0;

		/************************************************************************
		* @brief setMessageRead
		* @description: 设置消息已读
		* @param[in] targetid 传入会话对应的ID，群或者人
		* @param[in] msgs 传入要删除的消息ID集合
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void setMessageRead(int64 targetid, int64 msgid) = 0;

		/************************************************************************
		* @brief getMessages
		* @description: 获取消息
		* @param[in] targetid 传入会话对应的ID，群或者人
		* @param[in] msgid 传入查询消息的起始ID，将从该消息的下一条消息开始查询
		* @param[in] count 传入查询消息总数
		* @param[in] flag  传入上一页还是下一页 向上偏移 0；向下偏移 1
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getMessages(int64 targetid, int64 msgid, int count, int flag, std::function<void(ErrorInfo&, int64/*会话方ID*/, std::vector<MsgPtr>)> await) = 0;

		/************************************************************************
		* @brief getUnReadMessages
		* @description: 获取未读消息列表
		************************************************************************/
		virtual void getUnReadMessages(void) = 0;

		/************************************************************************
		* @brief searchMessage
		* @description: 全局查找消息
		* @param[in] key	   传入查找关键字
		* @param[in] property  传入查找的附加属性
		* @param[in] await     传入接收结果回调
		************************************************************************/
		virtual void searchMessage(std::string key, MsgSearchProperty& property, std::function<void(ErrorInfo&, std::vector<MsgSearchResult>&)> await) = 0;
	};

	std::shared_ptr<IChatService> getChatInstance(void);
}