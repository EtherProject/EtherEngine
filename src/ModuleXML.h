#ifndef _MODULE_XML_H_
#define _MODULE_XML_H_

#include "Module.h"
#include "Macros.h"

#include <lua.hpp>
#include <pugixml.hpp>
using namespace pugi;

#include <unordered_map>
using namespace std;

#define NODETYPE_EMPTY						0
#define NODETYPE_DOCUMENT					1
#define NODETYPE_ELEMENT					2
#define NODETYPE_PLAINCHARADATA				3
#define NODETYPE_CHARADATA					4
#define NODETYPE_COMMENT					5
#define NODETYPE_PROCESSINS					6
#define NODETYPE_DECLARATION				7
#define NODETYPE_DOCTYPE					8

#define METANAME_DOCUMENT					"XML.Document"
#define METANAME_NODE						"XML.Node"
#define METANAME_ATTRIBUTE					"XML.Attribute"

#define GetDocumentDataAt1stPos()			(xml_document*)(*(void**)luaL_checkudata(L, 1, METANAME_DOCUMENT))
#define GetNodeDataAt1stPos()				(xml_node*)(*(void**)luaL_checkudata(L, 1, METANAME_NODE))
#define GetAttributeDataAt1stPos()			(xml_attribute*)(*(void**)luaL_checkudata(L, 1, METANAME_ATTRIBUTE))

#define CheckDocumentDataAt1stPos(doc)		luaL_argcheck(L, doc, 1, "get document data failed")
#define CheckNodeDataAt1stPos(node)			luaL_argcheck(L, node, 1, "get node data failed")
#define CheckAttributeDataAt1stPos(attri)	luaL_argcheck(L, attri, 1, "get attribute data failed")

#define LoadXMLAndCheck(doc, res)\
	xml_parse_result result = res;\
	luaL_argcheck(L, !result.status, 1, string("XML parse error: ").append(result.description()).c_str());\
	xml_document** uppdoc = (xml_document**)lua_newuserdata(L, sizeof(xml_document*));\
	*uppdoc = doc; luaL_getmetatable(L, METANAME_DOCUMENT); lua_setmetatable(L, -2);

#define CopyAndPushNewUserdataToStack(L, T, src, name)\
	T* p = new T(src);\
	if (p->empty()) lua_pushnil(L);\
	else { T** upp = (T**)lua_newuserdata(L, sizeof(T*));\
		*upp = p; luaL_getmetatable(L, name); lua_setmetatable(L, -2); }

class ModuleXML : public Module
{
public:
	static unordered_map<int, int> mapNodeType;
	static ModuleXML& Instance();
	~ModuleXML() {};

private:
	ModuleXML();

};

ETHER_API node_GetRoot(lua_State* L);

ETHER_API node_GetParent(lua_State* L);

ETHER_API node_GetNextSibling(lua_State* L);

ETHER_API node_GetPreviousSibling(lua_State* L);

ETHER_API node_GetChild(lua_State* L);

ETHER_API node_GetFirstChild(lua_State* L);

ETHER_API node_GetLastChild(lua_State* L);

ETHER_API node_GetName(lua_State* L);

ETHER_API node_GetValue(lua_State* L);

ETHER_API node_GetChildValue(lua_State* L);

ETHER_API node_GetType(lua_State* L);

ETHER_API node_GetText(lua_State* L);

ETHER_API node_GetTextAsInteger(lua_State* L);

ETHER_API node_GetTextAsNumber(lua_State* L);

ETHER_API node_GetAttribute(lua_State* L);

ETHER_API node_GetFirstAttribute(lua_State* L);

ETHER_API node_GetLastAttribute(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

ETHER_API document_GetChild(lua_State* L);

ETHER_API __gc_Document(lua_State* L);

ETHER_API loadXML(lua_State* L);

ETHER_API loadXMLFromFile(lua_State* L);

ETHER_API loadXMLFromData(lua_State* L);

#endif // !_MODULE_XML_H_
