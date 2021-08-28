/*
	Copyright (c) 2021 Daniel Valcour
	
	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*! \file keyboard_key.h
 */
#ifndef TUIC_KEYBOARD_KEY //header guard
#define TUIC_KEYBOARD_KEY
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/boolean.h>


/*!
 * @brief Keyboard keys.
 */
typedef enum TuiKeyboardKey
{
	/*!
	 * \brief The keyboard key is invalid.
	 *
	 * This keyboard key is returned when an error occurs, and is also used to specify that no keyboard key is
	 * defined.
	 */
	TUIK_INVALID		   = 0,
	/*!
	 * \brief The alphanumeric spacebar key.
	 */
	TUIK_SPACE             = 32,
	/*!
	 * \brief The alphanumeric apostrophe key ( ' ).
	 */
	TUIK_APOSTROPHE        = 39,
	/*!
	 * \brief The alphanumeric comma key ( , ).
	 */
	TUIK_COMMA             = 44,
	/*!
	 * \brief The alphanumeric minus key ( - ).
	 */
	TUIK_MINUS             = 45,
	/*!
	 * \brief The alphanumeric period key ( . ).
	 */
	TUIK_PERIOD            = 46,
	/*!
	 * \brief The alphanumeric forward slash key ( / ).
	 */
	TUIK_SLASH             = 47,
	/*!
	 * \brief The alphanumeric 0 key.
	 */
	TUIK_0                 = 48,
	/*!
	 * \brief The alphanumeric 1 key.
	 */
	TUIK_1                 = 49,
	/*!
	 * \brief The alphanumeric 2 key.
	 */
	TUIK_2                 = 50,
	/*!
	 * \brief The alphanumeric 3 key.
	 */
	TUIK_3                 = 51,
	/*!
	 * \brief The alphanumeric 4 key.
	 */
	TUIK_4                 = 52,
	/*!
	 * \brief The alphanumeric 5 key.
	 */
	TUIK_5                 = 53,
	/*!
	 * \brief The alphanumeric 6 key.
	 */
	TUIK_6                 = 54,
	/*!
	 * \brief The alphanumeric 7 key.
	 */
	TUIK_7                 = 55,
	/*!
	 * \brief The alphanumeric 8 key.
	 */
	TUIK_8                 = 56,
	/*!
	 * \brief The alphanumeric 9 key.
	 */
	TUIK_9                 = 57,
	/*!
	 * \brief The alphanumeric semicolon key ( ; ).
	 */
	TUIK_SEMICOLON         = 59,
	/*!
	 * \brief The alphanumeric equal sign key ( = ).
	 */
	TUIK_EQUAL             = 61,
	/*!
	 * \brief The alphanumeric A key.
	 */
	TUIK_A                 = 65,
	/*!
	 * \brief The alphanumeric B key.
	 */
	TUIK_B                 = 66,
	/*!
	 * \brief The alphanumeric C key.
	 */
	TUIK_C                 = 67,
	/*!
	 * \brief The alphanumeric D key.
	 */
	TUIK_D                 = 68,
	/*!
	 * \brief The alphanumeric E key.
	 */
	TUIK_E                 = 69,
	/*!
	 * \brief The alphanumeric F key.
	 */
	TUIK_F                 = 70,
	/*!
	 * \brief The alphanumeric G key.
	 */
	TUIK_G                 = 71,
	/*!
	 * \brief The alphanumeric H key.
	 */
	TUIK_H                 = 72,
	/*!
	 * \brief The alphanumeric I key.
	 */
	TUIK_I                 = 73,
	/*!
	 * \brief The alphanumeric J key.
	 */
	TUIK_J                 = 74,
	/*!
	 * \brief The alphanumeric K key.
	 */
	TUIK_K                 = 75,
	/*!
	 * \brief The alphanumeric L key.
	 */
	TUIK_L                 = 76,
	/*!
	 * \brief The alphanumeric M key.
	 */
	TUIK_M                 = 77,
	/*!
	 * \brief The alphanumeric N key.
	 */
	TUIK_N                 = 78,
	/*!
	 * \brief The alphanumeric O key.
	 */
	TUIK_O                 = 79,
	/*!
	 * \brief The alphanumeric P key.
	 */
	TUIK_P                 = 80,
	/*!
	 * \brief The alphanumeric Q key.
	 */
	TUIK_Q                 = 81,
	/*!
	 * \brief The alphanumeric R key.
	 */
	TUIK_R                 = 82,
	/*!
	 * \brief The alphanumeric S key.
	 */
	TUIK_S                 = 83,
	/*!
	 * \brief The alphanumeric T key.
	 */
	TUIK_T                 = 84,
	/*!
	 * \brief The alphanumeric U key.
	 */
	TUIK_U                 = 85,
	/*!
	 * \brief The alphanumeric V key.
	 */
	TUIK_V                 = 86,
	/*!
	 * \brief The alphanumeric W key.
	 */
	TUIK_W                 = 87,
	/*!
	 * \brief The alphanumeric X key.
	 */
	TUIK_X                 = 88,
	/*!
	 * \brief The alphanumeric Y key.
	 */
	TUIK_Y                 = 89,
	/*!
	 * \brief The alphanumeric Z key.
	 */
	TUIK_Z                 = 90,
	/*!
	 * \brief The alphanumeric left bracket key ( [ ).
	 */
	TUIK_LEFT_BRACKET      = 91,
	/*!
	 * \brief The alphanumeric backslash key ( \ ).
	 */
	TUIK_BACKSLASH         = 92,
	/*!
	 * \brief The alphanumeric right bracket key ( ] ).
	 */
	TUIK_RIGHT_BRACKET     = 93,
	/*!
	 * \brief The alphanumeric grave accent key ( ` ).
	 */
	TUIK_GRAVE_ACCENT      = 96,
	/*!
	 * \brief Non-US keyboard key #1.
	 */
	TUIK_WORLD_1           = 161,
	/*!
	 * \brief Non-US keyboard key #2.
	 */
	TUIK_WORLD_2           = 162,
	/*!
	 * \brief The escape key.
	 */
	TUIK_ESCAPE            = 256,
	/*!
	 * \brief The enter key.
	 */
	TUIK_ENTER             = 257,
	/*!
	 * \brief The tab key.
	 */
	TUIK_TAB               = 258,
	/*!
	 * \brief The alphanumeric backspace key.
	 */
	TUIK_BACKSPACE         = 259,
	/*!
	 * \brief The insert key.
	 */
	TUIK_INSERT            = 260,
	/*!
	 * \brief The delete key.
	 */
	TUIK_DELETE            = 261,
	/*!
	 * \brief The right arrow key.
	 */
	TUIK_RIGHT             = 262,
	/*!
	 * \brief The left arrow key.
	 */
	TUIK_LEFT              = 263,
	/*!
	 * \brief The down arrow key.
	 */
	TUIK_DOWN              = 264,
	/*!
	 * \brief The up arrow key.
	 */
	TUIK_UP                = 265,
	/*!
	 * \brief The page up key.
	 */
	TUIK_PAGE_UP           = 266,
	/*!
	 * \brief The page down key.
	 */
	TUIK_PAGE_DOWN         = 267,
	/*!
	 * \brief The home key.
	 */
	TUIK_HOME              = 268,
	/*!
	 * \brief The end key.
	 */
	TUIK_END               = 269,
	/*!
	 * \brief The caps lock key.
	 */
	TUIK_CAPS_LOCK         = 280,
	/*!
	 * \brief The scroll lock key.
	 */
	TUIK_SCROLL_LOCK       = 281,
	/*!
	 * \brief The num lock key.
	 */
	TUIK_NUM_LOCK          = 282,
	/*!
	 * \brief The print screen key.
	 */
	TUIK_PRINT_SCREEN      = 283,
	/*!
	 * \brief The pause key.
	 */
	TUIK_PAUSE             = 284,
	/*!
	 * \brief The F1 key.
	 */
	TUIK_F1                = 290,
	/*!
	 * \brief The F2 key.
	 */
	TUIK_F2                = 291,
	/*!
	 * \brief The F3 key.
	 */
	TUIK_F3                = 292,
	/*!
	 * \brief The F4 key.
	 */
	TUIK_F4                = 293,
	/*!
	 * \brief The F5 key.
	 */
	TUIK_F5                = 294,
	/*!
	 * \brief The F6 key.
	 */
	TUIK_F6                = 295,
	/*!
	 * \brief The F7 key.
	 */
	TUIK_F7                = 296,
	/*!
	 * \brief The F8 key.
	 */
	TUIK_F8                = 297,
	/*!
	 * \brief The F9 key.
	 */
	TUIK_F9                = 298,
	/*!
	 * \brief The F10 key.
	 */
	TUIK_F10               = 299,
	/*!
	 * \brief The F11 key.
	 */
	TUIK_F11               = 300,
	/*!
	 * \brief The F12 key.
	 */
	TUIK_F12               = 301,
	/*!
	 * \brief The F13 key.
	 */
	TUIK_F13               = 302,
	/*!
	 * \brief The F14 key.
	 */
	TUIK_F14               = 303,
	/*!
	 * \brief The F15 key.
	 */
	TUIK_F15               = 304,
	/*!
	 * \brief The F16 key.
	 */
	TUIK_F16               = 305,
	/*!
	 * \brief The F17 key.
	 */
	TUIK_F17               = 306,
	/*!
	 * \brief The F18 key.
	 */
	TUIK_F18               = 307,
	/*!
	 * \brief The F19 key.
	 */
	TUIK_F19               = 308,
	/*!
	 * \brief The F20 key.
	 */
	TUIK_F20               = 309,
	/*!
	 * \brief The F21 key.
	 */
	TUIK_F21               = 310,
	/*!
	 * \brief The F22 key.
	 */
	TUIK_F22               = 311,
	/*!
	 * \brief The F23 key.
	 */
	TUIK_F23               = 312,
	/*!
	 * \brief The F24 key.
	 */
	TUIK_F24               = 313,
	/*!
	 * \brief The F25 key.
	 */
	TUIK_F25               = 314,
	/*!
	 * \brief The keypad 0 key.
	 */
	TUIK_KP_0              = 320,
	/*
	 * \brief The keypad 1 key.
	 */
	TUIK_KP_1              = 321,
	/*!
	 * \brief The keypad 2 key.
	 */
	TUIK_KP_2              = 322,
	/*!
	 * \brief The keypad 3 key.
	 */
	TUIK_KP_3              = 323,
	/*!
	 * \brief The keypad 4 key.
	 */
	TUIK_KP_4              = 324,
	/*!
	 * \brief The keypad 5 key.
	 */
	TUIK_KP_5              = 325,
	/*!
	 * \brief The keypad 6 key.
	 */
	TUIK_KP_6              = 326,
	/*!
	 * \brief The keypad 7 key.
	 */
	TUIK_KP_7              = 327,
	/*!
	 * \brief The keypad 8 key.
	 */
	TUIK_KP_8              = 328,
	/*!
	 * \brief The keypad 9 key.
	 */
	TUIK_KP_9              = 329,
	/*!
	 * \brief The keypad decimal key ( . ).
	 */
	TUIK_KP_DECIMAL        = 330,
	/*!
	 * \brief The keypad divide key ( / ).
	 */
	TUIK_KP_DIVIDE         = 331,
	/*!
	 * \brief The keypad multiply key ( * ).
	 */
	TUIK_KP_MULTIPLY       = 332,
	/*!
	 * \brief The keypad subtract key ( - ).
	 */
	TUIK_KP_SUBTRACT       = 333,
	/*!
	 * \brief The keypad add key ( + ).
	 */
	TUIK_KP_ADD            = 334,
	/*!
	 * \brief The keypad enter key.
	 */
	TUIK_KP_ENTER          = 335,
	/*!
	 * \brief The keypad equal key ( = ).
	 */
	TUIK_KP_EQUAL          = 336,
	/*!
	 * \brief The left shift key.
	 */
	TUIK_LEFT_SHIFT        = 340,
	/*!
	 * \brief The left control key.
	 */
	TUIK_LEFT_CONTROL      = 341,
	/*!
	 * \brief The left alt key.
	 */
	TUIK_LEFT_ALT          = 342,
	/*!
	 * \brief The left super key.
	 */
	TUIK_LEFT_SUPER        = 343,
	/*!
	 * \brief The right shift key.
	 */
	TUIK_RIGHT_SHIFT       = 344,
	/*!
	 * \brief The right control key.
	 */
	TUIK_RIGHT_CONTROL     = 345,
	/*!
	 * \brief The right alt key.
	 */
	TUIK_RIGHT_ALT         = 346,
	/*!
	 * \brief The right super key.
	 */
	TUIK_RIGHT_SUPER       = 347,
	/*!
	 * \brief The menu key.
	 */
	TUIK_MENU              = 348,
} TuiKeyboardKey;


/*! @name Keyboard Key Names
 *  @{ */
/*!
 * @brief String name of @ref TUIK_SPACE.
 */
extern const char* kTuik_Space_Name;
/*!
 * @brief String name of @ref TUIK_APOSTROPHE.
 */
extern const char* kTuik_Apostrophe_Name;
/*!
 * @brief String name of @ref TUIK_COMMA.
 */
extern const char* kTuik_Comma_Name;
/*!
 * @brief String name of @ref TUIK_MINUS.
 */
extern const char* kTuik_Minus_Name;
/*!
 * @brief String name of @ref TUIK_PERIOD.
 */
extern const char* kTuik_Period_Name;
/*!
 * @brief String name of @ref TUIK_SLASH.
 */
extern const char* kTuik_Slash_Name;
/*!
 * @brief String name of @ref TUIK_0.
 */
extern const char* kTuik_0_Name;
/*!
 * @brief String name of @ref TUIK_1.
 */
extern const char* kTuik_1_Name;
/*!
 * @brief String name of @ref TUIK_2.
 */
extern const char* kTuik_2_Name;
/*!
 * @brief String name of @ref TUIK_3.
 */
extern const char* kTuik_3_Name;
/*!
 * @brief String name of @ref TUIK_4.
 */
extern const char* kTuik_4_Name;
/*!
 * @brief String name of @ref TUIK_5.
 */
extern const char* kTuik_5_Name;
/*!
 * @brief String name of @ref TUIK_6.
 */
extern const char* kTuik_6_Name;
/*!
 * @brief String name of @ref TUIK_7.
 */
extern const char* kTuik_7_Name;
/*!
 * @brief String name of @ref TUIK_8.
 */
extern const char* kTuik_8_Name;
/*!
 * @brief String name of @ref TUIK_9.
 */
extern const char* kTuik_9_Name;
/*!
 * @brief String name of @ref TUIK_SEMICOLON.
 */
extern const char* kTuik_Semicolon_Name;
/*!
 * @brief String name of @ref TUIK_EQUAL.
 */
extern const char* kTuik_Equal_Name;
/*!
 * @brief String name of @ref TUIK_A.
 */
extern const char* kTuik_A_Name;
/*!
 * @brief String name of @ref TUIK_B.
 */
extern const char* kTuik_B_Name;
/*!
 * @brief String name of @ref TUIK_C.
 */
extern const char* kTuik_C_Name;
/*!
 * @brief String name of @ref TUIK_D.
 */
extern const char* kTuik_D_Name;
/*!
 * @brief String name of @ref TUIK_E.
 */
extern const char* kTuik_E_Name;
/*!
 * @brief String name of @ref TUIK_F.
 */
extern const char* kTuik_F_Name;
/*!
 * @brief String name of @ref TUIKK_G.
 */
extern const char* kTuik_G_Name;
/*!
 * @brief String name of @ref TUIK_M.
 */
extern const char* kTuik_H_Name;
/*!
 * @brief String name of @ref TUIK_I.
 */
extern const char* kTuik_I_Name;
/*!
 * @brief String name of @ref TUIK_J.
 */
extern const char* kTuik_J_Name;
/*!
 * @brief String name of @ref TUIK_K.
 */
extern const char* kTuik_K_Name;
/*!
 * @brief String name of @ref TUIK_L.
 */
extern const char* kTuik_L_Name;
/*!
 * @brief String name of @ref TUIK_M.
 */
extern const char* kTuik_M_Name;
/*!
 * @brief String name of @ref TUIK_N.
 */
extern const char* kTuik_N_Name;
/*!
 * @brief String name of @ref TUIK_O.
 */
extern const char* kTuik_O_Name;
/*!
 * @brief String name of @ref TUIK_P.
 */
extern const char* kTuik_P_Name;
/*!
 * @brief String name of @ref TUIK_Q.
 */
extern const char* kTuik_Q_Name;
/*!
 * @brief String name of @ref TUIK_R.
 */
extern const char* kTuik_R_Name;
/*!
 * @brief String name of @ref TUIK_S.
 */
extern const char* kTuik_S_Name;
/*!
 * @brief String name of @ref TUIK_T.
 */
extern const char* kTuik_T_Name;
/*!
 * @brief String name of @ref TUIK_U.
 */
extern const char* kTuik_U_Name;
/*!
 * @brief String name of @ref TUIK_V.
 */
extern const char* kTuik_V_Name;
/*!
 * @brief String name of @ref TUIK_W.
 */
extern const char* kTuik_W_Name;
/*!
 * @brief String name of @ref TUIK_X.
 */
extern const char* kTuik_X_Name;
/*!
 * @brief String name of @ref TUIK_Y.
 */
extern const char* kTuik_Y_Name;
/*!
 * @brief String name of @ref TUIK_Z.
 */
extern const char* kTuik_Z_Name;
/*!
 * @brief String name of @ref TUIK_LEFT_BRACKET.
 */
extern const char* kTuik_Left_Bracket_Name;
/*!
 * @brief String name of @ref TUIK_BACKSLASH.
 */
extern const char* kTuik_Backslash_Name;
/*!
 * @brief String name of @ref TUIK_RIGHT_BRACKET.
 */
extern const char* kTuik_Right_Bracket_Name;
/*!
 * @brief String name of @ref TUIK_GRAVE_ACCENT.
 */
extern const char* kTuik_Grave_Accent_Name;
/*!
 * @brief String name of @ref TUIK_WORLD_1.
 */
extern const char* kTuik_World_1_Name;
/*!
 * @brief String name of @ref TUIK_WORLD_2.
 */
extern const char* kTuik_World_2_Name;
/*!
 * @brief String name of @ref TUIK_ESCAPE.
 */
extern const char* kTuik_Escape_Name;
/*!
 * @brief String name of @ref TUIK_ENTER.
 */
extern const char* kTuik_Enter_Name;
/*!
 * @brief String name of @ref TUIK_TAB.
 */
extern const char* kTuik_Tab_Name;
/*!
 * @brief String name of @ref TUIK_BACKSPACE.
 */
extern const char* kTuik_Backspace_Name;
/*!
 * @brief String name of @ref TUIK_INSERT.
 */
extern const char* kTuik_Insert_Name;
/*!
 * @brief String name of @ref TUIK_DELETE.
 */
extern const char* kTuik_Delete_Name;
/*!
 * @brief String name of @ref TUIK_RIGHT.
 */
extern const char* kTuik_Right_Name;
/*!
 * @brief String name of @ref TUIK_LEFT.
 */
extern const char* kTuik_Left_Name;
/*!
 * @brief String name of @ref TUIK_DOWN.
 */
extern const char* kTuik_Down_Name;
/*!
 * @brief String name of @ref TUIK_UP.
 */
extern const char* kTuik_Up_Name;
/*!
 * @brief String name of @ref TUIK_PAGE_UP.
 */
extern const char* kTuik_Page_Up_Name;
/*!
 * @brief String name of @ref TUIK_PAGE_DOWN.
 */
extern const char* kTuik_Page_Down_Name;
/*!
 * @brief String name of @ref TUIK_HOME.
 */
extern const char* kTuik_Home_Name;
/*!
 * @brief String name of @ref TUIK_END.
 */
extern const char* kTuik_End_Name;
/*!
 * @brief String name of @ref TUIK_CAPS_LOCK.
 */
extern const char* kTuik_Caps_Lock_Name;
/*!
 * @brief String name of @ref TUIK_SCROLL_LOCK.
 */
extern const char* kTuik_Scroll_Lock_Name;
/*!
 * @brief String name of @ref TUIK_NUM_LOCK.
 */
extern const char* kTuik_Num_Lock_Name;
/*!
 * @brief String name of @ref TUIK_PRINT_SCREEN.
 */
extern const char* kTuik_Print_Screen_Name;
/*!
 * @brief String name of @ref TUIK_PAUSE.
 */
extern const char* kTuik_Pause_Name;
/*!
 * @brief String name of @ref TUIK_F1.
 */
extern const char* kTuik_F1_Name;
/*!
 * @brief String name of @ref TUIK_F2.
 */
extern const char* kTuik_F2_Name;
/*!
 * @brief String name of @ref TUIK_F3.
 */
extern const char* kTuik_F3_Name;
/*!
 * @brief String name of @ref TUIK_F4.
 */
extern const char* kTuik_F4_Name;
/*!
 * @brief String name of @ref TUIK_F5.
 */
extern const char* kTuik_F5_Name;
/*!
 * @brief String name of @ref TUIK_F6.
 */
extern const char* kTuik_F6_Name;
/*!
 * @brief String name of @ref TUIK_F7.
 */
extern const char* kTuik_F7_Name;
/*!
 * @brief String name of @ref TUIK_F8.
 */
extern const char* kTuik_F8_Name;
/*!
 * @brief String name of @ref TUIK_F9.
 */
extern const char* kTuik_F9_Name;
/*!
 * @brief String name of @ref TUIK_F10.
 */
extern const char* kTuik_F10_Name;
/*!
 * @brief String name of @ref TUIK_F11.
 */
extern const char* kTuik_F11_Name;
/*!
 * @brief String name of @ref TUIK_F12.
 */
extern const char* kTuik_F12_Name;
/*!
 * @brief String name of @ref TUIK_F13.
 */
extern const char* kTuik_F13_Name;
/*!
 * @brief String name of @ref TUIK_F14.
 */
extern const char* kTuik_F14_Name;
/*!
 * @brief String name of @ref TUIK_F15.
 */
extern const char* kTuik_F15_Name;
/*!
 * @brief String name of @ref TUIK_F16.
 */
extern const char* kTuik_F16_Name;
/*!
 * @brief String name of @ref TUIK_F17.
 */
extern const char* kTuik_F17_Name;
/*!
 * @brief String name of @ref TUIK_F18.
 */
extern const char* kTuik_F18_Name;
/*!
 * @brief String name of @ref TUIK_F19.
 */
extern const char* kTuik_F19_Name;
/*!
 * @brief String name of @ref TUIK_F20.
 */
extern const char* kTuik_F20_Name;
/*!
 * @brief String name of @ref TUIK_F21.
 */
extern const char* kTuik_F21_Name;
/*!
 * @brief String name of @ref TUIK_F22.
 */
extern const char* kTuik_F22_Name;
/*!
 * @brief String name of @ref TUIK_F23.
 */
extern const char* kTuik_F23_Name;
/*!
 * @brief String name of @ref TUIK_F24.
 */
extern const char* kTuik_F24_Name;
/*!
 * @brief String name of @ref TUIK_F25.
 */
extern const char* kTuik_F25_Name;
/*!
 * @brief String name of @ref TUIK_KP_0.
 */
extern const char* kTuik_KP_0_Name;
/*!
 * @brief String name of @ref TUIK_KP_1.
 */
extern const char* kTuik_KP_1_Name;
/*!
 * @brief String name of @ref TUIK_KP_2.
 */
extern const char* kTuik_KP_2_Name;
/*!
 * @brief String name of @ref TUIK_KP_3.
 */
extern const char* kTuik_KP_3_Name;
/*!
 * @brief String name of @ref TUIK_KP_4.
 */
extern const char* kTuik_KP_4_Name;
/*!
 * @brief String name of @ref TUIK_KP_5.
 */
extern const char* kTuik_KP_5_Name;
/*!
 * @brief String name of @ref TUIK_KP_6.
 */
extern const char* kTuik_KP_6_Name;
/*!
 * @brief String name of @ref TUIK_KP_7.
 */
extern const char* kTuik_KP_7_Name;
/*!
 * @brief String name of @ref TUIK_KP_8.
 */
extern const char* kTuik_KP_8_Name;
/*!
 * @brief String name of @ref TUIK_KP_9.
 */
extern const char* kTuik_KP_9_Name;
/*!
 * @brief String name of @ref TUIK_KP_DECIMAL.
 */
extern const char* kTuik_KP_Decimal_Name;
/*!
 * @brief String name of @ref TUIK_KP_DIVIDE.
 */
extern const char* kTuik_KP_Divide_Name;
/*!
 * @brief String name of @ref TUIK_KP_MULTIPLY.
 */
extern const char* kTuik_KP_Multiply_Name;
/*!
 * @brief String name of @ref TUIK_KP_SUBTRACT.
 */
extern const char* kTuik_KP_Subtract_Name;
/*!
 * @brief String name of @ref TUIK_KP_ADD.
 */
extern const char* kTuik_KP_Add_Name;
/*!
 * @brief String name of @ref TUIK_KP_ENTER.
 */
extern const char* kTuik_KP_Enter_Name;
/*!
 * @brief String name of @ref TUIK_KP_EQUAL.
 */
extern const char* kTuik_KP_Equal_Name;
/*!
 * @brief String name of @ref TUIK_LEFT_SHIFT.
 */
extern const char* kTuik_Left_Shift_Name;
/*!
 * @brief String name of @ref TUIK_LEFT_CONTROL.
 */
extern const char* kTuik_Left_Control_Name;
/*!
 * @brief String name of @ref TUIK_LEFT_ALT.
 */
extern const char* kTuik_Left_Alt_Name;
/*!
 * @brief String name of @ref TUIK_LEFT_SUPER.
 */
extern const char* kTuik_Left_Super_Name;
/*!
 * @brief String name of @ref TUIK_RIGHT_SHIFT.
 */
extern const char* kTuik_Right_Shift_Name;
/*!
 * @brief String name of @ref TUIK_RIGHT_CONTROL.
 */
extern const char* kTuik_Right_Control_Name;
/*!
 * @brief String name of @ref TUIK_RIGHT_ALT.
 */
extern const char* kTuik_Right_Alt_Name;
/*!
 * @brief String name of @ref TUIK_RIGHT_SUPER.
 */
extern const char* kTuik_Right_Super_Name;
/*!
 * @brief String name of @ref TUIK_MENU.
 */
extern const char* kTuik_Menu_Name;
/*! @} */


/*! @name Keyboard Key Functions
 *
 * Functions for dealing with @ref TuiKeyboardKey enum values.
 *  @{ */
/*!
 * @brief Determine if a @ref TuiKeyboardKey enum is valid.
 *
 * @param keyboard_key The @ref TuiKeyboardKey to check.
 *
 * @returns The @ref TuiBoolean result. If keyboard_key is a valid @ref TuiKeyboardKey, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiKeyboardKeyIsValid(TuiKeyboardKey keyboard_key);
/*!
 * @brief Retrieve the string name associated with a @ref TuiKeyboardKey enum.
 *
 * @param keyboard_key The @ref TuiKeyboardKey to get the name of.
 *
 * @returns The string name. @ref TUI_NULL is returned if keyboard_key is an invalid @ref TuiKeyboardKey.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
const char* tuiKeyboardKeyToString(TuiKeyboardKey keyboard_key);
/*!
 * @brief Determine the @ref TuiKeyboardKey enum value associated with a string name.
 *
 * @param str The string name.
 *
 * @returns The @ref TuiKeyboardKey. @ref TUIK_INVALID is returned if no match is found.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiKeyboardKey tuiStringToKeyboardKey(const char* str);
/*!
 * @brief Get the keyboard scancode of a @ref TuiKeyboardKey
 * 
 * @param keyboard_key The @ref TuiKeyboardKey.
 * 
 * @returns The keyboard scancode.
 * 
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
int tuiKeyboardKeyGetScancode(TuiKeyboardKey keyboard_key);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard