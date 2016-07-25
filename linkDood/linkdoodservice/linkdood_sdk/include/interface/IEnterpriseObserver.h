#pragma once
#include "../data/SDKTypes.h"
#include <memory>

class IEnterpriseObserver {
public:
	/************************************************************************
	* @brief onUpdateRootFinished
	* @description: 企业根节点更新完成通知
	* @param[in] flag 传入-1断线重连，0重连成功
	************************************************************************/
	virtual void onUpdateRootFinished(void) = 0;
};