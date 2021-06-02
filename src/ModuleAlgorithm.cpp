#include "ModuleAlgorithm.h"


ModuleAlgorithm& ModuleAlgorithm::Instance()
{
	static ModuleAlgorithm* _instance = new ModuleAlgorithm();
	return *_instance;
}


ModuleAlgorithm::ModuleAlgorithm()
{
	_vCMethods = {
		{ "Clamp", clamp },
		{ "CheckPointInRect", checkPointInRect },
		{ "CheckPointInCircle", checkPointInCircle },
		{ "CheckRectsOverlap", checkRectsOverlap },
		{ "CheckCirclesOverlap", checkCirclesOverlap },
		{ "GetPointsDistance", getPointsDistance },
		{ "GetLinesDistance", getLinesDistance },
		{ "GetPointLineDistance", getPointLineDistance },
		{ "RGBAToHSLA", rgbaToHSLA },
		{ "HSLAToRGBA", hslaToRGBA },
		{ "EncodeBase64", encodeBase64 },
		{ "DecodeBase64", decodeBase64 },
	};
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

ETHER_API clamp(lua_State * L)
{
	double checknum = luaL_checknumber(L, 1);
	double lower = 0, upper = 1;
	if (lua_isnumber(L, 2))
	{
		lower = luaL_checknumber(L, 2);
		upper = luaL_checknumber(L, 3);
	}

	if (lower > upper)
		luaL_error(L, "bad arguments #2 and #3 to 'Clamp' (lower limit must be less than upper limit)");

	if (checknum <= lower)
		lua_pushnumber(L, lower);
	else if (checknum >= upper)
		lua_pushnumber(L, upper);
	else
		lua_pushnumber(L, checknum);

	return 1;
}


ETHER_API checkPointInRect(lua_State* L)
{
	SDL_Point point;
	SDL_Rect rect;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetPointParam(L, 1, point), 1, "table point expected");
	luaL_argcheck(L, !GetRectParam(L, 2, rect), 2, "table rect expected");
#else
	GetPointParam(L, 1, point);
	GetRectParam(L, 2, rect);
#endif
	lua_pushboolean(
		L,
		lua_toboolean(L, 3) ?
		point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y <= rect.y + rect.h
		: point.x > rect.x && point.x < rect.x + rect.w && point.y > rect.y && point.y < rect.y + rect.h
	);

	return 1;
}


ETHER_API checkPointInCircle(lua_State* L)
{
	SDL_Point point, center;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetPointParam(L, 1, point), 1, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 2, center), 2, "table point expected");
#else
	GetPointParam(L, 1, point);
	GetPointParam(L, 2, center);
#endif
	lua_pushboolean(
		L, 
		lua_toboolean(L, 4) ? 
		sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) <= luaL_checknumber(L, 3)
		: sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) < luaL_checknumber(L, 3)
	);

	return 1;
}


ETHER_API checkRectsOverlap(lua_State* L)
{
	SDL_Rect rect_1, rect_2;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetRectParam(L, 1, rect_1), 1, "table rect expected");
	luaL_argcheck(L, !GetRectParam(L, 2, rect_2), 2, "table rect expected");
#else
	GetRectParam(L, 1, rect_1);
	GetRectParam(L, 2, rect_2);
#endif
	lua_pushboolean(
		L, 
		lua_toboolean(L, 3) ?
		fmax(rect_1.x + rect_1.w, rect_2.x + rect_2.w) - fmin(rect_1.x, rect_2.x) <= rect_1.w + rect_2.w && fmax(rect_1.y + rect_1.h, rect_2.y + rect_2.h) - fmin(rect_1.y, rect_2.y) <= rect_1.h + rect_2.h
		: fmax(rect_1.x + rect_1.w, rect_2.x + rect_2.w) - fmin(rect_1.x, rect_2.x) < rect_1.w + rect_2.w && fmax(rect_1.y + rect_1.h, rect_2.y + rect_2.h) - fmin(rect_1.y, rect_2.y) < rect_1.h + rect_2.h
	);

	return 1;
}


ETHER_API checkCirclesOverlap(lua_State* L)
{
	SDL_Point center_1, center_2;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetPointParam(L, 1, center_1), 1, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 3, center_2), 3, "table point expected");
#else
	GetPointParam(L, 1, center_1);
	GetPointParam(L, 2, center_2);
#endif
	lua_pushboolean(
		L,
		lua_toboolean(L, 5) ?
		sqrt(pow(center_1.x - center_2.x, 2) + pow(center_1.y - center_2.y, 2)) <= luaL_checknumber(L, 2) + luaL_checknumber(L, 4)
		: sqrt(pow(center_1.x - center_2.x, 2) + pow(center_1.y - center_2.y, 2)) < luaL_checknumber(L, 2) + luaL_checknumber(L, 4)
	);

	return 1;
}


ETHER_API getPointsDistance(lua_State* L)
{
	SDL_Point point_1, point_2;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetPointParam(L, 1, point_1), 1, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 2, point_2), 2, "table point expected");
#else
	GetPointParam(L, 1, point_1);
	GetPointParam(L, 2, point_2);
#endif
	lua_pushnumber(L, sqrt(pow(point_1.x - point_2.x, 2) + pow(point_1.y - point_2.y, 2)));

	return 1;
}


ETHER_API getLinesDistance(lua_State* L)
{
	SDL_Point point_1, point_2, point_3, point_4;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetPointParam(L, 1, point_1), 1, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 2, point_2), 2, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 3, point_3), 3, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 4, point_4), 4, "table point expected");
#else
	GetPointParam(L, 1, point_1);
	GetPointParam(L, 2, point_2);
	GetPointParam(L, 3, point_3);
	GetPointParam(L, 4, point_4);
#endif
	if (point_1.x == point_2.x && point_3.x == point_4.x)
		lua_pushnumber(L, abs(point_3.x - point_1.x));
	else if ((point_1.x == point_2.x || point_3.x == point_4.x)
		|| (point_1.y - point_2.y) / (point_1.x - point_2.x) != (point_3.y - point_4.y) / (point_3.x - point_4.x))
		lua_pushnumber(L, 0);
	else
		lua_pushnumber(L, (abs(point_1.y * point_2.x - point_2.y * point_1.x - point_3.y * point_2.x + point_3.y * point_1.x + point_3.x * point_2.y - point_3.x * point_1.y) / (point_2.x - point_1.x)) / (sqrt(pow(point_1.x - point_2.x, 2) + pow(point_1.y - point_2.y, 2)) / abs(point_2.x - point_1.x)));

	return 1;
}


ETHER_API getPointLineDistance(lua_State* L)
{
	SDL_Point point_0, point_1, point_2;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetPointParam(L, 1, point_0), 1, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 2, point_1), 2, "table point expected");
	luaL_argcheck(L, !GetPointParam(L, 2, point_2), 3, "table point expected");
#else
	GetPointParam(L, 1, point_0);
	GetPointParam(L, 2, point_1);
	GetPointParam(L, 2, point_2);
#endif
	if (point_1.x == point_2.x)
		lua_pushnumber(L, abs(point_1.x - point_0.x));
	else
	{
		double k = (point_1.y - point_2.y) / (point_1.x - point_2.x);
		lua_pushnumber(L, fabs(k * (point_0.x - point_1.x) + point_1.y - point_0.y) / sqrt(1 + k * k));
	}

	return 1;
}


ETHER_API rgbaToHSLA(lua_State* L)
{
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, !GetColorParam(L, 1, color), 1, "table color expected");
#else
	GetColorParam(L, 1, color);
#endif

	double r = (double)color.r / 255;
	double g = (double)color.g / 255;
	double b = (double)color.b / 255;

	double max = fmax(fmax(r, g), b);
	double min = fmin(fmin(r, g), b);
	double h, l = 0.5 * (max + min), s;

	if (max == min)
		h = 0;
	else if (max == r)
		if (g >= b)
			h = 60 * (g - b) / (max - min) + 0;
		else
			h = 60 * (g - b) / (max - min) + 360;
	else if (max == g)
		h = 60 * (b - r) / (max - min) + 120;
	else if (max == b)
		h = 60 * (r - g) / (max - min) + 240;

	if (l == 0 || max == min)
		s = 0;
	else if (0 < l && l <= 0.5)
		s = (max - min) / (max + min);
	else if (l > 0.5)
		s = (max - min) / (2 - max - min);

	lua_newtable(L);
	lua_pushstring(L, "h");
	lua_pushnumber(L, h);
	lua_settable(L, -3);
	lua_pushstring(L, "l");
	lua_pushnumber(L, l);
	lua_settable(L, -3);
	lua_pushstring(L, "s");
	lua_pushnumber(L, s);
	lua_settable(L, -3);
	lua_pushstring(L, "a");
	lua_pushnumber(L, (double)color.a / 255);
	lua_settable(L, -3);

	return 1;
}


ETHER_API hslaToRGBA(lua_State* L)
{
	ColorHSLA color;

#ifdef _ETHER_DEBUG_

	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument 1 to 'HSLAToRGBA' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_getfield(L, 1, "h");
		luaL_argcheck(L, lua_isnumber(L, -1), 1, "table must have number value for key 'h'");
		color.h = lua_tonumber(L, -1);
		lua_getfield(L, 1, "s");
		luaL_argcheck(L, lua_isnumber(L, -1), 1, "table must have number value for key 's'");
		color.s = lua_tonumber(L, -1);
		lua_getfield(L, 1, "l");
		luaL_argcheck(L, lua_isnumber(L, -1), 1, "table must have number value for key 'l'");
		color.l = lua_tonumber(L, -1);
		lua_getfield(L, 1, "a");
		luaL_argcheck(L, lua_isnumber(L, -1), 1, "table must have number value for key 'a'");
		color.a = lua_tonumber(L, -1);
	}

#else

	lua_getfield(L, 1, "h");
	color.h = lua_tonumber(L, -1);
	lua_getfield(L, 1, "s");
	color.s = lua_tonumber(L, -1);
	lua_getfield(L, 1, "l");
	color.l = lua_tonumber(L, -1);
	lua_getfield(L, 1, "a");
	color.a = lua_tonumber(L, -1);

#endif 

	Uint8 r, g, b;

	double cmax, cmin;

	if (color.l <= 0.5)
		cmax = color.l * (1 + color.s);
	else
		cmax = color.l * (1 - color.s) + color.s;
	cmin = 2 * color.l - cmax;

	if (color.s == 0) {
		r = g = b = color.l * 255;
	}
	else {
		r = HLS2RGBvalue(cmin, cmax, color.h + 120) * 255;
		g = HLS2RGBvalue(cmin, cmax, color.h) * 255;
		b = HLS2RGBvalue(cmin, cmax, color.h - 120) * 255;
	}

	lua_newtable(L);
	lua_pushstring(L, "r");
	lua_pushnumber(L, r);
	lua_settable(L, -3);
	lua_pushstring(L, "g");
	lua_pushnumber(L, g);
	lua_settable(L, -3);
	lua_pushstring(L, "b");
	lua_pushnumber(L, b);
	lua_settable(L, -3);
	lua_pushstring(L, "a");
	lua_pushnumber(L, color.a * 255);
	lua_settable(L, -3);

	return 1;
}


ETHER_API encodeBase64(lua_State* L)
{
	size_t size = 0;
	string strBase64 = base64_encode((const unsigned char*)luaL_checklstring(L, 1, &size), size);
	lua_pushstring(L, strBase64.c_str());

	return 1;
}


ETHER_API decodeBase64(lua_State* L)
{
	string strData = base64_decode(luaL_checkstring(L, 1));
	lua_pushlstring(L, strData.c_str(), strData.size());

	return 1;
}