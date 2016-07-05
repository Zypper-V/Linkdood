#include "cdoodemojimanager.h"
#include "cdoodemojiitem.h"

#include <QDir>

CDoodEmojiManager::CDoodEmojiManager(LinkDoodClient *client, QObject *parent) :
    CDoodListModel(parent), m_pClient(client)
{
    qRegisterMetaType<CDoodEmojiManager*>();
    getEmojiPic();
}

void CDoodEmojiManager::getEmojiPic()
{
//    loadEmoji(":/res/smilies/dynamic_expression");
    loadEmoji(":/res/smilies/emoji_face/");
    loadEmoji(":/res/smilies/instruct/");
}

void CDoodEmojiManager::onBtnItemClicked(QString index)
{
    emit signalEmojiChanged(emojiListMap[index]->path());
}

void CDoodEmojiManager::loadEmoji(QString path)
{
    QDir faceDir;
    faceDir.setPath(path);

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
