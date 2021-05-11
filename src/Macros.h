#ifndef _MACROS_H_
#define _MACROS_H_

/* 定义 _ETHER_DEUBG_ 以开启Debug模式 */
#define _ETHER_DEBUG_

#define _VERSION_ "Release v4.0.1"

#define ETHER_API extern "C" int

struct Macro
{
	const char* name;
	int value;
};

#endif // !_MACROS_H_
