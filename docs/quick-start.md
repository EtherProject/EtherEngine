# EtherAPI 快速入门

EtherAPI 由一套轻量级的 Lua 游戏开发接口，它基于许多 C/C++ 的开源项目发展而来，供游戏开发者快速搭建游戏原型或进行各种概念性测试；同样，它也支持各类游戏（当前版本仅支持 2D 游戏）的开发和发布版本的制作。  

这里是 EtherAPI 的快速入门指南，其目的是帮助您能够快速上手使用该接口库；故本文档只会对常用的接口内容进行介绍，许多重要的功能只会简单的介绍甚至未能提及。有关更多完整信息，您应阅读 [EtherAPI 完整手册](index.md)。

## 启动  

默认状态下，EtherAPI 启动器将自动加载同一目录下的 `Main.lua` 文件作为入口文件，虽然我们建议使用 `Main.lua` 作为入口文件的名称，但是文件名并不是大小写敏感的，如 `main.lua` 甚至是 `mAIn.lua` 都是合法的。

另外，所有使用相对路径引用的模块，都将以启动器所在根目录为根目录，如 `moudle = require("mods/moudle_name")` 只有当在启动器所在目录下存在 `mods` 文件夹且文件夹中存在名为 `moudle_name` 的 Lua 模块文件时才会执行成功。当然，通过修改 `package.path` 或 `package.cpath` 来自定义模块加载路径的方法同样有效。

## 引入模块

为了方便命名空间管理及优化引擎自动速度，我们将是否启用指定模块的权限交付给了开发者，开发者可以通过 `UsingMoudle()` 函数启用指定名称的模块，支持的模块名称参数见 [完整手册：目录](index.md#目录)，特殊的，传入字符串 `All` 表示引擎将启用全部模块，在测试时可以通过此方式避免冗杂的导包代码，除此以外，除非这些模块所包含的API都将在程序内被需要，我们不建议您这样做。  

与 Lua 的标准库函数 `require()` 不同的是，函数 `UsingMoudle()` 并不会将 table 类型的模块作为返回值返回，而是将制定模块中包含的函数压入全局空间，其自身的返回值为 `nil` 。需要注意的是，在 EtherAPI 3.0.x 以下所支持 `UsingMoudle()` 函数的版本中，引入模块会将模块所包含的宏一同引入全局空间，而 EtherAPI 3.0.x 及以上版本中，`UsingMoudle()` 函数会将宏放入与模块名相同的全局 table 中，相关的差异性示例代码如下：

```lua
-- 3.0.x 以下版本

UsingMoudle("Window")

CreateWindow(
    "HelloWorld",
    {x = 0, y = 0, w = 1280, h = 720},
    {WINDOW_RESIZABLE, WINDOW_MAXIMIZED}
)

-- 3.0.x 及以上版本

UsingMoudle("Window")

CreateWindow(
    "HelloWorld",
    {x = 0, y = 0, w = 1280, h = 720},
    {Window.WINDOW_RESIZABLE, Window.WINDOW_MAXIMIZED}
)

```

EtherAPI 中的 `宏` 在本质上为 number 类型的变量，常用作函数参数用来代表指定含义的标志。

## 创建窗口

`Window` 模块中的 API `CreateWindow()` 可以帮助我们很轻松地创建游戏窗口，并把这个窗口作为后续绘图和渲染的上下文。

`CreateWindow()` 函数接受三个参数用作初始化窗口属性：  
+ 第一个参数为 string 类型的窗口标题  
+ 第二个参数为 table 类型的矩形结构体，用以描述窗口的位置和大小
+ 第三个参数为 table 类型的窗口标识，用以描述窗口的样式等元信息  

这里我们提到了 `矩形结构体` 这个概念，类似的还有 `点结构体`、`RGBA 色彩空间结构体` 和 `HSLA 色彩空间结构体`，他们的本质是包含特定键值的 table 变量，如在 `矩形结构体` 中，需要包含的键有 `x`、`y`、`w` 和 `h`，分别用以表示某个矩形区域的坐标（左上角顶点位置）和尺寸，而 `点结构体` 则只需要包含 `x` 和 `y` 两个键值即可，更多的内容见 [完整手册：附录](index.md#附录)。

所以，创建一个标题为 `HelloWorld` 并且显示在默认位置的可拉伸窗口便可以写为如下代码：

```lua
UsingMoudle("Window")

CreateWindow(
    "HelloWorld",
    {
        x = Window.WINDOW_POSITION_DEFAULT, 
        y = Window.WINDOW_POSITION_DEFAULT, 
        w = 1280, 
        h = 720
    },
    {
        Window.WINDOW_RESIZABLE,
        Window.WINDOW_MAXIMIZED
    }
)
```

当然，由于 EtherAPI 并没有提供游戏的主循环，所以如果在创建窗口后进行其他操作，程序退出后窗口将自动关闭，你可以通过 [事件循环](#事件交互) 阻止窗口退出，这同样是在游戏开发过程中普遍使用的方式。

## 图像渲染

`Graphic` 模块

## 事件交互