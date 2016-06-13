#pragma once

#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"

#include "../data/SDKTypes.h"
#include <memory>

class IChatObserver {
public:
	/************************************************************************
	* @brief onMessageNotice
	* @description: 监听新消息通知
	* @param[in] flag 传入-1断线重连，0重连成功
	************************************************************************/
	virtual void onMessageNotice(std::shared_ptr<service::Msg> msg) = 0;

	/************************************************************************
	* @brief onAvatarChanged
	* @description: 监听头像更新
	* @param[in] targetid 传入目标ID，人或者群
	* @param[in] avatar   传入路径
	************************************************************************/
	virtual void onAvatarChanged(int64 targetid, std::string avatar) = 0;

	/************************************************************************
	* @brief onOfflineMsgChanged
	* @description: 监听离线消息通知
	* @param[in] msgs 传入离线消息集合
	************************************************************************/
	virtual void onOfflineMsgChanged(std::vector<OfflineMsg> msgs) = 0;

	/************************************************************************
	* @brief onListChanged
	* @description: 监听会话列表更新通知
	* @param[in] flag 传入列表标志
	* 1:0x01　第一个包,　　 需要清理原来的数据
	* 2:0x02  中间的包，　　在原来的数据后面追加
	* 3:0x04  最后的包，　　最近会话发送完毕
	* @param[in] chats 传入会话集合
	************************************************************************/
	virtual void onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats) = 0;
};