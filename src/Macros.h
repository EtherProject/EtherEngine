#ifndef _MACROS_H_
#define _MACROS_H_

/* 定义 _ETHER_DEUBG_ 以开启Debug模式 */
#ifndef _ETHER_DEBUG_
#define _ETHER_DEBUG_
#endif

#define _VERSION_ "Alpha v4.1.0"

#define ETHER_API extern "C" int

struct Macro
{
	const char* name;
	int value;
};

#endif // !_MACROS_H_
