### [[ << 回到上层 ]](index.md)

# RequestPost

> 使用Post请求向指定链接发送数据

```lua

response = RequestPost(link, data, type [, headers])

```

## 参数：

+ link [string]：链接
+ data [string]：数据体
+ type [Macro number]：MIME Type，可选值如下：

    + MIMETYPE_CSS：CSS资源
    + MIMETYPE_CSV：CSV资源
    + MIMETYPE_TEXT：TEXT资源
    + MIMETYPE_VTT：VTT资源
    + MIMETYPE_HTML：HTML资源
    + MIMETYPE_APNG：APNG资源
    + MIMETYPE_SVG：SVG资源
    + MIMETYPE_WEBP：WEBP资源
    + MIMETYPE_ICO：ICO资源
    + MIMETYPE_TIFF：TIFF资源
    + MIMETYPE_JPG：JPG资源
    + MIMETYPE_AVIF：AVIF资源
    + MIMETYPE_BMP：BMP资源
    + MIMETYPE_GIF：GIF资源
    + MIMETYPE_PNG：PNG资源
    + MIMETYPE_MP4：MP4资源
    + MIMETYPE_MPEG：MPEG资源
    + MIMETYPE_WEBM：WEBM资源
    + MIMETYPE_MPGA：MPGA资源
    + MIMETYPE_WEBA：WEBA资源
    + MIMETYPE_WAV：WAV资源
    + MIMETYPE_OTF：OTF资源
    + MIMETYPE_TTF：TTF资源
    + MIMETYPE_WOFF：WOFF资源
    + MIMETYPE_WOFF2：WOFF2资源
    + MIMETYPE_7Z：7Z资源
    + MIMETYPE_ATOM：ATOM资源
    + MIMETYPE_PDF：PDF资源
    + MIMETYPE_JS：JS资源
    + MIMETYPE_JSON：JSON资源
    + MIMETYPE_RSS：RSS资源
    + MIMETYPE_XHTML：XHTML资源
    + MIMETYPE_XSLT：XSLT资源
    + MIMETYPE_XML：XML资源
    + MIMETYPE_GZ：GZ资源
    + MIMETYPE_ZIP：ZIP资源
    + MIMETYPE_WASM：WASM资源
    + MIMETYPE_MP3：MP3资源

+ headers [table]：HttpHeaders，可选，默认为空

## 返回值：

+ response [table]：成功则返回Response表，表内成员如下，失败则返回nil：

    + statue [number]：状态码
    + headers [table]：响应头
    + body [string]：正文

## 示例

```lua

```