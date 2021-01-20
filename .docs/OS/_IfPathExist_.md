### [[ << 回到上层 ]](index.md)

# IfPathExist

> 判断指定路径是否存在

```lua

flag = IfPathExist(path [, mode])

```

## 参数：

+ path [string]：目录或文件所在的路径
+ mode [Macro number]：判断模式，可选，默认为 PATHMODE_FILEANDDIR，可以是以下选项：

    + PATHMODE_FILE：文件模式
    + PATHMODE_DIR：目录模式
    + PATHMODE_FILEANDDIR：文件和目录模式

## 返回值：

+ flag [bolean]：是否存在

## 示例

```lua

```