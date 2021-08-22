#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Module.h"
#include "Utils.h"
#include "ModuleGraphic.h"

#include <lua.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef __WINDOWS__
#define  WIN32_LEAN_AND_MEAN
#include <shlobj.h>
#include <tchar.h>
#else
#include ""
#endif

#define WINDOW_POSITION_DEFAULT INT_MIN

#define MSGBOX_ERROR					1001
#define MSGBOX_WARNING					1002
#define MSGBOX_INFO						1003

#define WINDOW_FULLSCREEN				1004
#define WINDOW_FULLSCREEN_DESKTOP		1005
#define WINDOW_BORDERLESS				1006
#define WINDOW_RESIZABLE				1007
#define WINDOW_MAXIMIZED				1008
#define WINDOW_MINIMIZED				1009

#define WINDOW_MODE_WINDOWED			1013
#define WINDOW_MODE_FULLSCREEN			1014
#define WINDOW_MODE_FULLSCREEN_DESKTOP	1015
#define WINDOW_MODE_BORDERLESS			1016
#define WINDOW_MODE_BORDERED			1017
#define WINDOW_MODE_RESIZABLE			1018
#define WINDOW_MODE_SIZEFIXED			1019

class ModuleWindow : public Module
{
public:
	static ModuleWindow& Instance();
	~ModuleWindow() {};

private:
	ModuleWindow();

};

extern SDL_Window* window;
extern SDL_Renderer* renderer;

// 显示模态的提示信息窗口
// 3参数：窗口类型（Macro number），提示窗口标题（string），提示信息内容（string）
// 0返回值
ETHER_API showMessageBox(lua_State * L);

// 显示模态的确认信息窗口
// 3或5参数：窗口类型（Macro number），提示窗口标题（string），提示信息内容（string），确认按钮文本（string，可选），取消按钮文本（string，可选）
// 1返回值：确认则返回 true（boolean），否则返回 false（boolean）
ETHER_API showConfirmMessageBox(lua_State* L);

// 显示文件夹选择器
// 1参数：提示信息内容
// 1返回时：选择成功则返回文件夹路径（string），否则返回nil
ETHER_API showFolderSelector(lua_State* L);

// 创建窗口，并将此窗口作为图形绘制等操作的上下文
// 5参数：窗口标题，用以描述显示区域的矩形，用以描述窗口属性的表（table）
// 0返回值
ETHER_API createWindow(lua_State * L);

// 关闭窗口
// 0参数
// 0返回值
ETHER_API closeWindow(lua_State * L);

// 设置窗口标题
// 1参数：窗口标题（string）
// 0返回值
ETHER_API setWindowTitle(lua_State * L);

// 获取窗口标题
// 0参数
// 1返回值：窗口标题（string）
ETHER_API getWindowTitle(lua_State * L);

// 设置窗口模式
// 1参数：窗口模式（Macro number）
// 0返回值
ETHER_API setWindowMode(lua_State * L);

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

// 获取窗口可渲染尺寸大小（支持高 DPI）
// 0 参数
// 2返回值：窗口可渲染宽度（number），窗口可渲染高度（number）
ETHER_API getWindowDrawableSize(lua_State* L);

// 设置窗口最小尺寸的大小
// 2参数：窗口最小宽度（number），窗口最小高度（number）
// 0返回值
ETHER_API setWindowMinSize(lua_State * L);

// 获取窗口最小尺寸的大小
// 0参数
// 2返回值：窗口最小宽度（number），窗口最小高度（number）
ETHER_API getWindowMinSize(lua_State * L);

// 设置窗口位置
// 1参数：窗口位置坐标（table）
// 0返回值
ETHER_API setWindowPosition(lua_State * L);

// 获取窗口位置
// 0参数
// 1返回值：窗口位置坐标（table）
ETHER_API getWindowPosition(lua_State * L);

// 设置窗口图标 (Windows平台下窗口将优先使用可执行文件图标资源)
// 1参数：图像数据（userdata-IMAGE）
// 0返回值
ETHER_API setWindowIcon(lua_State * L);

// 使用当前绘图颜色清空窗口内容
// 0参数
// 0返回值
ETHER_API clearWindow(lua_State * L);

// 将渲染缓冲区的内容刷新到屏幕上
// 0参数
// 0返回值
ETHER_API updateWindow(lua_State* L);

#endif // !_WINDOW_H_