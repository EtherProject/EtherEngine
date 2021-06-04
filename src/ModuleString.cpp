#include "ModuleString.h"

using namespace std;

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
		{ "SubStrUTF8", subStrUTF8 },
		{ "LenUTF8", lenUTF8 },
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


ETHER_API subStrUTF8(lua_State* L)
{
	string strRaw = luaL_checkstring(L, 1);

	size_t idxStrRaw = 0, lenUTF8 = 0;
	while (strRaw[idxStrRaw++]) lenUTF8 += ((strRaw[idxStrRaw] & 0xc0) != 0x80);
	idxStrRaw = 0;

	size_t idxStrUTF8 = 0, lenRaw = strRaw.length();
	long long startUTF8 = luaL_checkinteger(L, 2);
	startUTF8 = !startUTF8 ? 0 : (startUTF8 > 0 ? startUTF8 - 1 : (-startUTF8 >= lenUTF8 ? 0 : lenUTF8 + startUTF8));

	while (idxStrUTF8 < startUTF8 && idxStrRaw < lenRaw)
		idxStrUTF8 += ((strRaw[idxStrRaw++] & 0xc0) != 0x80);
	while (idxStrRaw < lenRaw && (strRaw[idxStrRaw] & 0xc0) == 0x80)
		idxStrRaw++;

	if (lua_gettop(L) == 2)
		lua_pushstring(L, strRaw.substr(idxStrRaw).c_str());
	else
	{
		size_t startRaw = idxStrRaw;
		long long endUTF8 = luaL_checkinteger(L, 3);
		endUTF8 = !endUTF8 ? 0 : (endUTF8 > 0 ? endUTF8 : (-endUTF8 >= lenUTF8 ? 0 : lenUTF8 + endUTF8 + 1));
		if (endUTF8 < startRaw)
			lua_pushstring(L, "");
		else
		{
			while (idxStrUTF8 < endUTF8 && idxStrRaw < lenRaw)
				idxStrUTF8 += ((strRaw[idxStrRaw++] & 0xc0) != 0x80);
			while (idxStrRaw < lenRaw && (strRaw[idxStrRaw] & 0xc0) == 0x80)
				idxStrRaw++;
			lua_pushstring(L, strRaw.substr(startRaw, idxStrRaw - startRaw).c_str());
		}
	}

	return 1;
}


ETHER_API lenUTF8(lua_State* L)
{
	const char* strUTF8 = luaL_checkstring(L, 1);
	size_t idxStr = 0, length = 0;
	while (strUTF8[idxStr++]) length += ((strUTF8[idxStr] & 0xc0) != 0x80);
	lua_pushnumber(L, length);

	return 1;
}
