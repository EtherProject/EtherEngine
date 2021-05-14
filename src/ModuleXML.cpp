#include "ModuleXML.h"

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
}


ETHER_API loadXML(lua_State* L)
{
	xml_document* doc = new xml_document();
	xml_parse_result result = doc->load_string(luaL_checkstring(L, 1));
	luaL_argcheck(L, !result.status, 1, string("XML parse error: ").append(result.description()).c_str());
	xml_document** uppdoc = (xml_document**)lua_newuserdata(L, sizeof(xml_document*));
	*uppdoc = doc;
	luaL_getmetatable(L, METANAME_DOCUMENT);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API loadXMLFromFile(lua_State* L)
{
	xml_document* doc = new xml_document();
	xml_parse_result result = doc->load_file(luaL_checkstring(L, 1));
	luaL_argcheck(L, !result.status, 1, string("XML parse error: ").append(result.description()).c_str());
	xml_document** uppdoc = (xml_document**)lua_newuserdata(L, sizeof(xml_document*));
	*uppdoc = doc;
	luaL_getmetatable(L, METANAME_DOCUMENT);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API loadXMLFromData(lua_State* L)
{
	size_t len;
	xml_document* doc = new xml_document();
	xml_parse_result result = doc->load_buffer(luaL_checklstring(L, 1, &len), len);
	luaL_argcheck(L, !result.status, 1, string("XML parse error: ").append(result.description()).c_str());
	xml_document** uppdoc = (xml_document**)lua_newuserdata(L, sizeof(xml_document*));
	*uppdoc = doc;
	luaL_getmetatable(L, METANAME_DOCUMENT);
	lua_setmetatable(L, -2);

	return 1;
}