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

#define GetClientDataAt1stPos()				(Client*)(*(void**)luaL_checkudata(L, 1, METANAME_CLIENT))
#define GetServerDataAt1stPos()				(E_Server*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER))
#define GetServerReqDataAt1stPos()			(Request*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER_REQ))
#define GetServerResDataAt1stPos()			(Response*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER_RES))

#define CheckClientDataAt1stPos(client)		luaL_argcheck(L, client, 1, "get client data failed")
#define CheckServerDataAt1stPos(server)		luaL_argcheck(L, server && server->pServer, 1, "get server data failed")
#define CheckServerReqDataAt1stPos(req)		luaL_argcheck(L, req, 1, "get request data failed")
#define CheckServerResDataAt1stPos(res)		luaL_argcheck(L, res, 1, "get response data failed")

#define CheckHandlerFunctionAt3rdPos()		luaL_argcheck(L, lua_isfunction(L, 3), 3, "callback handler must be function")

#define GetRouteAt2ndPosAndGenRefKey(server, route, refKey, cnt)\
	route = luaL_checkstring(L, 2);\
	if (route.empty() || route[0] != '/') route = "/" + route;\
	refKey = server->id + cnt + route;\
	server->refKeys.push_back(refKey);

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

/// <summary>
/// 将Lua栈中位于第二个参数位置的请求数据解析至结构体
/// </summary>
/// <param name="L">Lua虚拟机指针</param>
/// <param name="reqParam">接受数据的结构体</param>
/// <returns>错误信息</returns>
const char* GetRequestParamAt2ndPos(lua_State* L, RequestParam& reqParam);

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
* 客户端数据的GC函数
* 1参数：客户端数据（userdata-Client）
* 0返回值
*/
ETHER_API __gc_Client(lua_State* L);

/// <summary>
/// 服务端请求回调函数代理
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

/*
* 获取请求路由
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：请求路由（string）
*/
ETHER_API request_GetRoute(lua_State* L);

/*
* 获取请求头
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：请求头（table）
* 备注：由于Lua的table不支持一键多值，所以当请求头中一个键对应多个值时，
*	返回表中对应的键将保存最后一个值，请使用带索引参数的 GetHeaderValue 函数获取同一个键对应的不同值
*/
ETHER_API request_GetHeaders(lua_State* L);

/*
* 获取请求体
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：请求体（string）
*/
ETHER_API request_GetBody(lua_State* L);

/*
* 获取远程主机地址
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：主机地址（string）
*/
ETHER_API request_GetRemoteAddress(lua_State* L);

/*
* 获取远程主机端口
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：主机端口（number）
*/
ETHER_API request_GetRemotePort(lua_State* L);

/*
* 获取请求的HTTP版本
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：HTTP版本（number）
*/
ETHER_API request_GetVersion(lua_State* L);

/*
* 获取请求参数
* 1参数：请求数据对象数据（userdata-Request）
* 1返回值：请求参数（table）
* 备注：由于Lua的table不支持一键多值，所以当请求参数中一个键对应多个值时，
*	返回表中对应的键将保存最后一个值，请使用带索引参数的 GetParamValue 函数获取同一个键对应的不同值
*/
ETHER_API request_GetParams(lua_State* L);

/*
* 判断请求头中指定键是否存在
* 2参数：请求数据对象数据（userdata-Request），键（string）
* 1返回值：是否存在（boolean）
*/
ETHER_API request_CheckHeaderKeyExist(lua_State* L);

/*
* 获取请求头中指定键对应的值
* 2或3参数：请求数据对象数据（userdata-Request），键（string），索引（number，可选，默认为1）
* 1返回值：值（string）
*/
ETHER_API request_GetHeaderValue(lua_State* L);

/*
* 获取请求头中指定键对应的值的个数
* 2参数：请求数据对象数据（userdata-Request），键（string）
* 1返回值：值的个数（number）
*/
ETHER_API request_GetHeaderValueCount(lua_State* L);

/*
* 判断请求参数中指定键是否存在
* 2参数：请求数据对象数据（userdata-Request），键（string）
* 1返回值：是否存在（boolean）
*/
ETHER_API request_CheckParamKeyExist(lua_State* L);

/*
* 获取请求参数中指定键对应的值
* 2或3参数：请求数据对象数据（userdata-Request），键（string），索引（number，可选，默认为1）
* 1返回值：值（string）
*/
ETHER_API request_GetParamValue(lua_State* L);

/*
* 获取请求参数中指定键对应的值的个数
* 2参数：请求数据对象数据（userdata-Request），键（string）
* 1返回值：值的个数（number）
*/
ETHER_API request_GetParamValueCount(lua_State* L);

/*
* 设置响应的HTTP版本
* 2参数：响应数据对象数据（userdata-Response），HTTP版本（string）
* 0返回值
*/
ETHER_API response_SetVersion(lua_State* L);

/*
* 设置响应的状态码
* 2参数：响应数据对象数据（userdata-Response），状态码（number）
* 0返回值
*/
ETHER_API response_SetStatus(lua_State* L);

/*
* 获取响应头
* 1参数：响应数据对象数据（userdata-Response）
* 1返回值：响应头（table）
* 备注：由于Lua的table不支持一键多值，所以当响应头中一个键对应多个值时，
*	返回表中对应的键将保存最后一个值，请使用带索引参数的 GetHeaderValue 函数获取同一个键对应的不同值
*/
ETHER_API response_GetHeaders(lua_State* L);

/*
* 设置响应体
* 2参数：响应数据对象数据（userdata-Response），响应体（string）
* 0返回值
*/
ETHER_API response_SetBody(lua_State* L);

/*
* 判断响应头中指定键是否存在
* 2参数：响应数据对象数据（userdata-Response），键（string）
* 1返回值：是否存在（boolean）
*/
ETHER_API response_CheckHeaderKeyExist(lua_State* L);

/*
* 获取响应头中指定键对应的值
* 2或3参数：响应数据对象数据（userdata-Response），键（string），索引（number，可选，默认为1）
* 1返回值：值（string）
*/
ETHER_API response_GetHeaderValue(lua_State* L);

/*
* 获取响应头中指定键对应的值的个数
* 2参数：响应数据对象数据（userdata-Response），键（string）
* 1返回值：值的个数（number）
*/
ETHER_API response_GetHeaderValueCount(lua_State* L);

/*
* 设置响应头中指定键对应的值
* 3参数：响应数据对象数据（userdata-Response），键（string），值（string）
* 0返回值
*/
ETHER_API response_SetHeaderValue(lua_State* L);

/*
* 设置响应头
* 3参数：响应数据对象数据（userdata-Response），响应头（table）
* 0返回值
* 备注：由于Lua的table不支持一键多值，所以当响应头中一个键对应多个值时，
*	返回表中对应的键将保存最后一个值，请使用带索引参数的 SetHeaderValue 函数设置同一个键对应的不同值
*/
ETHER_API response_SetHeaders(lua_State* L);

/*
* 设置响应的重定向
* 2参数：响应数据对象数据（userdata-Response），重定向地址（string）
* 0返回值
*/
ETHER_API response_SetRedirect(lua_State* L);

/*
* 设置响应的内容
* 2或3参数：响应数据对象数据（userdata-Response），响应的内容（string），响应内容的MIME类型（string，可选，默认为 text/plain）
* 0返回值
*/
ETHER_API response_SetContent(lua_State* L);

/*
* 判断服务端是否创建成功
* 1参数：服务端数据（userdata-Server）
* 1返回值：是否创建成功（boolean）
*/
ETHER_API server_CheckValid(lua_State* L);

/*
* 判断服务端是否正在运行
* 1参数：服务端数据（userdata-Server）
* 1返回值：是否正在运行（boolean）
*/
ETHER_API server_CheckRunning(lua_State* L);

/*
* 配置服务端的Get请求路由及对应的回调函数
* 3参数：服务端数据（userdata-Server），路由（string），回调函数（function）
* 0返回值
* 备注：路由支持正则表达式；回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）
*/
ETHER_API server_Get(lua_State* L);

/*
* 配置服务端的Post请求路由及对应的回调函数
* 3参数：服务端数据（userdata-Server），路由（string），回调函数（function）
* 0返回值
* 备注：路由支持正则表达式；回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）
*/
ETHER_API server_Post(lua_State* L);

/*
* 配置服务端的Put请求路由及对应的回调函数
* 3参数：服务端数据（userdata-Server），路由（string），回调函数（function）
* 0返回值
* 备注：路由支持正则表达式；回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）
*/
ETHER_API server_Put(lua_State* L);

/*
* 配置服务端的Patch请求路由及对应的回调函数
* 3参数：服务端数据（userdata-Server），路由（string），回调函数（function）
* 0返回值
* 备注：路由支持正则表达式；回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）
*/
ETHER_API server_Patch(lua_State* L);

/*
* 配置服务端的Delete请求路由及对应的回调函数
* 3参数：服务端数据（userdata-Server），路由（string），回调函数（function）
* 0返回值
* 备注：路由支持正则表达式；回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）
*/
ETHER_API server_Delete(lua_State* L);

/*
* 配置服务端的Options请求路由及对应的回调函数
* 3参数：服务端数据（userdata-Server），路由（string），回调函数（function）
* 0返回值
* 备注：路由支持正则表达式；回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）
*/
ETHER_API server_Options(lua_State* L);

/*
* 添加服务端的静态资源挂载点
* 3参数：服务端数据（userdata-Server），挂载点（string），文件目录（string）
* 0返回值
*/
ETHER_API server_SetMountPoint(lua_State* L);

/*
* 移除服务端指定的静态资源挂载点
* 2参数：服务端数据（userdata-Server），挂载点（string）
* 0返回值
*/
ETHER_API server_RemoveMountPoint(lua_State* L);

/*
* 设置服务端的静态资源文件扩展名和响应的MIME类型映射
* 2参数：服务端数据（userdata-Server），静态资源文件扩展名（string），MIME类型（string）
* 0返回值
*/
ETHER_API server_SetFileExtMapToMIMEType(lua_State* L);

/*
* 设置服务端的异常处理函数
* 2参数：服务端数据（userdata-Server），异常处理回调函数（function）
* 0返回值
* 备注：回调函数接受3个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response），异常信息（string）
*/
ETHER_API server_SetExceptionHandler(lua_State* L);

/*
* 设置服务端的最大连接保持数
* 2参数：服务端数据（userdata-Server），最大链接保持数（number，默认为5）
* 0返回值
*/
ETHER_API server_SetMaxKeepAliveCount(lua_State* L);

/*
* 设置服务端的连接保持超时时间
* 2参数：服务端数据（userdata-Server），连接保持超时时间（number，单位为秒，默认为5）
* 0返回值
*/
ETHER_API server_SetKeepAliveTimeout(lua_State* L);

/*
* 设置服务端的资源读取超时时间
* 2参数：服务端数据（userdata-Server），超时时间（number，单位为秒）
* 0返回值
*/
ETHER_API server_SetReadTimeout(lua_State* L);

/*
* 设置服务端的资源写入超时时间
* 2参数：服务端数据（userdata-Server），超时时间（number，单位为秒）
* 0返回值
*/
ETHER_API server_SetWriteTimeout(lua_State* L);

/*
* 设置服务端的空闲间隔超时时间
* 2参数：服务端数据（userdata-Server），超时时间（number，单位为毫秒）
* 0返回值
*/
ETHER_API server_SetIdleInterval(lua_State* L);

/*
* 设置服务端接收的请求体数据的最大长度
* 2参数：服务端数据（userdata-Server），最大长度（number，单位为字节）
* 0返回值
*/
ETHER_API server_SetMaxRequestLength(lua_State* L);

/*
* 将当前服务端绑定到任意可用的端口上
* 1参数：服务端数据（userdata-Server）
* 1返回值：已绑定的端口号（number）
*/
ETHER_API server_BindToAnyPort(lua_State* L);

/*
* 启动已绑定端口的服务端的监听
* 1参数：服务端数据（userdata-Server）
* 0返回值
* 备注：服务端启动后将阻塞Lua主线程运行
*/
ETHER_API server_ListenAfterBind(lua_State* L);

/*
* 启动服务端监听
* 3参数：服务端数据（userdata-Server），主机地址（string），端口号（number）
* 0返回值
* 备注：服务端启动后将阻塞Lua主线程运行
*/
ETHER_API server_Listen(lua_State* L);

/*
* 停止服务端监听
* 1参数：服务端数据（userdata-Server）
* 0返回值
*/
ETHER_API server_Stop(lua_State* L);

/*
* 创建服务端
* 0或2参数：SSL服务端的证书文件路径（string，可选），SSL服务端的私钥文件路径（string，可选）
* 1返回值：客户端数据（userdata-Client）
* 备注：在不使用证书和私钥进行服务端创建的默认类型服务端不支持 HTTPS 协议 
*/
ETHER_API createServer(lua_State* L);

/*
* 服务端数据的GC函数
* 1参数：服务端数据（userdata-Server）
* 0返回值
*/
ETHER_API __gc_Server(lua_State* L);

/*
* 将 HTTP/HTTPS 链接分割为：主机地址、路由和参数
* 1参数：HTTP/HTTPS 链接（string）
* 3返回值：主机地址（string，默认为空字符串），路由（string，默认为 “/”），参数（string，默认为空字符串）
*/
ETHER_API splitLink(lua_State* L);

#endif // !_NETWORK_H_

