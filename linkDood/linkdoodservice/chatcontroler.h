#ifndef CHATCONTROLER_H
#define CHATCONTROLER_H

#endif // CHATCONTROLER_H
#include<IChatObserver.h>
class ChatControler:public IChatObserver
{
public:
    ChatControler();
    ~ChatControler();
    void onMessageNotice(std::shared_ptr<service::Msg> msg);
    void onAvatarChanged(int64 targetid, std::string avatar);
    void onOfflineMsgChanged(std::vector<OfflineMsg> msgs);
    void onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats);

};
