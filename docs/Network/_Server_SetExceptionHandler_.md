### [[ << 回到上层 ]](index.md)

# Server:SetExceptionHandler

> 设置服务端的异常处理函数

```lua

server:SetExceptionHandler(callback)

```

## 参数：

+ server [userdata-Server]：服务端数据
+ callback [function]：异常处理回调函数

## 返回值：

无

## 备注

+ 回调函数接受3个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response），异常信息（string）

## 示例

```lua

```