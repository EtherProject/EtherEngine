#ifndef _OTHERS_H_
#define _OTHERS_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>

// 获取程序运行的目录
// 0参数
// 1返回值：程序运行目录（string）
ETHER_API getBasePath(lua_State * L);

// 设置剪切板文本
// 1参数：剪切板文本（string）
// 0返回值
ETHER_API setClipboardText(lua_State * L);

// 获取剪切板文本
// 0参数
// 1返回值：剪切板文本（string）
ETHER_API getClipboardText(lua_State * L);

// 获取平台类型
// 0参数
// 1返回值：平台类型（string）
ETHER_API getPlatform(lua_State * L);

// 获取系统总内存大小
// 0参数
// 1返回值：系统内存（number，单位MB）
ETHER_API getSystemRAM(lua_State * L);

#endif // !_OTHERS_H_
