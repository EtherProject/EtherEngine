#include "ModuleOS.h"


ETHER_API getBasePath(lua_State * L)
{
	lua_pushstring(L, SDL_GetBasePath());

	return 1;
}


ETHER_API setClipboardText(lua_State * L)
{
	const char* text = luaL_checkstring(L, 1);
	SDL_SetClipboardText(text);

	return 0;
}


ETHER_API getClipboardText(lua_State * L)
{
	lua_pushstring(L, SDL_GetClipboardText());

	return 1;
}


ETHER_API getPlatformType(lua_State * L)
{
	lua_pushstring(L, SDL_GetPlatform());

	return 1;
}


ETHER_API getSystemTotalRAM(lua_State * L)
{
	lua_pushnumber(L, SDL_GetSystemRAM());

	return 1;
}


ETHER_API listDirectory(lua_State* L)
{

#ifdef __WINDOWS__

	intptr_t hFile = 0;
    _finddata_t fileinfo;
    string path = luaL_checkstring(L, 1);
	path = path.empty() ? "./*" : (path[path.length() - 1] == '\\' || path[path.length() - 1] == '/' ? path.append("*") : path.append("\\*"));

	if (_findfirst(path.c_str(), &fileinfo) == -1)
	{
		luaL_error(L, "bad argument #1 to 'ListDirectory' (path not exist)");
	}
	else
	{
		lua_newtable(L);
		if ((hFile = _findfirst(path.c_str(), &fileinfo)) != -1)
		{
			int index_file = 1;
			do
			{
				if (string(fileinfo.name) != "." && string(fileinfo.name) != "..")
				{
					lua_pushnumber(L, index_file);
					lua_pushstring(L, fileinfo.name);
					lua_settable(L, -3);
					index_file++;
				}
			} while (!_findnext(hFile, &fileinfo));
			_findclose(hFile);
		}
	}

#else

#endif

	return 1;
}


ETHER_API ifPathExist(lua_State* L)
{
	int mode = PATHMODE_FILEANDDIR;
	if (lua_isnumber(L, 2))
	{
		switch ((int)lua_tonumber(L, 2))
		{
		case PATHMODE_FILE:
			mode = PATHMODE_FILE;
			break;
		case PATHMODE_DIR:
			mode = PATHMODE_DIR;
			break;
		case PATHMODE_FILEANDDIR:
			mode = PATHMODE_FILEANDDIR;
			break;
		default:
			luaL_error(L, "bad argument #2 to 'IfPathExist' (MACRO number expected, got %s)", luaL_typename(L, 2));
			break;
		}
	}

#ifdef __WINDOWS__

	_finddata_t fileinfo;
	string path = luaL_checkstring(L, 1);

	if (_findfirst(path.c_str(), &fileinfo) == -1)
		lua_pushboolean(L, false);
	else
		switch (mode)
		{
		case PATHMODE_FILEANDDIR:
			lua_pushboolean(L, true);
			break;
		case PATHMODE_DIR:
			if (fileinfo.attrib & _A_SUBDIR)
				lua_pushboolean(L, true);
			else
				lua_pushboolean(L, false);
			break;
		case PATHMODE_FILE:
			if (!(fileinfo.attrib & _A_SUBDIR))
				lua_pushboolean(L, true);
			else
				lua_pushboolean(L, false);
			break;
		default:
			break;
		}

#else

#endif

	return 1;
}


ETHER_API getPathInfo(lua_State* L)
{

#ifdef __WINDOWS__

	intptr_t hFile = 0;
	_finddata_t fileinfo;
	string path = luaL_checkstring(L, 1);
	if ((hFile = _findfirst(path.c_str(), &fileinfo)) == -1)
		lua_pushnil(L);
	else
	{
		lua_newtable(L);
		lua_pushstring(L, "name");
		lua_pushstring(L, fileinfo.name);
		lua_settable(L, -3);
		lua_pushstring(L, "size");
		lua_pushnumber(L, fileinfo.size);
		lua_settable(L, -3);
		lua_pushstring(L, "attributes");
		lua_newtable(L);
		int index_attribute = 1;
		if (fileinfo.attrib & _A_ARCH)
		{
			lua_pushnumber(L, index_attribute);
			lua_pushnumber(L, FILEATTRIB_ARCH);
			lua_settable(L, -3);
			index_attribute++;
		}
		if (fileinfo.attrib & _A_HIDDEN)
		{
			lua_pushnumber(L, index_attribute);
			lua_pushnumber(L, FILEATTRIB_HIDDEN);
			lua_settable(L, -3);
			index_attribute++;
		}
		if (fileinfo.attrib & _A_NORMAL)
		{
			lua_pushnumber(L, index_attribute);
			lua_pushnumber(L, FILEATTRIB_NORMAL);
			lua_settable(L, -3);
			index_attribute++;
		}
		if (fileinfo.attrib & _A_RDONLY)
		{
			lua_pushnumber(L, index_attribute);
			lua_pushnumber(L, FILEATTRIB_RDONLY);
			lua_settable(L, -3);
			index_attribute++;
		}
		if (fileinfo.attrib & _A_SUBDIR)
		{
			lua_pushnumber(L, index_attribute);
			lua_pushnumber(L, FILEATTRIB_SUBDIR);
			lua_settable(L, -3);
			index_attribute++;
		}
		if (fileinfo.attrib & _A_SYSTEM)
		{
			lua_pushnumber(L, index_attribute);
			lua_pushnumber(L, FILEATTRIB_SYSTEM);
			lua_settable(L, -3);
			index_attribute++;
		}
		lua_settable(L, -3);
		lua_pushstring(L, "time");
		lua_newtable(L);
		lua_pushstring(L, "create");
		lua_pushnumber(L, fileinfo.time_create);
		lua_settable(L, -3);
		lua_pushstring(L, "access");
		lua_pushnumber(L, fileinfo.time_access);
		lua_settable(L, -3);
		lua_pushstring(L, "write");
		lua_pushnumber(L, fileinfo.time_write);
		lua_settable(L, -3);
		lua_settable(L, -3);
	}

#else

#endif

	return 1;
}


ETHER_API joinPath(lua_State* L)
{
	string path_1 = luaL_checkstring(L, 1);
	string path_2 = luaL_checkstring(L, 2);
	if (!path_1.empty() && (path_1[path_1.length() - 1] == '/' || path_1[path_1.length() - 1] == '\\'))
		path_1 = path_1.substr(0, path_1.length() - 1);
	if (path_2[0] == '/' || path_2[0] == '\\')
		path_2 = path_2.substr(1);

	lua_pushstring(L, path_1.empty() ? path_2.c_str() : path_1.append("\\").append(path_2).c_str());

	return 1;
}


ETHER_API getFileNameFromPath(lua_State* L)
{
	string path = luaL_checkstring(L, 1);
	string::size_type index_slash = path.find_last_of('/');
	string::size_type index_backslash = path.find_last_of('\\');

	if (index_slash == string::npos && index_backslash == string::npos)
	{
		lua_pushstring(L, path.c_str());
	}
	else if (index_slash != string::npos && index_backslash != string::npos)
	{
		lua_pushstring(L, path.substr((index_slash < index_backslash ? index_backslash : index_slash) + 1).c_str());
	}
	else
	{
		lua_pushstring(L, index_slash == string::npos ? path.substr(index_backslash + 1).c_str() : path.substr(index_slash + 1).c_str());
	}
	
	return 1;
}


ETHER_API getBasePathFromPath(lua_State* L)
{
	string path = luaL_checkstring(L, 1);
	string::size_type index_slash = path.find_last_of('/');
	string::size_type index_backslash = path.find_last_of('\\');

	if (index_slash == string::npos && index_backslash == string::npos)
	{
		lua_pushstring(L, path.c_str());
	}
	else if (index_slash != string::npos && index_backslash != string::npos)
	{
		lua_pushstring(L, path.substr(0, (index_slash < index_backslash ? index_backslash : index_slash) + 1).c_str());
	}
	else
	{
		lua_pushstring(L, index_slash == string::npos ? path.substr(0, index_backslash + 1).c_str() : path.substr(0, index_slash + 1).c_str());
	}

	return 1;
}


ModuleOS::ModuleOS(lua_State* L, string name) : Module(L, name)
{
	_vCMethods = {
		{ "GetBasePath", getBasePath },
		{ "SetClipboardText", setClipboardText },
		{ "GetClipboardText", getClipboardText },
		{ "GetPlatformType", getPlatformType },
		{ "GetSystemTotalRAM", getSystemTotalRAM },
		{ "ListDirectory", listDirectory },
		{ "IfPathExist", ifPathExist },
		{ "GetPathInfo", getPathInfo },
		{ "JoinPath", joinPath },
		{ "GetFileNameFromPath", getFileNameFromPath },
		{ "GetBasePathFromPath", getBasePathFromPath },
	};

	_vMacros = {
		{ "FILEATTRIB_ARCH", FILEATTRIB_ARCH },
		{ "FILEATTRIB_HIDDEN", FILEATTRIB_HIDDEN },
		{ "FILEATTRIB_NORMAL", FILEATTRIB_NORMAL },
		{ "FILEATTRIB_RDONLY", FILEATTRIB_RDONLY },
		{ "FILEATTRIB_SUBDIR", FILEATTRIB_SUBDIR },
		{ "FILEATTRIB_SYSTEM", FILEATTRIB_SYSTEM },

		{ "PATHMODE_FILE", PATHMODE_FILE },
		{ "PATHMODE_DIR", PATHMODE_DIR },
		{ "PATHMODE_FILEANDDIR", PATHMODE_FILEANDDIR },
	};
}