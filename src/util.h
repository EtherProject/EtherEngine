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

#ifdef _WINDOWS_

#include <Windows.h>
#include <wchar.h>

#endif


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

#endif // !_UTIL_H_

