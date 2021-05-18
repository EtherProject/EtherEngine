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
#define GetNodeData(idx)					(xml_node*)(*(void**)luaL_checkudata(L, idx, METANAME_NODE))
#define GetAttributeData(idx)				(xml_attribute*)(*(void**)luaL_checkudata(L, idx, METANAME_ATTRIBUTE))

#define CheckDocumentDataAt1stPos(doc)		luaL_argcheck(L, doc, 1, "get document data failed")
#define CheckNodeData(node, idx)			luaL_argcheck(L, node, idx, "get node data failed")
#define CheckAttributeData(attri, idx)		luaL_argcheck(L, attri, idx, "get attribute data failed")

#define CheckHandlerFunctionAt2ndPos()		luaL_argcheck(L, lua_isfunction(L, 2) && lua_gettop(L) == 2,\
												2, "the last param callback handler must be function")

#define REFKEY_NODE_FIND_HANDLER			"temp_xml_node_find_handler"
#define REFKEY_ATTRIBUTE_FIND_HANDLER		"temp_xml_attribute_find_handler"
#define REFKEY_NODE_TRAVERSE_HANDLER		"temp_xml_node_traverse_handler"

#define LoadXMLAndCheck(doc, res)\
	xml_parse_result result = res;\
	luaL_argcheck(L, !result.status, 1, string("XML parse error: ").append(result.description()).c_str());\
	xml_document** uppdoc = (xml_document**)lua_newuserdata(L, sizeof(xml_document*));\
	*uppdoc = doc; luaL_getmetatable(L, METANAME_DOCUMENT); lua_setmetatable(L, -2);

#define CopyAndPushNewUserdataToStack(T, src, name)\
	T* p = new T(src); if (p->empty()) lua_pushnil(L);\
	else { T** upp = (T**)lua_newuserdata(L, sizeof(T*));\
		*upp = p; luaL_getmetatable(L, name); lua_setmetatable(L, -2); }

#define CopyAndPushNewUserdataToTable(T, src, name, idx)\
	lua_pushnumber(L, idx); T* p = new T(src);\
	T** upp = (T**)lua_newuserdata(L, sizeof(T*));\
	**upp = *p; luaL_getmetatable(L, name);\
	lua_setmetatable(L, -2); lua_settable(L, -3); idx++;

#define CopyAndPushHandlerParamToStack(T, src, name)\
	T* p = new T(src); T** upp = (T**)lua_newuserdata(_L, sizeof(T*));\
	*upp = p; luaL_getmetatable(_L, name); lua_setmetatable(_L, -2);

struct XML_Searcher
{
	lua_State* _L;

	XML_Searcher(lua_State* L) : _L(L) {}

	bool operator()(pugi::xml_node node) const
	{
		lua_getfield(_L, LUA_REGISTRYINDEX, REFKEY_NODE_FIND_HANDLER);
		CopyAndPushHandlerParamToStack(xml_node, node, METANAME_NODE);
		lua_call(_L, 1, 1);
		bool flag = lua_toboolean(_L, -1);
		lua_pop(_L, 1);
		return flag;
	}

	bool operator()(pugi::xml_attribute attr) const
	{
		lua_getfield(_L, LUA_REGISTRYINDEX, REFKEY_ATTRIBUTE_FIND_HANDLER);
		CopyAndPushHandlerParamToStack(xml_attribute, attr, METANAME_ATTRIBUTE);
		lua_call(_L, 1, 1);
		bool flag = lua_toboolean(_L, -1);
		lua_pop(_L, 1);
		return flag;
	}
};

struct XML_Walker : xml_tree_walker
{
	lua_State* _L;

	XML_Walker(lua_State* L) : _L(L) {}

	virtual bool for_each(xml_node& node)
	{
		lua_getfield(_L, LUA_REGISTRYINDEX, REFKEY_NODE_TRAVERSE_HANDLER);
		CopyAndPushHandlerParamToStack(xml_node, node, METANAME_NODE);
		lua_pushnumber(_L, depth() + 1);
		lua_call(_L, 2, 1);
		bool flag = lua_isnil(_L, -1) ? true : lua_toboolean(_L, -1);
		lua_pop(_L, 1);
		return flag;
	}
};

struct XML_Writer : xml_writer
{
	lua_State* _L;

	XML_Writer(lua_State* L) : _L(L) {}

	virtual void write(const void* data, size_t size)
	{
		lua_pushlstring(_L, (char*)data, size);
	}
};

class ModuleXML : public Module
{
public:
	static unordered_map<int, int> mapNodeType;
	static ModuleXML& Instance();
	~ModuleXML() {};

private:
	ModuleXML();

};

ETHER_API attribute_GetName(lua_State* L);

ETHER_API attribute_GetValue(lua_State* L);

ETHER_API attribute_GetValueAsInteger(lua_State* L);

ETHER_API attribute_GetValueAsNumber(lua_State* L);

ETHER_API attribute_GetValueAsBoolean(lua_State* L);

ETHER_API attribute_SetName(lua_State* L);

ETHER_API attribute_SetValue(lua_State* L);

ETHER_API attribute_SetIntegerValue(lua_State* L);

ETHER_API attribute_SetNumberValue(lua_State* L);

ETHER_API attribute_SetBooleanValue(lua_State* L);

ETHER_API attribute_GetNextAttribute(lua_State* L);

ETHER_API attribute_GetPreviousAttribute(lua_State* L);

ETHER_API __gc_Attribute(lua_State* L);

ETHER_API node_GetRoot(lua_State* L);

ETHER_API node_GetParent(lua_State* L);

ETHER_API node_GetNextSibling(lua_State* L);

ETHER_API node_GetPreviousSibling(lua_State* L);

ETHER_API node_GetChild(lua_State* L);

ETHER_API node_GetChildByAttribute(lua_State* L);

ETHER_API node_GetFirstChild(lua_State* L);

ETHER_API node_GetLastChild(lua_State* L);

ETHER_API node_GetChildren(lua_State* L);

ETHER_API node_GetName(lua_State* L);

ETHER_API node_GetValue(lua_State* L);

ETHER_API node_GetChildValue(lua_State* L);

ETHER_API node_GetType(lua_State* L);

ETHER_API node_GetText(lua_State* L);

ETHER_API node_GetTextAsInteger(lua_State* L);

ETHER_API node_GetTextAsNumber(lua_State* L);

ETHER_API node_GetTextAsBoolean(lua_State* L);

ETHER_API node_GetAttribute(lua_State* L);

ETHER_API node_GetFirstAttribute(lua_State* L);

ETHER_API node_GetLastAttribute(lua_State* L);

ETHER_API node_GetAttributes(lua_State* L);

ETHER_API node_SetName(lua_State* L);

ETHER_API node_SetValue(lua_State* L);

ETHER_API node_SetText(lua_State* L);

ETHER_API node_SetTextAsInteger(lua_State* L);

ETHER_API node_SetTextAsNumber(lua_State* L);

ETHER_API node_SetTextAsBoolean(lua_State* L);

ETHER_API node_AppendAttribute(lua_State* L);

ETHER_API node_PrependAttribute(lua_State* L);

ETHER_API node_InsertAttributeAfter(lua_State* L);

ETHER_API node_InsertAttributeBefore(lua_State* L);

ETHER_API node_AppendAttributeCopy(lua_State* L);

ETHER_API node_PrependAttributeCopy(lua_State* L);

ETHER_API node_InsertAttributeCopyAfter(lua_State* L);

ETHER_API node_InsertAttributeCopyBefore(lua_State* L);

ETHER_API node_MoveNodeToChildAppend(lua_State* L);

ETHER_API node_MoveNodeToChildPrepend(lua_State* L);

ETHER_API node_MoveNodeToChildInsertAfter(lua_State* L);

ETHER_API node_MoveNodeToChildInsertBefore(lua_State* L);

ETHER_API node_RemoveAttribute(lua_State* L);

ETHER_API node_RemoveAttributes(lua_State* L);

ETHER_API node_RemoveChild(lua_State* L);

ETHER_API node_RemoveChildren(lua_State* L);

ETHER_API node_FindDirectChild(lua_State* L);

ETHER_API node_FindDescendedChild(lua_State* L);

ETHER_API node_FindAttribute(lua_State* L);

ETHER_API node_Traverse(lua_State* L);

ETHER_API node_Print(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

ETHER_API document_GetChild(lua_State* L);

ETHER_API document_SaveAsFile(lua_State* L);

ETHER_API document_Traverse(lua_State* L);

ETHER_API document_Print(lua_State* L);

ETHER_API __gc_Document(lua_State* L);

ETHER_API loadXML(lua_State* L);

ETHER_API loadXMLFromFile(lua_State* L);

ETHER_API loadXMLFromData(lua_State* L);

#endif // !_MODULE_XML_H_
