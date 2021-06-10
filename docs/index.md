# EtherEngine 开发者文档

## 模块索引

+ [Window](Window/index.md)：窗口相关操作

+ [Graphic](Graphic/index.md)：图形相关操作

+ [Interactivity](Interactivity/index.md)：交互相关操作

+ [Media](Media/index.md)：媒体相关操作

+ [Network](Network/index.md)：网络相关操作

+ [OS](OS/index.md)：操作系统相关操作

+ [Algorithm](Algorithm/index.md)：算法相关操作

+ [String](String/index.md)：字符串相关操作

+ [JSON](JSON/index.md)：JSON 数据格式相关操作

+ [Time](Time/index.md)：时间相关操作

+ [Compress](Compress/index.md)：压缩和解压缩相关操作

## 全局函数

+ UsingModule(name)

    + 功能：启用指定内置模块或加载外部模块
    + 参数：模块名（`string`）
    + 返回值：模块内容（`table`）

+ GetVersion()

    + 功能：获取当前引擎版本号
    + 参数：无
    + 返回值：当前引擎版本号（`string`）

## 启动配置

引擎启动时将默认加载同一目录下的 `config.json` 作为配置文件

一个完整的配置文件结构如下：

```json
{
    "entry": "",
    "package": {
        "path": [
          
        ],
        "cpath": [

        ]
    },
    "command": [
        
    ]
}
```

+ `entry` 属性指定入口文件，支持引擎目录为根目录的相对路径
+ `package` 属性配置额外的模块路径，字符串数组中填写的值将被追加到引擎环境的 `package` 属性中
+ `command` 属性为引擎启动添加额外启动参数，字符串数组中填写的值将会被添加到 `_argv` 全局表的头部，同时会修改 `_argc` 全局变量

如果 `config.json` 文件不存在或解析错误，引擎将使用默认配置启动，默认配置下引擎无附加模块目录及附加启动参数，并将同一目录下的 `Main.lua` 文件作为入口文件，使用 `_ETHER_DEBUG_` 宏进行编译的引擎会弹出警告信息

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
