### [[ << 回到上层 ]](index.md)

# Server:Get

> 配置服务端的 Get 请求路由及对应的回调函数

```lua

server:Get(route, callback)

```

## 参数：

+ server [userdata-Server]：服务端数据
+ route [string]：路由
+ callback [function]：回调函数

## 返回值：

无

## 备注

+ 路由支持正则表达式
+ 回调函数接受2个参数：请求数据对象数据（userdata-Request），响应数据对象数据（userdata-Response）

## 示例

```lua

```