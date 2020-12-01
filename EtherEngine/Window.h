#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <lua.hpp>
#include <SDL.h>
#include "Macros.h"

#include <string>
using namespace std;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// 显示模态的提示信息窗口
// 3参数：标题，提示信息内容，窗口类型（错误、警告、提示）
// 无返回值
extern "C" int showMessageBox(lua_State * L);

// 创建窗口，并将此窗口作为图形绘制等操作的上下文
// 5参数：窗口标题，窗口x、y坐标（负值为默认位置），窗口宽度和高度，窗口属性标志（对应关系见下方代码注释）
// 无返回值
extern "C" int createWindow(lua_State * L);

// 关闭窗口
// 无参数
// 无返回值
extern "C" int closeWindow(lua_State * L);

// 设置窗口标题
// 1参数：标题内容
// 无返回值
extern "C" int setWindowTitle(lua_State * L);

// 获取窗口标题
// 无参数
// 1返回值：标题内容
extern "C" int getWindowTitle(lua_State * L);

// 设置窗口模式
// 1参数：全屏标志（0，窗口模式；1，视频模式改变的真全屏；2，使用当前屏幕分辨率的假全屏）
// 无返回值
extern "C" int setWindowMode(lua_State * L);

// 设置窗口是否大小可变
// 1参数：是否大小可变
// 无返回值
extern "C" int setWindowResizable(lua_State * L);

// 设置窗口透明度
// 1参数：透明度大小（0-1）
// 无返回值
extern "C" int setWindowOpacity(lua_State * L);

// 设置窗口大小
// 2参数：窗口的宽和高
// 无返回值
extern "C" int setWindowSize(lua_State * L);

// 获取窗口大小
// 无参数
// 2返回值，窗口的宽和高
extern "C" int getWindowSize(lua_State * L);

// 设置窗口最大尺寸的大小
// 2参数：窗口宽度的最大值和高度的最大值
// 无返回值
extern "C" int setWindowMaxSize(lua_State * L);

// 获取窗口最大尺寸的大小
// 无参数
// 2返回值，窗口度的最大值和高度的最大值
extern "C" int getWindowMaxSize(lua_State * L);

// 设置窗口最小尺寸的大小
// 2参数：窗口宽度的最小值和高度的最小值
// 无返回值
extern "C" int setWindowMinSize(lua_State * L);

// 获取窗口最小尺寸的大小
// 无参数
// 2返回值，窗口度的最小值和高度的最小值
extern "C" int getWindowMinSize(lua_State * L);

// 设置窗口坐标
// 2参数：窗口位置的x和y坐标
// 无返回值
extern "C" int setWindowPosition(lua_State * L);

// 获取窗口坐标
// 无参数
// 2返回值，窗口位置的x和y坐标
extern "C" int getWindowPosition(lua_State * L);

// 使用当前绘图颜色清空窗口内容
// 无参数
// 无返回值
extern "C" int clearWindow(lua_State * L);

#endif // !_WINDOW_H_
