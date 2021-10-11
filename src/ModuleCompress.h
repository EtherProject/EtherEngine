#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include "Module.h"

#include "zlib.h"
#include "lua.hpp"

#include <iostream>


class ModuleCompress : public Module
{
public:
	static ModuleCompress& Instance();
	~ModuleCompress() {};

private:
	ModuleCompress();

};

/*
* 压缩数据
* 1或2参数：原始数据（string），压缩等级（可选，范围为1-10，默认为6）
* 1返回值：压缩后数据（string）
* 备注：在原始数据相同的一般情况下，压缩等级越高，耗时越长且压缩率越小；
* 特别地，压缩等级为1只归档数据为压缩格式，并不进行压缩处理
*/
ETHER_API compressData(lua_State* L);

/*
* 解压数据
* 1参数：压缩后数据（string）
* 1返回值：原始数据（string）
*/
ETHER_API decompressData(lua_State* L);

#endif // !_COMPRESS_H_
