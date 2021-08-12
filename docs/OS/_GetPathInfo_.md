### [[ << 回到上层 ]](README.md)

# GetPathInfo

> 获取指定路径的信息

```lua

info = GetPathInfo(path)

```

## 参数：

+ path [string]：目录或文件所在的路径

## 返回值：

+ info [table]：成功则返回路径信息，表内成员如下，失败则返回nil：

    + name [string]：文件名
    + size [number]：文件大小，单位为字节
    + time [table]：时间信息，表内成员如下：

        + create [number]：创建时间，单位为毫秒
        + access [number]：最后一次访问时间，单位为毫秒
        + write [number]：最后一次修改时间，单位为毫秒

    + attributes [table]：文件属性，成员可以为以下样式中的一种或多种：

        + FILEATTRIB_ARCH：存档
        + FILEATTRIB_HIDDEN：隐藏
        + FILEATTRIB_NORMAL：正常
        + FILEATTRIB_RDONLY：只读
        + FILEATTRIB_SUBDIR：文件夹
        + FILEATTRIB_SYSTEM：系统

## 示例

```lua

```