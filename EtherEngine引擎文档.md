# Ether引擎开发文档
> ~~更简单~~更专业的游戏引擎
## 1. API字母顺序总览
+ Circle():  在指定位置绘制无填充圆形
+ ClearWindow():  使用当前绘图颜色清空窗口内容
+ CloseWindow():  关闭窗口
+ CopyReshapeTexture():  将裁剪后的纹理拷贝至渲染缓冲区内
+ CopyRotateReshapeTexture():  将旋转且裁剪后的纹理拷贝至渲染缓冲区内
+ CopyRotateTexture():  将旋转后的纹理拷贝至渲染缓冲区内
+ CopyTexture():  将纹理拷贝至渲染缓冲区内
+ CreateTextImageBlended():  使用Blended模式创建文本图像
+ CreateTextImageShaded():  使用Shaded模式创建文本图像
+ CreateTextImageSolid():  使用Solid模式创建文本图像
+ CreateTexture():  从图像数据创建属于窗口的可渲染纹理
+ CreateUTF8TextImageBlended():  使用Blended模式创建UTF-8编码格式的文本图像
+ CreateUTF8TextImageShaded():  使用Shaded模式创建UTF-8编码格式的文本图像
+ CreateUTF8TextImageSolid():  使用Solid模式创建UTF-8编码格式的文本图像
+ CreateWindow():  创建窗口，并将此窗口作为图形绘制等操作的上下文
+ DestroyTexture():  销毁纹理数据
+ Ellipse():  在指定位置绘制无填充椭圆
+ FadeInMusic():  使用淡入效果播放已加载的音乐
+ FadeOutMusic():  使用淡出效果停止正在播放的音乐
+ FillCircle():  在指定位置绘制填充圆形
+ FillEllipse():  在指定位置绘制填充椭圆
+ FillPie():  在指定位置绘制填充扇形
+ FillRectangle():  在指定位置绘制填充矩形
+ FillRoundRectangle():  在指定位置绘制圆角填充矩形
+ FillTriangle():  在指定位置绘制填充三角形
+ GetAccurateCount():  获取高分辨率计数器当前值
+ GetBasePath():  获取程序运行的目录
+ GetClipboardText():  获取剪切板文本
+ GetCounterFrequency():  获取高分辨率计数器频率
+ GetCursorPosition():  获取当前鼠标位置
+ GetDrawColor():  获取窗口绘图颜色
+ GetEventType():  获取当前的内置事件类型
+ GetFontHeight():  获取字体高度
+ GetFontKerning():  获取字体间距
+ GetFontOutlineWidth():  获取已加载字体的轮廓线宽度
+ GetFontStyle():  获取已加载字体的样式
+ GetImageSize():  获取已加载图像尺寸
+ GetInitTime获取程序从初始化运行到现在为止的时间
+ GetMusicType():  获取指定音乐的类型
+ GetMusicVolume():  获取当前音乐播放的音量
+ GetPlatform():  获取平台类型
+ GetScrollValue():  获取鼠标滚轮滚动距离
+ GetSystemRAM():  获取系统总内存大小
+ GetTextSize():  获取文本尺寸
+ GetUTF8TextSize():  获取UTF-8编码格式的文本尺寸
+ GetWindowMaxSize():  获取窗口最大尺寸的大小
+ GetWindowMinSize():  获取窗口最小尺寸的大小
+ GetWindowPosition():  获取窗口坐标
+ GetWindowSize():  获取窗口大小
+ GetWindowTitle():  获取窗口标题
+ Line():  在指定位置绘制直线
+ LoadFont():  加载字体文件
+ LoadImage():  加载图像文件
+ LoadMusic():  加载音乐文件
+ LoadSound():  加载音效文件
+ Pause():  暂停程序
+ PauseMusic():  暂停当前正在播放的音乐
+ Pie():  在指定位置绘制无填充扇形
+ PlayMusic():  播放已加载的音乐
+ PlaySound():  播放已加载的音效
+ Point():  在指定位置绘制点
+ Rectangle():  在指定位置绘制无填充矩形
+ ResumeMusic():  恢复当前暂停状态的音乐
+ RewindMusic():  重新播放当前正在播放的音乐
+ RoundRectangle():  在指定位置绘制圆角无填充矩形
+ SetClipboardText():  设置剪切板文本
+ SetCursorShow():   设置鼠标是否显示
+ SetDrawColor():  设置窗口绘图颜色
+ SetFontKerning():  设置字体间距
+ SetFontOutlineWidth():  设置已加载字体的轮廓线宽度
+ SetFontStyle():  设置已加载字体的样式
+ SetImageColorKey():  设置的图片文件是否启用指定的ColorKey，启用的Color将被透明化
+ SetMusicVolume():  设置音乐播放的音量
+ SetTextureAlpha():  设置纹理透明度
+ SetWindowMaxSize():  设置窗口最大尺寸的大小
+ SetWindowMinSize():  设置窗口最小尺寸的大小
+ SetWindowMode():  设置窗口模式
+ SetWindowOpacity():  设置窗口透明度
+ SetWindowPosition():  设置窗口坐标
+ SetWindowResizable():  设置窗口大小是否可变
+ SetWindowSize():  设置窗口大小
+ SetWindowTitle():  设置窗口标题
+ ShowMessageBox():  显示模态的提示信息窗口
+ Sleep():  挂起程序指定时间
+ ThickLine():  在指定位置绘制粗直线
+ Triangle():  在指定位置绘制无填充三角形
+ UnloadFont():  释放已加载的字体
+ UnloadImage():  释放已加载的图像
+ UnloadMusic():  释放已加载的音乐
+ UnloadSound():  释放已加载的音效
+ UpdateEvent():  获取并更新内置事件
+ UpdateWindow():  将渲染缓冲区的内容刷新到屏幕上

## 2. API功能分类及介绍

### 2.1 Ether图形相关操作

> ## SetCursorShow
设置鼠标是否显示
```lua
SetCursorShow(value)
```
**参数**

+ ***[boolean] value***：是否显示鼠标

**返回值**

无

**示例**

> ## LoadImage
加载图像文件
```lua
surface = LoadImage(path)
```
**参数**

+ ***[string] path***：图像文件路径

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## SetImageColorKey
设置的图片文件是否启用指定的ColorKey，启用的Color将被透明化
```lua
SetImageColorKey(surface, value, ColorKey)
```
**参数**

+ ***[userdata-IMAGE] surface***：图像数据
+ ***[boolean] value***：是否启用
+ ***[table]ColorKey***：ColorKey

**返回值**

无

**示例**

> ## UnloadImage
释放已加载的图像
```lua
UnloadImage(surface)
```
**参数**

+ ***[userdata-IMAGE] surface***：图像数据

**返回值**

无

**示例**

> ## CreateTexture
从图像数据创建属于窗口的可渲染纹理（必须在创建窗口完成之后进行）
```lua
texture = CreateTexture(surface)
```
**参数**

+ ***[userdata-IMAGE] surface***：图像数据

**返回值**

+ ***[userdata-TEXTURE] texture***：纹理数据

**示例**

> ## DestroyTexture
销毁纹理数据
```lua
DestroyTexture(texture)
```
**参数**

+ ***[userdata-TEXTURE] texture***：纹理数据

**返回值**

无

**示例**

> ## SetTextureAlpha
设置纹理透明度
```lua
SetTextureAlpha(texture, number)
```
**参数**

+ ***[userdata-TEXTURE] texture***：纹理数据
+ ***[number] number***：透明度数值, 取值范围0-255
**返回值**

无

**示例**

> ## GetImageSize
获取已加载图像尺寸
```lua
width,height = = GetImageSize(surface)
```
**参数**

+ ***[userdata-IMAGE] surface***：图像数据

**返回值**

+ ***[number]width***：图像宽度
+ ***[number]height***：图像高度

**示例**

> ## CopyTexture
将纹理拷贝至渲染缓冲区内
```lua
CopyTexture（surface，show）
```
**参数**

+ ***[userdata-TEXTURE] surface***：纹理数据
+ ***[table]show***：用以描述显示区域的矩形

**返回值**

无

**示例**

> ## CopyRotateTexture
将旋转后的纹理拷贝至渲染缓冲区内
```lua
CopyRotateTexture（surface，angle, center, mode, show）
```
**参数**

+ ***[userdata-TEXTURE] surface***：纹理数据
+ ***[number]angle***：旋转角度
+ ***[table]center***：旋转中心坐标
+ ***[table]mode***：旋转模式
+ ***[table]show***：用以描述显示区域的矩形

**返回值**

无

**示例**

> ## CopyReshapeTexture
将裁剪后的纹理拷贝至渲染缓冲区内
```lua
CopyReshapeTexture（surface，cut, show）
```
**参数**

+ ***[userdata-TEXTURE] surface***：纹理数据
+ ***[table]cut***：用以描述裁剪区域的矩形
+ ***[table]show***：用以描述显示区域的矩形

**返回值**

无

**示例**

> ## CopyRotateReshapeTexture
将旋转且裁剪后的纹理拷贝至渲染缓冲区内
```lua
CopyRotateReshapeTexture（surface，angle, center, mode, cut, show）
```
**参数**

+ ***[userdata-TEXTURE] surface***：纹理数据
+ ***[number]angle***：旋转角度
+ ***[table]center***：旋转中心坐标
+ ***[table]mode***：旋转模式
+ ***[table]cut***：用以描述裁剪区域的矩形
+ ***[table]show***：用以描述显示区域的矩形

**返回值**

无

**示例**

> ## SetDrawColor
设置窗口绘图颜色
```lua
SetDrawColor（rgba）
```
**参数**

+ ***[table]rgba***：描述颜色的RGBA表（取值范围均为0-255）

**返回值**

无

**示例**

> ## GetDrawColor
获取窗口绘图颜色
```lua
rgba = GetDrawColor（）
```
**参数**

无

**返回值**

+ ***[table]rgba***：描述颜色的RGBA表（取值范围均为0-255）

**示例**

> ## Point
在指定位置绘制点
```lua
Point（point）
```
**参数**

+ ***[table]point***：点坐标

**返回值**

无

**示例**

> ## Line
在指定位置绘制直线
```lua
Line（start, end）
```
**参数**

+ ***[table]start***：点坐标
+ ***[table]end***：点坐标

**返回值**

无

**示例**

> ## ThickLine
在指定位置绘制粗直线
```lua
ThickLine（start, end, width）
```
**参数**

+ ***[table]start***：点坐标
+ ***[table]end***：点坐标
+ ***[number]width***：直线宽度

**返回值**

无

**示例**

> ## Rectangle
在指定位置绘制无填充矩形
```lua
Rectangle（rectangle）
```
**参数**

+ ***[table]rectangle***：用以描述显示区域的矩形

**返回值**

无

**示例**

> ## FillRectangle
在指定位置绘制填充矩形
```lua
FillRectangle（rectangle）
```
**参数**

+ ***[table]rectangle***：用以描述显示区域的矩形

**返回值**

无

**示例**

> ## RoundRectangle
在指定位置绘制圆角无填充矩形
```lua
RoundRectangle（rectangle, radius）
```
**参数**

+ ***[table]rectangle***：用以描述显示区域的矩形
+ ***[number]radius***：圆角半径大小

**返回值**

无

**示例**

> ## FillRoundRectangle
在指定位置绘制圆角填充矩形
```lua
FillRoundRectangle（rectangle, radius）
```
**参数**

+ ***[table]rectangle***：用以描述显示区域的矩形
+ ***[number]radius***：圆角半径大小

**返回值**

无

**示例**

> ## Circle
在指定位置绘制无填充圆形
```lua
Circle（point, radius）
```
**参数**

+ ***[table]point***：圆心坐标
+ ***[number]radius***：圆半径

**返回值**

无

**示例**

> ## FillCircle
在指定位置绘制填充圆形
```lua
FillCircle（point, radius）
```
**参数**

+ ***[table]point***：圆心坐标
+ ***[number]radius***：圆半径

**返回值**

无

**示例**

> ## Ellipse
在指定位置绘制无填充椭圆
```lua
Ellipse（point, radius_x, radius_y）
```
**参数**

+ ***[table]point***：椭圆中心坐标
+ ***[number]radius***：椭圆x轴半径
+ ***[number]radius***：椭圆y轴半径

**返回值**

无

**示例**

> ## FillEllipse
在指定位置绘制填充椭圆
```lua
FillEllipse（point, radius_x, radius_y）
```
**参数**

+ ***[table]point***：椭圆中心坐标
+ ***[number]radius_x***：椭圆x轴半径
+ ***[number]radius_y***：椭圆y轴半径

**返回值**

无

**示例**

> ## Pie
在指定位置绘制无填充扇形
```lua
Pie（point, radius, startangle，endangle）
```
**参数**

+ ***[table]point***：扇形所在圆的圆心坐标
+ ***[number]radius***：扇形所在圆的半径
+ ***[number]startangle***：扇形开始角度（扇形从以其所在圆心为原点的二维笛卡尔坐标系的x轴正方向开始绘制，角度的正方向为顺时针方向）
+ ***[number]endangle***：扇形结束角度

**返回值**

无

**示例**

> ## FillPie
在指定位置绘制填充扇形
```lua
FillPie（point, radius, startangle，endangle）
```
**参数**

+ ***[table]point***：扇形所在圆的圆心坐标
+ ***[number]radius***：扇形所在圆的半径
+ ***[number]startangle***：扇形开始角度（扇形从以其所在圆心为原点的二维笛卡尔坐标系的x轴正方向开始绘制，角度的正方向为顺时针方向）
+ ***[number]endangle***：扇形结束角度

**返回值**

无

**示例**

> ## Triangle
在指定位置绘制无填充三角形
```lua
Triangle（point_a, point_b, point_c）
```
**参数**

+ ***[table]point_a***：第一个顶点坐标
+ ***[table]point_b***：第二个顶点坐标
+ ***[table]point_c***：第三个顶点坐标

**返回值**

无

**示例**

> ## FillTriangle
在指定位置绘制填充三角形
```lua
FillTriangle（point_a, point_b, point_c）
```
**参数**

+ ***[table]point_a***：第一个顶点坐标
+ ***[table]point_b***：第二个顶点坐标
+ ***[table]point_c***：第三个顶点坐标

**返回值**

无

**示例**

> ## LoadFont
加载字体文件
```lua
font = LoadFont(path,  size)
```
**参数**

+ ***[string] path***：字体文件路径
+ ***[number] size***：字体大小

**返回值**

+ ***[userdata-FONT] font***：成功则返回字体数据，失败则返回nil

**示例**

> ## UnLoadFont
释放已加载的字体
```lua
UnLoadFont(font)
```
**参数**

+ ***[userdata-FONT] font***：字体数据

**返回值**

无

**示例**

> ## GetFontStyle
获取已加载字体的样式
```lua
style = GetFontStyle(font)
```
**参数**

+ ***[userdata-FONT] font***：字体数据

**返回值**

+ ***[table]style***：用以描述字体样式的表

**示例**

> ## SetFontStyle(
设置已加载字体的样式
```lua
SetFontStyle(font, style)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[table]style***：用以描述字体样式的表

**返回值**

无

**示例**

> ## GetFontOutlineWidth
获取已加载字体的轮廓线宽度
```lua
width = GetFontOutlineWidth(font)
```
**参数**

+ ***[userdata-FONT] font***：字体数据

**返回值**

+ ***[number] width***：: 轮廓线宽度

**示例**

> ## SetFontOutlineWidth
设置已加载字体的轮廓线宽度
```lua
SetFontOutlineWidth(font，width)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[number] width***：: 轮廓线宽度

**返回值**

无

**示例**

> ## GetFontKerning
获取字体间距
```lua
width = GetFontKerning(font)
```
**参数**

+ ***[userdata-FONT] font***：字体数据

**返回值**

+ ***[number] width***：: 字体间距

**示例**

> ## SetFontKerning
设置字体间距
```lua
SetFontKerning(font, width)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[number] width***：: 字体间距

**返回值**

无

**示例**

> ## GetFontHeight
获取字体高度
```lua
height = GetFontHeight(font)
```
**参数**

+ ***[userdata-FONT] font***：字体数据

**返回值**

+ ***[number] height***：: 字体高度

**示例**

> ## GetTextSize
获取文本尺寸
```lua
width, height = GetTextSize(font, text)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：文本内容

**返回值**

+ ***[number] width***：: 字体宽度
+ ***[number] height***：: 字体高度

**示例**

> ## GetUTF8TextSize
获取UTF-8编码格式的文本尺寸
```lua
width, height = GetUTF8TextSize(font, text)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：UTF-8编码格式的文本内容

**返回值**

+ ***[number] width***：: 字体宽度
+ ***[number] height***：: 字体高度

**示例**

> ## CreateTextImageSolid
使用Solid模式创建文本图像
```lua
surface = CreateTextImageSolid(font, text, rgba)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：文本内容
+ ***[table]rgba***：描述颜色的RGBA表（取值范围均为0-255）

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## CreateUTF8TextImageSolid
使用Solid模式创建文本图像
```lua
surface = CreateUTF8TextImageSolid(font, text, rgba)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：UTF-8编码格式的文本内容
+ ***[table]rgba***：用以描述文本颜色的RGBA表（取值范围均为0-255）

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## CreateTextImageShaded
使用Solid模式创建文本图像
```lua
surface = CreateTextImageShaded(font, text, rgba, rgba_background)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：文本内容
+ ***[table]rgba***：用以描述文本颜色的RGBA表（取值范围均为0-255）
+ ***[table]rgba_background***：用以描述文本背景颜色的RGBA表（取值范围均为0-255）

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## CreateUTF8TextImageShaded
使用Shaded模式创建UTF-8编码格式的文本图像
```lua
surface = CreateUTF8TextImageShaded(font, text, rgba, rgba_background)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：UTF-8编码格式的文本内容
+ ***[table]rgba***：用以描述文本颜色的RGBA表（取值范围均为0-255）
+ ***[table]rgba_background***：用以描述文本背景颜色的RGBA表（取值范围均为0-255）

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## CreateTextImageBlended
使用Blended模式创建文本图像
```lua
surface = CreateTextImageBlended(font, text, rgba)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：文本内容
+ ***[table]rgba***：用以描述文本颜色的RGBA表（取值范围均为0-255）

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## CreateUTF8TextImageBlended
使用Blended模式创建UTF-8编码格式的文本图像
```lua
surface = CreateUTF8TextImageBlended(font, text, rgba)
```
**参数**

+ ***[userdata-FONT] font***：字体数据
+ ***[string] text***：UTF-8编码格式的文本内容
+ ***[table]rgba***：用以描述文本颜色的RGBA表（取值范围均为0-255）

**返回值**

+ ***[userdata-IMAGE] surface***：成功则返回图像数据，失败则返回nil

**示例**

> ## UpdateWindow
将渲染缓冲区的内容刷新到屏幕上
```lua
UpdateWindow()
```
**参数**

无

**返回值**

+ ***[number] width***：: 字体宽度
+ ***[number] height***：: 字体高度

**示例**

### 2.2 Ether交互事件处理
> ## GetCursorPosition
获取当前鼠标位置
```lua
x, y = GetCursorPosition()
```
**参数**

无

**返回值**

+ ***[number] x***：鼠标位置的x坐标
+ ***[number] y***：鼠标位置的y坐标

**示例**

> ## GetScrollValue
获取鼠标滚轮滚动距离
```lua
x, y = GetScrollValue()
```
**参数**

无

**返回值**

+ ***[number] x***：滚轮水平方向滚动距离（向左为负，向右为正）
+ ***[number] y***：滚轮垂直方向滚动距离（向前为负，向后为正）

**示例**

> ## UpdateEvent
获取并更新内置事件
```lua
flag = UpdateEvent()
```
**参数**

无

**返回值**

+ ***[boolean] flag***：false，当前事件队列无待解决事件；true，当前事件队列有待解决事件

**示例**

> ## GetEventType
获取当前的内置事件类型（由于部分字符按键事件对应的输入在大多数键盘上只能通过组合键完成，故这些字符的按键事件在大多数键盘上可能无法通过物理按键激活）
```lua
flag = GetEventType()
```
**参数**

无

**返回值**

+ ***[MACRO number] flag***：事件类型

**示例**

### 2.3 Ether媒体相关操作
> ## LoadMusic
加载音乐文件
```lua
flag = LoadMusic(path)
```
**参数**

+ ***[string] path***：音乐文件路径

**返回值**

+ ***[userdata-MUSIC] flag***：成功则返回音乐数据，失败则返回nil

**示例**

> ## UnloadMusic
释放已加载的音乐
```lua
UnloadMusic(flag)
```
**参数**

+ ***[userdata-MUSIC] flag***：音乐数据

**返回值**

无

**示例**

> ## PlayMusic
播放已加载的音乐
```lua
PlayMusic(flag，loops)
```
**参数**

+ ***[userdata-MUSIC] flag***：音乐数据
+ ***[number] loops***：音乐播放的次数（-1为循环播放）

**返回值**

无

**示例**

> ## FadeInMusic
使用淡入效果播放已加载的音乐
```lua
FadeInMusic(flag，loops, ms)
```
**参数**

+ ***[userdata-MUSIC] flag***：成功则返回音乐数据，失败则返回nil
+ ***[number] loops***：音乐播放的次数（-1为循环播放）
+ ***[number] ms***：淡入音效持续时间，单位为毫秒

**返回值**

无

**示例**

> ## FadeOutMusic
使用淡出效果停止正在播放的音乐
```lua
FadeInMusic(ms)
```
**参数**

+ ***[number] ms***：淡出音效持续时间，单位为毫秒

**返回值**

无

**示例**

> ## SetMusicVolume
设置音乐播放的音量
```lua
SetMusicVolume(value)
```
**参数**

+ ***[number] value***：音量大小，取值范围为 0-128

**返回值**

无

**示例**

> ## GetMusicVolume
获取当前音乐播放的音量
```lua
value = GetMusicVolume()
```
**参数**

无

**返回值**

+ ***[number] value***：音量大小，取值范围为 0-128

**示例**

> ## PauseMusic
暂停当前正在播放的音乐
```lua
PauseMusic()
```
**参数**

无

**返回值**

无

**示例**

> ## ResumeMusic
恢复当前暂停状态的音乐
```lua
ResumeMusic()
```
**参数**

无

**返回值**

无

**示例**

> ## RewindMusic
重新播放当前正在播放的音乐
```lua
ResumeMusic()
```
**参数**

无

**返回值**

无

**示例**

> ## GetMusicType
获取指定音乐的类型
```lua
typeName = GetMusicType(flag)
```
**参数**

+ ***[userdata-MUSIC] flag***：音乐数据（nil表示正在播放的音乐）

**返回值**

+ ***[MACRO number] typeName***：音乐类型


**示例**

> ## LoadSound
加载音效文件
```lua
flag = LoadSound(flag)
```
**参数**

+ ***[string] path***：音效文件路径

**返回值**

+ ***[userdata-SOUND] flag***：成功则返回音效数据，失败则返回nil

**示例**

> ## UnloadSound
释放已加载的音效
```lua
UnloadSound(flag)
```
**参数**

+ ***[userdata-SOUND] flag***：音效数据

**返回值**

无

**示例**

> ## PlaySound
播放已加载的音效
```lua
PlaySound(flag, loops)
```
**参数**

+ ***[userdata-SOUND] flag***：音效数据
+ ***[number] loops***：音乐播放的次数（-1为循环播放）

**返回值**

无

**示例**

### 2.5 Ether时间相关操作
> ## Pause
暂停程序
```lua
Pause()
```
**参数**

无

**返回值**

无

**示例**

> ## Sleep
挂起程序指定时间
```lua
Sleep(ms)
```
**参数**

+ ***[number] ms***：挂起时间（单位：毫秒）

**返回值**

无

**示例**

> ## GetInitTime
获取程序从初始化运行到现在为止的时间
```lua
ms = GetInitTime()
```
**参数**

无

**返回值**

+ ***[number] ms***：运行时间（单位：毫秒）

**示例**

> ## GetAccurateCount
获取高分辨率计数器当前值
```lua
count = GetAccurateCount()
```
**参数**

无

**返回值**

+ ***[number] count***：计数器当前值

**示例**

> ## GetCounterFrequency
获取高分辨率计数器频率
```lua
hz = GetCounterFrequency()
```
**参数**

无

**返回值**

+ ***[number] hz***：计数器频率（单位：赫兹）

**示例**

### 2.6 Ether窗口相关操作
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

### 2.7 Ether其它功能
> ## GetBasePath
获取程序运行的目录
```lua
basepath = GetBasePath()
```
**参数**

无

**返回值**

+ ***[string] basepath***：程序运行目录

**示例**

> ## SetClipboardText
设置剪切板文本
```lua
SetClipboardText(text)
```
**参数**

+ ***[string] text***：剪切板文本

**返回值**

无

**示例**

> ## GetClipboardText
获取剪切板文本
```lua
text = GetClipboardText()
```
**参数**

无

**返回值**

+ ***[string] text***：剪切板文本

**示例**

> ## GetPlatform
获取平台类型
```lua
platform = GetPlatform()
```
**参数**

无

**返回值**

+ ***[string] platform***：平台类型

**示例**

> ## GetSystemRAM
获取系统总内存大小
```lua
mb = GetSystemRAM()
```
**参数**

无

**返回值**

+ ***[number] mb***：系统内存（单位MB）

**示例**

## 3. 附录
|                        值                         |                  描述                   |
| ------------------------------------------------- | ---------------------------------------- |
| MSGBOX_ERROR                              | 提示信息窗口类型：错误             |
| MSGBOX_WARNING                          | 提示信息窗口类型：警告             |
| MSGBOX_INFO                                | 提示信息窗口类型：信息             |
| WINDOW_FULLSCREEN                      | 窗口样式：全屏                       |
| WINDOW_FULLSCREEN_DESKTOP          | 窗口样式：桌面全屏                  |
| WINDOW_BORDERLESS                      | 窗口样式：无边框                     |
| WINDOW_RESIZABLE                         | 窗口样式：可调整大小                |
| WINDOW_MAXIMIZED                       | 窗口样式：最大化                     |
| WINDOW_MINIMIZED                        | 窗口样式：最小化                     |
| FLIP_HORIZONTAL                            | 翻转模式：水平翻转                  |
| FLIP_VERTICAL                                 | 翻转模式：垂直翻转                  |
| FLIP_NONE                                     | 翻转模式：无翻转                     |
| WINDOW_MODE_WINDOWED              | 窗口模式：窗口化                     |
| WINDOW_MODE_FULLSCREEN             | 窗口模式：全屏                       |
| WINDOW_MODE_FULLSCREEN_DESKTOP | 窗口模式：桌面全屏                  |
| EVENT_QUIT                                   | 事件：退出                            |
| EVENT_MOUSEMOTION                     | 事件：鼠标移动                       |
| EVENT_MOUSEBTNDOWN_LEFT            | 事件：鼠标右键按下                  |
| EVENT_MOUSEBTNDOWN_RIGHT            | 事件：鼠标左键按下                  |
| EVENT_MOUSEBTNDOWN_MIDDLE         | 事件：鼠标中键按下                  |
| EVENT_MOUSEBTNUP_LEFT                 | 事件：鼠标左键抬起                  |
| EVENT_MOUSEBTNUP_RIGHT               | 事件：鼠标右键抬起                  |
| EVENT_MOUSEBTNUP_MIDDLE             | 事件：鼠标中键抬起                  |
| EVENT_MOUSESCROLL                       | 事件：鼠标滚轮滚动                  |
| EVENT_WINDOW_SHOW                     | 事件：窗口显示                       |
| EVENT_WINDOW_HIDE                       | 事件：窗口隐藏                       |
| EVENT_WINDOW_MOVE                     | 事件：窗口移动                       |
| EVENT_WINDOW_RESIZE                    | 事件：调整窗口大小                  |
| EVENT_WINDOW_MINSIZE                  | 事件：窗口最小化                     |
| EVENT_WINDOW_MAXSIZE                  | 事件：窗口最大化                     |
| EVENT_WINDOW_ENTER                     | 事件：进入窗口                       |
| EVENT_WINDOW_LEAVE                     | 事件：离开窗口                       |
| EVENT_WINDOW_FOCUS                    | 事件：窗口获得焦点                  |
| EVENT_WINDOW_LOST                      | 事件：窗口失去焦点                  |
| EVENT_WINDOW_CLOSE                     | 事件：窗口关闭                       |
| EVENT_WINDOW_EXPOSED                 | 事件：窗口显示                       |
| EVENT_KEYDOWN_0                          | 事件：按下键位 0                     |
| EVENT_KEYDOWN_00                        | 事件：按下键位 00                   |
| EVENT_KEYDOWN_000                       | 事件：按下键位 000                  |
| EVENT_KEYDOWN_1                          | 事件：按下键位 1                     |
| EVENT_KEYDOWN_2                          | 事件：按下键位 2                     |
| EVENT_KEYDOWN_3                          | 事件：按下键位 3                     |
| EVENT_KEYDOWN_4                          | 事件：按下键位 4                     |
| EVENT_KEYDOWN_5                          | 事件：按下键位 5                     |
| EVENT_KEYDOWN_6                          | 事件：按下键位 6                     |
| EVENT_KEYDOWN_7                          | 事件：按下键位 7                     |
| EVENT_KEYDOWN_8                          | 事件：按下键位 8                     |
| EVENT_KEYDOWN_9                          | 事件：按下键位 9                     |
| EVENT_KEYDOWN_F1                        | 事件：按下键位 F1                   |
| EVENT_KEYDOWN_F2                        | 事件：按下键位 F2                   |
| EVENT_KEYDOWN_F3                        | 事件：按下键位 F3                   |
| EVENT_KEYDOWN_F4                        | 事件：按下键位 F4                   |
| EVENT_KEYDOWN_F5                        | 事件：按下键位 F5                   |
| EVENT_KEYDOWN_F6                        | 事件：按下键位 F6                   |
| EVENT_KEYDOWN_F7                        | 事件：按下键位 F7                   |
| EVENT_KEYDOWN_F8                        | 事件：按下键位 F8                   |
| EVENT_KEYDOWN_F9                        | 事件：按下键位 F9                   |
| EVENT_KEYDOWN_F10                       | 事件：按下键位 F10                  |
| EVENT_KEYDOWN_F11                       | 事件：按下键位 F11                  |
| EVENT_KEYDOWN_F12                       | 事件：按下键位 F12                  |
| EVENT_KEYDOWN_F13                       | 事件：按下键位 F13                  |
| EVENT_KEYDOWN_F14                       | 事件：按下键位 F14                  |
| EVENT_KEYDOWN_F15                       | 事件：按下键位 F15                  |
| EVENT_KEYDOWN_F16                       | 事件：按下键位 F16                  |
| EVENT_KEYDOWN_F17                       | 事件：按下键位 F17                  |
| EVENT_KEYDOWN_F18                       | 事件：按下键位 F18                  |
| EVENT_KEYDOWN_F19                       | 事件：按下键位 F19                  |
| EVENT_KEYDOWN_F20                       | 事件：按下键位 F20                  |
| EVENT_KEYDOWN_F21                       | 事件：按下键位 F21                  |
| EVENT_KEYDOWN_F22                       | 事件：按下键位 F22                  |
| EVENT_KEYDOWN_F23                       | 事件：按下键位 F23                  |
| EVENT_KEYDOWN_F24                       | 事件：按下键位 F24                  |
| EVENT_KEYDOWN_A                          | 事件：按下键位 A                     |
| EVENT_KEYDOWN_B                          | 事件：按下键位 B                     |
| EVENT_KEYDOWN_C                          | 事件：按下键位 C                     |
| EVENT_KEYDOWN_D                         | 事件：按下键位 D                    |
| EVENT_KEYDOWN_E                          | 事件：按下键位 E                     |
| EVENT_KEYDOWN_F                          | 事件：按下键位 F                     |
| EVENT_KEYDOWN_G                         | 事件：按下键位 G                    |
| EVENT_KEYDOWN_H                         | 事件：按下键位 H                    |
| EVENT_KEYDOWN_I                           | 事件：按下键位 I                      |
| EVENT_KEYDOWN_J                          | 事件：按下键位 J                     |
| EVENT_KEYDOWN_K                          | 事件：按下键位 K                     |
| EVENT_KEYDOWN_L                          | 事件：按下键位 L                     |
| EVENT_KEYDOWN_M                         | 事件：按下键位 M                    |
| EVENT_KEYDOWN_N                         | 事件：按下键位 N                    |
| EVENT_KEYDOWN_O                         | 事件：按下键位 O                    |
| EVENT_KEYDOWN_P                          | 事件：按下键位 P                     |
| EVENT_KEYDOWN_Q                         | 事件：按下键位 Q                    |
| EVENT_KEYDOWN_R                          | 事件：按下键位 R                     |
| EVENT_KEYDOWN_S                          | 事件：按下键位 S                     |
| EVENT_KEYDOWN_T                          | 事件：按下键位 T                     |
| EVENT_KEYDOWN_U                         | 事件：按下键位 U                    |
| EVENT_KEYDOWN_V                          | 事件：按下键位 V                     |
| EVENT_KEYDOWN_W                         | 事件：按下键位 W                    |
| EVENT_KEYDOWN_X                          | 事件：按下键位 X                     |
| EVENT_KEYDOWN_Y                          | 事件：按下键位 Y                     |
| EVENT_KEYDOWN_Z                          | 事件：按下键位 Z                     |
| EVENT_KEYDOWN_ESC                       | 事件：按下键位 ESC                  |
| EVENT_KEYDOWN_ENTER                    | 事件：按下键位 ENTER               |
| EVENT_KEYDOWN_BACKSPACE             | 事件：按下键位 BACKSPACE         |
| EVENT_KEYDOWN_UP                        | 事件：按下键位 UP                   |
| EVENT_KEYDOWN_DOWN                   | 事件：按下键位 DOWN              |
| EVENT_KEYDOWN_LEFT                      | 事件：按下键位 LEFT                 |
| EVENT_KEYDOWN_RIGHT                    | 事件：按下键位 LIGHT               |
| EVENT_KEYDOWN_INSERT                   | 事件：按下键位 INSERT              |
| EVENT_KEYDOWN_DELETE                   | 事件：按下键位 DELETE              |
| EVENT_KEYDOWN_HOME                    | 事件：按下键位 HOME               |
| EVENT_KEYDOWN_END                      | 事件：按下键位 END                 |
| EVENT_KEYDOWN_PAGEUP                 | 事件：按下键位 PAGEUP            |
| EVENT_KEYDOWN_PAGEDOWN            | 事件：按下键位 PAGEDOWN       |
| EVENT_KEYDOWN_LEFTCTRL                | 事件：按下键位 LEFTCTRL           |
| EVENT_KEYDOWN_LEFTGUI                 | 事件：按下键位 LEFTGUI            |
| EVENT_KEYDOWN_LEFTALT                  | 事件：按下键位 LEFTALT             |
| EVENT_KEYDOWN_LEFTSHIFT               | 事件：按下键位 LEFTSHIFT          |
| EVENT_KEYDOWN_RIGHTCTRL              | 事件：按下键位 RIGHTCTRL         |
| EVENT_KEYDOWN_RIGHTGUI               | 事件：按下键位 RIGHTGUI          |
| EVENT_KEYDOWN_RIGHTALT               | 事件：按下键位 GIGHTALT          |
| EVENT_KEYDOWN_RIGHTSHIFT             | 事件：按下键位 RIGHTSHIFT         |
| EVENT_KEYDOWN_SPACE                    | 事件：按下键位 SPACE               |
| EVENT_KEYDOWN_TAB                       | 事件：按下键位 TAB                  |
| EVENT_KEYDOWN_CAPSLOCK              | 事件：按下键位 CAPSLOCK           |
| EVENT_KEYDOWN_NUMLOCK              | 事件：按下键位 NUMLOCK           |
| EVENT_KEYDOWN_PRINTSCREEN           | 事件：按下键位 PRINTSCREEN      |
| EVENT_KEYDOWN_SCROLLLOCK            | 事件：按下键位 SCROLLLOCK       |
| EVENT_KEYDOWN_PAUSE                   | 事件：按下键位 PAUSE              |
| EVENT_KEYDOWN_AUDIOMUTE            | 事件：按下键位 AUDIOMUTE        |
| EVENT_KEYDOWN_AUDIOPREV             | 事件：按下键位 AUDIOPREV         |
| EVENT_KEYDOWN_AUDIONEXT             | 事件：按下键位 AUDIONEXT        |
| EVENT_KEYDOWN_AUDIOPLAY             | 事件：按下键位 AUDIOPLAY        |
| EVENT_KEYDOWN_AUDIOSTOP             | 事件：按下键位 AUDIOSTOP         |
| EVENT_KEYDOWN_VOLUMEUP             | 事件：按下键位 VOLUMEUP        |
| EVENT_KEYDOWN_VOLUMEDOWN        | 事件：按下键位 VOLUMEDOWN   |
| EVENT_KEYDOWN_BRIGHTNESSUP          | 事件：按下键位 BRIGHTNESSUP    |
| EVENT_KEYDOWN_BRIGHTNESSDOWN   | 事件：按下键位 BRIGHTNESSUP    |
| EVENT_KEYDOWN_BACKQUOTE            | 事件：按下键位 BACKQUOTE        |
| EVENT_KEYDOWN_EXCLAM                 | 事件：按下键位 EXCLAM            |
| EVENT_KEYDOWN_AT                        | 事件：按下键位 AT                   |
| EVENT_KEYDOWN_HASH                    | 事件：按下键位 HASH               |
| EVENT_KEYDOWN_DOOLAR                 | 事件：按下键位 DOOLAR            |
| EVENT_KEYDOWN_CARET                    | 事件：按下键位 CARET               |
| EVENT_KEYDOWN_AMPERSAND           | 事件：按下键位 AMPERSAND       |
| EVENT_KEYDOWN_DBLAMPERSAND        | 事件：按下键位 DBLAMPERSAND |
| EVENT_KEYDOWN_ASTERISK                | 事件：按下键位 ASTERISK           |
| EVENT_KEYDOWN_LEFTPAREN              | 事件：按下键位 LEFTPAREN          |
| EVENT_KEYDOWN_RIGHTPAREN            | 事件：按下键位 RIGHTPAREN       |
| EVENT_KEYDOWN_MINUS                   | 事件：按下键位 MINUS              |
| EVENT_KEYDOWN_UNDERSCORE          | 事件：按下键位 UNDERSCORE      |
| EVENT_KEYDOWN_PLUS                     | 事件：按下键位 PLUS                |
| EVENT_KEYDOWN_EQUALS                  | 事件：按下键位 EQUALS             |
| EVENT_KEYDOWN_LEFTBRACKET           | 事件：按下键位 LEFTBRACKET       |
| EVENT_KEYDOWN_RIGHTBRACKET         | 事件：按下键位 RIGHTBRACKET    |
| EVENT_KEYDOWN_LEFTBRACE              | 事件：按下键位 LEFTBRACE         |
| EVENT_KEYDOWN_RIGHTBRACE            | 事件：按下键位 RIGHTBRACE        |
| EVENT_KEYDOWN_COLON                  | 事件：按下键位 COLON             |
| EVENT_KEYDOWN_SEMICOLON            | 事件：按下键位 SEMICOLON       |
| EVENT_KEYDOWN_BACKSLASH             | 事件：按下键位 BACKSLASH         |
| EVENT_KEYDOWN_QUOTE                   | 事件：按下键位 QUOTE              |
| EVENT_KEYDOWN_QUOTEDBL              | 事件：按下键位 QUOTEDBL         |
| EVENT_KEYDOWN_LESS                      | 事件：按下键位 LESS                 |
| EVENT_KEYDOWN_GREATER                | 事件：按下键位 GREATER           |
| EVENT_KEYDOWN_COMMA                 | 事件：按下键位 COMMA            |
| EVENT_KEYDOWN_PERIOD                  | 事件：按下键位 PERIOD             |
| EVENT_KEYDOWN_QUESTION              | 事件：按下键位 QUESTION           |
| EVENT_KEYDOWN_SLASH                   | 事件：按下键位 SLASH              |
| EVENT_KEYDOWN_VERTICALBAR           | 事件：按下键位 VERTICALBAR       |
| EVENT_KEYDOWN_DBLVERTICALBAR       | 事件：按下键位 DBLVERTICALBAR |
| EVENT_KEYDOWN_WWW                    | 事件：按下键位 WWW               |
| EVENT_KEYDOWN_EMAIL                    | 事件：按下键位 EMAIL               |
| EVENT_KEYUP_0                               | 事件：松开键位 0                     |
| EVENT_KEYUP_00                             | 事件：松开键位 00                   |
| EVENT_KEYUP_000                            | 事件：松开键位 000                  |
| EVENT_KEYUP_1                               | 事件：松开键位 1                     |
| EVENT_KEYUP_2                               | 事件：松开键位 2                     |
| EVENT_KEYUP_3                               | 事件：松开键位 3                     |
| EVENT_KEYUP_4                               | 事件：松开键位 4                     |
| EVENT_KEYUP_5                               | 事件：松开键位 5                     |
| EVENT_KEYUP_6                               | 事件：松开键位 6                     |
| EVENT_KEYUP_7                               | 事件：松开键位 7                     |
| EVENT_KEYUP_8                               | 事件：松开键位 8                     |
| EVENT_KEYUP_9                               | 事件：松开键位 9                     |
| EVENT_KEYUP_F1                             | 事件：松开键位 F1                   |
| EVENT_KEYUP_F2                             | 事件：松开键位 F2                   |
| EVENT_KEYUP_F3                             | 事件：松开键位 F3                   |
| EVENT_KEYUP_F4                             | 事件：松开键位 F4                   |
| EVENT_KEYUP_F5                             | 事件：松开键位 F5                   |
| EVENT_KEYUP_F6                             | 事件：松开键位 F6                   |
| EVENT_KEYUP_F7                             | 事件：松开键位 F7                   |
| EVENT_KEYUP_F8                             | 事件：松开键位 F8                   |
| EVENT_KEYUP_F9                             | 事件：松开键位 F9                   |
| EVENT_KEYUP_F10                            | 事件：松开键位 F10                  |
| EVENT_KEYUP_F11                            | 事件：松开键位 F11                  |
| EVENT_KEYUP_F12                            | 事件：松开键位 F12                  |
| EVENT_KEYUP_F13                            | 事件：松开键位 F13                  |
| EVENT_KEYUP_F14                            | 事件：松开键位 F14                  |
| EVENT_KEYUP_F15                            | 事件：松开键位 F15                  |
| EVENT_KEYUP_F16                            | 事件：松开键位 F16                  |
| EVENT_KEYUP_F17                            | 事件：松开键位 F17                  |
| EVENT_KEYUP_F18                            | 事件：松开键位 F18                  |
| EVENT_KEYUP_F19                            | 事件：松开键位 F19                  |
| EVENT_KEYUP_F20                            | 事件：松开键位 F20                  |
| EVENT_KEYUP_F21                            | 事件：松开键位 F21                  |
| EVENT_KEYUP_F22                            | 事件：松开键位 F22                  |
| EVENT_KEYUP_F23                            | 事件：松开键位 F23                  |
| EVENT_KEYUP_F24                            | 事件：松开键位 F24                  |
| EVENT_KEYUP_A                               | 事件：松开键位 A                     |
| EVENT_KEYUP_B                               | 事件：松开键位 B                     |
| EVENT_KEYUP_C                               | 事件：松开键位 C                     |
| EVENT_KEYUP_D                              | 事件：松开键位 D                    |
| EVENT_KEYUP_E                               | 事件：松开键位 E                     |
| EVENT_KEYUP_F                               | 事件：松开键位 F                     |
| EVENT_KEYUP_G                              | 事件：松开键位 G                    |
| EVENT_KEYUP_H                              | 事件：松开键位 H                    |
| EVENT_KEYUP_I                                | 事件：松开键位 I                      |
| EVENT_KEYUP_J                               | 事件：松开键位 J                     |
| EVENT_KEYUP_K                               | 事件：松开键位 K                     |
| EVENT_KEYUP_L                               | 事件：松开键位 L                     |
| EVENT_KEYUP_M                              | 事件：松开键位 M                    |
| EVENT_KEYUP_N                              | 事件：松开键位 N                    |
| EVENT_KEYUP_O                              | 事件：松开键位 O                    |
| EVENT_KEYUP_P                               | 事件：松开键位 P                     |
| EVENT_KEYUP_Q                              | 事件：松开键位 Q                    |
| EVENT_KEYUP_R                               | 事件：松开键位 R                     |
| EVENT_KEYUP_S                               | 事件：松开键位 S                     |
| EVENT_KEYUP_T                               | 事件：松开键位 T                     |
| EVENT_KEYUP_U                              | 事件：松开键位 U                    |
| EVENT_KEYUP_V                               | 事件：松开键位 V                     |
| EVENT_KEYUP_W                              | 事件：松开键位 W                    |
| EVENT_KEYUP_X                               | 事件：松开键位 X                     |
| EVENT_KEYUP_Y                               | 事件：松开键位 Y                     |
| EVENT_KEYUP_Z                               | 事件：松开键位 Z                     |
| EVENT_KEYUP_ESC                            | 事件：松开键位 ESC                  |
| EVENT_KEYUP_ENTER                         | 事件：松开键位 ENTER               |
| EVENT_KEYUP_BACKSPACE                  | 事件：松开键位 BACKSPACE         |
| EVENT_KEYUP_UP                             | 事件：松开键位 UP                   |
| EVENT_KEYUP_DOWN                        | 事件：松开键位 DOWN              |
| EVENT_KEYUP_LEFT                           | 事件：松开键位 LEFT                 |
| EVENT_KEYUP_RIGHT                         | 事件：松开键位 LIGHT               |
| EVENT_KEYUP_INSERT                        | 事件：松开键位 INSERT              |
| EVENT_KEYUP_DELETE                        | 事件：松开键位 DELETE              |
| EVENT_KEYUP_HOME                         | 事件：松开键位 HOME               |
| EVENT_KEYUP_END                           | 事件：松开键位 END                 |
| EVENT_KEYUP_PAGEUP                      | 事件：松开键位 PAGEUP            |
| EVENT_KEYUP_PAGEDOWN                 | 事件：松开键位 PAGEDOWN       |
| EVENT_KEYUP_LEFTCTRL                     | 事件：松开键位 LEFTCTRL           |
| EVENT_KEYUP_LEFTGUI                      | 事件：松开键位 LEFTGUI            |
| EVENT_KEYUP_LEFTALT                       | 事件：松开键位 LEFTALT             |
| EVENT_KEYUP_LEFTSHIFT                    | 事件：松开键位 LEFTSHIFT          |
| EVENT_KEYUP_RIGHTCTRL                   | 事件：松开键位 RIGHTCTRL         |
| EVENT_KEYUP_RIGHTGUI                    | 事件：松开键位 RIGHTGUI          |
| EVENT_KEYUP_RIGHTALT                    | 事件：松开键位 GIGHTALT          |
| EVENT_KEYUP_RIGHTSHIFT                  | 事件：松开键位 RIGHTSHIFT         |
| EVENT_KEYUP_SPACE                         | 事件：松开键位 SPACE               |
| EVENT_KEYUP_TAB                            | 事件：松开键位 TAB                  |
| EVENT_KEYUP_CAPSLOCK                   | 事件：松开键位 CAPSLOCK           |
| EVENT_KEYUP_NUMLOCK                   | 事件：松开键位 NUMLOCK           |
| EVENT_KEYUP_PRINTSCREEN                | 事件：松开键位 PRINTSCREEN      |
| EVENT_KEYUP_SCROLLLOCK                 | 事件：松开键位 SCROLLLOCK       |
| EVENT_KEYUP_PAUSE                        | 事件：松开键位 PAUSE              |
| EVENT_KEYUP_AUDIOMUTE                 | 事件：松开键位 AUDIOMUTE        |
| EVENT_KEYUP_AUDIOPREV                  | 事件：松开键位 AUDIOPREV         |
| EVENT_KEYUP_AUDIONEXT                  | 事件：松开键位 AUDIONEXT        |
| EVENT_KEYUP_AUDIOPLAY                  | 事件：松开键位 AUDIOPLAY        |
| EVENT_KEYUP_AUDIOSTOP                  | 事件：松开键位 AUDIOSTOP         |
| EVENT_KEYUP_VOLUMEUP                  | 事件：松开键位 VOLUMEUP        |
| EVENT_KEYUP_VOLUMEDOWN             | 事件：松开键位 VOLUMEDOWN   |
| EVENT_KEYUP_BRIGHTNESSUP             | 事件：松开键位 BRIGHTNESSUP    |
| EVENT_KEYUP_BRIGHTNESSDOWN          | 事件：松开键位 BRIGHTNESSUP    |
| EVENT_KEYUP_BACKQUOTE                 | 事件：松开键位 BACKQUOTE        |
| EVENT_KEYUP_EXCLAM                      | 事件：松开键位 EXCLAM            |
| EVENT_KEYUP_AT                             | 事件：松开键位 AT                   |
| EVENT_KEYUP_HASH                         | 事件：松开键位 HASH               |
| EVENT_KEYUP_DOOLAR                      | 事件：松开键位 DOOLAR            |
| EVENT_KEYUP_CARET                         | 事件：松开键位 CARET               |
| EVENT_KEYUP_AMPERSAND                | 事件：松开键位 AMPERSAND       |
| EVENT_KEYUP_DBLAMPERSAND              | 事件：松开键位 DBLAMPERSAND |
| EVENT_KEYUP_ASTERISK                     | 事件：松开键位 ASTERISK           |
| EVENT_KEYUP_LEFTPAREN                   | 事件：松开键位 LEFTPAREN          |
| EVENT_KEYUP_RIGHTPAREN                 | 事件：松开键位 RIGHTPAREN       |
| EVENT_KEYUP_MINUS                        | 事件：松开键位 MINUS              |
| EVENT_KEYUP_UNDERSCORE               | 事件：松开键位 UNDERSCORE      |
| EVENT_KEYUP_PLUS                          | 事件：松开键位 PLUS                |
| EVENT_KEYUP_EQUALS                       | 事件：松开键位 EQUALS             |
| EVENT_KEYUP_LEFTBRACKET                | 事件：松开键位 LEFTBRACKET       |
| EVENT_KEYUP_RIGHTBRACKET              | 事件：松开键位 RIGHTBRACKET    |
| EVENT_KEYUP_LEFTBRACE                   | 事件：松开键位 LEFTBRACE         |
| EVENT_KEYUP_RIGHTBRACE                 | 事件：松开键位 RIGHTBRACE        |
| EVENT_KEYUP_COLON                       | 事件：松开键位 COLON             |
| EVENT_KEYUP_SEMICOLON                 | 事件：松开键位 SEMICOLON       |
| EVENT_KEYUP_BACKSLASH                  | 事件：松开键位 BACKSLASH         |
| EVENT_KEYUP_QUOTE                        | 事件：松开键位 QUOTE              |
| EVENT_KEYUP_QUOTEDBL                   | 事件：松开键位 QUOTEDBL         |
| EVENT_KEYUP_LESS                           | 事件：松开键位 LESS                 |
| EVENT_KEYUP_GREATER                     | 事件：松开键位 GREATER           |
| EVENT_KEYUP_COMMA                      | 事件：松开键位 COMMA            |
| EVENT_KEYUP_PERIOD                       | 事件：松开键位 PERIOD             |
| EVENT_KEYUP_QUESTION                   | 事件：松开键位 QUESTION           |
| EVENT_KEYUP_SLASH                        | 事件：松开键位 SLASH              |
| EVENT_KEYUP_VERTICALBAR                | 事件：松开键位 VERTICALBAR       |
| EVENT_KEYUP_DBLVERTICALBAR           | 事件：松开键位 DBLVERTICALBAR |
| EVENT_KEYUP_WWW                         | 事件：松开键位 WWW               |
| EVENT_KEYUP_EMAIL                         | 事件：松开键位 EMAIL               |
| FONT_STYLE_BOLD                            | 字体样式：黑体                       |
| FONT_STYLE_ITALIC                           | 字体样式：斜体                       |
| FONT_STYLE_UNDERLINE                    | 字体样式：下划线                     |
| FONT_STYLE_STRIKETHROUGH              | 字体样式：删除线                     |
| FONT_STYLE_NORMAL                       | 字体样式：默认                       |
| MUSIC_TYPE_WAV                            | 音乐类型：WAV                      |
| MUSIC_TYPE_MP3                             | 音乐类型：MP3                       |
| MUSIC_TYPE_OGG                            | 音乐类型：OGG                      |
| MUSIC_TYPE_CMD                            | 音乐类型：CMD                      |
| MUSIC_TYPE_MOD                            | 音乐类型：MOD                      |
| MUSIC_TYPE_MID                             | 音乐类型：MID                       |
| MUSIC_TYPE_UNKONWN                    | 音乐类型：未知                       |




