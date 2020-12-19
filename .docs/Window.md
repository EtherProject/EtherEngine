# Ether窗口相关操作
> ## ShowMessageBox
显示模态的提示信息窗口
```lua
ShowMessageBox(title, message, boxtype)
```
**参数**

+ ***[string] title***：标题
+ ***[string] message***：提示信息内容
+ ***[Macro number] boxtype***：窗口类型

**返回值**

无

**示例**

> ## CreateWindow
创建窗口，并将此窗口作为图形绘制等操作的上下文
```lua
CreateWindow(title, show, window)
```
**参数**

+ ***[string] title***：窗口标题
+ ***[table]show***：用以描述显示区域的矩形
+ ***[table]window***：用以描述窗口属性的表

**返回值**

无

**示例**

> ## CloseWindow
关闭窗口
```lua
CloseWindow()
```
**参数**

无

**返回值**

无

**示例**

> ## SetWindowTitle
设置窗口标题
```lua
SetWindowTitle(title)
```
**参数**

+ ***[string] title***：窗口标题

**返回值**

无

**示例**

> ## GetWindowTitle
获取窗口标题
```lua
GetWindowTitle(title)
```
**参数**

无

**返回值**

+ ***[string] title***：窗口标题

**示例**

> ## SetWindowMode
设置窗口模式
```lua
SetWindowMode(mode)
```
**参数**

+ ***[Macro number] mode***：窗口模式

**返回值**

无

**示例**

> ## SetWindowResizable
设置窗口大小是否可变
```lua
SetWindowResizable(flag)
```
**参数**

+ ***[boolean] flag***：是否可变

**返回值**

无

**示例**

> ## SetWindowOpacity
设置窗口透明度
```lua
SetWindowOpacity(number)
```
**参数**

+ ***[number] number***：透明度大小（取值范围0-1）

**返回值**

无

**示例**

> ## SetWindowSize
设置窗口大小
```lua
SetWindowSize(width,height)
```
**参数**

+ ***[number] width***：窗口宽度
+ ***[number] height***：窗口高度

**返回值**

无

**示例**

> #### GetWindowSize
设置窗口大小
```lua
width,height = GetWindowSize()
```
**参数**

无

**返回值**

+ ***[number] width***：窗口宽度
+ ***[number] height***：窗口高度

**示例**

> ## SetWindowMaxSize
设置窗口最大尺寸的大小
```lua
SetWindowMaxSize(width,height)
```
**参数**

+ ***[number] width***：窗口最大宽度
+ ***[number] height***：窗口最大高度

**返回值**

无

**示例**

> ## GetWindowMaxSize
获取窗口最大尺寸的大小
```lua
width,height = GetWindowMaxSize()
```
**参数**

无

**返回值**

+ ***[number] width***：窗口最大宽度
+ ***[number] height***：窗口最大高度

**示例**

> ## SetWindowMinSize
设置窗口最小尺寸的大小
```lua
SetWindowMinSize(width,height)
```
**参数**

+ ***[number] width***：窗口最小宽度
+ ***[number] height***：窗口最小高度

**返回值**

无

**示例**

> ## GetWindowMinSize
设置窗口最小尺寸的大小
```lua
width,height = GetWindowMinSize()
```
**参数**

无

**返回值**

+ ***[number] width***：窗口最小宽度
+ ***[number] height***：窗口最小高度

**示例**

> ## SetWindowPosition
设置窗口坐标
```lua
SetWindowPosition(x，y)
```
**参数**

+ ***[number] x***：窗口位置的x坐标
+ ***[number] y***：窗口位置的y坐标

**返回值**

无

**示例**

> ## GetWindowPosition
获取窗口坐标
```lua
x,y = GetWindowPosition()
```
**参数**

无

**返回值**

+ ***[number] x***：窗口位置的x坐标
+ ***[number] y***：窗口位置的y坐标


**示例**

> ## ClearWindow
使用当前绘图颜色清空窗口内容
```lua
ClearWindow()
```
**参数**

无

**返回值**

无


**示例**