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
/*! \file error_code.h
 */
#ifndef TUIC_ERROR_CODE_H //header guard
#define TUIC_ERROR_CODE_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/boolean.h>


/*!
 * @brief Error codes for errors caused by the TUIC library.
 */
typedef enum TuiErrorCode
{
	/*!
	 * \brief TUIC error code for when an unknown error has occured.
	 */
	TUI_ERROR_UNKNOWN = -1,
	/*!
	 * \brief TUIC error code for when no error has occured.
	 */
	TUI_ERROR_NONE = 0,
	/*!
	 * \brief TUIC error code for when TUIC has already been initialized.
	 */
	TUI_ERROR_ALREADY_INITIALIZED = 1,
	/*!
	 * \brief TUIC error code for when too many tiles are set in a @ref TuiBatch.
	 */
	TUI_ERROR_BATCH_OVERFLOW = 2,
	/*!
	 * \brief TUIC error code for when a graphics backend specific error has occured.
	 */
	TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC = 3,
	/*!
	 * \brief TUIC error code for when attempting to terminate TUIC with one or more dangling @ref TuiAtlas.
	 */
	TUI_ERROR_DANGLING_ATLAS = 4,
	/*!
	 * \brief TUIC error code for when attempting to terminate TUIC with one or more dangling @ref TuiCursor.
	 */
	TUI_ERROR_DANGLING_CURSOR = 5,
	/*!
	 * \brief TUIC error code for when attempting to terminate TUIC with one or more dangling @ref TuiPalette.
	 */
	TUI_ERROR_DANGLING_PALETTE = 6,
	/*!
	 * \brief TUIC error code for when attempting to terminate TUIC with one or more dangling @ref TuiPanel.
	 */
	TUI_ERROR_DANGLING_PANEL = 7,
	/*!
	 * \brief TUIC error code for when attempting to terminate TUIC with one or more dangling @ref TuiTexture.
	 */
	TUI_ERROR_DANGLING_TEXTURE = 8,
	/*!
	 * \brief TUIC error code for when attempting to terminate TUIC with one or more dangling @ref TuiWindow.
	 */
	TUI_ERROR_DANGLING_WINDOW = 9,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: GLFW could not find support for the requested API on the system.
	 */
	TUI_ERROR_GLFW_API_UNAVAILABLE = 10,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: the requested format is not supported or available.
	 */
	TUI_ERROR_GLFW_FORMAT_UNAVAILABLE = 11,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: one of the arguments to the function was an invalid enum value.
	 */
	TUI_ERROR_GLFW_INVALID_ENUM = 12,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: one of the arguments to the function was an invalid value.
	 */
	TUI_ERROR_GLFW_INVALID_VALUE = 13,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: GLFW has not been initialized.
	 */
	TUI_ERROR_GLFW_NOT_INITIALIZED = 14,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: No context is current for this thread.
	 */
	TUI_ERROR_GLFW_NO_CURRENT_CONTEXT = 15,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: The specified window does not have an OpenGL or OpenGL ES context.
	 */
	TUI_ERROR_GLFW_NO_WINDOW_CONTEXT = 16,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: a memory allocation failed.
	 */
	TUI_ERROR_GLFW_OUT_OF_MEMORY = 17,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: a platform-specific error occurred that does not match any of the more specific categories.
	 */
	TUI_ERROR_GLFW_PLATFORM_ERROR = 18,
	/*!
	 * \brief TUIC error code for when a GLFW error has occured: the requested OpenGL or OpenGL ES version is not available.
	 */
	TUI_ERROR_GLFW_VERSION_UNAVAILABLE = 19,
	/*!
	 * \brief TUIC error code for when the @ref TuiBlendMode of the @ref TuiAtlas is incompatible with the @ref TuiDetailMode of the batch data or @ref TuiBatch.
	 */
	TUI_ERROR_INCOMPATIBLE_BLEND_MODE = 20,
	/*!
	 * \brief TUIC error code for when images have incompatible channel counts.
	 */
	TUI_ERROR_INCOMPATIBLE_IMAGES = 21,
	/*!
	 * \brief TUIC error code for when an aspect ratio is numerator or denominator is less than or equal to 0.
	 */
	TUI_ERROR_INVALID_ASPECT_RATIO = 22,
	/*!
	 * \brief TUIC error code for when a @ref TuiAtlasType is invalid.
	 */
	TUI_ERROR_INVALID_ATLAS_TYPE = 23,
	/*!
	* \brief TUIC error code for when a function is used on a @ref TuiBatch that was intended for batches with a different @ref TuiDetailMode.
	*/
	TUI_ERROR_INVALID_BATCH_FUNCTION = 24,
	/*!
	 * \brief TUIC error code for when the pixel dimensions of a @ref TuiBatch are invalid.
	 */
	TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS = 25,
	/*!
	 * \brief TUIC error code for when the tile dimensions of a @ref TuiBatch are invalid.
	 */
	TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS = 26,
	/*!
	 * \brief TUIC error code for when a @ref TuiBlendMode is invalid.
     */
	TUI_ERROR_INVALID_BLEND_MODE = 27,
	/*!
	 * \brief TUIC error code for when a @ref TuiButtonState is invalid.
     */
	TUI_ERROR_INVALID_BUTTON_STATE = 28,
	/*!
	 * \brief TUIC error code for when a channel count is invalid.
     */
	TUI_ERROR_INVALID_CHANNEL_COUNT = 29,
	/*!
	 * \brief TUIC error code for when the pixel dimensions of codepage @ref TuiAtlas is not divisible by 16 and greater than 0.
     */
	TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS = 30,
	/*!
	 * \brief TUIC error code for when a @ref TuiCursorMode is invalid.
     */
	TUI_ERROR_INVALID_CURSOR_MODE = 31,
	/*!
	 * \brief TUIC error code for when a @ref TuiCursorShape is invalid.
     */
	TUI_ERROR_INVALID_CURSOR_SHAPE = 32,
	/*!
	 * \brief TUIC error code for when a @ref TuiDetailFlag is invalid.
     */
	TUI_ERROR_INVALID_DETAIL_FLAG = 33,
	/*!
	 * \brief TUIC error code for when a @ref TuiDetailMode is invalid.
     */
	TUI_ERROR_INVALID_DETAIL_MODE = 34,
	/*!
	 * \brief TUIC error code for when an event timeout time is less than 0 or is not finite.
	 */
	TUI_ERROR_INVALID_EVENT_TIMEOUT = 35,
	/*!
	 * \brief TUIC error code for when a file path is invalid or no file is found at the path.
	 */
	TUI_ERROR_INVALID_FILE_PATH = 36,
	/*!
	 * \brief TUIC error code for when a @ref TuiFilterMode is invalid.
     */
	TUI_ERROR_INVALID_FILTER_MODE = 37,
	/*!
	 * \brief TUIC error code for when the wrong GLFW library version is used. TUIC expects GLFW version 3.3.
     */
	TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION = 38,
	/*!
	 * \brief TUIC error code for when a @ref TuiAtlas glyph count is less than or equal to 0.
     */
	TUI_ERROR_INVALID_GLYPH_COUNT = 39,
	/*!
	 * \brief TUIC error code for when @ref TuiAtlas glyph pixel dimensions are less than or equal to 0.
     */
	TUI_ERROR_INVALID_GLYPH_DIMENSIONS = 40,
	/*!
	 * \brief TUIC error code for when the pixel dimensions of a @ref TuiImage are less than or equal to 0.
     */
	TUI_ERROR_INVALID_IMAGE_DIMENSIONS = 41,
	/*!
	 * \brief TUIC error code for when a @ref TuiKeyboardKey is invalid.
     */
	TUI_ERROR_INVALID_KEYBOARD_KEY = 42,
	/*!
	 * \brief TUIC error code for when a @ref TuiKeyboardMod is invalid.
     */
	TUI_ERROR_INVALID_KEYBOARD_MOD = 43,
	/*!
	 * \brief TUIC error code for when a @ref TuiMouseButton is invalid.
     */
	TUI_ERROR_INVALID_MOUSE_BUTTON = 44,
	/*!
	 * \brief TUIC error code for when a @ref TuiPalette is given an invalid color count.
     */
	TUI_ERROR_INVALID_PALETTE_COLOR_COUNT = 45,
	/*!
	 * \brief TUIC error code for when the pixel dimensions of a @ref TuiPanel are less than or equal to 0.
     */
	TUI_ERROR_INVALID_PANEL_DIMENSIONS = 46,
	/*!
	 * \brief TUIC error code for when the dimensions of a pixel array are less than or equal to 0.
     */
	TUI_ERROR_INVALID_PIXEL_DIMENSIONS = 47,
	/*!
	 * \brief TUIC error code for when the system time is less than 0 or greater than or equal to 18446744073.
     */
	TUI_ERROR_INVALID_TIME = 48,
	/*!
	 * \brief TUIC error code for when the pixel dimensions of a @ref TuiWindow framebuffer are less than or equal to 0.
     */
	TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS = 49,
	/*!
	 * \brief TUIC error code for when the pixel dimensions of a @ref TuiWindow viewport are less than or equal to 0.
     */
	TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS = 50,
	/*!
	 * \brief TUIC error code for when the size limits of a @ref TuiWindow are invalid.
     */
	TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS = 51,
	/*!
	 * \brief TUIC error code for when a @ref TuiImage has failed to be loaded from the filesystem.
     */
	TUI_ERROR_LOAD_IMAGE_FAILURE = 52,
	/*!
	 * \brief TUIC error code for when TUIC is not yet initialized.
     */
	TUI_ERROR_NOT_INITIALIZED = 53,
	/*!
	 * \brief TUIC error code for when a @ref TuiAtlas is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_ATLAS = 54,
	/*!
	 * \brief TUIC error code for when a @ref TuiBatch is @ref TUI_NULL.
	 */
	TUI_ERROR_NULL_BATCH = 55,
	/*!
	 * \brief TUIC error code for when a colors array is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_COLORS = 56,
	/*!
	 * \brief TUIC error code for when a @ref TuiCursor is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_CURSOR = 57,
	/*!
	 * \brief TUIC error code for when a glyph bounding boxes array is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES = 58,
	/*!
	 * \brief TUIC error code for when a @ref TuiImage is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_IMAGE = 59,
	/*!
	 * \brief TUIC error code for when a @ref TuiMonitor is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_MONITOR = 60,
	/*!
	 * \brief TUIC error code for when a @ref TuiPalette is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_PALETTE = 61,
	/*!
	 * \brief TUIC error code for when a @ref TuiPanel is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_PANEL = 62,
	/*!
	 * \brief TUIC error code for when a path is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_PATH = 63,
	/*!
	 * \brief TUIC error code for when a pixels array is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_PIXELS = 64,
	/*!
	 * \brief TUIC error code for when a string is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_STRING = 65,
	/*!
	 * \brief TUIC error code for when a subect @ref TuiPanel is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_SUBJECT_PANEL = 66,
	/*!
	 * \brief TUIC error code for when a subject @ref TuiWindow is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_SUBJECT_WINDOW = 67,
	/*!
	 * \brief TUIC error code for when a target @ref TuiImage is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_TARGET_IMAGE = 68,
	/*!
	 * \brief TUIC error code for when a @ref TuiTexture is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_TEXTURE = 69,
	/*!
	 * \brief TUIC error code for when a texture coordinates array is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_TEXTURE_COORDINATES = 70,
	/*!
	 * \brief TUIC error code for when a @ref TuiWindow is @ref TUI_NULL.
     */
	TUI_ERROR_NULL_WINDOW = 71,
	/*!
	 * \brief TUIC error code for when attempting to render batch data without a @ref TuiPalette when one is required by the @ref TuiDetailMode.
     */
	TUI_ERROR_PALETTE_REQUIRED = 72,
	/*!
	 * \brief TUIC error code for when a @ref TuiImage has failed to be resized.
     */
	TUI_ERROR_RESIZE_IMAGE_FAILURE = 73,
	/*!
	 * \brief TUIC error code for when a @ref TuiImage has failed to be saved.
	 */
	TUI_ERROR_SAVE_IMAGE_FAILURE = 74,
	/*!
	 * \brief TUIC error code for when a grapihcs API is unavailable on the current platform.
     */
	TUI_ERROR_UNAVAILABLE_GRAPHICS_API = 75,
	/*!
	 * \brief TUIC error code for when a graphics API version is unavailable on the current platform.
     */
	TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION = 76,
	/*!
	 * \brief TUIC error code for when a @ref TuiCursorShape is not supported on the current platform.
     */
	TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE = 77,
	/*!
	 * \brief TUIC error code for when raw mouse motion is not supported on the current platform.
     */
	TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION = 78,
	/*!
	 * \brief TUIC error code for when window icons are not supported on the current platform.
     */
	TUI_ERROR_UNSUPPORTED_WINDOW_ICONS = 79,
	/*!
	 * \brief The first GLFW error code.
     */
	TUI_ERROR_GLFW_FIRST = TUI_ERROR_GLFW_API_UNAVAILABLE,
	/*!
	 * \brief The last GLFW error code.
     */
	TUI_ERROR_GLFW_LAST = TUI_ERROR_GLFW_VERSION_UNAVAILABLE,
	/*!
	 * \brief The first valid @ref TuiErrorCode.
     */
	TUI_ERROR_FIRST = TUI_ERROR_UNKNOWN,
	/*!
	 * \brief The last valid @ref TuiErrorCode.
     */
	TUI_ERROR_LAST = TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION
} TuiErrorCode;


/*! @name Error Code Names
 *  @{ */
/*!
 * @brief String name of @ref TUI_ERROR_UNKNOWN.
 */
extern const char* kTui_Error_Unknown_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NONE.
 */
extern const char* kTui_Error_None_Name;
/*!
 * @brief String name of @ref TUI_ERROR_ALREADY_INITIALIZED.
 */
extern const char* kTui_Error_Already_Initialized_Name;
/*!
 * @brief String name of @ref TUI_ERROR_BATCH_OVERFLOW.
 */
extern const char* kTui_Error_Batch_Overflow_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC.
 */
extern const char* kTui_Error_Graphics_Backend_Specific_Name;
/*!
 * @brief String name of @ref TUI_ERROR_DANGLING_ATLAS.
 */
extern const char* kTui_Error_Dangling_Atlas_Name;
/*!
 * @brief String name of @ref TUI_ERROR_DANGLING_CURSOR.
 */
extern const char* kTui_Error_Dangling_Cursor_Name;
/*!
 * @brief String name of @ref TUI_ERROR_DANGLING_PALETTE.
 */
extern const char* kTui_Error_Dangling_Palette_Name;
/*!
 * @brief String name of @ref TUI_ERROR_DANGLING_PANEL.
 */
extern const char* kTui_Error_Dangling_Panel_Name;
/*!
 * @brief String name of @ref TUI_ERROR_DANGLING_TEXTURE.
 */
extern const char* kTui_Error_Dangling_Texture_Name;
/*!
 * @brief String name of @ref TUI_ERROR_DANGLING_WINDOW.
 */
extern const char* kTui_Error_Dangling_Window_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_API_UNAVAILABLE.
 */
extern const char* kTui_Error_Glfw_Api_Unavailable_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_FORMAT_UNAVAILABLE.
 */
extern const char* kTui_Error_Glfw_Format_Unavailable_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_INVALID_ENUM.
 */
extern const char* kTui_Error_Glfw_Invalid_Enum_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_INVALID_VALUE.
 */
extern const char* kTui_Error_Glfw_Invalid_Value_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_NOT_INITIALIZED.
 */
extern const char* kTui_Error_Glfw_Not_Initialized_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_NO_CURRENT_CONTEXT.
 */
extern const char* kTui_Error_Glfw_No_Current_Context_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_NO_WINDOW_CONTEXT.
 */
extern const char* kTui_Error_Glfw_No_Window_Context_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_OUT_OF_MEMORY.
 */
extern const char* kTui_Error_Glfw_Out_Of_Memory_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_PLATFORM_ERROR.
 */
extern const char* kTui_Error_Glfw_Platform_Error_Name;
/*!
 * @brief String name of @ref TUI_ERROR_GLFW_VERSION_UNAVAILABLE.
 */
extern const char* kTui_Error_Glfw_Version_Unavailable_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INCOMPATIBLE_BLEND_MODE.
 */
extern const char* kTui_Error_Incompatible_Blend_Mode_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INCOMPATIBLE_IMAGES.
 */
extern const char* kTui_Error_Incompatible_Images_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_ASPECT_RATIO.
 */
extern const char* kTui_Error_Invalid_Aspect_Ratio_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_ATLAS_TYPE.
 */
extern const char* kTui_Error_Invalid_Atlas_Type_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_BATCH_FUNCTION.
 */
extern const char* kTui_Error_Invalid_Batch_Function_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Batch_Pixel_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Batch_Tile_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_BLEND_MODE.
 */
extern const char* kTui_Error_Invalid_Blend_Mode_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_BUTTON_STATE.
 */
extern const char* kTui_Error_Invalid_Button_State_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_CHANNEL_COUNT.
 */
extern const char* kTui_Error_Invalid_Channel_Count_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Codepage_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_CURSOR_MODE.
 */
extern const char* kTui_Error_Invalid_Cursor_Mode_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_CURSOR_SHAPE.
 */
extern const char* kTui_Error_Invalid_Cursor_Shape_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_DETAIL_FLAG.
 */
extern const char* kTui_Error_Invalid_Detail_Flag_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_DETAIL_MODE.
 */
extern const char* kTui_Error_Invalid_Detail_Mode_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_EVENT_TIMEOUT.
 */
extern const char* kTui_Error_Invalid_Event_Timeout_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_FILE_PATH.
 */
extern const char* kTui_Error_Invalid_File_Path_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_FILTER_MODE.
 */
extern const char* kTui_Error_Invalid_Filter_Mode_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION.
 */
extern const char* kTui_Error_Invalid_Glfw_Library_Version_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_GLYPH_COUNT.
 */
extern const char* kTui_Error_Invalid_Glyph_Count_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_GLYPH_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Glyph_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_IMAGE_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Image_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_KEYBOARD_KEY.
 */
extern const char* kTui_Error_Invalid_Keyboard_Key_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_KEYBOARD_MOD.
 */
extern const char* kTui_Error_Invalid_Keyboard_Mod_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_MOUSE_BUTTON.
 */
extern const char* kTui_Error_Invalid_Mouse_Button_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_PALETTE_COLOR_COUNT.
 */
extern const char* kTui_Error_Invalid_Palette_Color_Count_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_PANEL_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Panel_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_PIXEL_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Pixel_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_TIME.
 */
extern const char* kTui_Error_Invalid_Time_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Window_Framebuffer_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Window_Viewport_Dimensions_Name;
/*!
 * @brief String name of @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS.
 */
extern const char* kTui_Error_Invalid_Window_Size_Limits_Name;
/*!
 * @brief String name of @ref TUI_ERROR_LOAD_IMAGE_FAILURE.
 */
extern const char* kTui_Error_Load_Image_Failure_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NOT_INITIALIZED.
 */
extern const char* kTui_Error_Not_Initialized_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_ATLAS.
 */
extern const char* kTui_Error_Null_Atlas_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_BATCH.
 */
extern const char* kTui_Error_Null_Batch_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_COLORS.
 */
extern const char* kTui_Error_Null_Colors_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_CURSOR.
 */
extern const char* kTui_Error_Null_Cursor_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES.
 */
extern const char* kTui_Error_Null_Glyph_Bounding_Boxes_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_IMAGE.
 */
extern const char* kTui_Error_Null_Image_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_MONITOR.
 */
extern const char* kTui_Error_Null_Monitor_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_PALETTE.
 */
extern const char* kTui_Error_Null_Palette_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_PANEL.
 */
extern const char* kTui_Error_Null_Panel_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_PATH.
 */
extern const char* kTui_Error_Null_Path_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_PIXELS.
 */
extern const char* kTui_Error_Null_Pixels_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_STRING.
 */
extern const char* kTui_Error_Null_String_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_SUBJECT_PANEL.
 */
extern const char* kTui_Error_Null_Subject_Panel_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_SUBJECT_WINDOW.
 */
extern const char* kTui_Error_Null_Subject_Window_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_TARGET_IMAGE.
 */
extern const char* kTui_Error_Null_Target_Image_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_TEXTURE.
 */
extern const char* kTui_Error_Null_Texture_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_TEXTURE_COORDINATES.
 */
extern const char* kTui_Error_Null_Texture_Coordinates_Name;
/*!
 * @brief String name of @ref TUI_ERROR_NULL_WINDOW.
 */
extern const char* kTui_Error_Null_Window_Name;
/*!
 * @brief String name of @ref TUI_ERROR_PALETTE_REQUIRED.
 */
extern const char* kTui_Error_Palette_Required_Name;
/*!
 * @brief String name of @ref TUI_ERROR_RESIZE_IMAGE_FAILURE.
 */
extern const char* kTui_Error_Resize_Image_Failure_Name;
/*!
 * @brief String name of @ref TUI_ERROR_SAVE_IMAGE_FAILURE.
 */
extern const char* kTui_Error_Save_Image_Failure_Name;
/*!
 * @brief String name of @ref TUI_ERROR_UNAVAILABLE_GRAPHICS_API.
 */
extern const char* kTui_Error_Unavailable_Graphics_Api_Name;
/*!
 * @brief String name of @ref TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION.
 */
extern const char* kTui_Error_Unavailable_Graphics_Api_Version_Name;
/*!
 * @brief String name of @ref TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE.
 */
extern const char* kTui_Error_Unsupported_Cursor_Shape_Name;
/*!
 * @brief String name of @ref TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION.
 */
extern const char* kTui_Error_Unsupported_Raw_Mouse_Motion_Name;
/*!
 * @brief String name of @ref TUI_ERROR_UNSUPPORTED_WINDOW_ICONS.
 */
extern const char* kTui_Error_Unsupported_Window_Icons_Name;
/*! @} */


/*! @name Error Code Descriptions
 *  @{ */
/*!
 * @brief String descriptions of @ref TUI_ERROR_UNKNOWN.
 */
extern const char* kTui_Error_Unknown_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NONE.
 */
extern const char* kTui_Error_None_Description;
/*!
 * @brief String description of @ref TUI_ERROR_ALREADY_INITIALIZED.
 */
extern const char* kTui_Error_Already_Initialized_Description;
/*!
 * @brief String description of @ref TUI_ERROR_BATCH_OVERFLOW.
 */
extern const char* kTui_Error_Batch_Overflow_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC.
 */
extern const char* kTui_Error_Graphics_Backend_Specific_Description;
/*!
 * @brief String description of @ref TUI_ERROR_DANGLING_ATLAS.
 */
extern const char* kTui_Error_Dangling_Atlas_Description;
/*!
 * @brief String description of @ref TUI_ERROR_DANGLING_CURSOR.
 */
extern const char* kTui_Error_Dangling_Cursor_Description;
/*!
 * @brief String description of @ref TUI_ERROR_DANGLING_PALETTE.
 */
extern const char* kTui_Error_Dangling_Palette_Description;
/*!
 * @brief String description of @ref TUI_ERROR_DANGLING_PANEL.
 */
extern const char* kTui_Error_Dangling_Panel_Description;
/*!
 * @brief String description of @ref TUI_ERROR_DANGLING_TEXTURE.
 */
extern const char* kTui_Error_Dangling_Texture_Description;
/*!
 * @brief String description of @ref TUI_ERROR_DANGLING_WINDOW.
 */
extern const char* kTui_Error_Dangling_Window_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_API_UNAVAILABLE.
 */
extern const char* kTui_Error_Glfw_Api_Unavailable_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_FORMAT_UNAVAILABLE.
 */
extern const char* kTui_Error_Glfw_Format_Unavailable_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_INVALID_ENUM.
 */
extern const char* kTui_Error_Glfw_Invalid_Enum_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_INVALID_VALUE.
 */
extern const char* kTui_Error_Glfw_Invalid_Value_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_NOT_INITIALIZED.
 */
extern const char* kTui_Error_Glfw_Not_Initialized_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_NO_CURRENT_CONTEXT.
 */
extern const char* kTui_Error_Glfw_No_Current_Context_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_NO_WINDOW_CONTEXT.
 */
extern const char* kTui_Error_Glfw_No_Window_Context_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_OUT_OF_MEMORY.
 */
extern const char* kTui_Error_Glfw_Out_Of_Memory_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_PLATFORM_ERROR.
 */
extern const char* kTui_Error_Glfw_Platform_Error_Description;
/*!
 * @brief String description of @ref TUI_ERROR_GLFW_VERSION_UNAVAILABLE.
 */
extern const char* kTui_Error_Glfw_Version_Unavailable_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INCOMPATIBLE_BLEND_MODE.
 */
extern const char* kTui_Error_Incompatible_Blend_Mode_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INCOMPATIBLE_IMAGES.
 */
extern const char* kTui_Error_Incompatible_Images_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_ASPECT_RATIO.
 */
extern const char* kTui_Error_Invalid_Aspect_Ratio_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_ATLAS_TYPE.
 */
extern const char* kTui_Error_Invalid_Atlas_Type_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_BATCH_FUNCTION.
 */
extern const char* kTui_Error_Invalid_Batch_Function_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Batch_Pixel_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Batch_Tile_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_BLEND_MODE.
 */
extern const char* kTui_Error_Invalid_Blend_Mode_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_BUTTON_STATE.
 */
extern const char* kTui_Error_Invalid_Button_State_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_CHANNEL_COUNT.
 */
extern const char* kTui_Error_Invalid_Channel_Count_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Codepage_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_CURSOR_MODE.
 */
extern const char* kTui_Error_Invalid_Cursor_Mode_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_CURSOR_SHAPE.
 */
extern const char* kTui_Error_Invalid_Cursor_Shape_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_DETAIL_FLAG.
 */
extern const char* kTui_Error_Invalid_Detail_Flag_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_DETAIL_MODE.
 */
extern const char* kTui_Error_Invalid_Detail_Mode_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_EVENT_TIMEOUT.
 */
extern const char* kTui_Error_Invalid_Event_Timeout_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_FILE_PATH.
 */
extern const char* kTui_Error_Invalid_File_Path_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_FILTER_MODE.
 */
extern const char* kTui_Error_Invalid_Filter_Mode_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION.
 */
extern const char* kTui_Error_Invalid_Glfw_Library_Version_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_GLYPH_COUNT.
 */
extern const char* kTui_Error_Invalid_Glyph_Count_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_GLYPH_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Glyph_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_IMAGE_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Image_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_KEYBOARD_KEY.
 */
extern const char* kTui_Error_Invalid_Keyboard_Key_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_KEYBOARD_MOD.
 */
extern const char* kTui_Error_Invalid_Keyboard_Mod_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_MOUSE_BUTTON.
 */
extern const char* kTui_Error_Invalid_Mouse_Button_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_PALETTE_COLOR_COUNT.
 */
extern const char* kTui_Error_Invalid_Palette_Color_Count_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_PANEL_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Panel_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_PIXEL_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Pixel_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_TIME.
 */
extern const char* kTui_Error_Invalid_Time_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Window_Framebuffer_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS.
 */
extern const char* kTui_Error_Invalid_Window_Viewport_Dimensions_Description;
/*!
 * @brief String description of @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS.
 */
extern const char* kTui_Error_Invalid_Window_Size_Limits_Description;
/*!
 * @brief String description of @ref TUI_ERROR_LOAD_IMAGE_FAILURE.
 */
extern const char* kTui_Error_Load_Image_Failure_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NOT_INITIALIZED.
 */
extern const char* kTui_Error_Not_Initialized_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_ATLAS.
 */
extern const char* kTui_Error_Null_Atlas_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_BATCH.
 */
extern const char* kTui_Error_Null_Batch_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_COLORS.
 */
extern const char* kTui_Error_Null_Colors_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_CURSOR.
 */
extern const char* kTui_Error_Null_Cursor_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES.
 */
extern const char* kTui_Error_Null_Glyph_Bounding_Boxes_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_IMAGE.
 */
extern const char* kTui_Error_Null_Image_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_MONITOR.
 */
extern const char* kTui_Error_Null_Monitor_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_PALETTE.
 */
extern const char* kTui_Error_Null_Palette_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_PANEL.
 */
extern const char* kTui_Error_Null_Panel_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_PATH.
 */
extern const char* kTui_Error_Null_Path_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_PIXELS.
 */
extern const char* kTui_Error_Null_Pixels_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_STRING.
 */
extern const char* kTui_Error_Null_String_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_SUBJECT_PANEL.
 */
extern const char* kTui_Error_Null_Subject_Panel_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_SUBJECT_WINDOW.
 */
extern const char* kTui_Error_Null_Subject_Window_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_TARGET_IMAGE.
 */
extern const char* kTui_Error_Null_Target_Image_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_TEXTURE.
 */
extern const char* kTui_Error_Null_Texture_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_TEXTURE_COORDINATES.
 */
extern const char* kTui_Error_Null_Texture_Coordinates_Description;
/*!
 * @brief String description of @ref TUI_ERROR_NULL_WINDOW.
 */
extern const char* kTui_Error_Null_Window_Description;
/*!
 * @brief String description of @ref TUI_ERROR_PALETTE_REQUIRED.
 */
extern const char* kTui_Error_Palette_Required_Description;
/*!
 * @brief String description of @ref TUI_ERROR_RESIZE_IMAGE_FAILURE.
 */
extern const char* kTui_Error_Resize_Image_Failure_Description;
/*!
 * @brief String description of @ref TUI_ERROR_SAVE_IMAGE_FAILURE.
 */
extern const char* kTui_Error_Save_Image_Failure_Description;
/*!
 * @brief String description of @ref TUI_ERROR_UNAVAILABLE_GRAPHICS_API.
 */
extern const char* kTui_Error_Unavailable_Graphics_Api_Description;
/*!
 * @brief String description of @ref TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION.
 */
extern const char* kTui_Error_Unavailable_Graphics_Api_Version_Description;
/*!
 * @brief String description of @ref TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE.
 */
extern const char* kTui_Error_Unsupported_Cursor_Shape_Description;
/*!
 * @brief String description of @ref TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION.
 */
extern const char* kTui_Error_Unsupported_Raw_Mouse_Motion_Description;
/*!
 * @brief String description of @ref TUI_ERROR_UNSUPPORTED_WINDOW_ICONS.
 */
extern const char* kTui_Error_Unsupported_Window_Icons_Description;
/*! @} */


/*! @name Error Code Functions
 *
 * Functions for dealing with @ref TuiErrorCode enum values.
 *  @{ */
/*!
 * @brief Determine if a @ref TuiErrorCode enum is valid.
 *
 * @param error_code The @ref TuiErrorCode to check.
 *
 * @returns The @ref TuiBoolean result. If error_code is a valid @ref TuiErrorCode, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiErrorCodeIsValid(TuiErrorCode error_code);
/*!
 * @brief Retrieve the string name associated with a @ref TuiErrorCode enum.
 *
 * @param error_code The @ref TuiErrorCode to get the name of.
 *
 * @returns The string name. @ref TUI_NULL is returned if error_code is an invalid @ref TuiErrorCode.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
const char* tuiErrorCodeToString(TuiErrorCode error_code);
/*!
 * @brief Determine the @ref TuiErrorCode enum value associated with a string name.
 *
 * @param str The string name.
 *
 * @returns The TuiErrorCode. @ref TUI_ERROR_UNKNOWN is returned if no match is found.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiErrorCode tuiStringToErrorCode(const char* str);
/*!
 * @brief Retrieve the string description associated with a @ref TuiErrorCode enum.
 *
 * @param error_code The @ref TuiErrorCode to get the description of.
 *
 * @returns The string description. @ref TUI_NULL is returned if error_code is an invalid @ref TuiErrorCode.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
const char* tuiErrorCodeGetDescription(TuiErrorCode error_code);
/*!
 * @brief Determine if a @ref TuiErrorCode enum is a GLFW error.
 *
 * @param error_code The @ref TuiErrorCode to check.
 *
 * @returns The @ref TuiBoolean result. If error_code is a GLFW error, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiBoolean tuiErrorCodeIsGlfwError(TuiErrorCode error_code);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard