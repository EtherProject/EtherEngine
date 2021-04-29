#ifndef _OS_H_
#define _OS_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>

#include <string>
using namespace std;

#ifdef __WINDOWS__
#include <io.h>
#else
#include ""
#endif

#define FILEATTRIB_ARCH			0
#define FILEATTRIB_HIDDEN		1
#define FILEATTRIB_NORMAL		2
#define FILEATTRIB_RDONLY		3
#define FILEATTRIB_SUBDIR		4
#define FILEATTRIB_SYSTEM		5

#define PATHMODE_FILE			6
#define PATHMODE_DIR			7
#define PATHMODE_FILEANDDIR		8

#define POWERSTATE_UNKOWN		9
#define POWERSTATE_ONBATTERY	10
#define POWERSTATE_NOBATTERY	11
#define POWERSTATE_CHARGING		12
#define POWERSTATE_CHARGEDN		13

class ModuleOS : public Module
{
public:
	static ModuleOS& Instance();
	~ModuleOS() {};

private:
	ModuleOS();

};

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
ETHER_API getPlatformType(lua_State * L);

// 获取 CPU 逻辑核心数
// 0参数
// 1返回值：CPU 逻辑核心数（number）
ETHER_API getCPUCount(lua_State* L);

// 获取系统总内存大小
// 0参数
// 1返回值：系统内存大小（number，单位为MB）
ETHER_API getSystemTotalRAM(lua_State * L);

// 获取指定组织的应用在当前系统用户下的数据文件夹路径，如果没有则创建
// 2参数：组织名（string），应用名（string）
// 1返回值：数据文件夹路径（string）
ETHER_API getAppDataPath(lua_State* L);

/*
* 获取设备当前电源信息
* 0参数
* 1返回值：设备当前电源信息（table，表结构如下）：
	{
		state: 供电状态（Macro number）,
		remain_time：成功则为剩余使用时长（number），单位为秒，失败或当前不是电池供电则为 -1（number）
		remain_percentage：成功则返回剩余电量百分比（number），取值范围为 0 - 100，失败则为 -1（number）
	}
*/
ETHER_API getPowerInfo(lua_State* L);

/*
* 获取指定目录下文件列表
* 1参数：目录路径（string）
* 1返回值：文件列表（table）
*/
ETHER_API listDirectory(lua_State* L);

/*
* 判断指定路径是否存在
* 1或2参数：目录或文件所在的路径（string），【可选】判断模式（Macro number）
* 1返回值：是否存在（boolean）
*/
ETHER_API checkPathExist(lua_State* L);

/*
* 获取指定路径的信息
* 1参数：目录或文件所在的路径（string）
* 1返回值：成功则返回路径信息（table，表结构如下）：
	{
		name：文件名（string），
		size：文件大小（number），
		time：{
			create：创建时间（number），
			access：最后一次访问时间（number），
			write：最后一次修改时间（number），
		}，
		attributes：文件属性（table），
	}
* ，失败则返回nil
*/
ETHER_API getPathInfo(lua_State* L);

/*
* 合并目录和文件名为完整路径
* 2参数：目录（string），文件名（string）
* 1返回值：完整路径（string）
*/
ETHER_API joinPath(lua_State* L);

/*
* 从路径中获取文件名
* 1参数：路径（string）
* 1返回值：文件名（string）
*/
ETHER_API getFileNameFromPath(lua_State* L);

/*
* 从路径中获取根目录路径
* 1参数：路径（string）
* 1返回值：根目录路径（string）
*/
ETHER_API getBasePathFromPath(lua_State* L);

#endif // !_OS_H_
