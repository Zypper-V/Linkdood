#include<chatcontroler.h>
#include<iostream>
#include<QDebug>
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
}
