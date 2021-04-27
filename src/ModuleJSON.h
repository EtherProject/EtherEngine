#ifndef _JSON_H_
#define _JSON_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>
#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class ModuleJSON : public Module
{
public:
	static ModuleJSON& Instance();
	~ModuleJSON() {};

private:
	ModuleJSON();

};

/// <summary>
/// 判断指定索引的元素是否为数组
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="iIndex">栈索引</param>
/// <returns>是否为数组</returns>
bool CheckArrary(lua_State* L, int iIndex);

/// <summary>
/// 将Lua的table序列化为JSON
/// </summary>
/// <param name="pJsonNode">cJson对象</param>
/// <param name="iIndex">栈索引</param>
/// <param name="L">当前Lua虚拟机环境</param>
void LuaTable2CJson(cJSON*& pJsonNode, int iIndex, lua_State* L);

/// <summary>
/// 将JSON反序列化为Lua的table
/// </summary>
/// <param name="pJsonNode">cJson对象</param>
/// <param name="L">当前Lua虚拟机环境</param>
void CJson2LuaObj(cJSON* pJsonNode, lua_State* L);

/// <summary>
/// 将Lua数据序列化为JSON字符串
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="bIsFormat">是否格式化</param>
/// <returns>JSON字符串</returns>
char* LuaVaule2JSONStr(lua_State* L, bool bIsFormat);

/*
* 将已编码的 JSON 对象解码为 Lua 对象
* 1参数：已编码的 JSON 对象字符串（string）
* 1返回值：解码后的 Lua 对象（nil / boolean / number / string / table）
*/
ETHER_API api_LoadJSON(lua_State* L);

/*
* 将指定路径文件中已编码的 JSON 对象解码为 Lua 对象
* 1参数：存储已编码 JSON 对象的文件路径（string）
* 1返回值：解码后的 Lua 对象（nil / boolean / number / string / table）
*/
ETHER_API api_LoadJSONFromFile(lua_State* L);

/*
* 将 Lua 对象编码成 JSON 字符串
* 1或2参数：Lua 对象（nil / boolean / number / string / table），【可选】是否对编码后的字符串格式化，默认不进行格式化（boolean）
* 1返回值：已编码的 JSON 对象字符串（string）
*/
ETHER_API api_DumpJSON(lua_State* L);

/*
* 将 Lua 对象编码成 JSON 字符串并存储到指定路径的文件中
* 2或3参数：Lua 对象（nil / boolean / number / string / table），用以存储已编码 JSON 对象的文件路径（string），【可选】是否对编码后的字符串格式化，默认不进行格式化（boolean）
* 0返回值
*/
ETHER_API api_DumpJSONToFile(lua_State* L);

#endif // !_JSON_H_
