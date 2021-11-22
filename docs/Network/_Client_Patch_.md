### [[ << 回到上层 ]](README.md)

# Client:Patch

> 使用 Patch 方法请求某路由

```lua

response = client:Patch(data)

```

## 参数：

+ client [userdata-Client]：客户端数据
+ data [table]：请求数据，结构如下：

    + route [string]：路由，
    + headers [table]：请求头（可选，默认为空或默认请求头）
    + params [string]：请求参数（可选，默认为空）
    + type [string]：文档的 MIME Type（可选，默认为 “application/x-www-form-urlencoded”）

## 返回值：

+ response [table]：响应数据，结构见 [附录](appendix.md)

## 示例

```lua

```