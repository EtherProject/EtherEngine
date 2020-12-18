# Ether时间相关操作
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
