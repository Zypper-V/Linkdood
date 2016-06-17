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

void ChatControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setChatObserver(this);
}

ChatControler::ChatControler(QObject* parent):
    QObject(parent)
{
    //qRegisterMetaType<Chat_UIList>("Chat_UIList");

    QObject::connect(this,SIGNAL(chatOnListChanged(Chat_UIList)),this,SLOT(onChatListChanged(Chat_UIList)));
}

ChatControler::~ChatControler()
{

}

void ChatControler::onMessageNotice(std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO;
}

void ChatControler::onAvatarChanged(int64 targetid, std::string avatar)
{
    qDebug() << Q_FUNC_INFO;
}

void ChatControler::onOfflineMsgChanged(std::vector<OfflineMsg> msgs)
{
    qDebug() << Q_FUNC_INFO;
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
            qDebug() << Q_FUNC_INFO << "avatar" << chatData.avatar;
            qDebug() << Q_FUNC_INFO << "thumb_avatar" << chatData.thumb_avatar;
        }
        emit chatOnListChanged(chatList);
    }
}

void ChatControler::onChatListChanged( Chat_UIList chats)
{
    qDebug() <<Q_FUNC_INFO<< "chats2 szie:" << chats.size();

    emit chatListChanged(chats);
}
