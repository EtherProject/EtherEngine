### [[ << 回到上层 ]](index.md)

# LoadFontFromData

> 从缓冲区中加载字体

```lua

font = LoadFontFromData(data, size)

```

## 参数：

+ data [userdata-Font]：缓冲区数据
+ size [number]：字体大小

## 返回值：

+ font [boolean]：成功则返回字体数据，在 `_ETHER_DEBUG_` 模式下失败将触发异常

## 备注

+ 字体大小为在 72DPI 下的字体大小，这通常代表着单位为像素的文本高度

## 示例

```lua

```