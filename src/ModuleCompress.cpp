#include "ModuleCompress.h"


ModuleCompress& ModuleCompress::Instance()
{
	static ModuleCompress* _instance = new ModuleCompress();
	return *_instance;
}


ModuleCompress::ModuleCompress()
{
	_vCMethods = {
		{"CompressData", compressData},
		{"DecompressData", decompressData},
	};
}


ETHER_API compressData(lua_State* L)
{
	size_t size;
	const char* raw_data = luaL_checklstring(L, 1, &size);
	uLong len_compress_data = compressBound(size), ulSize = size;
	char* buffer_compress_data = (char*)malloc(sizeof(uLong) + sizeof(char) * len_compress_data);
	switch (lua_isnumber(L, 2) ? compress2((Bytef*)(buffer_compress_data + sizeof(uLong)), &len_compress_data, (Bytef*)raw_data, size, lua_tonumber(L, 2)) : compress((Bytef*)(buffer_compress_data + sizeof(uLong)), &len_compress_data, (Bytef*)raw_data, size))
	{
	case Z_STREAM_ERROR:
		luaL_argerror(L, 2, "failed to compress, invalid compress level");
		break;
	case Z_MEM_ERROR:
		luaL_argerror(L, 1, "failed to compress, memory error");
		break;
	case Z_BUF_ERROR:
		luaL_argerror(L, 1, "failed to compress, buffer error");
		break;
	default:
		break;
	}
	memcpy(buffer_compress_data, &ulSize, sizeof(uLong));
	lua_pushlstring(L, buffer_compress_data, sizeof(uLong) + len_compress_data);
	free(buffer_compress_data);

	return 1;
}


ETHER_API decompressData(lua_State* L)
{
	size_t size;
	const char* compress_data = luaL_checklstring(L, 1, &size);
	uLong raw_size = *(uLong*)compress_data;
	char* buffer_raw_data = (char*)malloc(sizeof(char) * raw_size);
	switch (uncompress((Bytef*)buffer_raw_data, &raw_size, (Bytef*)(compress_data + sizeof(uLong)), size - sizeof(uLong)))
	{
	case Z_DATA_ERROR:
		luaL_argerror(L, 1, "failed to decompress, data content error");
		break;
	case Z_MEM_ERROR:
		luaL_argerror(L, 1, "failed to decompress, memory error");
		break;
	case Z_BUF_ERROR:
		luaL_argerror(L, 1, "failed to decompress, buffer error");
		break;
	default:
		break;
	}
	lua_pushlstring(L, buffer_raw_data, raw_size);
	free(buffer_raw_data);

	return 1;
}