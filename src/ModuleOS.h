#ifndef _OS_H_
#define _OS_H_

#include "Module.h"
#include "Macros.h"

#include "lua.hpp"
#include <SDL2/SDL.h>

#include <string>


#ifdef __WINDOWS__
#define  WIN32_LEAN_AND_MEAN
#include <shlobj.h>
#include <tchar.h>
#include <io.h>
#else
#include ""
#endif

#define FILEATTRIB_ARCH						0
#define FILEATTRIB_HIDDEN					1
#define FILEATTRIB_NORMAL					2
#define FILEATTRIB_RDONLY					3
#define FILEATTRIB_SUBDIR					4
#define FILEATTRIB_SYSTEM					5

#define PATHMODE_FILE						6
#define PATHMODE_DIR						7
#define PATHMODE_FILEANDDIR					8

#define POWERSTATE_UNKOWN					9
#define POWERSTATE_ONBATTERY				10
#define POWERSTATE_NOBATTERY				11
#define POWERSTATE_CHARGING					12
#define POWERSTATE_CHARGEDN					13

#define PATHATTRIB_DESKTOP					14          
#define PATHATTRIB_INTERNET					15          
#define PATHATTRIB_PROGRAMS					16          
#define PATHATTRIB_CONTROLS					17          
#define PATHATTRIB_PRINTERS					18          
#define PATHATTRIB_DOCUMENTS				19           
#define PATHATTRIB_FAVORITES				20          
#define PATHATTRIB_STARTUP					21          
#define PATHATTRIB_RECENT					22          
#define PATHATTRIB_SENDTO					23          
#define PATHATTRIB_RECYCLEBIN				24           
#define PATHATTRIB_STARTMENU				25                    
#define PATHATTRIB_MUSIC					26        
#define PATHATTRIB_VIDEO					27              
#define PATHATTRIB_DRIVES					28          
#define PATHATTRIB_NETWORK					29          
#define PATHATTRIB_NETHOOD					30          
#define PATHATTRIB_FONTS					31          
#define PATHATTRIB_TEMPLATES				32          
#define PATHATTRIB_COMMON_STARTMENU			33       
#define PATHATTRIB_COMMON_PROGRAMS			34  
#define PATHATTRIB_COMMON_STARTUP			35  
#define PATHATTRIB_COMMON_DESKTOP			36
#define PATHATTRIB_APPDATA					37  
#define PATHATTRIB_PRINTHOOD				38  
#define PATHATTRIB_LOCAL_APPDATA			39
#define PATHATTRIB_COMMON_FAVORITES			40
#define PATHATTRIB_INTERNET_CACHE			41
#define PATHATTRIB_COOKIES					42
#define PATHATTRIB_HISTORY					43
#define PATHATTRIB_COMMON_APPDATA			44
#define PATHATTRIB_WINDOWS					45
#define PATHATTRIB_SYSTEM					46
#define PATHATTRIB_PROGRAM_FILES			47
#define PATHATTRIB_PICTURES					48
#define PATHATTRIB_PROFILE					49 
#define PATHATTRIB_SYSTEMX86				50
#define PATHATTRIB_PROGRAM_FILESX86			51
#define PATHATTRIB_PROGRAM_FILES_COMMON		52
#define PATHATTRIB_PROGRAM_FILES_COMMONX86	53
#define PATHATTRIB_COMMON_TEMPLATES			54
#define PATHATTRIB_COMMON_DOCUMENTS			55
#define PATHATTRIB_COMMON_ADMINTOOLS		56
#define PATHATTRIB_ADMINTOOLS				57
#define PATHATTRIB_CONNECTIONS				58
#define PATHATTRIB_COMMON_MUSIC				59
#define PATHATTRIB_COMMON_PICTURES			60
#define PATHATTRIB_COMMON_VIDEO				61
#define PATHATTRIB_RESOURCES				62
#define PATHATTRIB_RESOURCES_LOCALIZED		63
#define PATHATTRIB_COMMON_OEM_LINKS			64
#define PATHATTRIB_CDBURN_AREA				65
#define PATHATTRIB_COMPUTERSNEARME			66

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

// 获取应用在当前系统用户下的存储目录，如果不存在则创建
// 2参数：组织名（string），应用名（string）
// 1返回值：数据文件夹路径（string）
ETHER_API getAppStorageDirectory(lua_State* L);

// 获取系统特殊路径
// 1参数：路径标识（Macro number）
// 1参数：完整路径（string）
ETHER_API getSpecialPath(lua_State* L);

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
* 将路径分割为文件夹路径和文件名
* 1参数：路径（string）
* 2返回值：文件夹路径（string），文件名（string）
*/
ETHER_API splitPath(lua_State* L);

#endif // !_OS_H_
