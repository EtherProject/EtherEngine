#include "ModuleCompress.h"


ModuleCompress& ModuleCompress::Instance()
{
	static ModuleCompress* _instance = new ModuleCompress();
	return *_instance;
}


ModuleCompress::ModuleCompress()
{
	_vCMethods = {
		{"CompressData", eapi_compress},
		{"DecompressData", eapi_decompress},
	};
}


ETHER_API eapi_compress(lua_State* L)
{
	size_t size = luaL_checknumber(L, 2);
	const char* raw_data = luaL_checklstring(L, 1, &size);
	uLong len_raw_data = strlen(raw_data) + 1, len_compress_data = compressBound(len_raw_data);
	char* buffer_compress_data = nullptr;
	luaL_argcheck(L, 
		((buffer_compress_data = (char*)malloc(sizeof(char) * len_compress_data)))
			&& compress((Bytef*)buffer_compress_data, &len_compress_data, (Bytef*)raw_data, len_raw_data) == Z_OK,
		1, 
		"failed to compress, consider reducing the data size of compression"
	);
	lua_pushlstring(L, buffer_compress_data, len_compress_data);
	lua_pushnumber(L, len_raw_data);
	free(buffer_compress_data);

	return 2;
}


ETHER_API eapi_decompress(lua_State* L)
{
	const char* compress_data = luaL_checkstring(L, 1);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, luaL_checknumber(L, 2) > 0, 2, "original data size must be greater than or equal to 0");
#endif
	uLong len_raw_data = luaL_checknumber(L, 2), len_compress_data = compressBound(len_raw_data);
	char* buffer_raw_data = nullptr;
	luaL_argcheck(L,
		((buffer_raw_data = (char*)malloc(sizeof(char) * len_raw_data)))
		&& uncompress((Bytef*)buffer_raw_data, &len_raw_data, (Bytef*)compress_data, len_compress_data) == Z_OK,
		2,
		"failed to decompress, consider increasing the dest data size"
	);
	lua_pushlstring(L, buffer_raw_data, len_raw_data);
	free(buffer_raw_data);

	return 1;
}