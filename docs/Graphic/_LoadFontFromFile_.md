### [[ << 回到上层 ]](README.md)

# LoadFontFromFile

> 从文件中加载字体

```lua

font = LoadFontFromFile(path, size)

```

## 参数：

+ path [userdata-Font]：字体文件路径
+ size [number]：字体大小

## 返回值：

+ font [boolean]：成功则返回字体数据，在 `_ETHER_DEBUG_` 模式下失败将触发异常

## 备注

+ 字体大小为在 72DPI 下的字体大小，这通常代表着单位为像素的文本高度

## 示例

```lua

```