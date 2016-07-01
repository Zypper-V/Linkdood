#ifndef CHATCONTROLER_H
#define CHATCONTROLER_H

#include<IChatObserver.h>
#include <QObject>
#include "linkdoodtypes.h"
#include "Msg.h"
#include "packet.h"

class ChatControler:public QObject,public IChatObserver
{
    Q_OBJECT
public:
    void init();//初始监听接口

     void getContactInfo(QString userId,Msg msg);

    //进入会话UI
    void entryChat(const QString targetId);
    //离开会话UI
    void exitChat(const QString targetId);
    //获取当前SessionId
    bool getCurrentSessionId(QString& targetId);

    /**************************************************
    * @brief removeChat
    * @description: 移除会话
    * @param[in] targetid 传入会话对应的ID，群或者人
    ****************************************************/
    void removeChat(QString targetid);

    /*****************************************
    * @brief setMessageRead
    * @description: 设置消息已读
    * @param[in] targetid 传入会话对应的ID，群或者人
    * @param[in] msgid 传入要删除的消息ID集合
    *****************************************/
    void setMessageRead(QString targetid, QString msgid);

    /*****************************************************
    * @brief getUnReadMessages
    * @description: 获取未读消息列表
    ******************************************************/
    void getUnReadMessages(void);

    /************************************
    * @brief sendMessage
    * @description: 发送消息
    * @param[in] msg 传入消息
    ************************************/
    void sendMessage(Msg& msg);

    /********************************************************************
    * @brief getMessages
    * @description: 获取消息
    * @param[in] targetid 传入会话对应的ID，群或者人
    * @param[in] msgid 传入查询消息的起始ID，将从该消息的下一条消息开始查询
    * @param[in] count 传入查询消息总数
    * @param[in] flag  传入上一页还是下一页 向上偏移 0；向下偏移 1
    ********************************************************************/
    void getMessages(QString targetid, QString msgid, int count, int flag);

    /*************************************************
    * @brief deleteMessage
    * @description: 删除消息
    * @param[in] targetid 传入会话对应的ID，群或者人
    * @param[in] msgs 传入要删除的消息ID集合
    ***************************************************/
    void deleteMessage(QString targetid, std::vector<QString> msgs);

    //获取会话列表
    void getChatList(void);

    ChatControler(QObject* parent=0);
    ~ChatControler();
    /*************************************************************
    * @brief onMessageNotice
    * @description: 监听新消息通知
    **************************************************************/
    void onMessageNotice(std::shared_ptr<service::Msg> msg);

    /***********************************************************
    * @brief onAvatarChanged
    * @description: 监听头像更新
    * @param[out] targetid 传入目标ID，人或者群
    * @param[out] avatar   传入路径
    *********************************************************/
    void onAvatarChanged(int64 targetid, std::string avatar);

    /**********************************************************
    * @brief onOfflineMsgChanged
    * @description: 监听离线消息通知
    * @param[out] msgs 传入离线消息集合
    ***********************************************************/
    void onOfflineMsgChanged(std::vector<OfflineMsg> msgs);

    /***************************************************
    * @brief onListChanged
    * @description: 监听会话列表更新通知
    * @param[in] flag 传入列表标志
    * 1:0x01　第一个包,　　 需要清理原来的数据
    * 2:0x02  中间的包，　　在原来的数据后面追加
    * 3:0x04  最后的包，　　最近会话发送完毕
    * @param[in] chats 传入会话集合
    ****************************************************/
    void onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats);

    /************************************************************************
    * @brief uploadAvatar
    * @description: 上传头像
    * @param[in] path 传入头像本地路径
    ************************************************************************/
    void uploadAvatar(QString path);

    /************************************************************************
    * @brief uploadFile
    * @description: 上传文件
    * @param[in] path 传入文件本地路径
    * @param[in] property 传入文件属性
    ************************************************************************/
    void uploadFile(QString path, QString property);

    /************************************************************************
    * @brief downloadFile
    * @description: 下载文件
    * @param[in] path 传入下载路径
    * @param[in] url 传入url
    * @param[in] property 传入文件属性
    ************************************************************************/
    void downloadFile(QString path, QString url, QString property);

    /************************************************************************
    * @brief uploadImage
    * @description: 上传照片
    * @param[in] thumbimg 传入缩略图
    * @param[in] srcimg 传入原图
    * @param[in] property 传入图片属性
    ************************************************************************/
    void uploadImage(QString thumbimg, QString srcimg, QString property);

    /************************************************************************
    * @brief downloadImage
    * @description: 下载图片
    * @param[in] url 传入图片url
    * @param[in] property 传入图片属性
    * @param[in] await  传入接收结果回调
    ************************************************************************/
    void downloadImage(QString url, QString property);

    /************************************************************************
    * @brief decryptFile
    * @description: 解密文件
    * @param[in] encryptkey 传入解密密码
    * @param[in] srcpath 传入原图路径
    * @param[in] destpath 传入解密后图片路径
    ************************************************************************/
    bool decryptFile(QString encryptkey, QString srcpath, QString destpath);

    /************************************************************************
    * @brief getFileList
    * @description: 获取文件列表
    * @param[in] targetid 传入查询对象id
    * @param[in] fileid 传入起始文件id
    * @param[in] count 传入数量
    * @param[in] flag 传入偏移标志0为向上1为向下
    ***********************************************************************/
    void getFileList(int64 targetid, int64 fileid, int count, int flag);


signals:
    //监听头像更新
    void avatarChangedBack(int64 id,QString avatar);
    //监听离线消息通知
   void offlineMsgNoticeBack(IMOfflineMsgList msgList);
    //监听新消息通知
   void chatMessageNotice(Msg msg);
    //会话消息
   void chatListChanged(const Chat_UIList& chats);
   //会话列表(通知栏)新消息更新通知
   void sessionMessageNotice(QString,QString,QString,QString,QString,QString,QString);
   //发送消息返回
   void sendMessageBack(bool code,int64 sendTime,int64 msgId);
   //获取消息结果返回
   void getMessagesBack(bool code,int64 sessionId,MsgList msgList);
   //移除会话结果返回
   void removeChatBack(bool);
    //删除消息
    void deleteMessagesBack(int code);

    //上传头像返回
    void uploadAvatarBack(std::string orgijson, std::string thumbjson, int code);
    //上传文件返回
    void uploadFileBack(int64 tagetid, std::string jasoninfo, int code);
    //文件进度返回
    void fileProgressBack(int32 extra_req, int32 process, std::string info);
    //下载文件返回
    void downloadFileBack(int code, std::string localpath, int64 tagetid);
    //上传图片返回
    void uploadImageBack(int64 tagetid, std::string orgijson, std::string thumbjson, int code);
    //下载图片返回
    void downloadImageBack(int code,  std::string localpath, int64 tagetid);
    //获取文件列表返回
    void getFileListBack(int code, FileInfoList fileList);


private:
    //处理时间显示
    //type 1 会话列表时间 2聊天界面时间
    QString dealTime(qint64 msgtime,int type);

    /************************************
    * @brief onRemoveChat
    * @description: 移除会话结果回调
    ************************************/
    void _removeChat(service::ErrorInfo&info);

    /************************************
    * @brief onSendMesage
    * @description: 发送消息结果回调
    ************************************/
    void _sendMesage(service::ErrorInfo&, int64/*发送时间*/,int64/*消息ID*/);
    /************************************
    * @brief onGetMesage
    * @description: 获取消息结果回调
    ************************************/
    void _getMesage(service::ErrorInfo&, int64/*会话方ID*/, std::vector<service::MsgPtr>);

    /*************************************************
    * @brief _deleteMessage
    * @description: 删除消息结果回调
    ***************************************************/
    void _deleteMessage(service::ErrorInfo& info);

    void _getContactInfo(service::ErrorInfo& info, service::User& user,Msg msg);

    //上传头像回调
    void _uploadAvatar(std::string orgijson, std::string thumbjson, int code);
    //上传文件回调
    void _uploadFile(int64 tagetid, std::string jasoninfo, int code);
    //文件进度
    void _fileProgress(int32 extra_req, int32 process, std::string info);
    //下载文件回调
    void _downloadFile(service::ErrorInfo& info, std::string localpath, int64 tagetid);
    //上传图片回调
    void _uploadImage(int64 tagetid, std::string orgijson, std::string thumbjson, int code);
    //下载图片回调
    void _downloadImage(service::ErrorInfo& info, std::string localpath, int64 tagetid);
    //获取文件列表回调
    void _getFileList(service::ErrorInfo& info, std::vector<FileInfo> files);

    Msg msgtextToQmsgtext(std::shared_ptr<service::MsgText> msgtext);
    service::MsgText QmsgtextTomsgtext(Msg Qmsgtext);

private:
    QString mSessionTargetID;
};

template<typename T>
T& imMsgCast(Msg& val){ return dynamic_cast<T&>(val); }

#endif // CHATCONTROLER_H

