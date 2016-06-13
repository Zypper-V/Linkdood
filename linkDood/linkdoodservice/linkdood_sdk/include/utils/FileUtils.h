#pragma once
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

namespace utils {
	class IMSDK_API FileUtils {
	public:
		struct Property{
			Property() :targetid(0){}
			long long targetid;
			std::string encryptkey;
		};
		static std::string getImgUrl(std::string json, std::string& srcimg);
		static std::string getFile(std::string json, std::string keyword);
		static std::string setProperty(Property p);
		static Property getProperty(std::string json);
	};
}