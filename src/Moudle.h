#ifndef _MOUDLE_H_
#define _MOUDLE_H_

#include "Macros.h"

#include <lua.hpp>

#include <vector>
using namespace std;

class Moudle
{
public:
	Moudle() {};
	~Moudle() {};
	void OpenMoudle(void);

protected:
	lua_State* _pL = nullptr;
	vector<luaL_Reg> _vCMethods;
	vector<Macro> _vMacros;
};

#endif // !_MOUDLE_H_
