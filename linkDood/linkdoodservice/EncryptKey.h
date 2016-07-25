#pragma once
#include <string>
#include <map>
//PC端随机16位秘钥生成算法头文件声明
class EncryptKey
{
public:
	EncryptKey();
	virtual ~EncryptKey();
	void initialise();
	std::string get_key();
private:
	int					m_rand;
	int					m_maxvalue;
	std::map<int, char> m_CharList;
};