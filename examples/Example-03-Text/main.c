
#include <TUIC/tuic.h>

#include <stdio.h>
#include <string.h>

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

const size_t kTilesWide = 50;
const size_t kTilesTall = 50;
const size_t kTilePixelWidth = 8;
const size_t kTilePixelHeight = 8;
static size_t sMaxTextSize = 0;
static char* sText;
static size_t sTextSize;
static TuiWindow sWindow;
static TuiBatch sBatch;
static TuiPalette sPalette;
static TuiAtlas sAtlas;

void update_batch()
{
    tuiBatchClear(sBatch);
    uint8_t foreground_color = 15;
    uint8_t background_color = 0;
    uint8_t colors_byte = tuiClassicColorCombine(foreground_color, background_color);
    for (size_t char_i = 0; char_i < sTextSize; char_i++)
    {
        int tile_x = char_i % kTilesWide;
        int tile_y = char_i / kTilesWide;
        tuiBatchSetTile_G8_C4_SPARSE(sBatch, tile_x, tile_y, sText[char_i], colors_byte);
    }
    tuiWindowClearColor(sWindow, 0, 0, 0, 255);
    tuiWindowDrawBatch(sWindow, sAtlas, sPalette, sBatch);
}

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState button_state, TuiKeyboardMod mod)
{
    TuiBoolean ctrl_mod = tuiKeyboardModHasMod(mod, TUI_MOD_CONTROL);
    if (key == TUIK_C && ctrl_mod == TUI_TRUE && button_state == TUI_BUTTON_PRESS)
    {
        sText[sTextSize] = '\0';
        tuiSetClipboardString(sText);
    }
    else if (key == TUIK_V && ctrl_mod == TUI_TRUE && button_state == TUI_BUTTON_PRESS)
    {
        const char* clipboard_string = tuiGetClipboardString();
        size_t new_text_size = strlen(clipboard_string);
        if (new_text_size > sMaxTextSize)
        {
            new_text_size = sMaxTextSize;
        }
        strncpy(sText, clipboard_string, new_text_size);
        sTextSize = new_text_size;
        update_batch();
    }
    else if (key == TUIK_X && ctrl_mod == TUI_TRUE && button_state == TUI_BUTTON_PRESS)
    {
        sText[sTextSize] = '\0';
        tuiSetClipboardString(sText);
        sTextSize = 0;
        update_batch();
    }
    else if (key == TUIK_BACKSPACE && (button_state == TUI_BUTTON_PRESS || button_state == TUI_BUTTON_REPEAT))
    {
        sTextSize--;
        update_batch();
    }
    else if (key == TUIK_DELETE && button_state == TUI_BUTTON_PRESS)
    {
        sTextSize = 0;
        update_batch();
    }
}

void char_callback(TuiWindow window, unsigned int codepoint)
{
    if (codepoint < 256 && codepoint != 0 && sTextSize != sMaxTextSize)
    {
        sText[sTextSize++] = (unsigned char)codepoint;
        update_batch();
    }
}

int main()
{
    int window_width = kTilesWide * kTilePixelWidth;
    int window_height = kTilesTall * kTilePixelHeight;
    sMaxTextSize = kTilesWide * kTilesTall;
    sText = tuiAllocate(sMaxTextSize);

    /* Initialize TUIC. */
    TuiBoolean initialization_successful = tuiInit();
    if (initialization_successful == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Load the atlas image */
    const char* atlas_image_name = "cp_8x8_rgb_fg_green.png";
    TuiImage atlas_image = tuiImageCreatePNG(atlas_image_name);
    if (atlas_image == TUI_NULL)
    {
        printf("Issue loading image file. Make sure that it was moved from the content folder to a location the executable can read. You need to do this manually.\n");
        tuiTerminate();
        return -1;
    }

    /* Create the atlas */
    TuiBlendMode blend_mode = TUI_BLEND_FG_GREEN;
    sAtlas = tuiAtlasCreateCodepageImage(atlas_image, blend_mode);
    tuiImageDestroy(atlas_image);
    atlas_image = TUI_NULL;

    /* Create the palette */
    int palette_color_count = 16;
    sPalette = tuiPaletteCreateXterm(palette_color_count);

    /* Create the batch */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_SPARSE;
    sBatch = tuiBatchCreateSparse(detail_mode, kTilesTall, kTilesWide, TUI_FALSE, 0);

    /* Create the window. */
    const char* window_title = "Example 3";
    sWindow = tuiWindowCreate(window_width, window_height, window_title, TUI_NULL);

    /* Render initial clear color to window. */
    tuiWindowClearColor(sWindow, 0, 0, 0, 255); //black

    /* Set the window callbacks. */
    tuiWindowSetKeyboardKeyCallback(sWindow, key_callback);
    tuiWindowSetCharCallback(sWindow, char_callback);

    /* Print prompt to console. */
    printf("Type to enter text. Press Ctrl+C to copy the text to the clipboard. Press Ctrl+V to paste clipboard text to the window. Press Ctrl+X to cut the text from the window. Press delete to delete all text in the window.\n");

    //Render loop
    while (tuiWindowShouldClose(sWindow) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback function.
       
        tuiWindowFrame(sWindow); //draw the next frame from the window framebuffer
    }


    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(sWindow);
    sWindow = TUI_NULL;
    tuiPaletteDestroy(sPalette);
    sPalette = TUI_NULL;
    tuiAtlasDestroy(sAtlas);
    sAtlas = TUI_NULL;
    tuiBatchDestroy(sBatch);
    sBatch = TUI_NULL;

    /* Free the text array */
    tuiFree(sText);

    tuiTerminate();
    return 0;
}
