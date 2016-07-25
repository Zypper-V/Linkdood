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
    static void dyEmojiParseFrom(QString src, QString& target,QString& explain);
    static void dyEmojiParseTo(QString src, QString& target,QString& explain);
private:
    static void init();

private:
     static QMap<QString, QString>         m_EmojiDynamicExplain;
     static QMap<QString, QString>         m_EmojiFace;
     static QMap<QString, QString>         m_EmojiInstruct;
     static bool isInit;
 };

#endif // EMOJIEXPLAIN_H
