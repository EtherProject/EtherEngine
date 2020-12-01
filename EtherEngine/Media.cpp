#include "Media.h"


extern "C" int loadMusic(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	Mix_Music* music = Mix_LoadMUS(path);
	music ? lua_pushlightuserdata(L, music) : lua_pushnil(L);

	return 1;
}


extern "C" int unloadMusic(lua_State * L)
{
	Mix_Music* music = (Mix_Music*)lua_touserdata(L, 1);
	if (!music)
	{
		luaL_error(L, "bad argument #1 to 'UnloadMusic' (userdata-MUSIC expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		Mix_FreeMusic(music);
		music = NULL;
	}
	return 0;
}


extern "C" int playMusic(lua_State * L)
{
	Mix_Music* music = (Mix_Music*)lua_touserdata(L, 1);
	if (!music)
	{
		luaL_error(L, "bad argument #1 to 'PlayMusic' (userdata-MUSIC expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		Mix_PlayMusic(music, luaL_checknumber(L, 2));
	}

	return 0;
}


extern "C" int fadeInMusic(lua_State * L)
{
	Mix_Music* music = (Mix_Music*)lua_touserdata(L, 1);
	if (!music)
	{
		luaL_error(L, "bad argument #1 to 'PlayMusic' (userdata-MUSIC expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		Mix_FadeInMusic(music, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	}

	return 0;
}


extern "C" int fadeOutMusic(lua_State * L)
{
	Mix_FadeOutMusic(luaL_checknumber(L, 1));

	return 0;
}


extern "C" int setMusicVolume(lua_State * L)
{
	Mix_VolumeMusic(luaL_checknumber(L, 1));

	return 0;
}


extern "C" int getMusicVolume(lua_State * L)
{
	lua_pushnumber(L, Mix_VolumeMusic(-1));

	return 1;
}


extern "C" int pauseMusic(lua_State * L)
{
	Mix_PauseMusic();

	return 0;
}


extern "C" int resumeMusic(lua_State * L)
{
	Mix_ResumeMusic();

	return 0;
}


extern "C" int rewindMusic(lua_State * L)
{
	Mix_RewindMusic();

	return 0;
}


extern "C" int getMusicType(lua_State * L)
{
	Mix_Music* music = (Mix_Music*)lua_touserdata(L, 1);
	switch (Mix_GetMusicType(music))
	{
	case MUS_WAV:
		lua_pushstring(L, "WAV");
		break;
	case MUS_MP3:
		lua_pushstring(L, "MP3");
		break;
	case MUS_OGG:
		lua_pushstring(L, "OGG");
		break;
	case MUS_CMD:
		lua_pushstring(L, "CMD");
		break;
	case MUS_MOD:
		lua_pushstring(L, "MOD");
		break;
	case MUS_MID:
		lua_pushstring(L, "MID");
		break;
	default:
		lua_pushstring(L, "UNKONWN");
		break;
	}

	return 1;
}


extern "C" int loadSound(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	Mix_Chunk* sound = Mix_LoadWAV(path);
	sound ? lua_pushlightuserdata(L, sound) : lua_pushnil(L);

	return 1;
}


extern "C" int unloadSound(lua_State * L)
{
	Mix_Chunk* sound = (Mix_Chunk*)lua_touserdata(L, 1);
	if (!sound)
	{
		luaL_error(L, "bad argument #1 to 'UnloadSound' (userdata-SOUND expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		Mix_FreeChunk(sound);
		sound = NULL;
	}

	return 0;
}


extern "C" int playSound(lua_State * L)
{
	Mix_Chunk* sound = (Mix_Chunk*)lua_touserdata(L, 1);
	if (!sound)
	{
		luaL_error(L, "bad argument #1 to 'PlaySound' (userdata-SOUND expected, got %s)", luaL_typename(L, 1));
	}
	else
	{
		Mix_PlayChannel(-1, sound, luaL_checknumber(L, 2));
	}

	return 0;
}