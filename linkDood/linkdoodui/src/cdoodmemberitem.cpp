#include "cdoodmemberitem.h"

CDoodMemberItem::CDoodMemberItem(QObject *parent): QObject(parent)
{

}
QString CDoodMemberItem::id() const
{
    return mId;
}

QString CDoodMemberItem::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodMemberItem::name() const
{
    return mName;
}

QString CDoodMemberItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodMemberItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodMemberItem::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

QString CDoodMemberItem::avatar() const
{
    return mAvatar;
}

QString CDoodMemberItem::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}

QString CDoodMemberItem::gender() const
{
    return mGender;
}

QString CDoodMemberItem::setGender(const QString &data)
{
    if(mGender == data) {
        return data;
    }
    mGender = data;
    emit genderChanged();
    return mGender;
}
QString CDoodMemberItem::member_type() const
{
    return mMember_type;
}

QString CDoodMemberItem::setMember_type(const QString &data)
{
    if(mMember_type == data) {
        return data;
    }
    mMember_type = data;
    emit member_typeChanged();
    return mMember_type;
}
QString CDoodMemberItem::team() const
{
    return mTeam;
}

QString CDoodMemberItem::setTeam(const QString &data)
{
    if(mTeam == data) {
        return data;
    }
    mTeam = data;
    emit teamChanged();
    return mTeam;
}
QString CDoodMemberItem::remark() const
{
    return mRemark;
}

QString CDoodMemberItem::setRemark(const QString &data)
{
    if(mRemark == data) {
        return data;
    }
    mRemark = data;
    emit remarkChanged();
    return mRemark;
}
QString CDoodMemberItem::groupid() const
{
    return mGroupid;
}

QString CDoodMemberItem::setGroupid(const QString &data)
{
    if(mGroupid == data) {
        return data;
    }
    mGroupid = data;
    emit groupidChanged();
    return mGroupid;
}
QString CDoodMemberItem::sectionKey() const
{
    return mSection;
}

QString CDoodMemberItem::setSection(const QString &section)
{
    if(mSection == section) {
        return section;
    }
    mSection = section;
    emit sectionChanged();
    return mSection;
}
QString CDoodMemberItem::isChoose() const
{
    return mIsChoose;
}

QString CDoodMemberItem::setIsChoose(const QString &data)
{
    if(mIsChoose==data){
        return data;
    }
    mIsChoose=data;
    emit isChooseChanged();
    return mIsChoose;
}
