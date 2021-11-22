### [[ << 回到上层 ]](README.md)

# CreateServer

> 创建服务端

```lua

server = CreateClient([cert, key])

```

## 参数：

+ cert [string]：SSL 服务端的证书文件路径，可选
+ key [string]：SSL 服务端的私钥文件路径，可选

## 返回值：

+ server [userdata-Server]：服务端数据

## 备注：

+ 在不使用证书和私钥进行服务端创建的默认类型服务端不支持 HTTPS 协议

## 示例

```lua

```