#include "EtherAPI.h"

using namespace std;

string strNameEntry = DEFAULTNAME_ENTRY;
vector<string> vStrPathList, vStrCPathList, vStrCmdList;

SDL_Event event;
SDL_Point pointCursorPos;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

lua_State* pL = luaL_newstate();

unordered_map<string, function<Module*()>> _mapMoudles = {
	{ MODULENAME_ALGORITHM, [] {return &ModuleAlgorithm::Instance();} },
	{ MODULENAME_GRAPHIC, [] {return &ModuleGraphic::Instance(); } },
	{ MODULENAME_INTERACTIVITY, [] {return &ModuleInteractivity::Instance(); } },
	{ MODULENAME_JSON, [] {return &ModuleJSON::Instance(); } },
	{ MODULENAME_MEDIA, [] {return &ModuleMedia::Instance(); } },
	{ MODULENAME_NETWORK, [] {return &ModuleNetwork::Instance(); } },
	{ MODULENAME_OS, [] {return &ModuleOS::Instance(); } },
	{ MODULENAME_STRING, [] {return &ModuleString::Instance(); } },
	{ MODULENAME_TIME, [] {return &ModuleTime::Instance(); } },
	{ MODULENAME_WINDOW, [] {return &ModuleWindow::Instance(); } },
	{ MODULENAME_COMPRESS, [] {return &ModuleCompress::Instance(); } },
	{ MODULENAME_XML, [] {return &ModuleXML::Instance(); } },
};


ETHER_API usingModule(lua_State* L)
{
	
	auto iter = _mapMoudles.find(luaL_checkstring(L, 1));
	if (iter != _mapMoudles.end())
	{
		Module* pModule = iter->second();
		pModule->PushMetaDataToGlobal(L);
		pModule->PushMoudleDataToStack(L);
	}	
	else
	{
		lua_getglobal(pL, "require");
		lua_pushstring(pL, lua_tostring(L, 1));
		lua_call(pL, 1, 1);
	}

	return 1;
}


ETHER_API getVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}


int _LoadConfig()
{
	ifstream fin("config.json");
	if (!fin.good())
		return CONFIGERROR_LOADING;

	stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

	cJSON* pJSONRoot = cJSON_Parse(ssContent.str().c_str());
	ssContent.clear();
	if (!(pJSONRoot && pJSONRoot->type == cJSON_Object))
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	cJSON* pJSONEntry, * pJSONPackage, * pJSONPath, * pJSONCPath, * pJSONCommand;
	if ((pJSONEntry = cJSON_GetObjectItem(pJSONRoot, "entry")) && pJSONEntry->type == cJSON_String && !string(pJSONEntry->valuestring).empty())
		strNameEntry = pJSONEntry->valuestring;
	else
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	if ((pJSONPackage = cJSON_GetObjectItem(pJSONRoot, "package")) && pJSONPackage->type == cJSON_Object)
	{
		if ((pJSONPath = cJSON_GetObjectItem(pJSONPackage, "path")) && pJSONPath->type == cJSON_Array)
			for (int i = 0; i < cJSON_GetArraySize(pJSONPath); i++)
			{
				cJSON* item = cJSON_GetArrayItem(pJSONPath, i);
				if (item && item->type == cJSON_String)
					vStrPathList.push_back(item->valuestring);
				else
				{
					cJSON_Delete(pJSONRoot);
					return CONFIGERROR_PARSING;
				}
			}
		if ((pJSONCPath = cJSON_GetObjectItem(pJSONPackage, "cpath")) && pJSONCPath->type == cJSON_Array)
			for (int i = 0; i < cJSON_GetArraySize(pJSONCPath); i++)
			{
				cJSON* item = cJSON_GetArrayItem(pJSONCPath, i);
				if (item && item->type == cJSON_String)
					vStrCPathList.push_back(item->valuestring);
				else
				{
					cJSON_Delete(pJSONRoot);
					return CONFIGERROR_PARSING;
				}
			}
	}
	else
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	if ((pJSONCommand = cJSON_GetObjectItem(pJSONRoot, "command")) && pJSONCommand->type == cJSON_Array)
		for (int i = 0; i < cJSON_GetArraySize(pJSONCommand); i++)
		{
			cJSON* item = cJSON_GetArrayItem(pJSONCommand, i);
			if (item && item->type == cJSON_String)
				vStrCmdList.push_back(item->valuestring);
			else
			{
				cJSON_Delete(pJSONRoot);
				return CONFIGERROR_PARSING;
			}
		}
	else
	{
		cJSON_Delete(pJSONRoot);
		return CONFIGERROR_PARSING;
	}

	lua_getglobal(pL, "package");

	lua_getfield(pL, -1, "path");
	string strPath = lua_tostring(pL, -1);
	for (string path : vStrPathList)
		strPath.append(";" + path);
	vector<string>().swap(vStrPathList);
	lua_pushstring(pL, strPath.c_str());
	lua_setfield(pL, -3, "path");
	lua_pop(pL, 1);

	lua_getfield(pL, -1, "cpath");
	string strCPath = lua_tostring(pL, -1);
	for (string cpath : vStrCPathList)
		strCPath.append(";" + cpath);
	vector<string>().swap(vStrCPathList);
	lua_pushstring(pL, strCPath.c_str());
	lua_setfield(pL, -3, "cpath");
	lua_pop(pL, 2);

	return CONFIGSUCCESS;
}


void _PushArgs(lua_State* L, int argc, char** argv, char** envp)
{
	lua_pushnumber(L, vStrCmdList.size() + argc);
	lua_setglobal(L, "_argc");

	lua_newtable(L);
	for (int i = 1; i < vStrCmdList.size() + 1; i++)
	{
		lua_pushnumber(L, i);
		lua_pushstring(L, vStrCmdList[i - 1].c_str());
		lua_settable(L, -3);
	}
	for (int i = vStrCmdList.size() + 1; i < vStrCmdList.size() + argc + 1; i++)
	{
		lua_pushnumber(L, i);
		lua_pushstring(L, argv[i - vStrCmdList.size() - 1]);
		lua_settable(L, -3);
	}
	vector<string>().swap(vStrCmdList);
	lua_setglobal(L, "_argv");

	lua_newtable(L);
	for (int i = 1; envp[i - 1]; i++)
	{
		string strEnvp = envp[i - 1];
		size_t stIndexEq = strEnvp.find_first_of('=');
		lua_pushstring(L, strEnvp.substr(0, stIndexEq).c_str());
		lua_pushstring(L, strEnvp.substr(stIndexEq + 1).c_str());
		lua_settable(L, -3);
	}
	lua_setglobal(L, "_envp");
}


void _HandleQuit()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

#undef main // SDL_main∫¶»À
int main(int argc, char** argv)
{
	luaL_openlibs(pL);

	lua_gc(pL, LUA_GCINC, 100);

#ifdef _ETHER_DEBUG_
	switch (_LoadConfig())
	{
	case CONFIGERROR_LOADING:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Load Configuration Failed", "Failed to load configuration file.\nProgram will run with the default configuration.\nDisable _ETHER_DEBUG_ to hide this warning.", nullptr);
		break;
	case CONFIGERROR_PARSING:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Parse Configuration Failed", "Failed to parse configuration file.\nProgram will run with the default configuration.\nDisable _ETHER_DEBUG_ to hide this warning.", nullptr);
		break;
	default:
		break;
	}
#else
	_LoadConfig();
#endif	

	SDL_Init(SDL_INIT_EVERYTHING);

	_PushArgs(pL, argc, argv, environ);

	lua_register(pL, "UsingModule", usingModule);
	lua_register(pL, "GetVersion", getVersion);

	try
	{
		if (luaL_dofile(pL, strNameEntry.c_str()))
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Scripts Run Failed", lua_tostring(pL, -1), nullptr);
	}
	catch (const std::exception& err)
	{
		SDL_SetClipboardText(err.what());
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Engine Crashed", 
			(string("A fatal error occurred, causing the engine to crash.\nThe error message has been copied to the clipboard.\nPlease contact the developer or submit an issue on GitHub.\n\nEmail:Voidmatrix@qq.com\nGitHub: https://github.com/VoidmatrixHeathcliff/EtherEngine\n\n[Error Message]\n") + err.what()).c_str(), 
			nullptr
		);
	}

	_HandleQuit();

	return 0;
}