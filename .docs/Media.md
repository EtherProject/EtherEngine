# Ether媒体相关操作
> ## LoadMusic
加载音乐文件
```lua
flag = LoadMusic(path)
```
**参数**

+ ***[string] path***：音乐文件路径

**返回值**

+ ***[userdata-MUSIC] flag***：成功则返回音乐数据，失败则返回nil

**示例**

> ## UnloadMusic
释放已加载的音乐
```lua
UnloadMusic(flag)
```
**参数**

+ ***[userdata-MUSIC] flag***：音乐数据

**返回值**

无

**示例**

> ## PlayMusic
播放已加载的音乐
```lua
PlayMusic(flag，loops)
```
**参数**

+ ***[userdata-MUSIC] flag***：音乐数据
+ ***[number] loops***：音乐播放的次数（-1为循环播放）

**返回值**

无

**示例**

> ## FadeInMusic
使用淡入效果播放已加载的音乐
```lua
FadeInMusic(flag，loops, ms)
```
**参数**

+ ***[userdata-MUSIC] flag***：成功则返回音乐数据，失败则返回nil
+ ***[number] loops***：音乐播放的次数（-1为循环播放）
+ ***[number] ms***：淡入音效持续时间，单位为毫秒

**返回值**

无

**示例**

> ## FadeOutMusic
使用淡出效果停止正在播放的音乐
```lua
FadeOutMusic(ms)
```
**参数**

+ ***[number] ms***：淡出音效持续时间，单位为毫秒

**返回值**

无

**示例**

> ## SetMusicVolume
设置音乐播放的音量
```lua
SetMusicVolume(value)
```
**参数**

+ ***[number] value***：音量大小，取值范围为 0-128

**返回值**

无

**示例**

> ## GetMusicVolume
获取当前音乐播放的音量
```lua
value = GetMusicVolume()
```
**参数**

无

**返回值**

+ ***[number] value***：音量大小，取值范围为 0-128

**示例**

> ## PauseMusic
暂停当前正在播放的音乐
```lua
PauseMusic()
```
**参数**

无

**返回值**

无

**示例**

> ## ResumeMusic
恢复当前暂停状态的音乐
```lua
ResumeMusic()
```
**参数**

无

**返回值**

无

**示例**

> ## RewindMusic
重新播放当前正在播放的音乐
```lua
RewindMusic()
```
**参数**

无

**返回值**

无

**示例**

> ## GetMusicType
获取指定音乐的类型
```lua
typeName = GetMusicType(flag)
```
**参数**

+ ***[userdata-MUSIC] flag***：音乐数据（nil表示正在播放的音乐）

**返回值**

+ ***[MACRO number] typeName***：音乐类型


**示例**

> ## LoadSound
加载音效文件
```lua
flag = LoadSound(flag)
```
**参数**

+ ***[string] path***：音效文件路径

**返回值**

+ ***[userdata-SOUND] flag***：成功则返回音效数据，失败则返回nil

**示例**

> ## UnloadSound
释放已加载的音效
```lua
UnloadSound(flag)
```
**参数**

+ ***[userdata-SOUND] flag***：音效数据

**返回值**

无

**示例**

> ## PlaySound
播放已加载的音效
```lua
PlaySound(flag, loops)
```
**参数**

+ ***[userdata-SOUND] flag***：音效数据
+ ***[number] loops***：音乐播放的次数（-1为循环播放）

**返回值**

无

**示例**
