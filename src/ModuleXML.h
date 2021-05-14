#ifndef _MODULE_XML_H_
#define _MODULE_XML_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>
#include <pugixml.hpp>
using namespace pugi;

#define METANAME_DOCUMENT	"XML.Document"

class ModuleXML : public Module
{
public:
	static ModuleXML& Instance();
	~ModuleXML() {};

private:
	ModuleXML();

};

ETHER_API loadXML(lua_State* L);

ETHER_API loadXMLFromFile(lua_State* L);

#endif // !_MODULE_XML_H_
