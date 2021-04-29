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

        + POWERSTATE_UNKOWN：无法确定当前供电状态
        + POWERSTATE_ONBATTERY：没有接通电源，正在使用电池供电
        + POWERSTATE_NOBATTERY：电源接通，电池不可用
        + POWERSTATE_CHARGING：电源接通，电池正在充电
        + POWERSTATE_CHARGEDN：电源接通，电池充电完毕

    + remain_time [number]：成功则为剩余使用时长（number），单位为秒，失败或当前不是电池供电则为 -1（number）
    + remain_percentage [number]：成功则返回剩余电量百分比（number），取值范围为 0 - 100，失败则为 -1（number）


## 示例

```lua

```