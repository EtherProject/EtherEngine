### [[ << 回到上层 ]](index.md)

# Music:GetType

> 获取音乐的类型

```lua

type = music:GetMusicType()

```

## 参数：

+ music [userdata-Music]：音乐数据，nil表示正在播放的音乐

## 返回值：

+ type [MACRO number]：音乐类型，可能的类型如下：

    + MUSIC_TYPE_WAV：WAV类型
    + MUSIC_TYPE_MP3：MP3类型
    + MUSIC_TYPE_OGG：OGG类型
    + MUSIC_TYPE_CMD：CMD类型
    + MUSIC_TYPE_MOD：MOD类型
    + MUSIC_TYPE_MID：MID类型
    + MUSIC_TYPE_UNKONWN：未知格式

## 示例

```lua

```