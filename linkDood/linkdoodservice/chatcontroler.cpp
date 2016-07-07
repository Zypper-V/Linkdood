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
#include "linkdoodservice.h"
#include "ISearchService.h"
#include "IContactService.h"
#include "IFileService.h"
#include "linkdoodtypedef.h"
#include "emojiexplain.h"

#include<QSettings>

void ChatControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setChatObserver(this);
}

void ChatControler::getContactInfo(QString userId,Msg msg)
{
    qDebug() << Q_FUNC_INFO << "xxxxxxxxxxxxxxxxxxxxxxxxx";
    service::IMClient::getClient()->getContact()->getContactInfo(userId.toLongLong(),std::bind(&ChatControler::_getContactInfo,this,std::placeholders::_1,std::placeholders::_2,msg));
}

void ChatControler::entryChat(const QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    QString path = LinkDoodService::instance()->dataPath();
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("SessionTargetID",targetId);
}

void ChatControler::exitChat(const QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    QString path = LinkDoodService::instance()->dataPath();
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.setValue("SessionTargetID","");
}

bool ChatControler::getCurrentSessionId(QString &targetId)
{
    qDebug() << Q_FUNC_INFO;
    QString path = LinkDoodService::instance()->dataPath();
    QString fileName = path+ "config.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    targetId = settings.value("SessionTargetID","").toString();

    return targetId.isEmpty();
}

void ChatControler::removeChat(QString targetid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->removeChat(targetid.toLongLong(),
                 std::bind(&ChatControler::_removeChat,this,
                           std::placeholders::_1));
}

void ChatControler::setMessageRead(QString targetid, QString msgid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->setMessageRead(targetid.toLongLong(),msgid.toLongLong());
}

void ChatControler::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->getUnReadMessages();
}

void ChatControler::sendMessage(Msg &imMsg)
{
    QDateTime dateTime = QDateTime::fromString(imMsg.time,"yyyy-MM-dd hh:mm:ss");
    QString time = dealTime(dateTime.toMSecsSinceEpoch(),1);

    emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,imMsg.body,time,imMsg.name,imMsg.thumb_avatar,"0");
    if(imMsg.msgtype.toInt() == MSG_TYPE_TEXT)
    {

        std::string src=imMsg.body.toStdString(),target("");
        //qDebug() <<Q_FUNC_INFO <<"a66666666666666";
        EmojiExplain::EmojiParseTo(src,target);
       // qDebug() <<Q_FUNC_INFO <<"b66666666666666";
        //qDebug() <<Q_FUNC_INFO <<"66666666666666:"<<src.c_str()<< "target:"<<target.c_str();

        service::MsgText msg = QmsgtextTomsgtext(imMsg);
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                     std::bind(&ChatControler::_sendMesage,this,
                               std::placeholders::_1,
                               std::placeholders::_2,
                               std::placeholders::_3,imMsg.msgid));
    }
}

void ChatControler::getMessages(QString targetid, QString msgid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->getMessages(targetid.toLongLong(),msgid.toLongLong(),count,flag,
                       std::bind(&ChatControler::_getMesage,this,
                                 std::placeholders::_1,
                                 std::placeholders::_2,
                                 std::placeholders::_3));

}

void ChatControler::deleteMessage(QString targetid, std::vector<QString> msgs)
{
    qDebug() << Q_FUNC_INFO;
    std::vector<int64>list;
    for(auto iter:msgs){
        list.push_back(iter.toLongLong());
    }
    service::IMClient::getClient()->getChat()->deleteMessage(targetid.toLongLong(),list,
                             std::bind(&ChatControler::_deleteMessage,this,
                                       std::placeholders::_1));
}

void ChatControler::getChatList()
{
    qDebug() << Q_FUNC_INFO << "dddddddddddddddd";
    service::IMClient::getClient()->getChat()->getChatList();
}

ChatControler::ChatControler(QObject* parent):
    QObject(parent)
{
    mSessionTargetID = "";
}

ChatControler::~ChatControler()
{

}

void ChatControler::onMessageNotice(std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO ;

    if(msg->msgtype == 2)
    {
       qDebug() << Q_FUNC_INFO << "adaFZSDZDFGDFGfdxggxgf:" << msg->time;
       if(msg->time == 0){
           msg->time = QDateTime::currentDateTime().toMSecsSinceEpoch();
       }
       std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg);
       Msg imMsg = msgtextToQmsgtext(msgText);
        qDebug() << Q_FUNC_INFO << "messageNotice:"<< imMsg.body;
       QString sessionId("");
       if(!getCurrentSessionId(sessionId)){
           emit chatMessageNotice(imMsg);
       }
       qDebug() << Q_FUNC_INFO << "SessionId:" << sessionId << "Time:" << imMsg.time;
       getContactInfo(imMsg.fromid,imMsg);
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
           Msg item = msgtextToQmsgtext(msgText);
           imMsg.body = item.body;
           imMsg.fromId = item.fromid;
           imMsg.msgId = item.msgid;
           imMsg.time = item.time;
           msgList.insert(msgList.size(),imMsg);
            qDebug() << Q_FUNC_INFO << "onOfflineMsgChanged:"<< imMsg.body;
        }
    }
    emit offlineMsgNoticeBack(msgList);
}

void ChatControler::onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() <<Q_FUNC_INFO<< "chats szie:" << chats.size();
    Chat_UIList  chatList;
    for(auto i: chats){

        std::shared_ptr<service::Chat> ch = std::dynamic_pointer_cast<service::Chat>(i);
        Chat_UI chatData;
        chatData.name = QString::fromStdString(ch->name);
        qDebug() <<Q_FUNC_INFO<<QString::fromStdString(ch->last_msg);
        if(ch->msg_type==2||ch->msg_type==8){
        chatData.last_msg =  QString::fromStdString(utils::MsgUtils::getText(ch->last_msg));
        }
        else{
        chatData.last_msg = "不支持的消息类型，请在电脑端查看";
        }
        chatData.avatar =  QString::fromStdString(ch->avatar);
        chatData.msg_time = dealTime(ch->msg_time,1);
        chatData.id = QString::number(ch->id);
        qDebug() << Q_FUNC_INFO << "name" << chatData.name<<"id"<<chatData.id<<"unreadcount"<<QString::number(ch->unread_count);
        chatData.chat_type = ch->chat_type;
        chatData.thumb_avatar = QString::fromStdString(ch->thumb_avatar);
        chatData.unread_count=ch->unread_count;
        if(chatData.chat_type == 1){
            chatList.push_back(chatData);
        }
        // qDebug() << Q_FUNC_INFO << "avatar" << chatData.avatar;
        // qDebug() << Q_FUNC_INFO << "thumb_avatar" << ch->thumb_avatar.c_str();
    }
    emit chatListChanged(chatList);

}

void ChatControler::uploadAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getFile()->uploadAvatar(path.toStdString(), std::bind(&ChatControler::_uploadAvatar, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void ChatControler::uploadFile(QString path, QString property)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getFile()->uploadFile(path.toStdString(), property.toStdString(), std::bind(&ChatControler::_uploadFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), std::bind(&ChatControler::_fileProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

}

void ChatControler::downloadFile(QString path, QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getFile()->downloadFile(path.toStdString(), url.toStdString(), property.toStdString(), std::bind(&ChatControler::_downloadFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), std::bind(&ChatControler::_fileProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

}

void ChatControler::uploadImage(QString thumbimg, QString srcimg, QString property)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getFile()->uploadImage(thumbimg.toStdString(), srcimg.toStdString(), property.toStdString(), std::bind(&ChatControler::_uploadImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void ChatControler::downloadImage(QString url, QString property)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getFile()->downloadImage(url.toStdString(), property.toStdString(), std::bind(&ChatControler::_downloadImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool ChatControler::decryptFile(QString encryptkey, QString srcpath, QString destpath)
{
    qDebug() << Q_FUNC_INFO;
    return service::IMClient::getClient()->getFile()->decryptFile(encryptkey.toStdString(), srcpath.toStdString(), destpath.toStdString());
}

void ChatControler::getFileList(int64 targetid, int64 fileid, int count, int flag)
{
    qDebug() << Q_FUNC_INFO;
    return service::IMClient::getClient()->getFile()->getFileList(targetid, fileid, count, flag, std::bind(&ChatControler::_getFileList, this, std::placeholders::_1, std::placeholders::_2));
}


QString ChatControler::dealTime(qint64 msgtime, int type)
{
    QString strDateTime("");
        QDateTime msgDateTime;
        int distance = 0;
        if (!msgtime)
        {
            return strDateTime;
        }
        msgDateTime.setMSecsSinceEpoch(msgtime);
        distance = msgDateTime.daysTo(QDateTime::currentDateTime());
        //今天
        if (qFabs(distance) <= 0)
        {
            strDateTime = msgDateTime.toString("HH:mm");
        }
        //昨天
        else if (qFabs(distance) <= 1)
        {
            if ( 1 == type)
            {
                strDateTime = "昨天";
            }
            else {
                strDateTime = "昨天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
            }

        }
        //前天
        else if (qFabs(distance) <= 2)
        {
            if (1 == type)
            {
                strDateTime = "前天";
            }
            else {
                strDateTime = "前天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
            }
        }
        else
        {
            if (1 == type)
            {
                strDateTime = msgDateTime.toString("MM月dd日");
            }
            else {
                strDateTime = msgDateTime.toString("MM月dd日") +QString::fromLocal8Bit(" ")+msgDateTime.toString("HH:mm");
            }
        }
        return strDateTime;
}

void ChatControler::_removeChat(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO;
    emit removeChatBack(info.code() == 0);

}

void ChatControler::_sendMesage(service::ErrorInfo &info, int64 sendTime, int64 msgId,QString localId)
{
    QString resultId =QString::number(msgId)+":"+ localId;
    if(!info.code()){
        emit sendMessageBack(true,sendTime,resultId);
    }else{
        emit sendMessageBack(false,sendTime,resultId);
    }
}

void ChatControler::_getMesage(service::ErrorInfo &info, int64 targetId, std::vector<service::MsgPtr>msgPtr)
{
    qDebug() << Q_FUNC_INFO << msgPtr.size();
    MsgList msgList;
    //std::shared_ptr<service::Msg> msg;

    for(auto msg:msgPtr){
        if(msg->msgtype == 2||msg->msgtype == 8){
            std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg);
            Msg item;
            item.activeType = QString::number(msgText->active_type);
            item.body = QString::fromStdString(utils::MsgUtils::getText(msgText->body));
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

void ChatControler::_getContactInfo(service::ErrorInfo &info, service::User &user, Msg msg)
{
    qDebug() << Q_FUNC_INFO << "sfdsffffffffffffffffffffffffffffffff" <<  user.name.c_str();
    msg.name = QString::fromStdString(user.name);
    msg.thumb_avatar = QString::fromStdString(user.thumb_avatar);
    QDateTime dateTime = QDateTime::fromString(msg.time,"yyyy-MM-dd hh:mm:ss");
    qDebug() << "dddddddddddd:"<< msg.time;
    QString time = dealTime(dateTime.toMSecsSinceEpoch(),1);
    QString sessionId("");
    if(!getCurrentSessionId(sessionId)){
       emit sessionMessageNotice(msg.targetid,msg.msgid,msg.body,time,msg.name,msg.thumb_avatar,"0");
    }
    else{
       emit sessionMessageNotice(msg.targetid,msg.msgid,msg.body,time,msg.name,msg.thumb_avatar,"1");
    }
}







void ChatControler::_uploadAvatar(std::string orgijson, std::string thumbjson, int code)
{
    emit uploadAvatarBack(orgijson, thumbjson, code);
}

void ChatControler::_uploadFile(int64 tagetid, std::string jasoninfo, int code)
{
    emit uploadFileBack(tagetid, jasoninfo, code);
}

void ChatControler::_fileProgress(int32 extra_req, int32 process, std::string info)
{
    emit fileProgressBack(extra_req, process, info);
}

void ChatControler::_downloadFile(service::ErrorInfo &info, std::string localpath, int64 tagetid)
{
    emit downloadFileBack(info.code(), localpath, tagetid);
}

void ChatControler::_uploadImage(int64 tagetid, std::string orgijson, std::string thumbjson, int code)
{
    emit uploadImageBack(tagetid, orgijson, thumbjson, code);
}

void ChatControler::_downloadImage(service::ErrorInfo &info, std::string localpath, int64 tagetid)
{
    emit downloadImageBack(info.code(), localpath, tagetid);
}

void ChatControler::_getFileList(service::ErrorInfo &info, std::vector<FileInfo> files)
{
    FileInfoList msgList;
    MsgFileInfo fileInfo;
    for(auto msg:files)
    {
        fileInfo.fileid = QString::number(msg.fileid);
        fileInfo.userid = QString::number(msg.userid);
        fileInfo.targetid = QString::number(msg.targetid);
        fileInfo.size = msg.size;
        fileInfo.time = msg.time;
        fileInfo.path = QString::fromStdString(msg.path);
        fileInfo.name = QString::fromStdString(msg.name);
        fileInfo.url = QString::fromStdString(msg.url);
        fileInfo.encrypt_key = QString::fromStdString(msg.encrypt_key);
        msgList.push_back(fileInfo);
    }
    emit getFileListBack(info.code(), msgList);
}


Msg ChatControler::msgtextToQmsgtext(std::shared_ptr<service::MsgText> msgtext)
{
    Msg Qmsgtext;
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

service::MsgText ChatControler::QmsgtextTomsgtext(Msg Qmsgtext)
{
    service::MsgText msgtext;
    if(Qmsgtext.activeType!=""){
    std::stringstream str(Qmsgtext.activeType.toStdString());
    str >> msgtext.active_type;
    }
    if(Qmsgtext.msgtype!=""){
    std::stringstream str1(Qmsgtext.msgtype.toStdString());
    str1 >> msgtext.msgtype;
    }
    if(Qmsgtext.msgid!=""){
    std::stringstream str2(Qmsgtext.msgid.toStdString());
    str2 >> msgtext.msgid;
    }
    if(Qmsgtext.targetid!=""){
    std::stringstream str3(Qmsgtext.targetid.toStdString());
    str3 >> msgtext.targetid;
    }
    if(Qmsgtext.fromid!=""){
    std::stringstream str4(Qmsgtext.fromid.toStdString());
    str4 >> msgtext.fromid;
    }
    if(Qmsgtext.toid!=""){
    std::stringstream str5(Qmsgtext.toid.toStdString());
    str5 >> msgtext.toid;
    }
    if(Qmsgtext.localid!=""){
    std::stringstream str6(Qmsgtext.localid.toStdString());
    str6 >> msgtext.localid;
    }
    if(Qmsgtext.time!=""){

      QDateTime dateTime = QDateTime::fromString(Qmsgtext.time,"yyyy-MM-dd hh:mm:ss");
      msgtext.time = dateTime.toMSecsSinceEpoch();
    }
     if(Qmsgtext.msgProperties!=""){
    msgtext.msg_properties =Qmsgtext.msgProperties.toStdString();
    }
    if(Qmsgtext.body!=""){
    msgtext.body           =Qmsgtext.body.toStdString();
    }
    return msgtext;
}
