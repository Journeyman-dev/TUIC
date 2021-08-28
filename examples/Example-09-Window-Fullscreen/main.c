
#include <TUIC/tuic.h>

#include <stdio.h>

const int windowed_window_width = 500;
const int windowed_window_height = 500;

void TuiMessageCallback(TuiErrorCode error_code, const char* msg)
{
    if (error_code == TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC)
    {
        printf("%s : %s backend message: %s\n", tuiErrorCodeToString(error_code), tuiErrorCodeGetDescription(error_code), msg);
    }
    else
    {
        printf("%s : %s location: %s\n", tuiErrorCodeToString(error_code), tuiErrorCodeGetDescription(error_code), msg);
    }
}

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState button_state, TuiKeyboardMod mod)
{
    if (key == TUIK_F && button_state == TUI_BUTTON_PRESS)
    {
        if (tuiWindowGetIsFullscreen(window))
        {
            tuiWindowSetWindowedViewportSize(window, windowed_window_width, windowed_window_height);
            printf("Window is now windowed!\n");
        }
        else
        {
            TuiMonitor window_monitor = tuiWindowGetMonitor(window);
            tuiWindowSetFullscreenCurrentMonitor(window);
            printf("Window is now fullscreen in monitor: \"%s\"! %d %d \n", tuiMonitorGetName(window_monitor), tuiWindowGetFramebufferPixelWidth(window), tuiWindowGetFramebufferPixelHeight(window));
        }
    }
}

int main()
{
    /* Initialize TUIC. */
    TuiBoolean initialization_successful = tuiInit();
    if (initialization_successful == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Load the custom window icon image. */
    TuiImage window_icon_image = tuiImageCreatePNG("sushi.png");

    /* Create the window. */
    const char* window_title = "Example 9";
    TuiWindow window = tuiWindowCreate(windowed_window_width, windowed_window_height, window_title, TUI_NULL);

    /* Set the key callback. */
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    /* Print prompt to console. */
    printf("Press F to swap between windowed and fullscreen mode.\n");

    printf("%d\n", tuiWindowGetFramebufferMatchesViewportSize(window));
    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback functions
       
        if (tuiWindowGetIsFullscreen(window))
        {
            tuiWindowClearColor(window, 255, 0, 0, 255); //red clear color
        }
        else
        {
            tuiWindowClearColor(window, 0, 0, 255, 255); //blue clear color
        }

        tuiWindowFrame(window); //swap the window buffers
    }

    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window); //The instance must always be created first and destroyed last.
    window = TUI_NULL;

    tuiTerminate();
    return 0;
}
