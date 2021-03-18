### [[ << 回到上层 ]](index.md)

# RequestGet

> 使用Get请求访问指定链接

```lua

response = RequestGet(link [, headers])

```

## 参数：

+ link [string]：链接
+ headers [table]：HttpHeaders，可选，默认为空

## 返回值：

+ response [table]：成功则返回Response表，表内成员如下，失败则返回nil：

    + status [number]：状态码
    + headers [table]：响应头
    + body [string]：正文

## 示例

```lua

```