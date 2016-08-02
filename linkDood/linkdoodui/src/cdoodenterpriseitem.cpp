#include "cdoodenterpriseitem.h"

CDoodEnterPriseItem::CDoodEnterPriseItem(QObject *parent) : QObject(parent)
{

}
QString CDoodEnterPriseItem::id() const
{
    return mId;
}

QString CDoodEnterPriseItem::setId(const QString &data)
{
    if(data != "" && mId != data){
        mId = data;
        emit idChanged();
    }
    return mId;
}

QString CDoodEnterPriseItem::name() const
{
    return mName;
}

QString CDoodEnterPriseItem::setName(const QString &data)
{
    if(data != "" && mName != data){
        mName = data;
    }
    emit nameChanged();
    return mName;
}

QString CDoodEnterPriseItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodEnterPriseItem::setThumbAvatar(const QString &data)
{
    if(data != "" && mThumbAvatar != data){
        mThumbAvatar = data;
    }
    emit thumbAvatarChanged();
    return mThumbAvatar;
}
QString CDoodEnterPriseItem::onlineStatus() const
{
    return mOnlineStatus;
}

QString CDoodEnterPriseItem::setOnlineStatus(const QString &data)
{
    if(data != "" && mOnlineStatus != data){
        mOnlineStatus = data;
        emit onlineStatusChanged();
    }
    return mOnlineStatus;
}
QString CDoodEnterPriseItem::gender() const
{
    return mGender;
}

QString CDoodEnterPriseItem::setGender(const QString &data)
{

    if(mGender == data) {
        return data;
    }
    mGender = data;
    emit genderChanged();
    return mGender;
}

QString CDoodEnterPriseItem::avatar() const
{
    return mAvatar;
}

QString CDoodEnterPriseItem::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}

QString CDoodEnterPriseItem::remark() const
{
    return mRemark;
}

QString CDoodEnterPriseItem::setRemark(const QString &data)
{
    if(mRemark == data) {
        return data;
    }
    mRemark = data;
    emit remarkChanged();
    return mRemark;
}

QString CDoodEnterPriseItem::order_num() const
{
    return mOrder_num;
}

QString CDoodEnterPriseItem::setOrder_num(const QString &data)
{
    if(mOrder_num==data){
        data;
    }
    mOrder_num=data;
    emit order_numChanged();
    return mOrder_num;
}



