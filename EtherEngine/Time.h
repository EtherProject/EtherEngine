#ifndef _TIME_H_
#define _TIME_H_

#include <lua.hpp>
#include <SDL.h>

// 暂停程序
// 无参数
// 无返回值
extern "C" int pause(lua_State * L);

// 挂起程序指定时间
// 1参数：挂起时间（单位：毫秒）
// 无返回值
extern "C" int sleep(lua_State * L);

// 获取程序从初始化运行到现在为止的时间
// 无参数
// 1返回值：运行时间（单位：毫秒）
extern "C" int getInitTime(lua_State * L);

// 获取高分辨率计数器当前值
// 无参数
// 1返回值：计数器当前值
extern "C" int getAccurateCount(lua_State * L);

// 获取高分辨率计数器频率
// 无参数
// 1返回值：计数器频率（单位：赫兹）
extern "C" int getCounterFrequency(lua_State * L);

#endif // !_TIME_H_
