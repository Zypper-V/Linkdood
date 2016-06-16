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
            msgtype = iter.value().toInt();
        }
        if (iter.key() == "active_type") {
            active_type = iter.value().toInt();
        }
        if (iter.key() == "msgid") {
            msgid = iter.value().toLongLong();
        }
        if (iter.key() == "targetid") {
            targetid = iter.value().toLongLong();
        }
        if (iter.key() == "fromid") {
            fromid = iter.value().toLongLong();
        }
        if (iter.key() == "toid") {
            toid = iter.value().toLongLong();
        }
        if (iter.key() == "localid") {
            localid = iter.value().toLongLong();
        }
        if (iter.key() == "related_msgid") {
            related_msgid = iter.value().toLongLong();
        }
        if (iter.key() == "time") {
            time = iter.value().toLongLong();
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
             << msg.related_msgid << msg.time ;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator >>(const QDBusArgument &argument, Msg &msg)
{
    argument.beginStructure();
    argument >> msg.fromid >> msg.toid >> msg.msgid
            >> msg.msgtype >> msg.body >> msg.localid
            >> msg.related_msgid >> msg.time ;
    argument.endStructure();
    return argument;
}


inline void registerImServiceDataTypes() {
    qDBusRegisterMetaType<Msg>();
    qDBusRegisterMetaType<MsgList>();
    qRegisterMetaType<MsgList>("MsgList");

}

