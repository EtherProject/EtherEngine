#include "MoudleGraphic.h"

ETHER_API setCursorShow(lua_State * L)
{
	SDL_ShowCursor(lua_toboolean(L, 1) ? SDL_ENABLE : SDL_DISABLE);

	return 0;
}


ETHER_API loadImage(lua_State * L)
{
	const char* path = luaL_checkstring(L, 1);
	SDL_Surface* surface = IMG_Load(path);
	surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);

	return 1;
}


ETHER_API setImageColorKey(lua_State * L)
{
	SDL_Surface* surface = (SDL_Surface*)lua_touserdata(L, 1);

	if (!surface)
	{
		luaL_error(L, "bad argument #1 to 'SetColorKey' (userdata-IMAGE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color color = GetColorParam(L, 3, "SetImageColorKey");
		SDL_SetColorKey(surface, lua_toboolean(L, 2), SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	}

	return 0;
}


ETHER_API unloadImage(lua_State * L)
{
	SDL_Surface* surface = (SDL_Surface*)lua_touserdata(L, 1);
	if (!surface)
	{
		luaL_error(L, "bad argument #1 to 'UnloadImage' (userdata-IMAGE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_FreeSurface(surface);
		surface = NULL;
	}

	return 0;
}


ETHER_API createTexture(lua_State * L)
{
	SDL_Surface* surface = (SDL_Surface*)lua_touserdata(L, 1);
	if (!surface)
	{
		luaL_error(L, "bad argument #1 to 'CreateTexture' (userdata-IMAGE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!renderer)
		{
			luaL_error(L, "Texture creation must be done after the window creation operation");
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		lua_pushlightuserdata(L, texture);
	}

	return 1;
}


ETHER_API destroyTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'DestroyTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}

	return 0;
}


ETHER_API setTextureAlpha(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'SetTextureAlpha' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture, luaL_checknumber(L, 2));
		lua_pushlightuserdata(L, texture);
	}

	return 0;
}


ETHER_API getImageSize(lua_State * L)
{
	SDL_Surface* surface = (SDL_Surface*)lua_touserdata(L, 1);
	if (!surface)
	{
		luaL_error(L, "bad argument #1 to 'GetImageSize' (userdata-IMAGE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_pushnumber(L, surface->w);
		lua_pushnumber(L, surface->h);
	}

	return 2;
}


ETHER_API copyTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Rect rect = GetRectParam(L, 2, "CopyTexture");
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}

	return 0;
}


ETHER_API copyRotateTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyRotateTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point flipCenter = GetPointParam(L, 3, "CopyRotateTexture");

		SDL_Rect showRect = GetRectParam(L, 5, "CopyRotateTexture");

		SDL_RendererFlip flip;
		if (!lua_istable(L, 4))
		{
			luaL_error(L, "bad argument #4 to 'CopyRotateTexture' (table expected, got %s)", luaL_typename(L, 4));
		}
		else
		{
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
		}

		SDL_RenderCopyEx(renderer, texture, NULL, &showRect, luaL_checknumber(L, 2), &flipCenter, flip);
	}

	return 0;
}


ETHER_API copyReshapeTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyReshapeTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Rect reshapeRect = GetRectParam(L, 2, "CopyReshapeTexture");

		SDL_Rect showRect = GetRectParam(L, 3, "CopyReshapeTexture");

		SDL_RenderCopy(renderer, texture, &reshapeRect, &showRect);
	}

	return 0;
}


ETHER_API copyRotateReshapeTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyRotateReshapeTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point flipCenter = GetPointParam(L, 3, "CopyRotateReshapeTexture");
		SDL_Rect reshapeRect = GetRectParam(L, 5, "CopyRotateReshapeTexture");
		SDL_Rect showRect = GetRectParam(L, 6, "CopyRotateReshapeTexture");

		SDL_RendererFlip flip;
		if (!lua_istable(L, 4))
		{
			luaL_error(L, "bad argument #4 to 'CopyRotateReshapeTexture' (table expected, got %s)", luaL_typename(L, 4));
		}
		else
		{
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
		}

		SDL_RenderCopyEx(renderer, texture, &reshapeRect, &showRect, luaL_checknumber(L, 2), &flipCenter, flip);
	}

	return 0;
}


ETHER_API setDrawColor(lua_State * L)
{
	SDL_Color color = GetColorParam(L, 1, "SetDrawColor");

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
	SDL_Point point = GetPointParam(L, 1, "Point");

	SDL_RenderDrawPoint(renderer, point.x, point.y);

	return 0;
}


ETHER_API singleline(lua_State * L)
{
	SDL_Point startPoint = GetPointParam(L, 1, "Line");

	SDL_Point endPoint = GetPointParam(L, 2, "Line");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aalineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API thickLine(lua_State * L)
{
	SDL_Point startPoint = GetPointParam(L, 1, "ThickLine");

	SDL_Point endPoint = GetPointParam(L, 2, "ThickLine");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	thickLineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API rectangle(lua_State * L)
{
	SDL_Rect rect = GetRectParam(L, 1, "Rectangle");

	SDL_RenderDrawRect(renderer, &rect);

	return 0;
}


ETHER_API fillRectangle(lua_State * L)
{
	SDL_Rect rect = GetRectParam(L, 1, "FillRectangle");

	SDL_RenderFillRect(renderer, &rect);

	return 0;
}


ETHER_API roundRectangle(lua_State * L)
{
	SDL_Rect rect = GetRectParam(L, 1, "RoundRectangle");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	roundedRectangleRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API fillRoundRectangle(lua_State * L)
{
	SDL_Rect rect = GetRectParam(L, 1, "FillRoundRectangle");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API circle(lua_State * L)
{
	SDL_Point point = GetPointParam(L, 1, "Circle");
	
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aacircleRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API fillCircle(lua_State * L)
{
	SDL_Point point = GetPointParam(L, 1, "FillCircle");
	
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledCircleRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API ellipse(lua_State * L)
{
	SDL_Point point = GetPointParam(L, 1, "Ellipse");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aaellipseRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API fillEllipse(lua_State * L)
{
	SDL_Point point = GetPointParam(L, 1, "FillEllipse");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledEllipseRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API pie(lua_State * L)
{
	SDL_Point point = GetPointParam(L, 1, "Pie");
	
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	pieRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API fillPie(lua_State * L)
{
	SDL_Point point = GetPointParam(L, 1, "FillPie");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledPieRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API triangle(lua_State * L)
{
	SDL_Point point_1 = GetPointParam(L, 1, "Triangle");
	SDL_Point point_2 = GetPointParam(L, 2, "Triangle");
	SDL_Point point_3 = GetPointParam(L, 3, "Triangle");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aatrigonRGBA(renderer, point_1.x, point_1.y, point_2.x, point_2.y, point_3.x, point_3.y, color.r, color.g, color.b, color.a);

	return 0;
}

ETHER_API fillTriangle(lua_State * L)
{
	SDL_Point point_1 = GetPointParam(L, 1, "Triangle");
	SDL_Point point_2 = GetPointParam(L, 2, "Triangle");
	SDL_Point point_3 = GetPointParam(L, 3, "Triangle");

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledTrigonRGBA(renderer, point_1.x, point_1.y, point_2.x, point_2.y, point_3.x, point_3.y, color.r, color.g, color.b, color.a);

	return 0;
}


ETHER_API loadFont(lua_State * L)
{
	const char* path = luaL_checkstring(L, 1);
	int size = luaL_checknumber(L, 2);
	TTF_Font* font = TTF_OpenFont(path, size);
	font ? lua_pushlightuserdata(L, font) : lua_pushnil(L);

	return 1;
}


ETHER_API unloadFont(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'UnloadFont' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	return 0;
}


ETHER_API getFontStyle(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'GetFontStyle' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
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
	}

	return 1;
}


ETHER_API setFontStyle(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'SetFontStyle' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 2))
		{
			luaL_error(L, "bad argument #2 to 'SetFontStyle' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			int style = 0;
			lua_pushnil(L);
			while (lua_next(L, 2))
			{
				lua_pushvalue(L, -2);
				if (!lua_isnumber(L, -2))
				{
					luaL_error(L, "bad argument #2 to 'SetFontStyle' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
				}
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
		}
	}

	return 0;
}


ETHER_API getFontOutlineWidth(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'GetFontOutlineWidth' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_pushnumber(L, TTF_GetFontOutline(font));
	}

	return 1;
}


ETHER_API setFontOutlineWidth(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'SetFontOutlineWidth' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		TTF_SetFontOutline(font, luaL_checknumber(L, 2));
	}

	return 0;
}


ETHER_API getFontKerning(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'GetFontKerning' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_pushnumber(L, TTF_GetFontKerning(font));
	}

	return 1;
}


ETHER_API setFontKerning(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'SetFontKerning' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		TTF_SetFontKerning(font, luaL_checknumber(L, 2));
	}

	return 0;
}


ETHER_API getFontHeight(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'GetFontHeight' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_pushnumber(L, TTF_FontHeight(font));
	}

	return 1;
}


ETHER_API getTextSize(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'GetTextSize' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		int width, height;
		TTF_SizeText(font, luaL_checkstring(L, 2), &width, &height);
		lua_pushnumber(L, width);
		lua_pushnumber(L, height);
	}

	return 1;
}


ETHER_API getUTF8TextSize(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'GetUTF8TextSize' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		int width, height;
		TTF_SizeUTF8(font, luaL_checkstring(L, 2), &width, &height);
		lua_pushnumber(L, width);
		lua_pushnumber(L, height);
	}

	return 1;
}


ETHER_API createTextImageSolid(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateTextImageSolid' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color color = GetColorParam(L, 3, "CreateTextImageSolid");

		SDL_Surface* surface = TTF_RenderText_Solid(font, luaL_checkstring(L, 2), color);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


ETHER_API createUTF8TextImageSolid(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateUTF8TextImageSolid' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color color = GetColorParam(L, 3, "CreateUTF8TextImageSolid");
		
		SDL_Surface* surface = TTF_RenderUTF8_Solid(font, luaL_checkstring(L, 2), color);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


ETHER_API createTextImageShaded(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateTextImageShaded' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color fgColor = GetColorParam(L, 3, "CreateTextImageShaded");
		SDL_Color bgColor = GetColorParam(L, 4, "CreateTextImageShaded");

		SDL_Surface* surface = TTF_RenderText_Shaded(font, luaL_checkstring(L, 2), fgColor, bgColor);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


ETHER_API createUTF8TextImageShaded(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateUTF8TextImageShaded' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color fgColor = GetColorParam(L, 3, "CreateUTF8TextImageShaded");
		SDL_Color bgColor = GetColorParam(L, 4, "CreateUTF8TextImageShaded");

		SDL_Surface* surface = TTF_RenderUTF8_Shaded(font, luaL_checkstring(L, 2), fgColor, bgColor);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


ETHER_API createTextImageBlended(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateTextImageBlended' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color color = GetColorParam(L, 3, "CreateTextImageBlended");

		SDL_Surface* surface = TTF_RenderText_Blended(font, luaL_checkstring(L, 2), color);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


ETHER_API createUTF8TextImageBlended(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateUTF8TextImageBlended' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color color = GetColorParam(L, 3, "CreateUTF8TextImageBlended");

		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, luaL_checkstring(L, 2), color);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


MoudleGraphic::MoudleGraphic(lua_State* L, string name) : Moudle(L, name)
{
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

	_vCMethods = {
		{ "SetCursorShow", setCursorShow },
		{ "LoadImage", loadImage },
		{ "SetImageColorKey", setImageColorKey },
		{ "UnloadImage", unloadImage },
		{ "CreateTexture", createTexture },
		{ "DestroyTexture", destroyTexture },
		{ "SetTextureAlpha", setTextureAlpha },
		{ "GetImageSize", getImageSize },
		{ "CopyTexture", copyTexture },
		{ "CopyRotateTexture", copyRotateTexture },
		{ "CopyReshapeTexture", copyReshapeTexture },
		{ "CopyRotateReshapeTexture", copyRotateReshapeTexture },
		{ "SetDrawColor", setDrawColor },
		{ "GetDrawColor", getDrawColor },
		{ "Point", point },
		{ "Line", singleline },
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
		{ "LoadFont", loadFont },
		{ "UnloadFont", unloadFont },
		{ "GetFontStyle", getFontStyle },
		{ "SetFontStyle", setFontStyle },
		{ "GetFontOutlineWidth", getFontOutlineWidth },
		{ "SetFontOutlineWidth", setFontOutlineWidth },
		{ "GetFontKerning", getFontKerning },
		{ "SetFontKerning", setFontKerning },
		{ "GetFontHeight", getFontHeight },
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
}