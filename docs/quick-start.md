# EtherAPI 快速入门

简体中文 | [English](quick-start_en.md) | [日本語](quick-start_ja.md)

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

`Graphic` 模块提供了与图像渲染相关的操作。需要注意的是，这些操作是基于上述所建立的窗口的，所以如果在未建立窗口的情况下调用部分 API，可能导致引擎报错（Debug 模式下）或出现不可预料的结果（Release 模式下）。  

### 图片渲染

游戏中最常见的操作便是加载并绘制图片，所以 EtherAPI 提供了一套极度简明且高效的接口：

+ 首先，`LoadImage()` 函数负责将图片文件从硬盘加载到内存，其参数是 string 类型的图片文件路径，返回值为 Image 类型的 userdata，若图片在 Debug 模式下加载失败则会导致引擎报错。

+ 然后，通过 `CreateTexture()` 函数将上步返回的 Image 数据渲染为可被显示的纹理数据，并返回 Texture 类型的 userdata，若纹理在 Debug 模式下创建失败则会导致引擎报错。

+ 最后，`CopyTexture()` 函数可以将上步创建的纹理拷贝至渲染缓冲区内，这个函数接受两个参数，分别是 Texture 类型的 userdata 和一个用以描述图片再窗口坐标系中的位置和尺寸的矩形结构体。需要注意的是，`CopyTexture()` 函数仅仅是将纹理数据拷贝到了渲染缓冲区，而并没有真正刷新显示到屏幕上，所以我们需要在接下来的步骤中调用 `Window` 模块中的 `UpdateWindow()` 函数来将渲染缓冲区的内容显示到屏幕上。

也就是说，只需要如下的寥寥几行代码便可以将图片显示出来：

```lua
-- 引入 Window 和 Graphic 模块
UsingMoudle("Window")
UsingMoudle("Graphic")

-- 创建绘图窗口
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

-- 加载 Player.png 图片文件
image = LoadImage("Player.png")

-- 将上步加载的图片数据渲染为纹理数据
texture = CreateTexture(image)

-- 将纹理数据拷贝到渲染缓冲区中
CopyTexture(texture, {x = 0, y = 0, w = 1280, h = 720})

-- 将渲染缓冲区的数据冲刷到窗口上
UpdateWindow()
```

需要明确的是，在窗口坐标系中，坐标系原点位于窗口左上角，水平方向向右为 x 轴正方向，竖直方向向下为 y 轴正方向。

另外，如果需要对图片裁剪或旋绕显示，则只需要在拷贝纹理至渲染缓冲区时调用指定的函数，如：  
+ [`CopyReshapeTexture()`](Graphic/_CopyReshapeTexture_.md) 函数可以将首先对纹理进行裁剪再进行拷贝  
+ [`CopyRotateTexture()`](Graphic/_CopyReshapeTexture_.md) 函数可以将首先对纹理进行旋转再进行拷贝  
+ [`CopyRotateReshapeTexture()`](Graphic/_CopyReshapeTexture_.md) 函数则会将纹理旋转并裁剪后才进行拷贝  

关于这些函数的描述，详见 [完整手册：Graphic 模块](Graphic/index.md)

### 文本渲染

类似的，如果想将文本内容渲染到屏幕上，也需要执行和显示图片相似的步骤，所有需要显示的文本内容最终都需要被渲染为文本纹理才能显示到屏幕上，具体步骤如下：

+ 首先，需要使用 `LoadFont()` 函数将字体文件加载到内存中，函数所需要的第一个参数便是字体文件的路径，由于一个字体文件中可能包含多种不同尺寸的字体，所以必须通过第二个参数指定我们所需要的字体字号索引；与 `LoadImage()` 函数类似，如函数将返回 Font 类型的 userdata，若在 Debug 模式下加载失败则会导致引擎报错。

+ 其次，使用如 `CreateTextImageBlended()` 等文本贴图渲染函数可以将文本字符串渲染为 Image 类型的 userdata 进行返回，`CreateTextImageBlended()` 函数接受三个参数，分别为 userdata 类型的字体数据、string 类型的文本内容 和 用以描述字体颜色的 RGBA 色彩空间结构体。

## 事件交互