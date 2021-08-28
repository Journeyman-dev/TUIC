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
#include <TUIC/tuic.h>
#include "objects.h"
#include "image_inline.h"
#include "opengl33.h"
#include "glfw_error_check.h"

static int sPanelCount = 0;

TuiPanel tuiPanelCreate(int pixel_width, int pixel_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_PANEL_DIMENSIONS, __func__);
		return TUI_NULL;
	}

	TuiPanel panel = tuiAllocate(sizeof(TuiPanel_s));
	panel->PixelWidth = (size_t)pixel_width;
	panel->PixelHeight = (size_t)pixel_height;
	panel->ApiData = TUI_NULL;
	TuiErrorCode error_code = tuiPanelCreate_Opengl33(panel);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiPanelDestroy(panel);
		tuiFree(panel);
		tuiDebugError(error_code, __func__);
		return TUI_NULL;
	}
	sPanelCount++;
	return panel;
}

void tuiPanelDestroy(TuiPanel panel)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}

	glfwMakeContextCurrent(system->BaseWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	TuiErrorCode error_code = tuiPanelDestroy_Opengl33(panel);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
	sPanelCount--;
	tuiFree(panel);
}

int tuiGetPanelCount()
{
	return sPanelCount;
}

TuiImage tuiPanelGetImage(TuiPanel panel)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return TUI_NULL;
	}

	size_t p_width = 0;
	size_t p_height = 0;
	uint8_t* pixel_data = TUI_NULL;
	TuiErrorCode error_code = tuiPanelGetPixels_Opengl33(panel, &p_width, &p_height, &pixel_data);
	if (error_code != TUI_ERROR_NONE)
	{
		if (pixel_data != TUI_NULL)
		{
			tuiFree(pixel_data);
		}
		tuiDebugError(error_code, __func__);
		return TUI_NULL;
	}
	TuiImage image = _CreateImage(p_width, p_height, 4, pixel_data, TUI_FALSE);
	return image;
}

void tuiPanelWriteImage(TuiPanel panel, TuiImage image)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (image == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_IMAGE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelGetPixels_Opengl33(panel, &image->PixelWidth, &image->PixelHeight, &(image->PixelData));
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

uint8_t* tuiPanelGetPixels(TuiPanel panel, int* pixel_width, int* pixel_height, uint8_t* fill_pixels)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return TUI_NULL;
	}

	size_t o_width, o_height;
	uint8_t* pixels = fill_pixels;
	if (pixels == TUI_NULL)
	{
		pixels = (uint8_t*)tuiAllocate((size_t)pixel_width * (size_t)pixel_height);
	}
	TuiErrorCode error_code = tuiPanelGetPixels_Opengl33(panel, &o_width, &o_height, &pixels);
	if (error_code != TUI_ERROR_NONE)
	{
		if (fill_pixels == TUI_NULL)
		{
			tuiFree(pixels);
		}
		tuiDebugError(error_code, __func__);
		return TUI_NULL;;
	}
	*pixel_width = (int)o_width;
	*pixel_height = (int)o_height;
	return pixels;
} 

void tuiPanelClearColor(TuiPanel panel, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	
	TuiErrorCode error_code = tuiPanelClearColor_Opengl33(panel, r, g, b, a);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelSetPixelDimensions(TuiPanel panel, int pixel_width, int pixel_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_PANEL_DIMENSIONS, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelSetSize_Opengl33(panel, (size_t)pixel_width, (size_t)pixel_height);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelGetPixelDimensions(TuiPanel panel, int* pixel_width, int* pixel_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}

	if (pixel_width != TUI_NULL)
	{
		*pixel_width = (int)panel->PixelWidth;
	}
	if (pixel_height != TUI_NULL)
	{
		*pixel_height = (int)panel->PixelHeight;
	}
}

int tuiPanelGetPixelWidth(TuiPanel panel)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return 0;
	}

	return panel->PixelWidth;
}

int tuiPanelGetPixelHeight(TuiPanel panel)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return 0;
	}

	return panel->PixelHeight;
}


void tuiPanelDrawBatch(TuiPanel panel, TuiAtlas atlas, TuiPalette palette, TuiBatch batch)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (atlas == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_ATLAS, __func__);
		return;
	}
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (tuiDetailHasPalette(batch->DetailMode) == TUI_TRUE && palette == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_PALETTE_REQUIRED, __func__);
		return;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
	{
		TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
		if (batch_sparse->TileCount == 0)
		{
			return;
		}
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
	{
		TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
		if (batch_free->TileCount == 0)
		{
			return;
		}
	}
	default:
		break;
	}

	TuiErrorCode error_code = tuiPanelDrawBatch_Opengl33(panel, atlas, palette, batch, 0, panel->PixelWidth, 0, panel->PixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawBatchTransformed(TuiPanel panel, TuiAtlas atlas, TuiPalette palette, TuiBatch batch, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (atlas == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_ATLAS, __func__);
		return;
	}
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (tuiDetailHasPalette(batch->DetailMode) == TUI_TRUE && palette == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_PALETTE_REQUIRED, __func__);
		return;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
	{
		TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
		if (batch_sparse->TileCount == 0)
		{
			return;
		}
	}
	break;
	default:
		break;
	}

	TuiErrorCode error_code = tuiPanelDrawBatch_Opengl33(panel, atlas, palette, batch, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawPanel(TuiPanel panel, TuiPanel subject_panel)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (subject_panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_SUBJECT_PANEL, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawPanel_Opengl33(panel, subject_panel, 0, (int)panel->PixelWidth, 0, (int)panel->PixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawPanelTransformed(TuiPanel panel, TuiPanel subject_panel, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (subject_panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_SUBJECT_PANEL, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawPanel_Opengl33(panel, subject_panel, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawTexture(TuiPanel panel, TuiTexture texture)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (texture == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawTexture_Opengl33(panel, texture, 0, (int)panel->PixelWidth, 0, (int)panel->PixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawTextureTransformed(TuiPanel panel, TuiTexture texture, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (texture == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawTexture_Opengl33(panel, texture, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawAtlas(TuiPanel panel, TuiAtlas atlas)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (atlas == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_ATLAS, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawAtlas_Opengl33(panel, atlas, 0, (int)panel->PixelWidth, 0, (int)panel->PixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawAtlasTransformed(TuiPanel panel, TuiAtlas atlas, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (atlas == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_ATLAS, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawAtlas_Opengl33(panel, atlas, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawWindow(TuiPanel panel, TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawWindow_Opengl33(panel, window, 0, (int)panel->PixelWidth, 0, (int)panel->PixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiPanelDrawWindowTransformed(TuiPanel panel, TuiWindow window, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiPanelDrawWindow_Opengl33(panel, window, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}