#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

extern SDL_Renderer* renderer;

// 设置鼠标是否显示
// 1参数：是否显示
// 无返回值
extern "C" int setCursorShow(lua_State * L);

// 加载图像文件
// 1参数：图像文件路径
// 1返回值：成功则返回图片userdata，失败则返回nil
extern "C" int loadImage(lua_State * L);

// 加载使用ColorKey表示透明区域的图像文件
// 4参数：图像文件路径，ColorKey的R、G、B分量
// 1返回值：-1，加载文件失败；其他，已加载的图像文件在图像库中的标志
extern "C" int setImageColorKey(lua_State * L);

// 释放已加载的图像
// 1参数：已加载的图像文件在图像库中的标志
// 1返回值：-1，释放图像失败；0，释放图像成功
extern "C" int unloadImage(lua_State * L);

extern "C" int createTexture(lua_State * L);

extern "C" int destroyTexture(lua_State * L);

// 设置已加载图像的透明度
// 2参数：已加载的图像文件在图像库中的标志，透明度数值（0-255）
// 1返回值：-1，设置图像透明度失败；0，设置图像透明度成功
extern "C" int setTextureAlpha(lua_State * L);

// 获取已加载图像尺寸
// 1参数：已加载的图像文件在图像库中的标志
// 2返回值：-1，-1，获取图像尺寸失败；成功则返回图像的长和宽
extern "C" int getImageSize(lua_State * L);

// 显示已加载的图像
// 5参数：已加载的图像文件在图像库中的标志，显示位置x，显示位置y，显示宽度，显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
extern "C" int copyTexture(lua_State * L);

// 显示旋转后的已加载图像
// 9参数：已加载的图像文件在图像库中的标志，顺时针旋转角度，旋转中心x坐标，旋转中心y坐标，显示位置x，显示位置y，显示宽度（-1为默认尺寸），显示高度（-1为默认尺寸），翻转模式
// 1返回值：-1，显示图像失败；0，显示图像成功
extern "C" int copyRotateTexture(lua_State * L);

// 显示裁剪后的已加载图像
// 9参数：已加载的图像文件在图像库中的标志，裁剪区域x，裁剪区域y，裁剪区域宽度（-1为默认尺寸），裁剪区域高度（-1为默认尺寸），显示位置x，显示位置y，显示宽度（-1为默认尺寸），显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
extern "C" int copyReshapeTexture(lua_State * L);

// 显示旋转且裁剪后的已加载图像
// 13参数：已加载的图像文件在图像库中的标志，旋转角度，旋转中心x坐标，旋转中心y坐标，旋转模式，裁剪区域x，裁剪区域y，裁剪区域宽度（-1为默认尺寸），裁剪区域高度（-1为默认尺寸），显示位置x，显示位置y，显示宽度（-1为默认尺寸），显示高度（-1为默认尺寸）
// 1返回值：-1，显示图像失败；0，显示图像成功
extern "C" int copyRotateReshapeTexture(lua_State * L);

// 设置窗口绘图颜色
// 4参数：颜色的R、G、B、A分量（取值范围均为0-255）
// 无返回值
extern "C" int setDrawColor(lua_State * L);

// 获取窗口绘图颜色
// 无参数
// 4返回值：颜色的R、G、B、A分量（取值范围均为0-255）
extern "C" int getDrawColor(lua_State * L);

// 在指定位置绘制点
// 2参数：点所在的x和y坐标
// 无返回值
extern "C" int point(lua_State * L);

// 在指定位置绘制直线
// 4参数：起点x、y坐标，终点x、y坐标
// 无返回值
extern "C" int line(lua_State * L);

// 在指定位置绘制粗直线
// 5参数：起点x、y坐标，终点x、y坐标，线条宽度
// 无返回值
extern "C" int thickLine(lua_State * L);

// 在指定位置绘制无填充矩形
// 4参数：矩形左上角x、y坐标，矩形宽和高
// 无返回值
extern "C" int rectangle(lua_State * L);

// 在指定位置绘制填充矩形
// 4参数：矩形左上角x、y坐标，矩形宽和高
// 无返回值
extern "C" int fillRectangle(lua_State * L);

// 在指定位置绘制圆角无填充矩形
// 5参数：矩形左上角x、y坐标，矩形宽和高，圆角半径大小
// 无返回值
extern "C" int roundRectangle(lua_State * L);

// 在指定位置绘制圆角填充矩形
// 5参数：矩形左上角x、y坐标，矩形宽和高，圆角半径大小
// 无返回值
extern "C" int fillRoundRectangle(lua_State * L);

// 在指定位置绘制无填充圆形
// 3参数：圆心x、y坐标，圆半径
// 无返回值
extern "C" int circle(lua_State * L);

// 在指定位置绘制填充圆形
// 3参数：圆心x、y坐标，圆半径
// 无返回值
extern "C" int fillCircle(lua_State * L);

// 在指定位置绘制无填充椭圆
// 4参数：椭圆中心x、y坐标，椭圆x轴半径和y轴半径
// 无返回值
extern "C" int ellipse(lua_State * L);

// 在指定位置绘制填充椭圆
// 4参数：椭圆中心x、y坐标，椭圆x轴半径和y轴半径
// 无返回值
extern "C" int fillEllipse(lua_State * L);

// 在指定位置绘制无填充扇形
// 5参数：扇形所在圆的圆心x、y坐标，扇形所在圆半径、开始和结束角度
// 无返回值
extern "C" int pie(lua_State * L);

// 在指定位置绘制填充扇形
// 5参数：扇形所在圆的圆心x、y坐标，扇形所在圆半径、开始和结束角度
// 无返回值
extern "C" int fillPie(lua_State * L);

// 在指定位置绘制无填充三角形
// 6参数：三角形三个顶点的x、y坐标
// 无返回值
extern "C" int triangle(lua_State * L);

// 在指定位置绘制填充三角形
// 6参数：三角形三个顶点的x、y坐标
// 无返回值
extern "C" int fillTriangle(lua_State * L);

// 加载字体文件
// 2参数：字体文件路径、字体大小
// 1返回值：-1，加载文件失败；其他，已加载的字体文件在字体库中的标志
extern "C" int loadFont(lua_State * L);

// 释放已加载的字体
// 1参数：已加载的字体文件在字体库中的标志
// 1返回值：-1，释放字体失败；0，释放字体成功
extern "C" int unloadFont(lua_State * L);

extern "C" int getFontStyle(lua_State * L);

extern "C" int setFontStyle(lua_State * L);

extern "C" int getFontOutlineWidth(lua_State * L);

extern "C" int setFontOutlineWidth(lua_State * L);

extern "C" int getFontKerning(lua_State * L);

extern "C" int setFontKerning(lua_State * L);

extern "C" int getFontHeight(lua_State * L);

extern "C" int getTextSize(lua_State * L);

extern "C" int getUTF8TextSize(lua_State * L);

extern "C" int createTextImageSolid(lua_State * L);

extern "C" int createUTF8TextImageSolid(lua_State * L);

extern "C" int createTextImageShaded(lua_State * L);

extern "C" int createUTF8TextImageShaded(lua_State * L);

extern "C" int createTextImageBlended(lua_State * L);

extern "C" int createUTF8TextImageBlended(lua_State * L);

// 将渲染缓冲区的内容刷新到屏幕上
// 无参数
// 无返回值
extern "C" int updateWindow(lua_State * L);


#endif // !_GRAPHIC_H_
