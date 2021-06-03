#include "ModuleGraphic.h"


ModuleGraphic& ModuleGraphic::Instance()
{
	static ModuleGraphic* _instance = new ModuleGraphic();
	return *_instance;
}


ModuleGraphic::ModuleGraphic()
{
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

	_vCMethods = {
		{ "SetCursorShow", setCursorShow },
		{ "LoadImageFromFile", loadImageFromFile },
		{ "LoadImageFromData", loadImageFromData },
		{ "CreateTexture", createTexture },
		{ "CopyTexture", copyTexture },
		{ "CopyRotateTexture", copyRotateTexture },
		{ "CopyReshapeTexture", copyReshapeTexture },
		{ "CopyRotateReshapeTexture", copyRotateReshapeTexture },
		{ "SetDrawColor", setDrawColor },
		{ "GetDrawColor", getDrawColor },
		{ "Point", point },
		{ "Line", ether_drawline },
		{ "ThickLine", thickLine },
		{ "Rectangle", rectangle },
		{ "FillRectangle", fillRectangle },
		{ "RoundRectangle", roundRectangle },
		{ "FillRoundRectangle", fillRoundRectangle },
		{ "Circle", circle },
		{ "FillCircle", fillCircle },
		{ "Ellipse", ellipse },
		{ "FillEllipse", fillEllipse },
		{ "Pie", pie },
		{ "FillPie", fillPie },
		{ "Triangle", triangle },
		{ "FillTriangle", fillTriangle },
		{ "LoadFontFromFile", loadFontFromFile },
		{ "LoadFontFromData", loadFontFromData },
		{ "GetTextSize", getTextSize },
		{ "GetUTF8TextSize", getUTF8TextSize },
		{ "CreateTextImageSolid", createTextImageSolid },
		{ "CreateUTF8TextImageSolid", createUTF8TextImageSolid },
		{ "CreateTextImageShaded", createTextImageShaded },
		{ "CreateUTF8TextImageShaded", createUTF8TextImageShaded },
		{ "CreateTextImageBlended", createTextImageBlended },
		{ "CreateUTF8TextImageBlended", createUTF8TextImageBlended },
	};

	_vMacros = {
		{ "FLIP_HORIZONTAL", FLIP_HORIZONTAL },
		{ "FLIP_VERTICAL", FLIP_VERTICAL },
		{ "FLIP_NONE", FLIP_NONE },

		{ "FONT_STYLE_BOLD", FONT_STYLE_BOLD },
		{ "FONT_STYLE_ITALIC", FONT_STYLE_ITALIC },
		{ "FONT_STYLE_UNDERLINE", FONT_STYLE_UNDERLINE },
		{ "FONT_STYLE_STRIKETHROUGH", FONT_STYLE_STRIKETHROUGH },
		{ "FONT_STYLE_NORMAL", FONT_STYLE_NORMAL },
	};

	_vMetaData = {
		{ 
			METANAME_IMAGE,
			{
				{ "SetColorKey", image_SetColorKey },
				{ "GetSize", image_GetSize },
			},
			__gc_Image
		},
		{ 
			METANAME_TEXTURE,
			{
				{ "SetAlpha", texture_SetAlpha },
			},
			__gc_Texture
		},
		{ 
			METANAME_FONT,
			{
				{ "GetStyle", font_GetStyle },
				{ "SetStyle", font_SetStyle },
				{ "GetOutlineWidth", font_GetOutlineWidth },
				{ "SetOutlineWidth", font_SetOutlineWidth },
				{ "GetKerning", font_GetKerning },
				{ "SetKerning", font_SetKerning },
				{ "GetHeight", font_GetHeight },
			},
			__gc_Font
		},
	};
}


ETHER_API setCursorShow(lua_State * L)
{
	SDL_ShowCursor(lua_toboolean(L, 1) ? SDL_ENABLE : SDL_DISABLE);

	return 0;
}

ETHER_API loadImageFromFile(lua_State * L)
{
	SDL_Surface* pSurface = IMG_Load(luaL_checkstring(L, 1));
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "load image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API loadImageFromData(lua_State* L)
{
	size_t size = 0;
	SDL_Surface* pSurface = IMG_Load_RW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "load image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API image_SetColorKey(lua_State * L)
{
	SDL_Surface* surface = GetImageDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckImageDataAt1stPos(surface);
#endif
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, color);
#else
	GetColorParam(L, 3, color);
#endif
	SDL_SetColorKey(surface, lua_toboolean(L, 2), SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));

	return 0;
}


ETHER_API __gc_Image(lua_State * L)
{
	SDL_Surface* surface = GetImageDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckImageDataAt1stPos(surface);
#endif
	SDL_FreeSurface(surface);
	surface = nullptr;

	return 0;
}


ETHER_API createTexture(lua_State * L)
{
	SDL_Surface* surface = GetImageDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckImageDataAt1stPos(surface);
	if (!renderer)
		luaL_error(L, "Texture creation must be done after the window created");
#endif
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, surface);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pTexture, 1, "create texture failed");
#endif
	SDL_Texture** uppTexture = (SDL_Texture**)lua_newuserdata(L, sizeof(SDL_Texture*));
	*uppTexture = pTexture;
	luaL_getmetatable(L, METANAME_TEXTURE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API __gc_Texture(lua_State * L)
{
	SDL_Texture* texture = GetTextureDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckTextureDataAt1stPos(texture);
#endif
	SDL_DestroyTexture(texture);
	texture = nullptr;

	return 0;
}


ETHER_API texture_SetAlpha(lua_State * L)
{
	SDL_Texture* texture = GetTextureDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckTextureDataAt1stPos(texture);
#endif
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, luaL_checknumber(L, 2));
	lua_pushlightuserdata(L, texture);

	return 0;
}


ETHER_API image_GetSize(lua_State * L)
{
	SDL_Surface* surface = GetImageDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckImageDataAt1stPos(surface);
#endif
	lua_pushnumber(L, surface->w);
	lua_pushnumber(L, surface->h);

	return 2;
}


ETHER_API copyTexture(lua_State * L)
{
	SDL_Texture* texture = GetTextureDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckTextureDataAt1stPos(texture);
#endif
	SDL_Rect rect;
#ifdef _ETHER_DEBUG_
	CheckRectParam(L, 2, rect);
#else
	GetRectParam(L, 2, rect);
#endif
	SDL_RenderCopy(renderer, texture, nullptr, &rect);

	return 0;
}


ETHER_API copyRotateTexture(lua_State * L)
{
	SDL_Texture* texture = GetTextureDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckTextureDataAt1stPos(texture);
#endif
	SDL_Point flipCenter;
	SDL_Rect showRect;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 3, flipCenter);
	CheckRectParam(L, 5, showRect);
#else
	GetPointParam(L, 3, flipCenter);
	GetRectParam(L, 5, showRect);
#endif
	SDL_RendererFlip flip;
#ifdef _ETHER_DEBUG_
	CheckTableParam(L, 4);
#endif
	lua_pushnil(L);
	while (lua_next(L, 4))
	{
		lua_pushvalue(L, -2);
		if (!lua_isnumber(L, -2))
		{
			luaL_error(L, "bad argument #4 to 'CopyRotateTexture' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
		}
		else
		{
			switch ((int)lua_tonumber(L, -2))
			{
			case FLIP_HORIZONTAL:
				flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
				break;
			case FLIP_VERTICAL:
				flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
				break;
			case FLIP_NONE:
				flip = (SDL_RendererFlip)(flip | SDL_FLIP_NONE);
				break;
			default:
				luaL_error(L, "bad argument #4 to 'CopyRotateTexture' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
				break;
			}
		}
		lua_pop(L, 2);
	}

	SDL_RenderCopyEx(renderer, texture, nullptr, &showRect, luaL_checknumber(L, 2), &flipCenter, flip);

	return 0;
}


ETHER_API copyReshapeTexture(lua_State * L)
{
	SDL_Texture* texture = GetTextureDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckTextureDataAt1stPos(texture);
#endif
	SDL_Rect reshapeRect, showRect;
#ifdef _ETHER_DEBUG_
	CheckRectParam(L, 2, reshapeRect);
	CheckRectParam(L, 3, showRect);
#else
	GetRectParam(L, 2, reshapeRect);
	GetRectParam(L, 3, showRect);
#endif

	SDL_RenderCopy(renderer, texture, &reshapeRect, &showRect);

	return 0;
}


ETHER_API copyRotateReshapeTexture(lua_State * L)
{
	SDL_Texture* texture = GetTextureDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckTextureDataAt1stPos(texture);
#endif
	SDL_Point flipCenter;
	SDL_Rect reshapeRect, showRect;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 3, flipCenter);
	CheckRectParam(L, 5, reshapeRect);
	CheckRectParam(L, 6, showRect);
#else
	GetPointParam(L, 3, flipCenter);
	GetRectParam(L, 5, reshapeRect);
	GetRectParam(L, 6, showRect);
#endif

	SDL_RendererFlip flip;
#ifdef _ETHER_DEBUG_
	CheckTableParam(L, 4);
#endif
	lua_pushnil(L);
	while (lua_next(L, 4))
	{
		lua_pushvalue(L, -2);
		if (!lua_isnumber(L, -2))
		{
			luaL_error(L, "bad argument #4 to 'CopyRotateReshapeTexture' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
		}
		else
		{
			switch ((int)lua_tonumber(L, -2))
			{
			case FLIP_HORIZONTAL:
				flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
				break;
			case FLIP_VERTICAL:
				flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
				break;
			case FLIP_NONE:
				flip = (SDL_RendererFlip)(flip | SDL_FLIP_NONE);
				break;
			default:
				luaL_error(L, "bad argument #4 to 'CopyRotateReshapeTexture' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
				break;
			}
		}
		lua_pop(L, 2);
	}

	SDL_RenderCopyEx(renderer, texture, &reshapeRect, &showRect, luaL_checknumber(L, 2), &flipCenter, flip);

	return 0;
}


ETHER_API setDrawColor(lua_State * L)
{
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 1, color);
#else
	GetColorParam(L, 1, color);
#endif

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API getDrawColor(lua_State * L)
{
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));

	lua_newtable(L);
	lua_pushstring(L, "r");
	lua_pushnumber(L, color.r);
	lua_settable(L, -3);
	lua_pushstring(L, "g");
	lua_pushnumber(L, color.g);
	lua_settable(L, -3);
	lua_pushstring(L, "b");
	lua_pushnumber(L, color.b);
	lua_settable(L, -3);
	lua_pushstring(L, "a");
	lua_pushnumber(L, color.a);
	lua_settable(L, -3);

	return 1;
}


ETHER_API point(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif

	SDL_RenderDrawPoint(renderer, point.x, point.y);

	return 0;
}

// ÓëSDL2µÄline³åÍ»
ETHER_API ether_drawline(lua_State * L)
{
	SDL_Point startPoint, endPoint;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, startPoint);
	CheckPointParam(L, 2, endPoint);
#else
	GetPointParam(L, 1, startPoint);
	GetPointParam(L, 2, endPoint);
#endif

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aalineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API thickLine(lua_State * L)
{
	SDL_Point startPoint, endPoint;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, startPoint);
	CheckPointParam(L, 2, endPoint);
#else
	GetPointParam(L, 1, startPoint);
	GetPointParam(L, 2, endPoint);
#endif

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	thickLineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API rectangle(lua_State * L)
{
	SDL_Rect rect;
#ifdef _ETHER_DEBUG_
	CheckRectParam(L, 1, rect);
#else
	GetRectParam(L, 1, rect);
#endif
	SDL_RenderDrawRect(renderer, &rect);

	return 0;
}


ETHER_API fillRectangle(lua_State * L)
{
	SDL_Rect rect;
#ifdef _ETHER_DEBUG_
	CheckRectParam(L, 1, rect);
#else
	GetRectParam(L, 1, rect);
#endif
	SDL_RenderFillRect(renderer, &rect);

	return 0;
}


ETHER_API roundRectangle(lua_State * L)
{
	SDL_Rect rect;
#ifdef _ETHER_DEBUG_
	CheckRectParam(L, 1, rect);
#else
	GetRectParam(L, 1, rect);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	roundedRectangleRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API fillRoundRectangle(lua_State * L)
{
	SDL_Rect rect;
#ifdef _ETHER_DEBUG_
	CheckRectParam(L, 1, rect);
#else
	GetRectParam(L, 1, rect);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API circle(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aacircleRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API fillCircle(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledCircleRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API ellipse(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aaellipseRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API fillEllipse(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledEllipseRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API pie(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	pieRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API fillPie(lua_State * L)
{
	SDL_Point point;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point);
#else
	GetPointParam(L, 1, point);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledPieRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API triangle(lua_State * L)
{
	SDL_Point point_1, point_2, point_3;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point_1);
	CheckPointParam(L, 2, point_2);
	CheckPointParam(L, 3, point_3);
#else
	GetPointParam(L, 1, point_1);
	GetPointParam(L, 2, point_2);
	GetPointParam(L, 3, point_3);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aatrigonRGBA(renderer, point_1.x, point_1.y, point_2.x, point_2.y, point_3.x, point_3.y, color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API fillTriangle(lua_State * L)
{
	SDL_Point point_1, point_2, point_3;
#ifdef _ETHER_DEBUG_
	CheckPointParam(L, 1, point_1);
	CheckPointParam(L, 2, point_2);
	CheckPointParam(L, 3, point_3);
#else
	GetPointParam(L, 1, point_1);
	GetPointParam(L, 2, point_2);
	GetPointParam(L, 3, point_3);
#endif
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledTrigonRGBA(renderer, point_1.x, point_1.y, point_2.x, point_2.y, point_3.x, point_3.y, color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API loadFontFromFile(lua_State * L)
{
	TTF_Font* pFont = TTF_OpenFont(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pFont, 1, "load font failed");
#endif
	TTF_Font** uppFont = (TTF_Font**)lua_newuserdata(L, sizeof(TTF_Font*));
	*uppFont = pFont;
	luaL_getmetatable(L, METANAME_FONT);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API loadFontFromData(lua_State* L)
{
	size_t size = 0;
	TTF_Font* pFont = TTF_OpenFontRW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1, luaL_checknumber(L, 2));
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pFont, 1, "load font failed");
#endif
	TTF_Font** uppFont = (TTF_Font**)lua_newuserdata(L, sizeof(TTF_Font*));
	*uppFont = pFont;
	luaL_getmetatable(L, METANAME_FONT);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API __gc_Font(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	TTF_CloseFont(font);
	font = nullptr;

	return 0;
}


ETHER_API font_GetStyle(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	lua_newtable(L);
	int style = TTF_GetFontStyle(font);
	if (style == TTF_STYLE_NORMAL)
	{
		lua_pushnumber(L, 1);
		lua_pushnumber(L, FONT_STYLE_NORMAL);
		lua_settable(L, -3);
	}
	else
	{
		int index = 1;
		if (style & TTF_STYLE_BOLD)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, FONT_STYLE_BOLD);
			lua_settable(L, -3);
			index++;
		}
		if (style & TTF_STYLE_ITALIC)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, FONT_STYLE_ITALIC);
			lua_settable(L, -3);
			index++;
		}
		if (style & TTF_STYLE_UNDERLINE)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, FONT_STYLE_UNDERLINE);
			lua_settable(L, -3);
			index++;
		}
		if (style & FONT_STYLE_STRIKETHROUGH)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, FONT_STYLE_STRIKETHROUGH);
			lua_settable(L, -3);
			index++;
		}
	}

	return 1;
}


ETHER_API font_SetStyle(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
	CheckTableParam(L, 2);
#endif
	int style = 0;
	lua_pushnil(L);
	while (lua_next(L, 2))
	{
		lua_pushvalue(L, -2);
		if (!lua_isnumber(L, -2))
			luaL_error(L, "bad argument #2 to 'SetFontStyle' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
		else
		{
			switch ((int)lua_tonumber(L, -2))
			{
			case FONT_STYLE_BOLD:
				style |= TTF_STYLE_BOLD;
				break;
			case FONT_STYLE_ITALIC:
				style |= TTF_STYLE_ITALIC;
				break;
			case FONT_STYLE_UNDERLINE:
				style |= TTF_STYLE_UNDERLINE;
				break;
			case FONT_STYLE_STRIKETHROUGH:
				style |= TTF_STYLE_STRIKETHROUGH;
				break;
			case FONT_STYLE_NORMAL:
				style |= TTF_STYLE_NORMAL;
				break;
			default:
				luaL_error(L, "bad argument #2 to 'SetFontStyle' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
				break;
			}
		}
		lua_pop(L, 2);
	}

	TTF_SetFontStyle(font, style);

	return 0;
}


ETHER_API font_GetOutlineWidth(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	lua_pushnumber(L, TTF_GetFontOutline(font));

	return 1;
}


ETHER_API font_SetOutlineWidth(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	TTF_SetFontOutline(font, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API font_GetKerning(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	lua_pushnumber(L, TTF_GetFontKerning(font));

	return 1;
}


ETHER_API font_SetKerning(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	TTF_SetFontKerning(font, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API font_GetHeight(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	lua_pushnumber(L, TTF_FontHeight(font));

	return 1;
}


ETHER_API getTextSize(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	int width, height;
	TTF_SizeText(font, luaL_checkstring(L, 2), &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);

	return 2;
}


ETHER_API getUTF8TextSize(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	int width, height;
	TTF_SizeUTF8(font, luaL_checkstring(L, 2), &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);

	return 2;
}


ETHER_API createTextImageSolid(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, color);
#else
	GetColorParam(L, 3, color);
#endif
	SDL_Surface* pSurface = TTF_RenderText_Solid(font, luaL_checkstring(L, 2), color);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "create text image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API createUTF8TextImageSolid(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, color);
#else
	GetColorParam(L, 3, color);
#endif
	SDL_Surface* pSurface = TTF_RenderUTF8_Solid(font, luaL_checkstring(L, 2), color);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "create text image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API createTextImageShaded(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	SDL_Color fgColor, bgColor;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, fgColor);
	CheckColorParam(L, 4, bgColor);
#else
	GetColorParam(L, 3, fgColor);
	GetColorParam(L, 4, bgColor);
#endif
	SDL_Surface* pSurface = TTF_RenderText_Shaded(font, luaL_checkstring(L, 2), fgColor, bgColor);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "create text image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API createUTF8TextImageShaded(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	SDL_Color fgColor, bgColor;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, fgColor);
	CheckColorParam(L, 4, bgColor);
#else
	GetColorParam(L, 3, fgColor);
	GetColorParam(L, 4, bgColor);
#endif
	SDL_Surface* pSurface = TTF_RenderUTF8_Shaded(font, luaL_checkstring(L, 2), fgColor, bgColor);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "create text image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API createTextImageBlended(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, color);
#else
	GetColorParam(L, 3, color);
#endif
	SDL_Surface* pSurface = TTF_RenderText_Blended(font, luaL_checkstring(L, 2), color);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "create text image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API createUTF8TextImageBlended(lua_State * L)
{
	TTF_Font* font = GetFontDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckFontDataAt1stPos(font);
#endif
	SDL_Color color;
#ifdef _ETHER_DEBUG_
	CheckColorParam(L, 3, color);
#else
	GetColorParam(L, 3, color);
#endif
	SDL_Surface* pSurface = TTF_RenderUTF8_Blended(font, luaL_checkstring(L, 2), color);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, pSurface, 1, "create text image failed");
#endif
	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, METANAME_IMAGE);
	lua_setmetatable(L, -2);

	return 1;
}