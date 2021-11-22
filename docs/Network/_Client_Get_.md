### [[ << 回到上层 ]](README.md)

# Client:Get

> 使用 Get 方法请求某路由

```lua

response = client:Get(data)

```

## 参数：

+ client [userdata-Client]：客户端数据
+ data [table]：请求数据，结构如下：

    + route [string]：路由，
    + headers [table]：请求头（可选，默认为空或默认请求头）

## 返回值：

+ response [table]：响应数据，结构见 [附录](appendix.md)

## 示例

```lua

```