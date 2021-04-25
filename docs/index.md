# EtherEngine 开发者文档

## 目录

+ [Algorithm](Algorithm/index.md)：算法相关API

+ [Graphic](Graphic/index.md)：图形相关API

+ [Interactivity](Interactivity/index.md)：交互相关API

+ [Media](Media/index.md)：媒体相关API

+ [Network](Network/index.md)：网络相关API

+ [OS](OS/index.md)：操作系统相关API

+ [String](String/index.md)：字符串相关API

+ [JSON](JSON/index.md)：JSON 格式数据相关API

+ [Time](Time/index.md)：时间相关API

+ [Window](Window/index.md)：窗口相关API

## 全局 API

+ UsingModule(name)

    + 功能：启用指定模块
    + 参数：模块名，传入字符串 "All" 表示启用所有模块
    + 返回值：无

+ GetVersion()

    + 功能：获取当前引擎版本号
    + 参数：无
    + 返回值：当前引擎版本号

## 附录

> 常用结构体内部成员简介

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

> 启动参数及环境变量

+ `_argc`

    + 类型：number
    + 描述：启动器参数个数

+ `_argv`

    + 类型：table
    + 描述：启动器参数列表

+ `_envp`

    + 类型：table
    + 描述：启动器环境变量键值表