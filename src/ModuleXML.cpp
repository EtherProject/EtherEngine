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
				{ "SaveAsFile", document_SaveAsFile },
				{ "Traverse", document_Traverse },
				{ "Print", document_Print },
			},
			__gc_Document
		},
		{
			METANAME_NODE,
			{
				{ "GetRoot", node_GetRoot },
				{ "GetParent", node_GetParent },
				{ "GetNextSibling", node_GetNextSibling },
				{ "GetPreviousSibling", node_GetPreviousSibling },
				{ "GetChild", node_GetChild },
				{ "GetFirstChild", node_GetFirstChild },
				{ "GetLastChild", node_GetLastChild },
				{ "GetChildren", node_GetChildren },
				{ "GetName", node_GetName },
				{ "GetValue", node_GetValue },
				{ "GetChildValue", node_GetChildValue },
				{ "GetType", node_GetType },
				{ "GetText", node_GetText },
				{ "GetTextAsInteger", node_GetTextAsInteger },
				{ "GetTextAsNumber", node_GetTextAsNumber },
				{ "GetTextAsBoolean", node_GetTextAsBoolean },
				{ "GetAttribute", node_GetAttribute },
				{ "GetFirstAttribute", node_GetFirstAttribute },
				{ "GetLastAttribute", node_GetLastAttribute },
				{ "GetAttributes", node_GetAttributes },
				{ "SetName", node_SetName },
				{ "SetValue", node_SetValue },
				{ "SetText", node_SetText },
				{ "SetTextAsInteger", node_SetTextAsInteger },
				{ "SetTextAsNumber", node_SetTextAsNumber },
				{ "SetTextAsBoolean", node_SetTextAsBoolean },
				{ "AppendAttribute", node_AppendAttribute },
				{ "PrependAttribute", node_PrependAttribute },
				{ "InsertAttributeAfter", node_InsertAttributeAfter },
				{ "InsertAttributeBefore", node_InsertAttributeBefore },
				{ "AppendAttributeCopy", node_AppendAttributeCopy },
				{ "PrependAttributeCopy", node_PrependAttributeCopy },
				{ "InsertAttributeCopyAfter", node_InsertAttributeCopyAfter },
				{ "InsertAttributeCopyBefore", node_InsertAttributeCopyBefore },
				{ "MoveNodeToChildAppend", node_MoveNodeToChildAppend },
				{ "MoveNodeToChildPrepend", node_MoveNodeToChildPrepend },
				{ "MoveNodeToChildInsertAfter", node_MoveNodeToChildInsertAfter },
				{ "MoveNodeToChildInsertBefore", node_MoveNodeToChildInsertBefore },
				{ "RemoveAttribute", node_RemoveAttribute },
				{ "RemoveAttributes", node_RemoveAttributes },
				{ "RemoveChild", node_RemoveChild },
				{ "RemoveChildren", node_RemoveChildren },
				{ "FindDirectChild", node_FindDirectChild },
				{ "FindDescendedChild", node_FindDescendedChild },
				{ "FindAttribute", node_FindAttribute },
				{ "Traverse", node_Traverse },
				{ "Print", node_Print },
			},
			__gc_Node
		},
		{
			METANAME_ATTRIBUTE,
			{
				{ "GetName", attribute_GetName },
				{ "GetValue", attribute_GetValue },
				{ "GetValueAsInteger", attribute_GetValueAsInteger },
				{ "GetValueAsNumber", attribute_GetValueAsNumber },
				{ "GetValueAsBoolean", attribute_GetValueAsBoolean },
				{ "SetName", attribute_SetName },
				{ "SetValue", attribute_SetValue },
				{ "SetIntegerValue", attribute_SetIntegerValue },
				{ "SetNumberValue", attribute_SetNumberValue },
				{ "SetBooleanValue", attribute_SetBooleanValue },
				{ "GetNextAttribute", attribute_GetNextAttribute },
				{ "GetPreviousAttribute", attribute_GetPreviousAttribute },
			},
			__gc_Attribute
		}
	};
}


ETHER_API attribute_GetName(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	lua_pushstring(L, attribute->name());

	return 1;
}


ETHER_API attribute_GetValue(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	lua_pushstring(L, attribute->value());

	return 1;
}


ETHER_API attribute_GetValueAsInteger(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	lua_pushinteger(L, attribute->as_llong());

	return 1;
}


ETHER_API attribute_GetValueAsNumber(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	lua_pushnumber(L, attribute->as_double());

	return 1;
}


ETHER_API attribute_GetValueAsBoolean(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	lua_pushboolean(L, attribute->as_bool());

	return 1;
}


ETHER_API attribute_SetName(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	if (!attribute->set_name(luaL_checkstring(L, 2)))
		luaL_error(L, "set attribute name failed");

	return 1;
}


ETHER_API attribute_SetValue(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	if (!attribute->set_value(luaL_checkstring(L, 2)))
		luaL_error(L, "set attribute value failed");

	return 1;
}


ETHER_API attribute_SetIntegerValue(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	if (!attribute->set_value(lua_tointeger(L, 2)))
		luaL_error(L, "set attribute value failed");

	return 1;
}


ETHER_API attribute_SetNumberValue(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	if (lua_gettop(L) > 2
		? (!attribute->set_value(lua_tonumber(L, 2)))
		: (!attribute->set_value(lua_tonumber(L, 2), lua_tointeger(L, 3))))
		luaL_error(L, "set attribute value failed");

	return 1;
}


ETHER_API attribute_SetBooleanValue(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	if (!attribute->set_value((bool)lua_toboolean(L, 2)))
		luaL_error(L, "set attribute value failed");

	return 1;
}


ETHER_API attribute_GetNextAttribute(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_attribute,
		attribute->next_attribute(), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API attribute_GetPreviousAttribute(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_attribute,
		attribute->previous_attribute(), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API __gc_Attribute(lua_State* L)
{
	xml_attribute* attribute = GetAttributeData(1);
#ifdef _ETHER_DEBUG_
	CheckAttributeData(attribute, 1);
#endif
	delete attribute;
	attribute = nullptr;

	return 1;
}


ETHER_API node_GetRoot(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		node->parent(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetParent(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		node->parent(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetNextSibling(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		lua_gettop(L) > 1 ? node->next_sibling(luaL_checkstring(L, 2)) 
		: node->next_sibling(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetPreviousSibling(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		lua_gettop(L) > 1 ? node->previous_sibling(luaL_checkstring(L, 2))
		: node->previous_sibling(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetChild(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node, 
		node->child(luaL_checkstring(L, 2)), METANAME_NODE);

	return 1;
}


ETHER_API node_GetFirstChild(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		node->first_child(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetLastChild(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		node->last_child(), METANAME_NODE);

	return 1;
}


ETHER_API node_GetChildByAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		lua_gettop(L) > 3 ?
		node->find_child_by_attribute(luaL_checkstring(L, 2), luaL_checkstring(L, 3), luaL_checkstring(L, 4))
		: node->find_child_by_attribute(luaL_checkstring(L, 2), luaL_checkstring(L, 3)), METANAME_NODE);

	return 1;
}


ETHER_API node_GetChildren(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	int index = 1;
	lua_newtable(L);
	if (lua_gettop(L) > 1)
	{
		for (const xml_node& node : node->children(luaL_checkstring(L, 2)))
		{
			CopyAndPushNewUserdataToTable(xml_node, node, METANAME_NODE, index);
		}
	}
	else
	{
		for (const xml_node& node : node->children())
		{
			CopyAndPushNewUserdataToTable(xml_node, node, METANAME_NODE, index);
		}
	}

	return 1;
}


ETHER_API node_GetName(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushstring(L, node->name());

	return 1;
}


ETHER_API node_GetValue(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushstring(L, node->value());

	return 1;
}


ETHER_API node_GetChildValue(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushstring(L, lua_gettop(L) > 1 ? 
		node->child_value(luaL_checkstring(L, 2)) : node->child_value());

	return 1;
}


ETHER_API node_GetType(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
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
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushstring(L, node->text().as_string());

	return 1;
}


ETHER_API node_GetTextAsInteger(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushinteger(L, node->text().as_llong());

	return 1;
}


ETHER_API node_GetTextAsNumber(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushnumber(L, node->text().as_double());

	return 1;
}


ETHER_API node_GetTextAsBoolean(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	lua_pushboolean(L, node->text().as_bool());

	return 1;
}


ETHER_API node_GetAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_attribute,
		node->attribute(luaL_checkstring(L, 2)), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API node_GetFirstAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_attribute,
		node->first_attribute(), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API node_GetLastAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CopyAndPushNewUserdataToStack(xml_attribute,
		node->last_attribute(), METANAME_ATTRIBUTE);

	return 1;
}


ETHER_API node_GetAttributes(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	int index = 1;
	lua_newtable(L);
	for (const xml_attribute& attribute : node->attributes())
	{
		CopyAndPushNewUserdataToTable(xml_attribute, attribute, METANAME_ATTRIBUTE, index);
	}

	return 1;
}


ETHER_API node_SetName(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->set_name(luaL_checkstring(L, 2)))
		luaL_error(L, "set node name failed");

	return 1;
}


ETHER_API node_SetValue(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->set_value(luaL_checkstring(L, 2)))
		luaL_error(L, "set node value failed");

	return 1;
}


ETHER_API node_SetText(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->text().set(luaL_checkstring(L, 2)))
		luaL_error(L, "set node text failed");

	return 1;
}


ETHER_API node_SetTextAsInteger(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->text().set(luaL_checkinteger(L, 2)))
		luaL_error(L, "set node text failed");

	return 1;
}


ETHER_API node_SetTextAsNumber(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->text().set(luaL_checknumber(L, 2)))
		luaL_error(L, "set node text failed");

	return 1;
}


ETHER_API node_SetTextAsBoolean(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->text().set((bool)lua_toboolean(L, 2)))
		luaL_error(L, "set node text failed");

	return 1;
}


ETHER_API node_AppendAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	luaL_argcheck(L, 
		!node->append_attribute(luaL_checkstring(L, 2)).empty(), 
		2, "append attribute failed");

	return 1;
}


ETHER_API node_PrependAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	luaL_argcheck(L, 
		!node->prepend_attribute(luaL_checkstring(L, 2)).empty(), 
		2, "prepend attribute failed");

	return 1;
}


ETHER_API node_InsertAttributeAfter(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_attribute* attribute = GetAttributeData(3);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckAttributeData(attribute, 3);
#endif
	luaL_argcheck(L, 
		!node->insert_attribute_after(luaL_checkstring(L, 2), *attribute).empty(), 
		2, "insert attribute failed");

	return 1;
}


ETHER_API node_InsertAttributeBefore(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_attribute* attribute = GetAttributeData(3);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckAttributeData(attribute, 3);
#endif
	luaL_argcheck(L,
		!node->insert_attribute_before(luaL_checkstring(L, 2), *attribute).empty(),
		2, "insert attribute failed");

	return 1;
}


ETHER_API node_AppendAttributeCopy(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_attribute* attribute = GetAttributeData(2);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckAttributeData(attribute, 2);
#endif
	luaL_argcheck(L,
		!node->append_copy(*attribute).empty(),
		2, "insert attribute failed");

	return 1;
}


ETHER_API node_PrependAttributeCopy(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_attribute* attribute = GetAttributeData(2);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckAttributeData(attribute, 2);
#endif
	luaL_argcheck(L,
		!node->prepend_copy(*attribute).empty(),
		2, "insert attribute failed");

	return 1;
}


ETHER_API node_InsertAttributeCopyAfter(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_attribute* attribute_1 = GetAttributeData(2);
	xml_attribute* attribute_2 = GetAttributeData(3);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckAttributeData(attribute_1, 2);
	CheckAttributeData(attribute_2, 3);
#endif
	if (node->insert_copy_after(*attribute_1, *attribute_2).empty())
		luaL_error(L, "insert attribute failed");

	return 1;
}


ETHER_API node_InsertAttributeCopyBefore(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_attribute* attribute_1 = GetAttributeData(2);
	xml_attribute* attribute_2 = GetAttributeData(3);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckAttributeData(attribute_1, 2);
	CheckAttributeData(attribute_2, 3);
#endif
	if (node->insert_copy_before(*attribute_1, *attribute_2).empty())
		luaL_error(L, "insert attribute failed");

	return 1;
}


ETHER_API node_MoveNodeToChildAppend(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_node* node_1 = GetNodeData(2);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckNodeData(node_1, 2);
#endif
	if (node->append_move(*node_1).empty())
		luaL_error(L, "move node failed");

	return 1;
}


ETHER_API node_MoveNodeToChildPrepend(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_node* node_1 = GetNodeData(2);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckNodeData(node_1, 2);
#endif
	if (node->prepend_move(*node_1).empty())
		luaL_error(L, "move node failed");

	return 1;
}


ETHER_API node_MoveNodeToChildInsertAfter(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_node* node_1 = GetNodeData(2);
	xml_node* node_2 = GetNodeData(3);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckNodeData(node_1, 2);
	CheckNodeData(node_2, 3);
#endif
	if (node->insert_move_after(*node_1, *node_2).empty())
		luaL_error(L, "move node failed");

	return 1;
}


ETHER_API node_MoveNodeToChildInsertBefore(lua_State* L)
{
	xml_node* node = GetNodeData(1);
	xml_node* node_1 = GetNodeData(2);
	xml_node* node_2 = GetNodeData(3);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
	CheckNodeData(node_1, 2);
	CheckNodeData(node_2, 3);
#endif
	if (node->insert_move_before(*node_1, *node_2).empty())
		luaL_error(L, "move node failed");

	return 1;
}


ETHER_API node_RemoveAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (lua_isuserdata(L, 2))
	{
		xml_attribute* attribute = GetAttributeData(2);
#ifdef _ETHER_DEBUG_
		CheckAttributeData(attribute, 2);
		if (!node->remove_attribute(*attribute))
			luaL_error(L, "remove attribute failed");
#endif
	}
	else
		if (!node->remove_attribute(luaL_checkstring(L, 2)))
			luaL_error(L, "remove attribute failed");
	
	return 1;
}


ETHER_API node_RemoveAttributes(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->remove_attributes())
		luaL_error(L, "remove attributes failed");

	return 1;
}


ETHER_API node_RemoveChild(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (lua_isuserdata(L, 2))
	{
		xml_node* node_1 = GetNodeData(1);
#ifdef _ETHER_DEBUG_
		CheckNodeData(node_1, 2);
		if (!node->remove_child(*node_1))
			luaL_error(L, "remove child failed");
#endif
	}
	else
		if (!node->remove_child(luaL_checkstring(L, 2)))
			luaL_error(L, "remove child failed");

	return 1;
}


ETHER_API node_RemoveChildren(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	if (!node->remove_children())
		luaL_error(L, "remove children failed");

	return 1;
}


ETHER_API node_FindDirectChild(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CheckHandlerFunctionAt2ndPos();
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_FIND_HANDLER);
	CopyAndPushNewUserdataToStack(xml_node,
		node->find_child(XML_Searcher(L)), METANAME_NODE);
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_FIND_HANDLER);

	return 1;
}


ETHER_API node_FindDescendedChild(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CheckHandlerFunctionAt2ndPos();
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_FIND_HANDLER);
	CopyAndPushNewUserdataToStack(xml_node,
		node->find_node(XML_Searcher(L)), METANAME_NODE);
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_FIND_HANDLER);

	return 1;
}


ETHER_API node_FindAttribute(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CheckHandlerFunctionAt2ndPos();
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_ATTRIBUTE_FIND_HANDLER);
	CopyAndPushNewUserdataToStack(xml_attribute,
		node->find_attribute(XML_Searcher(L)), METANAME_ATTRIBUTE);
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_ATTRIBUTE_FIND_HANDLER);

	return 1;
}


ETHER_API node_Traverse(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	CheckHandlerFunctionAt2ndPos();
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_TRAVERSE_HANDLER);
	XML_Walker walker(L);
	node->traverse(walker);
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_TRAVERSE_HANDLER);

	return 0;
}


ETHER_API node_Print(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	XML_Writer writer(L);
	lua_gettop(L) > 1 && !lua_toboolean(L, 2)
		? node->print(writer, "\t", format_raw)
		: node->print(writer);

	return 1;
}


ETHER_API __gc_Node(lua_State* L)
{
	xml_node* node = GetNodeData(1);
#ifdef _ETHER_DEBUG_
	CheckNodeData(node, 1);
#endif
	delete node;
	node = nullptr;

	return 0;
}


ETHER_API document_GetChild(lua_State* L)
{
	xml_document* document = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(document);
#endif
	CopyAndPushNewUserdataToStack(xml_node,
		document->child(luaL_checkstring(L, 2)), METANAME_NODE);

	return 1;
}


ETHER_API document_SaveAsFile(lua_State* L)
{
	xml_document* document = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(document);
#endif
	lua_gettop(L) > 2 && !lua_toboolean(L, 3)
		? document->save_file(luaL_checkstring(L, 2), "\t", format_raw)
		: document->save_file(luaL_checkstring(L, 2));

	return 1;
}


ETHER_API document_Traverse(lua_State* L)
{
	xml_document* document = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(document);
#endif
	CheckHandlerFunctionAt2ndPos();
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_TRAVERSE_HANDLER);
	XML_Walker walker(L);
	document->traverse(walker);
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, REFKEY_NODE_TRAVERSE_HANDLER);

	return 0;
}


ETHER_API document_Print(lua_State* L)
{
	xml_document* document = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(document);
#endif
	XML_Writer writer(L);
	lua_gettop(L) > 1 && !lua_toboolean(L, 2)
		? document->print(writer, "\t", format_raw)
		: document->print(writer);

	return 1;
}


ETHER_API __gc_Document(lua_State* L)
{
	xml_document* document = GetDocumentDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckDocumentDataAt1stPos(document);
#endif
	delete document;
	document = nullptr;

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
	size_t len = 0;
	xml_document* document = new xml_document();
	LoadXMLAndCheck(document, document->load_buffer(luaL_checklstring(L, 1, &len), len));

	return 1;
}