#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "Module.h"
#include "Macros.h"
#include "Utils.h"

#include "lua.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define FONT_STYLE_BOLD						1303
#define FONT_STYLE_ITALIC					1304
#define FONT_STYLE_UNDERLINE				1305
#define FONT_STYLE_STRIKETHROUGH			1306
#define FONT_STYLE_NORMAL					1307

#define FLIP_HORIZONTAL						1010
#define FLIP_VERTICAL						1011
#define FLIP_NONE							1012

#define METANAME_IMAGE						"Graphic.Image"
#define METANAME_TEXTURE					"Graphic.Texture"
#define METANAME_FONT						"Graphic.Font"

#define GetImageDataAt1stPos()				(SDL_Surface*)(*(void**)luaL_checkudata(L, 1, METANAME_IMAGE))
#define GetTextureDataAt1stPos()			(SDL_Texture*)(*(void**)luaL_checkudata(L, 1, METANAME_TEXTURE))
#define GetFontDataAt1stPos()				(TTF_Font*)(*(void**)luaL_checkudata(L, 1, METANAME_FONT))

#define CheckImageDataAt1stPos(surface)		luaL_argcheck(L, surface, 1, "get image data failed")
#define CheckTextureDataAt1stPos(texture)	luaL_argcheck(L, texture, 1, "get texture data failed")
#define CheckFontDataAt1stPos(font)			luaL_argcheck(L, font, 1, "get font data failed")

class ModuleGraphic : public Module
{
public:
	static ModuleGraphic& Instance();
	~ModuleGraphic() {};

private:
	ModuleGraphic();
};

extern SDL_Renderer* renderer;

// 设置鼠标是否显示
// 1参数：是否显示（boolean）
// 0返回值
ETHER_API setCursorShow(lua_State * L);

// 从文件中加载图像
// 1参数：图像文件路径（string）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API loadImageFromFile(lua_State * L);

// 从缓冲区中加载图像
// 1参数：缓冲区数据（string）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API loadImageFromData(lua_State* L);

// 设置的图片文件是否启用指定的ColorKey，启用的Color将被透明化
// 3参数：图像数据（userdata-IMAGE），是否启用（boolean），ColorKey（table）
// 0返回值
ETHER_API image_SetColorKey(lua_State * L);

// 图像数据GC函数
// 1参数：图像数据（userdata-IMAGE）
// 0返回值
ETHER_API __gc_Image(lua_State * L);

// 从图像数据创建属于窗口的可渲染纹理
// 1参数：图像数据（userdata-IMAGE）
// 1返回值：纹理数据（userdata-TEXTURE）
ETHER_API createTexture(lua_State * L);

// 纹理数据GC函数
// 1参数：纹理数据（userdata-TEXTURE）
// 0返回值
ETHER_API __gc_Texture(lua_State * L);

// 设置纹理透明度
// 2参数：纹理数据（userdata-TEXTURE），透明度数值（number，取值范围0-255）
// 0返回值
ETHER_API texture_SetAlpha(lua_State * L);

// 获取已加载图像尺寸
// 1参数：图像数据（userdata-IMAGE）
// 2返回值：图像宽度（number），图像高度（number）
ETHER_API image_GetSize(lua_State * L);

// 将纹理拷贝至渲染缓冲区内
// 2参数：纹理数据（userdata-TEXTURE），用以描述显示区域的矩形（table）
// 0返回值
ETHER_API copyTexture(lua_State * L);

// 将旋转后的纹理拷贝至渲染缓冲区内
// 5参数：纹理数据（userdata-TEXTURE），旋转角度（number），旋转中心坐标（table），旋转模式（table），用以描述显示区域的矩形（table）
// 0返回值
ETHER_API copyRotateTexture(lua_State * L);

// 将裁剪后的纹理拷贝至渲染缓冲区内
// 3参数：纹理数据（userdata-TEXTURE），用以描述裁剪区域的矩形（table），用以描述显示区域的矩形（table）
// 0返回值
ETHER_API copyReshapeTexture(lua_State * L);

// 将旋转且裁剪后的纹理拷贝至渲染缓冲区内
// 6参数：纹理数据（userdata-TEXTURE），旋转角度（number），旋转中心坐标（table），旋转模式（table），用以描述裁剪区域的矩形（table），用以描述显示区域的矩形（table）
// 0返回值
ETHER_API copyRotateReshapeTexture(lua_State * L);

// 设置窗口绘图颜色
// 1参数：描述颜色的RGBA表（table，取值范围均为0-255）
// 0返回值
ETHER_API setDrawColor(lua_State * L);

// 获取窗口绘图颜色
// 0参数
// 1返回值：用以描述颜色的RGBA表（table，取值范围均为0-255）
ETHER_API getDrawColor(lua_State * L);

// 在指定位置绘制点
// 1参数：点坐标（table）
// 0返回值
ETHER_API drawPoint(lua_State * L);

// 在指定位置绘制直线
// 2参数：起点坐标（table），终点坐标（table）
// 0返回值
ETHER_API drawLine(lua_State * L);

// 在指定位置绘制粗直线
// 3参数：起点坐标（table），终点坐标（table），线条宽度（number）
// 无返回值
ETHER_API drawThickLine(lua_State * L);

// 在指定位置绘制无填充矩形
// 1参数：用以描述显示区域的矩形（table）
// 0返回值
ETHER_API drawRectangle(lua_State * L);

// 在指定位置绘制填充矩形
// 1参数：用以描述显示区域的矩形（table）
// 0返回值
ETHER_API drawFillRectangle(lua_State * L);

// 在指定位置绘制圆角无填充矩形
// 2参数：用以描述显示区域的矩形（table），圆角半径大小（number）
// 0返回值
ETHER_API drawRoundRectangle(lua_State * L);

// 在指定位置绘制圆角填充矩形
// 2参数：用以描述显示区域的矩形（table），圆角半径大小（number）
// 0返回值
ETHER_API drawFillRoundRectangle(lua_State * L);

// 在指定位置绘制无填充圆形
// 2参数：圆心坐标（table），圆半径（number）
// 0返回值
ETHER_API drawCircle(lua_State * L);

// 在指定位置绘制填充圆形
// 2参数：圆心坐标（table），圆半径（number）
// 0返回值
ETHER_API drawFillCircle(lua_State * L);

// 在指定位置绘制无填充椭圆
// 3参数：椭圆中心坐标（table），椭圆x轴半径（number），椭圆y轴半径（number）
// 0返回值
ETHER_API drawEllipse(lua_State * L);

// 在指定位置绘制填充椭圆
// 3参数：椭圆中心坐标（table），椭圆x轴半径（number），椭圆y轴半径（number）
// 0返回值
ETHER_API drawFillEllipse(lua_State * L);

// 在指定位置绘制无填充扇形
// 4参数：扇形所在圆的圆心坐标（table），扇形所在圆的半径（number），扇形开始角度（number），扇形结束角度（number）（扇形从以其所在圆心为原点的二维笛卡尔坐标系的x轴正方向开始绘制，角度的正方向为顺时针方向）
// 0返回值
ETHER_API drawPie(lua_State * L);

// 在指定位置绘制填充扇形
// 4参数：扇形所在圆的圆心坐标（table），扇形所在圆的半径（number），扇形开始角度（number），扇形结束角度（number）（扇形从以其所在圆心为原点的二维笛卡尔坐标系的x轴正方向开始绘制，角度的正方向为顺时针方向）
// 0返回值
ETHER_API drawFillPie(lua_State * L);

// 在指定位置绘制无填充三角形
// 6参数：第一个顶点坐标（table），第二个顶点坐标（table），第三个顶点坐标（table）
// 0返回值
ETHER_API drawTriangle(lua_State * L);

// 在指定位置绘制填充三角形
// 6参数：第一个顶点坐标（table），第二个顶点坐标（table），第三个顶点坐标（table）
// 0返回值
ETHER_API drawFillTriangle(lua_State * L);

// 从文件中加载字体
// 2参数：字体文件路径（string）、字体大小（number）
// 1返回值：成功则返回字体数据（userdata-FONT），失败则返回nil
ETHER_API loadFontFromFile(lua_State * L);

// 从缓冲区中加载字体
// 2参数：缓冲区数据（string）、字体大小（number）
// 1返回值：成功则返回字体数据（userdata-FONT），失败则返回nil
ETHER_API loadFontFromData(lua_State* L);

// 字体数据GC函数
// 1参数：字体数据（userdata-FONT）
// 0返回值
ETHER_API __gc_Font(lua_State * L);

// 获取已加载字体的样式
// 1参数：字体数据（userdata-FONT）
// 1返回值：nil
ETHER_API font_GetStyle(lua_State * L);

// 设置已加载字体的样式
// 2参数：字体数据（userdata-FONT），用以描述字体样式的表（table）
// 0返回值
ETHER_API font_SetStyle(lua_State * L);

// 获取已加载字体的轮廓线宽度
// 1参数：字体数据（userdata-FONT）
// 1返回值：轮廓线宽度（number）
ETHER_API font_GetOutlineWidth(lua_State * L);

// 设置已加载字体的轮廓线宽度
// 2参数：字体数据（userdata-FONT），轮廓线宽度（number）
// 0返回值
ETHER_API font_SetOutlineWidth(lua_State * L);

// 获取字体间距
// 1参数：字体数据（userdata-FONT）
// 1返回值：字体间距（number）
ETHER_API font_GetKerning(lua_State * L);

// 设置字体间距
// 2参数：字体数据（userdata-FONT），字体间距（number）
// 0返回值
ETHER_API font_SetKerning(lua_State * L);

// 获取字体高度
// 1参数：字体数据（userdata-FONT）
// 1返回值：字体高度（number）
ETHER_API font_GetHeight(lua_State * L);

// 获取文本尺寸
// 2参数：字体数据（userdata-FONT），文本内容（string）
// 2返回值：文本宽度（number），文本高度（number）
ETHER_API getTextSize(lua_State * L);

// 获取UTF-8编码格式的文本尺寸
// 2参数：字体数据（userdata-FONT），UTF-8编码格式的文本内容（string）
// 2参数：文本宽度（number），文本高度（number）
ETHER_API getUTF8TextSize(lua_State * L);

// 使用Solid模式创建文本图像
// 3参数：字体数据（userdata-FONT），文本内容（string），用以描述文本颜色的RGBA表（table，取值范围均为0-255）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API createTextImageSolid(lua_State * L);

// 使用Solid模式创建UTF-8编码格式的文本图像
// 3参数：字体数据（userdata-FONT），UTF-8编码格式的文本内容（string），用以描述文本颜色的RGBA表（table，取值范围均为0-255）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API createUTF8TextImageSolid(lua_State * L);

// 使用Shaded模式创建文本图像
// 3参数：字体数据（userdata-FONT），文本内容（string），用以描述文本颜色的RGBA表（table，取值范围均为0-255），用以描述文本背景颜色的RGBA表（table，取值范围均为0-255）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API createTextImageShaded(lua_State * L);

// 使用Shaded模式创建UTF-8编码格式的文本图像
// 3参数：字体数据（userdata-FONT），UTF-8编码格式的文本内容（string），用以描述文本颜色的RGBA表（table，取值范围均为0-255），用以描述文本背景颜色的RGBA表（table，取值范围均为0-255）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API createUTF8TextImageShaded(lua_State * L);

// 使用Blended模式创建文本图像
// 3参数：字体数据（userdata-FONT），文本内容（string），用以描述文本颜色的RGBA表（table，取值范围均为0-255）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API createTextImageBlended(lua_State * L);

// 使用Blended模式创建UTF-8编码格式的文本图像
// 3参数：字体数据（userdata-FONT），UTF-8编码格式的文本内容（string），用以描述文本颜色的RGBA表（table，取值范围均为0-255）
// 1返回值：成功则返回图像数据（userdata-IMAGE），失败则返回nil
ETHER_API createUTF8TextImageBlended(lua_State * L);

#endif // !_GRAPHIC_H_
