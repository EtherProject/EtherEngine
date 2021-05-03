#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>

#define CPPHTTPLIB_ZLIB_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
using namespace httplib;

#include <iostream>
using namespace std;

#define ERRCODE_SUCCESS				1354
#define ERRCODE_UNKNOWN				1355
#define ERRCODE_CONNECTION			1356
#define ERRCODE_BINDIPADDRESS		1357
#define ERRCODE_READ				1358
#define ERRCODE_WRITE				1359
#define ERRCODE_EXCEEDREDRICTCOUNT	1360
#define ERRCODE_CANCELED			1361
#define ERRCODE_SSLCONNECTION		1362
#define ERRCODE_SSLLOADINGCERTS		1363
#define ERRCODE_SSLSERVERVERIFY		1364
#define ERRCODE_UNSUPPORTEDMBC		1365
#define ERRCODE_COMPRESSION			1366

#define METANAME_CLIENT		"Network.Client"

#define GetClientDataAtFirstPos() (Client*)(*(void**)luaL_checkudata(L, 1, METANAME_CLIENT))

#define CheckClientDataAtFirstPos(client) luaL_argcheck(L, client, 1, "get client data failed")

struct RequestParam
{
	string route;
	Headers headers;
	string str_params;
	Params tab_params;
	string content_type;
};

class ModuleNetwork : public Module
{
public:
	static ModuleNetwork& Instance();
	~ModuleNetwork() {};

private:
	ModuleNetwork();

};

const char* GetRequestParamAtSecondPos(lua_State* L, RequestParam& reqParam);

/// <summary>
/// ½« Error ×ª»»Îªºê
/// </summary>
/// <param name="error">Error</param>
/// <returns>ºê</returns>
int ConvertErrorCodeToMacro(const Error& error);

void PushResponseToStack(lua_State* L, const Result& res);

ETHER_API client_Get(lua_State* L);

ETHER_API client_Post(lua_State* L);

ETHER_API client_Put(lua_State* L);

ETHER_API client_Patch(lua_State* L);

ETHER_API client_Delete(lua_State* L);

ETHER_API client_Options(lua_State* L);

ETHER_API client_SetDefaultHeaders(lua_State* L);

ETHER_API client_SetConnectTimeout(lua_State* L);

ETHER_API client_SetReadTimeout(lua_State* L);

ETHER_API client_SetWriteTimeout(lua_State* L);

ETHER_API client_SetKeepAlive(lua_State* L);

ETHER_API client_SetFollowRedirect(lua_State* L);

ETHER_API client_SetCompressRequest(lua_State* L);

ETHER_API client_SetCompressResopnse(lua_State* L);

ETHER_API client_SetCACertPath(lua_State* L);

ETHER_API createClient(lua_State* L);

ETHER_API closeClient(lua_State* L);

ETHER_API splitLink(lua_State* L);

#endif // !_NETWORK_H_

