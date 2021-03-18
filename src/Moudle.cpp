#include "Moudle.h"

void Moudle::OpenMoudle()
{
	for (luaL_Reg method : _vCMethods)
	{
		lua_pushcfunction(_pL, method.func);
		lua_setglobal(_pL, method.name);
	}

	for (Macro macro : _vMacros)
	{
		lua_pushnumber(_pL, macro.value);
		lua_setglobal(_pL, macro.name);
	}
}
