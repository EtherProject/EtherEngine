### [[ << 回到上层 ]](index.md)

# Request:GetHeaders

> 获取请求头

```lua

headers = request:GetHeaders()

```

## 参数：

+ request [userdata-Request]：请求数据对象数据

## 返回值：

+ headers [table]：请求头

## 备注

+ 由于 Lua 的 table 不支持一键多值，所以当请求头中一个键对应多个值时，返回表中对应的键将保存最后一个值，请使用带索引参数的 [GetHeaderValue](_Request_GetHeaderValue_.md) 函数获取同一个键对应的不同值

## 示例

```lua

```