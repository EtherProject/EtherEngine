#  Ether交互事件处理
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