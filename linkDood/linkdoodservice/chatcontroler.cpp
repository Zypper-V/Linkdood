#include<chatcontroler.h>
#include<iostream>
#include<QDebug>
#include<QDateTime>
#include<sstream>
#include<string>

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
                 std::bind(&ChatControler::_removeChat,this,
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

void ChatControler::sendMessage(Msg &imMsg)
{
    qDebug() << Q_FUNC_INFO << "msg:" << imMsg.body;
    if(imMsg.msgtype.toInt() == MSG_TYPE_TEXT)
    {
        MsgText& msgText = imMsgCast<MsgText>(imMsg);
        service::Msg msg = QmsgtextTomsgtext(msgText);

        service::IMClient::getClient()->getChat()->sendMessage(msg,
                     std::bind(&ChatControler::_sendMesage,this,
                               std::placeholders::_1,
                               std::placeholders::_2,
                               std::placeholders::_3));
    }
}

void ChatControler::getMessages(int64 targetid, int64 msgid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->getMessages(targetid,msgid,count,flag,
                       std::bind(&ChatControler::_getMesage,this,
                                 std::placeholders::_1,
                                 std::placeholders::_2,
                                 std::placeholders::_3));

}

void ChatControler::deleteMessage(int64 targetid, std::vector<int64> msgs)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->deleteMessage(targetid,msgs,
                             std::bind(&ChatControler::_deleteMessage,this,
                                       std::placeholders::_1));
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
    qDebug() << Q_FUNC_INFO ;
    if(msg->msgtype == MSG_TYPE_TEXT)
    {
       std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg);
       Msg imMsg = msgtextToQmsgtext(msgText);
        qDebug() << Q_FUNC_INFO << "messageNotice:"<< imMsg.body;
       emit messageNoticeBack(imMsg);
    }

}

void ChatControler::onAvatarChanged(int64 targetid, std::string avatar)
{
    qDebug() << Q_FUNC_INFO;
    QString tmp = QString::fromStdString(avatar);
    emit avatarChangedBack(targetid,tmp);
}

void ChatControler::onOfflineMsgChanged(std::vector<OfflineMsg> msgs)
{
    qDebug() << Q_FUNC_INFO <<"offlineMsg:" << msgs.size();
    IMOfflineMsgList msgList;

    for(auto msg:msgs){
        IMOfflineMsg imMsg;
        imMsg.offlineType = msg.offline_type;
        imMsg.count = msg.count;
        if(msg.msg->msgtype == MSG_TYPE_TEXT){
           std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg.msg);
           imMsg.msg = msgtextToQmsgtext(msgText);
           msgList.insert(msgList.size(),imMsg);
            qDebug() << Q_FUNC_INFO << "onOfflineMsgChanged:"<< imMsg.msg.body;
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

void ChatControler::_removeChat(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatBack(info.code() == 0);

}

void ChatControler::_sendMesage(service::ErrorInfo &info, int64 sendTime, int64 msgId)
{
    qDebug() << Q_FUNC_INFO;
    if(!info.code()){
        emit sendMessageBack(true,sendTime,msgId);
    }else{
        emit sendMessageBack(false,sendTime,msgId);
    }
}

void ChatControler::_getMesage(service::ErrorInfo &info, int64 targetId, std::vector<service::MsgPtr>msgPtr)
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
        emit getMessagesBack(true,targetId,msgList);
    }else{
        emit getMessagesBack(true,targetId,msgList);
    }
}

void ChatControler::_deleteMessage(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO;
    emit deleteMessagesBack(info.code());
}

MsgText ChatControler::msgtextToQmsgtext(std::shared_ptr<service::MsgText> msgtext)
{
    MsgText Qmsgtext;
    Qmsgtext.activeType   =QString::number(msgtext->active_type);
    Qmsgtext.msgtype      =QString::number(msgtext->msgtype);
    Qmsgtext.msgid        =QString::number(msgtext->msgid);
    Qmsgtext.targetid     =QString::number(msgtext->targetid);
    Qmsgtext.fromid       =QString::number(msgtext->fromid);
    Qmsgtext.toid         =QString::number(msgtext->toid);
    Qmsgtext.localid      =QString::number(msgtext->localid);
    Qmsgtext.time         =QDateTime::fromMSecsSinceEpoch(msgtext->time).toString("yyyy-MM-dd hh:mm:ss");
    Qmsgtext.msgProperties=QString::fromStdString(msgtext->msg_properties);
    Qmsgtext.body         =QString::fromStdString(utils::MsgUtils::getText(msgtext->body));
    return Qmsgtext;
}

service::MsgText ChatControler::QmsgtextTomsgtext(MsgText Qmsgtext)
{
    service::MsgText msgtext;
    std::stringstream str(Qmsgtext.activeType.toStdString());
    str >> msgtext.active_type;
    std::stringstream str1(Qmsgtext.msgtype.toStdString());
    str1 >> msgtext.msgtype;
    std::stringstream str2(Qmsgtext.msgid.toStdString());
    str2 >> msgtext.msgid;
    std::stringstream str3(Qmsgtext.targetid.toStdString());
    str3 >> msgtext.targetid;
    std::stringstream str4(Qmsgtext.fromid.toStdString());
    str4 >> msgtext.fromid;
    std::stringstream str5(Qmsgtext.toid.toStdString());
    str5 >> msgtext.toid;
    std::stringstream str6(Qmsgtext.localid.toStdString());
    str6 >> msgtext.localid;
    std::stringstream str7(Qmsgtext.time.toStdString());
    str7 >> msgtext.time;
    msgtext.msg_properties =Qmsgtext.msgProperties.toStdString();
    msgtext.body           =utils::MsgUtils::MsgFormat(Qmsgtext.body.toStdString());
    return msgtext;
}
