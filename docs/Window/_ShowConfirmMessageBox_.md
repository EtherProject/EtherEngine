### [[ << 回到上层 ]](README.md)

# ShowConfirmMessageBox

> 显示模态的确认信息窗口

```lua

flag = ShowConfirmMessageBox(type, title, content [, ok_text, cancel_text])

```

## 参数：

+ type [Macro number]：窗口类型，可选值为：

    + MSGBOX_ERROR：错误
    + MSGBOX_WARNING：警告
    + MSGBOX_INFO：提示

+ title [string]：提示窗口标题
+ content [string]：提示信息内容
+ ok_text [string]：确认按钮文本，可选
+ cancel_text [string]：取消按钮文本，可选

## 返回值：

+ flag [boolean]：确认则返回 true，否则选择 false

## 示例

```lua

```