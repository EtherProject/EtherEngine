## EtherAPI
[![](https://img.shields.io/github/stars/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=e49e61)](https://github.com/VoidmatrixHeathcliff/EtherEngine/stargazers)  [![](https://img.shields.io/github/forks/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=e49e61)](https://github.com/VoidmatrixHeathcliff/EtherEngine/network/members)  [![](https://img.shields.io/github/issues/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/EtherEngine/issues)  ![](https://img.shields.io/github/license/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&label=license&message=notspecified&labelColor=3f48cc)

本项目由 EtherEngine 更名为 **EtherAPI**，旨在提供一套跨平台的 Lua 接口，供游戏开发使用（目前仅支持 2D 图形），功能涵盖 **图形、声音、媒体、交互、网络** 等方面，目前仍在不断开发和完善中；API 在设计过程中首先考虑的是 **简洁** 和 **易用性**，所以对于性能要求较高的游戏，EtherAPI 或许并不是一个很好的选择；但是在对于性能并不是很敏感的应用场景（如游戏原型的设计），EtherAPI 可以帮你快速建立起几乎所有类型游戏的演示框架甚至是一个已经可以发布的游戏。如果您对本项目感兴趣，欢迎为项目贡献代码或留下您的使用建议，记得点亮右上角的小星星哦 ~  

This project is renamed as **EtherAPI** from EtherEngine, which aims to provide a set of cross platform Lua interface for game development (currently only supports 2D graphics), with functions covering ** graphics, sound, media, interaction, network ** and other aspects, and is still under continuous development and improvement; the first consideration in the design process of API is **SIMPLICITY** and **EASE OF USE**, so EtherAPI may not be a good choice for games with high performance requirements. However, in application scenarios that are not very sensitive to performance (such as the design of game prototypes), etherapi can help you quickly build up the performance framework of almost all kinds of games, even a game that can be released. If you are interested in this project, you are welcome to contribute code to the project or leave your suggestions. Remember to light up the little star in the upper right corner~

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
