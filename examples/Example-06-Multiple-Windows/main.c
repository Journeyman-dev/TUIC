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

    /* Create the TUIC windows. */
    const char* window1_title = "Example 6 - Window 1";
    const char* window2_title = "Example 6 - Window 2";
    TuiWindow window1 = tuiWindowCreate(window_width, window_height, window1_title, TUI_NULL);
    TuiWindow window2 = tuiWindowCreate(window_width, window_height, window2_title, TUI_NULL);

    /* Load the atlas image */
    const char* atlas_image_name = "cp_8x8_rgb_fg_green.png";
    TuiImage atlas_image = tuiImageCreatePNG(atlas_image_name);
    if (atlas_image == TUI_NULL)
    {
        printf("Issue loading image file. Make sure that it was moved from the content folder to a location the executable can read. You need to do this manually.\n");
        tuiWindowDestroy(window1_title);
        window1_title = TUI_NULL;
        tuiWindowDestroy(window2_title);
        window2_title = TUI_NULL;
        tuiTerminate();
        return -1;
    }

    /* Create the Glyph Atlas */
    TuiBlendMode blend_mode = TUI_BLEND_FG_GREEN;
    TuiAtlas atlas = tuiAtlasCreateCodepageImage(atlas_image, blend_mode);
    tuiImageDestroy(atlas_image);
    atlas_image = TUI_NULL;

    /* Create the palette */
    int palette_color_count = 16;
    TuiPalette palette = tuiPaletteCreateXterm(palette_color_count);

    /* Create the panel (graphics framebuffer) */
    TuiPanel panel = tuiPanelCreate(window_width, window_height);

    /* Create the batch (tile rendering data container) */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_FULL; // same as (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_FULL)
    TuiBatch batch = tuiBatchCreateFull(detail_mode, tiles_wide, tiles_tall, 0);

    //Fill the batch with tile data.
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

    //Render the batch to the panel
    tuiPanelDrawBatch(panel, atlas, palette, batch);

    //Destroy the batch. We rendered it to the panel so we can render the panel instead of re-rendering the batch every frame.
    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    //Render panel to a png image file
    TuiImage out_image = tuiPanelGetImage(panel, TUI_NULL);
    const char* out_image_name = "example-1-screenshot.png";
    tuiImageSavePNG(out_image, out_image_name);
    tuiImageDestroy(out_image);
    out_image = TUI_NULL;

    //fps tracking setup
    double last_time = 0;
    int nbFrame = 0;

    //Render loop
    while (tuiWindowShouldClose(window1) == TUI_FALSE && tuiWindowShouldClose(window2) == TUI_FALSE)
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

        // draw the panel to the window
        tuiWindowDrawPanel(window1, panel);
        tuiWindowDrawPanel(window2, panel);
        // you can also render the contents of a window's framebuffer to a different window's framebuffer using tuiWindowDrawWindow() function
       
        tuiWindowFrame(window1); //draw the next frame from the window framebuffer
        tuiWindowFrame(window2);
    }

    /* Destroy all remaining TUIC objects */
    tuiPanelDestroy(panel);
    panel = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiWindowDestroy(window1);
    window1 = TUI_NULL;
    tuiWindowDestroy(window2);
    window2 = TUI_NULL;

    tuiTerminate();
    return 0;
}
