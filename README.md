## EtherEngine
[![](https://img.shields.io/github/stars/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/EtherEngine/stargazers)  [![](https://img.shields.io/github/forks/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/EtherEngine/network/members)  [![](https://img.shields.io/github/issues/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/EtherEngine/issues)  ![](https://img.shields.io/github/license/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&label=license&message=notspecified&labelColor=3f48cc)
> ~~更简单~~更专业的游戏引擎

## 启动引擎：

**<font color=#DC143C size=4> 引擎默认将相同目录的 `Main.lua` 文件作为入口点文件 </font>**

## 跳转到指定模块API列表：

+ [Algorithm](.docs/Algorithm/index.md)：算法相关API

+ [Graphic](.docs/Graphic/index.md)：图形相关API

+ [Interactivity](.docs/Interactivity/index.md)：交互相关API

+ [Media](.docs/Media/index.md)：媒体相关API

+ [Network](.docs/Network/index.md)：网络相关API

+ [OS](.docs/OS/index.md)：操作系统相关API

+ [String](.docs/String/index.md)：字符串相关API

+ [Time](.docs/Time/index.md)：时间相关API

+ [Window](.docs/Window/index.md)：窗口相关API

## 其他API：

+ UsingMoudle(name)

    + 功能：启用指定模块
    + 参数：模块名，传入字符串 "All" 表示启用所有模块
    + 返回值：无

+ GetVersion()

    + 功能：获取当前引擎版本号
    + 参数：无
    + 返回值：当前引擎版本号

## 附录：

> 常用表结构内部成员简介

+ 矩形：

    + x [number]：矩形左上角顶点x坐标
    + y [number]：矩形左上角顶点y坐标
    + w [number]：矩形宽度
    + h [number]：矩形高度

+ 点：

    + x [number]：点x坐标
    + y [number]：点y坐标

+ 颜色：

    + RGBA 颜色空间：

        + r [number]：颜色的红色分量
        + g [number]：颜色的绿色分量
        + b [number]：颜色的蓝色分量
        + a [number]：颜色的透明度

    + HSLA 颜色空间：
        
        + h [number]：颜色的色相
        + s [number]：颜色的饱和度
        + l [number]：颜色的亮度
        + a [number]：颜色的透明度

## 联系开发组

如果在使用过程中出现任何问题或有任何建议，请直接在本仓库中提交issue。

也欢迎您直接发送邮件至Voidmatrix@qq.com

## 投递作品

我们十分欢迎您将自己的作品投递到 [EtherEngine 作品集](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection) 仓库下！
