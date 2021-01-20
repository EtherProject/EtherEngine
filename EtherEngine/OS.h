#ifndef _OS_H_
#define _OS_H_

#include "Moudle.h"
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

/*
* 获取目录下文件信息
* 1参数：目录路径（string）
* 1返回值：文件列表（table）
*/
ETHER_API listDirectory(lua_State* L);

/*
* 判断指定路径是否存在
* 1或2参数：目录或文件所在的路径（string），【可选】判断模式（Macro number）
* 1返回值：是否存在（boolean）
*/
ETHER_API ifPathExist(lua_State* L);

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
		attributes：文件属性，
	}
* ，失败则返回nil
*/
ETHER_API getPathInfo(lua_State* L);

/*
* 合并目录和文件名为一个路径
* 2参数：目录（string），文件名（string）
* 1返回值：路径（string）
*/
ETHER_API joinPath(lua_State* L);


class MoudleOS : public Moudle
{
public:
	MoudleOS(lua_State* L);
	~MoudleOS() {};

};

#endif // !_OS_H_
