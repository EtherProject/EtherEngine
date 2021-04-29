### [[ << 回到上层 ]](index.md)

# GetPowerInfo

> 获取设备当前电源信息

```lua

info = GetPowerInfo()

```

## 参数：

无

## 返回值：

+ info [table]：设备当前电源信息，表内成员如下：

    
    + state [Macro number]：供电状态，值可以为以下状态之一：

        + FILEATTRIB_ARCH：存档
        + FILEATTRIB_HIDDEN：隐藏
        + FILEATTRIB_NORMAL：正常
        + FILEATTRIB_RDONLY：只读
        + FILEATTRIB_SUBDIR：文件夹
        + FILEATTRIB_SYSTEM：系统

    + remain_time [number]：成功则为剩余使用时长（number），单位为秒，失败或当前不是电池供电则为 -1（number）
    + remain_percentage [number]：成功则返回剩余电量百分比（number），取值范围为 0 - 100，失败则为 -1（number）


## 示例

```lua

```