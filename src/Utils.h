#ifndef _UTILS_H_
#define _UTILS_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>

#include <codecvt>
#include <locale>
#include <string>

#define CheckPointParam(L, index, point)	luaL_argcheck(L, !GetPointParam(L, index, point), index, "table point expected") 
#define CheckRectParam(L, index, rect)		luaL_argcheck(L, !GetRectParam(L, index, rect), index, "table rect expected") 
#define CheckColorParam(L, index, color)	luaL_argcheck(L, !GetColorParam(L, index, color), index, "table color expected") 

#define CheckTableParam(L, index)			luaL_argcheck(L, lua_istable(L, index), index, "table expected") 

class EncodingConversion
{
public:
	EncodingConversion() = delete;
	EncodingConversion(const EncodingConversion&) = delete;
	EncodingConversion(EncodingConversion&&) = delete;
	~EncodingConversion() = delete;
	EncodingConversion& operator=(const EncodingConversion&) = delete;
	EncodingConversion& operator=(EncodingConversion&&) = delete;

	static std::string    ToString(const std::wstring& wstr);
	static std::wstring   ToWString(const std::string& str);
	static std::string    GBKToUTF8(const std::string& str);
	static std::string    UTF8ToGBK(const std::string& str);
	static std::u16string UTF8toUTF16(const std::string& str);
	static std::u32string UTF8toUTF32(const std::string& str);
	static std::string    UTF16toUTF8(const std::u16string& str);
	static std::u32string UTF16toUTF32(const std::u16string& str);
	static std::string    UTF32toUTF8(const std::u32string& str);
	static std::u16string UTF32toUTF16(const std::u32string& str);
private:
	static std::string    ToGBK(const std::wstring& wstr);
	static std::wstring   FromGBK(const std::string& str);
	static std::string    ToUTF8(const std::wstring& wstr);
	static std::wstring   FromUTF8(const std::string& str);
private:
	static const char* GBK_LOCALE_NAME;
};

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

