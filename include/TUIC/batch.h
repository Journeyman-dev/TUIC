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
/*! \file batch.h
 */
#ifndef TUIC_BATCH_H //header guard
#define TUIC_BATCH_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/types.h>
#include <TUIC/detail_mode.h>
#include <TUIC/boolean.h>


/*! @name Batch Functions
 *
 * These functions are used for manipulating @ref TuiBatch opaque objects.
 *  @{ */
/*!
 * @brief Create a new @ref TuiBatch.
 *
 * @param tui_detail_mode The @ref TuiDetailMode that the @ref TuiBatch will use to organize its tile data.
 * @param tiles_wide The amount of tiles wide of the @ref TuiBatch data.
 * @param tiles_tall The amount of tiles tall of the @ref TuiBatch data.
 *
 * @returns The created @ref TuiBatch. @ref TUI_NULL is returned if an error occurs.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_INVALID_BATCH_DIMENSIONS and @ref TUI_ERROR_INVALID_DETAIL_MODE. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 * 
 * @pointer_lifetime The returned @ref TuiBatch must be destroyed using the function @ref tuiBatchDestroy().
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
TuiBatch tuiBatchCreate(TuiDetailMode detail_mode, int tiles_wide, int tiles_tall);
/*!
 * @brief  Destroy @ref TuiBatch and correctly dispose of of its internally managed resources.
 *
 * @param batch The @ref TuiBatch to destroy.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
void tuiBatchDestroy(TuiBatch batch);
/*!
 * @brief  Get the @ref TuiDetailMode used by a @ref TuiBatch.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns The @ref TuiDetailMode of the batch. 0 is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
TuiDetailMode tuiBatchGetDetail(TuiBatch batch);
/*!
 * @brief Set new tile dimensions of a @ref TuiBatch and clear its data.
 *
 * @param batch The @ref TuiBatch to resize.
 * @param tiles_wide The new batch tiles wide.
 * @param tiles_height The new batch tiles tall.
 * @param reserve_extra A @ref TuiBoolean enum that specifies if extra space in the data array should be rserved for future resizes instead of deallocated.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_DIMENSIONS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
void tuiBatchSetTileDimensions(TuiBatch batch, int tiles_wide, int tiles_tall, TuiBoolean reserve_extra);
/*!
 * @brief Get the tile dimensions of a @ref TuiBatch.
 *
 * @param batch The @ref TuiBatch to get the tile dimensions of.
 * @param tiles_wide A pointer to where the tile width of the @ref TuiBatch will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param tiles_height A pointer to where the tile height of the @ref TuiBatch will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
void tuiBatchGetTileDimensions(TuiBatch batch, int* tiles_wide, int* tiles_tall);
/*!
 * @brief Get the width of a @ref TuiBatch in tiles.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns The tiles wide. 0 is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
int tuiBatchGetTilesWide(TuiBatch batch);
/*!
 * @brief Get the height of a @ref TuiBatch in tiles.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns The tiles tall. 0 is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
int tuiBatchGetTilesTall(TuiBatch batch);
/*!
 * @brief Get the size of the data array of a @ref TuiBatch in bytes.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns The size of the data array in bytes. 0 is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
int tuiBatchGetDataSize(TuiBatch batch);
/*!
 * @brief Get the size of the data array of a @ref TuiBatch in bytes including reserved space.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns The size of the data array in bytes, including reserved space. 0 is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
int tuiBatchGetReservedSize(TuiBatch batch);
/*!
 * @brief Get the amount of tiles currently set in a @ref TuiBatch.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns The amount of tiles that are currently set. 0 is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access. 
 */
int tuiBatchGetTileCount(TuiBatch batch);
/*!
 * @brief Get a pointer to the data array of a @ref TuiBatch.
 *
 * @param batch The @ref TuiBatch.
 *
 * @returns A pointer to the data array. TUI_NULL is returned if an error occurs.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return.
 * 
 * @pointer_lifetime The returned pointer shares its lifetime with the @ref TuiBatch it was taken from, and must not be manually freed.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
const uint8_t* tuiBatchGetData(TuiBatch batch);
/*!
 * @brief Clear the data of a @ref TuiBatch to 0.
 *
 * @param batch The @ref TuiBatch to clear.
 *
 * @errors This function can have the error @ref TUI_ERROR_NULL_BATCH and immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread. However, it is important to manipulate and use each @ref TuiBatch on only one thread at a time to ensure safe memory access.
 */
void tuiBatchClear(TuiBatch batch);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C0_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C0_FULL(TuiBatch batch, int x, int y, uint8_t glyph);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C4_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_and_bg The 8 bit value that contains both the foreground and background color palette ids.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C4_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t colors);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C8_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C8_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C8NBG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C8NBG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C8NFG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C8NFG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C24_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C24_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C24NBG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C24NBG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C24NFG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C24NFG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C32_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C32_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C32NBG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C32NBG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C32NFG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C32NFG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C0_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C0_FULL(TuiBatch batch, int x, int y, uint16_t glyph);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C4_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_and_bg The 8 bit value that contains both the foreground and background color palette ids.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C4_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t colors);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C8_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C8_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C8NBG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C8NBG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C8NFG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C8NFG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C24_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C24_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C24NBG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C24NBG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C24NFG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C24NFG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C32_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C32_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C32NBG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C32NBG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C32NFG_FULL detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C32NFG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C0_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C0_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C4_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_and_bg The 8 bit value that contains both the foreground and background color palette ids.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C4_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t colors);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C8_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C8_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C8NBG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C8NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C8NFG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C8NFG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C24_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C24_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C24NBG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C24NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C24NFG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C24NFG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C32_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C32_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C32NBG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C32NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G8_C32NFG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 8 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G8_C32NFG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C0_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C0_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C4_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_and_bg The 8 bit value that contains both the foreground and background color palette ids.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C4_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t colors);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C8_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C8_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C8NBG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg The 8 bit value that contains the foreground color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C8NBG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C8NFG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param bg The 8 bit value that contains the background color palette id.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C8NFG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C24_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C24_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C24NBG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C24NBG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C24NFG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C24NFG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C32_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C32_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C32NBG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param fg_r The 8 bit value that contains the foreground color red color value.
 * @param fg_g The 8 bit value that contains the foreground color green color value.
 * @param fg_b The 8 bit value that contains the foreground color blue color value.
 * @param fg_a The 8 bit value that contains the foreground color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C32NBG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a);
/*!
 * @brief Set a tile of a @ref TuiBatch that uses @ref TUI_DETAIL_MODE_G16_C32NFG_SPARSE detail mode.
 *
 * @param batch The @ref TuiBatch.
 * @param x The x coordinate of the tile.
 * @param y The y coordinate of the tile.
 * @param glyph The 16 bit glyph id.
 * @param bg_r The 8 bit value that contains the background color red color value.
 * @param bg_g The 8 bit value that contains the background color green color value.
 * @param bg_b The 8 bit value that contains the background color blue color value.
 * @param bg_a The 8 bit value that contains the background color alpha color value.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_BATCH and @ref TUI_ERROR_INVALID_BATCH_SETTER. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function can be called safely on any thread at any time.
 */
void tuiBatchSetTile_G16_C32NFG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard