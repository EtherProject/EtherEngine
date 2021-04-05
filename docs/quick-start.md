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
-- 引入 Window 模块
UsingMoudle("Window")

-- 创建一个尺寸为 1280 x 720 的大小可变窗口
-- 标题为 "HelloWorld" 且显示在屏幕的默认位置上（通常为居中位置）
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

-- 死循环防止窗口退出
while true do end
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

while true do
    -- 将渲染缓冲区的数据冲刷到窗口上
    UpdateWindow() 
end
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

+ 最后，和显示图片的后两步相同，只需要通过 `CreateTexture()` 函数创建纹理并使用 `CopyTexture()` 函数拷贝纹理便可以完成文本渲染的全部过程。

示例代码如下：

```lua
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

-- 加载指定字号的字体文件
font = LoadFont("GameFont.ttf", 50)

-- 将文本使用已加载的字体文件渲染为文本贴图
text_image = CreateTextImageBlended(
    font,
    "This is My-Game!",
    -- 字体颜色为红色
    {r = 255, g = 0, b = 0, a = 255}
)

-- 将文本贴图渲染为纹理数据
text_texture = CreateTexture(text_image)

-- 将纹理数据拷贝到渲染缓冲区中
CopyTexture(text_texture, {x = 0, y = 0, w = 1280, h = 720})

while true do
    -- 将渲染缓冲区的数据冲刷到窗口上
    UpdateWindow() 
end
```

在第二步渲染文本贴图过程中，还有许多函数支持不同的文本渲染方式和不同的文本编码格式；除此之外，开发者还可以通过使用诸如 [`SetFontStyle()`](Graphic/_SetFontStyle_.md) 等函数对字体样式进行设置，更多内容详见 [完整手册：Graphic 模块](Graphic/index.md)

### 几何绘图

EtherAPI 也提供了大量的几何绘图 API，如点、线、矩形、三角形和圆等基本几何图元的绘制函数，以及对于其填充图形的绘制，示例代码如下：

```lua
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

-- 设置窗口的绘图颜色为红色
SetDrawColor({r = 255, g = 0, b = 0, a = 255})

-- 在屏幕中心绘制半径为 25 个像素的空心圆
Circle({x = 640, y = 360}, 25)

-- 设置窗口绘图颜色为蓝色
SetDrawColor({r = 0, g = 0, b = 255, a = 255})

-- 在屏幕左上角绘制长和宽均为 50 个像素的填充矩形
FillRectangle({x = 0, y = 0, w = 50, h = 50})

while true do
    -- 将渲染缓冲区的数据冲刷到窗口上
    UpdateWindow() 
end
```

通过 `SetDrawColor()` 函数可以设置窗口的绘图颜色，接下来的所有几何图元的绘制都将使用此颜色作为绘图色和填充色。

需要注意的是，所有的几何绘制同样在渲染缓冲区中进行，所以在绘制过程完毕后，依然需要调用 `UpdateWindow()` 函数来冲刷缓冲区。

更多几何绘图 API 详见 [完整手册：Graphic 模块](Graphic/index.md)

## 媒体播控  

声音作为游戏必不可少的一部分，在 EtherAPI 中也提供了几近完美的实现：EtherAPI 中的声音分为 `音乐` 和 `音效` 两类，音乐常用作全局的背景声音；音效则是用于战斗、动作等的环境音。在某种程度上，音乐和音效是等同可互换的，但是对于二者的内存加载策略和播控 API 可能并不相同。

所有声音的播放都是异步的，所以我们无需担心音乐和音效的播放会阻塞游戏的主线程，但是需要注意的是，在程序没有进行事件循环来确保程序持续运行的情况下，程序运行结束退出后音乐也会停止播放（与上述的窗口自动退出同理）

下面是一份简单的媒体播放样例代码：

```lua
-- 引入 Media 模块
UsingMoudle("Media")

-- 加载 BGM.mp3 音乐文件
music = LoadMusic("BGM.mp3")

-- 使用淡入效果循环播放音乐，淡入效果持续时间为 1.5 秒
FadeInMusic(music, -1, 1500)

-- 死循环防止程序退出
while true do end
```
更多的媒体播控 API 详见 [完整手册：Media 模块](Media/index.md)

## 事件交互

交互性是游戏的重要组成部分，EtherAPI 的 `Interactivity` 模块提供了简洁轻便的交互事件处理机制，常用的事件交互处理 API 如下：

+ [`UpdateEvent()`](Interactivity/_UpdateEvent_.md)：更新事件队列，如果当前事件队列有新的未处理事件，则返回 `true` ，否则返回 `false` 。
+ [`GetEventType()`](Interactivity/_GetEventType_.md)：获取事件队列未处理事件类型。 
+ [`GetCursorPosition()`](Interactivity/_GetCursorPosition_.md)：获取当前鼠标位置，返回值为描述鼠标在当前窗口坐标系中位置的点结构体。 
+ [`GetScrollValue()`](Interactivity/_GetScrollValue_.md)：获取鼠标滚轮的滚动距离，返回值分别为水平方向的滚动距离和垂直方向的滚动距离。 

故一个通用的事件循环可以写为如下代码：

```lua
UsingMoudle("Interactivity")

-- 创建游戏窗口
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

while true do
    -- 更新事件队列，若存在未处理事件则进行分支判断处理 
    if UpdateEvent() then
        -- 获取当前未处理事件类型
        local _event = GetEventType()
        -- 若事件类型为退出事件，则跳出游戏主循环
        -- 此处的宏使用方式只适用于 3.0.x 及以上版本
        if _event == Interactivity.EVENT_QUIT then
            break
        -- 若事件类型为鼠标移动事件，则输出当前鼠标位置
        -- 此处的宏使用方式只适用于 3.0.x 及以上版本
        else if _event == Interactivity.EVENT_MOUSEMOTION then
            local _cursor_pos = GetCursorPosition()
            print("CursorPosition: ", _cursor_pos.x, _cursor_pos.y)
        end
    end

    -- 将渲染缓冲区的数据冲刷到窗口上
    UpdateWindow() 
end
```

在一般情况下，如果一个窗口没有持续接收并更新事件，则会被系统认为此窗口进入异常的 `无响应` 状态，显而易见的，由于这个窗口不会对事件作出响应，故也无法拖拽移动、最小化或关闭窗口；所以，在游戏的主循环中持续调用 `UpdateEvent()` 函数时必要的。 

更多的交互事件类型详见 [完整手册：Interactivity 模块附录](Interactivity/appendix.md)

## 内存管理  

内存管理在游戏开发中的角色可谓是重要至极，EtherAPI 对于已加载和渲染出的数据的内存卸载提供了简单且高效的 API，简介如下：  

+ [`UnloadImage()`](Graphic/_UnloadImage_.md) 函数用来释放从文件中加载的图片数据或渲染出的文本贴图数据，即 Image 类型的 userdata 数据  
+ [`UnloadFont()`](Graphic/_UnloadFont_.md) 函数用来释放从文件中加载的字体数据，即 Image 类型的 userdata 数据 
+ [`DestroyTexture()`](Graphic/_DestroyTexture_.md) 函数用来销毁从渲染得到的纹理数据，即 Font 类型的 userdata 数据  
+ [`UnloadMusic()`](Media/_UnloadMusic_.md) 函数用来释放从文件中加载的音乐数据，即 Music 类型的 userdata 数据 
+ [`UnloadSound()`](Media/_UnloadSound_.md) 函数用来释放从文件中加载的音效数据，即 Sound 类型的 userdata 数据 

特别注意的是，这些 userdata 类型数据的销毁释放过程并未参与到 Lua 的自动内存管理中，简单地解除这些变量的引用或将变量设置为 `nil` 并不能完全释放其内部的数据，必须调用上述的内存释放 API 进行销毁，这样的设计保证了开发者更直接地对内存数据进行管理，防止游戏过程中 Lua 的内存管理策略并不完全适合开发者意图的情况出现。

## 工具模块

工具模块是一类对算法和系统层面封装的、用以辅助游戏开发的模块，涵盖了 算法、网络、时间、JSON解析、字符串编码、操作系统 等模块，下面只放置其目录索引，并不会对其进行详细介绍，具体内容请查看 [完整手册](index.md#目录) 的对应部分：

+ [算法模块](Algorithm/index.md)：封装了 数值限定、基础碰撞检测、色彩空间转换 等常用算法
+ [网络模块](Network/index.md)：提供了 主机地址和路由分离、HTTP请求 等操作
+ [时间模块](Time/index.md)：涵盖了 程序暂停、延时、动态延时、高分辨率计时 等功能
+ [JSON模块](JSON/index.md)：提供了 JSON 格式数据 编码 和 解码 等操作
+ [字符串模块](String/index.md)：为不同编码字符串相互转换提供了便捷操作
+ [操作系统模块](OS/index.md)：封装了 系统信息获取、平台相关文件系统 API 、剪切板操作等功能

## 协议

EtherAPI 是根据 MIT 许可协议进行发布的  

```
版权所有（c）2020-2021 Voidmatrix

本协议授予所有人免费的许可  
获取此软件和相关文档的副本

本协议不限制代码本身及其衍生物的使用权，
支持对源代码或其副本进行任意复制、修改、合并、发布、再许可或出售

但是使用者必须遵守如下规定：
软件按源码提供，不提供任何形式的保证，包括但不限于代码质量
软件作者保留版权，但不对任何使用者担负任何责任
您可以在开源或私有的软件中自由使用本软件，但是必须保证标注您使用过本软件
```