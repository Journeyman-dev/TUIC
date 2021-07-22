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

TuiBoolean tuiInit(TuiBoolean multi_window)
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
	sSystem->MultiWindow = multi_window;
	sSystem->BaseWindow = NULL;
	sSystem->BaseWindowClaimed = TUI_FALSE;
	sSystem->WindowIconsSupported = TUI_FALSE;
	sSystem->MonitorConnectedCallback = NULL;
	sSystem->ApiData = NULL;

	int glfw_version_major = 0;
	int glfw_version_minor = 0;

	glfwGetVersion(&glfw_version_major, &glfw_version_minor, NULL);
	if (glfw_version_major != 3 && glfw_version_minor != 3)
	{
		tuiDebugError(TUI_ERROR_GLFW_INVALID_VERSION, __func__);
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
	if (sSystem->BaseWindow == NULL)
	{
		tuiFree(sSystem);
		sSystem = NULL;
		glfwTerminate();
		GLFW_CLEAR_ERRORS()
			return TUI_FALSE;
	}
	GLFW_CLEAR_ERRORS()
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
	tuiSystemCreate_Opengl33();
	GLFW_CLEAR_ERRORS()
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
		return;
	}
	TuiBoolean failed = TUI_FALSE;
	if (tuiGetWindowCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_WINDOW, __func__);
		failed = TUI_TRUE;
	}
	if (tuiGetCursorCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_CURSOR, __func__);
		failed = TUI_TRUE;
	}
	if (tuiGetAtlasCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_ATLAS, __func__);
		failed = TUI_TRUE;
	}
	if (tuiGetPanelCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_PANEL, __func__);
		failed = TUI_TRUE;
	}
	if (tuiGetPaletteCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_PALETTE, __func__);
		failed = TUI_TRUE;
	}
	if (tuiGetTextureCount() != 0)
	{
		tuiDebugError(TUI_ERROR_DANGLING_TEXTURE, __func__);
		failed = TUI_TRUE;
	}
	if (failed == TUI_TRUE)
	{
		return;
	}


	tuiSystemDestroy_Opengl33();
	glfwDestroyWindow(sSystem->BaseWindow);
	tuiFree(sSystem);
	GLFW_CLEAR_ERRORS()
	glfwTerminate();
}

TuiBoolean tuiMultiWindowDesktop()
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	return sSystem->MultiWindow;
}

TuiBoolean tuiRawMouseMotionSupported()
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	int supported = glfwRawMouseMotionSupported();
	GLFW_CHECK_ERROR_RETURN(TUI_FALSE)
	if (supported == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiVulkanSupported()
{
	if (sSystem == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	int supported = glfwVulkanSupported();
	GLFW_CHECK_ERROR_RETURN(TUI_FALSE)
	if (supported == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}