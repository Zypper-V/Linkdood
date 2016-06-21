#include "linkdoodtypes.h"


Msg::Msg()
{
    init();
}

void Msg::toImMassage(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {
        if (iter.key() == "name") {
            name = iter.value().toString();
        }
        if (iter.key() == "thumb_avatar") {
            thumb_avatar = iter.value().toString();
        }
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
        if (iter.key() == "msgProperties") {
            msgProperties = iter.value().toString();
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
    argument << msg.name << msg.thumb_avatar << msg.msgtype << msg.activeType
             << msg.msgid << msg.targetid << msg.fromid << msg.toid
             << msg.localid << msg.relatedMsgid << msg.time << msg.body << msg.msgProperties;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, Msg &msg)
{
    argument.beginStructure();
    argument >> msg.name >> msg.thumb_avatar >> msg.msgtype >> msg.activeType
             >> msg.msgid >> msg.targetid >> msg.fromid >> msg.toid
             >> msg.localid >> msg.relatedMsgid >> msg.time >> msg.body >> msg.msgProperties;
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
    argument << offlineMsg.count << offlineMsg.offlineType << offlineMsg.body
             << offlineMsg.fromId << offlineMsg.msgId << offlineMsg.targetId << offlineMsg.time;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, IMOfflineMsg &offlineMsg)
{
    argument.beginStructure();
    argument >> offlineMsg.count >> offlineMsg.offlineType >> offlineMsg.body
            >> offlineMsg.fromId >> offlineMsg.msgId >> offlineMsg.targetId >> offlineMsg.time;
    argument.endStructure();
    return argument;
}
////////////////////////Org////////////////////////////////////////
Org::Org()
{
    init();
}

void Org::toImOrg(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {

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
        if(iter.key() == "level"){
            this->level = iter.value().toString();
        }
        if(iter.key() == "sonorg_count"){
            this->sonorg_count = iter.value().toString();
        }
        if(iter.key() == "leaf"){
            this->leaf = iter.value().toString();
        }
        if(iter.key() == "ishidden"){
            this->ishidden = iter.value().toString();
        }
        if(iter.key() == "sonuser_count"){
            this->sonuser_count = iter.value().toString();
        }
        if(iter.key() == "parent_id"){
            this->parent_id = iter.value().toString();
        }
        if(iter.key() == "ent_id"){
            this->ent_id = iter.value().toString();
        }
        if(iter.key() == "order_num"){
            this->order_num = iter.value().toString();
        }
        if(iter.key() == "branch_id"){
            this->branch_id = iter.value().toString();
        }
        if(iter.key() == "org_code"){
            this->org_code = iter.value().toString();
        }
    }
}

void Org::init()
{
    this->id = "";
    this->avatar  = "";
    this->extends = "";
    this->branch_id= "";
    this->ent_id= "";

    this->ishidden = "";
    this->leaf = "";
    this->level= "";
    this->name= "";
    this->order_num= "";
    this->org_code = "";
    this->parent_id= "";
    this->sonorg_count= "";
    this->sonuser_count = "";
    this->thumbAvatar= "";
}

QDBusArgument &operator << (QDBusArgument &argument, const Org &org)
{
    argument.beginStructure();
    argument << org.avatar << org.branch_id
             << org.ent_id << org.extends<< org.id
             << org.ishidden <<  org.leaf<< org.level
             << org.name << org.order_num << org.org_code
             << org.parent_id << org.sonorg_count
             << org.sonuser_count<<org.thumbAvatar;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >> (const QDBusArgument &argument, Org &org)
{
    argument.beginStructure();
    argument >> org.avatar >> org.branch_id
             >> org.ent_id >> org.extends>> org.id
             >> org.ishidden >>  org.leaf>> org.level
             >> org.name >> org.order_num >> org.org_code
             >> org.parent_id >> org.sonorg_count
             >> org.sonuser_count>>org.thumbAvatar;
    argument.endStructure();
    return argument;
}
////////////////////////OrgUser////////////////////////////////////////
OrgUser::OrgUser()
{
    init();
}

void OrgUser::toImOrgUser(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {

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
        if(iter.key() == "gender"){
            this->gender = iter.value().toString();
        }
        if(iter.key() == "timeZone"){
            this->timeZone = iter.value().toString();
        }


        if(iter.key() == "order_num"){
            this->order_num = iter.value().toString();
        }
        if(iter.key() == "ent_id"){
            this->ent_id = iter.value().toString();
        }
        if(iter.key() == "org_id"){
            this->org_id = iter.value().toString();
        }
        if(iter.key() == "role_id"){
            this->role_id = iter.value().toString();
        }
        if(iter.key() == "neworg_id"){
            this->neworg_id = iter.value().toString();
        }
        if(iter.key() == "duty"){
            this->duty = iter.value().toString();
        }
        if(iter.key() == "email"){
            this->email = iter.value().toString();
        }
        if(iter.key() == "phone"){
            this->phone = iter.value().toString();
        }
        if(iter.key() == "orgname"){
            this->orgname = iter.value().toString();
        }
        if(iter.key() == "pinyin"){
            this->pinyin = iter.value().toString();
        }
    }
}

void OrgUser::init()
{
    this->avatar = "";
    this->duty  = "";
    this->email = "";
    this->ent_id= "";
    this->extends= "";

    this->gender = "";
    this->id = "";
    this->name= "";
    this->neworg_id= "";
    this->order_num= "";
    this->orgname = "";
    this->org_id= "";
    this->phone= "";
    this->pinyin = "";
    this->role_id= "";
    this->thumbAvatar= "";
    this->timeZone="";
}

QDBusArgument &operator << (QDBusArgument &argument, const OrgUser &orguser)
{
    argument.beginStructure();
    argument << orguser.avatar << orguser.duty
             << orguser.email << orguser.ent_id<< orguser.extends
             << orguser.gender <<  orguser.id<< orguser.name
             << orguser.neworg_id << orguser.order_num << orguser.orgname
             << orguser.org_id << orguser.phone<<orguser.thumbAvatar
             << orguser.pinyin<<orguser.role_id<<orguser.timeZone;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >> (const QDBusArgument &argument, OrgUser &orguser)
{
    argument.beginStructure();
    argument >> orguser.avatar >> orguser.duty
             >> orguser.email >> orguser.ent_id>> orguser.extends
             >> orguser.gender >>  orguser.id>> orguser.name
             >> orguser.neworg_id >> orguser.order_num >> orguser.orgname
             >> orguser.org_id >> orguser.phone>>orguser.thumbAvatar
             >> orguser.pinyin>>orguser.role_id>>orguser.timeZone;
    argument.endStructure();
    return argument;
}

////////////////////////QOnlineState////////////////////////////////////////
QOnlineState::QOnlineState()
{
    init();
}

void QOnlineState::toImQOnlineState(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {

        if(iter.key() == "userid"){
            this->userid = iter.value().toString();
        }
        if(iter.key() == "connectId"){
            this->connectId = iter.value().toString();
        }
        if(iter.key() == "deviceType"){
            this->deviceType = iter.value().toString();
        }
        if(iter.key() == "flag"){
            this->flag = iter.value().toString();
        }
    }
}

void QOnlineState::init()
{
    this->userid = "";
    this->connectId  = "";
    this->deviceType = "";
    this->flag= "";
}

QDBusArgument &operator << (QDBusArgument &argument, const QOnlineState &onlinestate)
{
    argument.beginStructure();
    argument << onlinestate.connectId << onlinestate.deviceType
             << onlinestate.flag << onlinestate.userid;

    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >> (const QDBusArgument &argument, QOnlineState &onlinestate)
{
    argument.beginStructure();
    argument >> onlinestate.connectId >> onlinestate.deviceType
             >> onlinestate.flag >> onlinestate.userid;
    argument.endStructure();
    return argument;
}
////////////////////////////LoginInfo/////////////////////////////////////
LoginInfo::LoginInfo()
{
    this->account ="";
    this->areaNum = "";
    this->isAutoLogin = 0;
    this->isRemberPass = 0;
    this->lastLoginTime = 0;
    this->name = "";
    this->server = "";
    this->status = 0;
    this->userIcon = "";
    this->userId = 0;
}

void LoginInfo::toImLoginInfo(QVariantMap map)
{
    QVariantMap::const_iterator iter;
    for (iter = map.constBegin(); iter != map.constEnd(); ++iter) {
        if(iter.key() == "account"){
            this->account = iter.value().toString();
        }
        if(iter.key() == "areaNum"){
            this->areaNum = iter.value().toString();
        }
        if(iter.key() == "isAutoLogin"){
            this->isAutoLogin = iter.value().toLongLong();
        }
        if(iter.key() == "isRemberPass"){
            this->isRemberPass = iter.value().toLongLong();
        }
        if(iter.key() == "lastLoginTime"){
            this->lastLoginTime = iter.value().toLongLong();
        }
        if(iter.key() == "name"){
            this->name = iter.value().toString();
        }
        if(iter.key() == "server"){
            this->server = iter.value().toString();
        }
        if(iter.key() == "status"){
            this->status = iter.value().toLongLong();
        }
        if(iter.key() == "userIcon"){
            this->userIcon = iter.value().toString();
        }
        if(iter.key() == "userId"){
            this->userId = iter.value().toLongLong();
        }

    }
}
QDBusArgument &operator << (QDBusArgument &argument, const LoginInfo &info)
{
    argument.beginStructure();

    argument << info.account << info.areaNum << info.isAutoLogin
            << info.isRemberPass << info.lastLoginTime << info.name
            << info.server << info.status << info.userIcon;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >> (const QDBusArgument &argument, LoginInfo &info)
{
    argument.beginStructure();
    argument >> info.account >> info.areaNum >> info.isAutoLogin
            >> info.isRemberPass >> info.lastLoginTime >> info.name
            >> info.server >> info.status >> info.userIcon;
    argument.endStructure();
    return argument;
}
