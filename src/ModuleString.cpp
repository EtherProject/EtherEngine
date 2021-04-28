#include "ModuleString.h"


ModuleString& ModuleString::Instance()
{
	static ModuleString* _instance = new ModuleString();
	return *_instance;
}


ModuleString::ModuleString()
{
	_vCMethods = {
		{ "GBKToUTF8", gbkToUTF8 },
		{ "UTF8ToGBK", utf8ToGBK },
	};
}


ETHER_API gbkToUTF8(lua_State* L)
{
	try
	{
		lua_pushstring(L, EncodingConversion::GBKToUTF8(luaL_checkstring(L, 1)).c_str());
	}
	catch (const std::exception&)
	{
		lua_pushnil(L);
	}

	return 1;
}

ETHER_API utf8ToGBK(lua_State* L)
{
	try
	{
		lua_pushstring(L, EncodingConversion::UTF8ToGBK(luaL_checkstring(L, 1)).c_str());
	}
	catch (const std::exception&)
	{
		lua_pushnil(L);
	}

	return 1;
}
