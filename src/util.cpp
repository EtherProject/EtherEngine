#include "util.h"

SDL_Point GetPointParam(lua_State* L, int index, const char* funName)
{
	SDL_Point point;

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index))
	{
		luaL_error(L, "bad argument #%d to '%s' (table expected, got %s)", index, funName, luaL_typename(L, index));
	}
	else
	{
		lua_getfield(L, index, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'x', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'y', got %s)", index, funName, luaL_typename(L, -1));
	}

#else

	lua_getfield(L, index, "x");
	point.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	point.y = lua_tonumber(L, -1);

#endif

	return point;
}


SDL_Rect GetRectParam(lua_State* L, int index, const char* funName)
{
	SDL_Rect rect;

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index))
	{
		luaL_error(L, "bad argument #%d to '%s' (table expected, got %s)", index, funName, luaL_typename(L, index));
	}
	else
	{
		lua_getfield(L, index, "x");
		lua_isnumber(L, -1) ? rect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'x', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "y");
		lua_isnumber(L, -1) ? rect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'y', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "w");
		lua_isnumber(L, -1) ? rect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'w', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "h");
		lua_isnumber(L, -1) ? rect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'h', got %s)", index, funName, luaL_typename(L, -1));
	}

#else

	lua_getfield(L, index, "x");
	rect.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	rect.y = lua_tonumber(L, -1);
	lua_getfield(L, index, "w");
	rect.w = lua_tonumber(L, -1);
	lua_getfield(L, index, "h");
	rect.h = lua_tonumber(L, -1);

#endif

	return rect;
}


SDL_Color GetColorParam(lua_State* L, int index, const char* funName)
{
	SDL_Color color;

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, index))
	{
		luaL_error(L, "bad argument #%d to '%s' (table expected, got %s)", index, funName, luaL_typename(L, index));
	}
	else
	{
		lua_getfield(L, index, "r");
		lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'r', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "g");
		lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'g', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "b");
		lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'b', got %s)", index, funName, luaL_typename(L, -1));
		lua_getfield(L, index, "a");
		lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #%d to '%s' (table must have number value for key 'a', got %s)", index, funName, luaL_typename(L, -1));
	}

#else

	lua_getfield(L, index, "r");
	color.r = lua_tonumber(L, -1);
	lua_getfield(L, index, "g");
	color.g = lua_tonumber(L, -1);
	lua_getfield(L, index, "b");
	color.b = lua_tonumber(L, -1);
	lua_getfield(L, index, "a");
	color.a = lua_tonumber(L, -1);

#endif 

	return color;
}


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

void PushResponseTable(lua_State* L, shared_ptr<Response> response)
{
	if (!response)
		lua_pushnil(L);
	else
	{
		lua_newtable(L);
		lua_pushstring(L, "status");
		lua_pushnumber(L, response->status);
		lua_settable(L, -3);

		lua_pushstring(L, "body");
		lua_pushstring(L, response->body.c_str());
		lua_settable(L, -3);

		lua_pushstring(L, "headers");
		lua_newtable(L);
		for (auto kv : response->headers)
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


double HLS2RGBvalue(double n1, double n2, double hue)
{
	if (hue > 360)
		hue -= 360;
	else if (hue < 0)
		hue += 360;
	if (hue < 60)
		return n1 + (n2 - n1) * hue / 60;
	else if (hue < 180)
		return n2;
	else if (hue < 240)
		return n1 + (n2 - n1) * (240 - hue) / 60;
	else
		return n1;
}