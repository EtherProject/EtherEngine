#ifndef _MODULE_H_
#define _MODULE_H_

#include "Macros.h"

#include <lua.hpp>

#include <string>
#include <vector>


struct MetaData
{
	std::string name;
	std::vector<luaL_Reg> cFuns;
	lua_CFunction gcFun = [](lua_State* L) -> int { return 0; };
};

class Module
{
public:
	virtual Module& Instance();
	~Module() {};
	void PushMetaDataToGlobal(lua_State* L);
	void PushMoudleDataToStack(lua_State* L);

protected:
	Module() {};
	std::vector<luaL_Reg> _vCMethods;
	std::vector<Macro> _vMacros;
	std::vector<MetaData> _vMetaData;
	
};

#endif // !_MODULE_H_
