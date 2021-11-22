### [[ << 回到上层 ]](README.md)

# CopyRotateTexture

> 将旋转后的纹理拷贝至渲染缓冲区内

```lua

CopyRotateTexture(texture, angle, center, mode, rect)

```

## 参数：

+ texture [userdata-Texture]：纹理数据
+ angle [number]：旋转角度
+ center [table]：旋转中心坐标
+ mode [table]：旋转模式，成员可以为以下旋转模式中的一种或多种：

    + FLIP_HORIZONTAL：水平翻转
    + FLIP_VERTICAL：垂直翻转
    + FLIP_NONE：无翻转
    
+ rect [table]：用以描述显示区域的矩形

## 返回值：

无

## 示例

```lua

```