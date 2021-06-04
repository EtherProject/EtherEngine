#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Module.h"
#include "Macros.h"
#include "Utils.h"

#include <lua.hpp>
#include <SDL2/SDL.h>
#include <cpp-base64/base64.h>

#include <math.h>
#include <string>


class ModuleAlgorithm : public Module
{
public:
	static ModuleAlgorithm& Instance();
	~ModuleAlgorithm() {};

private:
	ModuleAlgorithm();

};

struct ColorHSLA
{
	double h;
	double s;
	double l;
	double a;
};

double HLS2RGBvalue(double n1, double n2, double hue);

// 将数值限制在指定区间
// 1或3参数：被限定值（number），下限和上限（number，默认为0和1）
// 1返回值：限定后值
ETHER_API clamp(lua_State * L);

// 判断点是否位于指定矩形区域内(包含矩形边界）
// 2或3参数：点坐标（table），矩形区域（table），是否包含边界（boolean，可选，默认为 true）
// 1返回值：是否位于区域内（boolean）
ETHER_API checkPointInRect(lua_State* L);

// 判断点是否位于指定圆形区域内(包含圆形边界）
// 3或4参数：点坐标（table），圆心坐标（table），圆半径（number），是否包含边界（boolean，可选，默认为 true）
// 1返回值：是否位于区域内（boolean）
ETHER_API checkPointInCircle(lua_State* L);

// 判断两矩形区域是否相交（包含矩形边界）
// 2或3参数：矩形1区域（table），矩形2区域（table），是否包含边界（boolean，可选，默认为 true）
// 1返回值：是否相交（boolean）
ETHER_API checkRectsOverlap(lua_State* L);

// 判断两圆是否相交（包含圆形边界）
// 4或5参数：圆1圆心坐标（table），圆1半径（number），圆2圆心坐标（table），圆2半径（number），是否包含边界（boolean，可选，默认为 true）
// 1返回值：是否相交（boolean）
ETHER_API checkCirclesOverlap(lua_State* L);

// 获取两点间直线距离
// 2参数：点1坐标（table），点2坐标（table）
// 1返回值：两点间直线距离（number）
ETHER_API getPointsDistance(lua_State* L);

// 获取两直线间距离
// 2参数：直线1起点坐标（table），直线1终点坐标（table），直线2起点坐标（table），直线2终点坐标（table）
// 1返回值：两直线间距离（number）
ETHER_API getLinesDistance(lua_State* L);

// 获取点到直线的垂直距离
// 3参数：点坐标（table），直线起点坐标（table），直线终点坐标（table）
// 1返回值：点到直线的距离（number）
ETHER_API getPointLineDistance(lua_State* L);

// RGBA颜色空间转HSLA颜色空间
// 1参数：使用RGBA描述的颜色（table）
// 1返回值：使用HSLA描述的颜色（table）
ETHER_API rgbaToHSLA(lua_State* L);

// HSLA颜色空间转RGBA颜色空间
// 1参数：使用HSLA描述的颜色（table）
// 1返回值：使用RGBA描述的颜色（table）
ETHER_API hslaToRGBA(lua_State* L);

// 将缓冲区数据编码为 Base64 编码的字符串
// 1参数：缓冲区数据（string）
// 1返回值：Base64 编码的字符串（string）
ETHER_API encodeBase64(lua_State* L);

// 将 Base64 编码的字符串解码为缓冲区数据
// 1参数：Base64 编码的字符串（string）
// 1返回值：缓冲区数据（string）
ETHER_API decodeBase64(lua_State* L);

#endif // !_ALGORITHM_H_

