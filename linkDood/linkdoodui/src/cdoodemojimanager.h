#ifndef CDOODEMOJIMANAGER_H
#define CDOODEMOJIMANAGER_H

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodEmojiItem;
class CDoodEmojiManager : public CDoodListModel
{
    Q_OBJECT
public:
    CDoodEmojiManager();
    Q_INVOKABLE void GetEmojiPic();
    Q_INVOKABLE void GetUserDefEmojiPic();


public slots:
    void onBtnItemClicked(QString index);

signals:
    void signalEmojiChanged(QString path);

private:
    LinkDoodClient *m_pClient;
    QMap<QString, CDoodEmojiItem*> emojiListMap;
};

#endif // CDOODEMOJIMANAGER_H
