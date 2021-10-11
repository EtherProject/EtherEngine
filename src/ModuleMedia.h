#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "Module.h"
#include "Macros.h"

#include "lua.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MUSIC_TYPE_WAV					1308
#define MUSIC_TYPE_MP3					1309
#define MUSIC_TYPE_OGG					1310
#define MUSIC_TYPE_CMD					1311
#define MUSIC_TYPE_MOD					1312
#define MUSIC_TYPE_MID					1313
#define MUSIC_TYPE_UNKONWN				1314

#define FADING_TYPE_NONE				1315
#define FADING_TYPE_IN					1316
#define FADING_TYPE_OUT					1317

#define METANAME_MUSIC					"Graphic.Music"
#define METANAME_SOUND					"Graphic.Sound"

#define GetMusicDataAt1stPos()			(Mix_Music*)(*(void**)luaL_checkudata(L, 1, METANAME_MUSIC))
#define GetSoundDataAt1stPos()			(Mix_Chunk*)(*(void**)luaL_checkudata(L, 1, METANAME_SOUND))

#define CheckMusicDataAt1stPos(music)	luaL_argcheck(L, music, 1, "get music data failed")
#define CheckSoundDataAt1stPos(sound)	luaL_argcheck(L, sound, 1, "get sound data failed")

class ModuleMedia : public Module
{
public:
	static ModuleMedia& Instance();
	~ModuleMedia() {};

private:
	ModuleMedia();

};

// 加载音乐文件
// 1参数：音乐文件路径
// 1返回值：成功则返回音乐数据（userdata-Music），失败则返回nil
ETHER_API loadMusic(lua_State * L);

// 音乐数据GC函数
// 1参数：音乐数据（userdata-Music）
// 0返回值
ETHER_API __gc_Music(lua_State * L);

// 播放已加载的音乐
// 2参数：音乐数据（userdata-Music）、音乐播放的次数（number，-1为循环播放）
// 0返回值
ETHER_API playMusic(lua_State * L);

// 使用淡入效果播放已加载的音乐
// 3参数：音乐数据（userdata-Music）、音乐播放的次数（number，-1为循环播放），淡入音效持续时间（number，单位为毫秒）
// 0返回值
ETHER_API playMusicWithFadeIn(lua_State * L);

// 停止正在播放的音乐
// 0参数
// 0返回值
ETHER_API stopMusic(lua_State* L);

// 使用淡出效果停止正在播放的音乐
// 1参数：淡出音效持续时间（number，单位为毫秒）
// 0返回值
ETHER_API stopMusicWithFadeOut(lua_State * L);

// 设置当音乐的播放位置
// 1参数：播放位置（number）
// 0返回值
// 备注：此操作仅支持以下三种格式的音乐，且参数意义各不相同：
// MOD：设置当前播放位置为此编码模型中对应索引的数据块处，0 将跳转至音乐开头
// OGG：设置当前播放位置为从音乐开始位置计算的指定秒数处
// MP3：设置当前播放位置为从当前播放位置计算的指定秒数处，可以使用 RewindMusic 将当前音乐的播放位置重置到开始处
ETHER_API setMusicPosition(lua_State* L);

// 设置音乐播放的音量
// 1参数：音量大小（number，取值范围为0-128）
// 0返回值
ETHER_API setMusicVolume(lua_State * L);

// 获取当前音乐播放的音量
// 0参数
// 1返回值：音量大小（number，取值范围为0-128）
ETHER_API getMusicVolume(lua_State * L);

// 暂停当前正在播放的音乐
// 0参数
// 0返回值
ETHER_API pauseMusic(lua_State * L);

// 恢复当前暂停状态的音乐
// 0参数
// 0返回值
ETHER_API resumeMusic(lua_State * L);

// 重新播放当前正在播放的音乐
// 0参数
// 0返回值
ETHER_API rewindMusic(lua_State * L);

// 判断当前音乐是否正在播放
// 0参数
// 1返回值：是否正在播放（boolean）
ETHER_API checkMusicPlaying(lua_State* L);

// 判断当前音乐是否已暂停
// 0参数
// 1返回值：是否已暂停（boolean）
ETHER_API checkMusicPaused(lua_State* L);

// 获取当前正在播放的音乐的淡化效果类型
// 0参数
// 1返回值：淡化效果类型（MACRO number）
ETHER_API getMusicFadingType(lua_State* L);

// 获取指定音乐的类型
// 1参数：音乐数据（userdata-Music，nil表示正在播放的音乐）
// 1返回值：音乐类型（MACRO number）
ETHER_API music_GetType(lua_State * L);

// 从文件中加载音效
// 1参数：音效文件路径
// 1返回值：成功则返回音效数据（userdata-Sound），失败则返回nil
ETHER_API loadSoundFromFile(lua_State * L);

// 从缓冲区中加载音效
// 1参数：缓冲区数据（string）
// 1返回值：成功则返回音效数据（userdata-Sound），失败则返回nil
ETHER_API loadSoundFromData(lua_State* L);

// 音效数据GC函数
// 1参数：音效数据（userdata-Sound）
// 0返回值
ETHER_API __gc_Sound(lua_State * L);

// 播放已加载的音效
// 2参数：音效数据（userdata-Sound）、音效播放的次数（number，-1为循环播放）
// 0返回值
ETHER_API sound_Play(lua_State * L);

// 设置音效播放的音量
// 2参数：音效数据（userdata-Sound），音量大小（number，取值范围为0-128）
// 0返回值
ETHER_API sound_SetVolume(lua_State* L);

// 获取音效播放的音量
// 1参数：音效数据（userdata-Sound）
// 1返回值：音量大小（number，取值范围为0-128）
ETHER_API sound_GetVolume(lua_State* L);

#endif // !_MEDIA_H_

