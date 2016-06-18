#include "linkdoodtypes.h"


Msg::Msg()
{
    init();
}

void Msg::toImMassage(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {
        if (iter.key() == "msgtype") {
            msgtype = iter.value().toString();
        }
        if (iter.key() == "activeType") {
            activeType = iter.value().toString();
        }
        if (iter.key() == "msgid") {
            msgid = iter.value().toString();
        }
        if (iter.key() == "targetid") {
            targetid = iter.value().toString();
        }
        if (iter.key() == "fromid") {
            fromid = iter.value().toString();
        }
        if (iter.key() == "toid") {
            toid = iter.value().toString();
        }
        if (iter.key() == "localid") {
            localid = iter.value().toString();
        }
        if (iter.key() == "relatedMsgid") {
            relatedMsgid = iter.value().toString();
        }
        if (iter.key() == "time") {
            time = iter.value().toString();
        }
        if (iter.key() == "body") {
            body = iter.value().toString();
        }
        if (iter.key() == "related_users") {
            // related_users.clear();
            // related_users.append(iter.value());
        }
        if (iter.key() == "limit_range") {
            // limit_range.clear();
            // limit_range.append(iter.value());
        }
    }
}

void Msg::init()
{
    body = QString();// 消息内容
}

QDBusArgument &operator <<(QDBusArgument &argument, const Msg &msg)
{
    argument.beginStructure();
    argument << msg.fromid << msg.toid << msg.msgid
             << msg.msgtype << msg.body << msg.localid
             << msg.relatedMsgid << msg.time ;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, Msg &msg)
{
    argument.beginStructure();
    argument >> msg.fromid >> msg.toid >> msg.msgid
            >> msg.msgtype >> msg.body >> msg.localid
            >> msg.relatedMsgid >> msg.time ;
    argument.endStructure();
    return argument;
}

///////////////////////////////MsgText///////////////////////////////
void MsgText::init()
{
    Msg::init();
    msgProperties = QString();// 消息内容
}

MsgText::MsgText()
{
    init();
}

void MsgText::toImMassage(QVariantMap map)
{
    Msg::toImMassage(map);
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {
        if("msg_properties" == iter.key()){
            msgProperties = iter.value().toString();
        }
    }
}

QDBusArgument &operator <<(QDBusArgument &argument, const MsgText &msg)
{
    argument.beginStructure();
    argument << msg.fromid << msg.toid << msg.msgid
             << msg.msgtype << msg.body << msg.localid
             << msg.relatedMsgid << msg.time
             << msg.msgProperties;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, MsgText &msg)
{
    argument.beginStructure();
    argument >> msg.fromid >> msg.toid >> msg.msgid
            >> msg.msgtype >> msg.body >> msg.localid
            >> msg.relatedMsgid >> msg.time >> msg.msgProperties ;
    argument.endStructure();
    return argument;
}

///////////////////////////////Chat_UI///////////////////////////////////
void Chat_UI::init(){

}
Chat_UI::Chat_UI()
{
    init();
}
void Chat_UI::toImChat(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {
        if(iter.key() == "msg_type"){
            msg_type = iter.value().toInt();
        }
        if(iter.key() == "chat_type"){
            chat_type = iter.value().toInt();
        }
        if(iter.key() == "oper_type"){
            oper_type = iter.value().toInt();
        }
        if(iter.key() == "unread_count"){
            unread_count = iter.value().toInt();
        }
        if(iter.key() == "last_msgid"){
            last_msgid = iter.value().toInt();
        }
        if(iter.key() == "msg_time"){
            msg_time = iter.value().toString();
        }
        if(iter.key() == "last_msg"){
            last_msg = iter.value().toString();
        }

        if(iter.key() == "name"){
            name = iter.value().toString();
        }

        if(iter.key() == "avatar"){
            avatar = iter.value().toString();
        }

        if(iter.key() == "extends"){
            extends = iter.value().toString();
        }

        if(iter.key() == "thumb_avatar"){
            thumb_avatar = iter.value().toString();
        }

        if(iter.key() == "gender"){
            gender = iter.value().toInt();
        }

        if(iter.key() == "time_zone"){
            time_zone = iter.value().toInt();
        }

        if(iter.key() == "id"){
            id = iter.value().toString();
        }

    }
}

QDBusArgument &operator <<(QDBusArgument &argument, const Chat_UI &chat)
{
    argument.beginStructure();
    argument << chat.msg_type << chat.last_msg << chat.last_msgid
             << chat.msg_time << chat.oper_type << chat.sub_type
             << chat.unread_count << chat.chat_type << chat.avatar
             << chat.extends <<chat.gender << chat.id << chat.name << chat.thumb_avatar
             << chat.time_zone;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, Chat_UI &chat)
{
    argument.beginStructure();
    argument >> chat.msg_type >> chat.last_msg >> chat.last_msgid
             >> chat.msg_time >> chat.oper_type >> chat.sub_type
             >> chat.unread_count >> chat.chat_type>> chat.avatar
             >> chat.extends >>chat.gender >> chat.id >> chat.name >> chat.thumb_avatar
             >> chat.time_zone;
    argument.endStructure();
    return argument;
}

////////////////////////Contact////////////////////////////////////////
Contact::Contact()
{
    init();
}

void Contact::toImContact(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {

        if(iter.key() == "timeZone"){
            this->timeZone = iter.value().toInt();
        }
        if(iter.key() == "gender"){
            this->gender = iter.value().toString();
        }
        if(iter.key() == "isStar"){
            this->isStar = iter.value().toInt();
        }
        if(iter.key() == "isVip"){
            this->isVip = iter.value().toInt();
        }
        if(iter.key() == "id"){
            this->id = iter.value().toString();
        }
        if(iter.key() == "name"){
            this->name = iter.value().toString();
        }
        if(iter.key() == "avatar"){
            this->avatar = iter.value().toString();
        }
        if(iter.key() == "extends"){
            this->extends = iter.value().toString();
        }
        if(iter.key() == "thumbAvatar"){
            this->thumbAvatar = iter.value().toString();
        }

        if(iter.key() == "pinyin"){
            this->pinyin = iter.value().toString();
        }

        if(iter.key() == "remark"){
            this->remark = iter.value().toString();
        }

        if(iter.key() == "server"){
            this->server = iter.value().toString();
        }
    }
}

void Contact::init()
{
    this->isStar = 2;
    this->isVip  = 2;
    this->pinyin = "";
    this->remark = "";
    this->server = "";

    this->avatar = "";
    this->extends = "";
    this->gender = "";
    this->id = "";
    this->name = "";
    this->thumbAvatar = "";
    this->timeZone = 0;
}

QDBusArgument &operator << (QDBusArgument &argument, const Contact &contact)
{
    argument.beginStructure();
    argument << contact.avatar << contact.extends
             << contact.gender << contact.id << contact.isStar
             << contact.isVip <<  contact.name << contact.name
             << contact.pinyin << contact.remark << contact.server
             << contact.thumbAvatar << contact.timeZone;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >> (const QDBusArgument &argument, Contact &contact)
{
    argument.beginStructure();
    argument >> contact.avatar >> contact.extends
             >> contact.gender >> contact.id >> contact.isStar
             >> contact.isVip >>  contact.name >> contact.name
             >> contact.pinyin >> contact.remark >> contact.server
             >> contact.thumbAvatar >> contact.timeZone;
    argument.endStructure();
    return argument;
}

///////////////////////IMOfflineMsg/////////////////////////////////////////
IMOfflineMsg::IMOfflineMsg()
{
    init();
}

void IMOfflineMsg::init()
{
    this->offlineType = 0;
    this->count = 0;
//    this->msg = 0;
}

QDBusArgument &operator <<(QDBusArgument &argument, const IMOfflineMsg &offlineMsg)
{
    argument.beginStructure();
    argument << offlineMsg.count << offlineMsg.offlineType << offlineMsg.msg;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, IMOfflineMsg &offlineMsg)
{
    argument.beginStructure();
    argument >> offlineMsg.count >> offlineMsg.offlineType >> offlineMsg.msg;
    argument.endStructure();
    return argument;
}

