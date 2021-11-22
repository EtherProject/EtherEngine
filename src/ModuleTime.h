#ifndef _TIME_H_
#define _TIME_H_

#include "Module.h"
#include "Macros.h"

#include "lua.hpp"
#include <SDL2/SDL.h>

class ModuleTime : public Module
{
public:
	static ModuleTime& Instance();
	~ModuleTime() {};

private:
	ModuleTime();

};

// 暂停程序
// 0参数
// 0返回值
ETHER_API pause(lua_State * L);

// 挂起程序指定时间
// 1参数：挂起时间（number，单位：毫秒）
// 0返回值
ETHER_API sleep(lua_State * L);

// 尝试挂起程序至期望的时间间隔
// 2参数：期望的时间间隔（number，单位：毫秒），已经度过的时间（number，单位：毫秒）
// 0返回值
ETHER_API dynamicSleep(lua_State* L);

// 获取程序从初始化运行到现在为止的时间
// 0参数
// 1返回值：运行时间（number，单位：毫秒）
ETHER_API getInitTime(lua_State * L);

// 获取高分辨率计数器当前值
// 0参数
// 1返回值：计数器当前值（number）
ETHER_API getAccurateCount(lua_State * L);

// 获取高分辨率计数器频率
// 0参数
// 1返回值：计数器频率（number，单位：赫兹）
ETHER_API getCounterFrequency(lua_State * L);

#endif // !_TIME_H_
