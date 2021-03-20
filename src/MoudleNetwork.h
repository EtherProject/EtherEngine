#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "Moudle.h"
#include "Macros.h"

#include <lua.hpp>
#include <httplib.h>
using namespace httplib;

#define MIMETYPE_CSS 1315
#define MIMETYPE_CSV 1316
#define MIMETYPE_TEXT 1317
#define MIMETYPE_VTT 1318
#define MIMETYPE_HTML 1319
#define MIMETYPE_APNG 1320
#define MIMETYPE_SVG 1321
#define MIMETYPE_WEBP 1322
#define MIMETYPE_ICO 1323
#define MIMETYPE_TIFF 1324
#define MIMETYPE_JPG 1325
#define MIMETYPE_AVIF 1326
#define MIMETYPE_BMP 1327
#define MIMETYPE_GIF 1328
#define MIMETYPE_PNG 1329
#define MIMETYPE_MP4 1330
#define MIMETYPE_MPEG 1331
#define MIMETYPE_WEBM 1332
#define MIMETYPE_MPGA 1333
#define MIMETYPE_WEBA 1334
#define MIMETYPE_WAV 1335
#define MIMETYPE_OTF 1336
#define MIMETYPE_TTF 1337
#define MIMETYPE_WOFF 1338
#define MIMETYPE_WOFF2 1339
#define MIMETYPE_7Z 1340
#define MIMETYPE_ATOM 1341
#define MIMETYPE_PDF 1342
#define MIMETYPE_JS 1343
#define MIMETYPE_JSON 1344
#define MIMETYPE_RSS 1345
#define MIMETYPE_TAR 1346
#define MIMETYPE_XHTML 1347
#define MIMETYPE_XSLT 1348
#define MIMETYPE_XML 1349
#define MIMETYPE_GZ 1350
#define MIMETYPE_ZIP 1351
#define MIMETYPE_WASM 1352
#define MIMETYPE_MP3 1353

/// <summary>
/// 从链接中获取域名
/// </summary>
/// <param name="link">链接</param>
/// <returns>域名</returns>
string GetLinkDomain(string link);

/// <summary>
/// 从链接中获取路由
/// </summary>
/// <param name="link">链接</param>
/// <returns>路由</returns>
string GetLinkRoute(string link);

/// <summary>
/// 将指定的Response表压入当前Lua虚拟栈
/// </summary>
/// <param name="L">当前Lua虚拟机环境</param>
/// <param name="response">Response表</param>
void PushResponseTable(lua_State* L, Result result);

/// <summary>
/// 将宏转换为 MIME Type
/// </summary>
/// <param name="macro">宏</param>
/// <returns>MIME Type</returns>
string ConvertMacroToMIMEType(int macro);

/*
* 从链接中获取域名
* 1参数：链接（string）
* 1返回值：域名（string）
*/
ETHER_API getLinkDomain(lua_State* L);

/*
* 从链接中获取路由
* 1参数：链接（string）
* 1返回值：路由（string）
*/
ETHER_API getLinkRoute(lua_State* L);

/*
* 使用Get请求访问指定链接
* 1或2参数：链接（string），【可选】HttpHeaders（table）
* 1返回值：成功则返回Response表（table）：
	{
		statue：状态码（number），
		headers：响应头（table），
		body：正文（string），
	}
* ，失败则返回nil
*/

ETHER_API requestGet(lua_State* L);

/*
* 使用Post请求向指定链接发送数据
* 3或4参数：链接（string），数据体（string），MIME Type（Macro number），【可选】HttpHeaders（table）
* 1返回值：成功则返回Response表（table，表结构如下）:
	{
		statue：状态码（number），
		headers：响应头（table），
		body：正文（string），
	}
* ，失败则返回nil
*/
ETHER_API requestPost(lua_State* L);


class MoudleNetwork : public Moudle
{
public:
	MoudleNetwork(lua_State* L, string name);
	~MoudleNetwork() {};

};

#endif // !_NETWORK_H_

