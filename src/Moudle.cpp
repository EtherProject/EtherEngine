#include "Moudle.h"

void Moudle::OpenMoudle()
{
	for (luaL_Reg method : _vCMethods)
	{
		lua_pushcfunction(_pL, method.func);
		lua_setglobal(_pL, method.name);
	}

	lua_newtable(_pL);

	for (Macro macro : _vMacros)
	{
		lua_pushstring(_pL, macro.name);
		lua_pushinteger(_pL, macro.value);
		lua_settable(_pL, -3);
	}

	lua_setglobal(_pL, _strName.c_str());
}
