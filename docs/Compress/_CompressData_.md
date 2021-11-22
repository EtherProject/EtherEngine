### [[ << 回到上层 ]](README.md)

# CompressData

> 压缩数据

```lua

data = CompressData(raw_data, level)

```

## 参数：

+ raw_data [string]：原始数据
+ level [number]：压缩等级，可选，范围为 1-10，默认为6

## 返回值：

+ data [string]：压缩后数据

## 备注

在原始数据相同的一般情况下，压缩等级越高，耗时越长且压缩率越小；特别地，压缩等级为1只归档数据为压缩格式，并不进行压缩处理

## 示例

```lua

```
