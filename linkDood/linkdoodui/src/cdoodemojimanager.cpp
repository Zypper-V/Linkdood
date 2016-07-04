#include "cdoodemojimanager.h"
#include "cdoodemojiitem.h"

#include <QDir>

CDoodEmojiManager::CDoodEmojiManager()
{

}

void CDoodEmojiManager::GetEmojiPic()
{
    GetUserDefEmojiPic();

    QDir faceDir;
    faceDir.setPath("ui/image/smilies/emoji_face");


    QFileInfoList faceFileInfoList = faceDir.entryInfoList(QDir::Files, QDir::Name);
    QString faceName="";
    QString facePath="";
    CDoodEmojiItem item;

    for (int i = 0; i < faceFileInfoList.size(); i++)
    {
        facePath = faceFileInfoList.at(i).absoluteFilePath();
        if (!facePath.isEmpty())
        {
            facePath = "file:///" + facePath;
        }
        faceName = faceFileInfoList.at(i).baseName();

        if (emojiListMap.contains(faceName))
        {
            item.setName(faceName);
            item.setPath(facePath);

            emojiListMap[faceName] = &item;
        }
    }
}

void CDoodEmojiManager::GetUserDefEmojiPic()
{
    QDir faceDir;

    faceDir.setPath("ui/image/smilies/instruct");
    QFileInfoList faceFileInfoList = faceDir.entryInfoList(QDir::Files, QDir::Name);
    QString faceName;
    QString facePath;
    CDoodEmojiItem item;
    for (int i = 0; i < faceFileInfoList.size(); i++)
    {
        faceName = faceFileInfoList.at(i).baseName();
        item.setName(faceName);

        facePath = faceFileInfoList.at(i).absoluteFilePath();
        if (!facePath.isEmpty())
        {
            facePath = "file:///" + facePath;
        }

        item.setPath(facePath);
        emojiListMap[faceName] = &item;
    }
}

void CDoodEmojiManager::onBtnItemClicked(QString index)
{
    emit signalEmojiChanged(emojiListMap[index]->path());
}
