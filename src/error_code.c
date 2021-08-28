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
#include <TUIC/error_code.h>
#include <GLFW/glfw3.h>
#include <string.h>

#define TO_STRING(value) #value

const char* kTui_Error_Unknown_Name = TO_STRING(TUI_ERROR_UNKNOWN);
const char* kTui_Error_None_Name = TO_STRING(TUI_ERROR_NONE);
const char* kTui_Error_Already_Initialized_Name = TO_STRING(TUI_ERROR_ALREADY_INITIALIZED);
const char* kTui_Error_Batch_Overflow_Name = TO_STRING(TUI_ERROR_BATCH_OVERFLOW);
const char* kTui_Error_Graphics_Backend_Specific_Name = TO_STRING(TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC);
const char* kTui_Error_Dangling_Atlas_Name = TO_STRING(TUI_ERROR_DANGLING_ATLAS);
const char* kTui_Error_Dangling_Cursor_Name = TO_STRING(TUI_ERROR_DANGLING_CURSOR);
const char* kTui_Error_Dangling_Palette_Name = TO_STRING(TUI_ERROR_DANGLING_PALETTE);
const char* kTui_Error_Dangling_Panel_Name = TO_STRING(TUI_ERROR_DANGLING_PANEL);
const char* kTui_Error_Dangling_Texture_Name = TO_STRING(TUI_ERROR_DANGLING_TEXTURE);
const char* kTui_Error_Dangling_Window_Name = TO_STRING(TUI_ERROR_DANGLING_WINDOW);
const char* kTui_Error_Glfw_Api_Unavailable_Name = TO_STRING(TUI_ERROR_GLFW_API_UNAVAILABLE);
const char* kTui_Error_Glfw_Format_Unavailable_Name = TO_STRING(TUI_ERROR_GLFW_FORMAT_UNAVAILABLE);
const char* kTui_Error_Glfw_Invalid_Enum_Name = TO_STRING(TUI_ERROR_GLFW_INVALID_ENUM);
const char* kTui_Error_Glfw_Invalid_Value_Name = TO_STRING(TUI_ERROR_GLFW_INVALID_VALUE);
const char* kTui_Error_Glfw_Not_Initialized_Name = TO_STRING(TUI_ERROR_GLFW_NOT_INITIALIZED);
const char* kTui_Error_Glfw_No_Current_Context_Name = TO_STRING(TUI_ERROR_GLFW_NO_CURRENT_CONTEXT);
const char* kTui_Error_Glfw_No_Window_Context_Name = TO_STRING(TUI_ERROR_GLFW_NO_WINDOW_CONTEXT);
const char* kTui_Error_Glfw_Out_Of_Memory_Name = TO_STRING(TUI_ERROR_GLFW_OUT_OF_MEMORY);
const char* kTui_Error_Glfw_Platform_Error_Name = TO_STRING(TUI_ERROR_GLFW_PLATFORM_ERROR);
const char* kTui_Error_Glfw_Version_Unavailable_Name = TO_STRING(TUI_ERROR_GLFW_VERSION_UNAVAILABLE);
const char* kTui_Error_Incompatible_Blend_Mode_Name = TO_STRING(TUI_ERROR_INCOMPATIBLE_BLEND_MODE);
const char* kTui_Error_Incompatible_Images_Name = TO_STRING(TUI_ERROR_INCOMPATIBLE_IMAGES);
const char* kTui_Error_Invalid_Aspect_Ratio_Name = TO_STRING(TUI_ERROR_INVALID_ASPECT_RATIO);
const char* kTui_Error_Invalid_Atlas_Type_Name = TO_STRING(TUI_ERROR_INVALID_ATLAS_TYPE);
const char* kTui_Error_Invalid_Batch_Function_Name = TO_STRING(TUI_ERROR_INVALID_BATCH_FUNCTION);
const char* kTui_Error_Invalid_Batch_Pixel_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS);
const char* kTui_Error_Invalid_Batch_Tile_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS);
const char* kTui_Error_Invalid_Blend_Mode_Name = TO_STRING(TUI_ERROR_INVALID_BLEND_MODE);
const char* kTui_Error_Invalid_Button_State_Name = TO_STRING(TUI_ERROR_INVALID_BUTTON_STATE);
const char* kTui_Error_Invalid_Channel_Count_Name = TO_STRING(TUI_ERROR_INVALID_CHANNEL_COUNT);
const char* kTui_Error_Invalid_Codepage_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS);
const char* kTui_Error_Invalid_Cursor_Mode_Name = TO_STRING(TUI_ERROR_INVALID_CURSOR_MODE);
const char* kTui_Error_Invalid_Cursor_Shape_Name = TO_STRING(TUI_ERROR_INVALID_CURSOR_SHAPE);
const char* kTui_Error_Invalid_Detail_Flag_Name = TO_STRING(TUI_ERROR_INVALID_DETAIL_FLAG);
const char* kTui_Error_Invalid_Detail_Mode_Name = TO_STRING(TUI_ERROR_INVALID_DETAIL_MODE);
const char* kTui_Error_Invalid_Event_Timeout_Name = TO_STRING(TUI_ERROR_INVALID_EVENT_TIMEOUT);
const char* kTui_Error_Invalid_File_Path_Name = TO_STRING(TUI_ERROR_INVALID_FILE_PATH);
const char* kTui_Error_Invalid_Filter_Mode_Name = TO_STRING(TUI_ERROR_INVALID_FILTER_MODE);
const char* kTui_Error_Invalid_Glfw_Library_Version_Name = TO_STRING(TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION);
const char* kTui_Error_Invalid_Glyph_Count_Name = TO_STRING(TUI_ERROR_INVALID_GLYPH_COUNT);
const char* kTui_Error_Invalid_Glyph_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_GLYPH_DIMENSIONS);
const char* kTui_Error_Invalid_Image_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_IMAGE_DIMENSIONS);
const char* kTui_Error_Invalid_Keyboard_Key_Name = TO_STRING(TUI_ERROR_INVALID_KEYBOARD_KEY);
const char* kTui_Error_Invalid_Keyboard_Mod_Name = TO_STRING(TUI_ERROR_INVALID_KEYBOARD_MOD);
const char* kTui_Error_Invalid_Mouse_Button_Name = TO_STRING(TUI_ERROR_INVALID_MOUSE_BUTTON);
const char* kTui_Error_Invalid_Palette_Color_Count_Name = TO_STRING(TUI_ERROR_INVALID_PALETTE_COLOR_COUNT);
const char* kTui_Error_Invalid_Panel_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_PANEL_DIMENSIONS);
const char* kTui_Error_Invalid_Pixel_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_PIXEL_DIMENSIONS);
const char* kTui_Error_Invalid_Time_Name = TO_STRING(TUI_ERROR_INVALID_TIME);
const char* kTui_Error_Invalid_Window_Framebuffer_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS);
const char* kTui_Error_Invalid_Window_Viewport_Dimensions_Name = TO_STRING(TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS);
const char* kTui_Error_Invalid_Window_Size_Limits_Name = TO_STRING(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS);
const char* kTui_Error_Load_Image_Failure_Name = TO_STRING(TUI_ERROR_LOAD_IMAGE_FAILURE);
const char* kTui_Error_Not_Initialized_Name = TO_STRING(TUI_ERROR_NOT_INITIALIZED);
const char* kTui_Error_Null_Atlas_Name = TO_STRING(TUI_ERROR_NULL_ATLAS);
const char* kTui_Error_Null_Batch_Name = TO_STRING(TUI_ERROR_NULL_BATCH);
const char* kTui_Error_Null_Colors_Name = TO_STRING(TUI_ERROR_NULL_COLORS);
const char* kTui_Error_Null_Cursor_Name = TO_STRING(TUI_ERROR_NULL_CURSOR);
const char* kTui_Error_Null_Glyph_Bounding_Boxes_Name = TO_STRING(TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES);
const char* kTui_Error_Null_Image_Name = TO_STRING(TUI_ERROR_NULL_IMAGE);
const char* kTui_Error_Null_Monitor_Name = TO_STRING(TUI_ERROR_NULL_MONITOR);
const char* kTui_Error_Null_Palette_Name = TO_STRING(TUI_ERROR_NULL_PALETTE);
const char* kTui_Error_Null_Panel_Name = TO_STRING(TUI_ERROR_NULL_PANEL);
const char* kTui_Error_Null_Path_Name = TO_STRING(TUI_ERROR_NULL_PATH);
const char* kTui_Error_Null_Pixels_Name = TO_STRING(TUI_ERROR_NULL_PIXELS);
const char* kTui_Error_Null_String_Name = TO_STRING(TUI_ERROR_NULL_STRING);
const char* kTui_Error_Null_Subject_Panel_Name = TO_STRING(TUI_ERROR_NULL_SUBJECT_PANEL);
const char* kTui_Error_Null_Subject_Window_Name = TO_STRING(TUI_ERROR_NULL_SUBJECT_WINDOW);
const char* kTui_Error_Null_Target_Image_Name = TO_STRING(TUI_ERROR_NULL_TARGET_IMAGE);
const char* kTui_Error_Null_Texture_Name = TO_STRING(TUI_ERROR_NULL_TEXTURE);
const char* kTui_Error_Null_Texture_Coordinates_Name = TO_STRING(TUI_ERROR_NULL_TEXTURE_COORDINATES);
const char* kTui_Error_Null_Window_Name = TO_STRING(TUI_ERROR_NULL_WINDOW);
const char* kTui_Error_Palette_Required_Name = TO_STRING(TUI_ERROR_PALETTE_REQUIRED);
const char* kTui_Error_Resize_Image_Failure_Name = TO_STRING(TUI_ERROR_RESIZE_IMAGE_FAILURE);
const char* kTui_Error_Save_Image_Failure_Name = TO_STRING(TUI_ERROR_SAVE_IMAGE_FAILURE);
const char* kTui_Error_Unavailable_Graphics_Api_Name = TO_STRING(TUI_ERROR_UNAVAILABLE_GRAPHICS_API);
const char* kTui_Error_Unavailable_Graphics_Api_Version_Name = TO_STRING(TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION);
const char* kTui_Error_Unsupported_Cursor_Shape_Name = TO_STRING(TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE);
const char* kTui_Error_Unsupported_Raw_Mouse_Motion_Name = TO_STRING(TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION);
const char* kTui_Error_Unsupported_Window_Icons_Name = TO_STRING(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS);

const char* kTui_Error_Unknown_Description = "An unknown error has occured.";
const char* kTui_Error_None_Description = "No error has occured.";
const char* kTui_Error_Already_Initialized_Description = "TUIC has already been initialized.";
const char* kTui_Error_Batch_Overflow_Description = "Too many tiles are set in a TuiBatch.";
const char* kTui_Error_Graphics_Backend_Specific_Description = "A graphics backend specific error has occured.";
const char* kTui_Error_Dangling_Atlas_Description = "Attempting to terminate TUIC with one or more dangling TuiAtlas.";
const char* kTui_Error_Dangling_Cursor_Description = "Attempting to terminate TUIC with one or more dangling TuiCursor.";
const char* kTui_Error_Dangling_Palette_Description = "Attempting to terminate TUIC with one or more dangling TuiPalette.";
const char* kTui_Error_Dangling_Panel_Description = "Attempting to terminate TUIC with one or more dangling TuiPanel.";
const char* kTui_Error_Dangling_Texture_Description = "Attempting to terminate TUIC with one or more dangling TuiTexture.";
const char* kTui_Error_Dangling_Window_Description = "Attempting to terminate TUIC with one or more dangling TuiWindow.";
const char* kTui_Error_Glfw_Api_Unavailable_Description = "A GLFW error has occured: GLFW could not find support for the requested API on the system.";
const char* kTui_Error_Glfw_Format_Unavailable_Description = "A GLFW error has occured: the requested format is not supported or available.";
const char* kTui_Error_Glfw_Invalid_Enum_Description = "A GLFW error has occured: one of the arguments to the function was an invalid enum value.";
const char* kTui_Error_Glfw_Invalid_Value_Description = "A GLFW error has occured: one of the arguments to the function was an invalid value.";
const char* kTui_Error_Glfw_Not_Initialized_Description = "A GLFW error has occured: GLFW has not been initialized.";
const char* kTui_Error_Glfw_No_Current_Context_Description = "A GLFW error has occured: No context is current for this thread.";
const char* kTui_Error_Glfw_No_Window_Context_Description = "A GLFW error has occured: The specified window does not have an OpenGL or OpenGL ES context.";
const char* kTui_Error_Glfw_Out_Of_Memory_Description = "A GLFW error has occured: a memory allocation failed.";
const char* kTui_Error_Glfw_Platform_Error_Description = "A GLFW error has occured: a platform-specific error occurred that does not match any of the more specific categories.";
const char* kTui_Error_Glfw_Version_Unavailable_Description = "A GLFW error has occured: the requested OpenGL or OpenGL ES version is not available.";
const char* kTui_Error_Incompatible_Blend_Mode_Description = "The TuiBlendMode of the TuiAtlas is incompatible with the TuiDetailMode of the batch data or TuiBatch.";
const char* kTui_Error_Incompatible_Images_Description = "The images have incompatible channel counts.";
const char* kTui_Error_Invalid_Aspect_Ratio_Description = "The aspect ratio is numerator or denominator must be greater than 0.";
const char* kTui_Error_Invalid_Atlas_Type_Description = "The TuiAtlasType is invalid.";
const char* kTui_Error_Invalid_Batch_Function_Description = "A function was used on a TuiBatch that was intended for batches with a different TuiDetailMode.";
const char* kTui_Error_Invalid_Batch_Pixel_Dimensions_Description = "The pixel dimensions of a TUiBatch are invalid.";
const char* kTui_Error_Invalid_Batch_Tile_Dimensions_Description = "The tile dimensions of a TuiBatch are invalid.";
const char* kTui_Error_Invalid_Blend_Mode_Description = "The TuiBlendMode is invalid.";
const char* kTui_Error_Invalid_Button_State_Description = "The TuiButtonState is invalid.";
const char* kTui_Error_Invalid_Channel_Count_Description = "The channel count is invalid.";
const char* kTui_Error_Invalid_Codepage_Dimensions_Description = "The pixel dimensions of codepage TuiAtlas must be divisible by 16 and greater than 0.";
const char* kTui_Error_Invalid_Cursor_Mode_Description = "The TuiCursorMode is invalid.";
const char* kTui_Error_Invalid_Cursor_Shape_Description = "The TuiCursorShape is invalid.";
const char* kTui_Error_Invalid_Detail_Flag_Description = "The TuiDetailFlag is invalid.";
const char* kTui_Error_Invalid_Detail_Mode_Description = "The TuiDetailMode is invalid.";
const char* kTui_Error_Invalid_Event_Timeout_Description = "The event timeout must be a positive finite number.";
const char* kTui_Error_Invalid_File_Path_Description = "The file path is invalid or no file was found at the path.";
const char* kTui_Error_Invalid_Filter_Mode_Description = "The TuiFilterMode is invalid.";
const char* kTui_Error_Invalid_Glfw_Library_Version_Description = "The GLFW library dependency has the incorrect version. TUIC requires GLFW version 3.3.";
const char* kTui_Error_Invalid_Glyph_Count_Description = "The glyph count must be greater than 0.";
const char* kTui_Error_Invalid_Glyph_Dimensions_Description = "The glyph dimensions must be greater than 0.";
const char* kTui_Error_Invalid_Image_Dimensions_Description = "The pixel dimensions of a TuiImage must be greater than 0.";
const char* kTui_Error_Invalid_Keyboard_Key_Description = "The TuiKeyboardKey is invalid.";
const char* kTui_Error_Invalid_Keyboard_Mod_Description = "The TuiKeyboardMod is invalid.";
const char* kTui_Error_Invalid_Mouse_Button_Description = "The TuiMouseButton is invalid.";
const char* kTui_Error_Invalid_Palette_Color_Count_Description = "The palette color count must be greater than 0 and less than or equal to 256.";
const char* kTui_Error_Invalid_Panel_Dimensions_Description = "The pixel dimensions of a TuiPanel must be greater than 0.";
const char* kTui_Error_Invalid_Pixel_Dimensions_Description = "The pixel dimensions of a pixel array must be greater than 0.";
const char* kTui_Error_Invalid_Time_Description = "The system time must be greater than or equal to 0 and less than 18446744073";
const char* kTui_Error_Invalid_Window_Framebuffer_Dimensions_Description = "The pixel dimensions of the framebuffer of a TuiWindow must be greater than 0.";
const char* kTui_Error_Invalid_Window_Viewport_Dimensions_Description = "The pixel dimensions of the viewport of a TuiWindow must be greater than 0.";
const char* kTui_Error_Invalid_Window_Size_Limits_Description = "The min size limits of a TuiWindow must be smaller than the max size limits, and no size limits can be less than 0.";
const char* kTui_Error_Load_Image_Failure_Description = "The image failed to be loaded.";
const char* kTui_Error_Not_Initialized_Description = "TUIC is not initialzed.";
const char* kTui_Error_Null_Atlas_Description = "The TuiAtlas is TUI_NULL.";
const char* kTui_Error_Null_Batch_Description = "The TuiBatch is TUI_NULL.";
const char* kTui_Error_Null_Batch_Data_Description = "The batch data array is TUI_NULL.";
const char* kTui_Error_Null_Colors_Description = "The colors array is TUI_NULL.";
const char* kTui_Error_Null_Cursor_Description = "The TuiCursor is TUI_NULL.";
const char* kTui_Error_Null_Glyph_Bounding_Boxes_Description = "The glyph bounding boxes array is TUI_NULL.";
const char* kTui_Error_Null_Image_Description = "The TuiImage is TUI_NULL.";
const char* kTui_Error_Null_Monitor_Description = "The TuiMonitor is TUI_NULL.";
const char* kTui_Error_Null_Palette_Description = "The TuiPalette is TUI_NULL.";
const char* kTui_Error_Null_Panel_Description = "The TuiPanel is TUI_NULL.";
const char* kTui_Error_Null_Path_Description = "The path string is TUI_NULL.";
const char* kTui_Error_Null_Pixels_Description = "The pixels array is TUI_NULL.";
const char* kTui_Error_Null_String_Description = "The string is TUI_NULL.";
const char* kTui_Error_Null_Subject_Panel_Description = "The subject TuiPanel is TUI_NULL.";
const char* kTui_Error_Null_Subject_Window_Description = "The subject TuiWindow is TUI_NULL.";
const char* kTui_Error_Null_Target_Image_Description = "The target TuiImage is TUI_NULL.";
const char* kTui_Error_Null_Texture_Description = "The TuiTexture is TUI_NULL.";
const char* kTui_Error_Null_Texture_Coordinates_Description = "The texture coordinates array is TUI_NULL.";
const char* kTui_Error_Null_Window_Description = "The TuiWindow is TUI_NULL.";
const char* kTui_Error_Palette_Required_Description = "Can not render batch data with without a TuiPalette because one is required for its TuiDetailMode.";
const char* kTui_Error_Resize_Image_Failure_Description = "TuiImage failed to be resized.";
const char* kTui_Error_Save_Image_Failure_Description = "TuiImage failed to be saved to image file.";
const char* kTui_Error_Unavailable_Graphics_Api_Description = "Graphics API is unavailable on this device.";
const char* kTui_Error_Unavailable_Graphics_Api_Version_Description = "Graphics API verison is unavailable on this device.";
const char* kTui_Error_Unsupported_Cursor_Shape_Description = "The TuiCursorShape is not supported on this platform.";
const char* kTui_Error_Unsupported_Raw_Mouse_Motion_Description = "Raw mouse motion is not supported on this platform.";
const char* kTui_Error_Unsupported_Window_Icons_Description = "Window icons are not supported on this platform.";

TuiBoolean tuiErrorCodeIsValid(TuiErrorCode error_code)
{
	if (
		(error_code >= TUI_ERROR_FIRST) &&
		(error_code <= TUI_ERROR_LAST)
		)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

const char* tuiErrorCodeToString(TuiErrorCode error_code)
{
	switch (error_code)
	{
	case TUI_ERROR_UNKNOWN:
		return kTui_Error_Unknown_Name;
	case TUI_ERROR_NONE:
		return kTui_Error_None_Name;
	case TUI_ERROR_ALREADY_INITIALIZED:
		return kTui_Error_Already_Initialized_Name;
	case TUI_ERROR_BATCH_OVERFLOW:
		return kTui_Error_Batch_Overflow_Name;
	case TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC:
		return kTui_Error_Graphics_Backend_Specific_Name;
	case TUI_ERROR_DANGLING_ATLAS:
		return kTui_Error_Dangling_Atlas_Name;
	case TUI_ERROR_DANGLING_CURSOR:
		return kTui_Error_Dangling_Cursor_Name;
	case TUI_ERROR_DANGLING_PALETTE:
		return kTui_Error_Dangling_Palette_Name;
	case TUI_ERROR_DANGLING_PANEL:
		return kTui_Error_Dangling_Panel_Name;
	case TUI_ERROR_DANGLING_TEXTURE:
		return kTui_Error_Dangling_Texture_Name;
	case TUI_ERROR_DANGLING_WINDOW:
		return kTui_Error_Dangling_Window_Name;
	case TUI_ERROR_GLFW_API_UNAVAILABLE:
		return kTui_Error_Glfw_Api_Unavailable_Name;
	case TUI_ERROR_GLFW_FORMAT_UNAVAILABLE:
		return kTui_Error_Glfw_Format_Unavailable_Name;
	case TUI_ERROR_GLFW_INVALID_ENUM:
		return kTui_Error_Glfw_Invalid_Enum_Name;
	case TUI_ERROR_GLFW_INVALID_VALUE:
		return kTui_Error_Glfw_Invalid_Value_Name;
	case TUI_ERROR_GLFW_NOT_INITIALIZED:
		return kTui_Error_Glfw_Not_Initialized_Name;
	case TUI_ERROR_GLFW_NO_CURRENT_CONTEXT:
		return kTui_Error_Glfw_No_Current_Context_Name;
	case TUI_ERROR_GLFW_NO_WINDOW_CONTEXT:
		return kTui_Error_Glfw_No_Window_Context_Name;
	case TUI_ERROR_GLFW_OUT_OF_MEMORY:
		return kTui_Error_Glfw_Out_Of_Memory_Name;
	case TUI_ERROR_GLFW_PLATFORM_ERROR:
		return kTui_Error_Glfw_Platform_Error_Name;
	case TUI_ERROR_GLFW_VERSION_UNAVAILABLE:
		return kTui_Error_Glfw_Version_Unavailable_Name;
	case TUI_ERROR_INCOMPATIBLE_BLEND_MODE:
		return kTui_Error_Incompatible_Blend_Mode_Name;
	case TUI_ERROR_INCOMPATIBLE_IMAGES:
		return kTui_Error_Incompatible_Images_Name;
	case TUI_ERROR_INVALID_ASPECT_RATIO:
		return kTui_Error_Invalid_Aspect_Ratio_Name;
	case TUI_ERROR_INVALID_ATLAS_TYPE:
		return kTui_Error_Invalid_Atlas_Type_Name;
	case TUI_ERROR_INVALID_BATCH_FUNCTION:
		return kTui_Error_Invalid_Batch_Function_Name;
	case TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS:
		return kTui_Error_Invalid_Batch_Pixel_Dimensions_Name;
	case TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS:
		return kTui_Error_Invalid_Batch_Tile_Dimensions_Name;
	case TUI_ERROR_INVALID_BLEND_MODE:
		return kTui_Error_Invalid_Blend_Mode_Name;
	case TUI_ERROR_INVALID_BUTTON_STATE:
		return kTui_Error_Invalid_Button_State_Name;
	case TUI_ERROR_INVALID_CHANNEL_COUNT:
		return kTui_Error_Invalid_Channel_Count_Name;
	case TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS:
		return kTui_Error_Invalid_Codepage_Dimensions_Name;
	case TUI_ERROR_INVALID_CURSOR_MODE:
		return kTui_Error_Invalid_Cursor_Mode_Name;
	case TUI_ERROR_INVALID_CURSOR_SHAPE:
		return kTui_Error_Invalid_Cursor_Shape_Name;
	case TUI_ERROR_INVALID_DETAIL_FLAG:
		return kTui_Error_Invalid_Detail_Flag_Name;
	case TUI_ERROR_INVALID_DETAIL_MODE:
		return kTui_Error_Invalid_Detail_Mode_Name;
	case TUI_ERROR_INVALID_EVENT_TIMEOUT:
		return kTui_Error_Invalid_Event_Timeout_Name;
	case TUI_ERROR_INVALID_FILE_PATH:
		return kTui_Error_Invalid_File_Path_Name;
	case TUI_ERROR_INVALID_FILTER_MODE:
		return kTui_Error_Invalid_Filter_Mode_Name;
	case TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION:
		return kTui_Error_Invalid_Glfw_Library_Version_Name;
	case TUI_ERROR_INVALID_GLYPH_COUNT:
		return kTui_Error_Invalid_Glyph_Count_Name;
	case TUI_ERROR_INVALID_GLYPH_DIMENSIONS:
		return kTui_Error_Invalid_Glyph_Dimensions_Name;
	case TUI_ERROR_INVALID_IMAGE_DIMENSIONS:
		return kTui_Error_Invalid_Image_Dimensions_Name;
	case TUI_ERROR_INVALID_KEYBOARD_KEY:
		return kTui_Error_Invalid_Keyboard_Key_Name;
	case TUI_ERROR_INVALID_KEYBOARD_MOD:
		return kTui_Error_Invalid_Keyboard_Mod_Name;
	case TUI_ERROR_INVALID_MOUSE_BUTTON:
		return kTui_Error_Invalid_Mouse_Button_Name;
	case TUI_ERROR_INVALID_PALETTE_COLOR_COUNT:
		return kTui_Error_Invalid_Palette_Color_Count_Name;
	case TUI_ERROR_INVALID_PANEL_DIMENSIONS:
		return kTui_Error_Invalid_Panel_Dimensions_Name;
	case TUI_ERROR_INVALID_PIXEL_DIMENSIONS:
		return kTui_Error_Invalid_Pixel_Dimensions_Name;
	case TUI_ERROR_INVALID_TIME:
		return kTui_Error_Invalid_Time_Name;
	case TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS:
		return kTui_Error_Invalid_Window_Framebuffer_Dimensions_Name;
	case TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS:
		return kTui_Error_Invalid_Window_Viewport_Dimensions_Name;
	case TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS:
		return kTui_Error_Invalid_Window_Size_Limits_Name;
	case TUI_ERROR_LOAD_IMAGE_FAILURE:
		return kTui_Error_Load_Image_Failure_Name;
	case TUI_ERROR_NOT_INITIALIZED:
		return kTui_Error_Not_Initialized_Name;
	case TUI_ERROR_NULL_ATLAS:
		return kTui_Error_Null_Atlas_Name;
	case TUI_ERROR_NULL_BATCH:
		return kTui_Error_Null_Batch_Name;
	case TUI_ERROR_NULL_COLORS:
		return kTui_Error_Null_Colors_Name;
	case TUI_ERROR_NULL_CURSOR:  
		return kTui_Error_Null_Cursor_Name;
	case TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES:
		return kTui_Error_Null_Glyph_Bounding_Boxes_Name;
	case TUI_ERROR_NULL_IMAGE:
		return kTui_Error_Null_Image_Name;
	case TUI_ERROR_NULL_MONITOR:
		return kTui_Error_Null_Monitor_Name;
	case TUI_ERROR_NULL_PALETTE:
		return kTui_Error_Null_Palette_Name;
	case TUI_ERROR_NULL_PANEL:
		return kTui_Error_Null_Panel_Name;
	case TUI_ERROR_NULL_PATH:
		return kTui_Error_Null_Path_Name;
	case TUI_ERROR_NULL_PIXELS:
		return kTui_Error_Null_Pixels_Name;
	case TUI_ERROR_NULL_STRING:
		return kTui_Error_Null_String_Name;
	case TUI_ERROR_NULL_SUBJECT_PANEL:
		return kTui_Error_Null_Subject_Panel_Name;
	case TUI_ERROR_NULL_SUBJECT_WINDOW:
		return kTui_Error_Null_Subject_Window_Name;
	case TUI_ERROR_NULL_TARGET_IMAGE:
		return kTui_Error_Null_Target_Image_Name;
	case TUI_ERROR_NULL_TEXTURE:
		return kTui_Error_Null_Texture_Name;
	case TUI_ERROR_NULL_TEXTURE_COORDINATES:
		return kTui_Error_Null_Texture_Coordinates_Name;
	case TUI_ERROR_NULL_WINDOW:
		return kTui_Error_Null_Window_Name;
	case TUI_ERROR_PALETTE_REQUIRED:
		return kTui_Error_Palette_Required_Name;
	case TUI_ERROR_RESIZE_IMAGE_FAILURE:
		return kTui_Error_Resize_Image_Failure_Name;
	case TUI_ERROR_SAVE_IMAGE_FAILURE:
		return kTui_Error_Save_Image_Failure_Name;
	case TUI_ERROR_UNAVAILABLE_GRAPHICS_API:
		return kTui_Error_Unavailable_Graphics_Api_Name;
	case TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION:
		return kTui_Error_Unavailable_Graphics_Api_Version_Name;
	case TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE:
		return kTui_Error_Unsupported_Cursor_Shape_Name;
	case TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION:
		return kTui_Error_Unsupported_Raw_Mouse_Motion_Name;
	case TUI_ERROR_UNSUPPORTED_WINDOW_ICONS:
		return kTui_Error_Unsupported_Window_Icons_Name;
	default:
		return kTui_Error_Unknown_Name;
	}
}

TuiErrorCode tuiStringToErrorCode(const char* str)
{
	if (strcmp(str, kTui_Error_Unknown_Name) == 0)
	{
		return TUI_ERROR_UNKNOWN;
	}
	else if (strcmp(str, kTui_Error_None_Name) == 0)
	{
		return TUI_ERROR_NONE;
	}
	else if (strcmp(str, kTui_Error_Already_Initialized_Name) == 0)
	{
		return TUI_ERROR_ALREADY_INITIALIZED;
	}
	else if (strcmp(str, kTui_Error_Batch_Overflow_Name) == 0)
	{
		return TUI_ERROR_BATCH_OVERFLOW;
	}
	else if (strcmp(str, kTui_Error_Graphics_Backend_Specific_Name) == 0)
	{
		return TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC;
	}
	else if (strcmp(str, kTui_Error_Dangling_Atlas_Name) == 0)
	{
		return TUI_ERROR_DANGLING_ATLAS;
	}
	else if (strcmp(str, kTui_Error_Dangling_Cursor_Name) == 0)
	{
		return TUI_ERROR_DANGLING_CURSOR;
	}
	else if (strcmp(str, kTui_Error_Dangling_Palette_Name) == 0)
	{
		return TUI_ERROR_DANGLING_PALETTE;
	}
	else if (strcmp(str, kTui_Error_Dangling_Panel_Name) == 0)
	{
		return TUI_ERROR_DANGLING_PANEL;
	}
	else if (strcmp(str, kTui_Error_Dangling_Texture_Name) == 0)
	{
		return TUI_ERROR_DANGLING_TEXTURE;
	}
	else if (strcmp(str, kTui_Error_Dangling_Window_Name) == 0)
	{
		return TUI_ERROR_DANGLING_WINDOW;
	}
	else if (strcmp(str, kTui_Error_Glfw_Api_Unavailable_Name) == 0)
	{
		return TUI_ERROR_GLFW_API_UNAVAILABLE;
	}
	else if (strcmp(str, kTui_Error_Glfw_Format_Unavailable_Name) == 0)
	{
		return TUI_ERROR_GLFW_FORMAT_UNAVAILABLE;
	}
	else if (strcmp(str, kTui_Error_Glfw_Invalid_Enum_Name) == 0)
	{
		return TUI_ERROR_GLFW_INVALID_ENUM;
	}
	else if (strcmp(str, kTui_Error_Glfw_Invalid_Value_Name) == 0)
	{
		return TUI_ERROR_GLFW_INVALID_VALUE;
	}
	else if (strcmp(str, kTui_Error_Glfw_Not_Initialized_Name) == 0)
	{
		return TUI_ERROR_GLFW_NOT_INITIALIZED;
	}
	else if (strcmp(str, kTui_Error_Glfw_No_Current_Context_Name) == 0)
	{
		return TUI_ERROR_GLFW_NO_CURRENT_CONTEXT;
	}
	else if (strcmp(str, kTui_Error_Glfw_No_Window_Context_Name) == 0)
	{
		return TUI_ERROR_GLFW_NO_WINDOW_CONTEXT;
	}
	else if (strcmp(str, kTui_Error_Glfw_Out_Of_Memory_Name) == 0)
	{
		return TUI_ERROR_GLFW_OUT_OF_MEMORY;
	}
	else if (strcmp(str, kTui_Error_Glfw_Platform_Error_Name) == 0)
	{
		return TUI_ERROR_GLFW_PLATFORM_ERROR;
	}
	else if (strcmp(str, kTui_Error_Glfw_Version_Unavailable_Name) == 0)
	{
		return TUI_ERROR_GLFW_VERSION_UNAVAILABLE;
	}
	else if (strcmp(str, kTui_Error_Incompatible_Blend_Mode_Name) == 0)
	{
		return TUI_ERROR_INCOMPATIBLE_BLEND_MODE;
	}
	else if (strcmp(str, kTui_Error_Incompatible_Images_Name) == 0)
	{
		return TUI_ERROR_INCOMPATIBLE_IMAGES;
	}
	else if (strcmp(str, kTui_Error_Invalid_Aspect_Ratio_Name) == 0)
	{
		return TUI_ERROR_INVALID_ASPECT_RATIO;
	}
	else if (strcmp(str, kTui_Error_Invalid_Atlas_Type_Name) == 0)
	{
		return TUI_ERROR_INVALID_ATLAS_TYPE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Batch_Function_Name) == 0)
	{
		return TUI_ERROR_INVALID_BATCH_FUNCTION;
	}
	else if (strcmp(str, kTui_Error_Invalid_Batch_Pixel_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Batch_Tile_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Blend_Mode_Name) == 0)
	{
		return TUI_ERROR_INVALID_BLEND_MODE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Button_State_Name) == 0)
	{
		return TUI_ERROR_INVALID_BUTTON_STATE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Channel_Count_Name) == 0)
	{
		return TUI_ERROR_INVALID_CHANNEL_COUNT;
	}
	else if (strcmp(str, kTui_Error_Invalid_Codepage_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Cursor_Mode_Name) == 0)
	{
		return TUI_ERROR_INVALID_CURSOR_MODE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Cursor_Shape_Name) == 0)
	{
		return TUI_ERROR_INVALID_CURSOR_SHAPE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Detail_Flag_Name) == 0)
	{
		return TUI_ERROR_INVALID_DETAIL_FLAG;
	}
	else if (strcmp(str, kTui_Error_Invalid_Detail_Mode_Name) == 0)
	{
		return TUI_ERROR_INVALID_DETAIL_MODE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Event_Timeout_Name) == 0)
	{
		return TUI_ERROR_INVALID_EVENT_TIMEOUT;
	}
	else if (strcmp(str, kTui_Error_Invalid_File_Path_Name) == 0)
	{
		return TUI_ERROR_INVALID_FILE_PATH;
	}
	else if (strcmp(str, kTui_Error_Invalid_Filter_Mode_Name) == 0)
	{
		return TUI_ERROR_INVALID_FILTER_MODE;
	}
	else if (strcmp(str, kTui_Error_Invalid_Glfw_Library_Version_Name) == 0)
	{
		return TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION;
	}
	else if (strcmp(str, kTui_Error_Invalid_Glyph_Count_Name) == 0)
	{
		return TUI_ERROR_INVALID_GLYPH_COUNT;
	}
	else if (strcmp(str, kTui_Error_Invalid_Glyph_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_GLYPH_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Image_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_IMAGE_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Keyboard_Key_Name) == 0)
	{
		return TUI_ERROR_INVALID_KEYBOARD_KEY;
	}
	else if (strcmp(str, kTui_Error_Invalid_Keyboard_Mod_Name) == 0)
	{
		return TUI_ERROR_INVALID_KEYBOARD_MOD;
	}
	else if (strcmp(str, kTui_Error_Invalid_Mouse_Button_Name) == 0)
	{
		return TUI_ERROR_INVALID_MOUSE_BUTTON;
	}
	else if (strcmp(str, kTui_Error_Invalid_Palette_Color_Count_Name) == 0)
	{
		return TUI_ERROR_INVALID_PALETTE_COLOR_COUNT;
	}
	else if (strcmp(str, kTui_Error_Invalid_Panel_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_PANEL_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Pixel_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_PIXEL_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Time_Name) == 0)
	{
		return TUI_ERROR_INVALID_TIME;
	}
	else if (strcmp(str, kTui_Error_Invalid_Window_Framebuffer_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Window_Viewport_Dimensions_Name) == 0)
	{
		return TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS;
	}
	else if (strcmp(str, kTui_Error_Invalid_Window_Size_Limits_Name) == 0)
	{
		return TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS;
	}
	else if (strcmp(str, kTui_Error_Load_Image_Failure_Name) == 0)
	{
		return TUI_ERROR_LOAD_IMAGE_FAILURE;
	}
	else if (strcmp(str, kTui_Error_Not_Initialized_Name) == 0)
	{
		return TUI_ERROR_NOT_INITIALIZED;
	}
	else if (strcmp(str, kTui_Error_Null_Atlas_Name) == 0)
	{
		return TUI_ERROR_NULL_ATLAS;
	}
	else if (strcmp(str, kTui_Error_Null_Batch_Name) == 0)
	{
		return TUI_ERROR_NULL_BATCH;
	}
	else if (strcmp(str, kTui_Error_Null_Colors_Name) == 0)
	{
		return TUI_ERROR_NULL_COLORS;
	}
	else if (strcmp(str, kTui_Error_Null_Cursor_Name) == 0)
	{
		return TUI_ERROR_NULL_CURSOR;
	}
	else if (strcmp(str, kTui_Error_Null_Glyph_Bounding_Boxes_Name) == 0)
	{
		return TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES;
	}
	else if (strcmp(str, kTui_Error_Null_Image_Name) == 0)
	{
		return TUI_ERROR_NULL_IMAGE;
	}
	else if (strcmp(str, kTui_Error_Null_Monitor_Name) == 0)
	{
		return TUI_ERROR_NULL_MONITOR;
	}
	else if (strcmp(str, kTui_Error_Null_Palette_Name) == 0)
	{
		return TUI_ERROR_NULL_PALETTE;
	}
	else if (strcmp(str, kTui_Error_Null_Panel_Name) == 0)
	{
		return TUI_ERROR_NULL_PANEL;
	}
	else if (strcmp(str, kTui_Error_Null_Path_Name) == 0)
	{
		return TUI_ERROR_NULL_PATH;
	}
	else if (strcmp(str, kTui_Error_Null_Pixels_Name) == 0)
	{
		return TUI_ERROR_NULL_PIXELS;
	}
	else if (strcmp(str, kTui_Error_Null_String_Name) == 0)
	{
		return TUI_ERROR_NULL_STRING;
	}
	else if (strcmp(str, kTui_Error_Null_Subject_Panel_Name) == 0)
	{
		return TUI_ERROR_NULL_SUBJECT_PANEL;
	}
	else if (strcmp(str, kTui_Error_Null_Subject_Window_Name) == 0)
	{
		return TUI_ERROR_NULL_SUBJECT_WINDOW;
	}
	else if (strcmp(str, kTui_Error_Null_Target_Image_Name) == 0)
	{
		return TUI_ERROR_NULL_TARGET_IMAGE;
	}
	else if (strcmp(str, kTui_Error_Null_Texture_Name) == 0)
	{
		return TUI_ERROR_NULL_TEXTURE;
	}
	else if (strcmp(str, kTui_Error_Null_Texture_Coordinates_Name) == 0)
	{
		return TUI_ERROR_NULL_TEXTURE_COORDINATES;
	}
	else if (strcmp(str, kTui_Error_Null_Window_Name) == 0)
	{
		return TUI_ERROR_NULL_WINDOW;
	}
	else if (strcmp(str, kTui_Error_Palette_Required_Name) == 0)
	{
		return TUI_ERROR_PALETTE_REQUIRED;
	}
	else if (strcmp(str, kTui_Error_Resize_Image_Failure_Name) == 0)
	{
		return TUI_ERROR_RESIZE_IMAGE_FAILURE;
	}
	else if (strcmp(str, kTui_Error_Save_Image_Failure_Name) == 0)
	{
		return TUI_ERROR_SAVE_IMAGE_FAILURE;
	}
	else if (strcmp(str, kTui_Error_Unavailable_Graphics_Api_Name) == 0)
	{
		return TUI_ERROR_UNAVAILABLE_GRAPHICS_API;
	}
	else if (strcmp(str, kTui_Error_Unavailable_Graphics_Api_Version_Name) == 0)
	{
		return TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION;
	}
	else if (strcmp(str, kTui_Error_Unsupported_Cursor_Shape_Name) == 0)
	{
		return TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE;
	}
	else if (strcmp(str, kTui_Error_Unsupported_Raw_Mouse_Motion_Name) == 0)
	{
		return TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION;
	}
	else if (strcmp(str, kTui_Error_Unsupported_Window_Icons_Name) == 0)
	{
		return TUI_ERROR_UNSUPPORTED_WINDOW_ICONS;
	}
	return TUI_ERROR_UNKNOWN;
}

const char* tuiErrorCodeGetDescription(TuiErrorCode error_code)
{
	switch (error_code)
	{
	case TUI_ERROR_UNKNOWN:
		return kTui_Error_Unknown_Description;
	case TUI_ERROR_NONE:
		return kTui_Error_None_Description;
	case TUI_ERROR_ALREADY_INITIALIZED:
		return kTui_Error_Already_Initialized_Description;
	case TUI_ERROR_BATCH_OVERFLOW:
		return kTui_Error_Batch_Overflow_Description;
	case TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC:
		return kTui_Error_Graphics_Backend_Specific_Description;
	case TUI_ERROR_DANGLING_ATLAS:
		return kTui_Error_Dangling_Atlas_Description;
	case TUI_ERROR_DANGLING_CURSOR:
		return kTui_Error_Dangling_Cursor_Description;
	case TUI_ERROR_DANGLING_PALETTE:
		return kTui_Error_Dangling_Palette_Description;
	case TUI_ERROR_DANGLING_PANEL:
		return kTui_Error_Dangling_Panel_Description;
	case TUI_ERROR_DANGLING_TEXTURE:
		return kTui_Error_Dangling_Texture_Description;
	case TUI_ERROR_DANGLING_WINDOW:
		return kTui_Error_Dangling_Window_Description;
	case TUI_ERROR_GLFW_API_UNAVAILABLE:
		return kTui_Error_Glfw_Api_Unavailable_Description;
	case TUI_ERROR_GLFW_FORMAT_UNAVAILABLE:
		return kTui_Error_Glfw_Format_Unavailable_Description;
	case TUI_ERROR_GLFW_INVALID_ENUM:
		return kTui_Error_Glfw_Invalid_Enum_Description;
	case TUI_ERROR_GLFW_INVALID_VALUE:
		return kTui_Error_Glfw_Invalid_Value_Description;
	case TUI_ERROR_GLFW_NOT_INITIALIZED:
		return kTui_Error_Glfw_Not_Initialized_Description;
	case TUI_ERROR_GLFW_NO_CURRENT_CONTEXT:
		return kTui_Error_Glfw_No_Current_Context_Description;
	case TUI_ERROR_GLFW_NO_WINDOW_CONTEXT:
		return kTui_Error_Glfw_No_Window_Context_Description;
	case TUI_ERROR_GLFW_OUT_OF_MEMORY:
		return kTui_Error_Glfw_Out_Of_Memory_Description;
	case TUI_ERROR_GLFW_PLATFORM_ERROR:
		return kTui_Error_Glfw_Platform_Error_Description;
	case TUI_ERROR_GLFW_VERSION_UNAVAILABLE:
		return kTui_Error_Glfw_Version_Unavailable_Description;
	case TUI_ERROR_INCOMPATIBLE_BLEND_MODE:
		return kTui_Error_Incompatible_Blend_Mode_Description;
	case TUI_ERROR_INCOMPATIBLE_IMAGES:
		return kTui_Error_Incompatible_Images_Description;
	case TUI_ERROR_INVALID_ASPECT_RATIO:
		return kTui_Error_Invalid_Aspect_Ratio_Description;
	case TUI_ERROR_INVALID_ATLAS_TYPE:
		return kTui_Error_Invalid_Atlas_Type_Description;
	case TUI_ERROR_INVALID_BATCH_FUNCTION:
		return kTui_Error_Invalid_Batch_Function_Description;
	case TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS:
		return kTui_Error_Invalid_Batch_Pixel_Dimensions_Description;
	case TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS:
		return kTui_Error_Invalid_Batch_Tile_Dimensions_Description;
	case TUI_ERROR_INVALID_BLEND_MODE:
		return kTui_Error_Invalid_Blend_Mode_Description;
	case TUI_ERROR_INVALID_BUTTON_STATE:
		return kTui_Error_Invalid_Button_State_Description;
	case TUI_ERROR_INVALID_CHANNEL_COUNT:
		return kTui_Error_Invalid_Channel_Count_Description;
	case TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS:
		return kTui_Error_Invalid_Codepage_Dimensions_Description;
	case TUI_ERROR_INVALID_CURSOR_MODE:
		return kTui_Error_Invalid_Cursor_Mode_Description;
	case TUI_ERROR_INVALID_CURSOR_SHAPE:
		return kTui_Error_Invalid_Cursor_Shape_Description;
	case TUI_ERROR_INVALID_DETAIL_FLAG:
		return kTui_Error_Invalid_Detail_Flag_Description;
	case TUI_ERROR_INVALID_DETAIL_MODE:
		return kTui_Error_Invalid_Detail_Mode_Description;
	case TUI_ERROR_INVALID_EVENT_TIMEOUT:
		return kTui_Error_Invalid_Event_Timeout_Description;
	case TUI_ERROR_INVALID_FILE_PATH:
		return kTui_Error_Invalid_File_Path_Description;
	case TUI_ERROR_INVALID_FILTER_MODE:
		return kTui_Error_Invalid_Filter_Mode_Description;
	case TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION:
		return kTui_Error_Invalid_Glfw_Library_Version_Description;
	case TUI_ERROR_INVALID_GLYPH_COUNT:
		return kTui_Error_Invalid_Glyph_Count_Description;
	case TUI_ERROR_INVALID_GLYPH_DIMENSIONS:
		return kTui_Error_Invalid_Glyph_Dimensions_Description;
	case TUI_ERROR_INVALID_IMAGE_DIMENSIONS:
		return kTui_Error_Invalid_Image_Dimensions_Description;
	case TUI_ERROR_INVALID_KEYBOARD_KEY:
		return kTui_Error_Invalid_Keyboard_Key_Description;
	case TUI_ERROR_INVALID_KEYBOARD_MOD:
		return kTui_Error_Invalid_Keyboard_Mod_Description;
	case TUI_ERROR_INVALID_MOUSE_BUTTON:
		return kTui_Error_Invalid_Mouse_Button_Description;
	case TUI_ERROR_INVALID_PALETTE_COLOR_COUNT:
		return kTui_Error_Invalid_Palette_Color_Count_Description;
	case TUI_ERROR_INVALID_PANEL_DIMENSIONS:
		return kTui_Error_Invalid_Panel_Dimensions_Description;
	case TUI_ERROR_INVALID_PIXEL_DIMENSIONS:
		return kTui_Error_Invalid_Pixel_Dimensions_Description;
	case TUI_ERROR_INVALID_TIME:
		return kTui_Error_Invalid_Time_Description;
	case TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS:
		return kTui_Error_Invalid_Window_Framebuffer_Dimensions_Description;
	case TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS:
		return kTui_Error_Invalid_Window_Viewport_Dimensions_Description;
	case TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS:
		return kTui_Error_Invalid_Window_Size_Limits_Description;
	case TUI_ERROR_LOAD_IMAGE_FAILURE:
		return kTui_Error_Load_Image_Failure_Description;
	case TUI_ERROR_NOT_INITIALIZED:
		return kTui_Error_Not_Initialized_Description;
	case TUI_ERROR_NULL_ATLAS:
		return kTui_Error_Null_Atlas_Description;
	case TUI_ERROR_NULL_BATCH:
		return kTui_Error_Null_Batch_Description;
	case TUI_ERROR_NULL_COLORS:
		return kTui_Error_Null_Colors_Description;
	case TUI_ERROR_NULL_CURSOR:  
		return kTui_Error_Null_Cursor_Description;
	case TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES:
		return kTui_Error_Null_Glyph_Bounding_Boxes_Description;
	case TUI_ERROR_NULL_IMAGE:
		return kTui_Error_Null_Image_Description;
	case TUI_ERROR_NULL_MONITOR:
		return kTui_Error_Null_Monitor_Description;
	case TUI_ERROR_NULL_PALETTE:
		return kTui_Error_Null_Palette_Description;
	case TUI_ERROR_NULL_PANEL:
		return kTui_Error_Null_Panel_Description;
	case TUI_ERROR_NULL_PATH:
		return kTui_Error_Null_Path_Description;
	case TUI_ERROR_NULL_PIXELS:
		return kTui_Error_Null_Pixels_Description;
	case TUI_ERROR_NULL_STRING:
		return kTui_Error_Null_String_Description;
	case TUI_ERROR_NULL_SUBJECT_PANEL:
		return kTui_Error_Null_Subject_Panel_Description;
	case TUI_ERROR_NULL_SUBJECT_WINDOW:
		return kTui_Error_Null_Subject_Window_Description;
	case TUI_ERROR_NULL_TARGET_IMAGE:
		return kTui_Error_Null_Target_Image_Description;
	case TUI_ERROR_NULL_TEXTURE:
		return kTui_Error_Null_Texture_Description;
	case TUI_ERROR_NULL_TEXTURE_COORDINATES:
		return kTui_Error_Null_Texture_Coordinates_Description;
	case TUI_ERROR_NULL_WINDOW:
		return kTui_Error_Null_Window_Description;
	case TUI_ERROR_PALETTE_REQUIRED:
		return kTui_Error_Palette_Required_Description;
	case TUI_ERROR_RESIZE_IMAGE_FAILURE:
		return kTui_Error_Resize_Image_Failure_Description;
	case TUI_ERROR_SAVE_IMAGE_FAILURE:
		return kTui_Error_Save_Image_Failure_Description;
	case TUI_ERROR_UNAVAILABLE_GRAPHICS_API:
		return kTui_Error_Unavailable_Graphics_Api_Description;
	case TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION:
		return kTui_Error_Unavailable_Graphics_Api_Version_Description;
	case TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE:
		return kTui_Error_Unsupported_Cursor_Shape_Description;
	case TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION:
		return kTui_Error_Unsupported_Raw_Mouse_Motion_Description;
	case TUI_ERROR_UNSUPPORTED_WINDOW_ICONS:
		return kTui_Error_Unsupported_Window_Icons_Description;
	default:
		return kTui_Error_Unknown_Description;
	}
}

TuiBoolean tuiErrorCodeIsGlfwError(TuiErrorCode error_code)
{
	if (error_code >= TUI_ERROR_GLFW_FIRST && error_code <= TUI_ERROR_GLFW_LAST)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}