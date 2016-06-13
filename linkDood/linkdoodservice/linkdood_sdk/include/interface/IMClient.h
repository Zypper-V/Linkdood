#pragma once

#include <memory>
#include <string>

#define	IMSDK_EXPOPRTS
#ifdef   IMSDK_EXPOPRTS
#ifdef _WIN32
#define  IMSDK_API   _declspec( dllexport )
#else
#define IMSDK_API 
#endif
#else
#ifdef _WIN32
#define  IMSDK_API   _declspec( dllimport )
#else
#define IMSDK_API 
#endif
#endif

namespace service {
 	class IAuthService;
 	class INotifyService;
	class IContactService;
	class ISearchService;
	class IFileService;
	class IGroupService;
	class IChatService;
	class ISysMsgService;
	class ISysSetService;
	class IEnterpriseService;
	class IMSDK_API IMClient {
	public:
		static std::shared_ptr<IMClient> getClient(void);
		virtual bool init(const std::string& dataPath, const std::string& certPath) = 0;
		virtual void uninit(void) = 0;

 		virtual std::shared_ptr<IAuthService> getAuth(void) = 0;
 		virtual std::shared_ptr<INotifyService> getNotify(void) = 0;
		virtual std::shared_ptr<IContactService> getContact(void) = 0;
		virtual std::shared_ptr<ISearchService> getSearch(void) = 0;
		virtual std::shared_ptr<IFileService> getFile(void) = 0;
		virtual std::shared_ptr<IGroupService> getGroup(void) = 0;
		virtual std::shared_ptr<IChatService> getChat(void) = 0;
		virtual std::shared_ptr<ISysMsgService> getSysMsg(void) = 0;
		virtual std::shared_ptr<ISysSetService> getSysSet(void) = 0;
		virtual std::shared_ptr<IEnterpriseService> getEnterprise(void) = 0;
	protected:
		IMClient(void){};
		static std::shared_ptr<IMClient> m_instance;
	};
}

