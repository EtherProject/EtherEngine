#ifndef _STRING_H_
#define _STRING_H_

#include "Moudle.h"
#include "Macros.h"
#include "util.h"

#include <lua.hpp>
#include "EncodingConversion.h"

/*
* 将GBK编码字符串转换为UTF-8编码
* 1参数：GBK编码字符串（string）
* 1返回值：UTF-8编码字符串（string）
*/
ETHER_API gbkToUTF8(lua_State* L);

/*
* 将UTF-8编码字符串转换为GBK编码
* 1参数：UTF-8编码字符串（string）
* 1返回值：GBK编码字符串（string）
*/
ETHER_API utf8ToGBK(lua_State* L);

class MoudleString : public Moudle
{
public:
	MoudleString(lua_State* L);
	~MoudleString() {};

};

#endif // !_STRING_H_
