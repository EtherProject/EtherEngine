#ifndef _UTIL_H_
#define _UTIL_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>
#include <httplib.h>
using namespace httplib;

#include <memory>
#include <string>
using namespace std;

/// <summary>
/// 获取描述点位置的表的参数
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="index">参数位置</param>
/// <param name="funName">宿主函数名</param>
/// <returns>点位置</returns>
SDL_Point GetPointParam(lua_State* L, int index, const char* funName);

/// <summary>
/// 获取描述矩形位置和大小的表的参数
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="index">参数位置</param>
/// <param name="funName">宿主函数名</param>
/// <returns>矩形位置和大小</returns>
SDL_Rect GetRectParam(lua_State* L, int index, const char* funName);

/// <summary>
/// 获取描述颜色的表的参数
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="index">参数位置</param>
/// <param name="funName">宿主函数名</param>
/// <returns>颜色</returns>
SDL_Color GetColorParam(lua_State* L, int index, const char* funName);

/// <summary>
/// 从链接中获取域名
/// </summary>
/// <param name="link">链接</param>
/// <returns>域名</returns>
string GetLinkDomain(string link);

/// <summary>
/// 从链接中获取路由
/// </summary>
/// <param name="link">链接</param>
/// <returns>路由</returns>
string GetLinkRoute(string link);

/// <summary>
/// 将指定的Response表压入当前Lua虚拟栈
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="response">Response表</param>
void PushResponseTable(lua_State* L, shared_ptr<Response> response);

/// <summary>
/// 将宏转换为 MIME Type
/// </summary>
/// <param name="macro">宏</param>
/// <returns>MIME Type</returns>
string ConvertMacroToMIMEType(int macro);

#endif // !_UTIL_H_

