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
/*! \file window.h
 */
#ifndef TUIC_WINDOW_H //header guard
#define TUIC_WINDOW_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/types.h>
#include <TUIC/boolean.h>
#include <TUIC/detail_mode.h>
#include <TUIC/mouse_button.h>
#include <TUIC/keyboard_key.h>
#include <TUIC/button_state.h>
#include <TUIC/cursor_mode.h>


/*!
 * @brief A struct for storing extended @ref TuiWindow craete info.
 */
typedef struct TuiWindowCreateInfo
{
	/*!
	 * @brief If the window should be resizable by the end user dragging the window edges.
	 */
	TuiBoolean resizable;
	/*!
	 * @brief If the window should be visible to the user or hidden from view.
	 */
	TuiBoolean visible;
	/*!
	 * @brief If the window should have a taskbar and buttons on the top and have borders on the sides.
	 */
	TuiBoolean decorated;
	/*!
	 * @brief If the window should open with input focus.
	 */
	TuiBoolean focused;
	/*!
	 * @brief If the window should always be on top of other windows.
	 */
	TuiBoolean topmost;
	/*!
	 * @brief If the window should start as maximized.
	 */
	TuiBoolean maximized;
	/*!
	 * @brief If the mouse cursor should be placed in the center of the window when it is opened.
	 */
	TuiBoolean center_cursor;
	/*!
	 * @brief If the window should gain input focus when @ref tuiWindowShow() is called.
	 */
	TuiBoolean focus_on_show;
	/*!
	 * @brief If the window should start hidden.
	 */
	TuiBoolean hidden;
	/*!
	 * @brief If the window should open as fullscreen.
	 */
	TuiBoolean fullscreen;
	/*!
	 * @brief If the window opens in fullscreen, which @ref TuiMonitor should it open in. If @ref TUI_NULL, it will open in the primary monitor.
	 */
	TuiMonitor monitor;
	/*!
	 * @brief If the size of the framebuffer should be resized automatically to match the viewport size of the window upon resizes.
	 */
	TuiBoolean framebuffer_match_viewport_size;
	/*!
	 * @brief The initial pixel width of the window framebuffer if it is unmathching of the viewport. If 0, the viewport width passed as a function parameter will be used instead.
	 */
	int unmatching_framebuffer_pixel_width;
	/*!
	 * @brief The initial pixel height of the window framebuffer if it is unmathching of the viewport. If 0, the viewport height passed as a function parameter will be used instead.
	 */
	int unmatching_framebuffer_pixel_height;
} TuiWindowCreateInfo;
/*! @name Window Create Info Functions
 *  @{ */
/*!
 * @brief Create a @ref TuiWindowCreateInfo struct, with all members set to default values.
 *
 * @returns The default value @ref TuiWindowCreateInfo struct.
 *
 * @errors This function can have no errors.
 *
 * @requirements This function can be called freely, even if TUIC is not currently initialized.
 *
 * @thread_safety This function does not access memory in ways that could cause a data race, so it is thread safe.
 */
TuiWindowCreateInfo tuiWindowCreateInfo();
/*! @} */


/*! @name Window Functions
 *
 * Functions for manipulating @ref TuiWindow opaque objects.
 *  @{ */
/*!
 * @brief Create a new @ref TuiWindow.
 *
 * @param viewport_pixel_width The pixel width of the viewport of the window.
 * @param viewport_pixel_height The pixel height of the viewport of the window.
 * @param title The title bar text of the window.
 * @param create_info A pointer to an @ref TuiWindowCreateInfo struct with extended window creation info. If @ref TUI_NULL, default values are used instead.
 *
 * @returns The created @ref TuiWindow. @ref TUI_NULL is returned if an error occurs.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS, @ref TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned @ref TuiWindow must be destroyed before TUIC is terminated, using the function @ref tuiWindowDestroy().
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
TuiWindow tuiWindowCreate(int viewport_pixel_width, int viewport_pixel_height, const char* title, TuiWindowCreateInfo* create_info);
/*!
 * @brief Free a @ref TuiWindow and correctly dispose of of its internally managed resources.
 *
 * @param window The @ref TuiWindow to destroy.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiWindowDestroy(TuiWindow window);
/*!
 * @brief Get the amount of @ref TuiWindow that currently exist.
 *
 * @returns The amount of windows that currently exist.
 *
 * @errors This function does not have errors.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiGetWindowCount();
/*!
 * @brief Clear the color of the framebuffer of a @ref TuiWindow to a solid color.
 *
 * @param window The @ref TuiWindow to clear.
 * @param r The red color value of the clear color.
 * @param g The green color value of the clear color.
 * @param b The blue color value of the clear color.
 * @param a The alpha color value of the clear color.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiWindowClearColor(TuiWindow window, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
/*!
 * @brief Get the pixel dimensions of the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param pixel_width A pointer to where the pixel width of the framebuffer will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param pixel_height A pointer to where the pixel height of the framebuffer will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiWindowSetFramebufferPixelDimensions(TuiWindow window, int pixel_width, int pixel_height);
/*!
 * @brief Get the pixel width of the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @return The pixel width of the framebuffer.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetFramebufferPixelWidth(TuiWindow window);
/*!
 * @brief Get the pixel height of the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @return The pixel height of the framebuffer.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetFramebufferPixelHeight(TuiWindow window);
/*!
 * @brief Get a @ref TuiImage rendered from the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow to render to the image.
 *
 * @returns The @ref TuiImage.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned @ref TuiImage must be destroyed using @ref tuiImageDestroy().
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
TuiImage tuiWindowGetImage(TuiWindow window);
/*!
 * @brief Render the framebuffer of a @ref TuiWindow to a @ref TuiImage, resizing it if necessary.
 *
 * @param window The @ref TuiWindow to render to the image.
 * @param image The @ref TuiImage to render to.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIZLIED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_IMAGE. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors..
 */
void tuiWindowWriteImage(TuiWindow window, TuiImage image);
/*!
 * @brief Get the raw pixels of the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow to get the pixels from.
 * @param pixel_width A pointer to where the pixel width of the window will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param pixel_height A pointer to where the pixel height of the window will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param fill_pixels A pointer to an array store the pixels array in. If the sizes specified in pixel_width and pixel_height do not fit the pixels, the array is reallocated. If @ref TUI_NULL, a new array is allocated instead.
 *
 * @returns The pixels array.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime If fill_pixels is used, it must point to an array created with @ref tuiAllocate(). The returned pixels array must be destroyed with @ref tuiFree().
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
uint8_t* tuiWindowGetPixels(TuiWindow window, int* pixel_width, int* pixel_height, uint8_t* fill_pixels);
/*!
 * @brief Draw a @ref TuiBatch to the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param atlas The @ref TuiAtlas.
 * @param palette The @ref TuiPalette.
 * @param batch The @ref TuiBatch.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_BATCH, and @ref TUI_ERROR_PALETTE_REQUIRED.  The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawBatch(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiBatch batch);
/*!
 * @brief Draw a @ref TuiBatch to the framebuffer of a @ref TuiWindow with a transformation.
 *
 * @param window The @ref TuiWindow.
 * @param atlas The @ref TuiAtlas.
 * @param palette The @ref TuiPalette.
 * @param batch The @ref TuiBatch.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the window.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the window.
 * @param top_y The topmost y pixel coordinate of the draw rect within the window.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_BATCH, and @ref TUI_ERROR_PALETTE_REQUIRED. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawBatchTransformed(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiBatch batch, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw a @ref TuiPanel to the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param panel The @ref TuiPanel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawPanel(TuiWindow window, TuiPanel panel);
/*!
 * @brief Draw a @ref TuiPanel to the framebuffer of a @ref TuiWindow with a transformation.
 *
 * @param window The @ref TuiWindow.
 * @param panel The @ref TuiPanel.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the window.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the window.
 * @param top_y The topmost y pixel coordinate of the draw rect within the window.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawPanelTransformed(TuiWindow window, TuiPanel panel, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw a @ref TuiTexture to the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param texture The @ref TuiTexture.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_TEXTURE. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawTexture(TuiWindow window, TuiTexture texture);
/*!
 * @brief Draw a @ref TuiTexture to the framebuffer of a @ref TuiWindow with a transformation.
 *
 * @param window The @ref TuiWindow.
 * @param texture The @ref TuiTexture.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the window.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the window.
 * @param top_y The topmost y pixel coordinate of the draw rect within the window.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_TEXTURE. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawTextureTransformed(TuiWindow window, TuiTexture texture, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw the texture of a @ref TuiAtlas to the framebuffer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param atlas The @ref TuiAtlas.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_ATLAS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawAtlas(TuiWindow window, TuiAtlas atlas);
/*!
 * @brief Draw the texture of a @ref TuiAtlas to the framebuffer of a @ref TuiWindow with a transformation.
 *
 * @param window The @ref TuiWindow.
 * @param atlas The @ref TuiAtlas.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the window.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the window.
 * @param top_y The topmost y pixel coordinate of the draw rect within the window.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_ATLAS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawAtlasTransformed(TuiWindow window, TuiAtlas atlas, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw a the framebuffer of a @ref TuiWindow to the framebuffer of another one.
 *
 * @param window The @ref TuiWindow.
 * @param subject_window The subject @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_SUBJECT_WINDOW. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawWindow(TuiWindow window, TuiWindow subject_window);
/*!
 * @brief Draw a the framebuffer of a @ref TuiWindow to the framebuffer of another one with a transformation.
 *
 * @param window The @ref TuiWindow.
 * @param subject_window The subject @ref TuiWindow.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the window.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the window.
 * @param top_y The topmost y pixel coordinate of the draw rect within the window.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and @ref TUI_ERROR_NULL_SUBJECT_WINDOW. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowDrawWindowTransformed(TuiWindow window, TuiWindow subject_window, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Render the framebuffer of a @ref TuiWindow to its viewport and swap the buffers.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowFrame(TuiWindow window);
/*!
 * @brief Set the actual rendered swap interval of the window.
 *
 * @param window The @ref TuiWindow.
 * @param interval The swap interval. If the it is 0, the interval is set to match its monitor's vsync.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowFrameInterval(TuiWindow window, int interval);
/*!
 * @brief Get the @ref TuiCursorMode of a @ref TuiWindow.
 * 
 * @param window The @ref TuiWindow.
 * 
 * @returns The @ref TuiCursorMode. @ref TUI_CURSOR_MODE_INVALID is returned if an error occurs.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiCursorMode tuiWindowGetCursorMode(TuiWindow window);
/*!
 * @brief Set the @ref TuiCursorMode of a @ref TuiWindow.
 * 
 * @param window The @ref TuiWindow.
 * @param cursor_mode The @ref TuiCursorMode.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_CURSOR_MODE, and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetCursorMode(TuiWindow window, TuiCursorMode cursor_mode);
/*!
 * @brief Get if sticky keys mode is enabled for a @ref TuiWindow. Effects the output of tuiGetKeyboardKey(), so that @ref TUI_BUTTON_PRESS is returned the first time after the key is pressed, even if it is no longer it is pressed.
 * 
 * @param window The @ref TuiWindow
 * 
 * @returns If sticky keys are enabled for the window.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 * 
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetStickyKeysEnabled(TuiWindow window);
/*!
 * @brief Set if sticky keys mode is enabled for a @ref TuiWindow. Effects the output of tuiGetKeyboardKey(), so that @ref TUI_BUTTON_PRESS is returned the first time after the key is pressed, even if it is no longer it is pressed.
 *
 * @param window The @ref TuiWindow.
 * @param sticky_keys_mode If sticky keys should be enabled for the window. 
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetStickyKeysEnabled(TuiWindow window, TuiBoolean sticky_keys_mode);
/*!
 * @brief Get if sticky mouse buttons mode is enabled for a @ref TuiWindow. Effects the output of tuiWindowGetMouseButton(), so that @ref TUI_BUTTON_PRESS is returned the first time after the mouse button is pressed, even if it is no longer it is pressed.
 *
 * @param window The @ref TuiWindow
 *
 * @returns If sticky mouse buttons are enabled for the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetStickyMouseButtonsEnabled(TuiWindow window);
/*!
 * @brief Set if sticky mouse buttons mode is enabled for a @ref TuiWindow. Effects the output of tuiWindowGetMouseButton(), so that @ref TUI_BUTTON_PRESS is returned the first time after the mouse button is pressed, even if it is no longer it is pressed.
 *
 * @param window The @ref TuiWindow.
 * @param sticky_mouse_buttons If sticky mouse buttons should be enabled for the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetStickyMouseButtonsEnabled(TuiWindow window, TuiBoolean sticky_mouse_buttons);
/*!
 * @brief Get if lock key mods mode is enabled for a @ref TuiWindow. If enabled, callback @ref TuiKeyboardMod values will include the mods @ref TUI_MOD_CAPS_LOCK and @ref TUI_MOD_NUM_LOCK if capslock or numlock is active, not if the key is pressed.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns If lock key mods mode buttons are enabled for the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetLockKeyModsEnabled(TuiWindow window);
/*!
 * @brief Set if lock key mods mode is enabled for a @ref TuiWindow. If enabled, callback @ref TuiKeyboardMod values will include the mods @ref TUI_MOD_CAPS_LOCK and @ref TUI_MOD_NUM_LOCK if capslock or numlock is active, not if the key is pressed.
 *
 * @param window The @ref TuiWindow.
 * @param lock_mods If lock key mods should be enabled for the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetLockKeyModsEnabled(TuiWindow window, TuiBoolean lock_mods);
/*!
 * @brief Get if raw mouse motion mode is enabled for a @ref TuiWindow. If enabled, raw mouse motion will be used instead of default mouse motion with scaling and acceleration when using cursor mode @ref TUI_CURSOR_MODE_DISABLED.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns If raw mouse motion is enabled for the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetRawMouseMotionEnabled(TuiWindow window);
/*!
 * @brief Set if raw mouse motion mode is enabled for a @ref TuiWindow. If enabled, raw mouse motion will be used instead of default mouse motion with scaling and acceleration when using cursor mode @ref TUI_CURSOR_MODE_DISABLED.
 *
 * @param window The @ref TuiWindow.
 * @param raw_mouse_motion If lock raw mouse motion should be enabled for the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetRawMouseMotionEnabled(TuiWindow window, TuiBoolean raw_mouse_motion);
/*!
 * @brief Get the @ref TuiButtonState of a @ref TuiKeyboardKey.
 *
 * @param window The @ref TuiWindow.
 * @param key The @ref TuiKeyboardKey.
 *
 * @returns The @ref TuiButtonState of the key.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiButtonState tuiWindowGetKeyboardKey(TuiWindow window, TuiKeyboardKey key);
/*!
 * @brief Get the @ref TuiButtonState of a @ref TuiMouseButton.
 *
 * @param window The @ref TuiWindow.
 * @param mouse_button The @ref TuiMouseButton.
 *
 * @returns The @ref TuiButtonState of the mouse button.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiButtonState tuiWindowGetMouseButton(TuiWindow window, TuiMouseButton mouse_button);
/*!
 * @brief Get the position of the mouse cursor.
 *
 * @param window The @ref TuiWindow to get the relative position from.
 * @param x_position A pointer to where the x position of the mouse cursor will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param y_position A pointer to where the y position of the mouse cursor will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowGetCursorPosition(TuiWindow window, double* x_position, double* y_position);
/*!
 * @brief Get the x position of the mouse cursor.
 *
 * @param window The @ref TuiWindow to get the relative position from.
 *
 * @returns The mouse position.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
double tuiWindowGetCursorXPosition(TuiWindow window);
/*!
 * @brief Get the y position of the mouse cursor.
 *
 * @param window The @ref TuiWindow to get the relative position from.
 *
 * @returns The mouse position.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
double tuiWindowGetCursorYPosition(TuiWindow window);
/*!
 * @brief Set the position of the mouse cursor.
 *
 * @param window The @ref TuiWindow to get the relative position from.
 * @param x_position The x position of the mouse cursor.
 * @param y_position The y position of the mouse cursor.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetCursorPosition(TuiWindow window, double x_position, double y_position);
/*!
 * @brief Get if a @ref TuiWindow should close
 *
 * @param window The @ref TuiWindow.
 * 
 * @returns @ref TuiBoolean that is @ref TUI_TRUE if the end user tried closing the window through the close button or other means, or if the window was set to close with tuiWindowsetShouldClose9).
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowShouldClose(TuiWindow window);
/*!
 * @brief Set if a @ref TuiWindow should close.
 *
 * @param window The @ref TuiWindow.
 * @param should_close The @ref TuiBoolean that is @ref TUI_TRUE if the window should close.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetShouldClose(TuiWindow window, TuiBoolean should_close);
/*!
 * @brief Set the title bar text of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param title The title.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_STRING, and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetTitle(TuiWindow window, const char* title);
/*!
 * @brief Set the title bar text of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param title The title.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_STRING, and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 * 
 * @pointer_lifetime The returned title array is reallocated every time the @ref TuiWindow title is changed again.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
const char* tuiWindowGetTitle(TuiWindow window);
/*!
 * @brief Set the icon of a @ref TuiWindow to the default platform icon.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_IMAGE, @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned title array is reallocated every time the @ref TuiWindow title is changed again.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetDefaultIcon(TuiWindow window);
/*!
 * @brief Set the icon of a @ref TuiWindow to a 4 channel @ref TuiImage
 *
 * @param window The @ref TuiWindow.
 * @param icon_image The window icon image.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_IMAGE, @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned title array is reallocated every time the @ref TuiWindow title is changed again.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetIconImage(TuiWindow window, TuiImage icon_image);
/*!
 * @brief Set the icon of a @ref TuiWindow to a 4 channel pixel array.
 *
 * @param window The @ref TuiWindow.
 * @param pixel_width The width of the pixel array in pixels.
 * @param pixel_height The height of the pixel array in pixels.
 * @param pixels A pointer to the pixel array.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_NULL_PIXELS, @ref TUI_ERROR_INVALID_PIXEL_DIMENSIONS, @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, and GLFW errors. The first error tha occurs will cause the function to immediatly return.  Also, an inccorectly sized or allocated pixel array may cause undefined behaviour or a fatal crash without an error.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned title array is reallocated every time the @ref TuiWindow title is changed again.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetIconRawPixels(TuiWindow window, int pixel_width, int pixel_height, const uint8_t* pxiels);
/*!
 * @brief Get the position of a @ref TuiWindow.
 * 
 * @param window The @ref TuiWindow.
 * @param x_position A pointer to where the x position of the top left of the window will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param y_position A pointer to where the y position of the top left corner of the window will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowGetPosition(TuiWindow window, int* x_position, int* y_position);
/*!
 * @brief Get the x position of a @ref TuiWindow.
 * 
 * @param window The @ref TuiWindow.
 * 
 * @returns The x position of the top left corner of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetXPosition(TuiWindow window);
/*!
 * @brief Get the y position of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The y position of the top left corner of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetYPosition(TuiWindow window);
/*!
 * @brief Set the position of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param x_position The x position of the top left corner of the window.
 * @param y_position The y position of the top left corner of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetPosition(TuiWindow window, int x_position, int y_position);
/*!
 * @brief Set size limits for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param min_width The minimum width limit. If 0, there is no size limit.
 * @param min_height The minimum height limit. If 0, there is no size limit.
 * @param max_width The maximum width limit. If 0, there is no limit.
 * @param max_height The maximum height. If 0, there is no limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetSizeLimits(TuiWindow window, int min_width, int min_height, int max_width, int max_height);
/*!
 * @brief Set minimum size limits for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param min_width The minimum width limit. If 0, there is no size limit.
 * @param min_height The minimum height limit. If 0, there is no size limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetMinSizeLimits(TuiWindow window, int min_width, int min_height);
/*!
 * @brief Set maximum size limits for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param max_width The maximum width limit. If 0, there is no limit.
 * @param max_height The maximum height. If 0, there is no limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetMaxSizeLimits(TuiWindow window, int max_width, int max_height);
/*!
 * @brief Set minimum width size limit for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param min_width The minimum width limit. If 0, there is no size limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetMinWidth(TuiWindow window, int min_width);
/*!
 * @brief Set the minimum height size limit for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param min_height The minimum height limit. If 0, there is no size limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetMinHeight(TuiWindow window, int min_height);
/*!
 * @brief Set the maximum width size limit for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param max_width The maximum width limit. If 0, there is no limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetMaxWidth(TuiWindow window, int max_width);
/*!
 * @brief Set the maximum height size limit for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param max_height The maximum height limit. If 0, there is no limit.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetMaxHeight(TuiWindow window, int max_height);
/*!
 * @brief Get the size limits for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param min_width A pointer to where the minimum width limit will be stored. If @ref TUI_NULL or an error occurs, it is ignored. If there is no limit, 0 will be stored.
 * @param min_height A pointer to where the minimum height limit will be stored. If @ref TUI_NULL or an error occurs, it is ignored. If there is no limit, 0 will be stored.
 * @param max_width A pointer to where the maximum width limit will be stored. If @ref TUI_NULL or an error occurs, it is ignored. If there is no limit, 0 will be stored.
 * @param max_height A pointer to where the maximum height limit will be stored. If @ref TUI_NULL or an error occurs, it is ignored. If there is no limit, 0 will be stored.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowGetSizeLimits(TuiWindow window, int* min_width, int* min_height, int* max_width, int* max_height);
/*!
 * @brief Get the minimum width of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The minimum width limit of the window.  If there is no limit, 0 will be returned.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetMinWidth(TuiWindow window);
/*!
 * @brief Get the minimum height of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The minimum height limit of the window.  If there is no limit, 0 will be returned.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetMinHeight(TuiWindow window);
/*!
 * @brief Get the maximum width of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The maximum width limit of the window.  If there is no limit, 0 will be returned.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetMaxWidth(TuiWindow window);
/*!
 * @brief Get the maximum height of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The maximum height limit of the window.  If there is no limit, 0 will be returned.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetMaxHeight(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow has one or more size limits.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window has one or more size limits, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowHasSizeLimits(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow has one or more minimum size limits.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window has one or more minimum size limits, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowHasMinSizeLimits(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow has one or more maximum size limits.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window has one or more maximum size limits, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowHasMaxSizeLimits(TuiWindow window);
/*!
 * @brief Set a fixed aspect ratio for a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param numerator The numerator of the fixed aspect ratio.
 * @param denominator The denominator of the fixed aspect ratio.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, @ref TUI_ERROR_INVALID_ASPECT_RATIO, and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetFixedAspectRatio(TuiWindow window, int numerator, int denominator);
/*!
 * @brief Fix the aspect ratio of a @ref TuiWindow to its current aspect ratio.
 * 
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowFixCurrentAspectRatio(TuiWindow window);
/*!
 * @brief Unfix the aspect ratio of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowUnfixAspectRatio(TuiWindow window);
/*!
 * @brief Get if the aspect ratio of a @ref TuiWindow is fixed.
 *
 * @param window The @ref TuiWindow.
 * 
 * @returns The @ref TuiBoolean result. If the window has a fixed aspect ratio, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetAspectRatioIsFixed(TuiWindow window);
/*!
 * @brief Get the aspect ratio of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param numerator A pointer to where to store the numerator. If @ref TUI_NULL or an error occurs, it is ignored. IF the window has no fixed aspect ratio, 0 is stored.
 * @param numerator A pointer to where to store the denominator. If @ref TUI_NULL or an error occurs, it is ignored. IF the window has no fixed aspect ratio, 0 is stored.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowGetAspectRatio(TuiWindow, int* numerator, int* denominator);
/*!
 * @brief Get the content scale of a @ref TuiWindow. This is the content scale is the ratio between the current DPI and the platform's default DPI.
 *
 * @param window The @ref TuiWindow.
 * @param numerator A pointer to where to store the numerator. If @ref TUI_NULL or an error occurs, it is ignored. IF the window has no fixed aspect ratio, 0 is stored.
 * @param numerator A pointer to where to store the denominator. If @ref TUI_NULL or an error occurs, it is ignored. IF the window has no fixed aspect ratio, 0 is stored.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowGetContentScale(TuiWindow window, float* scale_wide, float* scale_tall);
/*!
 * @brief Get the content scale wide of a @ref TuiWindow. This is the content scale is the ratio between the current DPI and the platform's default DPI.
 *
 * @param window The @ref TuiWindow.
 * 
 * @returns The content scale wide of the window.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
float tuiWindowGetContentScaleWide(TuiWindow window);
/*!
 * @brief Get the content scale tall of a @ref TuiWindow. This is the content scale is the ratio between the current DPI and the platform's default DPI.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The content scale tall of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
float tuiWindowGetContentScaleTall(TuiWindow window);
/*!
 * @brief Iconiify (minimize) a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowIconify(TuiWindow window);
/*!
 * @brief Restore a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowRestore(TuiWindow window);
/*!
 * @brief Maximize a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowMaximize(TuiWindow window);
/*!
 * @brief Show a @ref TuiWindow that was hidden with tuiWindowHide().
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowShow(TuiWindow window);
/*!
 * @brief Hide a @ref TuiWindow from the desktop so that it does not even appear on the taskbar.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowHide(TuiWindow window);
/*!
 * @brief Give a @ref TuiWindow input focus and bring it to the top of all other windows.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowFocus(TuiWindow window);
/*!
 * @brief Request attention to a window, causing it to flash on the taskbar and other operating system specific effects to notify the user.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowRequestAttention(TuiWindow window);
/*!
 * @brief Get the @ref TuiMonitor that a @ref TuiWindow is on.
 *
 * @param window The @ref TuiWindow.
 * 
 * @returns monitor The @ref TuiMonitor that the window is on.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiMonitor tuiWindowGetMonitor(TuiWindow window);
/*!
 * @brief Set a @ref TuiWindow to be fullscreen in its current monitor.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetFullscreenCurrentMonitor(TuiWindow window);
/*!
 * @brief Set a @ref TuiWindow to be fullscreen in a specific @ref TuiMonitor.
 *
 * @param window The @ref TuiWindow.
 * @param monitor The @ref TuiMonitor.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetFullscreen(TuiWindow window, TuiMonitor monitor);
/*!
 * @brief Set a @ref TuiWindow to be windowed.
 *
 * @param window The @ref TuiWindow.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetWindowed(TuiWindow window);
/*!
 * @brief Set the size of a @ref TuiWindow viewport when it is windowed.
 *
 * @param window The @ref TuiWindow.
 * @param viewport_pixel_width The pixel width of the viewport.
 * @param viewport_pixel_height The pixel height of the viewport.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetWindowedViewportSize(TuiWindow window, int viewport_pixel_width, int viewport_pixel_height);
/*!
 * @brief Get the pixel width of the viewport of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * 
 * @returns The pixel width of the viewport of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetViewportPixelWidth(TuiWindow window);
/*!
 * @brief Get the pixel height of the viewport of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The pixel height of the viewport of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiWindowGetViewportPixelHeight(TuiWindow window);
/*!
 * @brief Get the pixel dimensions of the viewport of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param pixel_width A pointer to where the pixel width of the framebuffer will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param pixel_height A pointer to where the pixel height of the framebuffer will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 *
 * @returns The pixel height of the viewport of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowGetViewportPixelDimensons(TuiWindow window, int* pixel_width, int* pixel_height);
/*!
 * @brief Set if the framebuffer size is fixed to match the viewport size of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param framebuffer_matches_viewport_size If the framebuffer size matches the viewport size of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetFramebufferMatchesViewportSize(TuiWindow window, TuiBoolean framebuffer_matches_viewport_size);
/*!
 * @brief Set if the framebuffer size is fixed to match the viewport size of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * 
 * @returns If the framebuffer size matches the viewport size of the window.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NULL_WINDOW and GLFW errors. The first error tha occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetFramebufferMatchesViewportSize(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow is currently fullscreen.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently fullscreen, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetIsFullscreen(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow currently has input focus.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window currently has input focus, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetFocused(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow is currently iconified (minimized).
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently minimized, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetIconified(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow is currently maximized.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently maximized, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetMaximized(TuiWindow window);
/*!
 * @brief Get if the mouse is currently within a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the mouse is currently within the window, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetMouseEntered(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow is currently visible.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently visible, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetVisible(TuiWindow window);
/*!
 * @brief Get if a @ref TuiWindow is currently resizable.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently resizable, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetResizable(TuiWindow window);
/*!
 * @brief Set the @ref TuiWindow asy resizable.
 *
 * @param window The @ref TuiWindow.
 * @param resizable If the window should be resizable or not.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetResizable(TuiWindow window, TuiBoolean resizable);
/*!
 * @brief Get if a @ref TuiWindow is currently hashas title bar, borders, and control buttons.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently decorated, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetDecorated(TuiWindow window);
/*!
 * @brief Set the @ref TuiWindow has title bar, borders, and control buttons.
 *
 * @param window The @ref TuiWindow.
 * @param resizable If the window should be resizable.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetDecorated(TuiWindow window, TuiBoolean decorated);
/*!
 * @brief Get if a @ref TuiWindow is currently forced on top of all other windows.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window is currently topmost, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetTopmost(TuiWindow window);
/*!
 * @brief Set if a @ref TuiWindow should be forced on top of all other windows.
 *
 * @param window The @ref TuiWindow.
 * @param resizable If the window should be resizable.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetTopmost(TuiWindow window, TuiBoolean topmost);
/*!
 * @brief Get if a @ref TuiWindow should gain input focus when @ref tuiWindowShow() is called.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The @ref TuiBoolean result. If the window currently focuses on show, it
 * returns @ref TUI_TRUE. Otherwise, it returns @ref TUI_FALSE.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
TuiBoolean tuiWindowGetFocusOnShow(TuiWindow window);
/*!
 * @brief Set the @ref TuiWindow should gain input focus when @ref tuiWindowShow() is called.
 *
 * @param window The @ref TuiWindow.
 * @param resizable If the window should be resizable.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetFocusOnShow(TuiWindow window, TuiBoolean focus_on_show);
/*!
 * @brief Set the user pointer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param ptr The user pointer.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_WINDOW. The first error that occurs will cause the function to immediatly return.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetUserPointer(TuiWindow window, void* ptr);
/*!
 * @brief Get the user pointer of a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 *
 * @returns The user pointer.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_WINDOW. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void* tuiWindowGetUserPointer(TuiWindow window);
/*!
 * @brief Set the @ref TuiCursor to use when the mouse is over a @ref TuiWindow.
 *
 * @param window The @ref TuiWindow.
 * @param cursor The @ref TuiCursor.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiWindowSetCursor(TuiWindow window, TuiCursor cursor);
/*!
 * @brief Set the @ref tuiWindowMoveFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowMoveFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowMoveFunction tuiWindowSetMoveCallback(TuiWindow window, tuiWindowMoveFunction callback);
/*!
 * @brief Set the @ref tuiWindowCloseFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowCloseFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowCloseFunction tuiWindowSetCloseCallback(TuiWindow window, tuiWindowCloseFunction callback);
/*!
 * @brief Set the @ref tuiWindowFocusFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowFocusFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowFocusFunction tuiWindowSetFocusCallback(TuiWindow window, tuiWindowFocusFunction callback);
/*!
 * @brief Set the @ref tuiWindowIconifyFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowIconifyFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowIconifyFunction tuiWindowSetIconifyCallback(TuiWindow window, tuiWindowIconifyFunction callback);
/*!
 * @brief Set the @ref tuiWindowMaximizeFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowMaximizeFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowMaximizeFunction tuiWindowSetMaximizeCallback(TuiWindow window, tuiWindowMaximizeFunction callback);
/*!
 * @brief Set the @ref tuiWindowViewportResizeFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowViewportResizeFunction.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowViewportResizeFunction tuiWindowSetViewportResizeCallback(TuiWindow window, tuiWindowViewportResizeFunction callback);
/*!
 * @brief Set the @ref tuiWindowContentScaleFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiWindowContentScaleFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiWindowContentScaleFunction tuiWindowSetContentScaleCallback(TuiWindow window, tuiWindowContentScaleFunction callback);
/*!
 * @brief Set the @ref tuiKeyboardKeyboardKeyFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiKeyboardKeyboardKeyFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiKeyboardKeyboardKeyFunction tuiWindowSetKeyboardKeyCallback(TuiWindow window, tuiKeyboardKeyboardKeyFunction callback);
/*!
 * @brief Set the @ref tuiCharFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiCharFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiCharFunction tuiWindowSetCharCallback(TuiWindow window, tuiCharFunction callback);
/*!
 * @brief Set the @ref tuiMouseButtonFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiMouseButtonFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiMouseButtonFunction tuiWindowSetMouseButtonCallback(TuiWindow window, tuiMouseButtonFunction callback);
/*!
 * @brief Set the @ref tuiCursorMoveFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiCursorMoveFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiCursorMoveFunction tuiWindowSetCursorMoveCallback(TuiWindow window, tuiCursorMoveFunction callback);
/*!
 * @brief Set the @ref tuiCursorEnterFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiCursorEnterFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiCursorEnterFunction tuiWindowSetCursorEnterCallback(TuiWindow window, tuiCursorEnterFunction callback);
/*!
 * @brief Set the @ref tuiMouseScrollFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiMouseScrollFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiMouseScrollFunction tuiWindowSetMouseScrollCallback(TuiWindow window, tuiMouseScrollFunction callback);
/*!
 * @brief Set the @ref tuiFileDropFunction called by a window.
 *
 * @param window The @ref TuiWindow.
 * @param callback The @ref tuiFileDropFunction.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_WINDOW, and GLFW errors. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
tuiFileDropFunction tuiWindowSetFileDropCallback(TuiWindow window, tuiFileDropFunction callback);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard