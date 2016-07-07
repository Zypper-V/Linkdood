#include "cdoodchatitem.h"

CDoodChatItem::CDoodChatItem(QObject *parent) : QObject(parent)
{
    mLoading = false;
    mSatus = true;
    mTextMsg = "";
}

bool CDoodChatItem::loading() const
{
    return mLoading;
}

bool CDoodChatItem::setLoading(const bool &data)
{
    if(mLoading == data) {
        return data;
    }
    mLoading = data;
    emit loadingChanged();
    return mLoading;
}

bool CDoodChatItem::status() const
{
    return mSatus;
}

bool CDoodChatItem::setStatus(const bool &data)
{
    if(mSatus == data) {
        return data;
    }
    mSatus = data;
    emit statusChanged();
    return mSatus;
}

QString CDoodChatItem::name() const
{
    return mName;
}

QString CDoodChatItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodChatItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodChatItem::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}


QString CDoodChatItem::tar_thumbAvatar() const
{
    return mTar_thumbAvatar;
}

QString CDoodChatItem::setTar_thumbAvatar(const QString &data)
{
    if(mTar_thumbAvatar == data) {
        return data;
    }
    mTar_thumbAvatar = data;
    emit tar_thumbAvatarChanged();
    return mTar_thumbAvatar;
}

QString CDoodChatItem::msgType() const
{
    return mMsgType;
}

QString CDoodChatItem::setMsgType(const QString &data)
{
    if(mMsgType == data) {
        return data;
    }
    mMsgType = data;
    emit msgTypeChanged();
    return mMsgType;
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

QDateTime CDoodChatItem::time() const
{
    return mTime;
}

QDateTime CDoodChatItem::setTime(const QDateTime &data)
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

QString CDoodChatItem::textMsgContent()
{
    return mTextMsg;
}

void CDoodChatItem::setTextMsgContent(QString &data)
{
    mTextMsg = data;
}



