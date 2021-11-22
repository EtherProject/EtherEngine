#ifndef _STRING_H_
#define _STRING_H_

#include "Module.h"
#include "Macros.h"
#include "Utils.h"

#include "lua.hpp"

class ModuleString : public Module
{
public:
	static ModuleString& Instance();
	~ModuleString() {};

private:
	ModuleString();

};

/*
* ��GBK�����ַ���ת��ΪUTF-8����
* 1������GBK�����ַ�����string��
* 1����ֵ��UTF-8�����ַ�����string��
*/
ETHER_API gbkToUTF8(lua_State* L);

/*
* ��UTF-8�����ַ���ת��ΪGBK����
* 1������UTF-8�����ַ�����string��
* 1����ֵ��GBK�����ַ�����string��
*/
ETHER_API utf8ToGBK(lua_State* L);

/*
* ��ȡUTF-8�����ַ���
* 2��3������UTF-8�����ַ�����string������ʼλ�ã�number��������λ�ã�number����ѡĬ��Ϊ-1��
* 1����ֵ����ȡ����ַ�����string��
*/
ETHER_API subStrUTF8(lua_State* L);

/*
* ��ȡUTF-8�����ַ�������
* 1������UTF-8�����ַ�����string��
* 1����ֵ���ַ������ȣ�number��
*/
ETHER_API lenUTF8(lua_State* L);

#endif // !_STRING_H_
