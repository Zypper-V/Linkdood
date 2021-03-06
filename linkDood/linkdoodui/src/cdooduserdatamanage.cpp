#include "cdooduserdatamanage.h"
#include<QDebug>
#include "linkdoodclient.h"

CDoodUserDataManage::CDoodUserDataManage(LinkDoodClient *client,QObject *parent) : QObject(parent),m_pClient(client)
{
    initConnect();
    mPhone = "";
}

void CDoodUserDataManage::clearData()
{
    setButtonType("");
    setGroupid("");
    setMemberType("");
    setId("");
    setAvatar("");
    setGender("");
    setName("");
    setRemark("");
    setThumbAvatar("");
    setPhone("");
    setIsFriend(false);
}

void CDoodUserDataManage::setRemark(QString remark)
{
    mRemark = remark;
    emit remarkChanged();
}

QString CDoodUserDataManage::remark()
{
    return mRemark;
}

QString CDoodUserDataManage::phone()
{
    return mPhone;
}

void CDoodUserDataManage::setPhone(QString phone)
{
    mPhone = phone;
    emit phoneChanged();
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

bool CDoodUserDataManage::isFriend() const
{
    return mIsFriend;
}

bool CDoodUserDataManage::setIsFriend(const bool &data)
{
    if(mIsFriend == data){
        return data;
    }
    mIsFriend = data;
    emit isFriendChanged();
    return mIsFriend;
}

void CDoodUserDataManage::onGetContactInfoResult(Contact contact)
{
    qDebug()<<Q_FUNC_INFO<<"contact.name:"<<contact.name<<"contact.remark:"<<contact.remark;
    setName(contact.name);
    setRemark(contact.remark);
}

void CDoodUserDataManage::initConnect()
{
    connect(m_pClient,SIGNAL(getContactInfoResult(Contact)),this,SLOT(onGetContactInfoResult(Contact)));
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

QString CDoodUserDataManage::buttonType() const
{
    return mButtonType;
}

QString CDoodUserDataManage::setButtonType(const QString &data)
{
    if(mButtonType == data) {
        return data;
    }
    mButtonType = data;
    emit buttonTypeChanged();
    return mButtonType;
}

QString CDoodUserDataManage::groupid() const
{
    return mGroupid;
}

QString CDoodUserDataManage::setGroupid(const QString &data)
{
    if(mGroupid == data) {
        return data;
    }
    mGroupid = data;
    emit groupidChanged();
    return mGroupid;
}

QString CDoodUserDataManage::memberType() const
{
    return mMemberType;
}

QString CDoodUserDataManage::setMemberType(const QString &data)
{
    if(mMemberType == data) {
        return data;
    }
    mMemberType = data;
    emit memberTypeChanged();
    return mMemberType;
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

