
#include <TUIC/tuic.h>

#include <stdio.h>

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

int main()
{
    int window_width = 500;
    int window_height = 500;

    /* Initialize TUIC. */
    TuiBoolean multi_window = TUI_FALSE;
    TuiBoolean initialization_successful = tuiInit(multi_window);
    if (initialization_successful == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Check if window icons are supported on this platform. */
    if (tuiWindowIconsSupported() == TUI_FALSE)
    {
        printf("Window icons are not supported on this platform.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Load the custom window icon image. */
    TuiImage window_icon_image = tuiImageCreatePNG("sushi.png");

    /* Create the window. */
    const char* window_title = "Example 10";
    TuiWindow window = tuiWindowCreate(window_width, window_height, window_title, TUI_NULL); 

    /* Set the window icon. */
    tuiWindowSetIconImage(window, window_icon_image);

    /* Destroy the window icon image. */
    tuiImageDestroy(window_icon_image);
    window_icon_image = TUI_NULL;

    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback functions

        tuiWindowFrame(window); //swap the window buffers
    }

    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window); //The instance must always be created first and destroyed last.
    window = TUI_NULL;

    tuiTerminate();
    return 0;
}
