#include "ModuleNetwork.h"


size_t ModuleNetwork::_stServerIndex = 0;

mutex mtxServer;


ModuleNetwork& ModuleNetwork::Instance()
{
	static ModuleNetwork* _instance = new ModuleNetwork();
	return *_instance;
}


string ModuleNetwork::GetServerID()
{
	return to_string(_stServerIndex++) + "_" + to_string(SDL_GetTicks());
}


ModuleNetwork::ModuleNetwork()
{
	_vCMethods = {
		{ "CreateClient", createClient },
		{ "CloseClient", closeClient },
		{ "CreateServer", createServer },
		{ "CloseServer", closeServer },
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
				{ "Get", client_Get },
				{ "Post", client_Post },
				{ "Put", client_Put },
				{ "Patch", client_Patch },
				{ "Delete", client_Delete },
				{ "Options", client_Options },
				{ "SetDefaultHeaders", client_SetDefaultHeaders },
				{ "SetConnectTimeout", client_SetConnectTimeout },
				{ "SetReadTimeout", client_SetReadTimeout },
				{ "SetWriteTimeout", client_SetWriteTimeout },
				{ "SetKeepAlive", client_SetKeepAlive },
				{ "SetFollowRedirect", client_SetFollowRedirect },
				{ "SetCompressRequest", client_SetCompressRequest },
				{ "SetCompressResponse", client_SetCompressResponse },
				{ "SetCACertPath", client_SetCACertPath },
				{ "SetProxy", client_SetProxy },
			}
		},
		{
			METANAME_SERVER,
			{
				{ "Get", server_Get },
				{ "SetExceptionHandler", server_SetExceptionHandler },
				{ "SetMaxKeepAliveCount", server_SetMaxKeepAliveCount },
				{ "SetKeepAliveTimeout", server_SetKeepAliveTimeout },
				{ "SetReadTimeout", server_SetReadTimeout },
				{ "SetWriteTimeout", server_SetWriteTimeout },
				{ "SetIdleInterval", server_SetIdleInterval },
				{ "SetMaxRequestLength", server_SetMaxRequestLength },
				{ "BindToAnyPort", server_BindToAnyPort },
				{ "ListenAfterBind", server_ListenAfterBind },
				{ "Listen", server_Listen },
				{ "Stop", server_Stop },
			}
		},
		{
			METANAME_SERVER_REQ,
			{
				{ "GetMethod", request_GetMethod },
				{ "GetRoute", request_GetRoute },
				{ "GetHeaders", request_GetHeaders },
				{ "GetBody", request_GetBody },
				{ "GetRemoteAddress", request_GetRemoteAddress },
				{ "GetRemotePort", request_GetRemotePort },
				{ "GetVersion", request_GetVersion },
				{ "GetParams", request_GetParams },
				{ "HasHeader", request_CheckHeaderExist },
				{ "GetHeaderValue", request_GetHeaderValue },
				{ "GetHeaderValueCount", request_GetHeaderValueCount },
				{ "HasParam", request_CheckParamExist },
				{ "GetParamValue", request_GetParamValue },
				{ "GetParamValueCount", request_GetParamValueCount },
			}
		},
		{
			METANAME_SERVER_RES,
			{
				{ "SetVersion", response_SetVersion },
				{ "SetStatus", response_SetStatus },
				{ "GetHeaders", response_GetHeaders },
				{ "SetBody", response_SetBody },
				{ "CheckHeaderExist", response_CheckHeaderExist },
				{ "GetHeaderValue", response_GetHeaderValue },
				{ "GetHeaderValueCount", response_GetHeaderValueCount },
				{ "SetHeaderValue", response_SetHeaderValue },
				{ "SetHeaders", response_SetHeaders },
				{ "SetRedirect", response_SetRedirect },
				{ "SetContent", response_SetContent },
			}
		}
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
		return httplib::Success;
		break;
	}
}


void PushResponseToStack(lua_State* L, const Result& res)
{
	lua_newtable(L);

	lua_pushstring(L, "error");
	lua_pushinteger(L, ConvertErrorCodeToMacro(res.error()));
	lua_settable(L, -3);

	if (res)
	{
		lua_pushstring(L, "status");
		lua_pushinteger(L, res->status);
		lua_settable(L, -3);
		
		lua_pushstring(L, "body");
		lua_pushlstring(L, res->body.c_str(), res->body.size());
		lua_settable(L, -3);

		lua_pushstring(L, "headers");
		lua_newtable(L);
		for (auto kv : res->headers)
		{
			lua_pushstring(L, kv.first.c_str());
			lua_pushstring(L, kv.second.c_str());
			lua_settable(L, -3);
		}
		lua_settable(L, -3);
	}	
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

	client->set_connection_timeout(0, luaL_checknumber(L, 2) * 1000);

	return 0;
}


ETHER_API client_SetReadTimeout(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_read_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API client_SetWriteTimeout(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_read_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API client_SetKeepAlive(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_keep_alive(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetFollowRedirect(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_follow_location(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetCompressRequest(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_compress(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetCompressResponse(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_decompress(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetCACertPath(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_ca_cert_path(luaL_checkstring(L, 2));

	return 0;
}


ETHER_API client_SetProxy(lua_State* L)
{
	Client* client = GetClientDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAtFirstPos(client);
#endif

	client->set_proxy(luaL_checkstring(L, 2), lua_tointeger(L, 3));

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


void CallHandler(const Request& req, Response& res, lua_State* L, const string& refKey, const char* err)
{
	mtxServer.lock();

	lua_getfield(L, LUA_REGISTRYINDEX, refKey.c_str());

	Request request = req;
	Request** uppRequest = (Request**)lua_newuserdata(L, sizeof(Request*));
	*uppRequest = &request;
	luaL_getmetatable(L, METANAME_SERVER_REQ);
	lua_setmetatable(L, -2);
	Response** uppResponse = (Response**)lua_newuserdata(L, sizeof(Response*));
	*uppResponse = &res;
	luaL_getmetatable(L, METANAME_SERVER_RES);
	lua_setmetatable(L, -2);
	if (err)
	{
		lua_pushstring(L, err);
		lua_call(L, 3, 0);
	}
	else
		lua_call(L, 2, 0);

	mtxServer.unlock();
}


ETHER_API request_GetMethod(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushstring(L, req->method.c_str());

	return 1;
}


ETHER_API request_GetRoute(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushstring(L, req->path.c_str());

	return 1;
}


ETHER_API request_GetHeaders(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_newtable(L);
	for (auto kv : req->headers)
	{
		lua_pushstring(L, kv.first.c_str());
		lua_pushstring(L, kv.second.c_str());
		lua_settable(L, -3);
	}

	return 1;
}


ETHER_API request_GetBody(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushlstring(L, req->body.c_str(), req->body.size());

	return 1;
}


ETHER_API request_GetRemoteAddress(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushstring(L, req->remote_addr.c_str());

	return 1;
}


ETHER_API request_GetRemotePort(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushinteger(L, req->remote_port);

	return 1;
}


ETHER_API request_GetVersion(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushstring(L, req->version.c_str());

	return 1;
}


ETHER_API request_GetParams(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_newtable(L);
	for (auto kv : req->params)
	{
		lua_pushstring(L, kv.first.c_str());
		lua_pushstring(L, kv.second.c_str());
		lua_settable(L, -3);
	}

	return 1;
}


ETHER_API request_CheckHeaderExist(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushboolean(L, req->has_header(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API request_GetHeaderValue(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushstring(L, req->get_header_value(luaL_checkstring(L, 2)).c_str());

	return 1;
}


ETHER_API request_GetHeaderValueCount(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushnumber(L, req->get_header_value_count(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API request_CheckParamExist(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushboolean(L, req->has_param(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API request_GetParamValue(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushstring(L, req->get_param_value(luaL_checkstring(L, 2)).c_str());

	return 1;
}


ETHER_API request_GetParamValueCount(lua_State* L)
{
	Request* req = GetServerReqDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAtFirstPos(req);
#endif
	lua_pushnumber(L, req->get_param_value_count(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API response_SetVersion(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	res->version = luaL_checkstring(L, 2);

	return 0;
}


ETHER_API response_SetStatus(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	res->status = luaL_checkinteger(L, 2);

	return 0;
}


ETHER_API response_GetHeaders(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	lua_newtable(L);
	for (auto kv : res->headers)
	{
		lua_pushstring(L, kv.first.c_str());
		lua_pushstring(L, kv.second.c_str());
		lua_settable(L, -3);
	}

	return 1;
}


ETHER_API response_SetBody(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	size_t len;
	const char* body = luaL_checklstring(L, 2, &len);
	res->body = string(body, len);

	return 0;
}


ETHER_API response_CheckHeaderExist(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	lua_pushboolean(L, res->has_header(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API response_GetHeaderValue(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	lua_pushstring(L, res->get_header_value(luaL_checkstring(L, 2)).c_str());

	return 1;
}


ETHER_API response_GetHeaderValueCount(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	lua_pushnumber(L, res->get_header_value_count(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API response_SetHeaderValue(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	res->set_header(luaL_checkstring(L, 2), luaL_checkstring(L, 3));

	return 0;
}


ETHER_API response_SetHeaders(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	luaL_argcheck(L, lua_istable(L, 2), 2, "headers must be table");
	Headers headers;
	int index_header = lua_gettop(L);
	lua_pushnil(L);
	while (lua_next(L, index_header))
	{
#ifdef _ETHER_DEBUG_
		luaL_argcheck(L, lua_isstring(L, -1) && luaL_checkstring(L, -2), 2,
			"key and value of 'headers' table must be string");
#endif
		headers.insert(make_pair(lua_tostring(L, -2), lua_tostring(L, -1)));
		lua_pop(L, 1);
	}
	res->headers = headers;

	return 0;
}


ETHER_API response_SetRedirect(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	res->set_redirect(luaL_checkstring(L, 2));

	return 0;
}


ETHER_API response_SetContent(lua_State* L)
{
	Response* res = GetServerResDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAtFirstPos(res);
#endif
	size_t len;
	res->set_content(luaL_checklstring(L, 2, &len), len, lua_isstring(L, 3) ? lua_tostring(L, 3) : "text/plain");

	return 0;
}


ETHER_API server_Get(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	string route = luaL_checkstring(L, 2);
	if (route.empty() || route[0] != '/') route = "/" + route;
	string refKey = server->id + "_get_" + route;
	server->refKeys.push_back(refKey);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, lua_isfunction(L, 3), 3, "callback handler must be function");
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Get(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallHandler(req, res, L, refKey);
		}
	);

	return 0;
}


ETHER_API server_SetExceptionHandler(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
	luaL_argcheck(L, lua_isfunction(L, 2), 2, "callback handler must be function");
#endif
	string refKey = server->id + "_error_handler";
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->set_exception_handler(
		[=](const Request& req, Response& res, std::exception& e) {
			CallHandler(req, res, L, refKey, e.what());
		}
	);

	return 0;
}


ETHER_API server_SetMaxKeepAliveCount(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->set_keep_alive_max_count(luaL_checknumber(L, 2));

	return 0;
}


ETHER_API server_SetKeepAliveTimeout(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->set_keep_alive_max_count(luaL_checknumber(L, 2));

	return 0;
}


ETHER_API server_SetReadTimeout(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->set_read_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API server_SetWriteTimeout(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->set_write_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API server_SetIdleInterval(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->set_idle_interval(0, luaL_checknumber(L, 2) * 1000);

	return 0;
}


ETHER_API server_SetMaxRequestLength(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->set_payload_max_length(luaL_checknumber(L, 2));

	return 0;
}


ETHER_API server_BindToAnyPort(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	lua_pushinteger(L, server->pServer->bind_to_any_port(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API server_ListenAfterBind(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->listen_after_bind();

	return 0;
}


ETHER_API server_Listen(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	const char* host = luaL_checkstring(L, 2);
	int port = luaL_checkinteger(L, 3);
	server->pServer->listen(host, port);

	return 0;
}


ETHER_API server_Stop(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	server->pServer->stop();

	return 0;
}


ETHER_API createServer(lua_State* L)
{
	E_Server* server = new E_Server(new Server(), ModuleNetwork::GetServerID());
	E_Server** uppServer = (E_Server**)lua_newuserdata(L, sizeof(E_Server*));
	*uppServer = server;
	luaL_getmetatable(L, METANAME_SERVER);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API closeServer(lua_State* L)
{
	E_Server* server = GetServerDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAtFirstPos(server);
#endif
	delete server->pServer;
	server->pServer = nullptr;
	for (string refKey : server->refKeys)
	{
		lua_pushnil(L);
		lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	}
	delete server;
	server = nullptr;
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