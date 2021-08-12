### [[ << 回到主页 ]](../README.md)

# Media

> Media 模块提供媒体相关操作

## 模块函数列表：

+ [LoadMusic(path)](_LoadMusic_.md)：加载音乐文件

+ [PlayMusic(music, times)](_PlayMusic_.md)：播放已加载的音乐

+ [PlayMusicWithFadeIn(music, times, delay)](_PlayMusicWithFadeIn_.md)：使用淡入效果播放已加载的音乐

+ [StopMusic()](_StopMusic_.md)：停止正在播放的音乐

+ [StopMusicWithFadeOut(delay)](_StopMusicWithFadeOut_.md)：使用淡出效果停止正在播放的音乐

+ [SetMusicVolume(value)](_SetMusicVolume_.md)：设置音乐播放的音量

+ [SetMusicPosition(position)](_SetMusicPosition_.md)：设置当音乐的播放位置

+ [GetMusicVolume()](_GetMusicVolume_.md)：获取当前音乐播放的音量

+ [PauseMusic()](_PauseMusic_.md)：暂停当前正在播放的音乐

+ [ResumeMusic()](_ResumeMusic_.md)：恢复当前暂停状态的音乐

+ [RewindMusic()](_RewindMusic_.md)：重新播放当前正在播放的音乐

+ [CheckMusicPlaying()](_CheckMusicPlaying_.md)：判断当前音乐是否正在播放

+ [CheckMusicPaused()](_CheckMusicPaused_.md)：判断当前音乐是否已暂停

+ [GetMusicFadingType()](_GetMusicFadingType_.md)：获取当前正在播放的音乐的淡化效果类型

+ [LoadSoundFromFile(path)](_LoadSoundFromFile_.md)：从文件中加载音效

+ [LoadSoundFromData(data)](_LoadSoundFromData_.md)：从缓冲区中加载音效

## 对象成员函数列表：

+ Music 对象成员函数：

    + [Music:GetType()](_Music_GetType_.md)：获取音乐的类型

+ Sound 对象成员函数：

    + [Sound:Play(times)](_Sound_Play_.md)：播放已加载的音效

    + [Sound:SetVolume(value)](_Sound_SetVolume_.md)：设置音效播放的音量

    + [Sound:GetVolume()](_Sound_GetVolume_.md)：获取音效播放的音量