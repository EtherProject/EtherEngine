# Ether图形相关操作

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

> ## UnloadFont
释放已加载的字体
```lua
UnloadFont(font)
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

> ## SetFontStyle
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
