#ifndef CDOODEMOJIMANAGER_H
#define CDOODEMOJIMANAGER_H

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodEmojiItem;
class CDoodEmojiManager : public CDoodListModel
{
    Q_OBJECT
public:
    CDoodEmojiManager(LinkDoodClient *client = 0, QObject *parent = 0);
    Q_INVOKABLE void getEmojiPic();

public slots:
    void onBtnItemClicked(QString index);

signals:
    void signalEmojiChanged(QString path);

private:
    void loadEmoji(QString path);

    LinkDoodClient *m_pClient;
    QMap<QString, CDoodEmojiItem*> emojiListMap;
};

#endif // CDOODEMOJIMANAGER_H
