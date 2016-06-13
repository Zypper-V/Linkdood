#pragma once
#include <memory>

class IAuthObserver;
class IContactObserver;
class IGroupObserver;
class IChatObserver;
class ISysMsgObserver;

typedef IAuthObserver* AuthObserverPtr;
typedef IContactObserver* ContactObserverPtr;
typedef IGroupObserver* GroupObserverPtr;
typedef IChatObserver* ChatObserverPtr;
typedef ISysMsgObserver* SysMsgObserverPtr;

namespace service {
	namespace sdk { class SdkChannel; }
	
	class INotifyService {
	public:
		
		/************************************************************************
		* @brief init
		* @description: 初始化INotifyService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief setAuthObserver
		* @description: 设置认证类监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void setAuthObserver(AuthObserverPtr observer) = 0;

		/************************************************************************
		* @brief removeAuthObserver
		* @description: 移除认证类监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void removeAuthObserver(AuthObserverPtr observer) = 0;

		/************************************************************************
		* @brief setAuthObserver
		* @description: 设置联系人监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void setContactObserver(ContactObserverPtr observer) = 0;

		/************************************************************************
		* @brief removeContactObserver
		* @description: 移除联系人监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void removeContactObserver(ContactObserverPtr observer) = 0;

		/************************************************************************
		* @brief setGroupObserver
		* @description: 设置群监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void setGroupObserver(GroupObserverPtr observer) = 0;

		/************************************************************************
		* @brief removeGroupObserver
		* @description: 移除群监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void removeGroupObserver(GroupObserverPtr observer) = 0;

		/************************************************************************
		* @brief setChatObserver
		* @description: 设置会话监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void setChatObserver(ChatObserverPtr observer) = 0;

		/************************************************************************
		* @brief removeChatObserver
		* @description: 移除会话监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void removeChatObserver(ChatObserverPtr observer) = 0;

		/************************************************************************
		* @brief setSysMsgObserver
		* @description: 设置系统消息监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void setSysMsgObserver(SysMsgObserverPtr observer) = 0;

		/************************************************************************
		* @brief removeSysMsgObserver
		* @description: 移除系统消息监听对象
		* @param[in] observer 传入监听对象实例
		************************************************************************/
		virtual void removeSysMsgObserver(SysMsgObserverPtr observer) = 0;
	};
	std::shared_ptr<INotifyService> getNotifyInstance(void);
}