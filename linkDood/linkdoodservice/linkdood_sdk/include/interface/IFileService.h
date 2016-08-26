#pragma once

#include "../data/SDKTypes.h"
#include "../data/ErrorInfo.hpp"
#include "../data/packet.h"

#include <memory>
#include <functional>
#include <string>
#include <vector>

namespace service{

	typedef enum FileOperType
	{
		FILE_UPLOAD = 1,
		FILE_DOWNLOAD
	};

	namespace sdk{
		class SdkChannel;
	}
	class IFileService {
	public:
		/************************************************************************
		* @brief init
		* @description: 初始化FileService
		* @param[in] channel 传入SdkChannel类实例，用于调用SDK接口
		* @return:	bool 成功:true, 失败:false
		************************************************************************/
		virtual bool init(
			std::shared_ptr<sdk::SdkChannel> channel) = 0;

		/************************************************************************
		* @brief uploadAvatar
		* @description: 上传头像
		* @param[in] path 传入头像本地路径
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void uploadAvatar(
			std::string path, std::function<void(std::string orgijson, std::string thumbjson, int code)> await) = 0;

		/************************************************************************
		* @brief uploadFile
		* @description: 上传文件
		* @param[in] path 传入文件本地路径
		* @param[in] property 传入文件属性
		* @param[in] await  传入接收结果回调
		* @return int64 返回用户操作文件传输的操作id
		************************************************************************/
		virtual int64 uploadFile(
			std::string path, std::string property, std::function<void(int64 tagetid, int64 operid, std::string jasoninfo, int code)> await, std::function<void(int32 extra_req, int32 process, std::string info)> pro) = 0;

		/************************************************************************
		* @brief downloadFile
		* @description: 下载文件
		* @param[in] path 传入下载路径
		* @param[in] url 传入url
		* @param[in] property 传入文件属性
		* @param[in] await  传入接收结果回调
		* @return int64 返回用户操作文件传输的操作id
		************************************************************************/
		virtual int64 downloadFile(
			std::string path, std::string url, std::string property, std::function<void(ErrorInfo& info, std::string localpath, int64 tagetid)> await, std::function<void(int32 extra_req, int32 process, std::string info)> pro) = 0;

		/************************************************************************
		* @brief uploadImage
		* @description: 上传照片
		* @param[in] thumbimg 传入缩略图
		* @param[in] srcimg 传入原图
		* @param[in] property 传入图片属性
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void uploadImage(
			std::string thumbimg, std::string srcimg, std::string property, std::function<void(int64 tagetid, std::string orgijson, std::string thumbjson, int code)> await, std::function<void(int32 extra_req, int32 process, std::string info)> pro = nullptr) = 0;

		/************************************************************************
		* @brief downloadImage
		* @description: 下载图片
		* @param[in] url 传入图片url
		* @param[in] property 传入图片属性
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void downloadImage(
			std::string url, std::string property, std::function<void(ErrorInfo& info, std::string imgname, int64 targetid)> await, std::function<void(int32 extra_req, int32 process, std::string info)> pro = nullptr) = 0;


		/************************************************************************
		* @brief decryptFile
		* @description: 解密文件
		* @param[in] encryptkey 传入解密密码
		* @param[in] srcpath 传入原图路径
		* @param[in] destpath 传入解密后图片路径
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual bool decryptFile(
			std::string encryptkey,std::string srcpath,std::string destpath) = 0;

		/************************************************************************
		* @brief getFileList
		* @description: 获取文件列表
		* @param[in] targetid 传入查询对象id
		* @param[in] fileid 传入起始文件id
		* @param[in] count 传入数量
		* @param[in] flag 传入偏移标志0为向上1为向下
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void getFileList(
			int64 targetid, int64 fileid, int count, int flag, std::function<void(ErrorInfo& info, std::vector<FileInfo> files)> await) = 0;

		/************************************************************************
		* @brief cancel
		* @description: 取消文件传输
		* @param[in] opertype 传入操作类型 
		* @param[in] id 传入文件id
		* @param[in] await  传入接收结果回调
		************************************************************************/
		virtual void cancel(FileOperType opertype, int64 id, std::function<void(int)> await) = 0;
	};

	std::shared_ptr<IFileService> getFileInstance(void);
}