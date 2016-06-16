#ifndef CHATCONTROLER_H
#define CHATCONTROLER_H

#endif // CHATCONTROLER_H
#include<IChatObserver.h>
#include <QObject>
#include "linkdoodtypes.h"

class ChatControler:public QObject,public IChatObserver
{
    Q_OBJECT
public:
    void init();//初始监听接口

    ChatControler(QObject* parent=0);
    ~ChatControler();
    void onMessageNotice(std::shared_ptr<service::Msg> msg);
    void onAvatarChanged(int64 targetid, std::string avatar);
    void onOfflineMsgChanged(std::vector<OfflineMsg> msgs);
    void onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats);

signals:
   void  chatListChanged(const Chat_UIList& chats);
   void  chatOnListChanged(Chat_UIList chats);

public slots:
    void onChatListChanged(Chat_UIList chats);
};
