### [[ << 回到上层 ]](index.md)

# CreateTextImageShaded

> 使用Shaded模式创建文本图像

```lua

image = CreateTextImageShaded(font, text, fgColor, bgColor)

```

## 参数：

+ font [userdata-FONT]：字体数据
+ text [string]：文本内容
+ fgColor [table]：用以描述文本颜色的RGBA表，各分量取值范围均为0-255
+ bgColor [table]：用以描述文本背景颜色的RGBA表，各分量取值范围均为0-255

## 返回值：

+ image [userdata-IMAGE]：成功则返回图像数据，失败则返回nil

## 示例

```lua

```