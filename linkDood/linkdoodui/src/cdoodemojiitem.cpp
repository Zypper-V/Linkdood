#include "cdoodemojiitem.h"

CDoodEmojiItem::CDoodEmojiItem(QObject *parent) : QObject(parent)
{
    mName = "";
    mPath = "";
    mExplain = "";
}

QString CDoodEmojiItem::name() const
{
    return mName;
}

QString CDoodEmojiItem::setName(const QString &data)
{
    if(mName == data)
        return data;
    mName = data;
    emit nameChanged();
    return mName;
}

QString CDoodEmojiItem::path() const
{
    return mPath;
}

QString CDoodEmojiItem::setPath(const QString &data)
{
    if(mPath == data)
        return data;
    mPath = data;
    emit pathChanged();
    return mPath;
}

QString CDoodEmojiItem::explain() const
{
    return mExplain;
}

QString CDoodEmojiItem::setExplain(const QString &data)
{
    if(mExplain == data)
        return data;
    mExplain = data;
    emit explainChanged();
    return mExplain;
}
