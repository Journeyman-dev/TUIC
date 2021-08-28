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
/*! \file detail_mode.h
 */
#ifndef TUIC_DETAIL_MODE_H //header guard
#define TUIC_DETAIL_MODE_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/detail_flag.h>
#include <TUIC/boolean.h>
#include <TUIC/blend_mode.h>
#include <stddef.h> // needed for size_t


/*!
 * @brief Modes of storing and rendering batch data.
 */
typedef enum TuiDetailMode
{
	/*!
	 * \brief The detail mode is invalid.
	 *
	 * This detail mode is returned when an error occurs, and is also used to specify that no detail mode is
	 * defined.
	 */
	TUI_DETAIL_MODE_INVALID = 0,
	/*!
	 * @brief TUI detail mode for full no glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G0_C8NBG_FULL = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_8NBG | TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full no glyph batches with 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G0_C24NBG_FULL = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_24NBG | TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full no glyph batches with 32 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G0_C32NBG_FULL = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_32NBG | TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with no colors.
	 */
	TUI_DETAIL_MODE_G8_C0_FULL =				(TUI_DETAIL_FLAG_GLYPH_8 		| TUI_DETAIL_FLAG_COLOR_0			| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with 4 bit colors (16 color palette).
	 */
	TUI_DETAIL_MODE_G8_C4_FULL =				(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_4			| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8_FULL =				(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_8			| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with an 8 bit foreground color (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8NBG_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_8NBG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with an 8 bit background color (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8NFG_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_8NFG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with an 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_24		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with a 24 bit foreground color (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24NBG_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_24NBG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with a 24 bit background color (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24NFG_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_24NFG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with an 32 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_32		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32NBG_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_32NBG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 8 bit glyph batches with a 32 bit background color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32NFG_FULL =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_32NFG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with no colors.
	 */
	TUI_DETAIL_MODE_G16_C0_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_0			| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with 4 bit colors (16 color palette).
	 */
	TUI_DETAIL_MODE_G16_C4_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_4			| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_8			| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with an 8 bit foreground color (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8NBG_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_8NBG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with an 8 bit background color (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8NFG_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_8NFG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with an 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_24		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with a 24 bit foreground color (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24NBG_FULL =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_24NBG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with a 24 bit background color (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24NFG_FULL =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_24NFG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32_FULL =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_32		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32NBG_FULL =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_32NBG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for full 16 bit glyph batches with a 32 bit background color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32NFG_FULL =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_32NFG		| TUI_DETAIL_FLAG_LAYOUT_FULL),
	/*!
	 * @brief TUI detail mode for sparse no glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G0_C8NBG_SPARSE = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_8NBG | TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse no glyph batches with 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G0_C24NBG_SPARSE = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_24NBG | TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse no glyph batches with 32 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G0_C32NBG_SPARSE = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_32NBG | TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with no colors.
	 */
	TUI_DETAIL_MODE_G8_C0_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_0			| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with 4 bit colors (16 color palette).
	 */
	TUI_DETAIL_MODE_G8_C4_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_4			| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_8			| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with an 8 bit foreground color (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8NBG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_8NBG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with an 8 bit background color (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8NFG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_8NFG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with an 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_24		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with a 24 bit foreground color (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24NBG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_24NBG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with a 24 bit background color (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24NFG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_24NFG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with an 32 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32_SPARSE = 			(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_32		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32NBG_SPARSE = 		(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_32NBG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 8 bit glyph batches with a 32 bit background color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32NFG_SPARSE = 		(TUI_DETAIL_FLAG_GLYPH_8		| TUI_DETAIL_FLAG_COLOR_32NFG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with no colors.
	 */
	TUI_DETAIL_MODE_G16_C0_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_0			| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with 4 bit colors (16 color palette).
	 */
	TUI_DETAIL_MODE_G16_C4_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_4			| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_8			| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with an 8 bit foreground color (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8NBG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_8NBG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with an 8 bit background color (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8NFG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_8NFG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with an 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_24		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with a 24 bit foreground color (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24NBG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_24NBG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with a 24 bit background color (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24NFG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_24NFG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with an 24 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32_SPARSE =			(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_32		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32NBG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_32NBG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for sparse 16 bit glyph batches with a 32 bit background color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32NFG_SPARSE =		(TUI_DETAIL_FLAG_GLYPH_16		| TUI_DETAIL_FLAG_COLOR_32NFG		| TUI_DETAIL_FLAG_LAYOUT_SPARSE),
	/*!
	 * @brief TUI detail mode for free no glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G0_C8NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_8NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free no glyph batches with 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G0_C24NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_24NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free no glyph batches with 32 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G0_C32NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_0 | TUI_DETAIL_FLAG_COLOR_32NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with no colors.
	 */
	TUI_DETAIL_MODE_G8_C0_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_0 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with 4 bit colors (16 color palette).
	 */
	TUI_DETAIL_MODE_G8_C4_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_8 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with an 8 bit foreground color (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_8NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with an 8 bit background color (256 color palette).
	 */
	TUI_DETAIL_MODE_G8_C8NFG_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_8NFG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with an 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_24 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with a 24 bit foreground color (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_24NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with a 24 bit background color (RGB full color).
	 */
	TUI_DETAIL_MODE_G8_C24NFG_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_24NFG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with an 32 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_32 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_32NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 8 bit glyph batches with a 32 bit background color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G8_C32NFG_FREE = (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_32NFG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with no colors.
	 */
	TUI_DETAIL_MODE_G16_C0_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_0 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with 4 bit colors (16 color palette).
	 */
	TUI_DETAIL_MODE_G16_C4_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with 8 bit colors (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_8 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with an 8 bit foreground color (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_8NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with an 8 bit background color (256 color palette).
	 */
	TUI_DETAIL_MODE_G16_C8NFG_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_8NFG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with an 24 bit colors (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_24 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with a 24 bit foreground color (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_24NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with a 24 bit background color (RGB full color).
	 */
	TUI_DETAIL_MODE_G16_C24NFG_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_24NFG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with an 24 bit colors (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_32 | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with a 32 bit foreground color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32NBG_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_32NBG | TUI_DETAIL_FLAG_LAYOUT_FREE),
	/*!
	 * @brief TUI detail mode for free 16 bit glyph batches with a 32 bit background color (RGBA full color).
	 */
	TUI_DETAIL_MODE_G16_C32NFG_FREE = (TUI_DETAIL_FLAG_GLYPH_16 | TUI_DETAIL_FLAG_COLOR_32NFG | TUI_DETAIL_FLAG_LAYOUT_FREE)
} TuiDetailMode;


/*! @name Detail Mode Constant Tile Byte Sizes
 *  These constants act as constants containing the size of a single tile in bytes for each supported detail mode.
 *  @{ */
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_0 and color flag @ref TUI_DETAIL_FLAG_COLOR_8NBG.
 */
extern const size_t kTui_Detail_G0_C8NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_0 and color flag @ref TUI_DETAIL_FLAG_COLOR_24NBG.
 */
extern const size_t kTui_Detail_G0_C24NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_0 and color flag @ref TUI_DETAIL_FLAG_COLOR_32NBG.
 */
extern const size_t kTui_Detail_G0_C32NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_0.
 */
extern const size_t kTui_Detail_G8_C0_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_4.
 */
extern const size_t kTui_Detail_G8_C4_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_8.
 */
extern const size_t kTui_Detail_G8_C8_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_8NBG.
 */
extern const size_t kTui_Detail_G8_C8NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_8NFG.
 */
extern const size_t kTui_Detail_G8_C8NFG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_24.
 */
extern const size_t kTui_Detail_G8_C24_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_24NBG.
 */
extern const size_t kTui_Detail_G8_C24NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_24NFG.
 */
extern const size_t kTui_Detail_G8_C24NFG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_32.
 */
extern const size_t kTui_Detail_G8_C32_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_32NBG.
 */
extern const size_t kTui_Detail_G8_C32NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_8 and color flag @ref TUI_DETAIL_FLAG_COLOR_32NFG.
 */
extern const size_t kTui_Detail_G8_C32NFG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_0.
 */
extern const size_t kTui_Detail_G16_C0_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_4.
 */
extern const size_t kTui_Detail_G16_C4_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_8.
 */
extern const size_t kTui_Detail_G16_C8_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_8NBG.
 */
extern const size_t kTui_Detail_G16_C8NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_8NFG.
 */
extern const size_t kTui_Detail_G16_C8NFG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_24.
 */
extern const size_t kTui_Detail_G16_C24_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_24NBG.
 */
extern const size_t kTui_Detail_G16_C24NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_24NFG.
 */
extern const size_t kTui_Detail_G16_C24NFG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_32.
 */
extern const size_t kTui_Detail_G16_C32_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_32NBG.
 */
extern const size_t kTui_Detail_G16_C32NBG_Size;
/*!
 * @brief Tile byte size of detail modes with glyph flag @ref TUI_DETAIL_FLAG_GLYPH_16 and color flag @ref TUI_DETAIL_FLAG_COLOR_32NFG.
 */
extern const size_t kTui_Detail_G16_C32NFG_Size;
/*! @} */


/*! @name Detail Mode Names
 *  These are const string names of @ref TuiDetailMode enum values.
 *  @{ */
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C8NBG_FULL.
 */
extern const char* kTui_Detail_G0_C8NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C24NBG_FULL.
 */
extern const char* kTui_Detail_G0_C24NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C32NBG_FULL.
 */
extern const char* kTui_Detail_G0_C32NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C0_FULL.
 */
extern const char* kTui_Detail_G8_C0_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C4_FULL.
 */
extern const char* kTui_Detail_G8_C4_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8_FULL.
 */
extern const char* kTui_Detail_G8_C8_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8NBG_FULL.
 */
extern const char* kTui_Detail_G8_C8NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8NFG_FULL.
 */
extern const char* kTui_Detail_G8_C8NFG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24_FULL.
 */
extern const char* kTui_Detail_G8_C24_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24NBG_FULL.
 */
extern const char* kTui_Detail_G8_C24NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24NFG_FULL.
 */
extern const char* kTui_Detail_G8_C24NFG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32_FULL.
 */
extern const char* kTui_Detail_G8_C32_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32NBG_FULL.
 */
extern const char* kTui_Detail_G8_C32NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32NFG_FULL.
 */
extern const char* kTui_Detail_G8_C32NFG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C0_FULL.
 */
extern const char* kTui_Detail_G16_C0_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C4_FULL.
 */
extern const char* kTui_Detail_G16_C4_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8_FULL.
 */
extern const char* kTui_Detail_G16_C8_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8NBG_FULL.
 */
extern const char* kTui_Detail_G16_C8NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8NFG_FULL.
 */
extern const char* kTui_Detail_G16_C8NFG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24_FULL.
 */
extern const char* kTui_Detail_G16_C24_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24NBG_FULL.
 */
extern const char* kTui_Detail_G16_C24NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24NFG_FULL.
 */
extern const char* kTui_Detail_G16_C24NFG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32_FULL.
 */
extern const char* kTui_Detail_G16_C32_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32NBG_FULL.
 */
extern const char* kTui_Detail_G16_C32NBG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32NFG_FULL.
 */
extern const char* kTui_Detail_G16_C32NFG_Full_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C8NBG_SPARSE.
 */
extern const char* kTui_Detail_G0_C8NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C24NBG_SPARSE.
 */
extern const char* kTui_Detail_G0_C24NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C32NBG_SPARSE.
 */
extern const char* kTui_Detail_G0_C32NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C0_SPARSE.
 */
extern const char* kTui_Detail_G8_C0_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C4_SPARSE.
 */
extern const char* kTui_Detail_G8_C4_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8_SPARSE.
 */
extern const char* kTui_Detail_G8_C8_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8NBG_SPARSE.
 */
extern const char* kTui_Detail_G8_C8NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8NFG_SPARSE.
 */
extern const char* kTui_Detail_G8_C8NFG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24_SPARSE.
 */
extern const char* kTui_Detail_G8_C24_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24NBG_SPARSE.
 */
extern const char* kTui_Detail_G8_C24NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24NFG_SPARSE.
 */
extern const char* kTui_Detail_G8_C24NFG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32_SPARSE.
 */
extern const char* kTui_Detail_G8_C32_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32NBG_SPARSE.
 */
extern const char* kTui_Detail_G8_C32NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32NFG_SPARSE.
 */
extern const char* kTui_Detail_G8_C32NFG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C0_SPARSE.
 */
extern const char* kTui_Detail_G16_C0_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C4_SPARSE.
 */
extern const char* kTui_Detail_G16_C4_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8_SPARSE.
 */
extern const char* kTui_Detail_G16_C8_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8NBG_SPARSE.
 */
extern const char* kTui_Detail_G16_C8NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8NFG_SPARSE.
 */
extern const char* kTui_Detail_G16_C8NFG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24_SPARSE.
 */
extern const char* kTui_Detail_G16_C24_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24NBG_SPARSE.
 */
extern const char* kTui_Detail_G16_C24NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24NFG_SPARSE.
 */
extern const char* kTui_Detail_G16_C24NFG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32_SPARSE.
 */
extern const char* kTui_Detail_G16_C32_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32NBG_SPARSE.
 */
extern const char* kTui_Detail_G16_C32NBG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32NFG_SPARSE.
 */
extern const char* kTui_Detail_G16_C32NFG_Sparse_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C8NBG_FREE.
 */
extern const char* kTui_Detail_G0_C8NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C24NBG_FREE.
 */
extern const char* kTui_Detail_G0_C24NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_G0_C32NBG_FREE.
 */
extern const char* kTui_Detail_G0_C32NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C0_FREE.
 */
extern const char* kTui_Detail_G8_C0_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C4_FREE.
 */
extern const char* kTui_Detail_G8_C4_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8_FREE.
 */
extern const char* kTui_Detail_G8_C8_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8NBG_FREE.
 */
extern const char* kTui_Detail_G8_C8NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C8NFG_FREE.
 */
extern const char* kTui_Detail_G8_C8NFG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24_FREE.
 */
extern const char* kTui_Detail_G8_C24_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24NBG_FREE.
 */
extern const char* kTui_Detail_G8_C24NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C24NFG_FREE.
 */
extern const char* kTui_Detail_G8_C24NFG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32_FREE.
 */
extern const char* kTui_Detail_G8_C32_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32NBG_FREE.
 */
extern const char* kTui_Detail_G8_C32NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G8_C32NFG_FREE.
 */
extern const char* kTui_Detail_G8_C32NFG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C0_FREE.
 */
extern const char* kTui_Detail_G16_C0_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C4_FREE.
 */
extern const char* kTui_Detail_G16_C4_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8_FREE.
 */
extern const char* kTui_Detail_G16_C8_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8NBG_FREE.
 */
extern const char* kTui_Detail_G16_C8NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C8NFG_FREE.
 */
extern const char* kTui_Detail_G16_C8NFG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24_FREE.
 */
extern const char* kTui_Detail_G16_C24_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24NBG_FREE.
 */
extern const char* kTui_Detail_G16_C24NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C24NFG_FREE.
 */
extern const char* kTui_Detail_G16_C24NFG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32_FREE.
 */
extern const char* kTui_Detail_G16_C32_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32NBG_FREE.
 */
extern const char* kTui_Detail_G16_C32NBG_Free_Name;
/*!
 * @brief String name of @ref TUI_DETAIL_MODE_G16_C32NFG_FREE.
 */
extern const char* kTui_Detail_G16_C32NFG_Free_Name;
/* @) */


/*! @name Detail Mode Functions
 *
 * Functions for dealing with @ref TuiDetailMode enum values.
 *  @{ */
/*!
 * @brief Get the glyph @ref TuiDetailFlag of a @ref TuiDetailMode.
 *
 * @param detail_mode The @ref TuiDetailMode.
 *
 * @returns The glyph @ref TuiDetailFlag.
 * 
 * @errors This function can haves no errors.
 * 
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiDetailFlag tuiDetailGetGlyphFlag(TuiDetailMode detail_mode);
/*!
 * @brief Get the color @ref TuiDetailFlag of a @ref TuiDetailMode.
 *
 * @param detail_mode The @ref TuiDetailMode.
 *
 * @returns The color @ref TuiDetailFlag.
 *
 * @errors This function can haves no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiDetailFlag tuiDetailGetColorFlag(TuiDetailMode detail_mode);
/*!
 * @brief Get the laoyout @ref TuiDetailFlag of a @ref TuiDetailMode.
 *
 * @param detail_mode The @ref TuiDetailMode.
 *
 * @returns The laoyout @ref TuiDetailFlag.
 *
 * @errors This function can haves no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiDetailFlag tuiDetailGetLayoutFlag(TuiDetailMode detail_mode);
/*!
 * @brief Get the bytes size of a glyph and color @ref TuiDetailFlag combination.
 *
 * @param glyph_flag The glyph @ref TuiDetailFlag.
 * 
 * @param color_flat The color @ref TuiDetailFlag.
 *
 * @returns The byte size of the tile data per tile.
 *
 * @errors This function can haves no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
size_t tuiDetailGetTileByteSize(TuiDetailFlag glyph_flag, TuiDetailFlag color_flag);
/*!
 * @brief Get if the @ref TuiDetailMode requires a @ref TuiPalette.
 *
 * @param detail_mode The @ref TuiDetailMode.
 *
 * @returns The @ref TuiBoolean result. If detail_mode is a requires a @ref TuiPalette for rendering batch data, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can haves no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiDetailHasPalette(TuiDetailMode detail_mode);
/*!
 * @brief Get if the @ref TuiDetailMode requires a @ref TuiAtlas.
 *
 * @param detail_mode The @ref TuiDetailMode.
 *
 * @returns The @ref TuiBoolean result. If detail_mode is a requires a @ref TuiAtlas for rendering batch data, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can haves no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiDetailHasAtlas(TuiDetailMode detail_mode);
/*!
 * @brief Determine if a @ref TuiDetailMode enum is valid.
 *
 * @param detail_mode The @ref TuiDetailMode to check.
 *
 * @returns The @ref TuiBoolean result. If detail_mode is a valid @ref TuiDetailMode, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiDetailIsValid(TuiDetailMode detail_mode);
/*!
 * @brief Determine if a @ref TuiDetailMode enum contains a @ref TuiDetailFlag.
 *
 * @param detail_mode The @ref TuiDetailMode to check for the flag.
 * @param detail_flag The @ref TuiDetailFlag to check for.
 *
 * @returns The @ref TuiBoolean result. If detail_mode contains the detail_flag, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiDetailHasFlag(TuiDetailMode detail_mode, TuiDetailFlag detail_flag);
/*!
 * @brief Get if a @ref TuiBlendMode is compatible with a @ref TuiDetailMode.
 *
 * @param detail_mode The @ref TuiDetailMode.
 * @param blend_mode The @ref TuiBlendMode.
 *
 * @returns The @ref TuiBoolean result. If detail_mode is compatible with the blend_mode, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiModesAreCompatible(TuiDetailMode detail_mode, TuiBlendMode blend_mode);
/*!
 * @brief Retrieve the string name associated with a @ref TuiDetailMode enum.
 *
 * @param detail_mode The @ref TuiDetailMode to get the name of.
 *
 * @returns The string name. @ref TUI_NULL is returned if detail_mode is an invalid @ref TuiDetailMode.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
const char* tuiDetailModeToString(TuiDetailMode detail_mode);
/*!
 * @brief Determine the @ref TuiDetailMode enum value associated with a string name.
 *
 * @param str The string name.
 *
 * @returns The @ref TuiDetailMode. @ref TUI_DETAIL_MODE_INVALID is returned if no match is found.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiDetailMode tuiStringToDetailMode(const char* string);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard