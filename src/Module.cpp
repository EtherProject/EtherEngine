#include "Module.h"

Module& Module::Instance()
{
	static Module* _instance = new Module();
	return *_instance;
}