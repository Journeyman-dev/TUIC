
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
    int tiles_wide = 50;
    int tiles_tall = 50;
    int glyph_pixel_dimensions = 8;
    int size_multiplier = 2;
    int window_width = tiles_wide * glyph_pixel_dimensions * size_multiplier;
    int window_height = tiles_tall * glyph_pixel_dimensions * size_multiplier;

    if (tuiInit() == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Create the window create info */
    TuiWindowCreateInfo window_create_info = tuiWindowCreateInfo();
    window_create_info.center_cursor = TUI_TRUE;

    /* Create the TUIC instance. */
    const char* window_title = "Example 1";
    TuiWindow window = tuiWindowCreate(window_width, window_height, window_title, &window_create_info);

    /* Load the atlas image */
    const char* atlas_image_name = "cp_8x8_rgb_fg_green.png";
    TuiImage atlas_image = tuiImageCreatePNG(atlas_image_name);
    if (atlas_image == TUI_NULL)
    {
        printf("Issue loading image file. Make sure that it was moved from the content folder to a location the executable can read. You need to do this manually.\n");
        tuiWindowDestroy(window);
        window = TUI_NULL;
        tuiTerminate();
        return -1;
    }

    /* Create the atlas */
    TuiBlendMode blend_mode = TUI_BLEND_FG_GREEN;
    TuiAtlas atlas = tuiAtlasCreateCodepageImage(atlas_image, blend_mode);
    tuiImageDestroy(atlas_image);
    atlas_image = TUI_NULL;

    /* Create the palette */
    int palette_color_count = 16;
    TuiPalette palette = tuiPaletteCreateXterm(palette_color_count);

    /* Create the batch (tile rendering data container) */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_FULL; // same as (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_FULL)
    TuiBatch batch = tuiBatchCreateFull(detail_mode, tiles_wide, tiles_tall, 0);

    /* Fill the batch with tile data. */
    for (int x = 0; x < tiles_wide; x++)
    {
        for (int y = 0; y < tiles_tall; y++)
        {
            uint8_t foreground_color_palette_id = x % 16;
            uint8_t background_color_palette_id = 16 - (y % 16);
            uint8_t two_color_byte = tuiClassicColorCombine(foreground_color_palette_id, background_color_palette_id);
            uint8_t glyph_id = (x + y) % 256;
            tuiBatchSetTile_G8_C4_FULL(batch, x, y, glyph_id, two_color_byte);
        }
    }

    /* Render initial clear color to window. */
    tuiWindowClearColor(window, 0, 0, 0, 255); //black

    /* Render the batch to the window */
    tuiWindowDrawBatch(window, atlas, palette, batch);

    /* Print prompt to console */
    printf("TUI rendered using a codepage glyph atlas and a 16 color XTerm palette.\n");

    /* fps tracking setup */
    double last_time = 0;
    int nbFrame = 0;

    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback functions

        /* Print fps to console */
        double currentTime = tuiGetTime();
        double delta = currentTime - last_time;
        nbFrame++;
        if (delta >= 1.0) { // If last fps print was more than 1 sec ago

            double fps = nbFrame / delta;
            printf("%f FPS\n", fps);
            nbFrame = 0;
            last_time = currentTime;
        }

        tuiWindowFrame(window); //draw the next frame from the window framebuffer
    }

    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window);
    window = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;

    tuiTerminate();
    return 0;
}
