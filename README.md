# EtherAPI
[![](https://img.shields.io/github/stars/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=e49e61)](https://github.com/VoidmatrixHeathcliff/EtherEngine/stargazers)
[![](https://img.shields.io/github/forks/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&labelColor=e49e61)](https://github.com/VoidmatrixHeathcliff/EtherEngine/network/members)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b2761c92b96e4125a5dbc9d681c54cf4)](https://www.codacy.com/gh/VoidmatrixHeathcliff/EtherEngine/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=VoidmatrixHeathcliff/EtherEngine&amp;utm_campaign=Badge_Grade)
[![](https://img.shields.io/github/license/VoidmatrixHeathcliff/EtherEngine.svg?style=flat&label=license&message=notspecified&labelColor=3f48cc)](https://github.com/VoidmatrixHeathcliff/EtherEngine/blob/main/LICENSE)
[![](https://img.shields.io/github/contributors/VoidmatrixHeathcliff/EtherEngine)](https://github.com/VoidmatrixHeathcliff/EtherEngine/graphs/contributors)
![](https://img.shields.io/github/commit-activity/m/VoidmatrixHeathcliff/EtherEngine)

本项目由 EtherEngine 更名为 **EtherAPI**，旨在提供一套跨平台的 Lua 接口，供游戏开发使用（当前版本仅支持 2D 游戏），功能涵盖 **图形、声音、交互、网络** 等方面，目前仍在不断开发和完善中；API 在设计过程中首先考虑的是 **简洁** 和 **易用性**，所以对于性能要求较高的游戏，EtherAPI 或许并不是一个最好的选择；但是在对于性能并不敏感的应用场景（如游戏原型的设计），EtherAPI 可以帮你快速建立起几乎所有类型游戏的演示框架甚至是一个已经可以直接发布的游戏。如果您对本项目感兴趣，欢迎为项目贡献代码或留下您的使用建议，记得点亮右上角的小星星哦 ~  

This project is renamed as **EtherAPI** from EtherEngine, which aims to provide a set of cross platform Lua interface for game development (the current version only supports 2D games), with functions covering **graphics, sound, media, interaction, network** and other aspects, and is still under continuous development and improvement; the first consideration in the design process of API is **SIMPLICITY** and **EASE OF USE**, so EtherAPI may not be the best choice for games with high performance requirements. However, in application scenarios that are not sensitive to performance (such as the design of game prototypes), EtherAPI can help you quickly build up the performance framework of almost all kinds of games, even a game that can be released directly. If you are interested in this project, you are welcome to contribute code to the project or leave your suggestions. Remember to light up the little star in the upper right corner~

## 本地编译 · Building

由于 EtherAPI 基于 SDL 和 Lua 等库实现，所以您可能需要先本地编译相关的库进行支持。  
您可以在以下网址处找到这些依赖适合您所使用的平台的发布版本或源码： 

Since EtherAPI is implemented based on SDL, Lua and other libraries, you may need to compile the relevant libraries for support first.
You can find the release version or source code of these dependencies for the platform you are using at the following address:   

+ **Lua - 5.4.0：**[http://www.lua.org/](http://www.lua.org/)
+ **SDL - 2.0.14：**[https://www.libsdl.org/](https://www.libsdl.org/)  
+ **SDL_image - 2.0.5：**[https://www.libsdl.org/projects/SDL_image/](https://www.libsdl.org/projects/SDL_image/) 
+ **SDL_gfx - 1.0.4：**[https://sourceforge.net/projects/sdlgfx/](https://sourceforge.net/projects/sdlgfx/) 
+ **SDL_mixer - 2.0.4：**[https://www.libsdl.org/projects/SDL_mixer/](https://www.libsdl.org/projects/SDL_mixer/) 
+ **SDL_ttf - 2.0.15：**[https://www.libsdl.org/projects/SDL_ttf/](https://www.libsdl.org/projects/SDL_ttf/) 
+ **cpp-httplib - 0.8.4：**[https://github.com/yhirose/cpp-httplib/](https://github.com/yhirose/cpp-httplib/) 
+ **cJSON - 1.7.14：**[https://github.com/DaveGamble/cJSON](https://github.com/DaveGamble/cJSON/) 
+ **zlib - 1.2.11：**[http://www.zlib.net/](http://www.zlib.net/) 
+ **openssl - 1.1.1k：**[https://www.openssl.org/](https://www.openssl.org/) 

然后将 `src` 文件夹内的所有源码文件添加到您的工程并进行编译，即可得到适合您当前开发平台的 EtherAPI 启动器，它将加载同一目录下的 `config.json` 作为配置文件，配置文件中描述了入口文件和附加模块路径等多种信息。  
另外，您可以在 `Macros.h` 文件中决定是否禁用 `_ETHER_DEBUG_` 宏来开启 Release 模式；在 Release 模式下，EtherAPI 将跳过部分严格的类型检查，来确保更加高效的运行，同时，在 Windows 平台下，此模式将意味着程序所使用的子系统为 `window` 而非 `console` ，程序将不会显示控制台，通过 `print()` 等操作输出的调试信息可能会被隐藏。

Then add all source files in the `src` folder to your project and compile them to get the Ethernet API loader suitable for your current development platform, it will load `config.json` in the same directory as the configuration file, which describes the entry file, add-on module path and other information.
In addition, you can decide whether to disable `_ETHER_DEBUG_` Macro in the `macro.h` file to open release mode; in release mode, etherapi will skip some strict type check to ensure more efficient operation. Meanwhile, under Windows platform, this mode will mean that the subsystem used by the program is `window` instead of `console`. The program will not show the console. Debugging information output through operation such as `print()` may be hidden.

## 文档 · Documentation：

当前发布的 EtherAPI 提供两个版本的开发者文档： 

There are two versions of the developer's documentation for the currently released EtherAPI:

+ [快速开始](docs/quick-start.md)：在这里您可以快速上手 EtherAPI ，文档将演示如 **窗口建立、按键交互、图像渲染、音乐播放** 等内容。  
+ [QuickStart](docs/quick-start_en.md): Here you can quickly start the EtherAPI, and the document will demonstrate the contents such as **window startup, key interaction, image rendering, music playback** and so on.

+ [完全参考手册](docs/index.md)：这里将包含 EtherAPI 的全部内容和详细介绍。  
+ [CompleteReferenceManual](docs/index.md): Here will contain all the contents and detailed introduction of EtherAPI.

我们建议您从 `快速开始` 开始接触 EtherAPI ，其中包含的实例将极大地减少您上手开发时的难度；尽管如此，`快速开始` 部分并不会对 EtherAPI 的全部内容进行详尽的介绍，所展示的内容也可能仅仅是您所需要的一部分，阅读 `完全参考手册` 来获取更多内容。

We suggest that you start to contact the EtherAPI from the `QuickStart`, and the examples contained in it will greatly reduce the difficulty when you start the development. However, the `QuickStart` section will not give a detailed introduction to all the contents of the EtherAPI, and the contents displayed may only be part of what you need. Read the `CompleteReferenceManual` for more information.

## 特别鸣谢 · Special Thanks

+ [HandamardMatrix](https://github.com/HandamardMatrix)：感谢我的小可爱，为引擎算法提供灵感并且陪我度过了最寒冷的冬天
+ [LHR1926](https://github.com/LHR1926)：感谢我的战友，为引擎的第一份 API 文档做出贡献
+ [VisualDust](https://github.com/VisualDust)：感谢素未谋面的大佬，能够在百忙之中为引擎文档提供英文译本

+ [HandamardMatrix](https://github.com/HandamardMatrix)：Thank my sweet for providing inspiration for engine algorithm and accompanying me through the coldest winter
+ [LHR1926](https://github.com/LHR1926)：Thank my comrades in arms for contributing to the first version of API document of the engine
+ [VisualDust](https://github.com/VisualDust)：Thank the mogul we haven't met before for providing English translation for engine documents in your busy time

## 联系开发组 · Contact Me

如果在使用过程中出现任何问题或有任何建议，欢迎在本仓库中提交 issue 或直接发送邮件至 Voidmatrix@qq.com

If there are any problems or suggestions during use, please submit issue in our depository or send email to Voidmatrix@qq.com directly.

## 投递作品 · Delivery Your Works

我们十分欢迎您将自己的作品投递到 [EtherAPI 作品集](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection) 仓库下！  
关于投递规范和协议等更多内容详见 [此处](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection/blob/main/README.md)。

We welcome you to send your works to the depository of [EtherWorkCollection](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection)!  
Please refer to [HERE](https://github.com/VoidmatrixHeathcliff/EtherWorkCollection/blob/main/README.md) for more details about delivery specifications and licenses.
