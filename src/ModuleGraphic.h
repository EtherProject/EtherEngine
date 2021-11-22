#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "Module.h"
#include "Macros.h"
#include "Utils.h"

#include "lua.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define FONT_STYLE_BOLD						1303
#define FONT_STYLE_ITALIC					1304
#define FONT_STYLE_UNDERLINE				1305
#define FONT_STYLE_STRIKETHROUGH			1306
#define FONT_STYLE_NORMAL					1307

#define FLIP_HORIZONTAL						1010
#define FLIP_VERTICAL						1011
#define FLIP_NONE							1012

#define METANAME_IMAGE						"Graphic.Image"
#define METANAME_TEXTURE					"Graphic.Texture"
#define METANAME_FONT						"Graphic.Font"

#define GetImageDataAt1stPos()				(SDL_Surface*)(*(void**)luaL_checkudata(L, 1, METANAME_IMAGE))
#define GetTextureDataAt1stPos()			(SDL_Texture*)(*(void**)luaL_checkudata(L, 1, METANAME_TEXTURE))
#define GetFontDataAt1stPos()				(TTF_Font*)(*(void**)luaL_checkudata(L, 1, METANAME_FONT))

#define CheckImageDataAt1stPos(surface)		luaL_argcheck(L, surface, 1, "get image data failed")
#define CheckTextureDataAt1stPos(texture)	luaL_argcheck(L, texture, 1, "get texture data failed")
#define CheckFontDataAt1stPos(font)			luaL_argcheck(L, font, 1, "get font data failed")

class ModuleGraphic : public Module
{
public:
	static ModuleGraphic& Instance();
	~ModuleGraphic() {};

private:
	ModuleGraphic();
};

extern SDL_Renderer* renderer;

// ��������Ƿ���ʾ
// 1�������Ƿ���ʾ��boolean��
// 0����ֵ
ETHER_API setCursorShow(lua_State * L);

// ���ļ��м���ͼ��
// 1������ͼ���ļ�·����string��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API loadImageFromFile(lua_State * L);

// �ӻ������м���ͼ��
// 1���������������ݣ�string��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API loadImageFromData(lua_State* L);

// ���õ�ͼƬ�ļ��Ƿ�����ָ����ColorKey�����õ�Color����͸����
// 3������ͼ�����ݣ�userdata-IMAGE�����Ƿ����ã�boolean����ColorKey��table��
// 0����ֵ
ETHER_API image_SetColorKey(lua_State * L);

// ͼ������GC����
// 1������ͼ�����ݣ�userdata-IMAGE��
// 0����ֵ
ETHER_API __gc_Image(lua_State * L);

// ��ͼ�����ݴ������ڴ��ڵĿ���Ⱦ����
// 1������ͼ�����ݣ�userdata-IMAGE��
// 1����ֵ���������ݣ�userdata-TEXTURE��
ETHER_API createTexture(lua_State * L);

// ��������GC����
// 1�������������ݣ�userdata-TEXTURE��
// 0����ֵ
ETHER_API __gc_Texture(lua_State * L);

// ��������͸����
// 2�������������ݣ�userdata-TEXTURE����͸������ֵ��number��ȡֵ��Χ0-255��
// 0����ֵ
ETHER_API texture_SetAlpha(lua_State * L);

// ��ȡ�Ѽ���ͼ��ߴ�
// 1������ͼ�����ݣ�userdata-IMAGE��
// 2����ֵ��ͼ���ȣ�number����ͼ��߶ȣ�number��
ETHER_API image_GetSize(lua_State * L);

// ������������Ⱦ��������
// 2�������������ݣ�userdata-TEXTURE��������������ʾ����ľ��Σ�table��
// 0����ֵ
ETHER_API copyTexture(lua_State * L);

// ����ת�������������Ⱦ��������
// 5�������������ݣ�userdata-TEXTURE������ת�Ƕȣ�number������ת�������꣨table������תģʽ��table��������������ʾ����ľ��Σ�table��
// 0����ֵ
ETHER_API copyRotateTexture(lua_State * L);

// ���ü��������������Ⱦ��������
// 3�������������ݣ�userdata-TEXTURE�������������ü�����ľ��Σ�table��������������ʾ����ľ��Σ�table��
// 0����ֵ
ETHER_API copyReshapeTexture(lua_State * L);

// ����ת�Ҳü��������������Ⱦ��������
// 6�������������ݣ�userdata-TEXTURE������ת�Ƕȣ�number������ת�������꣨table������תģʽ��table�������������ü�����ľ��Σ�table��������������ʾ����ľ��Σ�table��
// 0����ֵ
ETHER_API copyRotateReshapeTexture(lua_State * L);

// ���ô��ڻ�ͼ��ɫ
// 1������������ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 0����ֵ
ETHER_API setDrawColor(lua_State * L);

// ��ȡ���ڻ�ͼ��ɫ
// 0����
// 1����ֵ������������ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
ETHER_API getDrawColor(lua_State * L);

// ��ָ��λ�û��Ƶ�
// 1�����������꣨table��
// 0����ֵ
ETHER_API drawPoint(lua_State * L);

// ��ָ��λ�û���ֱ��
// 2������������꣨table�����յ����꣨table��
// 0����ֵ
ETHER_API drawLine(lua_State * L);

// ��ָ��λ�û��ƴ�ֱ��
// 3������������꣨table�����յ����꣨table����������ȣ�number��
// �޷���ֵ
ETHER_API drawThickLine(lua_State * L);

// ��ָ��λ�û�����������
// 1����������������ʾ����ľ��Σ�table��
// 0����ֵ
ETHER_API drawRectangle(lua_State * L);

// ��ָ��λ�û���������
// 1����������������ʾ����ľ��Σ�table��
// 0����ֵ
ETHER_API drawFillRectangle(lua_State * L);

// ��ָ��λ�û���Բ����������
// 2����������������ʾ����ľ��Σ�table����Բ�ǰ뾶��С��number��
// 0����ֵ
ETHER_API drawRoundRectangle(lua_State * L);

// ��ָ��λ�û���Բ��������
// 2����������������ʾ����ľ��Σ�table����Բ�ǰ뾶��С��number��
// 0����ֵ
ETHER_API drawFillRoundRectangle(lua_State * L);

// ��ָ��λ�û��������Բ��
// 2������Բ�����꣨table����Բ�뾶��number��
// 0����ֵ
ETHER_API drawCircle(lua_State * L);

// ��ָ��λ�û������Բ��
// 2������Բ�����꣨table����Բ�뾶��number��
// 0����ֵ
ETHER_API drawFillCircle(lua_State * L);

// ��ָ��λ�û����������Բ
// 3��������Բ�������꣨table������Բx��뾶��number������Բy��뾶��number��
// 0����ֵ
ETHER_API drawEllipse(lua_State * L);

// ��ָ��λ�û��������Բ
// 3��������Բ�������꣨table������Բx��뾶��number������Բy��뾶��number��
// 0����ֵ
ETHER_API drawFillEllipse(lua_State * L);

// ��ָ��λ�û������������
// 4��������������Բ��Բ�����꣨table������������Բ�İ뾶��number�������ο�ʼ�Ƕȣ�number�������ν����Ƕȣ�number�������δ���������Բ��Ϊԭ��Ķ�ά�ѿ�������ϵ��x��������ʼ���ƣ��Ƕȵ�������Ϊ˳ʱ�뷽��
// 0����ֵ
ETHER_API drawPie(lua_State * L);

// ��ָ��λ�û����������
// 4��������������Բ��Բ�����꣨table������������Բ�İ뾶��number�������ο�ʼ�Ƕȣ�number�������ν����Ƕȣ�number�������δ���������Բ��Ϊԭ��Ķ�ά�ѿ�������ϵ��x��������ʼ���ƣ��Ƕȵ�������Ϊ˳ʱ�뷽��
// 0����ֵ
ETHER_API drawFillPie(lua_State * L);

// ��ָ��λ�û��������������
// 6��������һ���������꣨table�����ڶ����������꣨table�����������������꣨table��
// 0����ֵ
ETHER_API drawTriangle(lua_State * L);

// ��ָ��λ�û������������
// 6��������һ���������꣨table�����ڶ����������꣨table�����������������꣨table��
// 0����ֵ
ETHER_API drawFillTriangle(lua_State * L);

// ���ļ��м�������
// 2�����������ļ�·����string���������С��number��
// 1����ֵ���ɹ��򷵻��������ݣ�userdata-FONT����ʧ���򷵻�nil
ETHER_API loadFontFromFile(lua_State * L);

// �ӻ������м�������
// 2���������������ݣ�string���������С��number��
// 1����ֵ���ɹ��򷵻��������ݣ�userdata-FONT����ʧ���򷵻�nil
ETHER_API loadFontFromData(lua_State* L);

// ��������GC����
// 1�������������ݣ�userdata-FONT��
// 0����ֵ
ETHER_API __gc_Font(lua_State * L);

// ��ȡ�Ѽ����������ʽ
// 1�������������ݣ�userdata-FONT��
// 1����ֵ��nil
ETHER_API font_GetStyle(lua_State * L);

// �����Ѽ����������ʽ
// 2�������������ݣ�userdata-FONT������������������ʽ�ı�table��
// 0����ֵ
ETHER_API font_SetStyle(lua_State * L);

// ��ȡ�Ѽ�������������߿��
// 1�������������ݣ�userdata-FONT��
// 1����ֵ�������߿�ȣ�number��
ETHER_API font_GetOutlineWidth(lua_State * L);

// �����Ѽ�������������߿��
// 2�������������ݣ�userdata-FONT���������߿�ȣ�number��
// 0����ֵ
ETHER_API font_SetOutlineWidth(lua_State * L);

// ��ȡ������
// 1�������������ݣ�userdata-FONT��
// 1����ֵ�������ࣨnumber��
ETHER_API font_GetKerning(lua_State * L);

// ����������
// 2�������������ݣ�userdata-FONT���������ࣨnumber��
// 0����ֵ
ETHER_API font_SetKerning(lua_State * L);

// ��ȡ����߶�
// 1�������������ݣ�userdata-FONT��
// 1����ֵ������߶ȣ�number��
ETHER_API font_GetHeight(lua_State * L);

// ��ȡ�ı��ߴ�
// 2�������������ݣ�userdata-FONT�����ı����ݣ�string��
// 2����ֵ���ı���ȣ�number�����ı��߶ȣ�number��
ETHER_API getTextSize(lua_State * L);

// ��ȡUTF-8�����ʽ���ı��ߴ�
// 2�������������ݣ�userdata-FONT����UTF-8�����ʽ���ı����ݣ�string��
// 2�������ı���ȣ�number�����ı��߶ȣ�number��
ETHER_API getUTF8TextSize(lua_State * L);

// ʹ��Solidģʽ�����ı�ͼ��
// 3�������������ݣ�userdata-FONT�����ı����ݣ�string�������������ı���ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API createTextImageSolid(lua_State * L);

// ʹ��Solidģʽ����UTF-8�����ʽ���ı�ͼ��
// 3�������������ݣ�userdata-FONT����UTF-8�����ʽ���ı����ݣ�string�������������ı���ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API createUTF8TextImageSolid(lua_State * L);

// ʹ��Shadedģʽ�����ı�ͼ��
// 3�������������ݣ�userdata-FONT�����ı����ݣ�string�������������ı���ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255�������������ı�������ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API createTextImageShaded(lua_State * L);

// ʹ��Shadedģʽ����UTF-8�����ʽ���ı�ͼ��
// 3�������������ݣ�userdata-FONT����UTF-8�����ʽ���ı����ݣ�string�������������ı���ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255�������������ı�������ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API createUTF8TextImageShaded(lua_State * L);

// ʹ��Blendedģʽ�����ı�ͼ��
// 3�������������ݣ�userdata-FONT�����ı����ݣ�string�������������ı���ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API createTextImageBlended(lua_State * L);

// ʹ��Blendedģʽ����UTF-8�����ʽ���ı�ͼ��
// 3�������������ݣ�userdata-FONT����UTF-8�����ʽ���ı����ݣ�string�������������ı���ɫ��RGBA��table��ȡֵ��Χ��Ϊ0-255��
// 1����ֵ���ɹ��򷵻�ͼ�����ݣ�userdata-IMAGE����ʧ���򷵻�nil
ETHER_API createUTF8TextImageBlended(lua_State * L);

#endif // !_GRAPHIC_H_
