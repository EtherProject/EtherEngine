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
				{"SetDefaultHeaders", client_SetDefaultHeaders},
			}
		},
	};
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
	Headers headers;
	if (lua_istable(L, 3))
	{
		int index_header = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, index_header))
		{
#ifdef _ETHER_DEBUG_
			luaL_argcheck(L, lua_isstring(L, -1) && luaL_checkstring(L, -2), 3, 
				"the key and value of the headers table must be string");
#endif
			headers.insert(make_pair(lua_tostring(L, -2), lua_tostring(L, -1)));
			lua_pop(L, 1);
		}
	}

	PushResponseToStack(L, client->Get(luaL_checkstring(L, 2), headers));

	return 1;
}


ETHER_API client_Post(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif
	if (lua_istable(L, 3))
	{
		Params params;
		int index_param = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, index_param))
		{
#ifdef _ETHER_DEBUG_
			luaL_argcheck(L, lua_isstring(L, -1) && luaL_checkstring(L, -2), 3, 
				"the key and value of the params table must be string");
#endif
			params.emplace(lua_tostring(L, -2), lua_tostring(L, -1));
			lua_pop(L, 1);
		}
		PushResponseToStack(L, client->Post(luaL_checkstring(L, 2), params));
	}
	else if (lua_isstring(L, 3))
		PushResponseToStack(L, client->Post(
			luaL_checkstring(L, 2),
			lua_tostring(L, 3),
			lua_isstring(L, 4) ? lua_tostring(L, 4) : "application/x-www-form-urlencoded")
		);
	else
		luaL_argcheck(L, false, 4, "the argument to post must be string or table");

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
				"the key and value of the headers table must be string");
#endif
			headers.insert(make_pair(lua_tostring(L, -2), lua_tostring(L, -1)));
			lua_pop(L, 1);
		}
	}

	client->set_default_headers(headers);

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