#ifndef _MEDIA_H_
#define _MEDIA_H_

#include <lua.hpp>
#include <SDL.h>
#include <SDL_mixer.h>

// 加载音乐文件
// 1参数：音乐文件路径
// 1返回值：-1，加载文件失败；其他，已加载的音乐文件在音乐库中的标志
extern "C" int loadMusic(lua_State * L);

// 释放已加载的音乐
// 1参数：已加载的音乐文件在音乐库中的标志
// 1返回值：-1，释放音乐失败；0，释放音乐成功
extern "C" int unloadMusic(lua_State * L);

// 播放已加载的音乐
// 2参数：已加载的音乐文件在音乐库中的标志、音乐播放的次数（-1为循环播放）
// 1返回值：-1，播放音乐失败；0，播放音乐成功
extern "C" int playMusic(lua_State * L);

// 播放淡入音乐
// 3参数：已加载的音乐文件在音乐库中的标志、音乐播放的次数、淡入音效持续时间（ms）
// 1参数：-1，播放音乐失败；0，播放音乐成功
extern "C" int fadeInMusic(lua_State * L);

// 淡出并停止当前正在播放的音乐
// 1参数：淡出音效持续时间（ms）
// 无返回值
extern "C" int fadeOutMusic(lua_State * L);

// 设置音乐播放的音量
// 1参数：音量大小（0-128）
// 无返回值
extern "C" int setMusicVolume(lua_State * L);

// 获取当前音乐音量
// 无参数
// 1返回值：当前音乐音量大小
extern "C" int getMusicVolume(lua_State * L);

// 暂停当前正在播放的音乐
// 无参数
// 无返回值
extern "C" int pauseMusic(lua_State * L);

// 恢复当前暂停状态的音乐
// 无参数
// 无返回值
extern "C" int resumeMusic(lua_State * L);

// 重播当前正在播放的音乐
// 无参数
// 无返回值
extern "C" int rewindMusic(lua_State * L);

// 获取指定音乐的类型
// 1参数：已加载的音乐文件在音乐库中的标志（nil表示正在播放的音乐）
// 1返回值：成功则返回指定音乐的类型（字符串），未知则返回"UNKONWN"，失败则返回"ERROR"
extern "C" int getMusicType(lua_State * L);

// 加载音效文件
// 1参数：音效文件路径
// 1返回值：-1，加载音效文件失败；其他，已加载的音效文件在音效库中的标志
// 备注：音效文件支持以下格式：WAVE, AIFF, RIFF, OGG, VOC
extern "C" int loadSound(lua_State * L);

// 释放已加载的音效
// 1参数：已加载的音效文件在音乐库中的标志
// 1返回值：-1，释放音效失败；0，释放音效成功
extern "C" int unloadSound(lua_State * L);

// 播放已加载的音效
// 2参数：已加载的音效文件在音效库中的标志、音效播放的次数（-1为循环播放）
// 1返回值：-1，播放音乐失败；0，播放音乐成功
extern "C" int playSound(lua_State * L);


#endif // !_MEDIA_H_

