#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include "Module.h"

#include "zlib.h"
#include <lua.hpp>

class ModuleCompress : public Module
{
public:
	static ModuleCompress& Instance();
	~ModuleCompress() {};

private:
	ModuleCompress();

};

ETHER_API eapi_compress(lua_State* L);

ETHER_API eapi_decompress(lua_State* L);

#endif // !_COMPRESS_H_
