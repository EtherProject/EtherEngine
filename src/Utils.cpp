#if _WIN32
#define _WIN32_LEAN_AND_MEAN 1
// 逃不掉的，只能把整个windows.h放进来
#include <Windows.h>
#endif

#include "Utils.h"

template<class Facet>
struct deletable_facet : Facet
{
	template<class ...Args>
	deletable_facet(Args&& ...args)
		: Facet(std::forward<Args>(args)...) {}
	~deletable_facet() {}
};
using mbs_facet_t = deletable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>>;

#if defined(_WIN32) || defined(_WIN64)
const char* EncodingConversion::GBK_LOCALE_NAME = ".936";
#else
const char* EncodingConversion::GBK_LOCALE_NAME = "zh_CN.GB18030";
#endif

std::string EncodingConversion::ToString(const std::wstring& wstr)
{
#ifdef _WIN32
	size_t wcs_size = wstr.size();

	// ACP，默认代码页
	int mbcs_size = WideCharToMultiByte(
		CP_ACP,
		0,
		wstr.data(),
		wcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)wcs_size,
		nullptr, 0, nullptr, nullptr
	);

	std::string mbcs{ (size_t)mbcs_size, '\0', std::allocator<char>{} };

	WideCharToMultiByte(
		CP_ACP,
		0,
		wstr.data(), (int)wcs_size,
		mbcs.data(), mbcs_size,
		nullptr, nullptr
	);

	return mbcs;
#else // posix
	// 考虑使用iconv
	const mbs_facet_t& cvt = std::use_facet<mbs_facet_t>(std::locale());
	std::wstring_convert<mbs_facet_t> converter(&cvt);
	std::string str = converter.to_bytes(wstr);
	return str;
#endif

}

std::wstring EncodingConversion::ToWString(const std::string& str)
{
#ifdef _WIN32
	size_t mbcs_size = str.size();

	// ACP，默认代码页
	int wcs_size = MultiByteToWideChar(
		CP_ACP,
		0,
		str.data(),
		mbcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)mbcs_size,
		nullptr, 0
	);

	std::wstring wcs{ (size_t)wcs_size, L'\0', std::allocator<wchar_t>{} };

	MultiByteToWideChar(
		CP_ACP,
		0,
		str.data(), (int)mbcs_size,
		wcs.data(), wcs_size
	);

	return wcs;
#else
	//std::locale::global(std::locale(""));
	const mbs_facet_t& cvt = std::use_facet<mbs_facet_t>(std::locale());
	std::wstring_convert<mbs_facet_t> converter(&cvt);
	std::wstring wstr = converter.from_bytes(str);
	return wstr;
#endif
}

std::string EncodingConversion::ToGBK(const std::wstring& wstr)
{
#ifdef _WIN32
	size_t wcs_size = wstr.size();

	// 936即GBK
	int mbcs_size = WideCharToMultiByte(
		936,
		0,
		wstr.data(),
		wcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)wcs_size,
		nullptr, 0, nullptr, nullptr
	);

	std::string mbcs{ (size_t)mbcs_size, '\0', std::allocator<char>{} };

	WideCharToMultiByte(
		936,
		0,
		wstr.data(), (int)wcs_size,
		mbcs.data(), mbcs_size,
		nullptr, nullptr
	);

	return mbcs;
#else
	std::wstring_convert<mbs_facet_t> conv(new mbs_facet_t(GBK_LOCALE_NAME));
	std::string  str = conv.to_bytes(wstr);
	return str;
#endif // _WIN32

}

std::wstring EncodingConversion::FromGBK(const std::string& str)
{
#ifdef _WIN32
	size_t mbcs_size = str.size();

	// ACP，默认代码页
	int wcs_size = MultiByteToWideChar(
		936,
		0,
		str.data(),
		mbcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)mbcs_size,
		nullptr, 0
	);

	std::wstring wcs{ (size_t)wcs_size, L'\0', std::allocator<wchar_t>{} };

	MultiByteToWideChar(
		936,
		0,
		str.data(), (int)mbcs_size,
		wcs.data(), wcs_size
	);

	return wcs;
#else
	std::wstring_convert<mbs_facet_t> conv(new mbs_facet_t(GBK_LOCALE_NAME));
	std::wstring wstr = conv.from_bytes(str);
	return wstr;
#endif
}

std::string EncodingConversion::ToUTF8(const std::wstring& wstr)
{
#if defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__)
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.to_bytes((char16_t*)wstr.data(), (char16_t*)wstr.data() + wstr.size());
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
	std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
	return convert.to_bytes(wstr.data(), wstr.data() + wstr.size());
#elif defined(_WIN32)
	size_t wcs_size = wstr.size();

	int mbcs_size = WideCharToMultiByte(
		CP_UTF8,
		0,
		wstr.data(),
		wcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)wcs_size,
		nullptr, 0, nullptr, nullptr
	);

	std::string mbcs{ (size_t)mbcs_size, '\0', std::allocator<char>{} };

	WideCharToMultiByte(
		CP_UTF8,
		0,
		wstr.data(), (int)wcs_size,
		mbcs.data(), mbcs_size,
		nullptr, nullptr
	);

	return mbcs;

#endif
}

std::wstring EncodingConversion::FromUTF8(const std::string& str)
{
#if defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__)
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	auto tmp = convert.from_bytes(str.data(), str.data() + str.size());
	return std::wstring(tmp.data(), tmp.data() + tmp.size());
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
	std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
	return convert.from_bytes(str.data(), str.data() + str.size());
#elif defined(_WIN32)
	size_t mbcs_size = str.size();

	int wcs_size = MultiByteToWideChar(
		CP_UTF8,
		0,
		str.data(),
		mbcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)mbcs_size,
		nullptr, 0
	);

	std::wstring wcs{ (size_t)wcs_size, L'\0', std::allocator<wchar_t>{} };

	// Windows Vista后等价
	MultiByteToWideChar(
		CP_UTF8,
		0,
		str.data(), (int)mbcs_size,
		wcs.data(), wcs_size
	);

	return wcs;
#endif
}

std::string EncodingConversion::GBKToUTF8(const std::string& str)
{
	return ToUTF8(FromGBK(str));
}

std::string EncodingConversion::UTF8ToGBK(const std::string& str)
{
	return ToGBK(FromUTF8(str));
}

std::u16string EncodingConversion::UTF8toUTF16(const std::string& str)
{
#ifdef _WIN32
	size_t mbcs_size = str.size();

	int wcs_size = MultiByteToWideChar(
		CP_UTF8,
		0,
		str.data(),
		mbcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)mbcs_size,
		nullptr, 0
	);

	std::u16string wcs{ (size_t)wcs_size, u'\0', std::allocator<char16_t>{} };
	
	// Windows Vista后等价
	MultiByteToWideChar(
		CP_UTF8,
		0,
		str.data(), (int)mbcs_size,
		(wchar_t*)wcs.data(), wcs_size
	);

	return wcs;
#else
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.from_bytes(str.data(), str.data() + str.size());
#endif
}

std::u32string EncodingConversion::UTF8toUTF32(const std::string& str)
{
#if defined(_MSC_VER)
	throw std::logic_error("utf32 conversion is not implemented");
#else
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
	return convert.from_bytes(str.data(), str.data() + str.size());
#endif
}

std::string EncodingConversion::UTF16toUTF8(const std::u16string& wstr)
{
#ifdef _WIN32
	size_t wcs_size = wstr.size();

	int mbcs_size = WideCharToMultiByte(
		CP_UTF8,
		0,
		(wchar_t*)wstr.data(),
		wcs_size >= INT_MAX ? throw std::invalid_argument("wstring is too long") : (int)wcs_size,
		nullptr, 0, nullptr, nullptr
	);

	std::string mbcs{ (size_t)mbcs_size, '\0', std::allocator<char>{} };

	WideCharToMultiByte(
		CP_UTF8,
		0,
		(wchar_t*)wstr.data(), (int)wcs_size,
		mbcs.data(), mbcs_size,
		nullptr, nullptr
	);

	return mbcs;
#else
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.to_bytes(str.data(), str.data() + str.size());
#endif
}

std::u32string EncodingConversion::UTF16toUTF32(const std::u16string& str)
{
	throw std::logic_error("not implemented");
}

std::string EncodingConversion::UTF32toUTF8(const std::u32string& str)
{
	throw std::logic_error("not implemented");
}

std::u16string EncodingConversion::UTF32toUTF16(const std::u32string& str)
{
	throw std::logic_error("not implemented");
}


int GetPointParam(lua_State* L, int index, SDL_Point& point)
{

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index)) return -1;
	else
	{
		lua_getfield(L, index, "x");
		if (!lua_isnumber(L, -1)) return -1;
		point.x = lua_tonumber(L, -1);
		lua_getfield(L, index, "y");
		if (!lua_isnumber(L, -1)) return -1;
		point.y = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, index, "x");
	point.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	point.y = lua_tonumber(L, -1);

#endif

	return 0;
}


int GetRectParam(lua_State* L, int index, SDL_Rect& rect)
{

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index)) return -1;
	else
	{
		lua_getfield(L, index, "x");
		if (!lua_isnumber(L, -1)) return -1;
		rect.x = lua_tonumber(L, -1);
		lua_getfield(L, index, "y");
		if (!lua_isnumber(L, -1)) return -1;
		rect.y = lua_tonumber(L, -1);
		lua_getfield(L, index, "w");
		if (!lua_isnumber(L, -1)) return -1;
		rect.w = lua_tonumber(L, -1);
		lua_getfield(L, index, "h");
		if (!lua_isnumber(L, -1)) return -1;
		rect.h = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, index, "x");
	rect.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	rect.y = lua_tonumber(L, -1);
	lua_getfield(L, index, "w");
	rect.w = lua_tonumber(L, -1);
	lua_getfield(L, index, "h");
	rect.h = lua_tonumber(L, -1);

#endif

	return 0;
}


int GetColorParam(lua_State* L, int index, SDL_Color& color)
{

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index)) return -1;
	else
	{
		lua_getfield(L, index, "r");
		if (!lua_isnumber(L, -1)) return -1;
		color.r = lua_tonumber(L, -1);
		lua_getfield(L, index, "g");
		if (!lua_isnumber(L, -1)) return -1;
		color.g = lua_tonumber(L, -1);
		lua_getfield(L, index, "b");
		if (!lua_isnumber(L, -1)) return -1;
		color.b = lua_tonumber(L, -1);
		lua_getfield(L, index, "a");
		if (!lua_isnumber(L, -1)) return -1;
		color.a = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, index, "r");
	color.r = lua_tonumber(L, -1);
	lua_getfield(L, index, "g");
	color.g = lua_tonumber(L, -1);
	lua_getfield(L, index, "b");
	color.b = lua_tonumber(L, -1);
	lua_getfield(L, index, "a");
	color.a = lua_tonumber(L, -1);

#endif 

	return 0;
}