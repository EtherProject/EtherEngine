#ifndef _MOUDLE_H_
#define _MOUDLE_H_

#include "Macros.h"

#include <lua.hpp>

#include <string>
#include <vector>
using namespace std;

class Moudle
{
public:
	Moudle(lua_State* L, string name) : _pL(L), _strName(name) {};
	~Moudle() {};
	void OpenMoudle(void);

protected:
	string _strName;
	lua_State* _pL = nullptr;
	vector<luaL_Reg> _vCMethods;
	vector<Macro> _vMacros;
};

#endif // !_MOUDLE_H_
