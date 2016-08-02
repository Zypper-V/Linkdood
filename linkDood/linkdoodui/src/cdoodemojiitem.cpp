#include "cdoodemojiitem.h"
#include<QDebug>

CDoodEmojiItem::CDoodEmojiItem(QObject *parent) : QObject(parent)
{
    mName = "";
    mPath = "";
    mExplain = "";
}

QString CDoodEmojiItem::name() const
{
    qDebug() << Q_FUNC_INFO;
    return mName;
}

QString CDoodEmojiItem::setName(const QString &data)
{
//    qDebug() << Q_FUNC_INFO;
    if(mName == data)
        return data;
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodEmojiItem::path() const
{
    qDebug() << Q_FUNC_INFO;
    return mPath;
}

QString CDoodEmojiItem::setPath(const QString &data)
{
//    qDebug() << Q_FUNC_INFO;
    if(mPath == data)
        return data;
    mPath = data;
    emit pathChanged();
    return mPath;
}

QString CDoodEmojiItem::explain() const
{
    qDebug() << Q_FUNC_INFO<<"3333333333:"<<mExplain;
    return mExplain;
}

QString CDoodEmojiItem::setExplain(const QString &data)
{
//    qDebug() << Q_FUNC_INFO;
    if(mExplain == data)
        return data;
    mExplain = data;
    emit explainChanged();
    return mExplain;
}
