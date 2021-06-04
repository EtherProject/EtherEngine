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
		{ "PlayMusic", playMusic },
		{ "PlayMusicWithFadeIn", playMusicWithFadeIn },
		{ "SetMusicPosition", setMusicPosition },
		{ "SetMusicVolume", setMusicVolume },
		{ "GetMusicVolume", getMusicVolume },
		{ "StopMusic", stopMusic },
		{ "StopMusicWithFadeOut", stopMusicWithFadeOut },
		{ "PauseMusic", pauseMusic },
		{ "ResumeMusic", resumeMusic },
		{ "RewindMusic", rewindMusic },
		{ "CheckMusicPlaying", checkMusicPlaying },
		{ "CheckMusicPaused", checkMusicPaused },
		{ "GetMusicFadingType", getMusicFadingType },
		{ "LoadSoundFromFile", loadSoundFromFile },
		{ "LoadSoundFromData", loadSoundFromData },
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
		{ 
			METANAME_MUSIC,
			{
				{ "GetType", music_GetType },
			},
			__gc_Music
		},
		{ 
			METANAME_SOUND,
			{
				{ "Play", sound_Play },
				{ "SetVolume", sound_SetVolume },
			},
			__gc_Sound
		},
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


ETHER_API __gc_Music(lua_State * L)
{
	Mix_Music* music = GetMusicDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAt1stPos(music);
#endif
	Mix_FreeMusic(music);
	music = nullptr;

	return 0;
}


ETHER_API playMusic(lua_State * L)
{
	Mix_Music* music = GetMusicDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAt1stPos(music);
#endif
	Mix_PlayMusic(music, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API playMusicWithFadeIn(lua_State * L)
{
	Mix_Music* music = GetMusicDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAt1stPos(music);
#endif
	Mix_FadeInMusic(music, luaL_checknumber(L, 2), luaL_checknumber(L, 3));

	return 0;
}


ETHER_API stopMusic(lua_State* L)
{
	Mix_HaltMusic();

	return 0;
}


ETHER_API stopMusicWithFadeOut(lua_State * L)
{
	Mix_FadeOutMusic(luaL_checknumber(L, 1));

	return 0;
}


ETHER_API setMusicPosition(lua_State* L)
{
	Mix_SetMusicPosition(luaL_checknumber(L, 1));

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


ETHER_API checkMusicPlaying(lua_State* L)
{
	lua_pushboolean(L, Mix_PlayingMusic());

	return 1;
}


ETHER_API checkMusicPaused(lua_State* L)
{
	lua_pushboolean(L, Mix_PausedMusic());

	return 1;
}


ETHER_API getMusicFadingType(lua_State* L)
{
	switch (Mix_FadingMusic())
	{
	case MIX_NO_FADING:
		lua_pushinteger(L, FADING_TYPE_NONE);
		break;
	case MIX_FADING_OUT:
		lua_pushinteger(L, FADING_TYPE_OUT);
		break;
	case MIX_FADING_IN:
		lua_pushinteger(L, FADING_TYPE_IN);
		break;
	default:
		break;
	}

	return 1;
}


ETHER_API music_GetType(lua_State * L)
{
	Mix_Music* music = GetMusicDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckMusicDataAt1stPos(music);
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


ETHER_API loadSoundFromFile(lua_State * L)
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


ETHER_API loadSoundFromData(lua_State* L)
{
	size_t size = 0;
	const char* data = luaL_checklstring(L, 1, &size);
	Mix_Chunk* sound = Mix_LoadWAV_RW(SDL_RWFromMem((void*)data, size), 1);
#ifdef _ETHER_DEBUG_
	luaL_argcheck(L, sound, 1, "load sound failed");
#endif
	Mix_Chunk** uppSound = (Mix_Chunk**)lua_newuserdata(L, sizeof(Mix_Chunk*));
	*uppSound = sound;
	luaL_getmetatable(L, METANAME_SOUND);
	lua_setmetatable(L, -2);

	return 1;
}


ETHER_API __gc_Sound(lua_State * L)
{
	Mix_Chunk* sound = GetSoundDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckSoundDataAt1stPos(sound);
#endif
	Mix_FreeChunk(sound);
	sound = nullptr;

	return 0;
}


ETHER_API sound_Play(lua_State * L)
{
	Mix_Chunk* sound = GetSoundDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckSoundDataAt1stPos(sound);
#endif
	Mix_PlayChannel(-1, sound, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API sound_SetVolume(lua_State* L)
{
	Mix_Chunk* sound = GetSoundDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckSoundDataAt1stPos(sound);
#endif
	Mix_VolumeChunk(sound, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API sound_GetVolume(lua_State* L)
{
	Mix_Chunk* sound = GetSoundDataAt1stPos();
#ifdef _ETHER_DEBUG_
	CheckSoundDataAt1stPos(sound);
#endif
	lua_pushnumber(L, sound->volume);

	return 1;
}