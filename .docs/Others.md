# Ether其它功能
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