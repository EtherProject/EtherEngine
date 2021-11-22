### [[ << 回到上层 ]](README.md)

# SplitLink

> 将 HTTP/HTTPS 链接分割为：主机地址、路由和参数

```lua

domain, route, param = SplitLink(link)

```

## 参数：

+ link [string]：HTTP/HTTPS 链接

## 返回值：

+ domain [string]：主机地址，默认为空字符串
+ route [string]：路由，默认为 “/”
+ param [string]：参数，默认为空字符串

## 示例

```lua

```