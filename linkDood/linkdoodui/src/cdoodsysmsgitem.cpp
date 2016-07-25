#include "cdoodsysmsgitem.h"

#include <QDebug>

CDoodSysmsgItem::CDoodSysmsgItem(QObject *parent) : QObject(parent)
{

}

bool CDoodSysmsgItem::CDoodSysmsgItem::isShowButton()  const
{
    qDebug() << Q_FUNC_INFO;
    return mIsShowButton;
}

bool CDoodSysmsgItem::setIsShowButton(bool data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mIsShowButton)
        return data;
    mIsShowButton = data;
    emit isShowButtonChanged();
    return mIsShowButton;

}

QString CDoodSysmsgItem::msgType() const
{
    return mMsgType;
}

QString CDoodSysmsgItem::setMsgType(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mMsgType)
        return data;
    mMsgType = data;
    emit msgTypeChanged();
    return mMsgType;
}

QString CDoodSysmsgItem::msgid() const
{
    qDebug() << Q_FUNC_INFO;
    return mMsgid;
}

QString CDoodSysmsgItem::setMsgid(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mMsgid)
        return data;
    mMsgid = data;
    emit msgidChanged();
    return mMsgid;
}

QString CDoodSysmsgItem::targetid() const
{
    qDebug() << Q_FUNC_INFO;
    return mTargetid;

}

QString CDoodSysmsgItem::setTargetid(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mTargetid)
        return data;
    mTargetid = data;
    emit targetidChanged();
    return mTargetid;
}

QString CDoodSysmsgItem::time() const
{
    qDebug() << Q_FUNC_INFO;
    return mTime;
}

QString CDoodSysmsgItem::setTime(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mTime)
        return data;
    mTime = data;
    emit timeChanged();
    return mTime;
}

QString CDoodSysmsgItem::msgtypeText() const
{
    qDebug() << Q_FUNC_INFO;
    return mMsgtypeText;
}

QString CDoodSysmsgItem::setMsgtypeText(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mMsgtypeText)
        return data;
    mMsgtypeText = data;
    emit msgtypeTextChanged();
    return mMsgtypeText;
}

QString CDoodSysmsgItem::name() const
{
    qDebug() << Q_FUNC_INFO;
    return mName;
}

QString CDoodSysmsgItem::setName(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mName)
        return data;
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodSysmsgItem::avatar() const
{
    qDebug() << Q_FUNC_INFO;
    return mAvatar;
}

QString CDoodSysmsgItem::setAvatar(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mAvatar)
        return data;
    mAvatar = data;
    emit avatarChanged();
    return mAvatar;
}

QString CDoodSysmsgItem::respons() const
{
    qDebug() << Q_FUNC_INFO;
    return mRespons;
}

QString CDoodSysmsgItem::setRespons(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mRespons)
        return data;
    mRespons = data;
    emit responsChanged();
    return mRespons;
}

QString CDoodSysmsgItem::info() const
{
    qDebug() << Q_FUNC_INFO;
    return mInfo;
}

QString CDoodSysmsgItem::setInfo(QString data)
{
    qDebug() << Q_FUNC_INFO;
    if(data == mInfo)
        return data;
    mInfo = data;
    emit infoChanged();
    return mInfo;
}
