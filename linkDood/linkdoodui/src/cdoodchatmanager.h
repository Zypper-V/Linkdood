#ifndef CDOODCHATMANAGER_H
#define CDOODCHATMANAGER_H

#include <QObject>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodChatManager : public CDoodListModel
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit CDoodChatManager(LinkDoodClient *client = 0, QObject *parent = 0);

    ~CDoodChatManager();

    //发送消息
    Q_INVOKABLE void sendText(QString fromId,QString text);
    Q_INVOKABLE void sendMessage(Msg& msg);
    //获取消息
    Q_INVOKABLE void getMessages(int64 targetid, int64 msgid, int count, int flag);

    //移除会话
    Q_INVOKABLE void removeChat(int64 targetid);
    //设置消息已读
    Q_INVOKABLE void setMessageRead(int64 targetid, int64 msgid);
    //获取未读消息列表
    void getUnReadMessages(void);
    //删除消息
    void deleteMessage(int64 targetid, QStringList msgs);

    QString id()const;
    QString name()const;

    Q_INVOKABLE void   setId(const QString&id);
    Q_INVOKABLE void   setName(const QString&name);
signals:
    //会话列表头像更新
    void chatAvatarChanged(int64 id,QString avatar);
    //监听离线消息通知
    void offlineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void newMessageNotice(Msg& msg);
    //发送消息返回
    void sendMessageResult(bool code,int64 sendTime,int64 msgId);
    //获取消息结果返回
    void getMessagesResult(bool code,int64 sessionId,MsgList& msgList);
    //移除会话结果返回
    void removeChatResult(bool);

    void idChanged();
    void nameChanged();
private slots:
    //会话列表头像更新
    void onChatAvatarChanged(int64 id,QString avatar);
    //监听离线消息通知
    void onChatOfflineMsgNotice(IMOfflineMsgList msgList);
    //监听新消息通知
    void onChatMessageNotice(Msg& msg);
    //发送消息返回
    void onChatSendMessageResult(bool code,int64 sendTime,int64 msgId);
    //获取消息结果返回
    void onChatGetMessagesResult(bool code,int64 sessionId,MsgList& msgList);
    //移除会话结果返回
    void onChatRemoveChatResult(bool code);
    //移除消息结果返回
    void onChatDeleteMessagesResult(int code);
private:
    LinkDoodClient *m_pClient;
    void initConnect();

    QString mId;
    QString mName;
};

#endif // CDOODCHATMANAGER_H
