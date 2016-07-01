#ifndef LINKDOODSERVICE_H
#define LINKDOODSERVICE_H

#include <QObject>
#include "authcontroler.h"
#include "enterprisecontroler.h"
#include "linkdoodtypes.h"
#include "MsgUtils.h"
#include "Msg.h"
#include "Org.h"

class CSystemPackageManager;
class ChatControler;
class ContactControler;

class LinkDoodService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.vrv.linkDood")

public:
    void static createService();

    static LinkDoodService* instance();

signals:

    //会话列表头像更新
    void chatAvatarChanged(int64 id,QString avatar);
    //监听离线消息通知
    void offlineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void chatMessageNotice(Msg msg);
    //发送消息返回
    void sendMessageResult(bool code,QString sendTime,QString msgId);
    //获取消息结果返回
    void getMessagesResult(bool code,QString sessionId,MsgList msgList);
    //移除会话结果返回
    void removeChatResult(bool);

    //删除消息
    void deleteMessagesResult(int code);
    //会话列表(通知栏)新消息更新通知
    void sessionMessageNotice(QString,QString,QString,QString,QString,QString,QString);

    //获取子组织返回
    void getSonOrgsResult(int code,OrgList orglist,OrgUserList orguserlist);
    void getOnlineStatesResult(QOnlineStateList onlinestatelist);
    void getOrgUserInfoResult(int code,OrgUser& orguser);

    //获取登录历史记录
    void getLoginHistoryResult(LoginInfoList list);

    //登录成功自动推送
    void loginResultObserver(int code,QString userID);

    //推送用户信息
    void accountInfoChanged(Contact user);

    //联系人信息更新
    void contactInfoChanged(int oper,Contact user);
    //联系人状态改变
    void contactOnlineChanged(QString id, QString deviceType);

    void loginSucceeded();
    void loginFailed(QString);
    void loginoutRelust(bool loginout);
    void changePasswordResult(QString);

    void chatListChanged(const Chat_UIList& chats);

    void contactListChanged(int oper,ContactList contacts);

    void srvGetContactInfo(service::User&user);
    void getContactInfo();


    //上传头像返回
    void uploadAvatarResult(QString orgijson, QString thumbjson, int code);
    //上传文件返回
    void uploadFileResult(QString tagetid, QString jasoninfo, int code);
    //文件进度返回
    void fileProgressResult(int32 extra_req, int32 process, QString info);
    //下载文件返回
    void downloadFileResult(int code, QString localpath, QString tagetid);
    //上传图片返回
    void uploadImageResult(QString tagetid, QString orgijson, QString thumbjson, int code);
    //下载图片返回
    void downloadImageResult(int code, QString jasoninfo, QString tagetid);
    //获取文件列表返回
    void getFileListResult(int code, FileInfoList fileList);


public slots:

    /**************************************
    * @brief getAppLoginStatus
    * @description: 从配置文件读取登录状态
    * @return  status 1:己经登录 0:未登录
    ***************************************/
    int getAppLoginStatus();

    /**************************************
    * @brief setAppLoginStatus
    * @description: 向配置文件写入登录状态
    * @param[out]  status 1:己经登录 0:未登录
    ***************************************/
    void setAppLoginStatus(const int status);

    QString installPath();

    QString dataPath();

    // 功能		:	登录
    // 返回		:	NULL
    // 返回值    :	void
    // 参数		:
    // 		1.  server	服务器地址
    // 		2.  userId	登录ID
    // 		3.  password	登录密码
    void login(const QString &server,
               const QString &userId,
               const QString &password);
    void changepassword(QString oldpsw,QString newpsw);

    void logout();
    void getContactInfo(int64 userId);

    //唯一标识Id
    QString createMsgId();

    //更新联系人信息
     void updateContactInfo(QString userId,QString operStar,QString remark="");

    //用户信息
    void getContactInfo(QString userId,Msg msg);
    //获取会话列表
    void getContactList();
    //改变联系人状态
    void onOnlineChanged(QString id, QString deviceType);
    //用户信息UserId
    QString UserId();
    QString userName();
    /*****************start chat**************************/
    //获取会话列表
    void getChatList(void);
    //获取未读消息列表
    void getUnReadMessages(void);

    //进入会话UI
    void entryChat(const QString targetId);
    //离开会话UI
    void exitChat(const QString targetId);
    //获取账户信息
    void getAccountInfo(void);
    //更新用户信息
    void updateAccountInfo(Contact user);

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

    /************************************
    * @brief sendMessage
    * @description: 发送消息
    * @param[in] msg 传入消息
    ************************************/
    void sendMessage(Msg msg);

    /********************************************************************
    * @brief getMessages
    * @description: 获取消息
    * @param[in] targetid 传入会话对应的ID，群或者人
    * @param[in] msgid 传入查询消息的起始ID，将从该消息的下一条消息开始查询
    * @param[in] count 传入查询消息总数
    * @param[in] flag  传入上一页还是下一页 向上偏移 0；向下偏移 1
    ********************************************************************/
    void getMessages(const QString &targetid, const QString & msgid, const int& count, const int& flag);

    /*************************************************
    * @brief deleteMessage
    * @description: 删除消息
    * @param[in] targetid 传入会话对应的ID，群或者人
    * @param[in] msgs 传入要删除的消息ID集合
    ***************************************************/
    void deleteMessage(QString targetid, QStringList msgs);

    /*****************end chat****************************/

     /*****************start Enterprise**************************/
    void getSonOrgs(QString orgid);
    void getOnlineStates(QStringList& userid);
    void getOrgUserInfo(QString userid);
    /*****************end Enterprise**************************/

    /***************************************
    * @brief getLoginHistory
    * @description: 获取登录历史记录
    ******************************************/
    void getLoginHistory(void);

    /******************************************
    * @brief setLoginInfo
    * @description: 设置登录信息
    * @param[in] flag 传入登录属性 记住密码 flag=2;自动登录 flag=6
    * @param[in] userid 传入用户ID
    * @param[in] username 传入用户名
    * @param[in] avatar	  传入用户头像
    *************************************************/
    void setLoginInfo(int flag, QString userid, QString username, QString avatar);

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


protected slots:
    //获取子组织返回
    void onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser orguser);


    void onChangePasswordResult(QString result);

    //联系人信息更新
    void onContactInfoChanged(int oper,Contact user);

    //联系人列表更新
    void onContactListChanged(int oper,ContactList contacts);
    //会话列表更新
    void onChatListChanged(Chat_UIList chats);
    //登录成功返回
    void onLoginSucceeded();
    //登录失败返回
    void onLoginFailed(int code);
    //退出登录结果返回
    void onLoginoutRelust(bool loginout);
    //获取联系人资料返回
    void onGetContactInfoResult(service::User&user);

    //会话列表头像更新
    void onChatAvatarChanged(int64 id,QString avatar);
    //监听离线消息通知
    void onChatOfflineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void onChatMessageNotice(Msg msg);
    //发送消息返回
    void onChatSendMessageResult(bool code,int64 sendTime,int64 msgId);
    //获取消息结果返回
    void onChatGetMessagesResult(bool code,int64 sessionId,MsgList msgList);
    //移除会话结果返回
    void onChatRemoveChatResult(bool);
    //删除消息
    void onChatDeleteMessagesResult(int code);


    //上传头像返回
    void onChatUploadAvatar(QString orgijson, QString thumbjson, int code);
    //上传文件返回
    void onChatUploadFile(int64 tagetid, QString jasoninfo, int code);
    //文件进度
    void onChatFileProgress(int32 extra_req, int32 process, QString info);
    //下载文件返回
    void onChatDownloadFile(service::ErrorInfo& info, QString localpath, int64 tagetid);
    //上传图片返回
    void onChatupLoadImage(int64 tagetid, QString orgijson, QString thumbjson, int code);
    //下载图片返回
    void onChatDownloadImage(service::ErrorInfo& info, QString localpath, int64 tagetid);
    //获取文件列表返回
    void onChatGetFileList(service::ErrorInfo& info, std::vector<FileInfo> files);



    //获取登录历史记录
    void onGetLoginHistoryResult(LoginInfoList list);
    //登录成功自动推送
    void onLoginResultObserver(int code,QString userID);
    //推送用户信息
    void onAccountInfoChanged(Contact user);
    //会话列表(通知栏)新消息更新通知
    void onSessionMessageNotice(QString targetId,
                               QString msgId,
                               QString lastMsg,
                               QString time,
                               QString name,
                               QString avater,
                               QString unreadmsg);
public:
    static LinkDoodService* m_pInstance;

private:
    LinkDoodService(QObject *parent = 0);

    ~LinkDoodService();

    // 初始化SDK
    void initSdk();
    void initObserver();//初始监听接口
    void initConnects();
    // 初始化Dbus连接
    void initDBusConnection();

    void onSrvGetContactInfoResult(service::ErrorInfo& info,service::User&user);
    void _getContactInfo(service::ErrorInfo& info, service::User& user,Msg msg);
private:
    CSystemPackageManager *m_pPackageManager;
    QString m_sInstallPath;

    std::shared_ptr<AuthControler>  m_pAuth;
    std::shared_ptr<ChatControler>  m_pChatObserver;
    std::shared_ptr<ContactControler>  m_pContactObserver;
    std::shared_ptr<EnterpriseControler> m_pEnterpriseControler;

    std::shared_ptr<service::IMClient> m_pIMClient;
};

#endif // LINKDOODSERVICE_H
