#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>
#include <SDL2/SDL.h>

#define CPPHTTPLIB_ZLIB_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
using namespace httplib;

#include <vector>
#include <mutex>
#include <unordered_map>


#define ERRCODE_SUCCESS							1354
#define ERRCODE_UNKNOWN							1355
#define ERRCODE_CONNECTION						1356
#define ERRCODE_BINDIPADDRESS					1357
#define ERRCODE_READ							1358
#define ERRCODE_WRITE							1359
#define ERRCODE_EXCEEDREDRICTCOUNT				1360
#define ERRCODE_CANCELED						1361
#define ERRCODE_SSLCONNECTION					1362
#define ERRCODE_SSLLOADINGCERTS					1363
#define ERRCODE_SSLSERVERVERIFY					1364
#define ERRCODE_UNSUPPORTEDMBC					1365
#define ERRCODE_COMPRESSION						1366

#define METANAME_CLIENT							"Network.Client"
#define METANAME_SERVER							"Network.Server"
#define METANAME_SERVER_REQ						"Network.Server.Request"
#define METANAME_SERVER_RES						"Network.Server.Response"

#define GetClientDataAt1stPos()					(Client*)(*(void**)luaL_checkudata(L, 1, METANAME_CLIENT))
#define GetServerDataAt1stPos()					(E_Server*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER))
#define GetServerReqDataAt1stPos()				(Request*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER_REQ))
#define GetServerResDataAt1stPos()				(Response*)(*(void**)luaL_checkudata(L, 1, METANAME_SERVER_RES))

#define CheckClientDataAt1stPos(client)			luaL_argcheck(L, client, 1, "get client data failed")
#define CheckServerDataAt1stPos(server)			luaL_argcheck(L, server && server->pServer, 1, "get server data failed")
#define CheckServerReqDataAt1stPos(req)			luaL_argcheck(L, req, 1, "get request data failed")
#define CheckServerResDataAt1stPos(res)			luaL_argcheck(L, res, 1, "get response data failed")

#define CheckHandlerFunctionAt3rdPos()			luaL_argcheck(L, lua_isfunction(L, 3) && lua_gettop(L) == 3,\
													3, "the last param callback handler must be function")

#define GenReqHandlerRefKey(id, route, type)	id + type + route
#define GenExpHandlerRefKey(id)					id + "_error_handler"
#define GetRouteAt2ndPosAndGenRefKey(server, route, refKey, type)\
	route = luaL_checkstring(L, 2);\
	if (route.empty() || route[0] != '/') route = "/" + route;\
	refKey = GenReqHandlerRefKey(server->id, route, type);\
	server->refKeys.push_back(refKey);

#define PushReqAndResToCallbackStack(req, res)\
	Request request = req;\
	Request** uppRequest = (Request**)lua_newuserdata(L, sizeof(Request*));\
	*uppRequest = &request;\
	luaL_getmetatable(L, METANAME_SERVER_REQ);\
	lua_setmetatable(L, -2);\
	Response** uppResponse = (Response**)lua_newuserdata(L, sizeof(Response*));\
	*uppResponse = &res;\
	luaL_getmetatable(L, METANAME_SERVER_RES);\
	lua_setmetatable(L, -2);

struct RequestParam
{
	std::string route;
	Headers headers;
	std::string str_params;
	Params tab_params;
	std::string content_type;
};

struct E_Server
{
	Server* pServer;
	std::string id;
	std::vector<std::string> refKeys;
	E_Server(Server* pServer, const std::string& id)
		: pServer(pServer), id(id) {}
};

class ModuleNetwork : public Module
{
public:
	static std::unordered_map<int, int> mapErrorList;
	static ModuleNetwork& Instance();
	static std::string GetServerID();
	~ModuleNetwork() {};

private:
	static size_t _stServerIndex;
	ModuleNetwork();

};

/// <summary>
/// ��Luaջ��λ�ڵڶ�������λ�õ��������ݽ������ṹ��
/// </summary>
/// <param name="L">Lua�����ָ��</param>
/// <param name="reqParam">�������ݵĽṹ��</param>
/// <returns>������Ϣ</returns>
const char* GetRequestParamAt2ndPos(lua_State* L, RequestParam& reqParam);

/// <summary>
/// �� ErrorCode ת��Ϊ��
/// </summary>
/// <param name="error">ErrorCode</param>
/// <returns>��</returns>
inline int ConvertErrorCodeToMacro(const Error& error);

/// <summary>
/// �� response ѹ�� Lua ջ��
/// </summary>
/// <param name="error">Error</param>
/// <returns>��</returns>
void PushResponseToStack(lua_State* L, const Result& res);

/*
* �жϿͻ����Ƿ񴴽��ɹ�
* 1�������ͻ������ݣ�userdata-Client��
* 1����ֵ���Ƿ񴴽��ɹ���boolean��
*/
ETHER_API client_CheckValid(lua_State* L);

/*
* ʹ�� Get ��������ĳ·��
* 2�������ͻ������ݣ�userdata-Client�����������ݣ�table���ṹ���£�
*	{
*		route��string����·�ɣ�
*		headers��table��������ͷ����ѡ��Ĭ��Ϊ�ջ�Ĭ������ͷ��
*	}
* 1����ֵ����Ӧ���ݣ�table���ṹ���£�
*	{
*		error��number����������룬
*		status��number����״̬�룬ʧ����Ϊ nil��
*		body��string������Ӧ���ݣ�ʧ����Ϊ nil��
*		headers��table������Ӧͷ��ʧ����Ϊ nil
*	}
*/
ETHER_API client_Get(lua_State* L);

/*
* ʹ�� Post ��������ĳ·��
* 2�������ͻ������ݣ�userdata-Client�����������ݣ�table���ṹ���£�
*	{
*		route��string����·�ɣ�
*		headers��table��������ͷ����ѡ��Ĭ��Ϊ�ջ�Ĭ������ͷ����
*		params��string/table���������������ѡ��Ĭ��Ϊ�գ���
*		type��string�����ĵ��� MIME Type����ѡ��Ĭ��Ϊ ��application/x-www-form-urlencoded����
*	}
* 1����ֵ����Ӧ���ݣ�table���ṹ���£�
*	{
*		error��number����������룬
*		status��number����״̬�룬ʧ����Ϊ nil��
*		body��string������Ӧ���ݣ�ʧ����Ϊ nil��
*		headers��table������Ӧͷ��ʧ����Ϊ nil
*	}
*/
ETHER_API client_Post(lua_State* L);

/*
* ʹ�� Put ��������ĳ·��
* 2�������ͻ������ݣ�userdata-Client�����������ݣ�table���ṹ���£�
*	{
*		route��string����·�ɣ�
*		headers��table��������ͷ����ѡ��Ĭ��Ϊ�ջ�Ĭ������ͷ����
*		params��string/table���������������ѡ��Ĭ��Ϊ�գ���
*		type��string�����ĵ��� MIME Type����ѡ��Ĭ��Ϊ ��application/x-www-form-urlencoded����
*	}
* 1����ֵ����Ӧ���ݣ�table���ṹ���£�
*	{
*		error��number����������룬
*		status��number����״̬�룬ʧ����Ϊ nil��
*		body��string������Ӧ���ݣ�ʧ����Ϊ nil��
*		headers��table������Ӧͷ��ʧ����Ϊ nil
*	}
*/
ETHER_API client_Put(lua_State* L);

/*
* ʹ�� Patch ��������ĳ·��
* 2�������ͻ������ݣ�userdata-Client�����������ݣ�table���ṹ���£�
*	{
*		route��string����·�ɣ�
*		headers��table��������ͷ����ѡ��Ĭ��Ϊ�ջ�Ĭ������ͷ����
*		params��string�����������ݣ���ѡ��Ĭ��Ϊ�գ���
*		type��string�����ĵ��� MIME Type����ѡ��Ĭ��Ϊ ��application/x-www-form-urlencoded����
*	}
* 1����ֵ����Ӧ���ݣ�table���ṹ���£�
*	{
*		error��number����������룬
*		status��number����״̬�룬ʧ����Ϊ nil��
*		body��string������Ӧ���ݣ�ʧ����Ϊ nil��
*		headers��table������Ӧͷ��ʧ����Ϊ nil
*	}
*/
ETHER_API client_Patch(lua_State* L);

/*
* ʹ�� Delete ��������ĳ·��
* 2�������ͻ������ݣ�userdata-Client�����������ݣ�table���ṹ���£�
*	{
*		route��string����·�ɣ�
*		headers��table��������ͷ����ѡ��Ĭ��Ϊ�ջ�Ĭ������ͷ����
*		params��string���������������ѡ��Ĭ��Ϊ�գ���
*		type��string�����ĵ��� MIME Type����ѡ��Ĭ��Ϊ ��application/x-www-form-urlencoded����
*	}
* 1����ֵ����Ӧ���ݣ�table���ṹ���£�
*	{
*		error��number����������룬
*		status��number����״̬�룬ʧ����Ϊ nil��
*		body��string������Ӧ���ݣ�ʧ����Ϊ nil��
*		headers��table������Ӧͷ��ʧ����Ϊ nil
*	}
*/
ETHER_API client_Delete(lua_State* L);

/*
* ʹ�� Options ��������ĳ·��
* 2�������ͻ������ݣ�userdata-Client�����������ݣ�table���ṹ���£�
*	{
*		route��string����·�ɣ�
*		headers��table��������ͷ����ѡ��Ĭ��Ϊ�ջ�Ĭ������ͷ��
*	}
* 1����ֵ����Ӧ���ݣ�table���ṹ���£�
*	{
*		error��number����������룬
*		status��number����״̬�룬ʧ����Ϊ nil��
*		body��string������Ӧ���ݣ�ʧ����Ϊ nil��
*		headers��table������Ӧͷ��ʧ����Ϊ nil
*	}
*/
ETHER_API client_Options(lua_State* L);

/*
* ���ÿͻ��˵�Ĭ������ͷ
* 2�������ͻ������ݣ�userdata-Client��������ͷ��table����ѡ��Ĭ��Ϊ�գ�
* 0����ֵ
*/
ETHER_API client_SetDefaultHeaders(lua_State* L);

/*
* ���ÿͻ��˵����ӳ�ʱʱ��
* 2�������ͻ������ݣ�userdata-Client������ʱʱ�䣨number����λΪ���룩
* 0����ֵ
*/
ETHER_API client_SetConnectTimeout(lua_State* L);

/*
* ���ÿͻ��˵���Դ��ȡ��ʱʱ��
* 2�������ͻ������ݣ�userdata-Client������ʱʱ�䣨number����λΪ�룩
* 0����ֵ
*/
ETHER_API client_SetReadTimeout(lua_State* L);

/*
* ���ÿͻ��˵���Դд�볬ʱʱ��
* 2�������ͻ������ݣ�userdata-Client������ʱʱ�䣨number����λΪ�룩
* 0����ֵ
*/
ETHER_API client_SetWriteTimeout(lua_State* L);

/*
* ���ÿͻ����Ƿ񱣳�����
* 2�������ͻ������ݣ�userdata-Client�����Ƿ񱣳����ӣ�boolean��
* 0����ֵ
*/
ETHER_API client_SetKeepAlive(lua_State* L);

/*
* ���ÿͻ����Ƿ�����ض���
* 2�������ͻ������ݣ�userdata-Client�����Ƿ�����ض���boolean��
* 0����ֵ
*/
ETHER_API client_SetFollowRedirect(lua_State* L);

/*
* ���ÿͻ����Ƿ�ѹ����������
* 2�������ͻ������ݣ�userdata-Client�����Ƿ�ѹ����boolean��
* 0����ֵ
*/
ETHER_API client_SetCompressRequest(lua_State* L);

/*
* ���ÿͻ����Ƿ�ѹ����Ӧ����
* 2�������ͻ������ݣ�userdata-Client�����Ƿ�ѹ����boolean��
* 0����ֵ
*/
ETHER_API client_SetCompressResponse(lua_State* L);

/*
* ���ÿͻ��� CACert �� SSL ����֤��·��
* 2�������ͻ������ݣ�userdata-Client��������֤��·����string��
* 0����ֵ
*/
ETHER_API client_SetCACertPath(lua_State* L);

/*
* ���ÿͻ��˵Ĵ�������
* 3�������ͻ������ݣ�userdata-Client��������������ַ��string�������������˿ڣ�number��
* 0����ֵ
*/
ETHER_API client_SetProxy(lua_State* L);

/*
* �����ͻ���
* 1������������ַ��string��
* 1����ֵ���ͻ������ݣ�userdata-Client��
*/
ETHER_API createClient(lua_State* L);

/*
* �ͻ������ݵ�GC����
* 1�������ͻ������ݣ�userdata-Client��
* 0����ֵ
*/
ETHER_API __gc_Client(lua_State* L);

/// <summary>
/// ���������ص���������
/// </summary>
/// <param name="req">�������ݶ���</param>
/// <param name="res">��Ӧ���ݶ���</param>
/// <param name="L">Lua �����ָ��</param>
/// <param name="refKey">�ص�����������ע����е�������</param>
/// <param name="serverID">�����ID</param>
void CallRequestHandler(const Request& req, Response& res, lua_State* L, const std::string& refKey, const std::string& serverID);

/// <summary>
/// ������쳣����ص���������
/// </summary>
/// <param name="req">�������ݶ���</param>
/// <param name="res">��Ӧ���ݶ���</param>
/// <param name="L">Lua �����ָ��</param>
/// <param name="refKey">�ص�����������ע����е�������</param>
/// <param name="errmsg">�쳣��Ϣ</param>
void CallExceptionHandler(const Request& req, Response& res, lua_State* L, const std::string& refKey, const std::string& errmsg);

/*
* ��ȡ���󷽷�
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ�����󷽷���string��
*/
ETHER_API request_GetMethod(lua_State* L);

/*
* ��ȡ����·��
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ������·�ɣ�string��
*/
ETHER_API request_GetRoute(lua_State* L);

/*
* ��ȡ����ͷ
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ������ͷ��table��
* ��ע������Lua��table��֧��һ����ֵ�����Ե�����ͷ��һ������Ӧ���ֵʱ��
*	���ر��ж�Ӧ�ļ����������һ��ֵ����ʹ�ô����������� GetHeaderValue ������ȡͬһ������Ӧ�Ĳ�ֵͬ
*/
ETHER_API request_GetHeaders(lua_State* L);

/*
* ��ȡ������
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ�������壨string��
*/
ETHER_API request_GetBody(lua_State* L);

/*
* ��ȡԶ��������ַ
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ��Զ��������ַ��string��
*/
ETHER_API request_GetRemoteAddress(lua_State* L);

/*
* ��ȡԶ�������˿ں�
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ��Զ�������˿ںţ�number��
*/
ETHER_API request_GetRemotePort(lua_State* L);

/*
* ��ȡ�����HTTP�汾
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ��HTTP�汾��string��
*/
ETHER_API request_GetVersion(lua_State* L);

/*
* ��ȡ�������
* 1�������������ݶ������ݣ�userdata-Request��
* 1����ֵ�����������table��
* ��ע������Lua��table��֧��һ����ֵ�����Ե����������һ������Ӧ���ֵʱ��
*	���ر��ж�Ӧ�ļ����������һ��ֵ����ʹ�ô����������� GetParamValue ������ȡͬһ������Ӧ�Ĳ�ֵͬ
*/
ETHER_API request_GetParams(lua_State* L);

/*
* �ж�����ͷ��ָ�����Ƿ����
* 2�������������ݶ������ݣ�userdata-Request��������string��
* 1����ֵ���Ƿ���ڣ�boolean��
*/
ETHER_API request_CheckHeaderKeyExist(lua_State* L);

/*
* ��ȡ����ͷ��ָ������Ӧ��ֵ
* 2��3�������������ݶ������ݣ�userdata-Request��������string����������number����ѡ��Ĭ��Ϊ1��
* 1����ֵ��ֵ��string��
*/
ETHER_API request_GetHeaderValue(lua_State* L);

/*
* ��ȡ����ͷ��ָ������Ӧ��ֵ�ĸ���
* 2�������������ݶ������ݣ�userdata-Request��������string��
* 1����ֵ��ֵ�ĸ�����number��
*/
ETHER_API request_GetHeaderValueCount(lua_State* L);

/*
* �ж����������ָ�����Ƿ����
* 2�������������ݶ������ݣ�userdata-Request��������string��
* 1����ֵ���Ƿ���ڣ�boolean��
*/
ETHER_API request_CheckParamKeyExist(lua_State* L);

/*
* ��ȡ���������ָ������Ӧ��ֵ
* 2��3�������������ݶ������ݣ�userdata-Request��������string����������number����ѡ��Ĭ��Ϊ1��
* 1����ֵ��ֵ��string��
*/
ETHER_API request_GetParamValue(lua_State* L);

/*
* ��ȡ���������ָ������Ӧ��ֵ�ĸ���
* 2�������������ݶ������ݣ�userdata-Request��������string��
* 1����ֵ��ֵ�ĸ�����number��
*/
ETHER_API request_GetParamValueCount(lua_State* L);

/*
* ������Ӧ��HTTP�汾
* 2��������Ӧ���ݶ������ݣ�userdata-Response����HTTP�汾��string��
* 0����ֵ
*/
ETHER_API response_SetVersion(lua_State* L);

/*
* ������Ӧ��״̬��
* 2��������Ӧ���ݶ������ݣ�userdata-Response����״̬�루number��
* 0����ֵ
*/
ETHER_API response_SetStatus(lua_State* L);

/*
* ��ȡ��Ӧͷ
* 1��������Ӧ���ݶ������ݣ�userdata-Response��
* 1����ֵ����Ӧͷ��table��
* ��ע������Lua��table��֧��һ����ֵ�����Ե���Ӧͷ��һ������Ӧ���ֵʱ��
*	���ر��ж�Ӧ�ļ����������һ��ֵ����ʹ�ô����������� GetHeaderValue ������ȡͬһ������Ӧ�Ĳ�ֵͬ
*/
ETHER_API response_GetHeaders(lua_State* L);

/*
* ������Ӧ��
* 2��������Ӧ���ݶ������ݣ�userdata-Response������Ӧ�壨string��
* 0����ֵ
*/
ETHER_API response_SetBody(lua_State* L);

/*
* �ж���Ӧͷ��ָ�����Ƿ����
* 2��������Ӧ���ݶ������ݣ�userdata-Response��������string��
* 1����ֵ���Ƿ���ڣ�boolean��
*/
ETHER_API response_CheckHeaderKeyExist(lua_State* L);

/*
* ��ȡ��Ӧͷ��ָ������Ӧ��ֵ
* 2��3��������Ӧ���ݶ������ݣ�userdata-Response��������string����������number����ѡ��Ĭ��Ϊ1��
* 1����ֵ��ֵ��string��
*/
ETHER_API response_GetHeaderValue(lua_State* L);

/*
* ��ȡ��Ӧͷ��ָ������Ӧ��ֵ�ĸ���
* 2��������Ӧ���ݶ������ݣ�userdata-Response��������string��
* 1����ֵ��ֵ�ĸ�����number��
*/
ETHER_API response_GetHeaderValueCount(lua_State* L);

/*
* ������Ӧͷ��ָ������Ӧ��ֵ
* 3��������Ӧ���ݶ������ݣ�userdata-Response��������string����ֵ��string��
* 0����ֵ
*/
ETHER_API response_SetHeaderValue(lua_State* L);

/*
* ������Ӧͷ
* 3��������Ӧ���ݶ������ݣ�userdata-Response������Ӧͷ��table��
* 0����ֵ
* ��ע������Lua��table��֧��һ����ֵ�����Ե���Ӧͷ��һ������Ӧ���ֵʱ��
*	���ر��ж�Ӧ�ļ����������һ��ֵ����ʹ�� SetHeaderValue ����Ϊͬһ�������ò�ֵͬ
*/
ETHER_API response_SetHeaders(lua_State* L);

/*
* ������Ӧ���ض����ַ
* 2��������Ӧ���ݶ������ݣ�userdata-Response�����ض����ַ��string��
* 0����ֵ
*/
ETHER_API response_SetRedirect(lua_State* L);

/*
* ������Ӧ������
* 2��3��������Ӧ���ݶ������ݣ�userdata-Response������Ӧ�����ݣ�string������Ӧ���ݵ�MIME���ͣ�string����ѡ��Ĭ��Ϊ text/plain��
* 0����ֵ
*/
ETHER_API response_SetContent(lua_State* L);

/*
* �жϷ�����Ƿ񴴽��ɹ�
* 1��������������ݣ�userdata-Server��
* 1����ֵ���Ƿ񴴽��ɹ���boolean��
*/
ETHER_API server_CheckValid(lua_State* L);

/*
* �жϷ�����Ƿ���������
* 1��������������ݣ�userdata-Server��
* 1����ֵ���Ƿ��������У�boolean��
*/
ETHER_API server_CheckRunning(lua_State* L);

/*
* ���÷���˵�Get����·�ɼ���Ӧ�Ļص�����
* 3��������������ݣ�userdata-Server����·�ɣ�string�����ص�������function��
* 0����ֵ
* ��ע��·��֧��������ʽ���ص���������2���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response��
*/
ETHER_API server_Get(lua_State* L);

/*
* ���÷���˵�Post����·�ɼ���Ӧ�Ļص�����
* 3��������������ݣ�userdata-Server����·�ɣ�string�����ص�������function��
* 0����ֵ
* ��ע��·��֧��������ʽ���ص���������2���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response��
*/
ETHER_API server_Post(lua_State* L);

/*
* ���÷���˵�Put����·�ɼ���Ӧ�Ļص�����
* 3��������������ݣ�userdata-Server����·�ɣ�string�����ص�������function��
* 0����ֵ
* ��ע��·��֧��������ʽ���ص���������2���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response��
*/
ETHER_API server_Put(lua_State* L);

/*
* ���÷���˵�Patch����·�ɼ���Ӧ�Ļص�����
* 3��������������ݣ�userdata-Server����·�ɣ�string�����ص�������function��
* 0����ֵ
* ��ע��·��֧��������ʽ���ص���������2���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response��
*/
ETHER_API server_Patch(lua_State* L);

/*
* ���÷���˵�Delete����·�ɼ���Ӧ�Ļص�����
* 3��������������ݣ�userdata-Server����·�ɣ�string�����ص�������function��
* 0����ֵ
* ��ע��·��֧��������ʽ���ص���������2���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response��
*/
ETHER_API server_Delete(lua_State* L);

/*
* ���÷���˵�Options����·�ɼ���Ӧ�Ļص�����
* 3��������������ݣ�userdata-Server����·�ɣ�string�����ص�������function��
* 0����ֵ
* ��ע��·��֧��������ʽ���ص���������2���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response��
*/
ETHER_API server_Options(lua_State* L);

/*
* ��ӷ���˵ľ�̬��Դ���ص�
* 3��������������ݣ�userdata-Server�������ص㣨string�����ļ�Ŀ¼��string��
* 0����ֵ
*/
ETHER_API server_SetMountPoint(lua_State* L);

/*
* �Ƴ������ָ���ľ�̬��Դ���ص�
* 2��������������ݣ�userdata-Server�������ص㣨string��
* 0����ֵ
*/
ETHER_API server_RemoveMountPoint(lua_State* L);

/*
* ���÷���˵ľ�̬��Դ�ļ���չ������Ӧ��MIME����ӳ��
* 2��������������ݣ�userdata-Server������̬��Դ�ļ���չ����string����MIME���ͣ�string��
* 0����ֵ
*/
ETHER_API server_SetFileExtMapToMIMEType(lua_State* L);

/*
* ���÷���˵��쳣������
* 2��������������ݣ�userdata-Server�����쳣����ص�������function��
* 0����ֵ
* ��ע���ص���������3���������������ݶ������ݣ�userdata-Request������Ӧ���ݶ������ݣ�userdata-Response�����쳣��Ϣ��string��
*/
ETHER_API server_SetExceptionHandler(lua_State* L);

/*
* ���÷���˵�������ӱ�����
* 2��������������ݣ�userdata-Server����������ӱ�������number��Ĭ��Ϊ5��
* 0����ֵ
*/
ETHER_API server_SetMaxKeepAliveCount(lua_State* L);

/*
* ���÷���˵����ӱ��ֳ�ʱʱ��
* 2��������������ݣ�userdata-Server�������ӱ��ֳ�ʱʱ�䣨number����λΪ�룬Ĭ��Ϊ5��
* 0����ֵ
*/
ETHER_API server_SetKeepAliveTimeout(lua_State* L);

/*
* ���÷���˵���Դ��ȡ��ʱʱ��
* 2��������������ݣ�userdata-Server������ʱʱ�䣨number����λΪ�룩
* 0����ֵ
*/
ETHER_API server_SetReadTimeout(lua_State* L);

/*
* ���÷���˵���Դд�볬ʱʱ��
* 2��������������ݣ�userdata-Server������ʱʱ�䣨number����λΪ�룩
* 0����ֵ
*/
ETHER_API server_SetWriteTimeout(lua_State* L);

/*
* ���÷���˵Ŀ��м����ʱʱ��
* 2��������������ݣ�userdata-Server������ʱʱ�䣨number����λΪ���룩
* 0����ֵ
*/
ETHER_API server_SetIdleInterval(lua_State* L);

/*
* ���÷���˽��յ����������ݵ���󳤶�
* 2��������������ݣ�userdata-Server������󳤶ȣ�number����λΪ�ֽڣ�
* 0����ֵ
*/
ETHER_API server_SetMaxRequestLength(lua_State* L);

/*
* ����ǰ����˰󶨵�������õĶ˿���
* 1��������������ݣ�userdata-Server��
* 1����ֵ���Ѱ󶨵Ķ˿ںţ�number��
*/
ETHER_API server_BindToAnyPort(lua_State* L);

/*
* �����Ѱ󶨶˿ڵķ���˵ļ���
* 1��������������ݣ�userdata-Server��
* 0����ֵ
* ��ע�����������������Lua���߳�����
*/
ETHER_API server_ListenAfterBind(lua_State* L);

/*
* ��������˼���
* 3��������������ݣ�userdata-Server����������ַ��string�����˿ںţ�number��
* 0����ֵ
* ��ע�����������������Lua���߳�����
*/
ETHER_API server_Listen(lua_State* L);

/*
* ֹͣ����˼���
* 1��������������ݣ�userdata-Server��
* 0����ֵ
*/
ETHER_API server_Stop(lua_State* L);

/*
* ���������
* 0��2������SSL����˵�֤���ļ�·����string����ѡ����SSL����˵�˽Կ�ļ�·����string����ѡ��
* 1����ֵ���ͻ������ݣ�userdata-Client��
* ��ע���ڲ�ʹ��֤���˽Կ���з���˴�����Ĭ�����ͷ���˲�֧�� HTTPS Э�� 
*/
ETHER_API createServer(lua_State* L);

/*
* ��������ݵ�GC����
* 1��������������ݣ�userdata-Server��
* 0����ֵ
*/
ETHER_API __gc_Server(lua_State* L);

/*
* �� HTTP/HTTPS ���ӷָ�Ϊ��������ַ��·�ɺͲ���
* 1������HTTP/HTTPS ���ӣ�string��
* 3����ֵ��������ַ��string��Ĭ��Ϊ���ַ�������·�ɣ�string��Ĭ��Ϊ ��/������������string��Ĭ��Ϊ���ַ�����
*/
ETHER_API splitLink(lua_State* L);

#endif // !_NETWORK_H_

