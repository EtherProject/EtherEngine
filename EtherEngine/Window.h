#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Macros.h"
#include "util.h"

#include <lua.hpp>
#include <SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// 显示模态的提示信息窗口
// 3参数：标题（string），提示信息内容（string），窗口类型（Macro number）
// 0返回值
ETHER_API showMessageBox(lua_State * L);

// 创建窗口，并将此窗口作为图形绘制等操作的上下文
// 5参数：窗口标题，用以描述显示区域的矩形（table，x和y的值为-1表示在默认位置显示），用以描述窗口属性的表（table）
// 0返回值
ETHER_API createWindow(lua_State * L);

// 关闭窗口
// 0参数
// 0返回值
ETHER_API closeWindow(lua_State * L);

// 设置窗口标题
// 1参数：标题内容（string）
// 0返回值
ETHER_API setWindowTitle(lua_State * L);

// 获取窗口标题
// 0参数
// 1返回值：标题内容（string）
ETHER_API getWindowTitle(lua_State * L);

// 设置窗口模式
// 1参数：窗口模式（Macro number）
// 0返回值
ETHER_API setWindowMode(lua_State * L);

// 设置窗口大小是否可变
// 1参数：是否可变（boolean）
// 0返回值
ETHER_API setWindowResizable(lua_State * L);

// 设置窗口透明度
// 1参数：透明度大小（number，取值范围0-1）
// 0返回值
ETHER_API setWindowOpacity(lua_State * L);

// 设置窗口大小
// 2参数：窗口宽度（number)，窗口高度（number）
// 0返回值
ETHER_API setWindowSize(lua_State * L);

// 获取窗口大小
// 0参数
// 2返回值：窗口宽度（number），窗口高度（number）
ETHER_API getWindowSize(lua_State * L);

// 设置窗口最大尺寸的大小
// 2参数：窗口最大宽度（number），窗口最大高度（number）
// 0返回值
ETHER_API setWindowMaxSize(lua_State * L);

// 获取窗口最大尺寸的大小
// 0参数
// 2返回值：窗口最大宽度（number），窗口最大高度（number）
ETHER_API getWindowMaxSize(lua_State * L);

// 设置窗口最小尺寸的大小
// 2参数：窗口最小宽度（number），窗口最小高度（number）
// 0返回值
ETHER_API setWindowMinSize(lua_State * L);

// 获取窗口最小尺寸的大小
// 0参数
// 2返回值：窗口最小宽度（number），窗口最小高度（number）
ETHER_API getWindowMinSize(lua_State * L);

// 设置窗口坐标
// 1参数：窗口位置坐标（table）
// 0返回值
ETHER_API setWindowPosition(lua_State * L);

// 获取窗口坐标
// 0参数
// 1返回值：窗口位置坐标（table）
ETHER_API getWindowPosition(lua_State * L);

// 使用当前绘图颜色清空窗口内容
// 0参数
// 0返回值
ETHER_API clearWindow(lua_State * L);

#endif // !_WINDOW_H_
