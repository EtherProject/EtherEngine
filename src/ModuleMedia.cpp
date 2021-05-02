#include "ModuleMedia.h"


ModuleMedia& ModuleMedia::Instance()
{
	static ModuleMedia* _instance = new ModuleMedia();
	return *_instance;
}


ModuleMedia::ModuleMedia()
{
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

	_vMetaData = {
		{ METANAME_MUSIC },
		{ METANAME_SOUND },
	};
}


ETHER_API loadMusic(lua_State * L)
{
	Mix_Music* music = Mix_LoadMUS(luaL_checkstring(L, 1));
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, music, 1, "load music failed");
#endif
	Mix_Music** uppMusic = (Mix_Music**)lua_newuserdata(L, sizeof(Mix_Music*));
	*uppMusic = music;
	luaL_getmetatable(L, METANAME_MUSIC);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API unloadMusic(lua_State * L)
{
	Mix_Music* music = GetMusicDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAtFirstPos(music);
#endif
	Mix_FreeMusic(music);
	music = nullptr;

	lua_pushnil(L);

	return 1;
}


ETHER_API playMusic(lua_State * L)
{
	Mix_Music* music = GetMusicDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAtFirstPos(music);
#endif
	Mix_PlayMusic(music, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API fadeInMusic(lua_State * L)
{
	Mix_Music* music = GetMusicDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAtFirstPos(music);
#endif
	Mix_FadeInMusic(music, luaL_checknumber(L, 2), luaL_checknumber(L, 3));

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
	Mix_Music* music = GetMusicDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAtFirstPos(music);
#endif
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
	Mix_Chunk* sound = Mix_LoadWAV(luaL_checkstring(L, 1));
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, sound, 1, "load sound failed");
#endif
	Mix_Chunk** uppSound = (Mix_Chunk**)lua_newuserdata(L, sizeof(Mix_Chunk*));
	*uppSound = sound;
	luaL_getmetatable(L, METANAME_SOUND);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API unloadSound(lua_State * L)
{
	Mix_Chunk* sound = GetSoundDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckSoundDataAtFirstPos(sound);
#endif
	Mix_FreeChunk(sound);
	sound = nullptr;

	lua_pushnil(L);

	return 1;
}


ETHER_API playSound(lua_State * L)
{
	Mix_Chunk* sound = GetSoundDataAtFirstPos();
#ifdef _ETHER_DEBUG_
	CheckSoundDataAtFirstPos(sound);
#endif
	Mix_PlayChannel(-1, sound, luaL_checknumber(L, 2));

	return 0;
}