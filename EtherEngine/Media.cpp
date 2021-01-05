#include "Media.h"


ETHER_API loadMusic(lua_State * L)
{
	const char* path = luaL_checkstring(L, 1);
	Mix_Music* music = Mix_LoadMUS(path);
	music ? lua_pushlightuserdata(L, music) : lua_pushnil(L);

	return 1;
}


ETHER_API unloadMusic(lua_State * L)
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


ETHER_API playMusic(lua_State * L)
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


ETHER_API fadeInMusic(lua_State * L)
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


ETHER_API fadeOutMusic(lua_State * L)
{
	Mix_FadeOutMusic(luaL_checknumber(L, 1));

	return 0;
}


ETHER_API setMusicVolume(lua_State * L)
{
	Mix_VolumeMusic(luaL_checknumber(L, 1));

	return 0;
}


ETHER_API getMusicVolume(lua_State * L)
{
	lua_pushnumber(L, Mix_VolumeMusic(-1));

	return 1;
}


ETHER_API pauseMusic(lua_State * L)
{
	Mix_PauseMusic();

	return 0;
}


ETHER_API resumeMusic(lua_State * L)
{
	Mix_ResumeMusic();

	return 0;
}


ETHER_API rewindMusic(lua_State * L)
{
	Mix_RewindMusic();

	return 0;
}


ETHER_API getMusicType(lua_State * L)
{
	Mix_Music* music = (Mix_Music*)lua_touserdata(L, 1);
	switch (Mix_GetMusicType(music))
	{
	case MUS_WAV:
		lua_pushnumber(L, MUSIC_TYPE_WAV);
		break;
	case MUS_MP3:
		lua_pushnumber(L, MUSIC_TYPE_MP3);
		break;
	case MUS_OGG:
		lua_pushnumber(L, MUSIC_TYPE_OGG);
		break;
	case MUS_CMD:
		lua_pushnumber(L, MUSIC_TYPE_CMD);
		break;
	case MUS_MOD:
		lua_pushnumber(L, MUSIC_TYPE_MOD);
		break;
	case MUS_MID:
		lua_pushnumber(L, MUSIC_TYPE_MID);
		break;
	default:
		lua_pushnumber(L, MUSIC_TYPE_UNKONWN);
		break;
	}

	return 1;
}


ETHER_API loadSound(lua_State * L)
{
	const char* path = lua_tostring(L, 1);
	Mix_Chunk* sound = Mix_LoadWAV(path);
	sound ? lua_pushlightuserdata(L, sound) : lua_pushnil(L);

	return 1;
}


ETHER_API unloadSound(lua_State * L)
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


ETHER_API playSound(lua_State * L)
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


MoudleMedia::MoudleMedia(lua_State* L)
{
	_pL = L;

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	_vCMethods = {
		{ "LoadMusic", loadMusic },
		{ "UnloadMusic", unloadMusic },
		{ "PlayMusic", playMusic },
		{ "FadeInMusic", fadeInMusic },
		{ "FadeOutMusic", fadeOutMusic },
		{ "SetMusicVolume", setMusicVolume },
		{ "GetMusicVolume", getMusicVolume },
		{ "PauseMusic", pauseMusic },
		{ "ResumeMusic", resumeMusic },
		{ "RewindMusic", rewindMusic },
		{ "GetMusicType", getMusicType },
		{ "LoadSound", loadSound },
		{ "UnloadSound", unloadSound },
		{ "PlaySound", playSound },
	};

	_vMacros = {
		{ "MUSIC_TYPE_WAV", MUSIC_TYPE_WAV },
		{ "MUSIC_TYPE_MP3", MUSIC_TYPE_MP3 },
		{ "MUSIC_TYPE_OGG", MUSIC_TYPE_OGG },
		{ "MUSIC_TYPE_CMD", MUSIC_TYPE_CMD },
		{ "MUSIC_TYPE_MOD", MUSIC_TYPE_MOD },
		{ "MUSIC_TYPE_MID", MUSIC_TYPE_MID },
		{ "MUSIC_TYPE_UNKONWN", MUSIC_TYPE_UNKONWN },
	};
}