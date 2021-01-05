#ifndef _INTERACTIVITY_H_
#define _INTERACTIVITY_H_

#include "Moudle.h"
#include "Macros.h"

#include <lua.hpp>
#include <SDL.h>

extern SDL_Event event;

// 获取当前鼠标位置
// 0参数
// 1返回值：鼠标位置坐标（table）
ETHER_API getCursorPosition(lua_State * L);

// 获取鼠标滚轮滚动距离
// 0参数
// 2返回值：滚轮水平方向滚动距离（number，向左为负，向右为正）、滚轮垂直方向滚动距离（number，向前为负，向后为正）
ETHER_API getScrollValue(lua_State * L);

// 获取并更新内置事件
// 0参数
// 1返回值：false，当前事件队列无待解决事件；true，当前事件队列有待解决事件
ETHER_API updateEvent(lua_State * L);

// 获取当前的内置事件类型（由于部分字符按键事件对应的输入在大多数键盘上只能通过组合键完成，故这些字符的按键事件在大多数键盘上可能无法通过物理按键激活）
// 0参数
// 1返回值：事件类型（MACRO number）
ETHER_API getEventType(lua_State * L);


class MoudleInteractivity : public Moudle
{
public:
	MoudleInteractivity(lua_State* L);
	~MoudleInteractivity() {};

};

#endif // !_INTERACTIVITY_H_
