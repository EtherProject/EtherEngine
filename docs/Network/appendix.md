# 附录

> HTTP/HTTPS 请求响应数据表结构：

+ error [number]：错误代码，可能是如下值：

    + ERRCODE_SUCCESS：请求成功
    + ERRCODE_UNKNOWN：未知错误
    + ERRCODE_CONNECTION：连接错误
    + ERRCODE_BINDIPADDRESS：IP 绑定错误
    + ERRCODE_READ：资源读取错误
    + ERRCODE_WRITE：错误写入错误
    + ERRCODE_EXCEEDREDRICTCOUNT：重定向次数过多
    + ERRCODE_CANCELED：请求取消
    + ERRCODE_SSLCONNECTION：SSL 连接错误
    + ERRCODE_SSLLOADINGCERTS：加载 SSL 证书错误
    + ERRCODE_SSLSERVERVERIFY：SSL 服务器验证错误
    + ERRCODE_UNSUPPORTEDMBC：不支持的多部分边界字符（Multipart Boundary Chars）
    + ERRCODE_COMPRESSION：压缩错误

+ status [number/nil]：状态码，失败则为 nil

+ body [string/nil]：响应数据，失败则为 nil

+ headers [table/nil]：响应头，失败则为 nil