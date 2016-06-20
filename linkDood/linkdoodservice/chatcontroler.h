#ifndef CHATCONTROLER_H
#define CHATCONTROLER_H

#include<IChatObserver.h>
#include <QObject>
#include "linkdoodtypes.h"
#include "Msg.h"

class ChatControler:public QObject,public IChatObserver
{
    Q_OBJECT
public:
    void init();//初始监听接口

    /**************************************************
    * @brief removeChat
    * @description: 移除会话
    * @param[in] targetid 传入会话对应的ID，群或者人
    ****************************************************/
    void removeChat(int64 targetid);

    /*****************************************
    * @brief setMessageRead
    * @description: 设置消息已读
    * @param[in] targetid 传入会话对应的ID，群或者人
    * @param[in] msgid 传入要删除的消息ID集合
    *****************************************/
    void setMessageRead(int64 targetid, int64 msgid);

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
    void getMessages(int64 targetid, int64 msgid, int count, int flag);

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

signals:
    //监听头像更新
    void avatarChangedBack(int64 id,QString avatar);
    //监听离线消息通知
   void offlineMsgNoticeBack(IMOfflineMsgList msgList);
    //监听新消息通知
   void messageNoticeBack(Msg& msg);
    //会话消息
   void  chatListChanged(const Chat_UIList& chats);

   //发送消息返回
   void sendMessageBack(bool code,int64 sendTime,int64 msgId);
   //void sendSrvMessageBack(bool code,int64 sendTime,int64 msgId);
   //获取消息结果返回
   void getMessagesBack(bool code,int64 sessionId,MsgList& msgList);
   //void getSrvMessagesBack(bool code,int64 sessionId,MsgList& msgList);
   //移除会话结果返回
   void removeChatBack(bool);
  // void removeSrvChatBack(bool);

private:

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

    MsgText msgtextToQmsgtext(std::shared_ptr<service::MsgText> msgtext);
    service::MsgText QmsgtextTomsgtext(MsgText Qmsgtext);
};

template<typename T>
T& imMsgCast(Msg& val){ return dynamic_cast<T&>(val); }

#endif // CHATCONTROLER_H

