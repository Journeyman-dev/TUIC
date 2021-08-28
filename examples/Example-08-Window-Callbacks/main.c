
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

void window_move_callback(TuiWindow window, int x_position, int y_position)
{
    printf("Window move: ( x = %d, y = %d )\n", x_position, y_position);
}

void window_close_callback(TuiWindow window)
{
    printf("Window close.\n");
}

void window_focus_callback(TuiWindow window, TuiBoolean focused)
{
    printf("Window focus: focused = %d\n", focused);
}

void window_iconify_callback(TuiWindow window, TuiBoolean iconified)
{
    printf("Window iconify: iconified = %d\n", iconified);
}

void window_maximize_callback(TuiWindow window, TuiBoolean maximized)
{
    printf("Window maximize: maximized = %d\n", maximized);
}

void window_resize_callback(TuiWindow window, int pixel_width, int pixel_height)
{
    printf("Window resize: ( x = %d, y = %d )\n", pixel_width, pixel_height);
}

void window_content_scale_callback(TuiWindow window, float scale_wide, float scale_tall)
{
    printf("Windos content scale: ( scale_wide = %f, scale_tall = %f )\n", scale_wide, scale_tall);
}

void mouse_button_callback(TuiWindow window, TuiMouseButton mouse_button, TuiButtonState button_state, TuiKeyboardMod mod)
{
    printf("Mouse button: button = %s state = %s shift = %d control = %d alt = %d super = %d caps = %d num = %d\n",
        tuiMouseButtonToString(mouse_button),
        tuiButtonStateToString(button_state),
        tuiKeyboardModHasMod(mod, TUI_MOD_SHIFT),
        tuiKeyboardModHasMod(mod, TUI_MOD_CONTROL),
        tuiKeyboardModHasMod(mod, TUI_MOD_ALT),
        tuiKeyboardModHasMod(mod, TUI_MOD_SUPER),
        tuiKeyboardModHasMod(mod, TUI_MOD_CAPS_LOCK),
        tuiKeyboardModHasMod(mod, TUI_MOD_NUM_LOCK)
    );
}

void cursor_move_callback(TuiWindow window, double x_position, double y_position)
{
    printf("Cursor move: ( x = %f, y = %f )\n", x_position, y_position);
}

void cursor_enter_callback(TuiWindow window, TuiBoolean entered)
{
    printf("Cursor enter: entered = %d\n", entered);
}

void mouse_scroll_callback(TuiWindow window, double x_translate, double y_translate)
{
    printf("Mouse scroll: ( x = %f, y = %f )\n", x_translate, y_translate);
}

void keyboard_key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState button_state, TuiKeyboardMod mod)
{
    printf("Keyboard key: key = %s scancode = %d state = %s shift = %d control = %d alt = %d super = %d caps = %d num = %d\n",
        tuiKeyboardKeyToString(key),
        scancode,
        tuiButtonStateToString(button_state),
        tuiKeyboardModHasMod(mod, TUI_MOD_SHIFT),
        tuiKeyboardModHasMod(mod, TUI_MOD_CONTROL),
        tuiKeyboardModHasMod(mod, TUI_MOD_ALT),
        tuiKeyboardModHasMod(mod, TUI_MOD_SUPER),
        tuiKeyboardModHasMod(mod, TUI_MOD_CAPS_LOCK),
        tuiKeyboardModHasMod(mod, TUI_MOD_NUM_LOCK)
    );
}

void char_callback(TuiWindow window, unsigned int codepoint)
{
    printf("Char: codepoint = %d (%c)\n", codepoint, (char)codepoint);
}

void file_drop_callback(TuiWindow window, int path_count, const char* paths[])
{
    printf("File drop: count = %d path0 = %s\n", path_count, paths[0]);
}

void monitor_callback(TuiMonitor monitor, TuiBoolean connected)
{
    printf("Monitor: name = %s connected = %d\n", (connected == TUI_TRUE) ? tuiMonitorGetName(monitor) : "(null)", connected);
}

int main()
{
    int window_width = 500;
    int window_height = 500;

    /* Initialize TUIC. */
    TuiBoolean initialization_successful = tuiInit();
    if (initialization_successful == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Create the window. */
    TuiWindowCreateInfo window_create_info = tuiWindowCreateInfo();
    window_create_info.resizable = TUI_TRUE;
    const char* window_title = "Example 8";
    TuiWindow window = tuiWindowCreate(window_width, window_height, window_title, &window_create_info);

    /* Set all of the custom callbacks. */
    tuiWindowSetMoveCallback(window, window_move_callback);
    tuiWindowSetCloseCallback(window, window_close_callback);
    tuiWindowSetFocusCallback(window, window_focus_callback);
    tuiWindowSetIconifyCallback(window, window_iconify_callback);
    tuiWindowSetMaximizeCallback(window, window_maximize_callback);
    tuiWindowSetViewportResizeCallback(window, window_resize_callback);
    tuiWindowSetContentScaleCallback(window, window_content_scale_callback);
    tuiWindowSetMouseButtonCallback(window, mouse_button_callback);
    tuiWindowSetCursorMoveCallback(window, cursor_move_callback);
    tuiWindowSetCursorEnterCallback(window, cursor_enter_callback);
    tuiWindowSetMouseScrollCallback(window, mouse_scroll_callback);
    tuiWindowSetKeyboardKeyCallback(window, keyboard_key_callback);
    tuiWindowSetCharCallback(window, char_callback);
    tuiWindowSetFileDropCallback(window, file_drop_callback);
    tuiSetMonitorConnectedCallback(monitor_callback);

    printf("Try the following to see the callback messages:\n"
        " * move your mouse inside the window\n"
        " * move mouse in and out of the window area\n"
        " * click and hold a mouse button inside the window and drag your mouse outside (external mouse position capture)\n"
        " * resize the window by dragging the edges\n"
        " * click outside the window to lose focus, and click inside to gain it again\n"
        " * minimize the window then restore it\n"
        " * maximize the window then restore it\n"
        " * move the window between monitors with different DPI to see the content scale change\n"
        " * press and release mouse buttons\n"
        " * scroll your scroll wheel\n"
        " * press keys on your keyboard\n"
        " * drag and drop files into the window area\n"
        " * plug and unplug monitors and joysticks/gamepads\n"
    );

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
