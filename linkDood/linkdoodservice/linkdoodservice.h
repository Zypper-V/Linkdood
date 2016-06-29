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
    void sessionMessageNotice(QString,QString,QString,QString,QString,QString);

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

    void loginSucceeded();
    void loginFailed(QString);
    void loginoutRelust(bool loginout);

    void chatListChanged(const Chat_UIList& chats);

    void contactListChanged(int oper,ContactList contacts);

    void srvGetContactInfo(service::User&user);
    void getContactInfo();
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

    void logout();
    void getContactInfo(int64 userId);

    //唯一标识Id
    QString createMsgId();

    //用户信息
    void getContactInfo(QString userId,Msg msg);
    //获取会话列表
    void getContactList();
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

protected slots:
    //获取子组织返回
    void onGetSonOrgsResult(int code, OrgList orglist,OrgUserList orguserlist);
    void onGetOnlineStatesResult(QOnlineStateList onlinestatelist);
    void onGetorgUserInfoResult(int code,OrgUser orguser);

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
                               QString avater);
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
