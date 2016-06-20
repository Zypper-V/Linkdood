#include "cdooduserdatamanage.h"
#include<QDebug>

CDoodUserDataManage::CDoodUserDataManage(QObject *parent) : QObject(parent)
{

}

QString CDoodUserDataManage::id() const
{
    return mId;
}

QString CDoodUserDataManage::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodUserDataManage::name() const
{
    return mName;
}

QString CDoodUserDataManage::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodUserDataManage::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodUserDataManage::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

QString CDoodUserDataManage::gender() const
{
    return mGender;
}

QString CDoodUserDataManage::setGender(const QString &data)
{
    qDebug() << Q_FUNC_INFO <<"xingbiexingbiexingbie"<<data;
//    if(mGender == data) {
//        emit genderChanged();
//        return data;
//    }
    mGender = data;
    emit genderChanged();
    return mGender;
}


QString CDoodUserDataManage::avatar() const
{
    return mAvatar;
}

QString CDoodUserDataManage::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}

