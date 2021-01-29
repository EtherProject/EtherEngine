#ifndef _STRING_H_
#define _STRING_H_

#include "Moudle.h"
#include "Macros.h"
#include "util.h"

#include <lua.hpp>
#include "EncodingConversion.h"

ETHER_API gbkToUTF8(lua_State* L);

ETHER_API utf8ToGBK(lua_State* L);

class MoudleString : public Moudle
{
public:
	MoudleString(lua_State* L);
	~MoudleString() {};

};

#endif // !_STRING_H_
