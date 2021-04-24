#include "ModuleNetwork.h"

string GetLinkDomain(string link)
{
	if (link.substr(0, 5) == "http:" || link.substr(0, 6) == "https:")
	{
		size_t index_begin = link.find_first_of("/") + 2;
		size_t index_end = link.find_first_of("/", index_begin + 1);
		return link.substr(index_begin, index_end - index_begin);
	}
	else
	{
		size_t index_end = link.find_first_of("/");
		if (index_end == string::npos)
			return link;
		return link.substr(0, index_end);
	}
}


string GetLinkRoute(string link)
{
	string domain = GetLinkDomain(link);
	size_t index_domain_end = link.find(domain) + domain.size();
	if (index_domain_end == link.size())
		return "/";
	else
		return link.substr(index_domain_end);
}

void PushResponseTable(lua_State* L, Result result)
{
	if (!result)
		lua_pushnil(L);
	else
	{
		lua_newtable(L);
		lua_pushstring(L, "status");
		lua_pushnumber(L, result->status);
		lua_settable(L, -3);

		lua_pushstring(L, "body");
		lua_pushstring(L, result->body.c_str());
		lua_settable(L, -3);

		lua_pushstring(L, "headers");
		lua_newtable(L);
		for (auto kv : result->headers)
		{
			lua_pushstring(L, kv.first.c_str());
			lua_pushstring(L, kv.second.c_str());
			lua_settable(L, -3);
		}
		lua_settable(L, -3);
	}
}


string ConvertMacroToMIMEType(int macro)
{
	switch (macro)
	{
	case MIMETYPE_CSS:
		return "text/css";
		break;
	case MIMETYPE_CSV:
		return "text/csv";
		break;
	case MIMETYPE_TEXT:
		return "text/plain";
		break;
	case MIMETYPE_VTT:
		return "text/vtt";
		break;
	case MIMETYPE_HTML:
		return "text/html";
		break;
	case MIMETYPE_APNG:
		return "image/apng";
		break;
	case MIMETYPE_SVG:
		return "image/svg+xml";
		break;
	case MIMETYPE_WEBP:
		return "image/webp";
	case MIMETYPE_ICO:
		return "image/x-icon";
		break;
	case MIMETYPE_TIFF:
		return "image/tiff";
		break;
	case MIMETYPE_JPG:
		return "image/jpeg";
		break;
	case MIMETYPE_AVIF:
		return "image/avif";
		break;
	case MIMETYPE_BMP:
		return "image/bmp";
		break;
	case MIMETYPE_GIF:
		return "image/gif";
		break;
	case MIMETYPE_PNG:
		return "image/png";
	case MIMETYPE_MP4:
		return "video/mp4";
		break;
	case MIMETYPE_MPEG:
		return "video/mpeg";
		break;
	case MIMETYPE_WEBM:
		return "video/webm";
		break;
	case MIMETYPE_MPGA:
		return "audio/mpeg";
		break;
	case MIMETYPE_WEBA:
		return "audio/webm";
		break;
	case MIMETYPE_MP3:
		return "audio/mp3";
		break;
	case MIMETYPE_WAV:
		return "audio/wave";
		break;
	case MIMETYPE_OTF:
		return "font/otf";
		break;
	case MIMETYPE_TTF:
		return "font/ttf";
		break;
	case MIMETYPE_WOFF:
		return "font/woff";
		break;
	case MIMETYPE_WOFF2:
		return "font/woff2";
		break;
	case MIMETYPE_7Z:
		return "application/x-7z-compressed";
		break;
	case MIMETYPE_ATOM:
		return "application/atom+xml";
		break;
	case MIMETYPE_PDF:
		return "application/pdf";
		break;
	case MIMETYPE_JS:
		return "application/javascript";
		break;
	case MIMETYPE_JSON:
		return "application/json";
		break;
	case MIMETYPE_RSS:
		return "application/rss+xml";
		break;
	case MIMETYPE_TAR:
		return "application/x-tar";
		break;
	case MIMETYPE_XHTML:
		return "application/xhtml+xml";
		break;
	case MIMETYPE_XSLT:
		return "application/xslt+xml";
		break;
	case MIMETYPE_XML:
		return "application/xml";
		break;
	case MIMETYPE_GZ:
		return "application/gzip";
		break;
	case MIMETYPE_ZIP:
		return "application/zip";
	case MIMETYPE_WASM:
		return "application/wasm";
		break;
	default:
		return "";
		break;
	}
}


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
		client = new Client(domain.c_str());
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
		client = new Client(domain.c_str());

	string mimeType = ConvertMacroToMIMEType(luaL_checknumber(L, 3));
	if (mimeType.empty())
		luaL_error(L, "bad argument #3 to 'RequestPost' (MACRO number expected, got %s)", luaL_typename(L, 3));
	PushResponseTable(L, client->Post(route.c_str(), headers, luaL_checkstring(L, 2), mimeType.c_str()));
	delete(client);

	return 1;
}


ModuleNetwork::ModuleNetwork(lua_State* L, string name) : Module(L, name)
{
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