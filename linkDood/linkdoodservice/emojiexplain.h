#ifndef EMOJIEXPLAIN_H
#define EMOJIEXPLAIN_H

#include <string>
#include <QString>
#include <QMap>

class EmojiExplain
{
public:
    EmojiExplain();
    static void EmojiParseFrom(std::string src, std::string& target);
    static void EmojiParseTo(std::string src, std::string& target);
private:
    void init();

private:
     QMap<QString, QString>         m_EmojiDynamicExplain;
     QMap<QString, QString>         m_EmojiFace;
     QMap<QString, QString>         m_EmojiInstruct;
 };

#endif // EMOJIEXPLAIN_H
