#include<chatcontroler.h>
#include<iostream>
#include<QDebug>
#include<QDateTime>

#include "IMClient.h"
#include "IChatService.h"
#include "INotifyService.h"
#include "linkdoodtypes.h"
#include "Chat.h"
#include "User.h"
#include "MsgUtils.h"
#include "Msg.h"
#include "packet.h"

void ChatControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setChatObserver(this);
}

void ChatControler::removeChat(int64 targetid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->removeChat(targetid,
                 std::bind(&ChatControler::onRemoveChat,this,
                           std::placeholders::_1));
}

void ChatControler::setMessageRead(int64 targetid, int64 msgid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->setMessageRead(targetid,msgid);
}

void ChatControler::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->getUnReadMessages();
}

void ChatControler::sendMessage(const Msg &imMsg)
{
    qDebug() << Q_FUNC_INFO;
    service::Msg msg;
    //TODO
    service::IMClient::getClient()->getChat()->sendMessage(msg,
                 std::bind(&ChatControler::onSendMesage,this,
                           std::placeholders::_1,
                           std::placeholders::_2,
                           std::placeholders::_3));
}

void ChatControler::getMessages(int64 targetid, int64 msgid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->getMessages(targetid,msgid,count,flag,
                       std::bind(&ChatControler::onGetMesage,this,
                                 std::placeholders::_1,
                                 std::placeholders::_2,
                                 std::placeholders::_3));

}

ChatControler::ChatControler(QObject* parent):
    QObject(parent)
{

}

ChatControler::~ChatControler()
{

}

void ChatControler::onMessageNotice(std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO;

    Msg imMsg;
    //TODO
    emit messageNoticeBack(imMsg);
}

void ChatControler::onAvatarChanged(int64 targetid, std::string avatar)
{
    qDebug() << Q_FUNC_INFO;
    QString tmp = QString::fromStdString(avatar);
    emit avatarChangedBack(targetid,tmp);
}

void ChatControler::onOfflineMsgChanged(std::vector<OfflineMsg> msgs)
{
    qDebug() << Q_FUNC_INFO;
    IMOfflineMsgList msgList;

    for(auto msg:msgs){
        IMOfflineMsg imMsg;
        imMsg.offlineType = msg.offline_type;
        imMsg.count = msg.count;
        if(msg.msg->msgtype == MSG_TYPE_TEXT){
           //TODO
           msgList.insert(msgList.size(),imMsg);
        }
    }
    emit offlineMsgNoticeBack(msgList);
}

void ChatControler::onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats)
{
    qDebug() << Q_FUNC_INFO;
     qDebug() <<Q_FUNC_INFO<< "chats szie:" << chats.size();
    //if(flag == 0x04)
    {
         Chat_UIList  chatList;

        for(auto i: chats){
            std::shared_ptr<service::Chat> ch = std::dynamic_pointer_cast<service::Chat>(i);
            Chat_UI chatData;
            chatData.name = QString::fromStdString(ch->name);
            chatData.last_msg =  QString::fromStdString(utils::MsgUtils::getText(ch->last_msg));
            chatData.avatar =  QString::fromStdString(ch->avatar);
            chatData.msg_time = QDateTime::fromMSecsSinceEpoch(ch->msg_time).toString("yyyy-MM-dd hh:mm:ss");
            chatData.id = QString::number(ch->id);
            chatData.chat_type = ch->chat_type;
            chatData.thumb_avatar = QString::fromStdString(ch->thumb_avatar);
            chatList.push_back(chatData);
           // qDebug() << Q_FUNC_INFO << "avatar" << chatData.avatar;
           // qDebug() << Q_FUNC_INFO << "thumb_avatar" << ch->thumb_avatar.c_str();
        }
        emit chatListChanged(chatList);
    }
}

void ChatControler::onSendMessageBack(bool code, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO;
    emit sendMessageBack(code,sendTime,msgId);
}

void ChatControler::onGetMessagesBack(bool code, int64 sessionId, MsgList& msgList)
{
    qDebug() << Q_FUNC_INFO;
    emit getMessagesBack(code,sessionId,msgList);
}

void ChatControler::onRemoveChatBack(bool code)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatBack(code);
}

void ChatControler::onRemoveChat(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO;
    emit removeSrvChatBack(info.code() == 0);

}

void ChatControler::onSendMesage(service::ErrorInfo &info, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO;
    if(!info.code()){
        emit sendSrvMessageBack(true,sendTime,msgId);
    }else{
        emit sendSrvMessageBack(false,sendTime,msgId);
    }
}

void ChatControler::onGetMesage(service::ErrorInfo &info, int64 targetId, std::vector<service::MsgPtr>msgPtr)
{
    qDebug() << Q_FUNC_INFO;
    MsgList msgList;
    //std::shared_ptr<service::Msg> msg;

    for(auto msg:msgPtr){
        if(msg->msgtype == MSG_TYPE_TEXT){
            std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg);
            MsgText item;

            item.activeType = QString::number(msgText->active_type);
            item.body = QString::fromStdString(msgText->body);
            item.fromid = QString::number(msgText->fromid);
            item.localid = QString::number(msgText->localid);
            item.msgid = QString::number(msgText->msgid);
            item.msgProperties = QString::fromStdString(msgText->msg_properties);
            item.msgtype = QString::number(msgText->msgtype);
            item.relatedMsgid = QString::number(msgText->related_msgid);
            item.targetid = QString::number(msgText->targetid);

            item.time = QString::number(msgText->time);
            item.toid = QString::number(msgText->toid);

            msgList.insert(msgList.size(),item);
        }
    }
    if(!info.code()){
        emit getSrvMessagesBack(true,targetId,msgList);
    }else{
        emit getSrvMessagesBack(true,targetId,msgList);
    }
}
