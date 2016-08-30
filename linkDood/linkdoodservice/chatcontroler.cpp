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
#include "FileUtils.h"
#include "EncryptKey.h"
#include "Contact.h"
#include "IDRangeJuge.hpp"
#include "IGroupService.h"

#include<QSettings>

void ChatControler::init()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getNotify()->setChatObserver(this);
}

void ChatControler::getContactInfo(QString userId,Msg msg)
{
    int64 id = userId.toLongLong();
    qDebug() << Q_FUNC_INFO << "userId:"<<userId<<"long long:"<<id;
    //service::IMClient::getClient()->getContact()->getContactInfo(id,std::bind(&ChatControler::_getContactInfo,this,std::placeholders::_1,std::placeholders::_2,msg));
}

void ChatControler::getUserProfile(QString userId, std::shared_ptr<service::Msg> msg)
{
    qDebug()<<Q_FUNC_INFO<<"userId:"<<userId;
    service::IMClient::getClient()->getSearch()->getUserInfo(userId.toLongLong(),std::bind(&ChatControler::_getUserProfile,this,std::placeholders::_1,std::placeholders::_2,msg));
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

    qDebug() << Q_FUNC_INFO << "targetId:" << targetId;
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
    qDebug() << Q_FUNC_INFO<<"targetid:"<<targetid<<"msgid:"<<msgid;
    service::IMClient::getClient()->getChat()->setMessageRead(targetid.toLongLong(),msgid.toLongLong());
}

void ChatControler::getUnReadMessages()
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getChat()->getUnReadMessages();
}

void ChatControler::sendMessage(Msg &imMsg)
{
    if(imMsg.isTransMsg){
        transMessage(imMsg);
        return;
    }

    QDateTime dateTime = QDateTime::fromString(imMsg.time,"yyyy-MM-dd hh:mm:ss");
    //QString time = dealTime(dateTime.toMSecsSinceEpoch(),1);
    QString time = QString::number(dateTime.toMSecsSinceEpoch());

    if(imMsg.msgtype.toInt() == MSG_TYPE_TEXT)
    {

        std::string src=imMsg.body.toStdString(),target("");
        EmojiExplain::EmojiParseTo(src,target);
        imMsg.body = QString::fromStdString(target);

        qDebug() << Q_FUNC_INFO<<"sendMessage:"<< imMsg.body;
        service::MsgText msg = QmsgtextTomsgtext(imMsg);
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_sendMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,imMsg.localid,imMsg.targetid));


        //解析表情文本类型
        src=imMsg.body.toStdString();
        target="";
        EmojiExplain::EmojiParseFrom(src,target);
        imMsg.body = QString::fromStdString(target);
        emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,imMsg.body,time,imMsg.targetName,imMsg.thumb_avatar,"0");
    }else if(imMsg.msgtype.toInt() == MEDIA_MSG_DYNAMIC_EMOJI){
        service::MsgDynExpression msg;
        msg.localid = imMsg.localid.toLongLong();
        msg.fromid = imMsg.fromid.toLongLong();
        msg.toid = imMsg.toid.toLongLong();
        msg.targetid = imMsg.targetid.toLongLong();
        msg.msgtype = MEDIA_MSG_DYNAMIC_EMOJI;
        QDateTime dateTime = QDateTime::fromString(imMsg.time,"yyyy-MM-dd hh:mm:ss");
        msg.time = dateTime.toMSecsSinceEpoch();

        QString explain(""),target("");
        EmojiExplain::dyEmojiParseTo(imMsg.body,target,explain);
        msg.body = target.toStdString();
        emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,explain,time,imMsg.targetName,imMsg.thumb_avatar,"0");
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_sendMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,imMsg.localid,imMsg.targetid));
    }else if(imMsg.msgtype.toInt() == MSG_TYPE_IMG){
        service::MsgImg msg;
        msg.main_url = imMsg.main_url.toStdString();
        msg.encrypt_key = imMsg.encrypt_key.toStdString();
        msg.file_name  =imMsg.filename.toStdString();
        msg.fromid = imMsg.fromid.toLongLong();
        msg.targetid = imMsg.targetid.toLongLong();
        msg.height = imMsg.i_height.toInt();
        msg.msgtype = 5;
        msg.toid = imMsg.targetid.toLongLong();
        msg.thumb_url = imMsg.thumb_url.toStdString();
        msg.width = imMsg.i_width.toInt();
        msg.encrypt_user = imMsg.encrypt_user.toLongLong();
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_sendMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,imMsg.localid,imMsg.targetid));
        emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,"[图片]",time,imMsg.targetName,imMsg.thumb_avatar,"0");
    }else if(imMsg.msgtype.toInt() == MSG_TYPE_FILE){
        service::MsgFile msg;
        msg.encrypt_user = imMsg.encrypt_user.toLongLong();
        msg.body = "";
        msg.encrypt_key = imMsg.encrypt_key.toStdString();
        msg.file_name = imMsg.filename.toStdString();
        msg.msgtype = MSG_TYPE_FILE;
        msg.fromid = imMsg.fromid.toLongLong();
        msg.file_path = imMsg.f_path.toStdString();
        msg.targetid = imMsg.targetid.toLongLong();
        msg.url = imMsg.f_url.toStdString();
        msg.toid = imMsg.toid.toLongLong();
        QDateTime dateTime = QDateTime::fromString(imMsg.time,"yyyy-MM-dd hh:mm:ss");
        msg.time = dateTime.toMSecsSinceEpoch();
        msg.states = 1;
        msg.size = imMsg.f_size.toLongLong();
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_sendMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,imMsg.localid,imMsg.targetid));
        emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,"[文件]",time,imMsg.targetName,imMsg.thumb_avatar,"0");
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
    qRegisterMetaType<std::shared_ptr<service::Msg> >("std::shared_ptr<service::Msg>");
    connect(this,SIGNAL(handleRevMsg(std::shared_ptr<service::Msg>)),this,SLOT(onHandleRevMsg(std::shared_ptr<service::Msg>)));

    mSessionTargetID = "";
    m_pWorkControl = new LinkDoodServiceThread(this);
    m_pWorkControl->moveToThread(&mWorkThread);
    connect(this,SIGNAL(bcNotify(QString,QString,QString,QString,QString,QString,QString,QString,int)),m_pWorkControl,SLOT(bcNotify(QString,QString,QString,QString,QString,QString,QString,QString,int)));
    mWorkThread.start();
}

ChatControler::~ChatControler()
{
    mWorkThread.quit();
    mWorkThread.wait();
}

void ChatControler::handleReciveImgMsg(std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO;
    std::shared_ptr<service::MsgImg> msgImg = std::dynamic_pointer_cast<service::MsgImg>(msg);
    QString thumbPath = QString::fromStdString(msgImg->thumb_url);
    QString appDataPath =  APP_DATA_PATH +LinkDoodService::instance()->UserId() + "/";


    Msg imMsg;
    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MSG_TYPE_IMG);
    imMsg.fromid = QString::number(msg->fromid);
    imMsg.toid   = QString::number(msg->toid);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.activeType = QString::number(msg->active_type);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    imMsg.i_height = QString::number(msgImg->height);
    imMsg.i_width  = QString::number(msgImg->width);
    imMsg.main_url = QString::fromStdString(msgImg->main_url);
    imMsg.encrypt_user = QString::number(msgImg->encrypt_user);
    imMsg.encrypt_key = QString::fromStdString(msgImg->encrypt_key);
    imMsg.thumb_url = QString::fromStdString(msgImg->thumb_url);
    imMsg.filename = QString::fromStdString(msgImg->file_name);
    imMsg.fromName = QString::fromStdString(msg->from_name);
    imMsg.body     = "[图片]";
    if(judgeFileExist(thumbPath,MSG_TYPE_IMG)){
        QDir tempDir;
        if (!tempDir.exists(appDataPath))
        {
            tempDir.mkdir(appDataPath);
        }
        QStringList strList = thumbPath.split("/");
        if (strList.size() > 0)
        {
            QString fileName = strList.at(strList.size() - 1);
            QString srcPath = appDataPath +"image/"+ fileName;
            QString outPath = (QString::fromStdString(APP_SAVE_IAMGE_APTH) +"/"+ fileName);
            if (!tempDir.exists(APP_SAVE_IAMGE_APTH))
            {
                tempDir.mkdir(APP_SAVE_IAMGE_APTH);
            }
            bool ret = service::IMClient::getClient()->getFile()->decryptFile(msgImg->encrypt_key,srcPath.toStdString(),outPath.toStdString());

            if(ret){
                imMsg.thumb_url = outPath;
                sendSessionMsg(imMsg);
            }
        }
    }else{
        //下载图片
        downloadImage(imMsg);
    }
}

void ChatControler::handleReciveFileMsg(std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO;
    std::shared_ptr<service::MsgFile> msgFile = std::dynamic_pointer_cast<service::MsgFile>(msg);

    Msg imMsg;
    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MSG_TYPE_FILE);
    imMsg.fromid = QString::number(msg->fromid);
    imMsg.toid   = QString::number(msg->toid);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.activeType = QString::number(msg->active_type);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");

    qDebug()<<Q_FUNC_INFO<<"msg:"<<msgFile->file_name.c_str()<<"size:"<<msgFile->size;
    imMsg.f_state = QString::number(msgFile->states);
    imMsg.f_id = QString::number(msgFile->fileid);
    imMsg.f_size  = QString::number(msgFile->size);
    imMsg.encrypt_user = QString::number(msgFile->encrypt_user);
    imMsg.encrypt_key = QString::fromStdString(msgFile->encrypt_key);
    imMsg.f_path = QString::fromStdString(msgFile->file_path);
    imMsg.f_url = QString::fromStdString(msgFile->url);
    imMsg.filename = QString::fromStdString(msgFile->file_name);
    imMsg.fromName = QString::fromStdString(msg->from_name);
    imMsg.body = "[文件]";
    sendSessionMsg(imMsg);
}

void ChatControler::handleReciveDyEmojiMsg(std::shared_ptr<service::Msg> msg)
{
    std::shared_ptr<service::MsgDynExpression> msgDyEmoji = std::dynamic_pointer_cast<service::MsgDynExpression>(msg);
    Msg imMsg;
    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MEDIA_MSG_DYNAMIC_EMOJI);
    imMsg.fromid = QString::number(msg->fromid);
    imMsg.toid   = QString::number(msg->toid);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.activeType = QString::number(msg->active_type);
    imMsg.fromName = QString::fromStdString(msg->from_name);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    QString explian(""),target("");
    std::string msgBody = utils::MsgUtils::getText(msg->body);
    EmojiExplain::dyEmojiParseFrom(QString::fromStdString(msgBody),target,explian);
    imMsg.body = target;
    imMsg.filename = explian;
    qDebug()<<Q_FUNC_INFO<<"exp:"<<imMsg.filename;
    sendSessionMsg(imMsg);
}

void ChatControler::sendSessionMsg(Msg imMsg)
{
    QString sessionId("");
    getCurrentSessionId(sessionId);
    QString isUnread = "0";
    QDateTime dateTime = QDateTime::fromString(imMsg.time,"yyyy-MM-dd hh:mm:ss");
    //QString time = dealTime(dateTime.toMSecsSinceEpoch(),1);
    QString time = QString::number(dateTime.toMSecsSinceEpoch());
    emit chatMessageNotice(imMsg);
    qDebug()<<Q_FUNC_INFO<<"session:"<<sessionId<<"tagertId:"<<imMsg.targetid;
    if(sessionId == imMsg.targetid){
    }else{
        isUnread = "1";
    }
    if(imMsg.msgtype == QString::number(MEDIA_MSG_DYNAMIC_EMOJI)){
        imMsg.body = imMsg.filename;
    }
    qDebug()<<Q_FUNC_INFO<<"session:"<<imMsg.body;
    emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,imMsg.body,time,imMsg.targetName,imMsg.thumb_avatar,isUnread);
}

void ChatControler::transMessage(Msg imMsg)
{

    QDateTime dateTime = QDateTime::fromString(imMsg.time,"yyyy-MM-dd hh:mm:ss");
    int64 time = dateTime.toMSecsSinceEpoch();
    QString bodyText(""),timeText = QString::number(time);

    QString info = imMsg.targetid +":"+imMsg.localid+":"+imMsg.targetName+":"+imMsg.thumb_avatar+":"+time;
    if(imMsg.msgtype.toInt() == MSG_TYPE_TEXT)
    {

        std::string src=imMsg.msgProperties.toStdString(),target("");
        EmojiExplain::EmojiParseTo(src,target);
        bodyText = imMsg.body;
        imMsg.body = QString::fromStdString(target);

        service::MsgText msg = QmsgtextTomsgtext(imMsg);
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_transMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,info));


    }else if(imMsg.msgtype.toInt() == MEDIA_MSG_DYNAMIC_EMOJI){
        service::MsgDynExpression msg;
        msg.localid = imMsg.localid.toLongLong();
        msg.fromid = imMsg.fromid.toLongLong();
        msg.toid = imMsg.toid.toLongLong();
        msg.targetid = imMsg.targetid.toLongLong();
        msg.msgtype = MEDIA_MSG_DYNAMIC_EMOJI;
        msg.time  = time;

        QString explain(""),target("");
        EmojiExplain::dyEmojiParseTo(imMsg.body,target,explain);
        msg.body = target.toStdString();
        bodyText = explain;
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_transMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,info));
    }else if(imMsg.msgtype.toInt() == MSG_TYPE_IMG){
        service::MsgImg msg;
        msg.main_url = imMsg.main_url.toStdString();
        msg.encrypt_key = imMsg.encrypt_key.toStdString();
        msg.file_name  =imMsg.filename.toStdString();
        msg.fromid = imMsg.fromid.toLongLong();
        msg.targetid = imMsg.targetid.toLongLong();
        msg.height = imMsg.i_height.toInt();
        msg.msgtype = 5;
        msg.toid = imMsg.targetid.toLongLong();
        msg.thumb_url = imMsg.thumb_url.toStdString();
        msg.width = imMsg.i_width.toInt();
        msg.time  = time;
        bodyText = "图片";
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_transMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,info));
    }else if(imMsg.msgtype.toInt() == MSG_TYPE_FILE){
        service::MsgFile msg;
        msg.encrypt_user = imMsg.encrypt_user.toLongLong();
        msg.body = "";
        msg.encrypt_key = imMsg.encrypt_key.toStdString();
        msg.file_name = imMsg.filename.toStdString();
        msg.msgtype = MSG_TYPE_FILE;
        msg.fromid = imMsg.fromid.toLongLong();
        msg.file_path = imMsg.f_path.toStdString();
        msg.targetid = imMsg.targetid.toLongLong();
        msg.url = imMsg.f_url.toStdString();
        msg.toid = imMsg.toid.toLongLong();
        msg.time  = time;
        msg.states = 1;
        msg.size = imMsg.f_size.toLongLong();
        bodyText = "文件";
        service::IMClient::getClient()->getChat()->sendMessage(msg,
                                                               std::bind(&ChatControler::_transMesage,this,
                                                                         std::placeholders::_1,
                                                                         std::placeholders::_2,
                                                                         std::placeholders::_3,info));
    }
    emit sessionMessageNotice(imMsg.targetid,imMsg.msgid,bodyText,timeText,imMsg.targetName,imMsg.thumb_avatar,"0");
}

void ChatControler::handleRecevieTextMsg(std::shared_ptr<service::Msg> msg)
{
    if(msg->time == 0){
        msg->time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    }
    std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg);
    Msg imMsg = msgtextToQmsgtext(msgText);
    imMsg.fromName = QString::fromStdString(msg->from_name);
    std::string target("");
    EmojiExplain::EmojiParseFrom(imMsg.body.toStdString(),target);
    imMsg.body = QString::fromStdString(target);
    imMsg.fromName = QString::fromStdString(msg->from_name);
    qDebug()<<Q_FUNC_INFO<<"1111111111111111111111";
    sendSessionMsg(imMsg);
}

void ChatControler::handleReciveTipMsg(std::shared_ptr<service::Msg> msg)
{
    //handleReciveTipMsg(msg);
    std::shared_ptr<service::MsgTip> msgTip = std::dynamic_pointer_cast<service::MsgTip>(msg);

    Msg imMsg;
    imMsg.body = QString::fromStdString(msgTip->body);
    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MSG_TYPE_TIP);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.fromid = QString::number(msg->targetid);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    emit chatMessageNotice(imMsg);
}

void ChatControler::handleReciveUnSurportMsg(std::shared_ptr<service::Msg> msg)
{
    Msg msgTip;
    msgTip.msgtype      = QString::number(MSG_TYPE_TEXT);
    msgTip.activeType   =QString::number(msg->active_type);
   // msgTip.msgtype      =QString::number(msg->msgtype);
    msgTip.msgid        =QString::number(msg->msgid);
    msgTip.targetid     =QString::number(msg->targetid);
    msgTip.fromid       =QString::number(msg->fromid);
    msgTip.toid         =QString::number(msg->toid);
    msgTip.localid      =QString::number(msg->localid);
    msgTip.time         =QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    msgTip.body = "此类型消息暂不支持，请在PC端查看";
    msgTip.fromName = QString::fromStdString(msg->from_name);
    sendSessionMsg(msgTip);
}

void ChatControler::onMessageNotice(std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO ;
    emit handleRevMsg(msg);
}

void ChatControler::onAvatarChanged(int64 userid, std::string avatar)
{
    if(avatar.size() == 0)
        return;
    qDebug() << Q_FUNC_INFO <<userid;
    emit chatAvatarChanged(QString::number(userid), QString::fromStdString(avatar));
}

void ChatControler::onOfflineMsgChanged(std::vector<OfflineMsg> msgs)
{
    qDebug() << Q_FUNC_INFO <<"offlineMsg:" << msgs.size();
    IMOfflineMsgList msgList;

    for(auto msg:msgs){
        if(msg.msg == NULL){
            return;
        }
        IMOfflineMsg imMsg;
        imMsg.offlineType = msg.offline_type;
        imMsg.count  = msg.count;

        imMsg.fromId =QString::number(msg.msg->fromid);
        imMsg.msgId  = QString::number(msg.msg->msgid);
        //imMsg.time   = QDateTime::fromMSecsSinceEpoch(msg.msg->time).toString("yyyy-MM-dd hh:mm:ss");
        imMsg.time =QString::number(msg.msg->time) /*dealTime(msg.msg->time,1)*/;
        imMsg.targetId =QString::number(msg.msg->targetid);
        if(msg.msg->msgtype == MSG_TYPE_TEXT){
            std::string target("");
            std::string msgBody = utils::MsgUtils::getText(msg.msg->body);
            if(msgBody == ""){
                msgBody = msg.msg->body;
            }
            EmojiExplain::EmojiParseFrom(msgBody,target);
            imMsg.body = QString::fromStdString(target);
        }
        else if(msg.msg->msgtype == MEDIA_MSG_DYNAMIC_EMOJI){
            QString explian(""),target("");
            std::string msgBody = utils::MsgUtils::getText(msg.msg->body);
            if(msgBody == ""){
                msgBody = msg.msg->body;
            }
            EmojiExplain::dyEmojiParseFrom(QString::fromStdString(msgBody),target,explian);
            imMsg.body = explian;
        }else if(msg.msg->msgtype == MSG_TYPE_FILE){
            imMsg.body = "文件";
        }else if(msg.msg->msgtype == MSG_TYPE_IMG){
            imMsg.body = "图片";
        }else{
            continue;
            imMsg.body = "此类型消息暂不支持，请在PC端查看";
        }
        msgList.push_back(imMsg);
    }
    emit offlineMsgNoticeBack(msgList);
}

void ChatControler::onListChanged(int flag, std::vector<std::shared_ptr<service::User> > chats)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() <<Q_FUNC_INFO<< "kanzhelikanzhelikanzheli" << chats.size();
    Chat_UIList  chatList;
    for(auto i: chats){

        if(i == NULL ){
            continue;
        }
        std::shared_ptr<service::Chat> ch = std::dynamic_pointer_cast<service::Chat>(i);
        if(ch->msg_type == 0||(IS_MSG_APP(ch->id))){
            continue;
        }
        Chat_UI chatData;
        chatData.name = QString::fromStdString(ch->name);
        qDebug() <<Q_FUNC_INFO<<QString::fromStdString(ch->last_msg);
        if(ch->msg_type== MSG_TYPE_TEXT){
            chatData.last_msg =  QString::fromStdString(utils::MsgUtils::getText(ch->last_msg));
            std::string target("");
            EmojiExplain::EmojiParseFrom(chatData.last_msg.toStdString(),target);
            chatData.last_msg = QString::fromStdString(target);
        }else if(ch->msg_type== MEDIA_MSG_DYNAMIC_EMOJI){

            std::string msgBody = utils::MsgUtils::getText(ch->last_msg);
            if(msgBody == ""){
                msgBody = ch->last_msg;
            }
            QString explian(""),target("");
            EmojiExplain::dyEmojiParseFrom(QString::fromStdString(msgBody),target,explian);
            chatData.last_msg = explian;
        }
        else if(ch->msg_type== MSG_TYPE_IMG){
            chatData.last_msg = "图片";
        }
        else if(ch->msg_type== MSG_TYPE_FILE){
            chatData.last_msg = "文件";
        }
        else{
            continue;
            chatData.last_msg = "此类型消息暂不支持，请在PC端查看";

        }
        chatData.avatar =  QString::fromStdString(ch->avatar);
        chatData.msg_time = QString::number(ch->msg_time)/*dealTime(ch->msg_time,1)*/;
        chatData.id = QString::number(ch->id);
        chatData.last_msgid = ch->last_msgid;
        qDebug() << Q_FUNC_INFO << "name" << chatData.name<<"tarid:"<<chatData.id<<" lastid:"<<chatData.last_msgid;
        chatData.chat_type = ch->chat_type;
        chatData.thumb_avatar = QString::fromStdString(ch->thumb_avatar);
        chatData.unread_count=ch->unread_count;
        qDebug()<<Q_FUNC_INFO<<"unread_count:"<<chatData.unread_count;
        chatList.push_back(chatData);
    }
    emit chatListChanged(chatList);

}

void ChatControler::uploadAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO << "path:" << path;
    service::IMClient::getClient()->getFile()->uploadAvatar(path.toStdString(), std::bind(&ChatControler::_uploadAvatar, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void ChatControler::uploadAndSendFileMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO;

    utils::FileUtils::Property p;
    EncryptKey encry;
    p.targetid = msg.targetid.toLongLong();
    p.encryptkey = encry.get_key();

    //std::string property = utils::FileUtils::setProperty(p);
    QString json("");
    json=json+"{\"encryptkey\":\""+p.encryptkey.c_str()+"\",\"targetid\":"+msg.targetid+"}";

    msg.encrypt_key = QString::fromStdString(p.encryptkey);
    msg.encrypt_user = msg.fromid;

    qDebug() << Q_FUNC_INFO << "f_path:" << msg.f_path << "  json:" << json;
    qint64 code = service::IMClient::getClient()->getFile()->uploadFile(msg.f_path.toStdString(), json.toStdString(), std::bind(&ChatControler::_uploadFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,std::placeholders::_4,msg), std::bind(&ChatControler::_fileProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,msg.msgid,msg.targetid));
    qDebug()<<Q_FUNC_INFO<<"ret:"<<code;
}

void ChatControler::downloadFile(QString path, QString url, QString json,QString localId,QString targetId)
{
    qDebug() << Q_FUNC_INFO;
    QString allFilePath = APP_DATA_PATH +LinkDoodService::instance()->UserId() + "/file/" + path;
    QString encryFilePath = APP_SAVE_FILE_APTH;
    encryFilePath +="/"+path;

    qDebug() << Q_FUNC_INFO << "allPath:" << allFilePath << "  url:" << url << "  json:" << json << "    localId:" << localId << "  targetId:" << targetId;
    qint64 code = service::IMClient::getClient()->getFile()->downloadFile(allFilePath.toStdString(), url.toStdString(), json.toStdString(), std::bind(&ChatControler::_downloadFile, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, encryFilePath, json,localId), std::bind(&ChatControler::_fileProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,localId,targetId));
    qDebug()<<Q_FUNC_INFO<<"ret:"<<code;
    emit downloadFileCancelId(localId,QString::number(code));
}

void ChatControler::cancelDonwloadFile(QString id)
{
    service::IMClient::getClient()->getFile()->cancel(service::FILE_DOWNLOAD,id.toLongLong(),std::bind(&ChatControler::_cancelFile,this, std::placeholders::_1));
}

void ChatControler::uploadAndSendImageMsg(Msg msg)
{
    qDebug() << Q_FUNC_INFO<<"3333:"<<msg.thumb_url<<":"<<msg.main_url<<":targetId:"<<msg.targetid;
    utils::FileUtils::Property p;
    EncryptKey encry;
    p.targetid = msg.targetid.toLongLong();
    p.encryptkey = encry.get_key();

    qDebug()<<Q_FUNC_INFO<<"4444:"<<encry.get_key().c_str();
    //std::string property = utils::FileUtils::setProperty(p);
    QString json("");
    json=json+"{\"encryptkey\":\""+p.encryptkey.c_str()+"\",\"targetid\":"+msg.targetid+"}";
    qDebug()<<Q_FUNC_INFO<<"555:"<<json;
    msg.encrypt_key = QString::fromStdString(p.encryptkey);
    msg.encrypt_user = msg.fromid;
    qDebug()<<Q_FUNC_INFO<<"666:"<<msg.encrypt_key;
    service::IMClient::getClient()->getFile()->uploadImage(msg.thumb_url.toStdString(), msg.main_url.toStdString(),json.toStdString(), std::bind(&ChatControler::_uploadImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,msg),std::bind(&ChatControler::_uploadImageProgess,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,msg.targetid,msg.localid));
}

void ChatControler::downloadImage(Msg msgImg)
{
    qDebug() << Q_FUNC_INFO;
    utils::FileUtils::Property p ;
    p.encryptkey = msgImg.encrypt_key.toStdString();
    p.targetid   = msgImg.targetid.toLongLong();
    qDebug() << Q_FUNC_INFO << "thum:"<<msgImg.thumb_url;
    QString json("");
    json=json+"{\"encryptkey\":\""+p.encryptkey.c_str()+"\",\"targetid\":"+msgImg.targetid+"}";
    qDebug() << Q_FUNC_INFO << "json:"<<json;
    service::IMClient::getClient()->getFile()->downloadImage(msgImg.thumb_url.toStdString(), json.toStdString(), std::bind(&ChatControler::_downloadImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,msgImg));
}

void ChatControler::downloadMainImage(QString main_url, QString encryptkey, QString targetId)
{
    qDebug() << Q_FUNC_INFO<<"main_url:"<<main_url<<"encryptkey:"<<encryptkey<<"targetId:"<<targetId;
    utils::FileUtils::Property p ;
    p.encryptkey=encryptkey.toStdString();
    p.targetid=targetId.toLongLong();
    QString json("");
    json=json+"{\"encryptkey\":\""+p.encryptkey.c_str()+"\",\"targetid\":"+targetId+"}";
    service::IMClient::getClient()->getFile()->downloadImage(main_url.toStdString(), json.toStdString(), std::bind(&ChatControler::_downloadMainImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,encryptkey,main_url));
}

void ChatControler::downloadHistoryImage(QString url, QString encryptKey, QString targetid, QString localid)
{
    qDebug() << Q_FUNC_INFO;
    utils::FileUtils::Property p ;
    p.encryptkey = encryptKey.toStdString();
    p.targetid   = targetid.toLongLong();
    QString json("");
    json=json+"{\"encryptkey\":\""+p.encryptkey.c_str()+"\",\"targetid\":"+targetid+"}";
    service::IMClient::getClient()->getFile()->downloadImage(url.toStdString(), json.toStdString(), std::bind(&ChatControler::_downloadHistoryImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, encryptKey, targetid, localid));

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

void ChatControler::getUserInfo(QString userid)
{
    qDebug() << Q_FUNC_INFO;
    service::IMClient::getClient()->getSearch()->getUserInfo(userid.toLongLong(), std::bind(&ChatControler::_getUserInfo, this, std::placeholders::_1, std::placeholders::_2));
}

void ChatControler::onSystemMessageNotice(QString info, int64 time)
{
    qDebug()<<Q_FUNC_INFO<<"info:"<<info;
    emit bcNotify("-5","-5",info,"-5",QString::number(time),"系统消息","","",1);
}

void ChatControler::onHandleRevMsg(std::shared_ptr<service::Msg> msg)
{
    if(msg != NULL){
        qDebug()<<Q_FUNC_INFO<<"mesage:targetId:"<<msg->targetid<<"fromId:"<<msg->fromid<<"body:"<<msg->body.c_str();
        if(msg->msgtype == MSG_TYPE_TEXT)
        {
            handleRecevieTextMsg(msg);
        }else if(msg->msgtype == MSG_TYPE_IMG){
            handleReciveImgMsg(msg);
        }else if(msg->msgtype == MSG_TYPE_FILE){
            handleReciveFileMsg(msg);
        }else if(msg->msgtype == MEDIA_MSG_DYNAMIC_EMOJI){
            handleReciveDyEmojiMsg(msg);
        }else if(msg->msgtype == MSG_TYPE_TIP){
            handleReciveTipMsg(msg);
        }else{
            //handleReciveUnSurportMsg(msg);
        }
        if(msg->msgtype != MSG_TYPE_TIP){
            handleNotification(msg);
        }
    }
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

void ChatControler::_sendMesage(service::ErrorInfo &info, int64 sendTime, int64 msgId,QString localId,QString targetId)
{
    QString resultId =QString::number(msgId)+":"+ localId+":"+targetId;
    qDebug()<<Q_FUNC_INFO<<"msg:"<<msgId<<":"<<info.code();
    if(info.code() == 0){
        emit sendMessageBack(true,sendTime,resultId);
    }else{
        emit sendMessageBack(false,sendTime,resultId);
    }
}

void ChatControler::_transMesage(service::ErrorInfo &info, int64 sendTime, int64 msgId, QString content)
{
    emit transMessageFinishBack(info.code(),content);
}

void ChatControler::_getMesage(service::ErrorInfo &info, int64 targetId, std::vector<service::MsgPtr>msgPtr)
{
    qDebug() << Q_FUNC_INFO << "sgdfgdfgfdj:"<<msgPtr.size();
    MsgList msgList;
    for(auto msg:msgPtr){
        if(msg->msgtype == MSG_TYPE_TEXT){
            qDebug()<<Q_FUNC_INFO<<"xxxxxxxxxxxxxxxxx:"<<msg->body.c_str();
            std::shared_ptr<service::MsgText> msgText = std::dynamic_pointer_cast<service::MsgText>(msg);
            Msg imMsg = msgtextToQmsgtext(msgText);

            std::string target(""),src = imMsg.body.toStdString();
            EmojiExplain::EmojiParseFrom(src,target);
            imMsg.body = QString::fromStdString(target);

            msgList.push_back(imMsg);

        }
        else if(msg->msgtype == MSG_TYPE_IMG)
        {
            Msg imMsg;
            handleHistoryImgMsg(imMsg,msg);
            msgList.push_back(imMsg);
        }else if(msg->msgtype == MEDIA_MSG_DYNAMIC_EMOJI){

            Msg imMsg;
            handleHistoryDyEmjiMsg(imMsg,msg);
            qDebug()<<Q_FUNC_INFO<<"dy:"<<imMsg.body;
            msgList.push_back(imMsg);
        }else if(msg->msgtype == MSG_TYPE_FILE){
            Msg imMsg;
            handleHistoryFileMsg(imMsg,msg);
            msgList.push_back(imMsg);

        }else if(msg->msgtype == MSG_TYPE_TIP){
            Msg imMsg;
            imMsg.body = QString::fromStdString(msg->body);
            imMsg.msgid = QString::number(msg->msgid);
            imMsg.msgtype = QString::number(MSG_TYPE_TIP);
            imMsg.targetid = QString::number(msg->targetid);
            imMsg.fromid = QString::number(msg->targetid);
            imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
            msgList.push_back(imMsg);
        }
        else{
            Msg msgTip;
            msgTip.msgtype      = QString::number(MSG_TYPE_TEXT);
            msgTip.activeType   =QString::number(msg->active_type);
            //msgTip.msgtype      =QString::number(msg->msgtype);
            msgTip.msgid        =QString::number(msg->msgid);
            msgTip.targetid     =QString::number(msg->targetid);
            msgTip.fromid       =QString::number(msg->fromid);
            msgTip.toid         =QString::number(msg->toid);
            msgTip.localid      =QString::number(msg->localid);
            msgTip.time         =QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
            msgTip.body = "此类型消息暂不支持，请在PC端查看";
            msgTip.fromName = QString::fromStdString(msg->from_name);
            msgList.push_back(msgTip);
        }
    }
    if(!info.code()){
        emit getMessagesBack(true,targetId,msgList);
    }else{
        emit getMessagesBack(true,targetId,msgList);
    }
}

void ChatControler::handleHistoryDyEmjiMsg(Msg& imMsg,std::shared_ptr<service::Msg> msg){
    std::shared_ptr<service::MsgDynExpression> msgDyEmoji = std::dynamic_pointer_cast<service::MsgDynExpression>(msg);
    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MEDIA_MSG_DYNAMIC_EMOJI);
    imMsg.fromid = QString::number(msg->fromid);
    imMsg.toid   = QString::number(msg->toid);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.activeType = QString::number(msg->active_type);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    QString explian(""),target("");
    std::string msgBody = utils::MsgUtils::getText(msg->body);
    if(msgBody == ""){
        msgBody = msg->body;
    }
    qDebug()<<Q_FUNC_INFO<<"hist:"<<msg->body.c_str();
    EmojiExplain::dyEmojiParseFrom(QString::fromStdString(msgBody),target,explian);
    imMsg.body = target;
}

void ChatControler::handleHistoryImgMsg(Msg &imMsg, std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO;
    std::shared_ptr<service::MsgImg> msgImg = std::dynamic_pointer_cast<service::MsgImg>(msg);

    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MSG_TYPE_IMG);
    imMsg.fromid = QString::number(msg->fromid);
    imMsg.toid   = QString::number(msg->toid);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.activeType = QString::number(msg->active_type);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    imMsg.i_height = QString::number(msgImg->height);
    imMsg.i_width  = QString::number(msgImg->width);
    imMsg.main_url = QString::fromStdString(msgImg->main_url);
    imMsg.encrypt_user = QString::number(msgImg->encrypt_user);
    imMsg.encrypt_key = QString::fromStdString(msgImg->encrypt_key);
    imMsg.thumb_url = QString::fromStdString(msgImg->thumb_url);
    imMsg.filename = QString::fromStdString(msgImg->file_name);
    QStringList list = imMsg.thumb_url.split("/");
    QString fileName = list.at(list.size() -1);
    qDebug()<<Q_FUNC_INFO<<"10 img path:"<<imMsg.thumb_url;
    if(judgeFileExist(fileName,MSG_TYPE_IMG)){

        QString tempImagePath =  APP_DATA_PATH +LinkDoodService::instance()->UserId()+"/cache/"+fileName;
        QFileInfo file(tempImagePath);
        if(file.exists()){
            imMsg.body = tempImagePath;
            qDebug()<<Q_FUNC_INFO<<"1 img path:"<<imMsg.body;
        }else{
            tempImagePath = APP_DATA_PATH +LinkDoodService::instance()->UserId()+"/image/"+fileName;
            QString outPath = APP_DATA_PATH +LinkDoodService::instance()->UserId()+"/cache/"+fileName;
            bool ret = service::IMClient::getClient()->getFile()->decryptFile(msgImg->encrypt_key,tempImagePath.toStdString(),outPath.toStdString());
            if(ret){
                imMsg.body = outPath;

                qDebug()<<Q_FUNC_INFO<<"2 img path:"<<imMsg.body;
            }else{
                imMsg.body = "";
                qDebug()<<Q_FUNC_INFO<<"3 img path:"<<imMsg.body;
            }
        }
    }else{
        imMsg.body = "";
        qDebug()<<Q_FUNC_INFO<<"4 img path:"<<imMsg.body;
    }
}

void ChatControler::handleHistoryFileMsg(Msg &imMsg, std::shared_ptr<service::Msg> msg)
{
    qDebug() << Q_FUNC_INFO;
    std::shared_ptr<service::MsgFile> msgFile = std::dynamic_pointer_cast<service::MsgFile>(msg);

    imMsg.msgid = QString::number(msg->msgid);
    imMsg.msgtype = QString::number(MSG_TYPE_FILE);
    imMsg.fromid = QString::number(msg->fromid);
    imMsg.toid   = QString::number(msg->toid);
    imMsg.targetid = QString::number(msg->targetid);
    imMsg.activeType = QString::number(msg->active_type);
    imMsg.time   =  QDateTime::fromMSecsSinceEpoch(msg->time).toString("yyyy-MM-dd hh:mm:ss");
    imMsg.f_state = QString::number(msgFile->states);
    imMsg.f_id = QString::number(msgFile->fileid);
    imMsg.f_size  = QString::number(msgFile->size);
    imMsg.encrypt_user = QString::number(msgFile->encrypt_user);
    imMsg.encrypt_key = QString::fromStdString(msgFile->encrypt_key);
    imMsg.f_path = QString::fromStdString(msgFile->file_path);
    imMsg.f_url = QString::fromStdString(msgFile->url);
    imMsg.filename = QString::fromStdString(msgFile->file_name);
}

void ChatControler::handleNotification(std::shared_ptr<service::Msg> msg)
{
    qDebug()<<Q_FUNC_INFO;
    QString sessionId("");
    getCurrentSessionId(sessionId);
    qDebug()<<Q_FUNC_INFO<<"seesionId:"<<msg->fromid<<"body:"<<msg->body.c_str();
    if(sessionId != ""){
        return;
    }
    if(!IS_MSG_GROUP(msg->targetid)){
        getUserProfile(QString::number(msg->fromid),msg);
    }else{
         service::IMClient::getClient()->getGroup()->getGroupInfo(msg->targetid,std::bind(&ChatControler::_getGroupInfo,this,std::placeholders::_1,std::placeholders::_2,msg));
    }

}

void ChatControler::_deleteMessage(service::ErrorInfo &info)
{
    qDebug() << Q_FUNC_INFO<<info.code();
    emit deleteMessagesBack(info.code());
}

void ChatControler::_getContactInfo(service::ErrorInfo &info, service::User &user, Msg msg)
{

    qDebug()<<Q_FUNC_INFO<<"11111111";
    service::Contact& contact= service::userCast<service::Contact>(user);

    msg.targetName = msg.name = QString::fromStdString(contact.name);
    msg.thumb_avatar = QString::fromStdString(contact.avatar);
    QDateTime dateTime = QDateTime::fromString(msg.time,"yyyy-MM-dd hh:mm:ss");
    QString time =QString::number(dateTime.toMSecsSinceEpoch());
    QString sessionId("");
    qDebug()<<Q_FUNC_INFO<<"wwwwwwwwwwwwwww:"<<msg.thumb_avatar;
    getCurrentSessionId(sessionId);
    if(sessionId == msg.targetid){
        emit sessionMessageNotice(msg.targetid,msg.msgid,msg.body,time,msg.targetName,msg.thumb_avatar,"0");
    }
    else{
        emit sessionMessageNotice(msg.targetid,msg.msgid,msg.body,time,msg.targetName,msg.thumb_avatar,"1");
    }
}

void ChatControler::_uploadAvatar(std::string orgijson, std::string thumbjson, int code)
{
    qDebug() << Q_FUNC_INFO << "orgijson:" << orgijson.c_str();
    qDebug() << Q_FUNC_INFO << "   thumbjson:" << thumbjson.c_str();
    qDebug() << Q_FUNC_INFO << "   code:" << code;

    emit uploadAvatarBack(QString::fromStdString(orgijson), QString::fromStdString(thumbjson), code);
}

void ChatControler::_uploadFile(int64 tagetid,int64 operId, std::string jasoninfo, int code,Msg fileMsg)
{
    qDebug()<<Q_FUNC_INFO<<"_uploadFile operId:"<<operId;
    fileMsg.f_url = QString::fromStdString(utils::FileUtils::getFile(jasoninfo,"url"));
    sendMessage(fileMsg);
    emit uploadFileBackUrl(fileMsg.targetid,fileMsg.localid,fileMsg.f_url,fileMsg.encrypt_key);
}

void ChatControler::_fileProgress(int32 extra_req, int32 process, std::string info,QString localId,QString targetId)
{
    qDebug()<<Q_FUNC_INFO<< "extra_req:" << extra_req << "   process:" << process  << "  info:" << info.c_str() << "   localId:" << localId << "   targetId:" << targetId;
    emit fileProgressBack(extra_req, process, QString::fromStdString(info),localId,targetId);
}

void ChatControler::_cancelFile(int code)
{
    qDebug()<<Q_FUNC_INFO<<code;
}

void ChatControler::_downloadFile(service::ErrorInfo &info, std::string localpath, int64 tagetid, QString encryFilePath, QString encryKey,QString localId)
{
    qDebug()<<Q_FUNC_INFO;
    if(info.code() == 0)
    {
        QDir tempDir;
        QString path = APP_SAVE_FILE_APTH/*APP_DATA_PATH +LinkDoodService::instance()->UserId() + "/file/encryfile/"*/;
        if (!tempDir.exists(path))
        {
            bool ret = tempDir.mkdir(path);
             qDebug()<<Q_FUNC_INFO <<"makedir:"<<path<<"ret:"<<ret;
        }
        qDebug()<<Q_FUNC_INFO << " localpath:" << localpath.c_str() << "  tagetid:" << tagetid << "  encryFilePath:" << encryFilePath << "  encryKey:" << encryKey;
        if(decryptFile(encryKey, QString::fromStdString(localpath), encryFilePath))
        {
            qDebug() << encryFilePath << " 解密成功!";
        }
    }
    emit downloadFileBack(info.code(), encryFilePath, localId);
}

void ChatControler::_uploadImage(int64 tagetid, std::string orgijson, std::string thumbjson, int code,Msg msg)
{
    qDebug()<<Q_FUNC_INFO<<"msg:"<<msg.thumb_url;
    msg.thumb_url = QString::fromStdString(utils::FileUtils::getFile(thumbjson,"url"));
    msg.main_url  = QString::fromStdString(utils::FileUtils::getFile(orgijson,"url"));
    sendMessage(msg);

    emit uploadImgeBackUrl(msg.targetid,msg.localid,msg.thumb_url,msg.main_url,msg.encrypt_key);
}

void ChatControler::_uploadImageProgess(int32 extra_req, int32 process, std::string info, QString target, QString localId)
{
    qDebug()<<Q_FUNC_INFO<<"progrss:"<<process;
    emit uploadImageProgess(target,localId,process);
}

void ChatControler::_downloadImage(service::ErrorInfo &info, std::string localpath, int64 tagetid,Msg msgImg)
{
    qDebug() << Q_FUNC_INFO<<"code:"<<info.code() <<"  localpath:" << localpath.c_str();
    QString appDataPath =  APP_DATA_PATH +LinkDoodService::instance()->UserId() + "/";
    QString imgPath = QString::fromStdString(localpath);

    if(judgeFileExist(imgPath,MSG_TYPE_IMG)){
        qDebug() << Q_FUNC_INFO<< "if(judgeFileExist(imgPath,MSG_TYPE_IMG)){ end";
        QDir tempDir;
        if (!tempDir.exists(appDataPath))
        {
            tempDir.mkdir(appDataPath);
        }
        QStringList strList = imgPath.split("/");
        qDebug() << Q_FUNC_INFO<< "strList.size = " << strList.size();
        if (strList.size() > 0)
        {
            QString fileName = strList.at(strList.size() - 1);
            QString srcPath = appDataPath +"image/"+ fileName;
            QString outPath = (QString::fromStdString(APP_SAVE_IAMGE_APTH) +"/"+ fileName);
            if (!tempDir.exists(APP_SAVE_IAMGE_APTH))
            {
                tempDir.mkdir(APP_SAVE_IAMGE_APTH);
            }

            bool ret = service::IMClient::getClient()->getFile()->decryptFile(msgImg.encrypt_key.toStdString(),srcPath.toStdString(),outPath.toStdString());
            qDebug()<<Q_FUNC_INFO<<"decryptFile:"<<outPath<<":ret:"<<ret;
            if(ret){
                msgImg.thumb_url = outPath;
                msgImg.body = "[图片]";
                sendSessionMsg(msgImg);
            }
        }
    }
}

void ChatControler::_downloadMainImage(service::ErrorInfo &info, std::string localpath, long long tagetid, QString encryptKey,QString main_url)
{
    qDebug() << Q_FUNC_INFO;
    QString appDataPath =  APP_DATA_PATH +LinkDoodService::instance()->UserId() + "/";
    QString imgPath = QString::fromStdString(localpath);
    if(judgeFileExist(imgPath,MSG_TYPE_IMG)){
        QDir tempDir;
        if (!tempDir.exists(appDataPath))
        {
            tempDir.mkdir(appDataPath);
        }
        QStringList strList = imgPath.split("/");
        qDebug() << Q_FUNC_INFO<< "strList.size = " << strList.size();
        if (strList.size() > 0)
        {
            QString fileName = strList.at(strList.size() - 1);
            QString srcPath = appDataPath +"image/"+ fileName;
            QString outPath = (appDataPath +"cache/"+ fileName);
            bool ret = service::IMClient::getClient()->getFile()->decryptFile(encryptKey.toStdString(),srcPath.toStdString(),outPath.toStdString());
            qDebug()<<Q_FUNC_INFO<<"decryptFile:"<<outPath<<":ret:"<<ret;
            if(ret){
             emit downloadMainImageResult(main_url,outPath);
            }
        }
    }
}

void ChatControler::_downloadHistoryImage(service::ErrorInfo &info, std::string localpath, int64 tid, QString encryptKey, QString targetid, QString localid)
{
    QString appDataPath =  APP_DATA_PATH +LinkDoodService::instance()->UserId() + "/";
    QString imgPath = QString::fromStdString(localpath);

    if(judgeFileExist(imgPath,MSG_TYPE_IMG)){
        QDir tempDir;
        if (!tempDir.exists(appDataPath+"cache/"))
        {
            tempDir.mkdir(appDataPath+"cache/");
        }
        QStringList strList = imgPath.split("/");
        qDebug() << Q_FUNC_INFO<< "strList.size = " << strList.size();
        if (strList.size() > 0)
        {
            QString fileName = strList.at(strList.size() - 1);
            QString srcPath = appDataPath +"image/"+ fileName;
            QString outPath = (appDataPath +"cache/"+ fileName);
            qDebug() << Q_FUNC_INFO << "decryptFile(...) start";
            bool ret = service::IMClient::getClient()->getFile()->decryptFile(encryptKey.toStdString(),srcPath.toStdString(),outPath.toStdString());
            if(ret){
                emit downloadHistoryImageResult(info.code(), outPath, targetid, localid);
            }
        }
    }
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

void ChatControler::_getUserInfo(service::ErrorInfo& info, service::User& user)
{
    qDebug()<<Q_FUNC_INFO << "code:" << info.code() << " name:" << user.name.c_str();
    Contact contact;
    contact.gender = QString::number(user.gender);
    contact.timeZone = user.time_zone;
    contact.id = QString::number(user.id);
    contact.name = QString::fromStdString(user.name);
    contact.avatar = QString::fromStdString(user.avatar);
    contact.extends = QString::fromStdString(user.extends);
    contact.thumbAvatar = QString::fromStdString(user.thumb_avatar);

    emit getUserInfoBack(info.code(), contact);
}

void ChatControler::_getUserProfile(service::ErrorInfo& info, service::User& user, std::shared_ptr<service::Msg> msg)
{
    qDebug()<<Q_FUNC_INFO<<"1111111111111";
    QString senderId, msgType,content,msgId, sendTime, displayName,icon("");
    if(msg->msgtype == MSG_TYPE_FILE){
        content= "[文件]";
    }else if(msg->msgtype == MSG_TYPE_IMG){
        content= "[图片]";
    }else if(msg->msgtype == MSG_TYPE_TEXT){
        std::string target("");
        std::string msgBody = utils::MsgUtils::getText(msg->body);
        if(msgBody == ""){
            msgBody = msg->body;
        }

        EmojiExplain::EmojiParseFrom(msgBody,target);
        content = QString::fromStdString(target);
        qDebug()<<Q_FUNC_INFO<<"22222222222";
    }else if(msg->msgtype == MEDIA_MSG_DYNAMIC_EMOJI){
        QString explian(""),target("");
        std::string msgBody = utils::MsgUtils::getText(msg->body);
        if(msgBody == ""){
            msgBody = msg->body;
        }
        EmojiExplain::dyEmojiParseFrom(QString::fromStdString(msgBody),target,explian);
        content = explian;
    }
    qDebug()<<Q_FUNC_INFO<<"33333333333333";
    senderId = QString::number(msg->fromid);
    msgType  = QString::number(msg->msgtype);
    msgId    = QString::number(msg->msgid);
    sendTime = QString::number(msg->time);

    displayName = QString::fromStdString(user.name);
    qDebug()<<Q_FUNC_INFO<<"555555555555555555555:"<<displayName;
    emit bcNotify(senderId,msgType,content,msgId,sendTime,displayName,icon,"",1);
}

void ChatControler::_getGroupInfo(service::ErrorInfo &info, service::Group group,std::shared_ptr<service::Msg> msg)
{
    qDebug()<<Q_FUNC_INFO;
    QString senderId, msgType,content,msgId, sendTime, displayName,icon("");
    if(msg->msgtype == MSG_TYPE_FILE){
        content= "[文件]";
    }else if(msg->msgtype == MSG_TYPE_IMG){
        content= "[图片]";
    }else if(msg->msgtype == MSG_TYPE_TEXT){
        std::string target("");
        std::string msgBody = utils::MsgUtils::getText(msg->body);
        if(msgBody == ""){
            msgBody = msg->body;
        }

        EmojiExplain::EmojiParseFrom(msgBody,target);
        content = QString::fromStdString(target);
        qDebug()<<Q_FUNC_INFO<<"22222222222";
    }else if(msg->msgtype == MEDIA_MSG_DYNAMIC_EMOJI){
        QString explian(""),target("");
        std::string msgBody = utils::MsgUtils::getText(msg->body);
        if(msgBody == ""){
            msgBody = msg->body;
        }
        EmojiExplain::dyEmojiParseFrom(QString::fromStdString(msgBody),target,explian);
        content = explian;
    }
    qDebug()<<Q_FUNC_INFO<<"33333333333333";
    senderId = QString::number(msg->targetid);
    msgType  = QString::number(msg->msgtype);
    msgId    = QString::number(msg->msgid);
    sendTime = QString::number(msg->time);

    displayName = QString::fromStdString(group.info.name);
    qDebug()<<Q_FUNC_INFO<<"555555555555555555555:"<<displayName;
    emit bcNotify(senderId,msgType,content,msgId,sendTime,displayName,icon,"",1);
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
    if(Qmsgtext.body == ""){
        Qmsgtext.body = QString::fromStdString(msgtext->body);
    }
    qDebug()<<Q_FUNC_INFO<<"msg body:"<<Qmsgtext.body;
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
bool ChatControler::judgeFileExist(QString urlPath, int msgType)
{
    qDebug()<<Q_FUNC_INFO << "urlPath:" << urlPath << "    msgType:" << msgType << "      start";
    bool bIsExist = false;
    QStringList strList = urlPath.split("/");
    QString fileName;
    QFileInfo fileInfo;
    QString filePath;
    QString tempImagePath =  APP_DATA_PATH +LinkDoodService::instance()->UserId();
    qDebug()<<Q_FUNC_INFO << "tempImagePath:" << tempImagePath;
    if (MSG_TYPE_IMG == msgType)
    {
        filePath = tempImagePath+"/image/";
    }
    else if (MSG_TYPE_FILE == msgType)
    {
        filePath = tempImagePath+"/file/";
    }
    if (strList.size() > 0)
    {
        fileName = strList.at(strList.size() - 1);
        filePath = filePath + fileName;
        fileInfo.setFile(filePath);
        if (fileInfo.isFile() && fileInfo.exists())
        {
            bIsExist = true;
        }
    }
    else
    {
        filePath = filePath + urlPath;
        fileInfo.setFile(filePath);
        if (fileInfo.isFile() && fileInfo.exists())
        {
            bIsExist = true;
            qDebug()<<Q_FUNC_INFO << "if (fileInfo.isFile() && fileInfo.exists()) end";
        }
    }
    qDebug()<<Q_FUNC_INFO << "bIsExist:" << bIsExist << " end";

    return bIsExist;
}
