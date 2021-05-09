#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>

#define CPPHTTPLIB_ZLIB_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
using namespace httplib;

#include <vector>
#include <mutex>
using namespace std;

#define ERRCODE_SUCCESS						1354
#define ERRCODE_UNKNOWN						1355
#define ERRCODE_CONNECTION					1356
#define ERRCODE_BINDIPADDRESS				1357
#define ERRCODE_READ						1358
#define ERRCODE_WRITE						1359
#define ERRCODE_EXCEEDREDRICTCOUNT			1360
#define ERRCODE_CANCELED					1361
#define ERRCODE_SSLCONNECTION				1362
#define ERRCODE_SSLLOADINGCERTS				1363
#define ERRCODE_SSLSERVERVERIFY				1364
#define ERRCODE_UNSUPPORTEDMBC				1365
#define ERRCODE_COMPRESSION					1366

#define METANAME_CLIENT						"Network.Client"
#define METANAME_SERVER						"Network.Server"
#define METANAME_SERVER_REQ					"Network.Server.Request"
#define METANAME_SERVER_RES					"Network.Server.Response"

#define GetClientDataAtFirstPos()			(Client*)(*(void**)luaL_checkudata(L, 1, METANAME_CLIENT))
#define GetServerDataAtFirstPos()			(E_Server*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER))
#define GetServerReqDataAtFirstPos()		(Request*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER_REQ))
#define GetServerResDataAtFirstPos()		(Response*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER_RES))

#define CheckClientDataAtFirstPos(client)	luaL_argcheck(L, client, 1, "get client data failed")
#define CheckServerDataAtFirstPos(server)	luaL_argcheck(L, server && server->pServer, 1, "get server data failed")
#define CheckServerReqDataAtFirstPos(req)	luaL_argcheck(L, req, 1, "get request data failed")
#define CheckServerResDataAtFirstPos(res)	luaL_argcheck(L, res, 1, "get response data failed")

struct RequestParam
{
	string route;
	Headers headers;
	string str_params;
	Params tab_params;
	string content_type;
};

struct E_Server
{
	Server* pServer;
	string id;
	vector<string> refKeys;
	E_Server(Server* pServer, string id)
		: pServer(pServer), id(id) {}
};

class ModuleNetwork : public Module
{
public:
	static ModuleNetwork& Instance();
	static string GetServerID();
	~ModuleNetwork() {};

private:
	static size_t _stServerIndex;
	ModuleNetwork();

};

const char* GetRequestParamAtSecondPos(lua_State* L, RequestParam& reqParam);

/// <summary>
/// 将 Error 转换为宏
/// </summary>
/// <param name="error">Error</param>
/// <returns>宏</returns>
int ConvertErrorCodeToMacro(const Error& error);

/// <summary>
/// 将 response 压入 Lua 栈中
/// </summary>
/// <param name="error">Error</param>
/// <returns>宏</returns>
void PushResponseToStack(lua_State* L, const Result& res);

/*
* 使用 Get 方法请求某路由
* 2参数：客户端数据（userdata-Client），请求数据（table）结构如下：
*	{
*		route（string）：路由，
*		headers（table）：请求头（可选，默认为空或默认请求头）
*	}
* 1返回值：响应数据（table）结构如下：
*	{
*		error（number）：错误代码，
*		status（number）：状态码，失败则为 nil，
*		body（string）：响应数据，失败则为 nil，
*		headers（table）：响应头，失败则为 nil
*	}
*/
ETHER_API client_Get(lua_State* L);

/*
* 使用 Post 方法请求某路由
* 2参数：客户端数据（userdata-Client），请求数据（table）结构如下：
*	{
*		route（string）：路由，
*		headers（table）：请求头（可选，默认为空或默认请求头），
*		params（string/table）：请求参数（可选，默认为空），
*		type（string）：文档的 MIME Type（可选，默认为 “application/x-www-form-urlencoded”）
*	}
* 1返回值：响应数据（table）结构如下：
*	{
*		error（number）：错误代码，
*		status（number）：状态码，失败则为 nil，
*		body（string）：响应数据，失败则为 nil，
*		headers（table）：响应头，失败则为 nil
*	}
*/
ETHER_API client_Post(lua_State* L);

/*
* 使用 Put 方法请求某路由
* 2参数：客户端数据（userdata-Client），请求数据（table）结构如下：
*	{
*		route（string）：路由，
*		headers（table）：请求头（可选，默认为空或默认请求头），
*		params（string/table）：请求参数（可选，默认为空），
*		type（string）：文档的 MIME Type（可选，默认为 “application/x-www-form-urlencoded”）
*	}
* 1返回值：响应数据（table）结构如下：
*	{
*		error（number）：错误代码，
*		status（number）：状态码，失败则为 nil，
*		body（string）：响应数据，失败则为 nil，
*		headers（table）：响应头，失败则为 nil
*	}
*/
ETHER_API client_Put(lua_State* L);

/*
* 使用 Patch 方法请求某路由
* 2参数：客户端数据（userdata-Client），请求数据（table）结构如下：
*	{
*		route（string）：路由，
*		headers（table）：请求头（可选，默认为空或默认请求头），
*		params（string）：请求数据（可选，默认为空），
*		type（string）：文档的 MIME Type（可选，默认为 “application/x-www-form-urlencoded”）
*	}
* 1返回值：响应数据（table）结构如下：
*	{
*		error（number）：错误代码，
*		status（number）：状态码，失败则为 nil，
*		body（string）：响应数据，失败则为 nil，
*		headers（table）：响应头，失败则为 nil
*	}
*/
ETHER_API client_Patch(lua_State* L);

/*
* 使用 Delete 方法请求某路由
* 2参数：客户端数据（userdata-Client），请求数据（table）结构如下：
*	{
*		route（string）：路由，
*		headers（table）：请求头（可选，默认为空或默认请求头），
*		params（string）：请求参数（可选，默认为空），
*		type（string）：文档的 MIME Type（可选，默认为 “application/x-www-form-urlencoded”）
*	}
* 1返回值：响应数据（table）结构如下：
*	{
*		error（number）：错误代码，
*		status（number）：状态码，失败则为 nil，
*		body（string）：响应数据，失败则为 nil，
*		headers（table）：响应头，失败则为 nil
*	}
*/
ETHER_API client_Delete(lua_State* L);

/*
* 使用 Options 方法请求某路由
* 2参数：客户端数据（userdata-Client），请求数据（table）结构如下：
*	{
*		route（string）：路由，
*		headers（table）：请求头（可选，默认为空或默认请求头）
*	}
* 1返回值：响应数据（table）结构如下：
*	{
*		error（number）：错误代码，
*		status（number）：状态码，失败则为 nil，
*		body（string）：响应数据，失败则为 nil，
*		headers（table）：响应头，失败则为 nil
*	}
*/
ETHER_API client_Options(lua_State* L);

/*
* 设置客户端的默认请求头
* 2参数：客户端数据（userdata-Client），请求头（table，可选，默认为空）
* 0返回值
*/
ETHER_API client_SetDefaultHeaders(lua_State* L);

/*
* 设置客户端的连接超时时间
* 2参数：客户端数据（userdata-Client），超时时间（number，单位为毫秒）
* 0返回值
*/
ETHER_API client_SetConnectTimeout(lua_State* L);

/*
* 设置客户端的资源读取超时时间
* 2参数：客户端数据（userdata-Client），超时时间（number，单位为秒）
* 0返回值
*/
ETHER_API client_SetReadTimeout(lua_State* L);

/*
* 设置客户端的资源写入超时时间
* 2参数：客户端数据（userdata-Client），超时时间（number，单位为秒）
* 0返回值
*/
ETHER_API client_SetWriteTimeout(lua_State* L);

/*
* 设置客户端是否保持连接
* 2参数：客户端数据（userdata-Client），是否保持连接（boolean）
* 0返回值
*/
ETHER_API client_SetKeepAlive(lua_State* L);

/*
* 设置客户端是否跟随重定向
* 2参数：客户端数据（userdata-Client），是否跟随重定向（boolean）
* 0返回值
*/
ETHER_API client_SetFollowRedirect(lua_State* L);

/*
* 设置客户端是否压缩请求数据
* 2参数：客户端数据（userdata-Client），是否压缩（boolean）
* 0返回值
*/
ETHER_API client_SetCompressRequest(lua_State* L);

/*
* 设置客户端是否压缩响应数据
* 2参数：客户端数据（userdata-Client），是否压缩（boolean）
* 0返回值
*/
ETHER_API client_SetCompressResponse(lua_State* L);

/*
* 设置客户端 CACert 的 SSL 数字证书路径
* 2参数：客户端数据（userdata-Client），数字证书路径（string）
* 0返回值
*/
ETHER_API client_SetCACertPath(lua_State* L);

/*
* 设置客户端的代理主机
* 3参数：客户端数据（userdata-Client），代理主机地址（string），代理主机端口（number）
* 0返回值
*/
ETHER_API client_SetProxy(lua_State* L);

/*
* 创建客户端
* 1参数：主机地址（string）
* 1返回值：客户端数据（userdata-Client）
*/
ETHER_API createClient(lua_State* L);

/*
* 关闭指定客户端
* 1参数：客户端数据（userdata-Client）
* 1返回值：nil
*/
ETHER_API closeClient(lua_State* L);

/// <summary>
/// 回调函数代理
/// </summary>
/// <param name="req">请求数据对象</param>
/// <param name="res">响应数据对象</param>
/// <param name="L">Lua 虚拟机指针</param>
/// <param name="refKey">回调函数对象在注册表中的索引键</param>
/// <param name="err">异常信息</param>
void CallHandler(const Request& req, Response& res, lua_State* L, const string& refKey, const char* err = nullptr);

/*
* 获取请求方法
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：请求方法（string）
*/
ETHER_API request_GetMethod(lua_State* L);

ETHER_API request_GetRoute(lua_State* L);

ETHER_API request_GetHeaders(lua_State* L);

ETHER_API request_GetBody(lua_State* L);

ETHER_API request_GetRemoteAddress(lua_State* L);

ETHER_API request_GetRemotePort(lua_State* L);

ETHER_API request_GetVersion(lua_State* L);

ETHER_API request_GetParams(lua_State* L);

ETHER_API request_CheckHeaderExist(lua_State* L);

ETHER_API request_GetHeaderValue(lua_State* L);

ETHER_API request_GetHeaderValueCount(lua_State* L);

ETHER_API request_CheckParamExist(lua_State* L);

ETHER_API request_GetParamValue(lua_State* L);

ETHER_API request_GetParamValueCount(lua_State* L);



ETHER_API response_SetVersion(lua_State* L);

ETHER_API response_SetStatus(lua_State* L);

ETHER_API response_GetHeaders(lua_State* L);

ETHER_API response_SetBody(lua_State* L);

ETHER_API response_CheckHeaderExist(lua_State* L);

ETHER_API response_GetHeaderValue(lua_State* L);

ETHER_API response_GetHeaderValueCount(lua_State* L);

ETHER_API response_SetHeaderValue(lua_State* L);

ETHER_API response_SetHeaders(lua_State* L);

ETHER_API response_SetRedirect(lua_State* L);

ETHER_API response_SetContent(lua_State* L);





ETHER_API server_Get(lua_State* L);

ETHER_API server_SetExceptionHandler(lua_State* L);

ETHER_API server_SetMaxKeepAliveCount(lua_State* L);

ETHER_API server_SetKeepAliveTimeout(lua_State* L);

ETHER_API server_SetReadTimeout(lua_State* L);

ETHER_API server_SetWriteTimeout(lua_State* L);

ETHER_API server_SetIdleInterval(lua_State* L);

ETHER_API server_SetMaxRequestLength(lua_State* L);

ETHER_API server_BindToAnyPort(lua_State* L);

ETHER_API server_ListenAfterBind(lua_State* L);

ETHER_API server_Listen(lua_State* L);

ETHER_API server_Stop(lua_State* L);


ETHER_API createServer(lua_State* L);

ETHER_API closeServer(lua_State* L);

/*
* 将 HTTP/HTTPS 链接分割为：主机地址、路由和参数
* 1参数：HTTP/HTTPS 链接（string）
* 3返回值：主机地址（string，默认为空字符串），路由（string，默认为 “/”），参数（string，默认为空字符串）
*/
ETHER_API splitLink(lua_State* L);

#endif // !_NETWORK_H_

