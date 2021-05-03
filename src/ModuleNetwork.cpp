#include "ModuleNetwork.h"


ModuleNetwork& ModuleNetwork::Instance()
{
	static ModuleNetwork* _instance = new ModuleNetwork();
	return *_instance;
}


ModuleNetwork::ModuleNetwork()
{
	_vCMethods = {
		{ "CreateClient", createClient },
		{ "CloseClient", closeClient },
		{ "SplitLink", splitLink },
	};

	_vMacros = {
		{ "ERRCODE_SUCCESS", ERRCODE_SUCCESS },
		{ "ERRCODE_UNKNOWN", ERRCODE_UNKNOWN },
		{ "ERRCODE_CONNECTION", ERRCODE_CONNECTION },
		{ "ERRCODE_BINDIPADDRESS", ERRCODE_BINDIPADDRESS },
		{ "ERRCODE_READ", ERRCODE_READ },
		{ "ERRCODE_WRITE", ERRCODE_WRITE },
		{ "ERRCODE_EXCEEDREDRICTCOUNT", ERRCODE_EXCEEDREDRICTCOUNT },
		{ "ERRCODE_CANCELED", ERRCODE_CANCELED },
		{ "ERRCODE_SSLCONNECTION", ERRCODE_SSLCONNECTION },
		{ "ERRCODE_SSLLOADINGCERTS", ERRCODE_SSLLOADINGCERTS },
		{ "ERRCODE_SSLSERVERVERIFY", ERRCODE_SSLSERVERVERIFY },
		{ "ERRCODE_UNSUPPORTEDMBC", ERRCODE_UNSUPPORTEDMBC },
		{ "ERRCODE_COMPRESSION", ERRCODE_COMPRESSION },
	};

	_vMetaData = {
		{
			METANAME_CLIENT,
			{
				{"Get", client_Get},
				{"Post", client_Post},
				{"Put", client_Put},
				{"Patch", client_Patch},
				{"Delete", client_Delete},
				{"Options", client_Options},
				{"SetDefaultHeaders", client_SetDefaultHeaders},
				{"SetConnectTimeout", client_SetConnectTimeout},
				{"SetReadTimeout", client_SetReadTimeout},
				{"client_SetWriteTimeout", client_SetWriteTimeout},
			}
		},
	};
}


const char* GetRequestParamAtSecondPos(lua_State* L, RequestParam& reqParam)
{
	if (!lua_istable(L, 2)) return "request parameter must be table";
	else
	{
		lua_getfield(L, 2, "route");
		if (!lua_isstring(L, -1)) return "string field 'route' expected";
		reqParam.route = lua_tostring(L, -1);
		if (reqParam.route.empty() || (reqParam.route[0] != '/' && reqParam.route[0] != '\\'))
			reqParam.route = "/" + reqParam.route;
		lua_getfield(L, 2, "headers");
		if (!lua_isnil(L, -1))
		{
			if (!lua_istable(L, 2)) return "'headers' field must be table";
			int index_header = lua_gettop(L);
			lua_pushnil(L);
			while (lua_next(L, index_header))
			{
#ifdef _ETHER_DEBUG_
				luaL_argcheck(L, lua_isstring(L, -1) && luaL_checkstring(L, -2), 2,
					"key and value of 'headers' table must be string");
#endif
				reqParam.headers.insert(make_pair(lua_tostring(L, -2), lua_tostring(L, -1)));
				lua_pop(L, 1);
			}
		}
		lua_getfield(L, 2, "params");
		if (lua_isstring(L, -1))
			reqParam.str_params = lua_tostring(L, -1);
		else if (lua_istable(L, -1))
		{
			int index_param = lua_gettop(L);
			lua_pushnil(L);
			while (lua_next(L, index_param))
			{
#ifdef _ETHER_DEBUG_
				luaL_argcheck(L, lua_isstring(L, -1) && luaL_checkstring(L, -2), 2,
					"key and value of 'params' table must be string");
#endif
				reqParam.tab_params.emplace(lua_tostring(L, -2), lua_tostring(L, -1));
				lua_pop(L, 1);
			}
		}
		else
			return "'params' field must be string or table";
		lua_getfield(L, 2, "type");
#ifdef _ETHER_DEBUG_
		if (!lua_isnil(L, -1))
			if (lua_isstring(L, -1))
				reqParam.content_type = lua_tostring(L, -1);
			else
				return "'type' field must be string";
#else
		reqParam.content_type = lua_tostring(L, -1);
#endif

	}

	return nullptr;
}


int ConvertErrorCodeToMacro(const Error& error)
{
	switch (error)
	{
	case httplib::Success:
		return ERRCODE_SUCCESS;
		break;
	case httplib::Unknown:
		return ERRCODE_UNKNOWN;
		break;
	case httplib::Connection:
		return ERRCODE_CONNECTION;
		break;
	case httplib::BindIPAddress:
		return ERRCODE_BINDIPADDRESS;
		break;
	case httplib::Read:
		return ERRCODE_READ;
		break;
	case httplib::Write:
		return ERRCODE_WRITE;
		break;
	case httplib::ExceedRedirectCount:
		return ERRCODE_EXCEEDREDRICTCOUNT;
		break;
	case httplib::Canceled:
		return ERRCODE_CANCELED;
		break;
	case httplib::SSLConnection:
		return ERRCODE_SSLCONNECTION;
		break;
	case httplib::SSLLoadingCerts:
		return ERRCODE_SSLLOADINGCERTS;
		break;
	case httplib::SSLServerVerification:
		return ERRCODE_SSLSERVERVERIFY;
		break;
	case httplib::UnsupportedMultipartBoundaryChars:
		return ERRCODE_UNSUPPORTEDMBC;
		break;
	case httplib::Compression:
		return ERRCODE_COMPRESSION;
		break;
	default:
		break;
	}
}


void PushResponseToStack(lua_State* L, const Result& res)
{
	lua_newtable(L);

	lua_pushstring(L, "error");
	lua_pushinteger(L, ConvertErrorCodeToMacro(res.error()));
	lua_settable(L, -3);

	lua_pushstring(L, "status");
	if (res)
		lua_pushinteger(L, res->status);
	else
		lua_pushnil(L);
	lua_settable(L, -3);

	lua_pushstring(L, "body");
	if (res)
		lua_pushlstring(L, res->body.c_str(), res->body.size());
	else
		lua_pushnil(L);
	lua_settable(L, -3);

	lua_pushstring(L, "headers");
	if (res)
	{
		lua_newtable(L);
		for (auto kv : res->headers)
		{
			lua_pushstring(L, kv.first.c_str());
			lua_pushstring(L, kv.second.c_str());
			lua_settable(L, -3);
		}
	}
	else
		lua_pushnil(L);
	lua_settable(L, -3);
}


ETHER_API client_Get(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAtSecondPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);

	PushResponseToStack(L, reqParam.headers.empty() 
		? client->Get(reqParam.route.c_str()) 
		: client->Get(reqParam.route.c_str(), reqParam.headers)
	);

	return 1;
}


ETHER_API client_Post(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAtSecondPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);

	PushResponseToStack(L, reqParam.str_params.empty() 
		? (reqParam.headers.empty()
			? client->Post(reqParam.route.c_str(), reqParam.tab_params)
			: client->Post(reqParam.route.c_str(), reqParam.headers, reqParam.tab_params)
			)
		: (reqParam.headers.empty()
			? client->Post(reqParam.route.c_str(), reqParam.str_params.c_str(), reqParam.content_type.c_str())
			: client->Post(reqParam.route.c_str(), reqParam.headers, reqParam.str_params.c_str(), reqParam.content_type.empty() ? "application/x-www-form-urlencoded" : reqParam.content_type.c_str())
			)
	);

	return 1;
}


ETHER_API client_Put(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAtSecondPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);

	PushResponseToStack(L, reqParam.str_params.empty()
		? (reqParam.headers.empty()
			? client->Put(reqParam.route.c_str(), reqParam.tab_params)
			: client->Put(reqParam.route.c_str(), reqParam.headers, reqParam.tab_params)
			)
		: (reqParam.headers.empty()
			? client->Put(reqParam.route.c_str(), reqParam.str_params.c_str(), reqParam.content_type.c_str())
			: client->Put(reqParam.route.c_str(), reqParam.headers, reqParam.str_params.c_str(), reqParam.content_type.empty() ? "application/x-www-form-urlencoded" : reqParam.content_type.c_str())
			)
	);

	return 1;
}


ETHER_API client_Patch(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAtSecondPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !reqParam.str_params.empty(), 2, "'params' field must be string");
#endif
	PushResponseToStack(L, reqParam.headers.empty()
		? client->Patch(reqParam.route.c_str(), reqParam.str_params.c_str(), reqParam.content_type.c_str())
		: client->Patch(reqParam.route.c_str(), reqParam.headers, reqParam.str_params.c_str(), reqParam.content_type.empty() ? "application/x-www-form-urlencoded" : reqParam.content_type.c_str())
	);

	return 1;
}


ETHER_API client_Delete(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAtSecondPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !reqParam.str_params.empty(), 2, "'params' field must be string");
#endif
	PushResponseToStack(L, reqParam.headers.empty()
		? client->Delete(reqParam.route.c_str(), reqParam.str_params.c_str(), reqParam.content_type.c_str())
		: client->Delete(reqParam.route.c_str(), reqParam.headers, reqParam.str_params.c_str(), reqParam.content_type.empty() ? "application/x-www-form-urlencoded" : reqParam.content_type.c_str())
	);

	return 1;
}


ETHER_API client_Options(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAtSecondPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);

	PushResponseToStack(L, reqParam.headers.empty()
		? client->Options(reqParam.route.c_str())
		: client->Options(reqParam.route.c_str(), reqParam.headers)
	);

	return 1;
}


ETHER_API client_SetDefaultHeaders(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif
	Headers headers;
	if (lua_istable(L, 2))
	{
		int index_header = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, index_header))
		{
#ifdef _ETHER_DEBUG_
			luaL_argcheck(L, lua_isstring(L, -1) && luaL_checkstring(L, -2), 2, 
				"key and value of the headers table must be string");
#endif
			headers.insert(make_pair(lua_tostring(L, -2), lua_tostring(L, -1)));
			lua_pop(L, 1);
		}
	}

	client->set_default_headers(headers);

	return 0;
}


ETHER_API client_SetConnectTimeout(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_connection_timeout(0, luaL_checknumber(L, 1) * 1000);

	return 0;
}


ETHER_API client_SetReadTimeout(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_read_timeout(luaL_checknumber(L, 1), 0);

	return 0;
}


ETHER_API client_SetWriteTimeout(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_read_timeout(luaL_checknumber(L, 1), 0);

	return 0;
}


ETHER_API createClient(lua_State* L)
{
	string host = luaL_checkstring(L, 1);
	if (host.back() == '\\' || host.back() == '/')
		host.pop_back();
	Client* client = new Client(host.c_str());
	Client** uppClient = (Client**)lua_newuserdata(L, sizeof(Client*));
	*uppClient = client;
	luaL_getmetatable(L, METANAME_CLIENT);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API closeClient(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif
	delete client;
	client = nullptr;

	lua_pushnil(L);

	return 1;
}


ETHER_API splitLink(lua_State* L)
{
	string link = luaL_checkstring(L, 1), domain, route, param;

	if (!link.empty())
	{
		link.erase(0, link.find_first_not_of(" "));
		link.erase(link.find_last_not_of(" ") + 1);
	}

	domain = link.substr(0, 5) == "http:" || link.substr(0, 6) == "https:" ?
		link.substr(0, link.find_first_of("/", link.find_first_of("/") + 3))
		: link.find_first_of("/") == string::npos ? link : link.substr(0, link.find_first_of("/"));

	size_t index_quemark = link.find_first_of("?");

	index_quemark == string::npos ?
		(param = "", route = domain.size() == link.size() ? "/" : link.substr(domain.size()))
		: (param = link.substr(index_quemark + 1), route = link.substr(domain.size(), index_quemark - domain.size()));

	lua_pushstring(L, domain.c_str());
	lua_pushstring(L, route.c_str());
	lua_pushstring(L, param.c_str());

	return 3;
}