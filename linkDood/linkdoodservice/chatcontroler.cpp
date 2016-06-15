#include<chatcontroler.h>
#include<iostream>
#include<QDebug>

#include "IMClient.h"
#include "IChatService.h"
#include "INotifyService.h"

void ChatControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setChatObserver(this);
}

ChatControler::ChatControler()
{

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
    if(flag == 0x04)
    {
        auto iter = chats.begin();
        for(;iter != chats.end();++iter)
        {
            qDebug() <<"chat list:" <<  (*iter)->name.c_str();
        }
    }
}
