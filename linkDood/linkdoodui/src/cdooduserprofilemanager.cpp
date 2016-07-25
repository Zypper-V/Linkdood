#include "cdooduserprofilemanager.h"

CDoodUserProfileManager::CDoodUserProfileManager(LinkDoodClient *client,QObject *parent) :m_pClient(client), QObject(parent)
{
    qRegisterMetaType<CDoodUserProfileManager*>();
    initConnect();
}

void CDoodUserProfileManager::initConnect()
{
    connect(m_pClient, SIGNAL(accountInfoChanged(Contact)), this, SLOT(onAccountInfoChanged(Contact)));
    connect(m_pClient, SIGNAL(connectChanged(QString)), this, SLOT(onConnectChanged(QString)));
    connect(m_pClient, SIGNAL(anthAvatarChanged(QString)), this, SLOT(onAvatarChanged(QString)));
}

QString CDoodUserProfileManager::id() const
{
    return mId;
}

QString CDoodUserProfileManager::setId(const QString &data)
{
    if(mId == data) {
        return data;
    }
    mId = data;
    emit idChanged();
    return mId;
}

QString CDoodUserProfileManager::name() const
{
    return mName;
}

QString CDoodUserProfileManager::setName(const QString &data)
{
    if(mName == data) {
        return data;
    }
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodUserProfileManager::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodUserProfileManager::setThumbAvatar(const QString &data)
{
    if(mThumbAvatar == data) {
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    return mThumbAvatar;
}

void CDoodUserProfileManager::getAccountInfo()
{
    m_pClient->getAccountInfo();
}

void CDoodUserProfileManager::updateAccountInfo(QString _name, QString _avater, QString _gender, QString nickid)
{
    Contact user;

    user.id     = id();
    if(_name != "" && _name != name()){
        user.name = _name;
    }
    if(_gender != "" && _gender != gender()){
        user.gender = _gender;
    }
    if(_avater != "" && _avater != avatar()){
       user.avatar = _avater;
    }
    if(nickid != "" && nickid != nickId()){
       user.nick_id = nickid;
    }
    m_pClient->updateAccountInfo(user);
}

void CDoodUserProfileManager::uploadAvatar(QString path)
{
    qDebug() << Q_FUNC_INFO;
    m_pClient->uploadAvatar(path);
}

void CDoodUserProfileManager::onAccountInfoChanged(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    if(user.avatar != ""){
        setAvatar(user.avatar);
    }
    if(user.gender != "" ){
            setGender(user.gender);
    }
    if(user.name != ""){
         setName(user.name);
    }
    if(user.thumbAvatar != ""){
        setThumbAvatar(user.thumbAvatar);
    }
    if(user.nick_id != ""){
           setNickId(user.nick_id);
    }
    setId(user.id);
}

void CDoodUserProfileManager::onConnectChanged(QString flag)
{
    qDebug() << Q_FUNC_INFO<<"asasasasasaassa"<<flag;
    setConnectFlag(flag);
}

void CDoodUserProfileManager::onAvatarChanged(QString avatar)
{
    if(avatar != ""){
        setThumbAvatar(avatar);
    }
}

void CDoodUserProfileManager::onUploadAvatarResult(QString orgijson, QString thumbjson, int code)
{

}

QString CDoodUserProfileManager::gender() const
{
    return mGender;
}

QString CDoodUserProfileManager::setGender(const QString &data)
{
    qDebug() << Q_FUNC_INFO <<"xingbiexingbiexingbie"<<data;
    mGender = data;
    emit genderChanged();
    return mGender;
}


QString CDoodUserProfileManager::avatar() const
{
    return mAvatar;
}

QString CDoodUserProfileManager::setAvatar(const QString &data)
{
    if(mAvatar == data) {
        return data;
    }
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}
QString CDoodUserProfileManager::connectFlag() const
{
    return mConnectFlag;
}

QString CDoodUserProfileManager::setConnectFlag(const QString &data)
{
    if(mConnectFlag == data) {
        return data;
    }
    mConnectFlag = data;
    emit connectFlagChanged();
    return mConnectFlag;
}

QString CDoodUserProfileManager::nickId() const
{
    return mNickId;
}

QString CDoodUserProfileManager::setNickId(const QString &data)
{
    if(data == mNickId)
        return data;
    mNickId = data;
    emit nickIdChanged();
    return mNickId;
}

