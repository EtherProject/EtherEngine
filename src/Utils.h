#ifndef _UTILS_H_
#define _UTILS_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>

#define METANAME_IMAGE "Graphic.Image"
#define METANAME_TEXTURE "Graphic.Texture"
#define METANAME_FONT "Graphic.Font"

#define GetImageDataAtFirstPos()			(SDL_Surface*)(*(void**)luaL_checkudata(L, 1, METANAME_IMAGE))
#define GetTextureDataAtFirstPos()			(SDL_Texture*)(*(void**)luaL_checkudata(L, 1, METANAME_TEXTURE))
#define GetFontDataAtFirstPos()				(TTF_Font*)(*(void**)luaL_checkudata(L, 1, METANAME_FONT))

#define CheckImageDataAtFirstPos(surface)	luaL_argcheck(L, surface, 1, "get image data failed")
#define CheckTextureDataAtFirstPos(texture) luaL_argcheck(L, texture, 1, "get texture data failed")
#define CheckFontDataAtFirstPos(font)		luaL_argcheck(L, font, 1, "get font data failed")

#define CheckPointParam(L, index, point)	luaL_argcheck(L, !GetPointParam(L, index, point), index, "table point expected") 
#define CheckRectParam(L, index, rect)		luaL_argcheck(L, !GetRectParam(L, index, rect), index, "table rect expected") 
#define CheckColorParam(L, index, color)	luaL_argcheck(L, !GetColorParam(L, index, color), index, "table color expected") 

#define CheckTableParam(L, index)			luaL_argcheck(L, lua_istable(L, index), index, "table expected") 

/// <summary>
/// 获取描述点位置的表的参数
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="index">参数位置</param>
/// <param name="point">点位置</param>
/// <returns>是否成功</returns>
int GetPointParam(lua_State* L, int index, SDL_Point& point);

/// <summary>
/// 获取描述矩形位置和大小的表的参数
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="index">参数位置</param>
/// <param name="rect">矩形位置和大小</param>
/// <returns>是否成功</returns>
int GetRectParam(lua_State* L, int index, SDL_Rect& rect);

/// <summary>
/// 获取描述颜色的表的参数
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="index">参数位置</param>
/// <param name="funName">颜色</param>
/// <returns>是否成功</returns>
int GetColorParam(lua_State* L, int index, SDL_Color& color);

#endif // !_UTILS_H_

