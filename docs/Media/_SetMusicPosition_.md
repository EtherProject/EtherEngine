### [[ << 回到上层 ]](README.md)

# SetMusicPosition

> 设置音乐播放的音量

```lua

SetMusicPosition(position)

```

## 参数：

+ position [number]：播放位置

## 返回值：

无

## 备注

+ 此操作仅支持以下三种格式的音乐，且参数意义各不相同：
    + MOD：设置当前播放位置为此编码模型中对应索引的数据块处，0 将跳转至音乐开头
    + OGG：设置当前播放位置为从音乐开始位置计算的指定秒数处
    + MP3：设置当前播放位置为从当前播放位置计算的指定秒数处，可以先使用 [RewindMusic](_RewindMusic_) 将当前音乐的播放位置重置到开始处

## 示例

```lua

```