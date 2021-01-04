#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Macros.h"
#include "util.h"

#include <lua.hpp>
#include <httplib.h>
using namespace httplib;

// 从链接中获取域名
// 1参数：链接（string）
// 1返回值：域名（string）
ETHER_API getLinkDomain(lua_State* L);

// 从链接中获取路由
// 1参数：链接（string）
// 1返回值：路由（string）
ETHER_API getLinkRoute(lua_State* L);

// 使用Get请求访问指定链接
// 1参数：链接（string）
// 1返回值：成功则返回Response表（table，成员：状态码status（number），响应头headers（table），正文body（string）），失败则返回nil
ETHER_API requestGet(lua_State* L);

#endif // !_NETWORK_H_

