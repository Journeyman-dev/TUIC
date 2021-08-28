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
/*! \file panel.h
 */
#ifndef TUIC_PANEL_H //header guard
#define TUIC_PANEL_H
#ifdef __cplusplus //extern C guard
extern "C" {
#endif
#include <TUIC/types.h>


/*! @name Panel Functions
 *
 * Functions for manipulating @ref TuiPanel opaque objects.
 *  @{ */
/*!
 * @brief Create a @ref TuiPanel.
 *
 * @param pixel_width The width of the framebuffer in pixels.
 * @param pixel_height The height of the framebuffer in pixels.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_INVALID_PANEL_DIMENSIONS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned @ref TuiPanel must be destroyed before TUIC is terminated, using the function @ref tuiPanelDestroy().
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
TuiPanel tuiPanelCreate(int pixel_width, int pixel_height);
/*!
 * @brief Free a @ref TuiPanel and correctly dispose of of its internally managed resources.
 *
 * @param palette The @ref TuiPanel to destroy.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiPanelDestroy(TuiPanel panel);
/*!
 * @brief Get the amount of @ref TuiPanel that currently exist.
 *
 * @returns The amount of panels that currently exist.
 *
 * @errors This function does not have errors.
 *
 * @requirements This function can be called at any time.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiGetPanelCount();
/*!
 * @brief Get a @ref TuiImage rendered from the framebuffer of a @ref TuiPanel.
 *
 * @param panel The @ref TuiPanel to render to the image.
 *
 * @returns The @ref TuiImage.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime The returned @ref TuiImage must be destroyed using @ref tuiImageDestroy().
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
TuiImage tuiPanelGetImage(TuiPanel panel);
/*!
 * @brief Render the framebuffer of a @ref TuiPanel to a @ref TuiImage, resizing it if necessary.
 *
 * @param panel The @ref TuiPanel to render to the image.
 * @param image The @ref TuiImage to render to.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_IMAGE. The first error that occurs will cause the function to immediatly return. 
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors..
 */
void tuiPanelWriteImage(TuiPanel panel, TuiImage image);
/*!
 * @brief Get the raw pixels of the framebuffer of a @ref TuiPanel.
 *
 * @param panel The @ref TuiPanel to get the pixels from.
 * @param pixel_width A pointer to where the pixel width of the panel will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param pixel_height A pointer to where the pixel height of the panel will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param fill_pixels A pointer to an array store the pixels array in. If the sizes specified in pixel_width and pixel_height do not fit the pixels, the array is reallocated. If @ref TUI_NULL, a new array is allocated instead.
 *
 * @returns The pixels array.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @pointer_lifetime If fill_pixels is used, it must point to an array created with @ref tuiAllocate(). The returned pixels array must be destroyed with @ref tuiFree().
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors..
 */
uint8_t* tuiPanelGetPixels(TuiPanel panel, int* pixel_width, int* pixel_height, uint8_t* fill_pixels);
/*!
 * @brief Clear the color of the framebuffer of a @ref TuiPanel to a solid color.
 *
 * @param panel The @ref TuiPanel to clear.
 * @param r The red color value of the clear color.
 * @param g The green color value of the clear color.
 * @param b The blue color value of the clear color.
 * @param a The alpha color value of the clear color.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiPanelClearColor(TuiPanel panel, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
/*!
 * @brief Set the pixel dimensions of the framebuffer of a @ref TuiPanel.
 * 
 * @param The @ref TuiPanel.
 * @param The new pixel width of the framebuffer.
 * @param The new pixel height of the framebuffer.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_INVALID_PANEL_DIMENSIONS. The first error that occurs will cause the function to immediatly return.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiPanelSetPixelDimensions(TuiPanel panel, int pixel_width, int pixel_height);
/*!
 * @brief Get the pixel dimensions of the framebuffer of a @ref TuiPanel.
 * 
 * @param panel The @ref TuiPanel.
 * @param pixel_width A pointer to where the pixel width of the framebuffer will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * @param pixel_height A pointer to where the pixel height of the framebuffer will be stored. If @ref TUI_NULL or an error occurs, it is ignored.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access and to prevent graphics context errors.
 */
void tuiPanelGetPixelDimensions(TuiPanel panel, int* pixel_width, int* pixel_height);
/*!
 * @brief Get the pixel width of the framebuffer of a @ref TuiPanel.
 * 
 * @param panel The @ref TuiPanel.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @return The pixel width of the framebuffer.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiPanelGetPixelWidth(TuiPanel panel);
/*!
 * @brief Get the pixel height of the framebuffer of a @ref TuiPanel.
 *
 * @param panel The @ref TuiPanel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED and @ref TUI_ERROR_NULL_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @return The pixel height of the framebuffer.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
int tuiPanelGetPixelHeight(TuiPanel panel);
/*!
 * @brief Draw a @ref TuiBatch to the framebuffer of a @ref TuiPanel.
 * 
 * @param panel The @ref TuiPanel.
 * @param atlas The @ref TuiAtlas.
 * @param palette The @ref TuiPalette.
 * @param batch The @ref TuiBatch.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL, @ref TUI_ERROR_NULL_ATLAS, @ref TUI_ERROR_NULL_BATCH, and @ref TUI_ERROR_PALETTE_REQUIRED.  The first error that occurs will cause the function to immediatly return.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawBatch(TuiPanel panel, TuiAtlas atlas, TuiPalette palette, TuiBatch batch);
/*!
 * @brief Draw a @ref TuiBatch to the framebuffer of a @ref TuiPanel with a transformation.
 *
 * @param panel The @ref TuiPanel.
 * @param atlas The @ref TuiAtlas.
 * @param palette The @ref TuiPalette.
 * @param batch The @ref TuiBatch.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the panel.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the panel.
 * @param top_y The topmost y pixel coordinate of the draw rect within the panel.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the panel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL, @ref TUI_ERROR_NULL_ATLAS, @ref TUI_ERROR_NULL_BATCH, and @ref TUI_ERROR_PALETTE_REQUIRED. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawBatchTransformed(TuiPanel panel, TuiAtlas atlas, TuiPalette palette, TuiBatch batch, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw a @ref TuiPanel to another panel.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param subject_panel The @ref TuiPanel to draw.
 * 
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_SUBJECT_PANEL. The first error that occurs will cause the function to immediatly return.
 * 
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawPanel(TuiPanel panel, TuiPanel subject_panel);
/*!
 * @brief Draw a @ref TuiPanel to another panel with a transformation.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param subject_panel The @ref TuiPanel to draw.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the panel.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the panel.
 * @param top_y The topmost y pixel coordinate of the draw rect within the panel.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the panel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_SUBJECT_PANEL. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawPanelTransformed(TuiPanel panel, TuiPanel subject_panel, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw a @ref TuiTexture to a @ref TuiPanel.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param texture The @ref TuiTexture to draw.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_TEXTURE. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawTexture(TuiPanel panel, TuiTexture texture);
/*!
 * @brief Draw a @ref TuiTexture to a @ref TuiPanel with a transformation.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param texture The @ref TuiTexture to draw.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the panel.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the panel.
 * @param top_y The topmost y pixel coordinate of the draw rect within the panel.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the panel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_TEXTURE. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawTextureTransformed(TuiPanel panel, TuiTexture texture, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw the texture of a @ref TuiAtlas to a @ref TuiPanel.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param atlas The @ref TuiAtlas to draw.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_ATLAS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawAtlas(TuiPanel panel, TuiAtlas atlas);
/*!
 * @brief Draw the texture of a @ref TuiAtlas to a @ref TuiPanel with a transformation.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param atlas The @ref TuiAtlas to draw.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the panel.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the panel.
 * @param top_y The topmost y pixel coordinate of the draw rect within the panel.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the panel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_ATLAS. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawAtlasTransformed(TuiPanel panel, TuiAtlas atlas, int left_x, int right_x, int top_y, int bottom_y);
/*!
 * @brief Draw a the framebuffer of a @ref TuiWindow to a @ref TuiPanel.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param window The @ref TuiWindow to draw.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_WINDOW. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawWindow(TuiPanel panel, TuiWindow window);
/*!
 * @brief Draw a the framebuffer of a @ref TuiWindow to a @ref TuiPanel with a transformation.
 *
 * @param panel The @ref TuiPanel to draw to.
 * @param window The @ref TuiWindow to draw.
 * @param left_x The leftmost x pixel coordinate of the draw rect within the panel.
 * @param right_x The rightmost x pixel coordinate of the draw rect within the panel.
 * @param top_y The topmost y pixel coordinate of the draw rect within the panel.
 * @param bottom_y The bottomost y pixel coordinate of the draw rect within the panel.
 *
 * @errors Possible errors in order are @ref TUI_ERROR_NOT_INITIALIZED, @ref TUI_ERROR_NULL_PANEL and @ref TUI_ERROR_NULL_WINDOW. The first error that occurs will cause the function to immediatly return.
 *
 * @requirements This function must be called only while TUIC is initialized.
 *
 * @thread_safety This function must only be called on the same thread on which TUIC was initialized to ensure safe memory access.
 */
void tuiPanelDrawWindowTransformed(TuiPanel panel, TuiWindow window, int left_x, int right_x, int top_y, int bottom_y);
/*! @} */


#ifdef __cplusplus //extern C guard
}
#endif
#endif //header guard