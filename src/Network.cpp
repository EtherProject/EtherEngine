#include "Network.h"

ETHER_API getLinkDomain(lua_State* L)
{
	lua_pushstring(L, GetLinkDomain(luaL_checkstring(L, 1)).c_str());

	return 1;
}


ETHER_API getLinkRoute(lua_State* L)
{
	lua_pushstring(L, GetLinkRoute(luaL_checkstring(L, 1)).c_str());

	return 1;
}


ETHER_API requestGet(lua_State* L)
{
	string domain = GetLinkDomain(luaL_checkstring(L, 1));
	string route = GetLinkRoute(luaL_checkstring(L, 1));
	
	Headers headers;
	if (lua_istable(L, 2))
	{
		int index_header = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, index_header))
		{
			headers.insert(make_pair(luaL_checkstring(L, -2), luaL_checkstring(L, -1)));
			lua_pop(L, 1);
		}
	}

	Client* client;
	if (domain.find(':') != string::npos)
		client = new Client(domain.substr(0, domain.find(':')), atoi(domain.substr(domain.find(':') + 1).c_str()));
	else
		client = new Client(domain);
	PushResponseTable(L, client->Get(route.c_str(), headers));
	delete(client);

	return 1;
}


ETHER_API requestPost(lua_State* L)
{
	string domain = GetLinkDomain(luaL_checkstring(L, 1));
	string route = GetLinkRoute(luaL_checkstring(L, 1));

	Headers headers;
	if (lua_istable(L, 4))
	{
		int index_header = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, index_header))
		{
			headers.insert(make_pair(luaL_checkstring(L, -2), luaL_checkstring(L, -1)));
			lua_pop(L, 1);
		}
	}

	Client* client;
	if (domain.find(':') != string::npos)
		client = new Client(domain.substr(0, domain.find(':')), atoi(domain.substr(domain.find(':') + 1).c_str()));
	else
		client = new Client(domain);

	string mimeType = ConvertMacroToMIMEType(luaL_checknumber(L, 3));
	if (mimeType.empty())
		luaL_error(L, "bad argument #3 to 'RequestPost' (MACRO number expected, got %s)", luaL_typename(L, 3));
	PushResponseTable(L, client->Post(route.c_str(), headers, luaL_checkstring(L, 2), mimeType.c_str()));
	delete(client);

	return 1;
}


MoudleNetwork::MoudleNetwork(lua_State* L)
{
	_pL = L;

	_vCMethods = {
		{ "GetLinkDomain", getLinkDomain },
		{ "GetLinkRoute", getLinkRoute },
		{ "RequestGet", requestGet },
		{ "RequestPost", requestPost },
	};

	_vMacros = {
		{ "MIMETYPE_CSS", MIMETYPE_CSS },
		{ "MIMETYPE_CSV", MIMETYPE_CSV },
		{ "MIMETYPE_TEXT", MIMETYPE_TEXT },
		{ "MIMETYPE_VTT", MIMETYPE_VTT },
		{ "MIMETYPE_HTML", MIMETYPE_HTML },
		{ "MIMETYPE_APNG", MIMETYPE_APNG },
		{ "MIMETYPE_SVG", MIMETYPE_SVG },
		{ "MIMETYPE_WEBP", MIMETYPE_WEBP },
		{ "MIMETYPE_ICO", MIMETYPE_ICO },
		{ "MIMETYPE_TIFF", MIMETYPE_TIFF },
		{ "MIMETYPE_JPG", MIMETYPE_JPG },
		{ "MIMETYPE_AVIF", MIMETYPE_AVIF },
		{ "MIMETYPE_BMP", MIMETYPE_BMP },
		{ "MIMETYPE_GIF", MIMETYPE_GIF },
		{ "MIMETYPE_PNG", MIMETYPE_PNG },
		{ "MIMETYPE_MP4", MIMETYPE_MP4 },
		{ "MIMETYPE_MPEG", MIMETYPE_MPEG },
		{ "MIMETYPE_WEBM", MIMETYPE_WEBM },
		{ "MIMETYPE_MPGA", MIMETYPE_MPGA },
		{ "MIMETYPE_WEBA", MIMETYPE_WEBA },
		{ "MIMETYPE_WAV", MIMETYPE_WAV },
		{ "MIMETYPE_OTF", MIMETYPE_OTF },
		{ "MIMETYPE_TTF", MIMETYPE_TTF },
		{ "MIMETYPE_WOFF", MIMETYPE_WOFF },
		{ "MIMETYPE_WOFF2", MIMETYPE_WOFF2 },
		{ "MIMETYPE_7Z", MIMETYPE_7Z },
		{ "MIMETYPE_ATOM", MIMETYPE_ATOM },
		{ "MIMETYPE_PDF", MIMETYPE_PDF },
		{ "MIMETYPE_JS", MIMETYPE_JS },
		{ "MIMETYPE_JSON", MIMETYPE_JSON },
		{ "MIMETYPE_RSS", MIMETYPE_RSS },
		{ "MIMETYPE_XHTML", MIMETYPE_XHTML },
		{ "MIMETYPE_XSLT", MIMETYPE_XSLT },
		{ "MIMETYPE_XML", MIMETYPE_XML },
		{ "MIMETYPE_GZ", MIMETYPE_GZ },
		{ "MIMETYPE_ZIP", MIMETYPE_ZIP },
		{ "MIMETYPE_WASM", MIMETYPE_WASM },
		{ "MIMETYPE_MP3", MIMETYPE_MP3 },
	};
}