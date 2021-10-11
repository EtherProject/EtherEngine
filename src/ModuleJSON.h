#ifndef _JSON_H_
#define _JSON_H_

#include "Module.h"
#include "Macros.h"

#include "lua.hpp"
#include <cjson/cJSON.h>

#include <string>
#include <fstream>
#include <sstream>


class ModuleJSON : public Module
{
public:
	static ModuleJSON& Instance();
	~ModuleJSON() {};

private:
	ModuleJSON();

};

/// <summary>
/// �ж�ָ��������Ԫ���Ƿ�Ϊ����
/// </summary>
/// <param name="L">��ǰLua���������</param>
/// <param name="iIndex">ջ����</param>
/// <returns>�Ƿ�Ϊ����</returns>
bool CheckArrary(lua_State* L, int iIndex);

/// <summary>
/// ��Lua��table���л�ΪJSON
/// </summary>
/// <param name="pJsonNode">cJson����</param>
/// <param name="iIndex">ջ����</param>
/// <param name="L">��ǰLua���������</param>
void LuaTable2CJson(cJSON*& pJsonNode, int iIndex, lua_State* L);

/// <summary>
/// ��JSON�����л�ΪLua��table
/// </summary>
/// <param name="pJsonNode">cJson����</param>
/// <param name="L">��ǰLua���������</param>
void CJson2LuaObj(cJSON* pJsonNode, lua_State* L);

/// <summary>
/// ��Lua�������л�ΪJSON�ַ���
/// </summary>
/// <param name="L">��ǰLua���������</param>
/// <param name="bIsFormat">�Ƿ��ʽ��</param>
/// <returns>JSON�ַ���</returns>
char* LuaVaule2JSONStr(lua_State* L, bool bIsFormat);

/*
* ���ѱ���� JSON �������Ϊ Lua ����
* 1�������ѱ���� JSON �����ַ�����string��
* 1����ֵ�������� Lua ����nil / boolean / number / string / table��
*/
ETHER_API loadJSON(lua_State* L);

/*
* ��ָ��·���ļ����ѱ���� JSON �������Ϊ Lua ����
* 1�������洢�ѱ��� JSON ������ļ�·����string��
* 1����ֵ�������� Lua ����nil / boolean / number / string / table��
*/
ETHER_API loadJSONFromFile(lua_State* L);

/*
* �� Lua �������� JSON �ַ���
* 1��2������Lua ����nil / boolean / number / string / table��������ѡ���Ƿ�Ա������ַ�����ʽ����Ĭ�ϲ����и�ʽ����boolean��
* 1����ֵ���ѱ���� JSON �����ַ�����string��
*/
ETHER_API dumpJSON(lua_State* L);

/*
* �� Lua �������� JSON �ַ������洢��ָ��·�����ļ���
* 2��3������Lua ����nil / boolean / number / string / table�������Դ洢�ѱ��� JSON ������ļ�·����string��������ѡ���Ƿ�Ա������ַ�����ʽ����Ĭ�ϲ����и�ʽ����boolean��
* 0����ֵ
*/
ETHER_API dumpJSONToFile(lua_State* L);

#endif // !_JSON_H_
