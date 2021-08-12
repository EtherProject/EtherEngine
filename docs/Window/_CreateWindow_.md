### [[ << 回到上层 ]](README.md)

# CreateWindow

> 创建窗口，并将此窗口作为图形绘制等操作的上下文

```lua

CreateWindow(title, rect, attributes)

```

## 参数：

+ title [string]：窗口标题
+ rect [table]：用以描述显示区域的矩形，其中 x 和 y 成员可以取值 WINDOW_POSITION_DEFAULT 表示窗口显示在默认位置
+ attributes [table]：用以描述窗口属性的表，成员可以为以下属性中的一种或多种：

    + WINDOW_FULLSCREEN：全屏（视频输出模式更改的真全屏）
    + WINDOW_FULLSCREEN_DESKTOP：全屏（将窗口拉伸至屏幕分辨率大小的伪全屏）
    + WINDOW_BORDERLESS：无边框
    + WINDOW_RESIZABLE：大小可变
    + WINDOW_MAXIMIZED：最大化
    + WINDOW_MINIMIZED：最小化

## 返回值：

无

## 示例

```lua

```