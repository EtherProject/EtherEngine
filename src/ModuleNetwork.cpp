#include "ModuleNetwork.h"

using namespace std;

size_t ModuleNetwork::_stServerIndex = 0;

unordered_map<int, int> ModuleNetwork::mapErrorList = {
	{ httplib::Success, ERRCODE_SUCCESS },
	{ httplib::Unknown, ERRCODE_UNKNOWN },
	{ httplib::Connection, ERRCODE_CONNECTION },
	{ httplib::BindIPAddress, ERRCODE_BINDIPADDRESS },
	{ httplib::Read, ERRCODE_READ },
	{ httplib::Write, ERRCODE_WRITE },
	{ httplib::ExceedRedirectCount, ERRCODE_EXCEEDREDRICTCOUNT },
	{ httplib::Canceled, ERRCODE_CANCELED },
	{ httplib::SSLConnection, ERRCODE_SSLCONNECTION },
	{ httplib::SSLLoadingCerts, ERRCODE_SSLLOADINGCERTS },
	{ httplib::SSLServerVerification, ERRCODE_SSLSERVERVERIFY },
	{ httplib::UnsupportedMultipartBoundaryChars, ERRCODE_UNSUPPORTEDMBC },
	{ httplib::Compression, ERRCODE_COMPRESSION },
};

mutex mtxServerRequest, mtxServerException;


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
		{ "CreateServer", createServer },
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
				{ "CheckValid", client_CheckValid },
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
			},
			__gc_Client
		},
		{
			METANAME_SERVER,
			{
				{ "CheckValid", server_CheckValid },
				{ "CheckRunning", server_CheckRunning },
				{ "Get", server_Get },
				{ "Post", server_Post },
				{ "Put", server_Put },
				{ "Patch", server_Patch },
				{ "Delete", server_Delete },
				{ "Options", server_Options },
				{ "SetMountPoint", server_SetMountPoint },
				{ "RemoveMountPoint", server_RemoveMountPoint },
				{ "SetFileExtMapToMIMEType", server_SetFileExtMapToMIMEType },
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
			},
			__gc_Server
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
				{ "CheckHeaderKeyExist", request_CheckHeaderKeyExist },
				{ "GetHeaderValue", request_GetHeaderValue },
				{ "GetHeaderValueCount", request_GetHeaderValueCount },
				{ "CheckParamKeyExist", request_CheckParamKeyExist },
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
				{ "CheckHeaderKeyExist", response_CheckHeaderKeyExist },
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


const char* GetRequestParamAt2ndPos(lua_State* L, RequestParam& reqParam)
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
	auto itor = ModuleNetwork::mapErrorList.find(error);
	if (itor != ModuleNetwork::mapErrorList.end())
		return itor->second;
	else
		return ERRCODE_UNKNOWN;
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


ETHER_API client_CheckValid(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif
	lua_pushboolean(L, client->is_valid());

	return 1;
}


ETHER_API client_Get(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAt2ndPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);

	PushResponseToStack(L, reqParam.headers.empty()
		? client->Get(reqParam.route.c_str())
		: client->Get(reqParam.route.c_str(), reqParam.headers)
	);

	return 1;
}


ETHER_API client_Post(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAt2ndPos(L, reqParam);
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
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAt2ndPos(L, reqParam);
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
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAt2ndPos(L, reqParam);
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
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAt2ndPos(L, reqParam);
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
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	RequestParam reqParam;
	const char* err = GetRequestParamAt2ndPos(L, reqParam);
	luaL_argcheck(L, !err, 2, err);

	PushResponseToStack(L, reqParam.headers.empty()
		? client->Options(reqParam.route.c_str())
		: client->Options(reqParam.route.c_str(), reqParam.headers)
	);

	return 1;
}


ETHER_API client_SetDefaultHeaders(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
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
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_connection_timeout(0, luaL_checknumber(L, 2) * 1000);

	return 0;
}


ETHER_API client_SetReadTimeout(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_read_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API client_SetWriteTimeout(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_read_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API client_SetKeepAlive(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_keep_alive(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetFollowRedirect(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_follow_location(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetCompressRequest(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_compress(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetCompressResponse(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_decompress(lua_toboolean(L, 2));

	return 0;
}


ETHER_API client_SetCACertPath(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif

	client->set_ca_cert_path(luaL_checkstring(L, 2));

	return 0;
}


ETHER_API client_SetProxy(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
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


ETHER_API __gc_Client(lua_State* L)
{
	Client* client = GetClientDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckClientDataAt1stPos(client);
#endif
	delete client;
	client = nullptr;

	return 0;
}


void CallRequestHandler(const Request& req, Response& res, lua_State* L, const string& refKey, const string& serverID)
{
	mtxServerRequest.lock();

	lua_getfield(L, LUA_REGISTRYINDEX, refKey.c_str());

	PushReqAndResToCallbackStack(req, res);

	if (lua_pcall(L, 2, 0, 0))
		CallExceptionHandler(req, res, L, GenExpHandlerRefKey(serverID), lua_tostring(L, -1));
		
	mtxServerRequest.unlock();
}


void CallExceptionHandler(const Request& req, Response& res, lua_State* L, const string& refKey, const string& errmsg)
{
	mtxServerException.lock();

	PushReqAndResToCallbackStack(req, res);

	if (lua_pcall(L, 3, 0, 0))
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unhandle Server Error ", lua_tostring(L, -1), nullptr);

	mtxServerException.unlock();
}


ETHER_API request_GetMethod(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushstring(L, req->method.c_str());

	return 1;
}


ETHER_API request_GetRoute(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushstring(L, req->path.c_str());

	return 1;
}


ETHER_API request_GetHeaders(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
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
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushlstring(L, req->body.c_str(), req->body.size());

	return 1;
}


ETHER_API request_GetRemoteAddress(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushstring(L, req->remote_addr.c_str());

	return 1;
}


ETHER_API request_GetRemotePort(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushinteger(L, req->remote_port);

	return 1;
}


ETHER_API request_GetVersion(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushstring(L, req->version.c_str());

	return 1;
}


ETHER_API request_GetParams(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
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


ETHER_API request_CheckHeaderKeyExist(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushboolean(L, req->has_header(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API request_GetHeaderValue(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif

	lua_pushstring(L, req->get_header_value(luaL_checkstring(L, 2), lua_isnumber(L, 3) ? lua_tonumber(L, 3) - 1 : 0).c_str());

	return 1;
}


ETHER_API request_GetHeaderValueCount(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushnumber(L, req->get_header_value_count(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API request_CheckParamKeyExist(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushboolean(L, req->has_param(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API request_GetParamValue(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushstring(L, req->get_param_value(luaL_checkstring(L, 2), lua_isnumber(L, 3) ? lua_tonumber(L, 3) - 1 : 0).c_str());

	return 1;
}


ETHER_API request_GetParamValueCount(lua_State* L)
{
	Request* req = GetServerReqDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerReqDataAt1stPos(req);
#endif
	lua_pushnumber(L, req->get_param_value_count(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API response_SetVersion(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	res->version = luaL_checkstring(L, 2);

	return 0;
}


ETHER_API response_SetStatus(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	res->status = luaL_checkinteger(L, 2);

	return 0;
}


ETHER_API response_GetHeaders(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
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
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	size_t len;
	const char* body = luaL_checklstring(L, 2, &len);
	res->body = string(body, len);

	return 0;
}


ETHER_API response_CheckHeaderKeyExist(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	lua_pushboolean(L, res->has_header(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API response_GetHeaderValue(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	lua_pushstring(L, res->get_header_value(luaL_checkstring(L, 2), lua_isnumber(L, 3) ? lua_tonumber(L, 3) - 1 : 0).c_str());

	return 1;
}


ETHER_API response_GetHeaderValueCount(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	lua_pushnumber(L, res->get_header_value_count(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API response_SetHeaderValue(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	res->set_header(luaL_checkstring(L, 2), luaL_checkstring(L, 3));

	return 0;
}


ETHER_API response_SetHeaders(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
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
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	res->set_redirect(luaL_checkstring(L, 2));

	return 0;
}


ETHER_API response_SetContent(lua_State* L)
{
	Response* res = GetServerResDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerResDataAt1stPos(res);
#endif
	size_t len;
	res->set_content(luaL_checklstring(L, 2, &len), len, lua_isstring(L, 3) ? lua_tostring(L, 3) : "text/plain");

	return 0;
}


ETHER_API server_CheckValid(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	lua_pushboolean(L, server->pServer->is_valid());

	return 1;
}


ETHER_API server_CheckRunning(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	lua_pushboolean(L, server->pServer->is_running());

	return 1;
}


ETHER_API server_Get(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string route, refKey;
	GetRouteAt2ndPosAndGenRefKey(server, route, refKey, "_get_");
#ifdef _ETHER_DEBUG_
	CheckHandlerFunctionAt3rdPos();
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Get(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallRequestHandler(req, res, L, refKey, server->id);
		}
	);

	return 0;
}


ETHER_API server_Post(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string route, refKey;
	GetRouteAt2ndPosAndGenRefKey(server, route, refKey, "_post_");
#ifdef _ETHER_DEBUG_
	CheckHandlerFunctionAt3rdPos();
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Post(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallRequestHandler(req, res, L, refKey, server->id);
		}
	);

	return 0;
}


ETHER_API server_Put(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string route, refKey;
	GetRouteAt2ndPosAndGenRefKey(server, route, refKey, "_put_");
#ifdef _ETHER_DEBUG_
	CheckHandlerFunctionAt3rdPos();
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Put(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallRequestHandler(req, res, L, refKey, server->id);
		}
	);

	return 0;
}


ETHER_API server_Patch(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string route, refKey;
	GetRouteAt2ndPosAndGenRefKey(server, route, refKey, "_patch_");
#ifdef _ETHER_DEBUG_
	CheckHandlerFunctionAt3rdPos();
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Patch(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallRequestHandler(req, res, L, refKey, server->id);
		}
	);

	return 0;
}


ETHER_API server_Delete(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string route, refKey;
	GetRouteAt2ndPosAndGenRefKey(server, route, refKey, "_delete_");
#ifdef _ETHER_DEBUG_
	CheckHandlerFunctionAt3rdPos();
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Delete(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallRequestHandler(req, res, L, refKey, server->id);
		}
	);

	return 0;
}


ETHER_API server_Options(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string route, refKey;
	GetRouteAt2ndPosAndGenRefKey(server, route, refKey, "_options_");
#ifdef _ETHER_DEBUG_
	CheckHandlerFunctionAt3rdPos();
#endif
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->Options(
		route.c_str(),
		[=](const Request& req, Response& res) {
			CallRequestHandler(req, res, L, refKey, server->id);
		}
	);

	return 0;
}


ETHER_API server_SetMountPoint(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string mount = luaL_checkstring(L, 2);
	if (mount.empty() || mount[0] != '/') mount = "/" + mount;
	server->pServer->set_mount_point(mount.c_str(), luaL_checkstring(L, 3));

	return 0;
}


ETHER_API server_RemoveMountPoint(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	string mount = luaL_checkstring(L, 2);
	if (mount.empty() || mount[0] != '/') mount = "/" + mount;
	server->pServer->remove_mount_point(mount.c_str());

	return 0;
}


ETHER_API server_SetFileExtMapToMIMEType(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_file_extension_and_mimetype_mapping(luaL_checkstring(L, 2), luaL_checkstring(L, 3));

	return 0;
}


ETHER_API server_SetExceptionHandler(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
	luaL_argcheck(L, lua_isfunction(L, 2), 2, "callback handler must be function");
#endif
	string refKey = GenExpHandlerRefKey(server->id);
	lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	server->pServer->set_exception_handler(
		[=](const Request& req, Response& res, std::exception& e) {
			CallRequestHandler(req, res, L, refKey, e.what());
		}
	);

	return 0;
}


ETHER_API server_SetMaxKeepAliveCount(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_keep_alive_max_count(luaL_checknumber(L, 2));

	return 0;
}


ETHER_API server_SetKeepAliveTimeout(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_keep_alive_timeout(luaL_checknumber(L, 2));

	return 0;
}


ETHER_API server_SetReadTimeout(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_read_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API server_SetWriteTimeout(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_write_timeout(luaL_checknumber(L, 2), 0);

	return 0;
}


ETHER_API server_SetIdleInterval(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_idle_interval(0, luaL_checknumber(L, 2) * 1000);

	return 0;
}


ETHER_API server_SetMaxRequestLength(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->set_payload_max_length(luaL_checknumber(L, 2));

	return 0;
}


ETHER_API server_BindToAnyPort(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	lua_pushinteger(L, server->pServer->bind_to_any_port(luaL_checkstring(L, 2)));

	return 1;
}


ETHER_API server_ListenAfterBind(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->listen_after_bind();

	return 0;
}


ETHER_API server_Listen(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->listen(luaL_checkstring(L, 2), luaL_checkinteger(L, 3));

	return 0;
}


ETHER_API server_Stop(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	server->pServer->stop();

	return 0;
}


ETHER_API createServer(lua_State* L)
{
	E_Server* server = new E_Server(
		lua_isstring(L, 1) 
		? new SSLServer(lua_tostring(L, 1), luaL_checkstring(L, 2)) 
		: new Server(), ModuleNetwork::GetServerID()
	);
	E_Server** uppServer = (E_Server**)lua_newuserdata(L, sizeof(E_Server*));
	*uppServer = server;
	luaL_getmetatable(L, METANAME_SERVER);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API __gc_Server(lua_State* L)
{
	E_Server* server = GetServerDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckServerDataAt1stPos(server);
#endif
	delete server->pServer;
	server->pServer = nullptr;
	for (string refKey : server->refKeys)
	{
		lua_pushnil(L);
		lua_setfield(L, LUA_REGISTRYINDEX, refKey.c_str());
	}
	delete server;

	return 0;
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