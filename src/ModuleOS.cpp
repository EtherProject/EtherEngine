#include "ModuleOS.h"


ModuleOS& ModuleOS::Instance()
{
	static ModuleOS* _instance = new ModuleOS();
	return *_instance;
}


ModuleOS::ModuleOS()
{
	_vCMethods = {
		{ "GetBasePath", getBasePath },
		{ "SetClipboardText", setClipboardText },
		{ "GetClipboardText", getClipboardText },
		{ "GetPlatformType", getPlatformType },
		{ "GetCPUCount", getCPUCount },
		{ "GetSystemTotalRAM", getSystemTotalRAM },
		{ "GetAppStorageDirectory", getAppStorageDirectory },
		{ "GetSpecialPath", getSpecialPath },
		{ "GetPowerInfo", getPowerInfo },
		{ "ListDirectory", listDirectory },
		{ "CheckPathExist", checkPathExist },
		{ "GetPathInfo", getPathInfo },
		{ "JoinPath", joinPath },
		{ "SplitPath", splitPath },
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

		{ "POWERSTATE_UNKOWN", POWERSTATE_UNKOWN },
		{ "POWERSTATE_ONBATTERY", POWERSTATE_ONBATTERY },
		{ "POWERSTATE_NOBATTERY", POWERSTATE_NOBATTERY },
		{ "POWERSTATE_CHARGING", POWERSTATE_CHARGING },
		{ "POWERSTATE_CHARGEDN", POWERSTATE_CHARGEDN },

		{ "PATHATTRIB_DESKTOP", PATHATTRIB_DESKTOP },
		{ "PATHATTRIB_INTERNET", PATHATTRIB_INTERNET },
		{ "PATHATTRIB_PROGRAMS", PATHATTRIB_PROGRAMS },
		{ "PATHATTRIB_CONTROLS", PATHATTRIB_CONTROLS },
		{ "PATHATTRIB_PRINTERS", PATHATTRIB_PRINTERS },
		{ "PATHATTRIB_DOCUMENTS", PATHATTRIB_DOCUMENTS },
		{ "PATHATTRIB_FAVORITES", PATHATTRIB_FAVORITES },
		{ "PATHATTRIB_STARTUP", PATHATTRIB_STARTUP },
		{ "PATHATTRIB_RECENT", PATHATTRIB_RECENT },
		{ "PATHATTRIB_SENDTO", PATHATTRIB_SENDTO },
		{ "PATHATTRIB_RECYCLEBIN", PATHATTRIB_RECYCLEBIN },
		{ "PATHATTRIB_STARTMENU", PATHATTRIB_STARTMENU },
		{ "PATHATTRIB_MUSIC", PATHATTRIB_MUSIC },
		{ "PATHATTRIB_VIDEO", PATHATTRIB_VIDEO },
		{ "PATHATTRIB_DRIVES", PATHATTRIB_DRIVES },
		{ "PATHATTRIB_NETWORK", PATHATTRIB_NETWORK },
		{ "PATHATTRIB_NETHOOD", PATHATTRIB_NETHOOD },
		{ "PATHATTRIB_FONTS", PATHATTRIB_FONTS },
		{ "PATHATTRIB_TEMPLATES", PATHATTRIB_TEMPLATES },
		{ "PATHATTRIB_COMMON_STARTMENU", PATHATTRIB_COMMON_STARTMENU },
		{ "PATHATTRIB_COMMON_PROGRAMS", PATHATTRIB_COMMON_PROGRAMS },
		{ "PATHATTRIB_COMMON_STARTUP", PATHATTRIB_COMMON_STARTUP },
		{ "PATHATTRIB_COMMON_DESKTOP", PATHATTRIB_COMMON_DESKTOP },
		{ "PATHATTRIB_APPDATA", PATHATTRIB_APPDATA },
		{ "PATHATTRIB_PRINTHOOD", PATHATTRIB_PRINTHOOD },
		{ "PATHATTRIB_LOCAL_APPDATA", PATHATTRIB_LOCAL_APPDATA },
		{ "PATHATTRIB_COMMON_FAVORITES", PATHATTRIB_COMMON_FAVORITES },
		{ "PATHATTRIB_INTERNET_CACHE", PATHATTRIB_INTERNET_CACHE },
		{ "PATHATTRIB_COOKIES", PATHATTRIB_COOKIES },
		{ "PATHATTRIB_HISTORY", PATHATTRIB_HISTORY },
		{ "PATHATTRIB_COMMON_APPDATA", PATHATTRIB_COMMON_APPDATA },
		{ "PATHATTRIB_WINDOWS", PATHATTRIB_WINDOWS },
		{ "PATHATTRIB_SYSTEM", PATHATTRIB_SYSTEM },
		{ "PATHATTRIB_PROGRAM_FILES", PATHATTRIB_PROGRAM_FILES },
		{ "PATHATTRIB_PICTURES", PATHATTRIB_PICTURES },
		{ "PATHATTRIB_PROFILE", PATHATTRIB_PROFILE },
		{ "PATHATTRIB_SYSTEMX86", PATHATTRIB_SYSTEMX86 },
		{ "PATHATTRIB_PROGRAM_FILESX86", PATHATTRIB_PROGRAM_FILESX86 },
		{ "PATHATTRIB_PROGRAM_FILES_COMMON", PATHATTRIB_PROGRAM_FILES_COMMON },
		{ "PATHATTRIB_PROGRAM_FILES_COMMONX86", PATHATTRIB_PROGRAM_FILES_COMMONX86 },
		{ "PATHATTRIB_COMMON_TEMPLATES", PATHATTRIB_COMMON_TEMPLATES },
		{ "PATHATTRIB_COMMON_DOCUMENTS", PATHATTRIB_COMMON_DOCUMENTS },
		{ "PATHATTRIB_COMMON_ADMINTOOLS", PATHATTRIB_COMMON_ADMINTOOLS },
		{ "PATHATTRIB_ADMINTOOLS", PATHATTRIB_ADMINTOOLS },
		{ "PATHATTRIB_CONNECTIONS", PATHATTRIB_CONNECTIONS },
		{ "PATHATTRIB_COMMON_MUSIC", PATHATTRIB_COMMON_MUSIC },
		{ "PATHATTRIB_COMMON_PICTURES", PATHATTRIB_COMMON_PICTURES },
		{ "PATHATTRIB_COMMON_VIDEO", PATHATTRIB_COMMON_VIDEO },
		{ "PATHATTRIB_RESOURCES", PATHATTRIB_RESOURCES },
		{ "PATHATTRIB_RESOURCES_LOCALIZED", PATHATTRIB_RESOURCES_LOCALIZED },
		{ "PATHATTRIB_COMMON_OEM_LINKS", PATHATTRIB_COMMON_OEM_LINKS },
		{ "PATHATTRIB_CDBURN_AREA", PATHATTRIB_CDBURN_AREA },
		{ "PATHATTRIB_COMPUTERSNEARME", PATHATTRIB_COMPUTERSNEARME },
	};
}


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


ETHER_API getCPUCount(lua_State* L)
{
	lua_pushnumber(L, SDL_GetCPUCount());

	return 1;
}


ETHER_API getSystemTotalRAM(lua_State * L)
{
	lua_pushnumber(L, SDL_GetSystemRAM());

	return 1;
}


ETHER_API getAppStorageDirectory(lua_State* L)
{
	lua_pushstring(L, SDL_GetPrefPath(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API getSpecialPath(lua_State* L)
{
#ifdef __WINDOWS__

	TCHAR szPath[MAX_PATH];
	switch ((int)luaL_checknumber(L, 1))
	{
	case PATHATTRIB_DESKTOP:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_DESKTOP, FALSE);
		break;
	case PATHATTRIB_INTERNET:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_INTERNET, FALSE);
		break;
	case PATHATTRIB_PROGRAMS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PROGRAMS, FALSE);
		break;
	case PATHATTRIB_CONTROLS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_CONTROLS, FALSE);
		break;
	case PATHATTRIB_PRINTERS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PRINTERS, FALSE);
		break;
	case PATHATTRIB_DOCUMENTS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PERSONAL, FALSE);
		break;
	case PATHATTRIB_FAVORITES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_FAVORITES, FALSE);
		break;
	case PATHATTRIB_STARTUP:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_STARTUP, FALSE);
		break;
	case PATHATTRIB_RECENT:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_RECENT, FALSE);
		break;
	case PATHATTRIB_SENDTO:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_SENDTO, FALSE);
		break;
	case PATHATTRIB_RECYCLEBIN:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_BITBUCKET, FALSE);
		break;
	case PATHATTRIB_STARTMENU:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_STARTMENU, FALSE);
		break;
	case PATHATTRIB_MUSIC:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_MYMUSIC, FALSE);
		break;
	case PATHATTRIB_VIDEO:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_MYVIDEO, FALSE);
		break;
	case PATHATTRIB_DRIVES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_DRIVES, FALSE);
		break;
	case PATHATTRIB_NETWORK:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_NETWORK, FALSE);
		break;
	case PATHATTRIB_NETHOOD:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_NETHOOD, FALSE);
		break;
	case PATHATTRIB_FONTS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_FONTS, FALSE);
		break;
	case PATHATTRIB_TEMPLATES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_TEMPLATES, FALSE);
		break;
	case PATHATTRIB_COMMON_STARTMENU:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_STARTMENU, FALSE);
		break;
	case PATHATTRIB_COMMON_PROGRAMS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_PROGRAMS, FALSE);
		break;
	case PATHATTRIB_COMMON_STARTUP:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_STARTUP, FALSE);
		break;
	case PATHATTRIB_COMMON_DESKTOP:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_DESKTOPDIRECTORY, FALSE);
		break;
	case PATHATTRIB_APPDATA:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_APPDATA, FALSE);
		break;
	case PATHATTRIB_PRINTHOOD:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PRINTHOOD, FALSE);
		break;
	case PATHATTRIB_LOCAL_APPDATA:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_LOCAL_APPDATA, FALSE);
		break;
	case PATHATTRIB_COMMON_FAVORITES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_FAVORITES, FALSE);
		break;
	case PATHATTRIB_INTERNET_CACHE:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_INTERNET_CACHE, FALSE);
		break;
	case PATHATTRIB_COOKIES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COOKIES, FALSE);
		break;
	case PATHATTRIB_HISTORY:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_HISTORY, FALSE);
		break;
	case PATHATTRIB_COMMON_APPDATA:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_APPDATA, FALSE);
		break;
	case PATHATTRIB_WINDOWS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_WINDOWS, FALSE);
		break;
	case PATHATTRIB_SYSTEM:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_SYSTEM, FALSE);
		break;
	case PATHATTRIB_PROGRAM_FILES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PROGRAM_FILES, FALSE);
		break;
	case PATHATTRIB_PICTURES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_MYPICTURES, FALSE);
		break;
	case PATHATTRIB_PROFILE:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PROFILE, FALSE);
		break;
	case PATHATTRIB_SYSTEMX86:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_SYSTEMX86, FALSE);
		break;
	case PATHATTRIB_PROGRAM_FILESX86:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PROGRAM_FILESX86, FALSE);
		break;
	case PATHATTRIB_PROGRAM_FILES_COMMON:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PROGRAM_FILES_COMMON, FALSE);
		break;
	case PATHATTRIB_PROGRAM_FILES_COMMONX86:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_PROGRAM_FILES_COMMONX86, FALSE);
		break;
	case PATHATTRIB_COMMON_TEMPLATES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_TEMPLATES, FALSE);
		break;
	case PATHATTRIB_COMMON_DOCUMENTS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_DOCUMENTS, FALSE);
		break;
	case PATHATTRIB_COMMON_ADMINTOOLS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_ADMINTOOLS, FALSE);
		break;
	case PATHATTRIB_ADMINTOOLS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_ADMINTOOLS, FALSE);
		break;
	case PATHATTRIB_CONNECTIONS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_CONNECTIONS, FALSE);
		break;
	case PATHATTRIB_COMMON_MUSIC:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_MUSIC, FALSE);
		break;
	case PATHATTRIB_COMMON_PICTURES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_PICTURES, FALSE);
		break;
	case PATHATTRIB_COMMON_VIDEO:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_VIDEO, FALSE);
		break;
	case PATHATTRIB_RESOURCES:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_RESOURCES, FALSE);
		break;
	case PATHATTRIB_RESOURCES_LOCALIZED:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_RESOURCES_LOCALIZED, FALSE);
		break;
	case PATHATTRIB_COMMON_OEM_LINKS:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMMON_OEM_LINKS, FALSE);
		break;
	case PATHATTRIB_CDBURN_AREA:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_CDBURN_AREA, FALSE);
		break;
	case PATHATTRIB_COMPUTERSNEARME:
		SHGetSpecialFolderPath(nullptr, szPath, CSIDL_COMPUTERSNEARME, FALSE);
		break;
	default:
		luaL_error(L, "bad argument #1 to 'GetSpecialPath' (MACRO number expected, got %s)", luaL_typename(L, 1));
		break;
	}

	int iLen = WideCharToMultiByte(CP_ACP, 0, szPath, -1, nullptr, 0, nullptr, nullptr);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, szPath, -1, chRtn, iLen, nullptr, nullptr);
	lua_pushstring(L, chRtn);
	delete[] chRtn;

#else

#endif

	return 1;
}


ETHER_API getPowerInfo(lua_State* L)
{
	int secs, pct;
	lua_newtable(L);

	lua_pushstring(L, "state");
	switch (SDL_GetPowerInfo(&secs, &pct))
	{
	case SDL_POWERSTATE_UNKNOWN:
		lua_pushinteger(L, POWERSTATE_UNKOWN);
		break;
	case SDL_POWERSTATE_ON_BATTERY:
		lua_pushinteger(L, POWERSTATE_ONBATTERY);
		break;
	case SDL_POWERSTATE_NO_BATTERY:
		lua_pushinteger(L, POWERSTATE_NOBATTERY);
		break;
	case SDL_POWERSTATE_CHARGING:
		lua_pushinteger(L, POWERSTATE_CHARGING);
		break;
	case SDL_POWERSTATE_CHARGED:
		lua_pushinteger(L, POWERSTATE_CHARGEDN);
		break;
	default:
		break;
	}
	lua_settable(L, -3);

	lua_pushstring(L, "remain_time");
	lua_pushinteger(L, secs);
	lua_settable(L, -3);

	lua_pushstring(L, "remain_percentage");
	lua_pushinteger(L, pct);
	lua_settable(L, -3);

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


ETHER_API checkPathExist(lua_State* L)
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
			luaL_error(L, "bad argument #2 to 'CheckPathExist' (MACRO number expected, got %s)", luaL_typename(L, 2));
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


ETHER_API splitPath(lua_State* L)
{
	string path = luaL_checkstring(L, 1);
	string::size_type index_slash = path.find_last_of('/');
	string::size_type index_backslash = path.find_last_of('\\');

	if (index_slash == string::npos && index_backslash == string::npos)
	{
		bool isFolder = false;
		lua_pushstring(L, (isFolder = path.find('.') == string::npos) ? path.c_str() : "");
		lua_pushstring(L, isFolder ? "" : path.c_str());
	}
	else if (index_slash != string::npos && index_backslash != string::npos)
	{
		lua_pushstring(L, path.substr(0, (index_slash < index_backslash ? index_backslash : index_slash) + 1).c_str());
		lua_pushstring(L, path.substr((index_slash < index_backslash ? index_backslash : index_slash) + 1).c_str());
	}
	else
	{
		lua_pushstring(L, index_slash == string::npos ? path.substr(0, index_backslash + 1).c_str() : path.substr(0, index_slash + 1).c_str());
		lua_pushstring(L, index_slash == string::npos ? path.substr(index_backslash + 1).c_str() : path.substr(index_slash + 1).c_str());
	}

	return 2;
}