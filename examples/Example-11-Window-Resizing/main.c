
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

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState button_state, TuiKeyboardMod mod)
{
    if (key == TUIK_A && button_state == TUI_BUTTON_PRESS)
    {
        if(tuiWindowGetAspectRatioIsFixed(window) == TUI_FALSE)
        {
            tuiWindowFixCurrentAspectRatio(window);
            int aspect_numerator = 0;
            int aspect_denominator = 0;
            tuiWindowGetAspectRatio(window, &aspect_numerator, &aspect_denominator);
            printf("Aspect ratio fixed at ( %d/%d ).\n", aspect_numerator, aspect_denominator);
        }
        else
        {
            tuiWindowUnfixAspectRatio(window);
            printf("Aspect ratio is unfixed.\n");
        }
    }
    if (key == TUIK_S && button_state == TUI_BUTTON_PRESS)
    {
        if (tuiWindowHasMinSizeLimits(window) == TUI_TRUE)
        {
            tuiWindowSetMinSizeLimits(window, 0, 0);
            printf("Min size limits removed.\n");
        }
        else
        {
            int width = tuiWindowGetFramebufferPixelWidth(window);
            int height = tuiWindowGetFramebufferPixelHeight(window);
            tuiWindowSetMinSizeLimits(window, width, height);
            printf("Min size limits set to ( %d, %d ).\n", width, height);
        }
    }
    if (key == TUIK_D && button_state == TUI_BUTTON_PRESS)
    {
        if (tuiWindowHasMaxSizeLimits(window) == TUI_TRUE)
        {
            tuiWindowSetMaxSizeLimits(window, 0, 0);
            printf("Max size limits removed.\n");
        }
        else
        {
            int width = tuiWindowGetFramebufferPixelWidth(window);
            int height = tuiWindowGetFramebufferPixelHeight(window);
            tuiWindowSetMaxSizeLimits(window, width, height);
            printf("Max size limits set to ( %d, %d ).\n", width, height);
        }
    }
}

typedef struct WindowUserPointer
{
    TuiWindow window;
    TuiBatch batch;
    TuiAtlas atlas;
    TuiPalette palette;
} WindowUserPointer;

const int kWindowWidth = 640;
const int kWindowHeight = 640;
const int kTilePixelWidth = 8;
const int kTilePixelHeight = 8;
const int kTileSizeMultiplier = 4;

void window_resize_callback(TuiWindow window, int pixel_width, int pixel_height)
{
    printf("Window resize: ( x = %d, y = %d )\n", pixel_width, pixel_height);

    WindowUserPointer* window_user_pointer = (WindowUserPointer*)tuiWindowGetUserPointer(window);

    //get what the tiles wide and tall would be at the new size
    int new_tiles_wide = pixel_width / (kTilePixelWidth * kTileSizeMultiplier);
    int new_tiles_tall = pixel_height / (kTilePixelHeight * kTileSizeMultiplier);
    //min should be 1 to avoid 0 size batch dimensions (causes error)
    if (new_tiles_wide == 0)
    {
        new_tiles_wide = 1;
    }
    if (new_tiles_tall == 0)
    {
        new_tiles_tall = 1;
    }
    if (new_tiles_wide != tuiBatchGetTilesWide(window_user_pointer->batch) || new_tiles_tall != tuiBatchGetTilesTall(window_user_pointer->batch)) //if the new size is different than the previous batch size...
    {
        TuiBoolean reserve_leftover_batch_space = TUI_TRUE; //reserve the leftover space if less space is needed for the new size. This can lower allocations/increase performance.
        tuiBatchSetTileDimensions(window_user_pointer->batch, new_tiles_wide, new_tiles_tall, reserve_leftover_batch_space);
        for (int x = 0; x < new_tiles_wide; x++)
        {
            for (int y = 0; y < new_tiles_tall; y++)
            {
                int color = tuiClassicColorCombine(x % 256, y % 256);
                tuiBatchSetTile_G8_C4_FULL(window_user_pointer->batch, x, y, (x + y) % 256, color);
            }
        }
    }

    int extra_pixels_wide = pixel_width % (kTilePixelWidth * kTileSizeMultiplier);
    int extra_pixels_tall = pixel_height % (kTilePixelHeight * kTileSizeMultiplier);
    tuiWindowClearColor(window, 255, 255, 255, 255); //white clear color
    tuiWindowDrawBatchTransformed(window,
        window_user_pointer->atlas,
        window_user_pointer->palette,
        window_user_pointer->batch,
        0,
        pixel_width - extra_pixels_wide,
        0,
        pixel_height - extra_pixels_tall
    );
    tuiWindowFrame(window);
}

int main()
{
    int tiles_wide = kWindowWidth / (kTilePixelWidth * kTileSizeMultiplier);
    int tiles_tall = kWindowHeight / (kTilePixelHeight * kTileSizeMultiplier);
    int extra_pixels_wide = kWindowWidth % (kTilePixelWidth * kTileSizeMultiplier);
    int extra_pixels_tall = kWindowHeight % (kTilePixelHeight * kTileSizeMultiplier);

    /* Initialize the user ptr. */
    WindowUserPointer window_user_pointer;

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

    /* Create the Atlas. */
    TuiBlendMode blend_mode = TUI_BLEND_FG_GREEN;
    TuiAtlas atlas = tuiAtlasCreateCodepageImage(atlas_image, blend_mode);
    tuiImageDestroy(atlas_image);
    atlas_image = TUI_NULL;
    window_user_pointer.atlas = atlas;

    /* Create the palette. */
    int palette_color_count = 16;
    TuiPalette palette = tuiPaletteCreateXterm(palette_color_count);
    window_user_pointer.palette = palette;

    /* Create the batch. */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_FULL; // same as (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_FULL)
    TuiBatch batch = tuiBatchCreateFull(detail_mode, tiles_wide, tiles_tall, 0);
    window_user_pointer.batch = batch;

    /* Set the batch data. */
    for (int x = 0; x < tiles_wide; x++)
    {
        for (int y = 0; y < tiles_tall; y++)
        {
            int color = tuiClassicColorCombine(x % 256, y % 256);
            tuiBatchSetTile_G8_C4_FULL(batch, x, y, (x + y) % 256, color);
        }
    }

    /* Create the window. */
    TuiWindowCreateInfo window_create_info = tuiWindowCreateInfo();
    window_create_info.resizable = TUI_TRUE;
    const char* window_title = "Example 11";
    TuiWindow window = tuiWindowCreate(kWindowWidth, kWindowHeight, window_title, &window_create_info);
    window_user_pointer.window = window;

    /* Render the initial batch to the window. */
    tuiWindowClearColor(window, 255, 255, 255, 255); //white clear color
    tuiWindowDrawBatchTransformed(window,
        atlas,
        palette,
        batch,
        0,
        kWindowWidth - extra_pixels_wide,
        0,
        kWindowHeight - extra_pixels_tall
    );

    /* Set the window callbacks. */
    tuiWindowSetKeyboardKeyCallback(window, key_callback);
    tuiWindowSetViewportResizeCallback(window, window_resize_callback);

    /* Set the window user ptr. */
    tuiWindowSetUserPointer(window, &window_user_pointer);

    /* Print prompt to console. */
    printf("Press A to fix or unfix the aspect ratio. Press S to set the minimum size limits to the current size or remove the minimum size limits. Press D to set the maximum size limits as the current size or remove the maximum size limits. Resize the window by dragging the edges. The rendered tile dimensions will update dynamically based on the window size. Extra space will be left as white pixels. \n");

    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback function.

        tuiWindowFrame(window);
    }

    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window);
    window = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    /* Termiate the TUIC system. */
    tuiTerminate();

    return 0;
}
