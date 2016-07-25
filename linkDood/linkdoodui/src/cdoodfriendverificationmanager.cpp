#include "cdoodfriendverificationmanager.h"
#include <QDebug>

CDoodFriendVerificationManager::CDoodFriendVerificationManager(QObject *parent) : QObject(parent)
{

}

QString CDoodFriendVerificationManager::id() const
{
    return mId;
}

QString CDoodFriendVerificationManager::setId(const QString &data)
{
    if(data == mId){
        return data;
    }
    mId = data;
    emit idChanged();
    qDebug() << Q_FUNC_INFO;
    return mId;
}

QString CDoodFriendVerificationManager::name() const
{
    return mName;
}

QString CDoodFriendVerificationManager::setName(const QString &data)
{
    if(data == mName){
        return data;
    }
    mName = data;
    emit nameChanged();
    qDebug() << Q_FUNC_INFO;
    return mName;
}

QString CDoodFriendVerificationManager::thumbAvatar() const
{
    return mThumbAvatar;
}

QString CDoodFriendVerificationManager::setThumbAvatar(const QString &data)
{
    if(data == mThumbAvatar){
        return data;
    }
    mThumbAvatar = data;
    emit thumbAvatarChanged();
    qDebug() << Q_FUNC_INFO;
    return mThumbAvatar;
}

QString CDoodFriendVerificationManager::myName() const
{
    return mMyname;
}

QString CDoodFriendVerificationManager::setMyName(const QString &data)
{
    if(data == mMyname){
        return data;
    }
    mMyname = data;
    emit thumbAvatarChanged();
    qDebug() << Q_FUNC_INFO;
    return mMyname;
}
