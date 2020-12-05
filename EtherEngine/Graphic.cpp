#include "Graphic.h"


extern "C" int setCursorShow(lua_State * L)
{
	SDL_ShowCursor(lua_toboolean(L, 1) ? SDL_ENABLE : SDL_DISABLE);

	return 0;
}


extern "C" int loadImage(lua_State * L)
{
	const char* path = luaL_checkstring(L, 1);
	SDL_Surface* surface = IMG_Load(path);
	surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);

	return 1;
}


extern "C" int setImageColorKey(lua_State * L)
{
	SDL_Surface* surface = (SDL_Surface*)lua_touserdata(L, 1);
	if (!surface)
	{
		luaL_error(L, "bad argument #1 to 'SetColorKey' (userdata-IMAGE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'SetColorKey' (table expected, got %s)", luaL_typename(L, 3));
		}
		else
		{
			SDL_Color color;
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'SetColorKey' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'SetColorKey' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'SetColorKey' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'SetColorKey' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));

			SDL_SetColorKey(surface, lua_toboolean(L, 2), SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
		}
	}

	return 0;
}


extern "C" int unloadImage(lua_State * L)
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


extern "C" int createTexture(lua_State * L)
{
	SDL_Surface* surface = (SDL_Surface*)lua_touserdata(L, 1);
	if (!surface)
	{
		luaL_error(L, "bad argument #1 to 'CreateTexture' (userdata-IMAGE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		lua_pushlightuserdata(L, texture);
	}

	return 1;
}

extern "C" int destroyTexture(lua_State * L)
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


extern "C" int setTextureAlpha(lua_State * L)
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


extern "C" int getImageSize(lua_State * L)
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


extern "C" int copyTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 2))
		{
			luaL_error(L, "bad argument #2 to 'CopyTexture' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			SDL_Rect rect;
			lua_getfield(L, 2, "x");
			lua_isnumber(L, -1) ? rect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 2, "y");
			lua_isnumber(L, -1) ? rect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 2, "w");
			lua_isnumber(L, -1) ? rect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyTexture' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 2, "h");
			lua_isnumber(L, -1) ? rect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyTexture' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));
			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}
	}

	return 0;
}


extern "C" int copyRotateTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyRotateTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		double degree = luaL_checknumber(L, 2);

		
		SDL_Point flipCenter;
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CopyRotateTexture' (table expected, got %s)", luaL_typename(L, 3));
		}
		else
		{
			lua_getfield(L, 3, "x");
			lua_isnumber(L, -1) ? flipCenter.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyRotateTexture' (table must have number value for key 'x')");
			lua_getfield(L, 3, "y");
			lua_isnumber(L, -1) ? flipCenter.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyRotateTexture' (table must have number value for key 'y')");
		}

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

		SDL_Rect showRect;
		if (!lua_istable(L, 5))
		{
			luaL_error(L, "bad argument #5 to 'CopyRotateTexture' (table expected, got %s)", luaL_typename(L, 5));
		}
		else
		{
			lua_getfield(L, 5, "x");
			lua_isnumber(L, -1) ? showRect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 5, "y");
			lua_isnumber(L, -1) ? showRect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 5, "w");
			lua_isnumber(L, -1) ? showRect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateTexture' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 5, "h");
			lua_isnumber(L, -1) ? showRect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateTexture' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));
		}
		SDL_RenderCopyEx(renderer, texture, NULL, &showRect, degree, &flipCenter, flip);
	}

	return 0;
}


extern "C" int copyReshapeTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyReshapeTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Rect reshapeRect;
		if (!lua_istable(L, 2))
		{
			luaL_error(L, "bad argument #2 to 'CopyReshapeTexture' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			lua_getfield(L, 2, "x");
			lua_isnumber(L, -1) ? reshapeRect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyReshapeTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 2, "y");
			lua_isnumber(L, -1) ? reshapeRect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyReshapeTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 2, "w");
			lua_isnumber(L, -1) ? reshapeRect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyReshapeTexture' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 2, "h");
			lua_isnumber(L, -1) ? reshapeRect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'CopyReshapeTexture' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));
		}

		SDL_Rect showRect;
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'copyReshapeTexture' (table expected, got %s)", luaL_typename(L, 3));
		}
		else
		{
			lua_getfield(L, 3, "x");
			lua_isnumber(L, -1) ? showRect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyReshapeTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "y");
			lua_isnumber(L, -1) ? showRect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyReshapeTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "w");
			lua_isnumber(L, -1) ? showRect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyReshapeTexture' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "h");
			lua_isnumber(L, -1) ? showRect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyReshapeTexture' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));
		}

		SDL_RenderCopy(renderer, texture, &reshapeRect, &showRect);
	}

	return 0;
}


extern "C" int copyRotateReshapeTexture(lua_State * L)
{
	SDL_Texture* texture = (SDL_Texture*)lua_touserdata(L, 1);
	if (!texture)
	{
		luaL_error(L, "bad argument #1 to 'CopyRotateReshapeTexture' (userdata-TEXTURE expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		int degree = luaL_checknumber(L, 2);

		SDL_Point flipCenter;
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CopyRotateReshapeTexture' (table expected, got %s)", luaL_typename(L, 3));
		}
		else
		{
			lua_getfield(L, 3, "x");
			lua_isnumber(L, -1) ? flipCenter.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyRotateReshapeTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "y");
			lua_isnumber(L, -1) ? flipCenter.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CopyRotateReshapeTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
		}

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

		SDL_Rect reshapeRect;
		if (!lua_istable(L, 5))
		{
			luaL_error(L, "bad argument #5 to 'CopyRotateReshapeTexture' (table expected, got %s)", luaL_typename(L, 5));
		}
		else
		{
			lua_getfield(L, 5, "x");
			lua_isnumber(L, -1) ? reshapeRect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateReshapeTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 5, "y");
			lua_isnumber(L, -1) ? reshapeRect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateReshapeTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 5, "w");
			lua_isnumber(L, -1) ? reshapeRect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateReshapeTexture' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 5, "h");
			lua_isnumber(L, -1) ? reshapeRect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #5 to 'CopyRotateReshapeTexture' (table must have number value for key 'h'), got %s)", luaL_typename(L, -1));
		}

		SDL_Rect showRect;
		if (!lua_istable(L, 6))
		{
			luaL_error(L, "bad argument #6 to 'CopyRotateReshapeTexture' (table expected, got %s)", luaL_typename(L, 6));
		}
		else
		{
			lua_getfield(L, 6, "x");
			lua_isnumber(L, -1) ? showRect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #6 to 'CopyRotateReshapeTexture' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 6, "y");
			lua_isnumber(L, -1) ? showRect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #6 to 'CopyRotateReshapeTexture' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 6, "w");
			lua_isnumber(L, -1) ? showRect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #6 to 'CopyRotateReshapeTexture' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 6, "h");
			lua_isnumber(L, -1) ? showRect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #6 to 'CopyRotateReshapeTexture' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));
		}

		SDL_RenderCopyEx(renderer, texture, &reshapeRect, &showRect, degree, &flipCenter, flip);
	}

	return 0;
}


extern "C" int setDrawColor(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'SetDrawColor' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color color;
		lua_getfield(L, 1, "r");
		lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'SetDrawColor' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "g");
		lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'SetDrawColor' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "b");
		lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'SetDrawColor' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "a");
		lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'SetDrawColor' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}

	return 0;
}


extern "C" int getDrawColor(lua_State * L)
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


extern "C" int point(lua_State * L)
{
	
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Point' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Point' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Point' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_RenderDrawPoint(renderer, point.x, point.y);
	}

	return 0;
}


extern "C" int line(lua_State * L)
{
	SDL_Point startPoint;
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Line' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? startPoint.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Line' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? startPoint.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Line' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Point endPoint;
	if (!lua_istable(L, 2))
	{
		luaL_error(L, "bad argument #2 to 'Line' (table expected, got %s)", luaL_typename(L, 2));
	}
	else
	{
		lua_getfield(L, 2, "x");
		lua_isnumber(L, -1) ? endPoint.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'Line' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 2, "y");
		lua_isnumber(L, -1) ? endPoint.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'Line' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aalineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, color.r, color.g, color.b, color.a);

	return 0;
}


extern "C" int thickLine(lua_State * L)
{
	SDL_Point startPoint;
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'ThickLine' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? startPoint.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'ThickLine' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? startPoint.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'ThickLine' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Point endPoint;
	if (!lua_istable(L, 2))
	{
		luaL_error(L, "bad argument #2 to 'ThickLine' (table expected, got %s)", luaL_typename(L, 2));
	}
	else
	{
		lua_getfield(L, 2, "x");
		lua_isnumber(L, -1) ? endPoint.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'ThickLine' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 2, "y");
		lua_isnumber(L, -1) ? endPoint.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'ThickLine' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	thickLineRGBA(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y, luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);

	return 0;
}


extern "C" int rectangle(lua_State * L)
{
	
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Rectangle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Rect rect;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? rect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Rectangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? rect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Rectangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "w");
		lua_isnumber(L, -1) ? rect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Rectangle' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "h");
		lua_isnumber(L, -1) ? rect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Rectangle' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));

		SDL_RenderDrawRect(renderer, &rect);
	}

	return 0;
}


extern "C" int fillRectangle(lua_State * L)
{
	SDL_Rect rect;
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'FillRectangle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? rect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillRectangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? rect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillRectangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "w");
		lua_isnumber(L, -1) ? rect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillRectangle' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "h");
		lua_isnumber(L, -1) ? rect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillRectangle' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));

		SDL_RenderFillRect(renderer, &rect);
	}

	return 0;
}


extern "C" int roundRectangle(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'RoundRectangle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Rect rect;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? rect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? rect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "w");
		lua_isnumber(L, -1) ? rect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "h");
		lua_isnumber(L, -1) ? rect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		roundedRectangleRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);
	}

	return 0;
}


extern "C" int fillRoundRectangle(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'RoundRectangle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Rect rect;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? rect.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? rect.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "w");
		lua_isnumber(L, -1) ? rect.w = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'w', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "h");
		lua_isnumber(L, -1) ? rect.h = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'RoundRectangle' (table must have number value for key 'h', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);
	}

	return 0;
}


extern "C" int circle(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Circle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Circle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Circle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		aacircleRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);
	}

	return 0;
}


extern "C" int fillCircle(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'FillCircle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillCircle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillCircle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		filledCircleRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), color.r, color.g, color.b, color.a);
	}

	return 0;
}


extern "C" int ellipse(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Ellipse' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Ellipse' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Ellipse' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		aaellipseRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);
	}

	return 0;
}


extern "C" int fillEllipse(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'FillEllipse' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillEllipse' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillEllipse' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		aaellipseRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), color.r, color.g, color.b, color.a);
	}

	return 0;
}

extern "C" int pie(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Pie' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Pie' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Pie' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		pieRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), color.r, color.g, color.b, color.a);
	}

	return 0;
}

extern "C" int fillPie(lua_State * L)
{
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'FillPie' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Point point;
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillPie' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillPie' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));

		SDL_Color color;
		SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
		filledPieRGBA(renderer, point.x, point.y, luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), color.r, color.g, color.b, color.a);
	}

	return 0;
}

extern "C" int triangle(lua_State * L)
{
	SDL_Point point_1;
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'Triangle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point_1.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Triangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point_1.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'Triangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Point point_2;
	if (!lua_istable(L, 2))
	{
		luaL_error(L, "bad argument #2 to 'Triangle' (table expected, got %s)", luaL_typename(L, 2));
	}
	else
	{
		lua_getfield(L, 2, "x");
		lua_isnumber(L, -1) ? point_2.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'Triangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 2, "y");
		lua_isnumber(L, -1) ? point_2.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'Triangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Point point_3;
	if (!lua_istable(L, 3))
	{
		luaL_error(L, "bad argument #3 to 'Triangle' (table expected, got %s)", luaL_typename(L, 3));
	}
	else
	{
		lua_getfield(L, 3, "x");
		lua_isnumber(L, -1) ? point_3.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'Triangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 3, "y");
		lua_isnumber(L, -1) ? point_3.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'Triangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	aatrigonRGBA(renderer, point_1.x, point_1.y, point_2.x, point_2.y, point_3.x, point_3.y, color.r, color.g, color.b, color.a);

	return 0;
}

extern "C" int fillTriangle(lua_State * L)
{
	SDL_Point point_1;
	if (!lua_istable(L, 1))
	{
		luaL_error(L, "bad argument #1 to 'FillTriangle' (table expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		lua_getfield(L, 1, "x");
		lua_isnumber(L, -1) ? point_1.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillTriangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 1, "y");
		lua_isnumber(L, -1) ? point_1.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #1 to 'FillTriangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Point point_2;
	if (!lua_istable(L, 2))
	{
		luaL_error(L, "bad argument #2 to 'FillTriangle' (table expected, got %s)", luaL_typename(L, 2));
	}
	else
	{
		lua_getfield(L, 2, "x");
		lua_isnumber(L, -1) ? point_2.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'FillTriangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 2, "y");
		lua_isnumber(L, -1) ? point_2.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #2 to 'FillTriangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Point point_3;
	if (!lua_istable(L, 3))
	{
		luaL_error(L, "bad argument #3 to 'FillTriangle' (table expected, got %s)", luaL_typename(L, 3));
	}
	else
	{
		lua_getfield(L, 3, "x");
		lua_isnumber(L, -1) ? point_3.x = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'FillTriangle' (table must have number value for key 'x', got %s)", luaL_typename(L, -1));
		lua_getfield(L, 3, "y");
		lua_isnumber(L, -1) ? point_3.y = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'FillTriangle' (table must have number value for key 'y', got %s)", luaL_typename(L, -1));
	}

	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &(color.r), &(color.g), &(color.b), &(color.a));
	filledTrigonRGBA(renderer, point_1.x, point_1.y, point_2.x, point_2.y, point_3.x, point_3.y, color.r, color.g, color.b, color.a);

	return 0;
}


extern "C" int loadFont(lua_State * L)
{
	const char* path = luaL_checkstring(L, 1);
	int size = luaL_checknumber(L, 2);
	TTF_Font* font = TTF_OpenFont(path, size);
	font ? lua_pushlightuserdata(L, font) : lua_pushnil(L);

	return 1;
}


extern "C" int unloadFont(lua_State * L)
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


extern "C" int getFontStyle(lua_State * L)
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


extern "C" int setFontStyle(lua_State * L)
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


extern "C" int getFontOutlineWidth(lua_State * L)
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


extern "C" int setFontOutlineWidth(lua_State * L)
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


extern "C" int getFontKerning(lua_State * L)
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


extern "C" int setFontKerning(lua_State * L)
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


extern "C" int getFontHeight(lua_State * L)
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


extern "C" int getTextSize(lua_State * L)
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


extern "C" int getUTF8TextSize(lua_State * L)
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


extern "C" int createTextImageSolid(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateTextImageSolid' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			SDL_Color color;
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
			SDL_Surface* surface = TTF_RenderText_Solid(font, luaL_checkstring(L, 2), color);
			surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
		}
	}

	return 1;
}


extern "C" int createUTF8TextImageSolid(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateUTF8TextImageSolid' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageSolid' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			SDL_Color color;
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageSolid' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageSolid' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageSolid' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageSolid' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
			SDL_Surface* surface = TTF_RenderUTF8_Solid(font, luaL_checkstring(L, 2), color);
			surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
		}
	}

	return 1;
}


extern "C" int createTextImageShaded(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateTextImageSolid' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color fgColor;
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? fgColor.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? fgColor.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? fgColor.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? fgColor.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageSolid' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
		}

		SDL_Color bgColor;
		if (!lua_istable(L, 4))
		{
			luaL_error(L, "bad argument #4 to 'CreateTextImageSolid' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			lua_getfield(L, 4, "r");
			lua_isnumber(L, -1) ? bgColor.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateTextImageSolid' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 4, "g");
			lua_isnumber(L, -1) ? bgColor.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateTextImageSolid' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 4, "b");
			lua_isnumber(L, -1) ? bgColor.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateTextImageSolid' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 4, "a");
			lua_isnumber(L, -1) ? bgColor.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateTextImageSolid' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
		}

		SDL_Surface* surface = TTF_RenderText_Shaded(font, luaL_checkstring(L, 2), fgColor, bgColor);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


extern "C" int createUTF8TextImageShaded(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateUTF8TextImageShaded' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		SDL_Color fgColor;
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageShaded' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? fgColor.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageShaded' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? fgColor.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageShaded' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? fgColor.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageShaded' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? fgColor.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageShaded' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
		}

		SDL_Color bgColor;
		if (!lua_istable(L, 4))
		{
			luaL_error(L, "bad argument #4 to 'CreateUTF8TextImageShaded' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			lua_getfield(L, 4, "r");
			lua_isnumber(L, -1) ? bgColor.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateUTF8TextImageShaded' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 4, "g");
			lua_isnumber(L, -1) ? bgColor.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateUTF8TextImageShaded' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 4, "b");
			lua_isnumber(L, -1) ? bgColor.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateUTF8TextImageShaded' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 4, "a");
			lua_isnumber(L, -1) ? bgColor.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #4 to 'CreateUTF8TextImageShaded' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
		}

		SDL_Surface* surface = TTF_RenderUTF8_Shaded(font, luaL_checkstring(L, 2), fgColor, bgColor);
		surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
	}

	return 1;
}


extern "C" int createTextImageBlended(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateTextImageBlended' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CreateTextImageBlended' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			SDL_Color color;
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageBlended' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageBlended' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageBlended' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateTextImageBlended' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
			SDL_Surface* surface = TTF_RenderText_Blended(font, luaL_checkstring(L, 2), color);
			surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
		}
	}

	return 1;
}


extern "C" int createUTF8TextImageBlended(lua_State * L)
{
	TTF_Font* font = (TTF_Font*)lua_touserdata(L, 1);
	if (!font)
	{
		luaL_error(L, "bad argument #1 to 'CreateUTF8TextImageBlended' (userdata-FONT expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		if (!lua_istable(L, 3))
		{
			luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageBlended' (table expected, got %s)", luaL_typename(L, 2));
		}
		else
		{
			SDL_Color color;
			lua_getfield(L, 3, "r");
			lua_isnumber(L, -1) ? color.r = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageBlended' (table must have number value for key 'r', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "g");
			lua_isnumber(L, -1) ? color.g = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageBlended' (table must have number value for key 'g', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "b");
			lua_isnumber(L, -1) ? color.b = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageBlended' (table must have number value for key 'b', got %s)", luaL_typename(L, -1));
			lua_getfield(L, 3, "a");
			lua_isnumber(L, -1) ? color.a = lua_tonumber(L, -1) : luaL_error(L, "bad argument #3 to 'CreateUTF8TextImageBlended' (table must have number value for key 'a', got %s)", luaL_typename(L, -1));
			SDL_Surface* surface = TTF_RenderUTF8_Blended(font, luaL_checkstring(L, 2), color);
			surface ? lua_pushlightuserdata(L, surface) : lua_pushnil(L);
		}
	}

	return 1;
}


extern "C" int updateWindow(lua_State * L)
{
	SDL_RenderPresent(renderer);

	return 0;
}