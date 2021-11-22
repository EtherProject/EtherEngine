### [[ << 回到上层 ]](README.md)

# Request:GetParams

> 获取请求参数

```lua

params = request:GetParams()

```

## 参数：

+ request [userdata-Request]：请求数据对象数据

## 返回值：

+ params [table]：请求参数

## 备注

+ 由于 Lua 的 table 不支持一键多值，所以当请求参数中一个键对应多个值时，返回表中对应的键将保存最后一个值，请使用带索引参数的 [GetParamValue](_Request_GetParamValue_.md) 函数获取同一个键对应的不同值

## 示例

```lua

```