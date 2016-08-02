#ifndef LINKDOODSERVICE_H
#define LINKDOODSERVICE_H

#include <QObject>
#include "authcontroler.h"
#include "enterprisecontroler.h"
#include "groupcontroler.h"
#include "linkdoodtypes.h"
#include "MsgUtils.h"
#include "Msg.h"
#include "Org.h"

class CSystemPackageManager;
class ChatControler;
class ContactControler;
class SysMsgControler;

class LinkDoodService : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.vrv.linkDood")

public:
    void static createService();

    static LinkDoodService* instance();

signals:
    void getContactInfoResult(Contact contact);
    //系统消息推送
    void sysMessageNotice(IMSysMsg sysMsg);
    void getSysMessageResult(int code, IMSysMsgList sysMsgList);
    void anthAvatarChanged(QString avatar);
    //servie重启信号
    void serviceRestart();

    //会话列表头像更新
    void chatAvatarChanged(QString id,QString avatar);
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
    //更新联系人信息
    void updateContactInfoResult(int code);
    //联系人信息更新
    void contactInfoChanged(int oper,Contact user);
    //联系人状态改变
    void contactOnlineChanged(QString id, QString deviceType);
    void elsewhereLogin(QString);
    void loginSucceeded();
    void loginFailed(QString);
    void loginoutRelust(bool loginout);
    void changePasswordResult(QString);
    void getVerifyImgResult(QString,QString);
    void connectChanged(QString);

    void chatListChanged(const Chat_UIList& chats);

    void contactListChanged(int oper,ContactList contacts);

    void srvGetContactInfo(service::User&user);

    void transMessageFinishBack(int code,QString targetId);
    //上传头像返回
    void uploadAvatarResult(QString orgijson, QString thumbjson, int code);
    //上传文件返回
    void uploadFileResult(QString tagetid, QString jasoninfo, int code);
    //文件进度返回
    void fileProgressResult(int extra_req, int process, QString info,QString localId,QString targetId);
    //下载文件返回
    void downloadFileResult(int code, QString localpath, QString tagetid);
    //上传图片返回
    void uploadImageResult(QString tagetid, QString orgijson, QString thumbjson, int code);
    //下载图片返回
    void downloadImageResult(int code, QString jasoninfo, QString tagetid);
    void downloadHistoryImageResult(int code, QString localpath, QString targetid, QString localid);
    //获取文件列表返回
    void getFileListResult(int code, FileInfoList fileList);
    //获取联系人返回
    void getUserInfoResult(int code, Contact contact);
    //从网络查找联系人返回
    void searchFromNetResult(int code, ContactList user, ContactList group);
    //从本地查找联系人返回
    void searchFromLocalResult(int code, ContactList user, ContactList group);
    //添加联系人返回
    void addContactResult(int code);
    //删除联系人返回
    void removeContactResult(int code);
    //获取验证方式
    void getVerifyTypeResult(int code, QString userid, int type);

    void uploadFileBackUrl(QString targetId,QString localId,QString fileUrl,QString enkey);
    void uploadImgeBackUrl(QString targetId,QString localId,QString mainUrl,QString thumbUrl,QString enkey);

    void groupListChanged(GroupList groupList);
    void groupAvatarChanged(QString groupid,QString avatar);
    void memberAvatarChanged(QString userid,QString avatar);
    void groupInfoChanged(QString operType,Group group);
    void groupLeaderChanged(QString userid,QString user_name,QString groupid,QString group_name);
    void memberInfoChanged(QString groupid,Member member);
    void memberListChanged(QString operType,QString groupid,MemberList members);
    void createGroupResult(QString result);
    void addGroupResult(QString result);
    void removeGroupResult(QString result);
    void transferGroupResult(QString result);
    void setGroupSetResult(QString result);
    void setGroupInfoResult(QString result);
    void getGroupSetResult(QString result,QString verify_type,QString is_allow);
    void getGroupInfoResult(QString result,Group group);
    void inviteMemberResult(QString result);
    void removeMemberResult(QString result);
    void setMemberInfoResult(QString result);
    void getMemberInfoResult(QString result,Member member);
    void getMemberListResult(QString result,MemberList memberList);
    void getGroupFileListResult(FileInfoList fileInfoList);
    void deleteGroupFileResult(QString result);
    void getGroupMemberListReslut(int code,QString id,MemberList list);
    void uploadGroupAvatarResult(QString thum_url,QString src_url);

    void setPrivateSettingResult(int code);
    void getPrivateSettingResult(int code, IMPrivateSetting ps);

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
    QString userType(QString userId);
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
    void autoLogin(QString id,QString service);
    void getVerifyImg( QString userid,QString code);
    void changepassword(QString oldpsw,QString newpsw);

    void logout();
    void getContactInfo(QString userId);

    //唯一标识Id
    QString createMsgId();

    //更新联系人信息
    void updateContactInfo(QString userId,QString operStar,QString remark="");

    //用户信息
    void getContactInfo(QString userId,Msg msg);
    //获取会话列表
    void getContactList();
    //更新联系人信息
    void onUpdateContactInfo(int code);
    //改变联系人状态
    void onOnlineChanged(QString id, QString deviceType,int flag);
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
    void  uploadAndSendFileMsg(Msg msg);

    /***************************
    * @brief downloadFile
    * @description: 下载文件
    * @param[in] path 传入下载路径
    * @param[in] url 传入url
    **************************/
    void downloadFile(QString path, QString url, QString json,QString localId,QString targetId);

    /********************************************
    * @brief uploadImage
    * @description: 上传照片
    ********************************************/
    void uploadAndSendImageMsg(Msg msg);

    /************************************************************************
    * @brief downloadImage
    * @description: 下载图片
    * @param[in] url 传入图片url
    * @param[in] property 传入图片属性
    * @param[in] await  传入接收结果回调
    ************************************************************************/
    void downloadImage(QString url, QString property);

    void downloadHistoryImage(QString url, QString property, QString targetid, QString localid);

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

    //获取联系人信息
    void getUserInfo(QString userid);
    /************************************************************************
    * @brief searchFromNet
    * @description: 从网络进行查找
    * @param[in] key 传入关键字
    ************************************************************************/
    void searchFromNet(QString key);
    /************************************************************************
    * @brief searchFromNet
    * @description: 从本地进行查找
    * @param[in] key 传入关键字
    ************************************************************************/
    void searchFromLocal(QString key);
    /**
     * @brief addContact  添加联系人
     * @param userid      传入联系人ID
     * @param remark      传入联系人备注，可以为空
     * @param info        传入验证信息
     */
    void addContact(QString userid, QString remark, QString info);
    /**
     * @brief removeContact 删除联系人
     * @param userid       传入联系人ID
     */
    void removeContact(QString userid);
    void getVerifyType(QString userid);

    void createGroup(QString level, QString name, MemberList memberList);
    void addGroup(QString groupid, QString verify_info);
    void removeGroup(QString type, QString groupid);
    void transferGroup(QString groupid, QString userid);
    void setGroupSet(QString groupid, QString verify_type, QString is_allow);
    void setGroupInfo(Group group);
    void getGroupSet(QString groupid);
    void getGroupInfo(QString groupid);
    void inviteMember(QString groupid,MemberList memberList);
    void removeMember(QString groupid, QString userid);
    void setMemberInfo(Member member);
    void getMemberInfo(QString groupid,QString userid);
    void getMemberList(QString groupid);
    void getGroupList();
    void getGroupFileList(QString groupid);
    void deleteGroupFile(QStringList fileIdList);
    void uploadGroupAvatar(QString path);

    void getSysMessages(int type,int count,QString msgid,int flag);
    void setSysMessagRead(int type, QString msg);
    void response(IMSysMsgRespInfo info);

    void setPrivateSetting(IMPrivateSetting ps);
    void getPrivateSetting();

protected slots:

    //系统消息推送
    void onSysMessageNotice(IMSysMsg sysMsg);
    void onGetSysMessages(int code, IMSysMsgList sysMsgList);

    //获取联系人资料返回
    void onGetContactInfoResult(Contact contact);

    //获取子组织返回
    void onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser orguser);

    void onAnthAvatarChanged(QString avatar);
    void onChangePasswordResult(QString result);
    void onGetVerifyImgResult(QString code,QString img);
    void onConnectChanged(QString flag);

    //联系人信息更新
    void onContactInfoChanged(int oper,Contact user);

    //联系人列表更新
    void onContactListChanged(int oper,ContactList contacts);
    //会话列表更新
    void onChatListChanged(Chat_UIList chats);
    //登录成功返回
    void onLoginSucceeded(QString userid);
    //登录失败返回
    void onLoginFailed(int code);
    //退出登录结果返回
    void onLoginoutRelust(bool loginout);

    //会话列表头像更新
    void onChatAvatarChanged(QString id,QString avatar);
    //监听离线消息通知
    void onChatOfflineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void onChatMessageNotice(Msg msg);
    //发送消息返回
    void onChatSendMessageResult(bool code,int64 sendTime,QString msgId);
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
    void onChatFileProgress(int extra_req, int process, QString info,QString localId,QString targetId);

    //下载文件返回
    void onChatDownloadFile(int code, QString localpath, QString tagetid);
    //上传图片返回
    void onChatupLoadImage(int64 tagetid, QString orgijson, QString thumbjson, int code);
    //下载图片返回
    void onChatDownloadImage(service::ErrorInfo& info, QString localpath, int64 tagetid);
    void onDownloadHistoryImage(int code, QString localpath, QString targetid, QString localid);
    //获取文件列表返回
    void onChatGetFileList(service::ErrorInfo& info, std::vector<FileInfo> files);
    //获取联系人信息返回
    void onGetUserInfoResult(int code, Contact contact);

    //从网络获取联系人返回
    void onSearchFromNet(int code, ContactList user, ContactList group);
    //从本地获取联系人返回
    void onSearchFromLocal(int code, ContactList user, ContactList group);
    //添加联系人返回
    void onAddContact(int code);
    //删除联系人返回
    void onRemoveContact(int code);
    void onGetVerifyType(int code, QString userid, int type);


    void onUploadFileBackUrl(QString targetId,QString localId,QString fileUrl,QString enkey);
    void onUploadImgeBackUrl(QString targetId,QString localId,QString mainUrl,QString thumbUrl,QString enkey);
    void onTransMessageFinishBack(int code,QString targetId);
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



    void onGroupListChanged(GroupList groupList);
    void onGroupAvatarChanged(QString groupid,QString avatar);
    void onMemberAvatarChanged(QString userid,QString avatar);
    void onGroupInfoChanged(QString operType,Group group);
    void onGroupLeaderChanged(QString userid,QString user_name,QString groupid,QString group_name);
    void onMemberInfoChanged(QString groupid,Member member);
    void onMemberListChanged(QString operType,QString groupid,MemberList memberList);
    void onCreateGroupResult(QString result);
    void onAddGroupResult(QString result);
    void onRemoveGroupResult(QString result);
    void onTransferGroupResult(QString result);
    void onSetGroupSetResult(QString result);
    void onSetGroupInfoResult(QString result);
    void onGetGroupSetResult(QString result,QString verify_type,QString is_allow);
    void onGetGroupInfoResult(QString result,Group group);
    void onInviteMemberResult(QString result);
    void onRemoveMemberResult(QString result);
    void onSetMemberInfoResult(QString result);
    void onGetMemberInfoResult(QString result,Member member);
    void onGetGroupMemberListReslut(int code,QString id,MemberList list);
    void onGetMemberListResult(QString result,MemberList memberList);
    void onGetGroupFileListResult(FileInfoList fileInfoList);
    void onDeleteGroupFileResult(QString result);
    void onUploadGroupAvatarResult(QString thum_url,QString src_url);

    void onSetPrivateSetting(int code);
    void onGetPrivateSetting(int code, IMPrivateSetting ps);


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
    QString m_userid;

    std::shared_ptr<AuthControler>  m_pAuth;
    std::shared_ptr<SysMsgControler>  m_pSysMsg;
    std::shared_ptr<ChatControler>  m_pChatObserver;
    std::shared_ptr<ContactControler>  m_pContactObserver;
    std::shared_ptr<EnterpriseControler> m_pEnterpriseControler;
    std::shared_ptr<GroupControler> m_pGroupControler;
    std::shared_ptr<service::IMClient> m_pIMClient;
};

#endif // LINKDOODSERVICE_H
