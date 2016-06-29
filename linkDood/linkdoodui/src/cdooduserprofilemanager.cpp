#include "cdooduserprofilemanager.h"

CDoodUserProfileManager::CDoodUserProfileManager(LinkDoodClient *client,QObject *parent) :m_pClient(client), QObject(parent)
{
    qRegisterMetaType<CDoodUserProfileManager*>();
    initConnect();
}

void CDoodUserProfileManager::initConnect()
{
    connect(m_pClient, SIGNAL(accountInfoChanged(Contact)), this, SLOT(onAccountInfoChanged(Contact)));

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

void CDoodUserProfileManager::onAccountInfoChanged(Contact user)
{
    qDebug() << Q_FUNC_INFO;
    setAvatar(user.avatar);
    setGender(user.gender);
    setId(user.id);
    setName(user.name);
    setThumbAvatar(user.thumbAvatar);
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

