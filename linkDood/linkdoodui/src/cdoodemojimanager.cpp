#include "cdoodemojimanager.h"
#include "cdoodemojiitem.h"

#include <QDir>

CDoodEmojiManager::CDoodEmojiManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qRegisterMetaType<CDoodEmojiManager*>();
    GetEmojiPic();
}

void CDoodEmojiManager::GetEmojiPic()
{
    //GetUserDefEmojiPic();

    QDir faceDir;
    faceDir.setPath(":/res/smilies/emoji_face/");


    QFileInfoList faceFileInfoList = faceDir.entryInfoList(QDir::Files, QDir::Name);
    QString faceName="";
    QString facePath="";

    qDebug() << Q_FUNC_INFO <<"77777777777:"<< faceFileInfoList.size();
    for (int i = 0; i < faceFileInfoList.size(); i++)
    {
        facePath = "qrc"+faceFileInfoList.at(i).absoluteFilePath();

        faceName = faceFileInfoList.at(i).baseName();

        if (emojiListMap.contains(faceName))
        {
            CDoodEmojiItem* item = (CDoodEmojiItem*)emojiListMap.value(faceName);
            item->setName(faceName);
            item->setPath(facePath);
        }else{

            CDoodEmojiItem* item = new CDoodEmojiItem(this);
            item->setName(faceName);
            item->setPath(facePath);
            insertItem(itemCount(),item);
            emojiListMap[faceName] = item;
        }
        qDebug() << Q_FUNC_INFO << "name" <<faceName <<"path:" <<facePath;
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
