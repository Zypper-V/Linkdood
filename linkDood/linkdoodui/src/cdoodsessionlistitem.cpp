#include "cdoodsessionlistitem.h"
#include "common.h"

CDoodSessionListItem::CDoodSessionListItem(QObject *parent) : QObject(parent)
{
    mUnReadCount = "0";
    mUnreadMsgCount = 0;
    mdraft = "";
}

void CDoodSessionListItem::setUnreadMsgCOunt(int count)
{
    mUnreadMsgCount = count;
}

int CDoodSessionListItem::unReadMsgCount()
{
    return mUnreadMsgCount;
}

qint64 CDoodSessionListItem::dateTime()
{
    return mMsgTime.toLongLong();
}

QString CDoodSessionListItem::id() const
{
    return mId;
}

QString CDoodSessionListItem::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

void CDoodSessionListItem::setDraft(QString data)
{
    mdraft = data;
    emit draftChanged();
}

QString CDoodSessionListItem::draft()
{
    return mdraft;
}

QString CDoodSessionListItem::name() const
{
    if(mName ==""){
        return mId;
    }
    return mName;
}

QString CDoodSessionListItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodSessionListItem::msgType() const
{
    return mMsgType;
}

QString CDoodSessionListItem::setMsgType(const QString &data)
{
    if(mMsgType == data) {
        return data;
    }
    mMsgType = data;
    emit msgTypeChanged();
    return mMsgType;
}

QString CDoodSessionListItem::chatType() const
{
    return mChatType;
}

QString CDoodSessionListItem::setChatType(const QString &data)
{
    if(mChatType == data) {
        return data;
    }
    mChatType = data;
    emit chatTypeChanged();
    return mChatType;
}

QString CDoodSessionListItem::operType() const
{
    return mOperType;
}

QString CDoodSessionListItem::setOperType(const QString &data)
{
    if(mOperType == data) {
        return data;
    }
    mOperType = data;
    emit operTypeChanged();
    return mOperType;
}

QString CDoodSessionListItem::subType() const
{
    return mSubType;
}

QString CDoodSessionListItem::setSubType(const QString &data)
{
    if(mSubType == data) {
        return data;
    }
    mSubType = data;
    emit subTypeChanged();
    return mSubType;
}

QString CDoodSessionListItem::unReadCount() const
{
    return mUnReadCount;
}

QString CDoodSessionListItem::setUnReadCount(const QString &data)
{
    if(mUnReadCount == data) {
        return data;
    }
    mUnReadCount = data;
    emit unReadCountChanged();
    return mUnReadCount;
}

QString CDoodSessionListItem::lastMsgid() const
{
    return mLastMsgid;
}

QString CDoodSessionListItem::setLastMsgid(const QString &data)
{
    if(mLastMsgid == data) {
        return data;
    }
    mLastMsgid = data;
    emit lastMsgidChanged();
    return mLastMsgid;
}

QString CDoodSessionListItem::msgTime() const
{
    QString tmp = Common::dealTime(mMsgTime.toLongLong(),1);
    return tmp;
}

QString CDoodSessionListItem::setMsgTime(const QString &data)
{
    if(mMsgTime == data) {
        return data;
    }
    mMsgTime = data;
    emit msgTimeChanged();
    return mMsgTime;
}

QString CDoodSessionListItem::lastMsg() const
{
    return mLastMsg;
}

QString CDoodSessionListItem::setLastMsg(const QString &data)
{
    setDraft("");
    if(mLastMsg == data) {
        return data;
    }
    mLastMsg = data;
    emit lastMsgChanged();
    return mLastMsg;
}

QString CDoodSessionListItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodSessionListItem::setThumbAvatar(const QString &data)
{
    if(data != "") {
        mThumbAvatar = data;
        emit thumbAvatarChanged();
    }
    return mThumbAvatar;
}

