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
/*! \file objects.h
 */
#ifndef TUIC_OPAQUE_OBJECTS_H // header guard
#define TUIC_OPAQUE_OBJECTS_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <stdint.h>
#include <TUIC/types.h>
#include <GLFW/glfw3.h>
#include <TUIC/blend_mode.h>
#include <TUIC/filter_mode.h>
#include <TUIC/desktop_callback.h>

typedef struct TuiSystem_s
{
	TuiBoolean MultiWindow;

	TuiBoolean BaseWindowClaimed; //for non multi-window systems. if the base window is claimed by the window, this is true.

	GLFWwindow* BaseWindow;

	void* ApiData;
} TuiSystem_s;

typedef TuiSystem_s* TuiSystem;

TuiSystem tui_get_system();

typedef struct TuiWindow_s
{
	void* UserPointer;

	tuiWindowMoveFunction WindowMoveCallback;

	tuiWindowCloseFunction WindowCloseCallback;

	tuiWindowRefreshFunction WindowRefreshCallback;

	tuiWindowFocusFunction WindowFocusCallback;

	tuiWindowIconifyFunction WindowIconifyCallback;

	tuiWindowMaximizeFunction WindowMaximizeCallback;

	tuiWindowResizeFunction WindowResizeCallback;

	tuiWindowContentScaleFunction WindowContentScaleCallback;

	tuiMouseButtonFunction MouseButtonCallback;

	tuiCursorMoveFunction CursorMoveCallback;

	tuiCursorEnterFunction CursorEnterCallback;

	tuiMouseScrollFunction MouseScrollCallback;

	tuiKeyboardKeyFunction KeyboardKeyCallback;

	tuiCharFunction CharCallback;

	tuiFileDropFunction FileDropCallback;

	GLFWwindow* GlfwWindow;

	size_t PixelWidth;

	size_t PixelHeight;

	void* ApiData;
} TuiWindow_s;

typedef struct TuiAtlas_s
{

	TuiBlendMode BlendMode;

	size_t AtlasType;

	size_t ChannelCount;

	size_t PixelWidth;

	size_t PixelHeight;

	size_t TileWidth;

	size_t TileHeight;

	size_t PixelDataSize;

	size_t GlyphCount;

	size_t GridGlyphsWide;

	size_t GridGlyphsTall;

	void* ApiData;
} TuiAtlas_s;

typedef struct TuiTexture_s
{

	TuiFilterMode FilterMode;

	size_t PixelWidth;

	size_t PixelHeight;

	size_t ChannelCount;

	void* ApiData;
} TuiTexture_s;

typedef struct TuiPalette_s
{

	int ChannelCount;

	size_t ColorCount;	

	void* ApiData;
} TuiPalette_s;

typedef struct TuiPanel_s
{

	size_t PixelWidth;

	size_t PixelHeight;

	void* ApiData;
} TuiPanel_s;

typedef struct TuiBatch_s
{

	size_t DetailMode;

	uint8_t* Data;

	size_t UsedDataSize;

	size_t ReservedDataSize;

	size_t BytesPerTile;

	size_t TileCount;

	size_t TilesWide;

	size_t TilesTall;

	TuiBoolean IsLargeSparseWide;

	TuiBoolean IsLargeSparseTall;

	uint16_t* SparseUsedIndices;

	size_t SparseUsedIndicesSize;
} TuiBatch_s;

typedef struct TuiImage_s
{

	size_t ChannelCount;

	size_t PixelWidth;

	size_t PixelHeight;

	size_t PixelDataSize;

	uint8_t* PixelData;
} TuiImage_s;

#ifdef __cplusplus // extern C guard
}
#endif
#endif // header guard