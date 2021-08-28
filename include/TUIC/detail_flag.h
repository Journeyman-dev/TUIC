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
/*! \file detail_flag.h
 */
#ifndef TUIC_DETAIL_FLAG_H //header guard
#define TUIC_DETAIL_FLAG_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/boolean.h>


/*!
 * @brief Bitflag components that are combined into @ref TuiDetailMode enums.
 */
typedef enum TuiDetailFlag
{
	/*!
	 * \brief The detail flag is invalid.
	 *
	 * This detail flag is returned when an error occurs, and is also used to specify that no detail flag is
	 * defined.
	 */
	TUI_DETAIL_FLAG_INVALID = 0,
	/*!
	 * @brief TUI detail mode glyph flag for no glyphs. This glyph flag can only work with color flags with only a foreground color.
	 */
	TUI_DETAIL_FLAG_GLYPH_0 = (1 << 0),
	/*!
	 * @brief TUI detail mode glyph flag for 8 bit glyphs. This supports up to 256 unique glyphs. This size is optimal if you only want to use code page 437 for rendering.
	 */
	TUI_DETAIL_FLAG_GLYPH_8 = (1 << 1),
	/*!
	 * @brief Detail mode glyph flag for 16 bit glyphs. This supports up to 65536 unique glyphs per @ref TuiAtlas.
	 */
	TUI_DETAIL_FLAG_GLYPH_16 = (1 << 2),
	/*!
	 * @brief TUI detail mode flag for no colors. This shrinks the byte size per tile by not requiring any information about foreground and background colors.
	 */
	TUI_DETAIL_FLAG_COLOR_0 = (1 << 3),
	/*!
	 * @brief TUI detail mode color flag for 4 bit colors. This enables use of a 16 color @ref TuiPalette for colors.
	 */
	TUI_DETAIL_FLAG_COLOR_4 = (1 << 4),
	/*!
	 * @brief TUI detail mode color flag for 8 bit colors. This enables use of a 256 color @ref TuiPalette for colors.
	 */
	TUI_DETAIL_FLAG_COLOR_8 = (1 << 5),
	/*!
	 * @brief TUI detail mode color flag for 8 bit colors with no foreground color. This enables use of a 256 color @ref TuiPalette for colors.
	 */
	TUI_DETAIL_FLAG_COLOR_8NFG = (1 << 6),
	/*!
	 * @brief TUI detail mode color flag for 8 bit colors with no background color. This enables use of a 256 color @ref TuiPalette for colors.
	 */
	TUI_DETAIL_FLAG_COLOR_8NBG = (1 << 7),
	/*!
	 * @brief TUI detail mode color flag for 24 bit colors. This enables use of 24 bit full colors with RGB components.
	 */
	TUI_DETAIL_FLAG_COLOR_24 = (1 << 8),
	/*!
	 * @brief TUI detail mode color flag for a single 24 bit background color per tile. This enables use of 24 bit full colors with RGB components.
	 */
	TUI_DETAIL_FLAG_COLOR_24NFG = (1 << 9),
	/*!
	 * @brief TUI detail mode color flag for a single 24 bit foreground color per tile. This enables use of 24 bit full colors with RGB components.
	 */
	TUI_DETAIL_FLAG_COLOR_24NBG = (1 << 10),
	/*!
	 * @brief TUI detail mode color flag for 32 bit colors. This enables use of 32 bit full colors with RGBA components.
	 */
	TUI_DETAIL_FLAG_COLOR_32 = (1 << 11),
	/*!
	 * @brief TUI detail mode color flag for a single 32 bit background color per tile. This enables use of 32 bit full colors with RGBA components.
	 */
	TUI_DETAIL_FLAG_COLOR_32NFG = (1 << 12),
	/*!
	 * @brief TUI detail mode color flag for a single 32 bit foreground color per tile. This enables use of 32 bit full colors with RGBA components.
	 */
	TUI_DETAIL_FLAG_COLOR_32NBG = (1 << 13),
	/*!
	 * @brief TUI detail mode layout flag for full batches of tiles without increased batch size for coordinate information. This is most optimal for rendering in situations where almost all tiles are updated every frame.
	 */
	TUI_DETAIL_FLAG_LAYOUT_FULL = (1 << 14),
	/*!
	 * @brief TUI detail mode layout flag for rendering tiles as needed instead of every tile every frame. This is most optimal for rendering in situations where few tiles are updated every frame.
	 */
	TUI_DETAIL_FLAG_LAYOUT_SPARSE = (1 << 15),
	/*!
	 * @brief TUI detail mode layout flag for renderint tiles at pixel positions on the screen, independently of a grid.
	 */
	TUI_DETAIL_FLAG_LAYOUT_FREE = (1 << 16),
	/*!
	 * @brief All glyph detail bitflags.
	 */
	TUI_DETAIL_FLAG_GLYPH_BITS = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_GLYPH_16),
	/*!
	 * @brief All color detail bitflags.
	 */
	TUI_DETAIL_FLAG_COLOR_BITS = (TUI_DETAIL_FLAG_COLOR_0 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_COLOR_8 | TUI_DETAIL_FLAG_COLOR_8NBG |
		TUI_DETAIL_FLAG_COLOR_8NFG | TUI_DETAIL_FLAG_COLOR_24 | TUI_DETAIL_FLAG_COLOR_24NBG | TUI_DETAIL_FLAG_COLOR_24NFG | 
		TUI_DETAIL_FLAG_COLOR_32 | TUI_DETAIL_FLAG_COLOR_32NBG | TUI_DETAIL_FLAG_COLOR_32NFG),
	/*!
	 * @brief All layout detail bitflags.
	 */
	TUI_DETAIL_FLAG_LAYOUT_BITS = (TUI_DETAIL_FLAG_LAYOUT_FULL | TUI_DETAIL_FLAG_LAYOUT_SPARSE | TUI_DETAIL_FLAG_LAYOUT_FREE)
} TuiDetailFlag;


/*! @name Detail Mode Flag Names
 *
 * Constant string names of each detali flag.
 *  @{ */
 /*!
  * @brief String name of @ref TUI_DETAIL_FLAG_GLYPH_0.
  */
extern const char* kTui_Detail_Flag_G0_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_GLYPH_8.
 */
extern const char* kTui_Detail_Flag_G8_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_GLYPH_16.
 */
extern const char* kTui_Detail_Flag_G16_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_0.
 */
extern const char* kTui_Detail_Flag_C0_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_4.
 */
extern const char* kTui_Detail_Flag_C4_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_8.
 */
extern const char* kTui_Detail_Flag_C8_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_8NBG.
 */
extern const char* kTui_Detail_Flag_C8NBG_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_8NFG.
 */
extern const char* kTui_Detail_Flag_C8NFG_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_24.
 */
extern const char* kTui_Detail_Flag_C24_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_24NBG.
 */
extern const char* kTui_Detail_Flag_C24NBG_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_24NFG.
 */
extern const char* kTui_Detail_Flag_C24NFG_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_32.
 */
extern const char* kTui_Detail_Flag_C32_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_32NBG.
 */
extern const char* kTui_Detail_Flag_C32NBG_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_COLOR_32NFG.
 */
extern const char* kTui_Detail_Flag_C32NFG_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_LAYOUT_FULL.
 */
extern const char* kTui_Detail_Flag_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_LAYOUT_SPARSE.
 */
extern const char* kTui_Detail_Flag_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_FLAG_LAYOUT_FREE.
 */
extern const char* kTui_Detail_Flag_Free_Name;
/*! @} */


/*! @name Detail Mode Flag Function
 *
 * Functions for dealing with @ref TuiDetailFlag enum values.
 *  @{ */
/*!
 * @brief Determine if a @ref TuiDetailFlag enum is valid.
 *
 * @param detail_flag The @ref TuiDetailFlag to check.
 *
 * @returns The @ref TuiBoolean result. If detail_flag is a valid @ref TuiDetailFlag, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiDetailFlagIsValid(TuiDetailFlag detail_flag);
/*!
 * @brief Retrieve the string name associated with a @ref TuiDetailFlag enum.
 *
 * @param detail_flag The @ref TuiDetailFlag to get the name of.
 *
 * @returns The string name. @ref TUI_NULL is returned if cursor_mode is an invalid @ref TuiDetailFlag.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
const char* tuiDetailFlagToString(TuiDetailFlag detail_flag);
/*!
 * @brief Determine the @ref TuiDetailFlag enum value associated with a string name.
 *
 * @param str The string name.
 *
 * @returns The TuiDetailFlag. @ref TUI_DETAIL_FLAG_INVALID is returned if no match is found.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiDetailFlag tuiStringToDetailFlag(const char* string);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard