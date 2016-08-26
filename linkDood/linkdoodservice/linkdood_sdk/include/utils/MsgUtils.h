#pragma once

#include "../data/SDKTypes.h"
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
	class IMSDK_API MsgUtils {
	public:
		struct FileProperty {
			std::string fileName;
			std::string docid;
			std::string mediaUrl;
			int64 fileSize;
			int64 encryptUser;
			std::string enc_dec_key;
		};
		struct ImageProperty{
			std::string fileName;
			std::string docid;
			int height;
			int width;
			std::string thumbUrl;
			std::string mediaUrl;
			int64 encryptUser;
			std::string enc_dec_key;
		};
		struct TipProperty{
			int tipType;
			int operType;
			std::string time;
			std::string operUser;
			std::string userInfo;
			std::string tipMsg;
		};
		static std::string MsgFormat(std::string body);
		static std::string MsgFormat(ImageProperty imageporperty);
		static std::string MsgFormat(FileProperty fileproperty);
		static std::string PropertyFormat(int device_type);
		static std::string getText(std::string json);
		static FileProperty  getFile(std::string json);
		static ImageProperty getImg(std::string json);
		static TipProperty getTip(std::string json);
	};
}