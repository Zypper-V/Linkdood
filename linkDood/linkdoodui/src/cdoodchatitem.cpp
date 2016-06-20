#include "cdoodchatitem.h"

CDoodChatItem::CDoodChatItem(QObject *parent) : QObject(parent)
{

}

QString CDoodChatItem::msgType() const
{
    return mMsgYype;
}

QString CDoodChatItem::setMsgType(const QString &data)
{
    if(mMsgYype == data) {
        return data;
    }
    mMsgYype = data;
    emit msgTypeChanged();
    return mMsgYype;
}

QString CDoodChatItem::activeType() const
{
    return mActiveType;
}

QString CDoodChatItem::setActiveType(const QString &data)
{
    if(mActiveType == data) {
        return data;
    }
    mActiveType = data;
    emit activeTypeChanged();
    return mActiveType;
}

QString CDoodChatItem::msgId() const
{
    return mMsgId;
}

QString CDoodChatItem::setMsgId(const QString &data)
{
    if(mMsgId == data) {
        return data;
    }
    mMsgId = data;
    emit msgIdChanged();
    return mMsgId;
}

QString CDoodChatItem::targetId() const
{
    return mTargetId;
}

QString CDoodChatItem::setTargetId(const QString &data)
{
    if(mTargetId == data) {
        return data;
    }
    mTargetId = data;
    emit targetIdChanged();
    return mTargetId;
}

QString CDoodChatItem::fromId() const
{
    return mFromId;
}

QString CDoodChatItem::setFromId(const QString &data)
{
    if(mFromId == data) {
        return data;
    }
    mFromId = data;
    emit fromIdChanged();
    return mFromId;
}

QString CDoodChatItem::toId() const
{
    return mToId;
}

QString CDoodChatItem::setToId(const QString &data)
{
    if(mToId == data) {
        return data;
    }
    mToId = data;
    emit toIdChanged();
    return mToId;
}

QString CDoodChatItem::localId() const
{
    return mLocalId;
}

QString CDoodChatItem::setLocalId(const QString &data)
{
    if(mLocalId == data) {
        return data;
    }
    mLocalId = data;
    emit localIdChanged();
    return mLocalId;
}

QString CDoodChatItem::relatedMsgId() const
{
    return mRelatedMsgId;
}

QString CDoodChatItem::setRelatedMsgId(const QString &data)
{
    if(mRelatedMsgId == data) {
        return data;
    }
    mRelatedMsgId = data;
    emit relatedMsgIdChanged();
    return mRelatedMsgId;
}

QString CDoodChatItem::time() const
{
    return mTime;
}

QString CDoodChatItem::setTime(const QString &data)
{
    if(mTime == data) {
        return data;
    }
    mTime = data;
    emit timeChanged();
    return mTime;
}

QString CDoodChatItem::body() const
{
    return mBody;
}

QString CDoodChatItem::setBody(const QString &data)
{
    if(mBody == data) {
        return data;
    }
    mBody = data;
    emit bodyChanged();
    return mBody;
}

QString CDoodChatItem::sgProperties() const
{
    return msgProperties;
}

QString CDoodChatItem::setSgProperties(const QString &data)
{
    if(msgProperties == data) {
        return data;
    }
    msgProperties = data;
    emit sgPropertiesChanged();
    return msgProperties;
}

