### [[ << 回到主页 ]](../README.md)

# Network

> Network 模块提供网络相关API

## 模块函数列表：

+ [SplitLink(link)](_SplitLink_.md)：将 HTTP/HTTPS 链接分割为：主机地址、路由和参数

+ [CreateClient(domain)](_CreateClient_.md)：创建客户端

+ [CreateServer([cert, key])](_CreateServer_.md)：创建服务端

## 对象成员函数列表：

+ Client 对象成员函数：

    + [Client:CheckValid()](_Client_CheckValid_.md)：判断客户端是否创建成功

    + [Client:Get(data)](_Client_Get_.md)：使用 Get 方法请求某路由

    + [Client:Post(data)](_Client_Post_.md)：使用 Post 方法请求某路由

    + [Client:Put(data)](_Client_Put_.md)：使用 Put 方法请求某路由

    + [Client:Patch(data)](_Client_Patch_.md)：使用 Patch 方法请求某路由

    + [Client:Delete(data)](_Client_Delete_.md)：使用 Delete 方法请求某路由

    + [Client:Options(data)](_Client_Options_.md)：使用 Options 方法请求某路由

    + [Client:SetDefaultHeaders(headers)](_Client_SetDefaultHeaders_.md)：设置客户端的默认请求头

    + [Client:SetConnectTimeout(delay)](_Client_SetConnectTimeout_.md)：设置客户端的连接超时时间

    + [Client:SetReadTimeout(delay)](_Client_SetReadTimeout_.md)：设置客户端的资源读取超时时间

    + [Client:SetWriteTimeout(delay)](_Client_SetWriteTimeout_.md)：设置客户端的资源写入超时时间

    + [Client:SetKeepAlive(flag)](_Client_SetKeepAlive_.md)：设置客户端是否保持连接

    + [Client:SetFollowRedirect(flag)](_Client_SetFollowRedirect_.md)：设置客户端是否跟随重定向

    + [Client:SetCompressRequest(flag)](_Client_SetCompressRequest_.md)：设置客户端是否压缩请求数据

    + [Client:SetCompressResponse(flag)](_Client_SetCompressResponse_.md)：设置客户端是否压缩响应数据

    + [Client:SetCACertPath(path)](_Client_SetCACertPath_.md)：设置客户端 CACert 的 SSL 数字证书路径

    + [Client:SetProxy(host, port)](_Client_SetProxy_.md)：设置客户端的代理主机

+ Server 对象成员函数：

    + [Server:CheckValid()](_Server_CheckValid_.md)：判断服务端是否创建成功

    + [Server:CheckRunning()](_Server_CheckRunning_.md)：判断服务端是否正在运行

    + [Server:Get(route, callback)](_Server_Get_.md)：配置服务端的 Get 请求路由及对应的回调函数

    + [Server:Post(route, callback)](_Server_Post_.md)：配置服务端的 Post 请求路由及对应的回调函数

    + [Server:Put(route, callback)](_Server_Put_.md)：配置服务端的 Put 请求路由及对应的回调函数

    + [Server:Patch(route, callback)](_Server_Patch_.md)：配置服务端的 Patch 请求路由及对应的回调函数

    + [Server:Delete(route, callback)](_Server_Delete_.md)：配置服务端的 Delete 请求路由及对应的回调函数

    + [Server:Options(route, callback)](_Server_Options_.md)：配置服务端的 Options 请求路由及对应的回调函数

    + [Server:SetMountPoint(mount, path)](_Server_SetMountPoint_.md)：添加服务端的静态资源挂载点

    + [Server:RemoveMountPoint(mount)](_Server_RemoveMountPoint_.md)：移除服务端指定的静态资源挂载点

    + [Server:SetFileExtMapToMIMEType(ext, type)](_Server_SetFileExtMapToMIMEType_.md)：设置服务端的静态资源文件扩展名和响应的 MIME 类型映射

    + [Server:SetExceptionHandler(callback)](_Server_SetExceptionHandler_.md)：设置服务端的异常处理函数

    + [Server:SetMaxKeepAliveCount(count)](_Server_SetMaxKeepAliveCount_.md)：设置服务端的最大连接保持数

    + [Server:SetKeepAliveTimeout(delay)](_Server_SetKeepAliveTimeout_.md)：设置服务端的连接保持超时时间

    + [Server:SetReadTimeout(delay)](_Server_SetReadTimeout_.md)：设置服务端的资源读取超时时间
    
    + [Server:SetWriteTimeout(delay)](_Server_SetWriteTimeout_.md)：设置服务端的资源写入超时时间

    + [Server:SetIdleInterval(delay)](_Server_SetIdleInterval_.md)：设置服务端的空闲间隔超时时间
    
    + [Server:SetMaxRequestLength(length)](_Server_SetMaxRequestLength_.md)：设置服务端接收的请求体数据的最大长度

    + [Server:BindToAnyPort()](_Server_BindToAnyPort_.md)：将当前服务端绑定到任意可用的端口上

    + [Server:ListenAfterBind()](_Server_ListenAfterBind_.md)：启动已绑定端口的服务端的监听

    + [Server:Listen(host, port)](_Server_Listen_.md)：启动服务端监听

    + [Server:Stop()](_Server_Stop_.md)：停止服务端监听

+ Request 对象成员函数：

    + [Request:GetMethod()](_Request_GetMethod_.md)：获取请求方法
    
    + [Request:GetRoute()](_Request_GetRoute_.md)：获取请求路由
        
    + [Request:GetHeaders()](_Request_GetHeaders_.md)：获取请求头
        
    + [Request:GetBody()](_Request_GetBody_.md)：获取请求体
        
    + [Request:GetRemoteAddress()](_Request_GetRemoteAddress_.md)：获取远程主机地址
        
    + [Request:GetRemotePort()](_Request_GetRemotePort_.md)：获取远程主机端口号
        
    + [Request:GetVersion()](_Request_GetVersion_.md)：获取请求的 HTTP 版本
        
    + [Request:GetParams()](_Request_GetParams_.md)：获取请求参数
        
    + [Request:CheckHeaderKeyExist(key)](_Request_CheckHeaderKeyExist_.md)：判断请求头中指定键是否存在
        
    + [Request:GetHeaderValue(key [, index])](_Request_GetHeaderValue_.md)：获取请求头中指定键对应的值
        
    + [Request:GetHeaderValueCount(key)](_Request_GetHeaderValueCount_.md)：获取请求头中指定键对应的值的个数
        
    + [Request:CheckParamKeyExist(key)](_Request_CheckParamKeyExist_.md)：判断请求参数中指定键是否存在
        
    + [Request:GetParamValue(key [, index])](_Request_GetParamValue_.md)：获取请求参数中指定键对应的值

    + [Request:GetParamValueCount(key)](_Request_GetParamValueCount_.md)：获取请求参数中指定键对应的值的个数
    
+ Response 对象成员函数：

    + [Response:SetVersion(version)](_Response_SetVersion_.md)：设置响应的 HTTP 版本
    
    + [Response:SetStatus(status)](_Response_SetStatus_.md)：设置响应的状态码
    
    + [Response:GetHeaders(headers)](_Response_GetHeaders_.md)：获取响应头
    
    + [Response:SetBody(body)](_Response_SetBody_.md)：设置响应体
    
    + [Response:CheckHeaderKeyExist(key)](_Response_CheckHeaderKeyExist_.md)：判断响应头中指定键是否存在
    
    + [Response:GetHeaderValue(key [, index])](_Response_GetHeaderValue_.md)：获取响应头中指定键对应的值
    
    + [Response:GetHeaderValueCount(key)](_Response_GetHeaderValueCount_.md)：获取响应头中指定键对应的值的个数
    
    + [Response:SetHeaderValue(key, value)](_Response_SetHeaderValue_.md)：设置响应头中指定键对应的值
    
    + [Response:SetHeaders(headers)](_Response_SetHeaders_.md)：设置响应头
    
    + [Response:SetRedirect(url)](_Response_SetRedirect_.md)：设置响应的重定向
    
    + [Response:SetContent(content [, type])](_Response_SetContent_.md)：设置响应的内容