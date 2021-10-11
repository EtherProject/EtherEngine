#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "Module.h"
#include "Macros.h"

#include "lua.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MUSIC_TYPE_WAV					1308
#define MUSIC_TYPE_MP3					1309
#define MUSIC_TYPE_OGG					1310
#define MUSIC_TYPE_CMD					1311
#define MUSIC_TYPE_MOD					1312
#define MUSIC_TYPE_MID					1313
#define MUSIC_TYPE_UNKONWN				1314

#define FADING_TYPE_NONE				1315
#define FADING_TYPE_IN					1316
#define FADING_TYPE_OUT					1317

#define METANAME_MUSIC					"Graphic.Music"
#define METANAME_SOUND					"Graphic.Sound"

#define GetMusicDataAt1stPos()			(Mix_Music*)(*(void**)luaL_checkudata(L, 1, METANAME_MUSIC))
#define GetSoundDataAt1stPos()			(Mix_Chunk*)(*(void**)luaL_checkudata(L, 1, METANAME_SOUND))

#define CheckMusicDataAt1stPos(music)	luaL_argcheck(L, music, 1, "get music data failed")
#define CheckSoundDataAt1stPos(sound)	luaL_argcheck(L, sound, 1, "get sound data failed")

class ModuleMedia : public Module
{
public:
	static ModuleMedia& Instance();
	~ModuleMedia() {};

private:
	ModuleMedia();

};

// ���������ļ�
// 1�����������ļ�·��
// 1����ֵ���ɹ��򷵻��������ݣ�userdata-Music����ʧ���򷵻�nil
ETHER_API loadMusic(lua_State * L);

// ��������GC����
// 1�������������ݣ�userdata-Music��
// 0����ֵ
ETHER_API __gc_Music(lua_State * L);

// �����Ѽ��ص�����
// 2�������������ݣ�userdata-Music�������ֲ��ŵĴ�����number��-1Ϊѭ�����ţ�
// 0����ֵ
ETHER_API playMusic(lua_State * L);

// ʹ�õ���Ч�������Ѽ��ص�����
// 3�������������ݣ�userdata-Music�������ֲ��ŵĴ�����number��-1Ϊѭ�����ţ���������Ч����ʱ�䣨number����λΪ���룩
// 0����ֵ
ETHER_API playMusicWithFadeIn(lua_State * L);

// ֹͣ���ڲ��ŵ�����
// 0����
// 0����ֵ
ETHER_API stopMusic(lua_State* L);

// ʹ�õ���Ч��ֹͣ���ڲ��ŵ�����
// 1������������Ч����ʱ�䣨number����λΪ���룩
// 0����ֵ
ETHER_API stopMusicWithFadeOut(lua_State * L);

// ���õ����ֵĲ���λ��
// 1����������λ�ã�number��
// 0����ֵ
// ��ע���˲�����֧���������ָ�ʽ�����֣��Ҳ������������ͬ��
// MOD�����õ�ǰ����λ��Ϊ�˱���ģ���ж�Ӧ���������ݿ鴦��0 ����ת�����ֿ�ͷ
// OGG�����õ�ǰ����λ��Ϊ�����ֿ�ʼλ�ü����ָ��������
// MP3�����õ�ǰ����λ��Ϊ�ӵ�ǰ����λ�ü����ָ��������������ʹ�� RewindMusic ����ǰ���ֵĲ���λ�����õ���ʼ��
ETHER_API setMusicPosition(lua_State* L);

// �������ֲ��ŵ�����
// 1������������С��number��ȡֵ��ΧΪ0-128��
// 0����ֵ
ETHER_API setMusicVolume(lua_State * L);

// ��ȡ��ǰ���ֲ��ŵ�����
// 0����
// 1����ֵ��������С��number��ȡֵ��ΧΪ0-128��
ETHER_API getMusicVolume(lua_State * L);

// ��ͣ��ǰ���ڲ��ŵ�����
// 0����
// 0����ֵ
ETHER_API pauseMusic(lua_State * L);

// �ָ���ǰ��ͣ״̬������
// 0����
// 0����ֵ
ETHER_API resumeMusic(lua_State * L);

// ���²��ŵ�ǰ���ڲ��ŵ�����
// 0����
// 0����ֵ
ETHER_API rewindMusic(lua_State * L);

// �жϵ�ǰ�����Ƿ����ڲ���
// 0����
// 1����ֵ���Ƿ����ڲ��ţ�boolean��
ETHER_API checkMusicPlaying(lua_State* L);

// �жϵ�ǰ�����Ƿ�����ͣ
// 0����
// 1����ֵ���Ƿ�����ͣ��boolean��
ETHER_API checkMusicPaused(lua_State* L);

// ��ȡ��ǰ���ڲ��ŵ����ֵĵ���Ч������
// 0����
// 1����ֵ������Ч�����ͣ�MACRO number��
ETHER_API getMusicFadingType(lua_State* L);

// ��ȡָ�����ֵ�����
// 1�������������ݣ�userdata-Music��nil��ʾ���ڲ��ŵ����֣�
// 1����ֵ���������ͣ�MACRO number��
ETHER_API music_GetType(lua_State * L);

// ���ļ��м�����Ч
// 1��������Ч�ļ�·��
// 1����ֵ���ɹ��򷵻���Ч���ݣ�userdata-Sound����ʧ���򷵻�nil
ETHER_API loadSoundFromFile(lua_State * L);

// �ӻ������м�����Ч
// 1���������������ݣ�string��
// 1����ֵ���ɹ��򷵻���Ч���ݣ�userdata-Sound����ʧ���򷵻�nil
ETHER_API loadSoundFromData(lua_State* L);

// ��Ч����GC����
// 1��������Ч���ݣ�userdata-Sound��
// 0����ֵ
ETHER_API __gc_Sound(lua_State * L);

// �����Ѽ��ص���Ч
// 2��������Ч���ݣ�userdata-Sound������Ч���ŵĴ�����number��-1Ϊѭ�����ţ�
// 0����ֵ
ETHER_API sound_Play(lua_State * L);

// ������Ч���ŵ�����
// 2��������Ч���ݣ�userdata-Sound����������С��number��ȡֵ��ΧΪ0-128��
// 0����ֵ
ETHER_API sound_SetVolume(lua_State* L);

// ��ȡ��Ч���ŵ�����
// 1��������Ч���ݣ�userdata-Sound��
// 1����ֵ��������С��number��ȡֵ��ΧΪ0-128��
ETHER_API sound_GetVolume(lua_State* L);

#endif // !_MEDIA_H_

