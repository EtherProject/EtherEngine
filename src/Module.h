#ifndef _MODULE_H_
#define _MODULE_H_

#include "Macros.h"

#include <lua.hpp>

#include <string>
#include <vector>
using namespace std;

class Module
{
public:
	Module(lua_State* L, string name) : _pL(L), _strName(name) {};
	~Module() {};
	void OpenModule(void);

protected:
	string _strName;
	lua_State* _pL = nullptr;
	vector<luaL_Reg> _vCMethods;
	vector<Macro> _vMacros;
};

#endif // !_MODULE_H_
