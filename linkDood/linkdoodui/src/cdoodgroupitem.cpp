#include "cdoodgroupitem.h"
#include<QDebug>
CDoodGroupItem::CDoodGroupItem(QObject *parent): QObject(parent)
{

}
QString CDoodGroupItem::id() const
{
    return mId;
}

QString CDoodGroupItem::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodGroupItem::name() const
{
    return mName;
}

QString CDoodGroupItem::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodGroupItem::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodGroupItem::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}
QString CDoodGroupItem::timeZone() const
{
    return mTimeZone;
}

QString CDoodGroupItem::setTimeZone(const QString &data)
{
    if(mTimeZone == data) {
        return data;
    }
    mTimeZone = data;
    emit timeZoneChanged();
    return mTimeZone;
}

QString CDoodGroupItem::avatar() const
{
    return mAvatar;
}

QString CDoodGroupItem::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}
QString CDoodGroupItem::pinYin() const
{
    return mPinYin;
}

QString CDoodGroupItem::setPinYin(const QString &data)
{
    if(mPinYin == data) {
        return data;
    }
    mPinYin = data;
    emit pinYinChanged();
    return mPinYin;
}
QString CDoodGroupItem::server() const
{
    return mServer;
}

QString CDoodGroupItem::setServer(const QString &data)
{
    if(mServer == data) {
        return data;
    }
    mServer = data;
    emit serverChanged();
    return mServer;
}
QString CDoodGroupItem::level() const
{
    return mLevel;
}

QString CDoodGroupItem::setLevel(const QString &data)
{
    if(mLevel == data) {
        return data;
    }
    mLevel = data;
    emit levelChanged();
    return mLevel;
}
QString CDoodGroupItem::sectionKey() const
{
    return mSection;
}

QString CDoodGroupItem::setSection(const QString &section)
{
    if(mSection == section) {
        return section;
    }
    mSection = section;
    emit sectionChanged();
    return mSection;
}

QString CDoodGroupItem::f_fileid() const
{
    return mF_fileid;
}

QString CDoodGroupItem::setF_fileid(const QString &data)
{
   if(mF_fileid==data){
       return data;
   }
   mF_fileid=data;
   emit f_fileidChanged();
   return mF_fileid;
}

QString CDoodGroupItem::f_userid() const
{
    return mF_userid;
}

QString CDoodGroupItem::setF_userid(const QString &data)
{
    if(mF_userid==data){
        return data;
    }
    mF_userid=data;
    emit f_useridChanged();
    return mF_userid;
}

QString CDoodGroupItem::f_username() const
{
    return mF_username;
}

QString CDoodGroupItem::setF_username(const QString &data)
{
    if(mF_username==data){
        return data;
    }
    mF_username=data;
    emit f_usernameChanged();
    return mF_username;
}

QString CDoodGroupItem::f_targetid() const
{
    return mF_targetid;
}

QString CDoodGroupItem::setF_targetid(const QString &data)
{
    if(mF_targetid==data){
        return data;
    }
    mF_targetid=data;
    emit f_targetidChanged();
    return mF_targetid;
}

QString CDoodGroupItem::f_size() const
{
    return mF_size;
}

QString CDoodGroupItem::setF_size(const QString &data)
{
    if(mF_size==data){
        return data;
    }
    mF_size=data;
    emit f_sizeChanged();
    return mF_size;
}

QString CDoodGroupItem::f_time() const
{
    return mF_time;
}

QString CDoodGroupItem::setF_time(const QString &data)
{
    if(mF_time==data){
        return data;
    }
    mF_time=data;
    emit f_timeChanged();
    return mF_time;
}

QString CDoodGroupItem::f_path() const
{
    return mF_path;
}

QString CDoodGroupItem::setF_path(const QString &data)
{
    if(mF_path==data){
        return data;
    }
    mF_path=data;
    emit f_pathChanged();
    return mF_path;
}

QString CDoodGroupItem::f_name() const
{
    return mF_name;
}

QString CDoodGroupItem::setF_name(const QString &data)
{
    if(mF_name==data){
        return data;
    }
    mF_name=data;
    emit f_nameChanged();
    return mF_name;
}

QString CDoodGroupItem::f_url() const
{
    return mF_url;
}

QString CDoodGroupItem::setF_url(const QString &data)
{
    if(mF_url==data){
        return data;
    }
    mF_url=data;
    emit f_urlChanged();
    return mF_url;
}

QString CDoodGroupItem::f_encrypt_key() const
{
    return mF_encrypt_key;
}

QString CDoodGroupItem::setF_encrypt_key(const QString &data)
{
    if(mF_encrypt_key==data){
        return data;
    }
    mF_encrypt_key=data;
    emit f_encrypt_keyChanged();
    return mF_encrypt_key;
}
