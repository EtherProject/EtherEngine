#include "Module.h"


Module& Module::Instance()
{
	static Module* _instance = new Module();
	return *_instance;
}


void Module::PushMetaDataToGlobal(lua_State* L)
{
	for (MetaData metadata : _vMetaData)
	{
		luaL_newmetatable(L, metadata.name.c_str());

		lua_pushstring(L, "__index");
		lua_newtable(L);
		for (luaL_Reg method : metadata.cFuns)
		{
			lua_pushstring(L, method.name);
			lua_pushcfunction(L, method.func);
			lua_settable(L, -3);
		}
		lua_settable(L, -3);

		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, metadata.gcFun);
		lua_settable(L, -3);
	}
}


void Module::PushMoudleDataToStack(lua_State* L)
{
	lua_newtable(L);

	for (luaL_Reg method : _vCMethods)
	{
		lua_pushstring(L, method.name);
		lua_pushcfunction(L, method.func);
		lua_settable(L, -3);
	}

	for (Macro macro : _vMacros)
	{
		lua_pushstring(L, macro.name);
		lua_pushinteger(L, macro.value);
		lua_settable(L, -3);
	}
}
