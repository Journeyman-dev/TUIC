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
#include <GLFW/glfw3.h>
#include "opengl33.h"
#include "glfw_error_check.h"
#include "image_inline.h"

static int mini(int x, int y)
{
	return x < y ? x : y;
}

static int maxi(int x, int y)
{
	return x > y ? x : y;
}

//taken from https://stackoverflow.com/a/31526753
static inline TuiMonitor _GetCurrentMonitor(GLFWwindow* window)
{
	GLFWmonitor* monitor = glfwGetWindowMonitor(window);
	if (monitor != TUI_NULL)
	{
		return (TuiMonitor)monitor;
	}

	int nmonitors, i;
	int wx, wy, ww, wh;
	int mx, my, mw, mh;
	int overlap, bestoverlap;

	GLFWmonitor** monitors;
	const GLFWvidmode* mode;

	bestoverlap = 0;

	glfwGetWindowPos(window, &wx, &wy);
	glfwGetWindowSize(window, &ww, &wh);
	monitors = glfwGetMonitors(&nmonitors);

	for (i = 0; i < nmonitors; i++) {
		mode = glfwGetVideoMode(monitors[i]);
		glfwGetMonitorPos(monitors[i], &mx, &my);
		mw = mode->width;
		mh = mode->height;

		overlap =
			maxi(0, mini(wx + ww, mx + mw) - maxi(wx, mx)) *
			maxi(0, mini(wy + wh, my + mh) - maxi(wy, my));

		if (bestoverlap < overlap) {
			bestoverlap = overlap;
			monitor = monitors[i];
		}
	}
	return (TuiMonitor)monitor;
}

static inline int _GCF(int n, int m) //returns the greatest common factor of the two values
{
	int gcf, remainder;

	while (n != 0)
	{
		remainder = m % n;
		m = n;
		n = remainder;
	}

	gcf = m;

	return gcf;
}

static inline TuiBoolean _WindowHasSizeLimits(TuiWindow window)
{
	return window->MinWidth != 0 && window->MinHeight != 0 && window->MaxWidth != 0 && window->MaxHeight != 0;
}

static inline void _WindowUpdateSizeLimits(TuiWindow window)
{
	glfwSetWindowSizeLimits(window->GlfwWindow, window->MinWidth, window->MinHeight, (window->MaxWidth == 0) ? GLFW_DONT_CARE : window->MaxWidth, (window->MaxHeight == 0) ? GLFW_DONT_CARE : window->MaxHeight);
}

static void glfwWindowPosCallback(GLFWwindow* glfw_window, int xpos, int ypos)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowMoveCallback(window, xpos, ypos);
}

static void glfwWindowCloseCallback(GLFWwindow* glfw_window)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowCloseCallback(window);
}

static void glfwWindowFocusCallback(GLFWwindow* glfw_window, int focused)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowFocusCallback(window, (TuiBoolean)focused);
}

static void glfwWindowIconifyCallback(GLFWwindow* glfw_window, int iconified)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowIconifyCallback(window, (TuiBoolean)iconified);
}

static void glfwWindowMaximizeCallback(GLFWwindow* glfw_window, int maximized)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowMaximizeCallback(window, (TuiBoolean)maximized);
}

static void glfwWindowFramebufferSizeCallback(GLFWwindow* glfw_window, int pixel_width, int pixel_height)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	if (
		(window->IsFullscreen == TUI_FALSE && glfwGetWindowAttrib(glfw_window, GLFW_RESIZABLE) == GLFW_TRUE) ||
		(window->ViewportPixelWidth == pixel_width && window->ViewportPixelHeight == pixel_height) ||
		(glfwGetWindowAttrib(glfw_window, GLFW_MAXIMIZED) == GLFW_TRUE)
		) //this condition is to fix a weird GLFW issue where invalid sizes sometimes get passed into this callback. seems to happen especially when transitioning between windowed and fullscreen.
	{
		if (window->FramebufferMatchViewportSize == TUI_TRUE)
		{
			TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, pixel_width, pixel_height);
			if (error_code != TUI_ERROR_NONE)
			{
				tuiDebugError(error_code, __func__);
				return;
			}
		}
		window->ViewportPixelWidth = pixel_width;
		window->ViewportPixelHeight = pixel_height;
		if (window->WindowViewportResizeCallback != TUI_NULL)
		{
			window->WindowViewportResizeCallback(window, pixel_width, pixel_height);
		}
	}
}

static void glfwWindowContentScaleCallback(GLFWwindow* glfw_window, float scale_wide, float scale_tall)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowContentScaleCallback(window, scale_wide, scale_tall);
}

static void glfwKeyCallback(GLFWwindow* glfw_window, int key, int scancode, int button_state, int mod)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->KeyboardKeyCallback(window, (TuiKeyboardKey)key, scancode, (TuiButtonState)button_state, (TuiKeyboardMod)mod);
}

static void glfwCharCallback(GLFWwindow* glfw_window, unsigned int charcode)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->CharCallback(window, charcode);
}

static void glfwMouseButtonCallback(GLFWwindow* glfw_window, int mouse_button, int button_state, int mod)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->MouseButtonCallback(window, (TuiMouseButton)mouse_button, (TuiButtonState)button_state, (TuiKeyboardMod)mod);
}

static void glfwCursorMoveCallback(GLFWwindow* glfw_window, double xpos, double ypos)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->CursorMoveCallback(window, xpos, ypos);
}

static void glfwCursorEnterCallback(GLFWwindow* glfw_window, int entered)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->CursorEnterCallback(window, (TuiBoolean)entered);
}

static void glfwScrollCallback(GLFWwindow* glfw_window, double xscroll, double yscroll)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->MouseScrollCallback(window, xscroll, yscroll);
}

static void glfwDropCallback(GLFWwindow* glfw_window, int path_count, const char* paths[])
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->FileDropCallback(window, path_count, paths);
}

static size_t sWindowCount = 0;

TuiWindow tuiWindowCreate(int viewport_pixel_width, int viewport_pixel_height, const char* title, TuiWindowCreateInfo* create_info)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (viewport_pixel_width <= 0 || viewport_pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS, __func__);
		return TUI_NULL;
	}
	if (create_info != TUI_NULL && create_info->framebuffer_match_viewport_size == TUI_FALSE && (create_info->unmatching_framebuffer_pixel_width < 0 || create_info->unmatching_framebuffer_pixel_height < 0))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS, __func__);
		return TUI_NULL;
	}

	if (title == TUI_NULL)
	{
		title = "";
	}

	TuiWindowCreateInfo create_info_used;
	if (create_info == TUI_NULL)
	{
		create_info_used = tuiWindowCreateInfo();
	}
	else
	{
		create_info_used = *create_info;
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	int glfw_error = _GlfwErrorCheck(); //catch api version or api unavailable errors
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}

	glfwWindowHint(GLFW_RESIZABLE, create_info_used.resizable);
	glfwWindowHint(GLFW_VISIBLE, create_info_used.visible);
	glfwWindowHint(GLFW_DECORATED, create_info_used.decorated);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, create_info_used.focused);
	glfwWindowHint(GLFW_FLOATING, create_info_used.topmost);
	glfwWindowHint(GLFW_MAXIMIZED, create_info_used.maximized);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, create_info_used.focus_on_show);
	glfwWindowHint(GLFW_VISIBLE, !create_info_used.hidden);

	glfw_error = _GlfwErrorCheck(); //window hint errors
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
	}

	GLFWwindow* glfw_window = TUI_NULL;
	if (create_info_used.fullscreen == TUI_TRUE)
	{
		if (create_info_used.monitor == TUI_NULL)
		{
			create_info_used.monitor = glfwGetPrimaryMonitor();
		}
		const GLFWvidmode* vid_mode = glfwGetVideoMode(create_info_used.monitor);
		glfwWindowHint(GLFW_RED_BITS, vid_mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vid_mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vid_mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vid_mode->refreshRate);
		glfw_window = glfwCreateWindow(vid_mode->width, vid_mode->height, title, create_info_used.monitor, system->BaseWindow);
		viewport_pixel_width = vid_mode->width;
		viewport_pixel_height = vid_mode->height;
	}
	else //if (create_info_used.fullscreen == TUI_FALSE)
	{
		glfw_window = glfwCreateWindow(viewport_pixel_width, viewport_pixel_height, title, TUI_NULL, system->BaseWindow);
		create_info_used.monitor = TUI_NULL;
	}
	
	if (glfw_window == TUI_NULL) //catch window creation errors
	{
		glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
		}
		else
		{
			tuiDebugError(TUI_ERROR_UNKNOWN, __func__);
		}
		return TUI_NULL;
	}

	if (create_info_used.center_cursor == TUI_TRUE)
	{
		glfwSetCursorPos(glfw_window, (double)viewport_pixel_width / 2.0, (double)viewport_pixel_height / 2.0);
	}

	int framebuffer_pixel_width = viewport_pixel_width;
	int framebuffer_pixel_height = viewport_pixel_height;

	if (create_info_used.framebuffer_match_viewport_size == TUI_FALSE)
	{
		if (create_info_used.unmatching_framebuffer_pixel_width != 0)
		{
			framebuffer_pixel_width = create_info_used.unmatching_framebuffer_pixel_width;
		}
		if (create_info_used.unmatching_framebuffer_pixel_height != 0)
		{
			framebuffer_pixel_width = create_info_used.unmatching_framebuffer_pixel_height;
		}
	}

	glfwSetFramebufferSizeCallback(glfw_window, glfwWindowFramebufferSizeCallback);

	glfw_error = _GlfwErrorCheck(); //final error check before allocating TuiWindow
	if (glfw_error != TUI_ERROR_NONE)
	{
		glfwDestroyWindow(glfw_window); //it was created, so now destroy it
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}

	TuiWindow window = (TuiWindow_s*)tuiAllocate(sizeof(TuiWindow_s));
	window->FramebufferPixelWidth = framebuffer_pixel_width;
	window->FramebufferPixelHeight = framebuffer_pixel_height;
	window->ViewportPixelWidth = viewport_pixel_width;
	window->ViewportPixelHeight = viewport_pixel_height;
	window->GlfwWindow = glfw_window;
	window->IsFullscreen = create_info_used.fullscreen;
	window->FramebufferMatchViewportSize = create_info_used.framebuffer_match_viewport_size;
	window->MinWidth = 0;
	window->MaxWidth = 0;
	window->MinHeight = 0;
	window->MaxHeight = 0;
	TuiMonitor cur_monitor = _GetCurrentMonitor(glfw_window);
	glfwGetWindowPos(glfw_window, &window->FullscreenLastWindowedPositionX, &window->FullscreenLastWindowedPositionY);
	window->IsFixedAspectRatio = TUI_FALSE;
	window->UserPointer = TUI_NULL;
	window->WindowMoveCallback = TUI_NULL;
	window->WindowFocusCallback = TUI_NULL;
	window->WindowIconifyCallback = TUI_NULL;
	window->WindowMaximizeCallback = TUI_NULL;
	window->WindowViewportResizeCallback = TUI_NULL;
	window->WindowContentScaleCallback = TUI_NULL;
	window->MouseButtonCallback = TUI_NULL;
	window->CursorMoveCallback = TUI_NULL;
	window->CursorEnterCallback = TUI_NULL;
	window->MouseScrollCallback = TUI_NULL;
	window->KeyboardKeyCallback = TUI_NULL;
	window->CharCallback = TUI_NULL;
	window->FileDropCallback = TUI_NULL;
	window->Title = tuiAllocate((strlen(title) + 1) * sizeof(char));
	strcpy(window->Title, title);
	glfwSetWindowUserPointer(glfw_window, window);
	glfwMakeContextCurrent(glfw_window);
	glfw_error = _GlfwErrorCheck(); // last error check after allocation of TuiWindow
	if (glfw_error != TUI_ERROR_NONE)
	{
		glfwDestroyWindow(glfw_window); //it was created, so now destroy it
		tuiFree(window);
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	TuiErrorCode error_code = tuiWindowCreate_Opengl33(window);
	if (error_code != TUI_ERROR_NONE)
	{
		glfwDestroyWindow(window->GlfwWindow);
		tuiFree(window);
		tuiDebugError(error_code, __func__);
		return TUI_NULL;
	}
	sWindowCount++;
	
	return window;
}

TuiWindowCreateInfo tuiWindowCreateInfo()
{
	TuiWindowCreateInfo info;
	info.resizable = TUI_FALSE;
	info.visible = TUI_TRUE;
	info.decorated = TUI_TRUE;
	info.focused = TUI_TRUE;
	info.topmost = TUI_FALSE;
	info.maximized = TUI_FALSE;
	info.center_cursor = TUI_FALSE;
	info.focus_on_show = TUI_TRUE;
	info.hidden = TUI_FALSE;
	info.fullscreen = TUI_FALSE;
	info.monitor = TUI_NULL;
	info.framebuffer_match_viewport_size = TUI_TRUE;
	info.unmatching_framebuffer_pixel_width = 0;
	info.unmatching_framebuffer_pixel_height = 0;
	return info;
}

void tuiWindowDestroy(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDestroy_Opengl33(window);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
	glfwDestroyWindow(window->GlfwWindow);
	_GlfwClearErrors();
	tuiFree(window->Title);
	tuiFree(window);
	sWindowCount--;
}

int tuiGetWindowCount()
{
	return sWindowCount;
}

void tuiWindowClearColor(TuiWindow window, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowClearColor_Opengl33(window, r, g, b, a);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowGetFramebufferPixelDimensions(TuiWindow window, int* width, int* height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (width != TUI_NULL)
	{
		*width = (int)window->FramebufferPixelWidth;
	}
	if (height != TUI_NULL)
	{
		*height = (int)window->FramebufferPixelHeight;
	}
}

int tuiWindowGetFramebufferPixelWidth(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return (int)window->FramebufferPixelWidth;
}

int tuiWindowGetFramebufferPixelHeight(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return (int)window->FramebufferPixelHeight;
}

void tuiWindowSetFramebufferPixelDimensions(TuiWindow window, int pixel_width, int pixel_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS, __func__);
		return;
	}


	if (window->FramebufferMatchViewportSize == TUI_TRUE && window->IsFullscreen == TUI_FALSE)
	{
		window->ViewportPixelWidth = pixel_width;
		window->ViewportPixelHeight = pixel_height;
		glfwSetWindowSize(window->GlfwWindow, pixel_width, pixel_height);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, pixel_width, pixel_height);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

TuiImage tuiWindowGetImage(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	size_t p_width = 0;
	size_t p_height = 0;
	uint8_t* pixel_data = TUI_NULL;
	TuiErrorCode error_code = tuiWindowGetPixels_Opengl33(window, &p_width, &p_height, &pixel_data);
	if (error_code != TUI_ERROR_NONE)
	{
		if (pixel_data != TUI_NULL)
		{
			tuiFree(pixel_data);
		}
		return TUI_NULL;
	}
	TuiImage image = _CreateImage(p_width, p_height, 4, pixel_data, TUI_FALSE);
	return image;
}

void tuiWindowWriteImage(TuiWindow window, TuiImage image)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (image == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_IMAGE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowGetPixels_Opengl33(window, &image->PixelWidth, &image->PixelHeight, &image->PixelData);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

uint8_t* tuiWindowGetPixels(TuiWindow window, int* pixel_width, int* pixel_height, uint8_t* fill_pixels)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	size_t o_width, o_height;
	uint8_t* pixels = fill_pixels;
	if (pixels == TUI_NULL)
	{
		pixels = (uint8_t*)tuiAllocate((size_t)pixel_width * (size_t)pixel_height);
	}
	TuiErrorCode error_code = tuiWindowGetPixels_Opengl33(window, &o_width, &o_height, &pixels);
	if (error_code != TUI_ERROR_NONE)
	{		
		if (fill_pixels == TUI_NULL)
		{
			tuiFree(pixels);
		}
		tuiDebugError(error_code, __func__);
		return TUI_NULL;
	}
	*pixel_width = (int)o_width;
	*pixel_height = (int)o_height;
	return pixels;
}

void tuiWindowDrawBatch(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiBatch batch)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
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

	TuiErrorCode error_code = tuiWindowDrawBatch_Opengl33(window, atlas, palette, batch, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawBatchTransformed(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiBatch batch, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
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

	TuiErrorCode error_code = tuiWindowDrawBatch_Opengl33(window, atlas, palette, batch, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawPanel(TuiWindow window, TuiPanel panel)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawPanel_Opengl33(window, panel, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawPanelTransformed(TuiWindow window, TuiPanel panel, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (panel == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawPanel_Opengl33(window, panel, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawTexture(TuiWindow window, TuiTexture texture)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (texture == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawTexture_Opengl33(window, texture, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawTextureTransformed(TuiWindow window, TuiTexture texture, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (texture == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawTexture_Opengl33(window, texture, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawAtlas(TuiWindow window, TuiAtlas atlas)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (atlas == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawAtlas_Opengl33(window, atlas, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawAtlasTransformed(TuiWindow window, TuiAtlas atlas, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (atlas == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawAtlas_Opengl33(window, atlas, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawWindow(TuiWindow window, TuiWindow subject_window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (subject_window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_SUBJECT_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawWindow_Opengl33(window, subject_window, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowDrawWindowTransformed(TuiWindow window, TuiWindow subject_window, int left_x, int right_x, int top_y, int bottom_y)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (subject_window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_SUBJECT_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowDrawWindow_Opengl33(window, subject_window, left_x, right_x, top_y, bottom_y);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
}

void tuiWindowFrame(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	TuiErrorCode error_code = tuiWindowRender_Opengl33(window);
	if (error_code != TUI_ERROR_NONE)
	{
		tuiDebugError(error_code, __func__);
		return;
	}
	glfwSwapBuffers(window->GlfwWindow);
	//glfwSwapBuffers(system->BaseWindow); // uncomment this to allow inspection with renderdoc
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	
}

void tuiWindowFrameInterval(TuiWindow window, int interval)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwMakeContextCurrent(window->GlfwWindow);
	glfwSwapInterval(interval);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiCursorMode tuiWindowGetCursorMode(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_CURSOR_MODE_INVALID;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_CURSOR_MODE_INVALID;
	}

	TuiCursorMode cursor_mode = (TuiCursorMode)glfwGetInputMode(window->GlfwWindow, GLFW_CURSOR);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_CURSOR_MODE_INVALID;
	}
	return cursor_mode;
}

void tuiWindowSetCursorMode(TuiWindow window, TuiCursorMode cursor_mode)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (tuiCursorModeIsValid(cursor_mode) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_CURSOR_MODE, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_CURSOR, (int)cursor_mode);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetStickyKeysEnabled(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int sticky_keys = glfwGetInputMode(window->GlfwWindow, GLFW_STICKY_KEYS);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (sticky_keys == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetStickyKeysEnabled(TuiWindow window, TuiBoolean sticky_keys_mode)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_STICKY_KEYS, (int)sticky_keys_mode);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetStickyMouseButtonsEnabled(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int sticky_mouse_buttons = glfwGetInputMode(window->GlfwWindow, GLFW_STICKY_MOUSE_BUTTONS);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (sticky_mouse_buttons == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetStickyMouseButtonsEnabled(TuiWindow window, TuiBoolean sticky_mouse_buttons)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_STICKY_MOUSE_BUTTONS, (int)sticky_mouse_buttons);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetLockKeyModsEnabled(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int lock_mods = glfwGetInputMode(window->GlfwWindow, GLFW_LOCK_KEY_MODS);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (lock_mods == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetLockKeyModsEnabled(TuiWindow window, TuiBoolean lock_mods)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_LOCK_KEY_MODS, (int)lock_mods);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetRawMouseMotionEnabled(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int raw_mouse_motion = glfwGetInputMode(window->GlfwWindow, GLFW_RAW_MOUSE_MOTION);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (raw_mouse_motion == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetRawMouseMotionEnabled(TuiWindow window, TuiBoolean raw_mouse_motion)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (glfwRawMouseMotionSupported() == GLFW_FALSE)
	{
		tuiDebugError(TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_RAW_MOUSE_MOTION, (int)raw_mouse_motion);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiButtonState tuiWindowGetKeyboardKey(TuiWindow window, TuiKeyboardKey key)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_BUTTON_INVALID;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_BUTTON_INVALID;
	}
	if (tuiKeyboardKeyIsValid(key) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_KEYBOARD_KEY, __func__);
		return TUI_BUTTON_INVALID;
	}
	
	TuiButtonState button_state = (TuiButtonState)glfwGetKey(window->GlfwWindow, key);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_BUTTON_INVALID;
	}
	return button_state;
}

TuiButtonState tuiWindowGetMouseButton(TuiWindow window, TuiMouseButton mouse_button)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_BUTTON_INVALID;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_BUTTON_INVALID;
	}
	if (tuiMouseButtonIsValid(mouse_button) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_MOUSE_BUTTON, __func__);
		return TUI_BUTTON_INVALID;
	}

	TuiButtonState button_state = (TuiButtonState)glfwGetMouseButton(window->GlfwWindow, mouse_button);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_BUTTON_INVALID;
	}
	return button_state;
}

void tuiWindowGetCursorPosition(TuiWindow window, double* x_position, double* y_position)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwGetCursorPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

double tuiWindowGetCursorXPosition(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0.0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0;
	}

	double x_position = 0.0;
	glfwGetCursorPos(window->GlfwWindow, &x_position, TUI_NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0;
	}
	return x_position;
}

double tuiWindowGetCursorYPosition(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0.0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0;
	}

	double y_position = 0.0;
	glfwGetCursorPos(window->GlfwWindow, TUI_NULL, &y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0;
	}
	return y_position;
}

void tuiWindowSetCursorPosition(TuiWindow window, double x_position, double y_position)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetCursorPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetTitle(TuiWindow window, const char* title)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (title == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_STRING, __func__);
		return;
	}

	if (title == TUI_NULL)
	{
		title = "";
	}

	window->Title = tuiReallocate(window->Title, strlen(title) * sizeof(char));
	strcpy(window->Title, title);
	glfwSetWindowTitle(window->GlfwWindow, title);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

const char* tuiWindowGetTitle(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	return window->Title;
}

void tuiWindowSetDefaultIcon(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (system->WindowIconsSupported == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, __func__);
		return;
	}

	glfwSetWindowIcon(window->GlfwWindow, 0, TUI_NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void _WindowSetIcon(TuiWindow window, int pixel_width, int pixel_height, const uint8_t* pxiels, const char* func_name)
{

	GLFWimage icon_images[3];

	unsigned char level1pixels[16 * 16 * 4];
	icon_images[0].width = 16;
	icon_images[0].height = 16;
	icon_images[0].pixels = _ResizeImageData(pxiels, pixel_width, pixel_height, 4, 16, 16, level1pixels, func_name);

	unsigned char level2pixels[32 * 32 * 4];
	icon_images[1].width = 32;
	icon_images[1].height = 32;
	icon_images[1].pixels = _ResizeImageData(pxiels, pixel_width, pixel_height, 4, 32, 32, level2pixels, func_name);

	unsigned char level3pixels[48 * 48 * 4];
	icon_images[2].width = 48;
	icon_images[2].height = 48;
	icon_images[2].pixels = _ResizeImageData(pxiels, pixel_width, pixel_height, 4, 48, 48, level3pixels, func_name);

	glfwSetWindowIcon(window->GlfwWindow, 3, icon_images);
}

void tuiWindowSetIconImage(TuiWindow window, TuiImage icon_image)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (icon_image == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_IMAGE, __func__);
		return;
	}
	if (icon_image->ChannelCount != 4)
	{
		tuiDebugError(TUI_ERROR_INVALID_CHANNEL_COUNT, __func__);
		return;
	}
	if (system->WindowIconsSupported == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, __func__);
		return;
	}

	_WindowSetIcon(window, icon_image->PixelWidth, icon_image->PixelHeight, icon_image->PixelData, __func__);

	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetIconRawPixels(TuiWindow window, int pixel_width, int pixel_height, const uint8_t* pxiels)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (pxiels == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PIXELS, __func__);
		return;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_PIXEL_DIMENSIONS, __func__);
		return;
	}
	if (system->WindowIconsSupported == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, __func__);
		return;
	}

	_WindowSetIcon(window, pixel_width, pixel_height, pxiels, __func__);

	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowGetPosition(TuiWindow window, int* x_position, int* y_position)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwGetWindowPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

int tuiWindowGetXPosition(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	int x_position = 0;
	glfwGetWindowPos(window->GlfwWindow, &x_position, TUI_NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0;
	}
	return x_position;
}

int tuiWindowGetYPosition(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	int y_position = 0;
	glfwGetWindowPos(window->GlfwWindow, TUI_NULL, &y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0;
	}
	return y_position;
}

void tuiWindowSetPosition(TuiWindow window, int x_position, int y_position)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetSizeLimits(TuiWindow window, int min_width, int min_height, int max_width, int max_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_width < 0 ||
		min_height < 0 ||
		max_width < 0 ||
		max_height < 0 ||
		((max_width != 0) && (max_width < min_width)) ||
		((max_height != 0) && max_height < min_height)
		)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinWidth = min_width;
	window->MinHeight = min_height;
	window->MaxWidth = max_width;
	window->MaxHeight = max_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMinSizeLimits(TuiWindow window, int min_width, int min_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_width < 0 || min_height < 0 || ((window->MaxWidth != 0) && min_width > window->MaxWidth) || ((window->MaxHeight != 0) && min_height > window->MaxHeight))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinWidth = min_width;
	window->MinHeight = min_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMaxSizeLimits(TuiWindow window, int max_width, int max_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (max_width < 0 || max_height < 0 || ((max_width != 0) && (max_width < window->MinWidth)) ||	((max_height != 0) && max_height < window->MinHeight))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MaxWidth = max_width;
	window->MaxHeight = max_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMinWidth(TuiWindow window, int min_width)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_width < 0 || ((window->MaxWidth != 0) && (window->MaxWidth < window->MinWidth)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinWidth = min_width;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMinHeight(TuiWindow window, int min_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_height < 0 || ((window->MaxHeight != 0) && (window->MaxHeight < min_height)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinHeight = min_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMaxWidth(TuiWindow window, int max_width)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (max_width < 0 || ((max_width != 0) && (max_width < window->MinWidth)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MaxWidth = max_width;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMaxHeight(TuiWindow window, int max_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (max_height < 0 || ((max_height != 0) && (max_height < window->MinHeight)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MaxHeight = max_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowGetSizeLimits(TuiWindow window, int* min_width, int* min_height, int* max_width, int* max_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (min_width != TUI_NULL)
	{
		*min_width = window->MinWidth;
	}
	if (min_height != TUI_NULL)
	{
		*min_height = window->MinHeight;
	}
	if (max_width != TUI_NULL)
	{
		*max_width = window->MaxWidth;
	}
	if (max_height != TUI_NULL)
	{
		*max_height = window->MaxHeight;
	}
}

int tuiWindowGetMinWidth(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MinWidth;
}

int tuiWindowGetMinHeight(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MinHeight;
}

int tuiWindowGetMaxWidth(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MaxWidth;
}

int tuiWindowGetMaxHeight(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MaxHeight;
}

TuiBoolean tuiWindowHasSizeLimits(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return _WindowHasSizeLimits(window);
}

TuiBoolean tuiWindowHasMinSizeLimits(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	if (window->MinWidth != 0 || window->MinHeight != 0)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowHasMaxSizeLimits(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	if (window->MaxWidth != 0 || window->MaxHeight != 0)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetFixedAspectRatio(TuiWindow window, int numerator, int denominator)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (numerator <= 0 || denominator <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_ASPECT_RATIO, __func__);
		return;
	}

	window->IsFixedAspectRatio = TUI_TRUE;
	glfwSetWindowAspectRatio(window->GlfwWindow, numerator, denominator);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowFixCurrentAspectRatio(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	window->IsFixedAspectRatio = TUI_TRUE;
	int greatest_common_factor = _GCF(window->ViewportPixelWidth, window->ViewportPixelHeight);
	glfwSetWindowAspectRatio(window->GlfwWindow, window->ViewportPixelWidth / greatest_common_factor, window->ViewportPixelHeight / greatest_common_factor);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowUnfixAspectRatio(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	
	window->IsFixedAspectRatio = TUI_FALSE;
	glfwSetWindowAspectRatio(window->GlfwWindow, GLFW_DONT_CARE, GLFW_DONT_CARE);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetAspectRatioIsFixed(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return window->IsFixedAspectRatio;
}

void tuiWindowGetAspectRatio(TuiWindow window, int* numerator, int* denominator)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	int greatest_common_factor = _GCF(window->ViewportPixelWidth, window->ViewportPixelHeight);
	if (numerator != TUI_NULL)
	{
		*numerator = window->ViewportPixelWidth / greatest_common_factor;
	}
	if (denominator != TUI_NULL)
	{
		*denominator = window->ViewportPixelHeight / greatest_common_factor;
	}
}

void tuiWindowGetContentScale(TuiWindow window, float* scale_wide, float* scale_tall)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwGetWindowContentScale(window->GlfwWindow, scale_wide, scale_tall);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

float tuiWindowGetContentScaleWide(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0.0f;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0f;
	}

	float scale_wide = 0.0f;
	glfwGetWindowContentScale(window->GlfwWindow, &scale_wide, TUI_NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0f;
	}
	return scale_wide;
}

float tuiWindowGetContentScaleTall(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0.0f;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0f;
	}

	float scale_tall = 0.0f;
	glfwGetWindowContentScale(window->GlfwWindow, TUI_NULL, &scale_tall);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0f;
	}
	return scale_tall;
}

void tuiWindowIconify(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwIconifyWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowRestore(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwRestoreWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}


TuiBoolean tuiWindowShouldClose(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int should_close = glfwWindowShouldClose(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (should_close == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetShouldClose(TuiWindow window, TuiBoolean should_close)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowShouldClose(window->GlfwWindow, should_close);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowMaximize(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwMaximizeWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowShow(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwShowWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowHide(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwHideWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowFocus(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwFocusWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowRequestAttention(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwRequestWindowAttention(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiMonitor tuiWindowGetMonitor(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	TuiMonitor monitor = _GetCurrentMonitor(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return monitor;
}

void tuiWindowSetFullscreenCurrentMonitor(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (window->IsFullscreen == TUI_TRUE)
	{
		return;
	}

	TuiMonitor monitor = _GetCurrentMonitor(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	glfwGetWindowPos(window->GlfwWindow, &window->FullscreenLastWindowedPositionX, &window->FullscreenLastWindowedPositionY);
	const GLFWvidmode* vid_mode = glfwGetVideoMode(monitor);
	window->IsFullscreen = TUI_TRUE;
	glfwSetWindowMonitor(window->GlfwWindow, monitor, 0, 0, vid_mode->width, vid_mode->height, vid_mode->refreshRate);
	glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	window->ViewportPixelWidth = vid_mode->width;
	window->ViewportPixelHeight = vid_mode->height;
	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, (size_t)vid_mode->width, (size_t)vid_mode->height);
		if (error_code != TUI_ERROR_NONE)
		{
			tuiDebugError(error_code, __func__);
			return;
		}
	}
}

void tuiWindowSetFullscreen(TuiWindow window, TuiMonitor monitor)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (monitor == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_MONITOR, __func__);
		return;
	}

	if (window->IsFullscreen == TUI_FALSE)
	{
		glfwGetWindowPos(window->GlfwWindow, &window->FullscreenLastWindowedPositionX, &window->FullscreenLastWindowedPositionY);
	}
	const GLFWvidmode* vid_mode = glfwGetVideoMode(monitor);
	window->IsFullscreen = TUI_TRUE;
	glfwSetWindowMonitor(window->GlfwWindow, monitor, 0, 0, vid_mode->width, vid_mode->height, vid_mode->refreshRate);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	window->ViewportPixelWidth = vid_mode->width;
	window->ViewportPixelHeight = vid_mode->height;
	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, (size_t)vid_mode->width, (size_t)vid_mode->height);
		if (error_code != TUI_ERROR_NONE)
		{
			tuiDebugError(error_code, __func__);
			return;
		}
	}
}

void tuiWindowSetWindowed(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (window->IsFullscreen == TUI_TRUE)
	{
		glfwSetWindowMonitor(window->GlfwWindow, TUI_NULL, window->FullscreenLastWindowedPositionX, window->FullscreenLastWindowedPositionY, window->FramebufferPixelWidth, window->FramebufferPixelHeight, GLFW_DONT_CARE);
		TuiErrorCode glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
			return;
		}
		window->IsFullscreen = TUI_FALSE;
		window->ViewportPixelWidth = window->FramebufferPixelWidth;
		window->ViewportPixelHeight = window->FramebufferPixelHeight;
	}
}

void tuiWindowSetWindowedViewportSize(TuiWindow window, int viewport_pixel_width, int viewport_pixel_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (viewport_pixel_width <= 0 || viewport_pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS, __func__);
		return;
	}

	if (window->IsFullscreen == TUI_TRUE)
	{
		window->IsFullscreen = TUI_FALSE;
		window->ViewportPixelWidth = viewport_pixel_width;
		window->ViewportPixelHeight = viewport_pixel_height;
		glfwSetWindowMonitor(window->GlfwWindow, TUI_NULL, window->FullscreenLastWindowedPositionX, window->FullscreenLastWindowedPositionY, viewport_pixel_width, viewport_pixel_height, GLFW_DONT_CARE);
		TuiErrorCode glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
			return;
		}
		if (window->FramebufferMatchViewportSize == TUI_TRUE)
		{
			TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, (size_t)viewport_pixel_width, (size_t)viewport_pixel_height);
			if (error_code != TUI_ERROR_NONE)
			{
				tuiDebugError(error_code, __func__);
				return;
			}
		}
	}
	else //(window->IsFullscreen == TUI_FALSE)
	{
		window->ViewportPixelWidth = viewport_pixel_width;
		window->ViewportPixelHeight = viewport_pixel_height;
		glfwSetWindowSize(window->GlfwWindow, viewport_pixel_width, viewport_pixel_height);
		TuiErrorCode glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
			return;
		}
		if (window->FramebufferMatchViewportSize == TUI_TRUE)
		{
			TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, (size_t)viewport_pixel_width, (size_t)viewport_pixel_height);
			if (error_code != TUI_ERROR_NONE)
			{
				tuiDebugError(error_code, __func__);
				return;
			}
		}
	}
}

int tuiWindowGetViewportPixelWidth(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->ViewportPixelWidth;
}

int tuiWindowGetViewportPixelHeight(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return 0;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->ViewportPixelHeight;
}

void tuiWindowGetViewportPixelDimensons(TuiWindow window, int* pixel_width, int* pixel_height)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (pixel_width != TUI_NULL)
	{
		*pixel_width = (int)window->ViewportPixelWidth;
	}
	if (pixel_height != TUI_NULL)
	{
		*pixel_height = (int)window->ViewportPixelHeight;
	}
}

void tuiWindowSetFramebufferMatchesViewportSize(TuiWindow window, TuiBoolean framebuffer_matches_viewport_size)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	window->FramebufferMatchViewportSize = framebuffer_matches_viewport_size;
	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		TuiErrorCode error_code = tuiWindowSetSize_Opengl33(window, window->ViewportPixelWidth, window->ViewportPixelHeight);
		if (error_code != TUI_ERROR_NONE)
		{
			tuiDebugError(error_code, __func__);
			return;
		}
	}
}

TuiBoolean tuiWindowGetFramebufferMatchesViewportSize(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return window->FramebufferMatchViewportSize;
}

TuiBoolean tuiWindowGetIsFullscreen(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return window->IsFullscreen;
}

TuiBoolean tuiWindowGetFocused(TuiWindow window)
{ 
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int focused = glfwGetWindowAttrib(window->GlfwWindow, GLFW_FOCUSED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (focused == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetIconified(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int iconified = glfwGetWindowAttrib(window->GlfwWindow, GLFW_ICONIFIED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (iconified == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetMaximized(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int maximized = glfwGetWindowAttrib(window->GlfwWindow, GLFW_MAXIMIZED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (maximized == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetMouseEntered(TuiWindow window)
{ 
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int mouse_entered = glfwGetWindowAttrib(window->GlfwWindow, GLFW_HOVERED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (mouse_entered == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetVisible(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int visible = glfwGetWindowAttrib(window->GlfwWindow, GLFW_VISIBLE);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (visible == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetResizable(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int resizable = glfwGetWindowAttrib(window->GlfwWindow, GLFW_RESIZABLE);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (resizable == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetResizable(TuiWindow window, TuiBoolean resizable)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_RESIZABLE, (int)resizable);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetDecorated(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int decorated = glfwGetWindowAttrib(window->GlfwWindow, GLFW_DECORATED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (decorated == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetDecorated(TuiWindow window, TuiBoolean decorated)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_DECORATED, (int)decorated);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetTopmost(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int topmost =glfwGetWindowAttrib(window->GlfwWindow, GLFW_FLOATING); //"topmost" is easier to understand than "floating"
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (topmost == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetTopmost(TuiWindow window, TuiBoolean topmost)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_FLOATING, (int)topmost);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetFocusOnShow(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int focus_on_show = glfwGetWindowAttrib(window->GlfwWindow, GLFW_FOCUS_ON_SHOW);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (focus_on_show == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetFocusOnShow(TuiWindow window, TuiBoolean focus_on_show)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_FOCUS_ON_SHOW, (int)focus_on_show);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetUserPointer(TuiWindow window, void* ptr)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	window->UserPointer = ptr; //use a member variable instead of the GLFWwindow user pointer, because that pointer contains a pointer to this TuiWindow for internal uses.
}

void* tuiWindowGetUserPointer(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	return window->UserPointer;
}

void tuiWindowSetCursor(TuiWindow window, TuiCursor cursor)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetCursor(window->GlfwWindow, cursor);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

tuiWindowMoveFunction tuiWindowSetMoveCallback(TuiWindow window, tuiWindowMoveFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowMoveFunction old_callback = window->WindowMoveCallback;
	window->WindowMoveCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetWindowPosCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetWindowPosCallback(window->GlfwWindow, glfwWindowPosCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiWindowCloseFunction tuiWindowSetCloseCallback(TuiWindow window, tuiWindowCloseFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowCloseFunction old_callback = window->WindowCloseCallback;
	window->WindowCloseCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetWindowCloseCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetWindowCloseCallback(window->GlfwWindow, glfwWindowCloseCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiWindowFocusFunction tuiWindowSetFocusCallback(TuiWindow window, tuiWindowFocusFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowFocusFunction old_callback = window->WindowFocusCallback;
	window->WindowFocusCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetWindowFocusCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetWindowFocusCallback(window->GlfwWindow, glfwWindowFocusCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiWindowIconifyFunction tuiWindowSetIconifyCallback(TuiWindow window, tuiWindowIconifyFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowIconifyFunction old_callback = window->WindowIconifyCallback;
	window->WindowIconifyCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetWindowIconifyCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetWindowIconifyCallback(window->GlfwWindow, glfwWindowIconifyCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiWindowMaximizeFunction tuiWindowSetMaximizeCallback(TuiWindow window, tuiWindowMaximizeFunction callback)
{ 
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowMaximizeFunction old_callback = window->WindowMaximizeCallback;
	window->WindowMaximizeCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetWindowMaximizeCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetWindowMaximizeCallback(window->GlfwWindow, glfwWindowMaximizeCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiWindowViewportResizeFunction tuiWindowSetViewportResizeCallback(TuiWindow window, tuiWindowViewportResizeFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowViewportResizeFunction old_callback = window->WindowViewportResizeCallback;
	window->WindowViewportResizeCallback = callback;
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiWindowContentScaleFunction tuiWindowSetContentScaleCallback(TuiWindow window, tuiWindowContentScaleFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiWindowContentScaleFunction old_callback = window->WindowContentScaleCallback;
	window->WindowContentScaleCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetWindowContentScaleCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetWindowContentScaleCallback(window->GlfwWindow, glfwWindowContentScaleCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiKeyboardKeyboardKeyFunction tuiWindowSetKeyboardKeyCallback(TuiWindow window, tuiKeyboardKeyboardKeyFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiKeyboardKeyboardKeyFunction old_callback = window->KeyboardKeyCallback;
	window->KeyboardKeyCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetKeyCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetKeyCallback(window->GlfwWindow, glfwKeyCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiCharFunction tuiWindowSetCharCallback(TuiWindow window, tuiCharFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiCharFunction old_callback = window->CharCallback;
	window->CharCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetCharCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetCharCallback(window->GlfwWindow, glfwCharCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiMouseButtonFunction tuiWindowSetMouseButtonCallback(TuiWindow window, tuiMouseButtonFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiMouseButtonFunction old_callback = window->MouseButtonCallback;
	window->MouseButtonCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetMouseButtonCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetMouseButtonCallback(window->GlfwWindow, glfwMouseButtonCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiCursorMoveFunction tuiWindowSetCursorMoveCallback(TuiWindow window, tuiCursorMoveFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiCursorMoveFunction old_callback = window->CursorMoveCallback;
	window->CursorMoveCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetCursorPosCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetCursorPosCallback(window->GlfwWindow, glfwCursorMoveCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiCursorEnterFunction tuiWindowSetCursorEnterCallback(TuiWindow window, tuiCursorEnterFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiCursorEnterFunction old_callback = window->CursorEnterCallback;
	window->CursorEnterCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetCursorEnterCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetCursorEnterCallback(window->GlfwWindow, glfwCursorEnterCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiMouseScrollFunction tuiWindowSetMouseScrollCallback(TuiWindow window, tuiMouseScrollFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiMouseScrollFunction old_callback = window->MouseScrollCallback;
	window->MouseScrollCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetScrollCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetScrollCallback(window->GlfwWindow, glfwScrollCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}

tuiFileDropFunction tuiWindowSetFileDropCallback(TuiWindow window, tuiFileDropFunction callback)
{
	TuiSystem system = tui_get_system();
	if (system == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_NULL;
	}
	if (window == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_NULL;
	}

	tuiFileDropFunction old_callback = window->FileDropCallback;
	window->FileDropCallback = callback;
	if (callback == TUI_NULL)
	{
		glfwSetDropCallback(window->GlfwWindow, TUI_NULL);
	}
	else
	{
		glfwSetDropCallback(window->GlfwWindow, glfwDropCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_NULL;
	}
	return old_callback;
}
