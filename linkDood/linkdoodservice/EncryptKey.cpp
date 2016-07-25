#include <time.h>
#include <stdlib.h>
#include "EncryptKey.h"
EncryptKey::EncryptKey() :m_rand(0)
{
	initialise();
}
//析构函数
EncryptKey::~EncryptKey()
{

}
//初始化
void EncryptKey::initialise()
{
	m_CharList.clear();
	m_CharList.insert(std::pair<int, char>(0, '0'));
	m_CharList.insert(std::pair<int, char>(1, '1'));
	m_CharList.insert(std::pair<int, char>(2, '2'));
	m_CharList.insert(std::pair<int, char>(3, '3'));
	m_CharList.insert(std::pair<int, char>(4, '4'));
	m_CharList.insert(std::pair<int, char>(5, '5'));
	m_CharList.insert(std::pair<int, char>(6, '6'));
	m_CharList.insert(std::pair<int, char>(7, '7'));
	m_CharList.insert(std::pair<int, char>(8, '8'));
	m_CharList.insert(std::pair<int, char>(9, '9'));
	m_CharList.insert(std::pair<int, char>(10, 'a'));
	m_CharList.insert(std::pair<int, char>(11, 'b'));
	m_CharList.insert(std::pair<int, char>(12, 'c'));
	m_CharList.insert(std::pair<int, char>(13, 'd'));
	m_CharList.insert(std::pair<int, char>(14, 'e'));
	m_CharList.insert(std::pair<int, char>(15, 'f'));
	m_CharList.insert(std::pair<int, char>(16, 'g'));
	m_CharList.insert(std::pair<int, char>(17, 'h'));
	m_CharList.insert(std::pair<int, char>(18, 'i'));
	m_CharList.insert(std::pair<int, char>(19, 'j'));
	m_CharList.insert(std::pair<int, char>(20, 'k'));
	m_CharList.insert(std::pair<int, char>(21, 'l'));
	m_CharList.insert(std::pair<int, char>(22, 'm'));
	m_CharList.insert(std::pair<int, char>(23, 'n'));
	m_CharList.insert(std::pair<int, char>(24, 'o'));
	m_CharList.insert(std::pair<int, char>(25, 'p'));
	m_CharList.insert(std::pair<int, char>(26, 'q'));
	m_CharList.insert(std::pair<int, char>(27, 'r'));
	m_CharList.insert(std::pair<int, char>(28, 's'));
	m_CharList.insert(std::pair<int, char>(29, 't'));
	m_CharList.insert(std::pair<int, char>(30, 'u'));
	m_CharList.insert(std::pair<int, char>(31, 'v'));
	m_CharList.insert(std::pair<int, char>(32, 'w'));
	m_CharList.insert(std::pair<int, char>(33, 'x'));
	m_CharList.insert(std::pair<int, char>(34, 'y'));
	m_CharList.insert(std::pair<int, char>(35, 'z'));
	m_maxvalue = m_CharList.size();
	srand((unsigned)time(NULL));

}
//生成16位秘钥
std::string EncryptKey::get_key()
{
	std::string key("");
	int			pos = 0;
	char		Temp = 0;

	for (int index = 0; index < 16; ++index)
	{
		pos = rand() % m_maxvalue;
		Temp = m_CharList[pos];
		key += Temp;
	}
	return key;
}
