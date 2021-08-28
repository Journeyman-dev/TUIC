
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
const size_t kTilePixelWidth = 16;
const size_t kTilePixelHeight = 16;

int main()
{
    int window_width = kTilesWide * kTilePixelWidth;
    int window_height = kTilesTall * kTilePixelHeight;

    /* Initialize TUIC. */
    TuiBoolean multi_window = TUI_FALSE;
    TuiBoolean initialization_successful = tuiInit(multi_window);
    if (initialization_successful == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Load the atlas image */
    const char* atlas_image_name = "kenny_roguelikeSheet_transparent.png";
    TuiImage atlas_image = tuiImageCreatePNG(atlas_image_name);
    if (atlas_image == TUI_NULL)
    {
        printf("Issue loading image file. Make sure that it was moved from the content folder to a location the executable can read. You need to do this manually.\n");
        tuiTerminate();
        return -1;
    }

    /* Create the atlas */
    const uint16_t glyphs_tall = 31;
    const uint16_t glyphs_wide = 53;
    const uint16_t glyph_count = glyphs_tall * glyphs_wide;
    const uint16_t glyph_width = 16;
    const uint16_t glyph_height = 16;
    uint16_t* glyph_bounding_boxes = tuiAllocate(sizeof(size_t) * glyph_count * 4);
    {
        size_t i = 0;
        for (uint16_t y = 0; y < glyphs_tall; y++)
        {
            for (uint16_t x = 0; x < glyphs_wide; x++)
            {
                glyph_bounding_boxes[i++] = (x * glyph_width) + x;                      //left x pixel
                glyph_bounding_boxes[i++] = (x * glyph_width) + (x + glyph_width);      //right x pixel
                glyph_bounding_boxes[i++] = (y * glyph_height) + (y + glyph_height);    //top y pixel
                glyph_bounding_boxes[i++] = (y * glyph_height) + y;                     //bottom y pixel
            }
        }
    }
    TuiBlendMode blend_mode = TUI_BLEND_BG_ALPHA;
    TuiAtlas atlas = tuiAtlasCreateCoordinateImagePixelBoundingBoxes(atlas_image, glyph_count, glyph_bounding_boxes, blend_mode);
    tuiImageDestroy(atlas_image);
    atlas_image = TUI_NULL;
    tuiFree(glyph_bounding_boxes);
    glyph_bounding_boxes = TUI_NULL;

    /* Create the batch */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G16_C24_FULL;
    TuiBatch batch = tuiBatchCreateFull(detail_mode, kTilesTall, kTilesWide, 0);

    /* Fill the batch with data */
    for (int tile_x = 0; tile_x < kTilesWide; tile_x++)
    {
        for (int tile_y = 0; tile_y < kTilesTall; tile_y++)
        {
            int glyph = (tile_x * tile_y) % glyph_count;
            uint8_t fg_r = (tile_x * 4) % 255;
            uint8_t fg_g = (tile_y * 2) % 255;
            uint8_t fg_b = (tile_x * tile_y) % 255;
            uint8_t bg_r = 0;
            uint8_t bg_g = 0;
            uint8_t bg_b = 0;
            tuiBatchSetTile_G16_C24_FULL(batch, tile_x, tile_y, glyph, fg_r, fg_g, fg_b, bg_r, bg_g, bg_b);
        }
    }

    /* Create the window. */
    const char* window_title = "Example 2";
    TuiWindow window = tuiWindowCreate(window_width, window_height, window_title, TUI_NULL);

    /* Render initial clear color to window. */
    tuiWindowClearColor(window, 0, 0, 0, 255); //black

    /* Draw batch to window */
    TuiPalette palette = TUI_NULL; //no palette for this detail mode
    tuiWindowDrawBatch(window, atlas, palette, batch);

    //Destroy the batch. We rendered it to the panel so we can render the panel instead of re-rendering the batch every frame.
    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    /* Print prompt to console */
    printf("TUI rendered using a cutom glyph atlas and 24 bit fullcolor.\n");
    
    /* fps tracking setup */
    double last_time = 0;
    int nbFrame = 0;

    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback function.

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
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    tuiTerminate();
    return 0;
}
