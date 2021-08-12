### [[ << 回到上层 ]](README.md)

# GetUTF8TextSize

> 获取UTF-8编码格式的文本尺寸

```lua

width, height = GetUTF8TextSize(font, text)

```

## 参数：

+ font [userdata-Font]：字体数据
+ text [string]：UTF-8编码格式的文本内容

## 返回值：

+ width [number]：文本宽度
+ height [number]：文本高度

## 备注

+ 此函数可以在不渲染文字图像的前提下通过已加载字体大小获取使用该字体渲染后文字图像的尺寸

## 示例

```lua

```