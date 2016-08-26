#include "cdoodcontactitem.h"
#include<QDebug>

CDoodContactItem::CDoodContactItem(QObject *parent) : QObject(parent)
{
    mSection = "";
    mOnlineStatus = "";
}

QString CDoodContactItem::id() const
{
    return mId;
}

QString CDoodContactItem::setId(const QString &data)
{
    if(data != "" && mId != data){
        mId = data;
        emit idChanged();
    }
    return mId;
}

QString CDoodContactItem::name() const
{
    return mName;
}

QString CDoodContactItem::setName(const QString &data)
{
    if(data != "" && mName != data){
        mName = data;
    }
    emit nameChanged();
    return mName;
}

QString CDoodContactItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodContactItem::setThumbAvatar(const QString &data)
{
    if(data != "" && mThumbAvatar != data){
        mThumbAvatar = data;
    }
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

QString CDoodContactItem::sectionKey() const
{
    return mSection;
}

QString CDoodContactItem::setSection(const QString &data)
{
    if(data != "" && mSection != data){
        mSection = data;
        emit sectionChanged();
    }
    return mSection;
}
QString CDoodContactItem::searchKey() const
{
    return mSearchKey;
}

QString CDoodContactItem::setSearchKey(const QString &data)
{
    if(data != "" && mSearchKey != data){
        mSearchKey = data;
        emit searchKeyChanged();
    }
    return mSearchKey;
}

QString CDoodContactItem::onlineStatus() const
{
    return mOnlineStatus;
}

QString CDoodContactItem::setOnlineStatus(const QString &data)
{
    //if(/*data != "" && mOnlineStatus != data*/){
        mOnlineStatus = data;
        emit onlineStatusChanged();
    //}
    return mOnlineStatus;
}

QString CDoodContactItem::extend() const
{
    qDebug() << Q_FUNC_INFO;
    return mExtend;
}

QString CDoodContactItem::setExtend(const QString &data)
{
    if(data != "" && mExtend != data){
        mExtend = data;
        emit extendChanged();
    }
    return mExtend;
}

QString CDoodContactItem::userOrGroup() const
{
    return mUserOrGroup;
}

QString CDoodContactItem::setUserOrGroup(const QString &data)
{
    if(mUserOrGroup == data)
        return data;
    mUserOrGroup = data;
    emit userOrGroupChanged();
    qDebug() << Q_FUNC_INFO;
    return mUserOrGroup;
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

QString CDoodContactItem::isChoose() const
{
    return mIsChoose;
}

QString CDoodContactItem::setIsChoose(const QString &data)
{
    if(mIsChoose==data){
        return data;
    }
    mIsChoose=data;
    emit isChooseChanged();
    return mIsChoose;
}

QString CDoodContactItem::clearIsChoose(const QString &data)
{
    mIsChoose=data;
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
    if(data != "" && mIsStar != data){
        mIsStar = data;
        emit isStarChanged();
    }
    return mIsStar;
}

QString CDoodContactItem::isVip() const
{
    return mIsVip;
}

QString CDoodContactItem::setIsVip(const QString &data)
{
    if(data != "" && mIsVip != data){
        mIsVip = data;
        emit isVipChanged();
    }
    return mIsVip;
}

QString CDoodContactItem::pinYin() const
{
    return mPinYin;
}

QString CDoodContactItem::setPinYin(const QString &data)
{
    if(data != "" && mPinYin != data){
        mPinYin = data;
        emit pinYinChanged();
    }
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


