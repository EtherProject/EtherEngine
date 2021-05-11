### [[ << 回到上层 ]](index.md)

# CopyRotateReshapeTexture

> 将旋转且裁剪后的纹理拷贝至渲染缓冲区内

```lua

CopyRotateReshapeTexture(texture, angle, center, mode, shape, rect)

```

## 参数：

+ texture [userdata-Texture]：纹理数据
+ angle [number]：旋转角度
+ center [table]：旋转中心坐标
+ mode [table]：旋转模式，成员可以为以下旋转模式中的一种或多种：

    + FLIP_HORIZONTAL：水平翻转
    + FLIP_VERTICAL：垂直翻转
    + FLIP_NONE：无翻转
    
+ shape [table]：用以描述裁剪区域的矩形
+ rect [table]：用以描述显示区域的矩形

## 返回值：

无

## 示例

```lua

```