#include "common.h"

#include <cstring>
#include <QDateTime>
#include <QtMath>
Common::Common()
{

}

int Common::hexcharToInt(char c)
{
    if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
    return 0;
}
void Common::hexstringToBytes(char* hexstring, char* bytes)
{
    for (size_t i = 0; i < strlen(hexstring); i += 2)
    {
        bytes[i / 2] = (char)((hexcharToInt(hexstring[i]) << 4) | hexcharToInt(hexstring[i + 1]));
    }
}

void Common::bytesToHexstring(char* bytes, int bytelength, char *hexstring, int hexstrlength)
{
    char str2[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    for (int i = 0, j = 0; i < bytelength, j < hexstrlength; i++, j++)
    {
        int b;
        b = 0x0f & (bytes[i] >> 4);
        char s1 = str2[b];
        hexstring[j] = s1;
        b = 0x0f & bytes[i];
        char s2 = str2[b];
        j++;
        hexstring[j] = s2;
    }
}

string Common::Hex2Emoji(string hexer)
{
    std::string bytes("");
    char sz_bytes[512] = { 0 };
    memset(sz_bytes, 0, sizeof(char)*(hexer.size() / 2));
    hexstringToBytes((char*)hexer.c_str(), sz_bytes);
    for (size_t i = 0; i < hexer.size() / 2; ++i)
    {
        bytes += sz_bytes[i];
    }
    return bytes;
}

string Common::Emoji2Hex(string emoji)
{
    char* phex = NULL;
    std::string	hex("");

    phex = new char[emoji.size() * 2];
    memset(phex, 0, emoji.size() * 2);
    bytesToHexstring((char*)emoji.c_str(), emoji.size(), phex, emoji.size() * 2);
    for (size_t i = 0; i < emoji.size() * 2; ++i)
    {
        hex += phex[i];
    }
    return hex;
}

QString Common::dealTime(qint64 msgtime, int type)
{
    QString strDateTime("");
    QDateTime msgDateTime;
    int distance = 0;
    if (!msgtime)
    {
        return strDateTime;
    }
    msgDateTime.setMSecsSinceEpoch(msgtime);
    distance = msgDateTime.daysTo(QDateTime::currentDateTime());
    //今天
    if (qFabs(distance) <= 0)
    {
        strDateTime = msgDateTime.toString("HH:mm");
    }
    //昨天
    else if (qFabs(distance) <= 1)
    {
        if ( 1 == type)
        {
            strDateTime = "昨天";
        }
        else {
            strDateTime = "昨天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
        }

    }
    //前天
    else if (qFabs(distance) <= 2)
    {
        if (1 == type)
        {
            strDateTime = "前天";
        }
        else {
            strDateTime = "前天" + QString::fromLocal8Bit(" ") + msgDateTime.toString("HH:mm");
        }
    }
    else
    {
        if (1 == type)
        {
            strDateTime = msgDateTime.toString("MM月dd日");
        }
        else {
            strDateTime = msgDateTime.toString("MM月dd日") +QString::fromLocal8Bit(" ")+msgDateTime.toString("HH:mm");
        }
    }
    return strDateTime;
}

