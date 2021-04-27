#ifndef _MODULE_H_
#define _MODULE_H_

#include "Macros.h"

#include <lua.hpp>

#include <vector>
using namespace std;

class Module
{
public:
	virtual Module& Instance();
	~Module() {};
	vector<luaL_Reg> _vCMethods;
	vector<Macro> _vMacros;

protected:
	Module() {};
	
};

#endif // !_MODULE_H_
