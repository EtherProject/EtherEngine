#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Moudle.h"
#include "Macros.h"
#include "util.h"

#include <lua.hpp>
#include <httplib.h>
using namespace httplib;
/*
* 从链接中获取域名
* 1参数：链接（string）
* 1返回值：域名（string）
*/
ETHER_API getLinkDomain(lua_State* L);

/*
* 从链接中获取路由
* 1参数：链接（string）
* 1返回值：路由（string）
*/
ETHER_API getLinkRoute(lua_State* L);

/*
* 使用Get请求访问指定链接
* 1或2参数：链接（string），【可选】HttpHeaders（table）
* 1返回值：成功则返回Response表（table）：
	{
		statue：状态码（number），
		headers：响应头（table），
		body：正文（string），
	}
* ，失败则返回nil
*/

ETHER_API requestGet(lua_State* L);

/*
* 使用Post请求向指定链接发送数据
* 3或4参数：链接（string），数据体（string），MIME Type（Macro number），【可选】HttpHeaders（table）
* 1返回值：成功则返回Response表（table，表结构如下）:
	{
		statue：状态码（number），
		headers：响应头（table），
		body：正文（string），
	}
* ，失败则返回nil
*/
ETHER_API requestPost(lua_State* L);


class MoudleNetwork : public Moudle
{
public:
	MoudleNetwork(lua_State* L);
	~MoudleNetwork() {};

};

#endif // !_NETWORK_H_

