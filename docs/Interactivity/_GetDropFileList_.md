### [[ << 回到上层 ]](README.md)

# GetDropFileList

> 获取当前这一组拖放的文件路径

## 参数：

无

## 返回值：

+ 一组拖放文件的路径

## 备注

+ 仅当事件类型为`EVENT_DROPFILE_READY`时，该函数有意义

## 示例

```lua
-- 在主事件循环中
if event_type == EVENT_DROPFILE_READY then
	droppedfiles = GetDropFileList()
	for _, path in pairs(droppedfiles) do
		-- 处理各个文件
	end
end
```