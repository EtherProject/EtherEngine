### [[ << 回到上层 ]](README.md)

# Response:SetHeaders

> 设置响应头

```lua

response:SetHeaders(headers)

```

## 参数：

+ response [userdata-Request]：响应数据对象数据
+ headers [table]：响应头

## 返回值：

无

## 备注

+ 由于 Lua 的 table 不支持一键多值，所以当响应头中一个键对应多个值时，返回表中对应的键将保存最后一个值，请使用 [SetHeaderValue](_Response_SetHeaderValue_.md) 函数为同一个键设置不同值

## 示例

```lua

```