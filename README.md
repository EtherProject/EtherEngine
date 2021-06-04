# EtherEngine
[![](https://img.shields.io/github/stars/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=e49e61)](https://github.com/VoidmatrixHeathcliff/EtherEngine/stargazers)
[![](https://img.shields.io/github/forks/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=e49e61)](https://github.com/VoidmatrixHeathcliff/EtherEngine/network/members)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b2761c92b96e4125a5dbc9d681c54cf4)](https://www.codacy.com/gh/VoidmatrixHeathcliff/EtherEngine/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=VoidmatrixHeathcliff/EtherEngine&amp;utm_campaign=Badge_Grade)
[![](https://img.shields.io/github/contributors/VoidmatrixHeathcliff/EtherEngine)](https://github.com/VoidmatrixHeathcliff/EtherEngine/graphs/contributors)
![](https://img.shields.io/github/commit-activity/m/VoidmatrixHeathcliff/EtherEngine)

**EtherEngine** 旨在提供一套跨平台的 Lua 接口，供游戏开发使用（当前版本仅支持 2D 游戏），功能涵盖 **图形、媒体、交互、网络** 等方面，目前仍在不断开发和完善中；API 在设计过程中首先考虑的是 **简洁** 和 **易用性**，**EtherEngine** 可以帮你快速建立起几乎所有类型游戏的演示框架甚至是一个已经可以直接发布的游戏。如果您对本项目感兴趣，欢迎为项目贡献代码或留下您的使用建议，记得点亮右上角的小星星哦 ~  

**EtherEngine** aims to provide a set of cross platform Lua interface for game development (the current version only supports 2D games), with functions covering **graphics, media, interactivity, network**, etc. , which is still under development and improvement; In the process of API design, the first consideration is **SIMPLICITY** and **EASE OF USE**, **EtherEngine** can help you quickly build a demo framework for almost all types of games, even a game that can be released directly. If you are interested in this project, you are welcome to contribute code to the project or leave your suggestions. Remember to light up the little star in the upper right corner ~

## 本地编译 · Building

### Windows 平台 · Windows Platform

EtherEngine 使用 [vcpkg](https://github.com/microsoft/vcpkg) 作为自动构建工具，请确保您的设备上已安装 [vcpkg](https://github.com/microsoft/vcpkg) 并配置完全，使用 [VisualStudio](https://visualstudio.microsoft.com/) 打开 `msbuild` 目录下的 `EtherEngine.sln` 工程文件即可进行项目自动化配置及编译。

EtherEngine uses [vcpkg](https://github.com/microsoft/vcpkg) as an automatic build tool, make sure [vcpkg](https://github.com/microsoft/vcpkg) is installed on your device, and the configuration is complete, using [VisualStudio](https://visualstudio.microsoft.com/) open the `EtherEngine.sln` project file under the `msbuild` directory to configure and compile the project automatically.

`OptimizedDebug` 模式将启用 `_ETHER_DEBUG_` 宏进行编译，关于 `_ETHER_DEBUG_` 宏的更多内容见下方描述。

`OptimizedDebug` mode will be enabled `_ETHER_DEBUG_` macro to compile, more about the `_ETHER_DEBUG_` macro is described below.

### 其他平台 · Other Platforms

由于 EtherEngine 基于 SDL 和 Lua 等库实现，所以您可能需要先本地编译相关的库进行支持。
您可以在以下网址处找到这些依赖适合您所使用的平台的发布版本或源码： 

Since EtherEngine is implemented based on SDL, Lua and other libraries, you may need to compile the relevant libraries for support first.
You can find the release version or source code of these dependencies for the platform you are using at the following address:   

|库名称|网址|协议|
|----|----|----|
|**Lua - 5.4.0**|[http://www.lua.org/](http://www.lua.org/)  | MIT |
|**SDL - 2.0.14**|[https://www.libsdl.org/](https://www.libsdl.org/)  | zlib license |
|**SDL_image - 2.0.5**|[https://www.libsdl.org/projects/SDL_image/](https://www.libsdl.org/projects/SDL_image/)  | zlib license |
|**SDL_gfx - 1.0.4**|[https://sourceforge.net/projects/sdlgfx/](https://sourceforge.net/projects/sdlgfx/)  | zlib/libpng License |
|**SDL_mixer - 2.0.4**|[https://www.libsdl.org/projects/SDL_mixer/](https://www.libsdl.org/projects/SDL_mixer/)  | zlib license |
|**SDL_ttf - 2.0.15**|[https://www.libsdl.org/projects/SDL_ttf/](https://www.libsdl.org/projects/SDL_ttf/)  | zlib license |
|**cpp-httplib - 0.8.4**|[https://github.com/yhirose/cpp-httplib/](https://github.com/yhirose/cpp-httplib/)  | MIT |
|**cJSON - 1.7.14**|[https://github.com/DaveGamble/cJSON](https://github.com/DaveGamble/cJSON/)  | MIT |
|**zlib - 1.2.11**|[http://www.zlib.net/](http://www.zlib.net/)  | zlib license in ```zlib.h``` |
|**openssl - 1.1.1k**|[https://www.openssl.org/](https://www.openssl.org/)  | "Apache-style license" |
|**pugixml - 1.11.4**|[https://github.com/zeux/pugixml](https://github.com/zeux/pugixml)  | MIT |
|**base64 - 0.4.0**|[https://github.com/aklomp/base64](https://github.com/aklomp/base64)  | BSD-2-Clause License |

然后将 `src` 文件夹内的所有源码文件添加到您的工程并进行编译，即可得到适合您当前开发平台的 EtherEngine 启动器。

### 条件编译 · Conditional Compilation

您可以在 `Macros.h` 文件中定义宏或添加编译指令 `_ETHER_DEBUG_` 来开启 Debug 模式；在 Debug 模式下，EtherEngine 将对参数进行严格的类型检查，来确保严谨正确的程序逻辑，同时，在 Windows 平台下，此模式将意味着程序所使用的子系统为 `console` 而非 `window` ，程序将显示控制台，通过 `print()` 等操作输出的调试信息不会被隐藏。

You can define macros in the `Macros.h` file or add compilation instructions `_ETHER_DEBUG_` to open debug mode; In debug mode, EtherEngine will conduct strict type checking on parameters to ensure rigorous and correct program logic. At the same time, in Windows platform, this mode means that the subsystem used by the program is `console` instead of `window`. The program will display the console, and the debugging information output through such as `print()` will not be hidden

## 文档 · Documentation：

当前发布的 EtherEngine 提供两个版本的开发者文档： 

There are two versions of the developer's documentation for the currently released EtherEngine:

+ [快速开始](docs/quick-start.md)：在这里您可以快速上手 EtherEngine ，文档将演示如 **窗口建立、按键交互、图像渲染、音乐播放** 等内容。  
+ [QuickStart](docs/quick-start_en.md): Here you can quickly start the EtherEngine, and the document will demonstrate the contents such as **window startup, key interaction, image rendering, music playback** and so on.

+ [完全参考手册](docs/index.md)：这里将包含 EtherEngine 的全部内容和详细介绍。  
+ [CompleteReferenceManual](docs/index.md): Here will contain all the contents and detailed introduction of EtherEngine.

我们建议您从 `快速开始` 开始接触 EtherEngine ，其中包含的实例将极大地减少您上手开发时的难度；尽管如此，`快速开始` 部分并不会对 EtherEngine 的全部内容进行详尽的介绍，所展示的内容也可能仅仅是您所需要的一部分，阅读 `完全参考手册` 来获取更多内容。

We suggest that you start to contact the EtherEngine from the `QuickStart`, and the examples contained in it will greatly reduce the difficulty when you start the development. However, the `QuickStart` section will not give a detailed introduction to all the contents of the EtherEngine, and the contents displayed may only be part of what you need. Read the `CompleteReferenceManual` for more information.

## 特别鸣谢 · Special Thanks

+ [Fa鸽](https://github.com/Akarinnnnn)：感谢技术高超的大佬，为项目的自动化构建无私地付出了大量精力，提供了极其关键的重构
+ [HandamardMatrix](https://github.com/HandamardMatrix)：感谢我的小可爱，为引擎算法提供灵感并且陪我度过了最寒冷的冬天
+ [LHR1926](https://github.com/LHR1926)：感谢我的战友，为引擎的第一份 API 文档做出贡献
+ [VisualDust](https://github.com/VisualDust)：感谢素未谋面的大佬，能够在百忙之中为引擎文档提供英文译本

+ [Fa鸽](https://github.com/Akarinnnnn)：Thanks to the highly skilled mogul, who selflessly paid a lot of energy for the automatic construction of the project and provided the extremely critical reconstruction
+ [HandamardMatrix](https://github.com/HandamardMatrix)：Thank my sweet for providing inspiration for engine algorithm and accompanying me through the coldest winter
+ [LHR1926](https://github.com/LHR1926)：Thank my comrades in arms for contributing to the first version of API document of the engine
+ [VisualDust](https://github.com/VisualDust)：Thank the mogul we haven't met before for providing English translation for engine documents in your busy time

## 联系开发组 · Contact Me

如果在使用过程中出现任何问题或有任何建议，欢迎在本仓库中提交 issue 或直接发送邮件至 Voidmatrix@qq.com

If there are any problems or suggestions during use, please submit issue in our depository or send email to Voidmatrix@qq.com directly.

## 投递作品 · Delivery Your Works

我们十分欢迎您将自己的作品投递到 [EtherEngine 作品集](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection) 仓库下！  
关于投递规范和协议等更多内容详见 [此处](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection/blob/main/README.md)。

We welcome you to send your works to the depository of [EtherWorkCollection](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection)!  
Please refer to [HERE](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection/blob/main/README.md) for more details about delivery specifications and licenses.
