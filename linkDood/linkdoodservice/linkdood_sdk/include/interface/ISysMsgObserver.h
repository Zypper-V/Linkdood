#pragma once
#include"../data/SysMsg.h"

#include <memory>
#include <vector>


class ISysMsgObserver {
public:
	/************************************************************************
	* @brief onSysMessageNotice
	* @description: 监听系统消息
	* @param[in] msg 传入消息
	* @param[in] unreadcount 传入未读数量
	************************************************************************/
	virtual void onSysMessageNotice(SysMsg& msg, int unreadcount = 0) = 0;
};