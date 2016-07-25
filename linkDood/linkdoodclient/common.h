#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <QString>

using namespace std;

class Common
{
public:
    Common();

    static int hexcharToInt(char c);
    static void hexstringToBytes(char* hexstring, char* bytes);
    static void bytesToHexstring(char* bytes, int bytelength, char *hexstring, int hexstrlength);
    //16进制转换成字符表情编码
    static string  Hex2Emoji(std::string hexer);

    //字符表情编码转换成16进制
    static string Emoji2Hex(std::string emoji);
    static QString dealTime(qint64 msgtime, int type);
};

#endif // COMMON_H
