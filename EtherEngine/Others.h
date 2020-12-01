#ifndef _OTHERS_H_
#define _OTHERS_H_

#include <lua.hpp>
#include <SDL.h>

// 获取程序运行的目录
// 无参数
// 1返回值：程序运行目录
extern "C" int getBasePath(lua_State * L);

// 设置剪切板文本
// 1参数：剪切板文本
// 无返回值
extern "C" int setClipboardText(lua_State * L);

// 获取剪切板文本
// 无参数
// 1返回值：剪切板文本
extern "C" int getClipboardText(lua_State * L);

// 获取平台类型
// 无参数
// 1返回值：平台类型（字符串）
extern "C" int getPlatform(lua_State * L);

// 获取系统总内存大小
// 无参数
// 1返回值：系统内存（MB）
extern "C" int getSystemRAM(lua_State * L);

#endif // !_OTHERS_H_
