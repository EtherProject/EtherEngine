#include "Algorithm.h"

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


ETHER_API ifPointInRect(lua_State* L)
{
	SDL_Point point = GetPointParam(L, 1, "IfPointInRect");
	SDL_Rect rect = GetRectParam(L, 2, "IfPointInRect");

	lua_pushboolean(L, point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y < rect.y + rect.h);

	return 1;
}


ETHER_API ifPointInRectStrict(lua_State* L)
{
	SDL_Point point = GetPointParam(L, 1, "IfPointInRectStrict");
	SDL_Rect rect = GetRectParam(L, 2, "IfPointInRectStrict");

	lua_pushboolean(L, point.x > rect.x && point.x < rect.x + rect.w && point.y > rect.y && point.y < rect.y + rect.h);

	return 1;
}


ETHER_API ifPointInCircle(lua_State* L)
{
	SDL_Point point = GetPointParam(L, 1, "IfPointInCircle");
	SDL_Point center = GetPointParam(L, 2, "IfPointInCircle");

	lua_pushboolean(L, sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) <= luaL_checknumber(L, 3));

	return 1;
}


ETHER_API ifPointInCircleStrict(lua_State* L)
{
	SDL_Point point = GetPointParam(L, 1, "IfPointInCircleStrict");
	SDL_Point center = GetPointParam(L, 2, "IfPointInCircleStrict");

	lua_pushboolean(L, sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2)) < luaL_checknumber(L, 3));

	return 1;
}


ETHER_API ifRectsOverlap(lua_State* L)
{
	SDL_Rect rect_1 = GetRectParam(L, 1, "IfRectsOverlap");
	SDL_Rect rect_2 = GetRectParam(L, 2, "IfRectsOverlap");

	lua_pushboolean(L, fmax(rect_1.x + rect_1.w, rect_2.x + rect_2.w) - fmin(rect_1.x, rect_2.x) <= rect_1.w + rect_2.w && fmax(rect_1.y + rect_1.h, rect_2.y + rect_2.h) - fmin(rect_1.y, rect_2.y) <= rect_1.h + rect_2.h);

	return 1;
}


ETHER_API ifRectsOverlapStrict(lua_State* L)
{
	SDL_Rect rect_1 = GetRectParam(L, 1, "IfRectsOverlapStrict");
	SDL_Rect rect_2 = GetRectParam(L, 2, "IfRectsOverlapStrict");

	lua_pushboolean(L, fmax(rect_1.x + rect_1.w, rect_2.x + rect_2.w) - fmin(rect_1.x, rect_2.x) < rect_1.w + rect_2.w && fmax(rect_1.y + rect_1.h, rect_2.y + rect_2.h) - fmin(rect_1.y, rect_2.y) < rect_1.h + rect_2.h);

	return 1;
}


ETHER_API ifCirclesOverlap(lua_State* L)
{
	SDL_Point center_1 = GetPointParam(L, 1, "IfCirclesOverlap");
	SDL_Point center_2 = GetPointParam(L, 2, "IfCirclesOverlap");

	lua_pushboolean(L, sqrt(pow(center_1.x - center_2.x, 2) + pow(center_1.y - center_2.y, 2)) <= luaL_checknumber(L, 2) + luaL_checknumber(L, 4));

	return 1;
}

ETHER_API ifCirclesOverlapStrict(lua_State* L)
{
	SDL_Point center_1 = GetPointParam(L, 1, "IfCirclesOverlapStrict");
	SDL_Point center_2 = GetPointParam(L, 2, "IfCirclesOverlapStrict");

	lua_pushboolean(L, sqrt(pow(center_1.x - center_2.x, 2) + pow(center_1.y - center_2.y, 2)) < luaL_checknumber(L, 2) + luaL_checknumber(L, 4));

	return 1;
}


ETHER_API getPointsDistance(lua_State* L)
{
	SDL_Point point_1 = GetPointParam(L, 1, "GetPointsDistance");
	SDL_Point point_2 = GetPointParam(L, 2, "GetPointsDistance");

	lua_pushnumber(L, sqrt(pow(point_1.x - point_2.x, 2) + pow(point_1.y - point_2.y, 2)));

	return 1;
}


ETHER_API getLinesDistance(lua_State* L)
{
	SDL_Point point_1 = GetPointParam(L, 1, "GetLinesDistance");
	SDL_Point point_2 = GetPointParam(L, 2, "GetLinesDistance");
	SDL_Point point_3 = GetPointParam(L, 3, "GetLinesDistance");
	SDL_Point point_4 = GetPointParam(L, 4, "GetLinesDistance");
	
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
	SDL_Point point_0 = GetPointParam(L, 1, "GetLinesDistance");
	SDL_Point point_1 = GetPointParam(L, 2, "GetLinesDistance");
	SDL_Point point_2 = GetPointParam(L, 3, "GetLinesDistance");

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
	/*SDL_Color color = GetColorParam(L, 1, "RGBAToHSLA");
	
	double r = color.r / 255;
	double g = color.g / 255;
	double b = color.b / 255;

	int max = fmax(fmax(r, g), b);
	int min = fmin(fmin(r, g), b);
	int h, l = 0.5 * (max + min), s;

	if (max == min)
		h = 0;
	else if (max == r)
		if (g >= b)
			h = 60 * (g - b) / (max - min);
		else
			h = 60 * (g - b) / (max - min) + 360;
	else if (max == g)
		h = 60 * (b - r) / (max - min) + 120;
	else if (max == color.b)
		h = 60 * (b - r) / (max - min) + 120;

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
	lua_pushnumber(L, color.a);
	lua_settable(L, -3);*/

	// 待施工 ...

	return 1;
}


ETHER_API hslaToRGBA(lua_State* L)
{
	// 待施工 ...

	return 1;
}


ETHER_API ifElementInTable(lua_State* L)
{
	int type;
	switch ((int)luaL_checknumber(L, 3))
	{
	case ELEMENTTYPE_NUM:
		type = ELEMENTTYPE_NUM;
		break;
	case ELEMENTTYPE_STR:
		type = ELEMENTTYPE_STR;
		break;
	default:
		luaL_error(L, "bad argument #3 to 'IfElementInTable' (MACRO number expected, got %s)", luaL_typename(L, 3));
		break;
	}

	if (!lua_istable(L, 2))
	{
		luaL_error(L, "bad argument #2 to 'IfElementInTable' (table expected, got %s)", luaL_typename(L, 2));
	}
	else
	{
		if (type == ELEMENTTYPE_NUM)
		{
			bool isExist = false;
			double num = luaL_checknumber(L, 1);
			lua_pushnil(L);
			while (!isExist && lua_next(L, 2))
			{
				lua_pushvalue(L, -2);
				if (!lua_isnumber(L, -2))
					luaL_error(L, "bad argument #2 to 'IfElementInTable' (table elements must be number, got %s)", luaL_typename(L, -2));
				else if (num == lua_tonumber(L, -2))
					isExist = true;
				lua_pop(L, 2);
			}
			lua_pushboolean(L, isExist);
		}
		else
		{
			bool isExist = false;
			string str = luaL_checkstring(L, 1);
			lua_pushnil(L);
			while (!isExist && lua_next(L, 2))
			{
				lua_pushvalue(L, -2);
				if (!lua_isstring(L, -2))
					luaL_error(L, "bad argument #2 to 'IfElementInTable' (table elements must be string, got %s)", luaL_typename(L, -2));
				else if (str == lua_tostring(L, -2))
					isExist = true;
				lua_pop(L, 2);
			}
			lua_pushboolean(L, isExist);
		}
	}

	return 1;
}


MoudleAlgorithm::MoudleAlgorithm(lua_State* L)
{
	_pL = L;

	_vCMethods = {
		{ "Clamp", clamp },
		{ "IfPointInRect", ifPointInRect },
		{ "IfPointInRectStrict", ifPointInRectStrict },
		{ "IfPointInCircle", ifPointInCircle },
		{ "IfPointInCircleStrict", ifPointInCircleStrict },
		{ "IfRectsOverlap", ifRectsOverlap },
		{ "IfRectsOverlapStrict", ifRectsOverlapStrict },
		{ "IfCirclesOverlap", ifCirclesOverlap },
		{ "IfCirclesOverlapStrict", ifCirclesOverlapStrict },
		{ "GetPointsDistance", getPointsDistance },
		{ "GetLinesDistance", getLinesDistance },
		{ "GetPointLineDistance", getPointLineDistance },
		{ "RGBAToHSLA", rgbaToHSLA },
		{ "HSLAToRGBA", hslaToRGBA },
		{ "IfElementInTable", ifElementInTable },
	};

	_vMacros = {
		{ "ELEMENTTYPE_NUM", ELEMENTTYPE_NUM },
		{ "ELEMENTTYPE_STR", ELEMENTTYPE_STR },
	};
}
