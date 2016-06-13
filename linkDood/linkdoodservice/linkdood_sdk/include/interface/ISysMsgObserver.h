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
	************************************************************************/
	virtual void onSysMessageNotice(SysMsg& msg) = 0;
};