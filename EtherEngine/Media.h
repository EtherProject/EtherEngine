#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>
#include <SDL_mixer.h>

// 加载音乐文件
// 1参数：音乐文件路径
// 1返回值：成功则返回音乐数据（userdata-MUSIC），失败则返回nil
extern "C" int loadMusic(lua_State * L);

// 释放已加载的音乐
// 1参数：音乐数据（userdata-MUSIC）
// 0返回值
extern "C" int unloadMusic(lua_State * L);

// 播放已加载的音乐
// 2参数：音乐数据（userdata-MUSIC）、音乐播放的次数（number，-1为循环播放）
// 0返回值
extern "C" int playMusic(lua_State * L);

// 使用淡入效果播放已加载的音乐
// 3参数：音乐数据（userdata-MUSIC）、音乐播放的次数（number，-1为循环播放），淡入音效持续时间（number，单位为毫秒）
// 0返回值
extern "C" int fadeInMusic(lua_State * L);

// 使用淡出效果停止正在播放的音乐
// 1参数：淡出音效持续时间（number，单位为毫秒）
// 0返回值
extern "C" int fadeOutMusic(lua_State * L);

// 设置音乐播放的音量
// 1参数：音量大小（number，取值范围为0-128）
// 0返回值
extern "C" int setMusicVolume(lua_State * L);

// 获取当前音乐播放的音量
// 0参数
// 1返回值：音量大小（number，取值范围为0-128）
extern "C" int getMusicVolume(lua_State * L);

// 暂停当前正在播放的音乐
// 0参数
// 0返回值
extern "C" int pauseMusic(lua_State * L);

// 恢复当前暂停状态的音乐
// 0参数
// 0返回值
extern "C" int resumeMusic(lua_State * L);

// 重新播放当前正在播放的音乐
// 0参数
// 0返回值
extern "C" int rewindMusic(lua_State * L);

// 获取指定音乐的类型
// 1参数：音乐数据（userdata-MUSIC，nil表示正在播放的音乐）
// 1返回值：音乐类型（MACRO number）
extern "C" int getMusicType(lua_State * L);

// 加载音效文件
// 1参数：音效文件路径
// 1返回值：成功则返回音效数据（userdata-SOUND），失败则返回nil
extern "C" int loadSound(lua_State * L);

// 释放已加载的音效
// 1参数：音效数据（userdata-SOUND）
// 0返回值
extern "C" int unloadSound(lua_State * L);

// 播放已加载的音效
// 2参数：音效数据（userdata-MUSIC）、音效播放的次数（number，-1为循环播放）
// 0返回值
extern "C" int playSound(lua_State * L);


#endif // !_MEDIA_H_

