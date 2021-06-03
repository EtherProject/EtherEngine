#ifndef _UTILS_H_
#define _UTILS_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL2/SDL.h>

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
/// ��ȡ������λ�õı�Ĳ���
/// </summary>
/// <param name="L">��ǰLua���������</param>
/// <param name="index">����λ��</param>
/// <param name="point">��λ��</param>
/// <returns>�Ƿ�ɹ�</returns>
int GetPointParam(lua_State* L, int index, SDL_Point& point);

/// <summary>
/// ��ȡ��������λ�úʹ�С�ı�Ĳ���
/// </summary>
/// <param name="L">��ǰLua���������</param>
/// <param name="index">����λ��</param>
/// <param name="rect">����λ�úʹ�С</param>
/// <returns>�Ƿ�ɹ�</returns>
int GetRectParam(lua_State* L, int index, SDL_Rect& rect);

/// <summary>
/// ��ȡ������ɫ�ı�Ĳ���
/// </summary>
/// <param name="L">��ǰLua���������</param>
/// <param name="index">����λ��</param>
/// <param name="funName">��ɫ</param>
/// <returns>�Ƿ�ɹ�</returns>
int GetColorParam(lua_State* L, int index, SDL_Color& color);

#endif // !_UTILS_H_

