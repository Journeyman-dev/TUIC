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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <TUIC/desktop_callback.h>
#include "glfw_error_check.h"
#include "objects.h"
#include "opengl33.h"

static TuiSystem sSystem;

TuiSystem tui_get_system()
{
	return sSystem;
}

TuiBoolean tuiInit()
{
	if (sSystem != NULL)
	{
		tuiDebugError(TUI_ERROR_ALREADY_INITIALIZED, __func__);
		return TUI_FALSE;
	}

	int initialized = glfwInit();

	if (initialized != GLFW_TRUE)
	{
		return TUI_FALSE;
	}

	sSystem = tuiAllocate(sizeof(TuiSystem_s));
	sSystem->BaseWindow = NULL;
	sSystem->WindowIconsSupported = TUI_FALSE;
	sSystem->MonitorConnectedCallback = NULL;
	sSystem->ApiData = NULL;

	int glfw_version_major = 0;
	int glfw_version_minor = 0;

	glfwGetVersion(&glfw_version_major, &glfw_version_minor, NULL);
	if (glfw_version_major != 3 && glfw_version_minor != 3)
	{
		tuiDebugError(TUI_ERROR_INVALID_GLFW_LIBRARY_VERSION, __func__);
		return TUI_FALSE;
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	sSystem->BaseWindow = glfwCreateWindow(1, 1, "", NULL, NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		tuiFree(sSystem);
		sSystem = NULL;
		glfwTerminate();
		return TUI_FALSE;
	}
	if (sSystem->BaseWindow == NULL)
	{
		tuiFree(sSystem);
		sSystem = NULL;
		glfwTerminate();
		return TUI_FALSE;
	}
	unsigned char image_pixels[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //we need to test if icons are supported now so tuiWindowIconsSupported function can work later
	GLFWimage test_icon_image; //this is because GLFW does not have a function for this purpose, so we need to be creative
	test_icon_image.width = 2;
	test_icon_image.height = 2;
	test_icon_image.pixels = image_pixels;
	glfwSetWindowIcon(sSystem->BaseWindow, 1, &test_icon_image); // try setting a dummy icon
	if (glfwGetError(NULL) == GLFW_NO_ERROR) //if it was set successfully...
	{
		sSystem->WindowIconsSupported = TUI_TRUE; //icons are supported on this platform.
		glfwSetWindowIcon(sSystem->BaseWindow, 0, NULL); //set the icon back to default.
	}
	else
	{
		_GlfwClearErrors();
	}
	tuiSystemCreate_Opengl33();
	
	return TUI_TRUE;
}

TuiBoolean tuiIsActive()
{
	return sSystem != NULL;
}

void tuiTerminate()
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		
	}
	if (tuiGetWindowCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_WINDOW, __func__);
		return;
	}
	if (tuiGetCursorCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_CURSOR, __func__);
		return;
	}
	if (tuiGetAtlasCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_ATLAS, __func__);
		return;
	}
	if (tuiGetPanelCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_PANEL, __func__);
		return;
	}
	if (tuiGetPaletteCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_PALETTE, __func__);
		return;
	}
	if (tuiGetTextureCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_TEXTURE, __func__);
		return;
	}

	tuiSystemDestroy_Opengl33();
	glfwDestroyWindow(sSystem->BaseWindow);
	tuiFree(sSystem);
	_GlfwClearErrors();
	glfwTerminate();
}

TuiBoolean tuiRawMouseMotionSupported()
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	int supported = glfwRawMouseMotionSupported();
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (supported == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

const char* tuGetClipboardString()
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}

	const char* str = glfwGetClipboardString(sSystem->BaseWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return str;
}

void tuiSetClipboardString(const char* string)
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	if (string == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_STRING, __func__);
		return;
	}

	glfwSetClipboardString(sSystem->BaseWindow, string);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}