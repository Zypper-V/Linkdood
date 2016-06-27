#include "cdoodcontactitem.h"
#include<QDebug>

CDoodContactItem::CDoodContactItem(QObject *parent) : QObject(parent)
{

}

QString CDoodContactItem::id() const
{
    return mId;
}

QString CDoodContactItem::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodContactItem::name() const
{
    return mName;
}

QString CDoodContactItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodContactItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodContactItem::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

bool CDoodContactItem::isOrg() const
{
    return mIsOrg;
}

bool CDoodContactItem::setIsOrg(bool isOrg)
{
    if(mIsOrg == isOrg) {
        return isOrg;
    }
    mIsOrg = isOrg;
    emit isOrgChanged();
    return mIsOrg;
}

QString CDoodContactItem::gender() const
{
    return mGender;
}

QString CDoodContactItem::setGender(const QString &data)
{

    if(mGender == data) {
        return data;
    }
    mGender = data;
    emit genderChanged();
    return mGender;
}

QString CDoodContactItem::timeZone() const
{
    return mTimeZone;
}

QString CDoodContactItem::setTimeZone(const QString &data)
{
    if(mTimeZone == data) {
        return data;
    }
    mTimeZone = data;
    emit timeZoneChanged();
    return mTimeZone;
}

QString CDoodContactItem::avatar() const
{
    return mAvatar;
}

QString CDoodContactItem::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}

QString CDoodContactItem::isStar() const
{
    return mIsStar;
}

QString CDoodContactItem::setIsStar(const QString &data)
{
    if(mIsStar == data) {
        return data;
    }
    mIsStar = data;
    emit isStarChanged();
    return mIsStar;
}

QString CDoodContactItem::isVip() const
{
    return mIsVip;
}

QString CDoodContactItem::setIsVip(const QString &data)
{
    if(mIsVip == data) {
        return data;
    }
    mIsVip = data;
    emit isVipChanged();
    return mIsVip;
}

QString CDoodContactItem::pinYin() const
{
    return mPinYin;
}

QString CDoodContactItem::setPinYin(const QString &data)
{
    if(mPinYin == data) {
        return data;
    }
    mPinYin = data;
    emit pinYinChanged();
    return mPinYin;
}

QString CDoodContactItem::remark() const
{
    return mRemark;
}

QString CDoodContactItem::setRemark(const QString &data)
{
    if(mRemark == data) {
        return data;
    }
    mRemark = data;
    emit remarkChanged();
    return mRemark;
}

QString CDoodContactItem::server() const
{
    return mServer;
}

QString CDoodContactItem::setServer(const QString &data)
{
    if(mServer == data) {
        return data;
    }
    mServer = data;
    emit serverChanged();
    return mServer;
}

