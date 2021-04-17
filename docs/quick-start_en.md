# Good Journey Quick Start

[简体中文](quick-start.md) | English | [日本語](quick-start_ja.md)

Welcome to EtherAPI (for EtherEngine). EtherAPI consists of a set of lightweight Lua game development interfaces developed based on many C/C++ open source projects for game developers to quickly build game prototypes or conduct various conceptual tests. similarly, it also supports various games (The current version only supports 2D games) in development and production environments.

Here is a quick start guide for EtherAPI, its purpose is to help you quickly get started using the interface library; therefore, this document will only introduce the content of commonly used interfaces, and many important functions will only be briefly introduced or even not mentioned. For more complete information, you should read [Full EtherAPI Manual](index.md).

---

## Launching

The EtherAPI launcher will automatically load the `Main.lua` file in the current directory as the entry file as default. Although we recommend using `Main.lua` as the entry file, the file name is not case sensitive, such as `main.lua` and even `mAIn.lua` are both legal.

In addition, all modules referenced by relative paths will use the root directory of the launcher as the root directory, such as `moudle = require("mods/moudle_name")` only when the `mods` folder exists in the directory where the launcher is located and The execution will be successful only when there is a Lua module file named `moudle_name` in the folder. Of course, the method of customizing the module loading path by modifying `package.path` or `package.cpath` is also effective.