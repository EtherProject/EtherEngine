#include "ModuleXML.h"


unordered_map<int, int> ModuleXML::mapNodeType = {
	{ node_null, NODETYPE_EMPTY },
	{ node_document, NODETYPE_DOCUMENT },
	{ node_element, NODETYPE_ELEMENT },
	{ node_pcdata, NODETYPE_PLAINCHARADATA },
	{ node_cdata, NODETYPE_CHARADATA },
	{ node_comment, NODETYPE_COMMENT },
	{ node_pi, NODETYPE_PROCESSINS },
	{ node_declaration, NODETYPE_DECLARATION },
	{ node_doctype, NODETYPE_DOCTYPE },
};


ModuleXML& ModuleXML::Instance()
{
	static ModuleXML* _instance = new ModuleXML();
	return *_instance;
}


ModuleXML::ModuleXML()
{
	_vCMethods = {
		{ "LoadXML", loadXML },
		{ "LoadXMLFromFile", loadXMLFromFile },
		{ "LoadXMLFromData", loadXMLFromData },
	};

	_vMetaData = {
		{
			METANAME_DOCUMENT,
			{
				{ "GetChild", document_GetChild },
			},
			__gc_Document
		},
		{
			METANAME_NODE,
			{
				{ "node_GetRoot", node_GetRoot },
				{ "node_GetParent", node_GetParent },
				{ "node_GetNextSibling", node_GetNextSibling },
				{ "node_GetPreviousSibling", node_GetPreviousSibling },
				{ "node_GetChild", node_GetChild },
				{ "node_GetFirstChild", node_GetFirstChild },
				{ "node_GetLastChild", node_GetLastChild },
				{ "node_GetName", node_GetName },
				{ "node_GetValue", node_GetValue },
				{ "node_GetChildValue", node_GetChildValue },
				{ "node_GetType", node_GetType },
				{ "node_GetText", node_GetText },
				{ "node_GetTextAsInteger", node_GetTextAsInteger },
				{ "node_GetTextAsNumber", node_GetTextAsNumber },
				{ "node_GetAttribute", node_GetAttribute },
				{ "node_GetFirstAttribute", node_GetFirstAttribute },
				{ "node_GetLastAttribute", node_GetLastAttribute },
			},
			__gc_Node
		},
	};
}


ETHER_API node_GetRoot(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		node->parent(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetParent(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		node->parent(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetNextSibling(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		node->next_sibling(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetPreviousSibling(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		node->previous_sibling(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetChild(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node, 
		node->child(luaL_checkstring(L, 2)), METANAME_NODE);

	return 1;
}


ETHER_API node_GetFirstChild(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		node->first_child(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetLastChild(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		node->last_child(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetName(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	lua_pushstring(L, node->name());

	return 1;
}


ETHER_API node_GetValue(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	lua_pushstring(L, node->value());

	return 1;
}


ETHER_API node_GetChildValue(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	lua_pushstring(L, lua_gettop(L) > 1 ? 
		node->child_value(luaL_checkstring(L, 2)) : node->child_value());

	return 1;
}


ETHER_API node_GetType(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	auto itorType = ModuleXML::mapNodeType.find(node->type());
	if (itorType != ModuleXML::mapNodeType.end())
		lua_pushinteger(L, itorType->second);
	else
		lua_pushinteger(L, NODETYPE_EMPTY);

	return 1;
}


ETHER_API node_GetText(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	lua_pushstring(L, node->text().as_string());

	return 1;
}


ETHER_API node_GetTextAsInteger(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	lua_pushinteger(L, node->text().as_llong());

	return 1;
}


ETHER_API node_GetTextAsNumber(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	lua_pushnumber(L, node->text().as_double());

	return 1;
}


ETHER_API node_GetAttribute(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_attribute,
		node->attribute(luaL_checkstring(L, 2)), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API node_GetFirstAttribute(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_attribute,
		node->first_attribute(), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API node_GetLastAttribute(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	CopyAndPushNewUserdataToStack(L, xml_attribute,
		node->last_attribute(), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API __gc_Node(lua_State* L)
{
	xml_node* node = GetNodeDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckNodeDataAt1stPos(node);
#endif
	delete node;
	node = nullptr;

	return 0;
}


ETHER_API document_GetChild(lua_State* L)
{
	xml_document* doc = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(doc);
#endif
	CopyAndPushNewUserdataToStack(L, xml_node,
		doc->child(luaL_checkstring(L, 2)), METANAME_NODE);

	return 1;
}


ETHER_API __gc_Document(lua_State* L)
{
	xml_document* doc = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(doc);
#endif
	delete doc;
	doc = nullptr;

	return 0;
}


ETHER_API loadXML(lua_State* L)
{
	xml_document* document = new xml_document();
	LoadXMLAndCheck(document, document->load_string(luaL_checkstring(L, 1)));

	return 1;
}


ETHER_API loadXMLFromFile(lua_State* L)
{
	xml_document* document = new xml_document();
	LoadXMLAndCheck(document, document->load_file(luaL_checkstring(L, 1)));

	return 1;
}


ETHER_API loadXMLFromData(lua_State* L)
{
	size_t len;
	xml_document* document = new xml_document();
	LoadXMLAndCheck(document, document->load_buffer(luaL_checklstring(L, 1, &len), len));

	return 1;
}