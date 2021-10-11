#ifndef _INTERACTIVITY_H_
#define _INTERACTIVITY_H_

#include "Module.h"
#include "Macros.h"

#include "lua.hpp"
#include <sdl2/SDL.h>

#include <unordered_map>

#define EVENT_QUIT						1016

#define EVENT_MOUSEMOTION				1017
#define EVENT_MOUSEBTNDOWN_LEFT			1018
#define EVENT_MOUSEBTNDOWN_RIGHT		1019
#define EVENT_MOUSEBTNDOWN_MIDDLE		1020
#define EVENT_MOUSEBTNUP_LEFT			1021
#define EVENT_MOUSEBTNUP_RIGHT			1022
#define EVENT_MOUSEBTNUP_MIDDLE			1023
#define EVENT_MOUSESCROLL				1024

#define EVENT_WINDOW_SHOW				1025
#define EVENT_WINDOW_HIDE				1026
#define EVENT_WINDOW_MOVE				1027
#define EVENT_WINDOW_RESIZE				1028
#define EVENT_WINDOW_MINSIZE			1029
#define EVENT_WINDOW_MAXSIZE			1030
#define EVENT_WINDOW_ENTER				1031
#define EVENT_WINDOW_LEAVE				1032
#define EVENT_WINDOW_FOCUS				1033
#define EVENT_WINDOW_LOST				1034
#define EVENT_WINDOW_CLOSE				1035
#define EVENT_WINDOW_EXPOSED			1036

#define EVENT_KEYDOWN_0					1037
#define EVENT_KEYDOWN_00				1038
#define EVENT_KEYDOWN_000				1039
#define EVENT_KEYDOWN_1					1040
#define EVENT_KEYDOWN_2					1041
#define EVENT_KEYDOWN_3					1042
#define EVENT_KEYDOWN_4					1043
#define EVENT_KEYDOWN_5					1044
#define EVENT_KEYDOWN_6					1045
#define EVENT_KEYDOWN_7					1046
#define EVENT_KEYDOWN_8					1047
#define EVENT_KEYDOWN_9					1048
#define EVENT_KEYDOWN_F1				1049
#define EVENT_KEYDOWN_F2				1050
#define EVENT_KEYDOWN_F3				1051
#define EVENT_KEYDOWN_F4				1052
#define EVENT_KEYDOWN_F5				1053
#define EVENT_KEYDOWN_F6				1054
#define EVENT_KEYDOWN_F7				1055
#define EVENT_KEYDOWN_F8				1056
#define EVENT_KEYDOWN_F9				1057
#define EVENT_KEYDOWN_F10				1058
#define EVENT_KEYDOWN_F11				1059
#define EVENT_KEYDOWN_F12				1060
#define EVENT_KEYDOWN_F13				1061
#define EVENT_KEYDOWN_F14				1062
#define EVENT_KEYDOWN_F15				1063
#define EVENT_KEYDOWN_F16				1064
#define EVENT_KEYDOWN_F17				1065
#define EVENT_KEYDOWN_F18				1066
#define EVENT_KEYDOWN_F19				1066
#define EVENT_KEYDOWN_F20				1068
#define EVENT_KEYDOWN_F21				1068
#define EVENT_KEYDOWN_F22				1069
#define EVENT_KEYDOWN_F23				1070
#define EVENT_KEYDOWN_F24				1071
#define EVENT_KEYDOWN_A					1072
#define EVENT_KEYDOWN_B					1073
#define EVENT_KEYDOWN_C					1074
#define EVENT_KEYDOWN_D					1075
#define EVENT_KEYDOWN_E					1076
#define EVENT_KEYDOWN_F					1077
#define EVENT_KEYDOWN_G					1078
#define EVENT_KEYDOWN_H					1079
#define EVENT_KEYDOWN_I					1080
#define EVENT_KEYDOWN_J					1081
#define EVENT_KEYDOWN_K					1082
#define EVENT_KEYDOWN_L					1083
#define EVENT_KEYDOWN_M					1084
#define EVENT_KEYDOWN_N					1085
#define EVENT_KEYDOWN_O					1086
#define EVENT_KEYDOWN_P					1087
#define EVENT_KEYDOWN_Q					1088
#define EVENT_KEYDOWN_R					1089
#define EVENT_KEYDOWN_S					1090
#define EVENT_KEYDOWN_T					1091
#define EVENT_KEYDOWN_U					1092
#define EVENT_KEYDOWN_V					1093
#define EVENT_KEYDOWN_W					1094
#define EVENT_KEYDOWN_X					1095
#define EVENT_KEYDOWN_Y					1096
#define EVENT_KEYDOWN_Z					1097
#define EVENT_KEYDOWN_ESC				1098
#define EVENT_KEYDOWN_ENTER				1099
#define EVENT_KEYDOWN_BACKSPACE			1100
#define EVENT_KEYDOWN_UP				1101
#define EVENT_KEYDOWN_DOWN				1102
#define EVENT_KEYDOWN_LEFT				1103
#define EVENT_KEYDOWN_RIGHT				1104
#define EVENT_KEYDOWN_INSERT			1106
#define EVENT_KEYDOWN_DELETE			1107
#define EVENT_KEYDOWN_HOME				1108
#define EVENT_KEYDOWN_END				1109
#define EVENT_KEYDOWN_PAGEUP			1110
#define EVENT_KEYDOWN_PAGEDOWN			1111
#define EVENT_KEYDOWN_LEFTCTRL			1112
#define EVENT_KEYDOWN_LEFTGUI			1113
#define EVENT_KEYDOWN_LEFTALT			1114
#define EVENT_KEYDOWN_LEFTSHIFT			1115
#define EVENT_KEYDOWN_RIGHTCTRL			1116
#define EVENT_KEYDOWN_RIGHTGUI			1117
#define EVENT_KEYDOWN_RIGHTALT			1118
#define EVENT_KEYDOWN_RIGHTSHIFT		1119
#define EVENT_KEYDOWN_SPACE				1120
#define EVENT_KEYDOWN_TAB				1121
#define EVENT_KEYDOWN_CAPSLOCK			1122
#define EVENT_KEYDOWN_NUMLOCK			1123
#define EVENT_KEYDOWN_PRINTSCREEN		1124
#define EVENT_KEYDOWN_SCROLLLOCK		1125
#define EVENT_KEYDOWN_PAUSE				1126
#define EVENT_KEYDOWN_AUDIOMUTE			1127
#define EVENT_KEYDOWN_AUDIOPREV			1128
#define EVENT_KEYDOWN_AUDIONEXT			1129
#define EVENT_KEYDOWN_AUDIOPLAY			1130
#define EVENT_KEYDOWN_AUDIOSTOP			1131
#define EVENT_KEYDOWN_VOLUMEUP			1132
#define EVENT_KEYDOWN_VOLUMEDOWN		1133
#define EVENT_KEYDOWN_BRIGHTNESSUP		1134
#define EVENT_KEYDOWN_BRIGHTNESSDOWN	1135
#define EVENT_KEYDOWN_BACKQUOTE			1136
#define EVENT_KEYDOWN_EXCLAM			1137
#define EVENT_KEYDOWN_AT				1138
#define EVENT_KEYDOWN_HASH				1139
#define EVENT_KEYDOWN_DOOLAR			1140
#define EVENT_KEYDOWN_CARET				1141
#define EVENT_KEYDOWN_AMPERSAND			1142
#define EVENT_KEYDOWN_DBLAMPERSAND		1143
#define EVENT_KEYDOWN_ASTERISK			1144
#define EVENT_KEYDOWN_LEFTPAREN			1145
#define EVENT_KEYDOWN_RIGHTPAREN		1146
#define EVENT_KEYDOWN_MINUS				1147
#define EVENT_KEYDOWN_UNDERSCORE		1148
#define EVENT_KEYDOWN_PLUS				1149
#define EVENT_KEYDOWN_EQUALS			1150
#define EVENT_KEYDOWN_LEFTBRACKET		1151
#define EVENT_KEYDOWN_RIGHTBRACKET		1152
#define EVENT_KEYDOWN_LEFTBRACE			1153
#define EVENT_KEYDOWN_RIGHTBRACE		1154
#define EVENT_KEYDOWN_COLON				1155
#define EVENT_KEYDOWN_SEMICOLON			1156
#define EVENT_KEYDOWN_BACKSLASH			1157
#define EVENT_KEYDOWN_QUOTE				1158
#define EVENT_KEYDOWN_QUOTEDBL			1159
#define EVENT_KEYDOWN_LESS				1160
#define EVENT_KEYDOWN_GREATER			1161
#define EVENT_KEYDOWN_COMMA				1162
#define EVENT_KEYDOWN_PERIOD			1163
#define EVENT_KEYDOWN_QUESTION			1164
#define EVENT_KEYDOWN_SLASH				1165
#define EVENT_KEYDOWN_VERTICALBAR		1166
#define EVENT_KEYDOWN_DBLVERTICALBAR	1167
#define EVENT_KEYDOWN_WWW				1168
#define EVENT_KEYDOWN_EMAIL				1169
#define EVENT_KEYUP_0					1170
#define EVENT_KEYUP_00					1171
#define EVENT_KEYUP_000					1172
#define EVENT_KEYUP_1					1173
#define EVENT_KEYUP_2					1174
#define EVENT_KEYUP_3					1175
#define EVENT_KEYUP_4					1176
#define EVENT_KEYUP_5					1177
#define EVENT_KEYUP_6					1178
#define EVENT_KEYUP_7					1179
#define EVENT_KEYUP_8					1180
#define EVENT_KEYUP_9					1181
#define EVENT_KEYUP_F1					1182
#define EVENT_KEYUP_F2					1183
#define EVENT_KEYUP_F3					1184
#define EVENT_KEYUP_F4					1185
#define EVENT_KEYUP_F5					1186
#define EVENT_KEYUP_F6					1187
#define EVENT_KEYUP_F7					1188
#define EVENT_KEYUP_F8					1189
#define EVENT_KEYUP_F9					1190
#define EVENT_KEYUP_F10					1191
#define EVENT_KEYUP_F11					1192
#define EVENT_KEYUP_F12					1193
#define EVENT_KEYUP_F13					1194
#define EVENT_KEYUP_F14					1195
#define EVENT_KEYUP_F15					1196
#define EVENT_KEYUP_F16					1197
#define EVENT_KEYUP_F17					1198
#define EVENT_KEYUP_F18					1199
#define EVENT_KEYUP_F19					1200
#define EVENT_KEYUP_F20					1201
#define EVENT_KEYUP_F21					1202
#define EVENT_KEYUP_F22					1203
#define EVENT_KEYUP_F23					1204
#define EVENT_KEYUP_F24					1204
#define EVENT_KEYUP_A					1206
#define EVENT_KEYUP_B					1207
#define EVENT_KEYUP_C					1208
#define EVENT_KEYUP_D					1209
#define EVENT_KEYUP_E					1210
#define EVENT_KEYUP_F					1211
#define EVENT_KEYUP_G					1212
#define EVENT_KEYUP_H					1213
#define EVENT_KEYUP_I					1214
#define EVENT_KEYUP_J					1215
#define EVENT_KEYUP_K					1216
#define EVENT_KEYUP_L					1217
#define EVENT_KEYUP_M					1218
#define EVENT_KEYUP_N					1219
#define EVENT_KEYUP_O					1220
#define EVENT_KEYUP_P					1221
#define EVENT_KEYUP_Q					1222
#define EVENT_KEYUP_R					1223
#define EVENT_KEYUP_S					1224
#define EVENT_KEYUP_T					1225
#define EVENT_KEYUP_U					1226
#define EVENT_KEYUP_V					1227
#define EVENT_KEYUP_W					1228
#define EVENT_KEYUP_X					1229
#define EVENT_KEYUP_Y					1230
#define EVENT_KEYUP_Z					1231
#define EVENT_KEYUP_ESC					1232
#define EVENT_KEYUP_ENTER				1233
#define EVENT_KEYUP_BACKSPACE			1234
#define EVENT_KEYUP_UP					1235
#define EVENT_KEYUP_DOWN				1236
#define EVENT_KEYUP_LEFT				1237
#define EVENT_KEYUP_RIGHT				1238
#define EVENT_KEYUP_INSERT				1239
#define EVENT_KEYUP_DELETE				1240
#define EVENT_KEYUP_HOME				1241
#define EVENT_KEYUP_END					1242
#define EVENT_KEYUP_PAGEUP				1243
#define EVENT_KEYUP_PAGEDOWN			1244
#define EVENT_KEYUP_LEFTCTRL			1245
#define EVENT_KEYUP_LEFTGUI				1246
#define EVENT_KEYUP_LEFTALT				1247
#define EVENT_KEYUP_LEFTSHIFT			1248
#define EVENT_KEYUP_RIGHTCTRL			1249
#define EVENT_KEYUP_RIGHTGUI			1250
#define EVENT_KEYUP_RIGHTALT			1251
#define EVENT_KEYUP_RIGHTSHIFT			1252
#define EVENT_KEYUP_SPACE				1253
#define EVENT_KEYUP_TAB					1254
#define EVENT_KEYUP_CAPSLOCK			1255
#define EVENT_KEYUP_NUMLOCK				1256
#define EVENT_KEYUP_PRINTSCREEN			1257
#define EVENT_KEYUP_SCROLLLOCK			1258
#define EVENT_KEYUP_PAUSE				1259
#define EVENT_KEYUP_AUDIOMUTE			1260
#define EVENT_KEYUP_AUDIOPREV			1261
#define EVENT_KEYUP_AUDIONEXT			1262
#define EVENT_KEYUP_AUDIOPLAY			1263
#define EVENT_KEYUP_AUDIOSTOP			1264
#define EVENT_KEYUP_VOLUMEUP			1265
#define EVENT_KEYUP_VOLUMEDOWN			1266
#define EVENT_KEYUP_BRIGHTNESSUP		1267
#define EVENT_KEYUP_BRIGHTNESSDOWN		1268
#define EVENT_KEYUP_BACKQUOTE			1269
#define EVENT_KEYUP_EXCLAM				1270
#define EVENT_KEYUP_AT					1271
#define EVENT_KEYUP_HASH				1272
#define EVENT_KEYUP_DOOLAR				1273
#define EVENT_KEYUP_CARET				1274
#define EVENT_KEYUP_AMPERSAND			1275
#define EVENT_KEYUP_DBLAMPERSAND		1276
#define EVENT_KEYUP_ASTERISK			1277
#define EVENT_KEYUP_LEFTPAREN			1278
#define EVENT_KEYUP_RIGHTPAREN			1279
#define EVENT_KEYUP_MINUS				1280
#define EVENT_KEYUP_UNDERSCORE			1281
#define EVENT_KEYUP_PLUS				1282
#define EVENT_KEYUP_EQUALS				1283
#define EVENT_KEYUP_LEFTBRACKET			1284
#define EVENT_KEYUP_RIGHTBRACKET		1285
#define EVENT_KEYUP_LEFTBRACE			1286
#define EVENT_KEYUP_RIGHTBRACE			1287
#define EVENT_KEYUP_COLON				1288
#define EVENT_KEYUP_SEMICOLON			1289
#define EVENT_KEYUP_BACKSLASH			1290
#define EVENT_KEYUP_QUOTE				1291
#define EVENT_KEYUP_QUOTEDBL			1292
#define EVENT_KEYUP_LESS				1293
#define EVENT_KEYUP_GREATER				1294
#define EVENT_KEYUP_COMMA				1295
#define EVENT_KEYUP_PERIOD				1296
#define EVENT_KEYUP_QUESTION			1297
#define EVENT_KEYUP_SLASH				1298
#define EVENT_KEYUP_VERTICALBAR			1299
#define EVENT_KEYUP_DBLVERTICALBAR		1300
#define EVENT_KEYUP_WWW					1301
#define EVENT_KEYUP_EMAIL				1302

#define EVENT_TEXTINPUT					1303

class ModuleInteractivity : public Module
{
public:
	static std::unordered_map<int, std::unordered_map<int, int>> mapMultiEventList;
	static std::unordered_map<int, int> mapSingleEventList;
	static ModuleInteractivity& Instance();
	~ModuleInteractivity() {};

private:
	ModuleInteractivity();

};

extern SDL_Event event;

extern SDL_Point pointCursorPos;

/// <summary>
/// 根据事件Map的一级Key获取Map的二级Value
/// </summary>
/// <param name="firstLevelKey">一级Key</param>
/// <returns>Map的二级Value</returns>
inline int Get2ndLevelValue(int firstLevelKey);

// 获取当前鼠标位置
// 0参数
// 1返回值：鼠标位置坐标（table）
ETHER_API getCursorPosition(lua_State * L);

// 获取鼠标滚轮滚动距离
// 0参数
// 2返回值：滚轮水平方向滚动距离（number，向左为负，向右为正）、滚轮垂直方向滚动距离（number，向前为负，向后为正）
ETHER_API getScrollValue(lua_State * L);

// 开始接收文本输入内容
// 0参数
// 0返回值
ETHER_API startTextInput(lua_State* L);

// 结束接收文本输入内容
// 0参数
// 0返回值
ETHER_API stopTextInput(lua_State* L);

// 获取文本输入内容
// 0参数
// 1返回值：文本输入内容（string）
ETHER_API getInputText(lua_State* L);

// 获取并更新内置事件
// 0参数
// 1返回值：false，当前事件队列无待解决事件；true，当前事件队列有待解决事件
ETHER_API updateEvent(lua_State * L);

// 获取当前的内置事件类型（由于部分字符按键事件对应的输入在大多数键盘上只能通过组合键完成，故这些字符的按键事件在大多数键盘上可能无法通过物理按键激活）
// 0参数
// 1返回值：事件类型（MACRO number）
ETHER_API getEventType(lua_State * L);

#endif // !_INTERACTIVITY_H_
