### [[ << 回到上层 ]](index.md)

# CreateUTF8TextImageShaded

> 使用Shaded模式创建文本图像

```lua

image = CreateUTF8TextImageShaded(font, text, fgColor, bgColor)

```

## 参数：

+ font [userdata-Font]：字体数据
+ text [string]：UTF-8编码格式的文本内容
+ fgColor [table]：用以描述文本颜色的RGBA表，各分量取值范围均为0-255
+ bgColor [table]：用以描述文本背景颜色的RGBA表，各分量取值范围均为0-255

## 返回值：

+ image [userdata-Image]：成功则返回图像数据，失败则返回nil

## 示例

```lua

```