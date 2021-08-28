
#include <TUIC/tuic.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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

typedef struct FreeGlyph
{
    uint8_t glyph;
    uint8_t colors;
    int x;
    int y;
    TuiBoolean x_move_right;
    TuiBoolean y_move_down;
} FreeGlyph;

FreeGlyph* create_glyphs(int free_glyph_count, int window_width, int window_height, int glyph_pixel_dimensions)
{
    /* Allocate heap memory for the glyph data array. */
    size_t free_glyph_size = sizeof(FreeGlyph) * (size_t)free_glyph_count;
    FreeGlyph* free_glyphs = (FreeGlyph*)tuiAllocate(free_glyph_size);

    /* 0 out the glyph data array. */
    memset(free_glyphs, 0, free_glyph_size);

    /* Populate the glyphs in the array with randomized starting data. */
    for (size_t glyph_i = 0; glyph_i < (size_t)free_glyph_count; glyph_i++)
    {
        FreeGlyph* cur_glyph = free_glyphs + glyph_i;
        cur_glyph->glyph = rand() % 256;
        cur_glyph->colors = rand() % 256;
        cur_glyph->x = rand() % window_width - glyph_pixel_dimensions;
        cur_glyph->y = rand() % window_height - glyph_pixel_dimensions;
        cur_glyph->x_move_right = (TuiBoolean)(rand() % 2);
        cur_glyph->y_move_down = (TuiBoolean)(rand() % 2);
    }

    /* Return the free glyph array. */
    return free_glyphs;
}

void update_glyphs(FreeGlyph* free_glyphs, int free_glyph_count, int window_width, int window_height, int glyph_dimensions)
{
    /* Loop through each glyph to update its position for a new frame. */
    for (size_t glyph_i = 0; glyph_i < (size_t)free_glyph_count; glyph_i++)
    {
        FreeGlyph* cur_glyph = &free_glyphs[glyph_i];
        /* Move the glyph horizontally, and flip horizontal movement direction if hit the window edge. */
        if (cur_glyph->x_move_right)
        {
            if (cur_glyph->x >= window_width - glyph_dimensions)
            {
                cur_glyph->x_move_right = !cur_glyph->x_move_right;
            }
            else
            {
                cur_glyph->x++;
            }
        }
        else //if (!free_glyphs->x_move_right)
        {
            if (cur_glyph->x <= 0)
            {
                cur_glyph->x_move_right = !cur_glyph->x_move_right;
            }
            else
            {
                cur_glyph->x--;
            }
        }
        /* Move the glyph vertically, and flip verical movement direction if hit the window edge. */
        if (cur_glyph->y_move_down)
        {
            if (cur_glyph->y >= window_height - glyph_dimensions)
            {
                cur_glyph->y_move_down = !cur_glyph->y_move_down;
            }
            else
            {
                cur_glyph->y++;
            }
        }
        else //if (!free_glyphs->y_move_down)
        {
            if (cur_glyph->y <= 0)
            {
                cur_glyph->y_move_down = !cur_glyph->y_move_down;
            }
            else
            {
                cur_glyph->y--;
            }
        }
    }
}

void update_batch(TuiBatch batch, FreeGlyph* free_glyphs, int free_glyph_count)
{
    tuiBatchClear(batch);
    for (size_t glyph_i = 0; glyph_i < (size_t)free_glyph_count; glyph_i++)
    {
        FreeGlyph* cur_glyph = &free_glyphs[glyph_i];
        tuiBatchSetTile_G8_C4_FREE(batch, cur_glyph->x, cur_glyph->y, cur_glyph->glyph, cur_glyph->colors);
    }
}

int main()
{
    const int glyph_pixel_dimensions = 8;
    const int window_width = 256;
    const int window_height = 256;

    /* Initialize the TUIC library. */
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
    const char* window_title = "Example 5";
    TuiWindow window = tuiWindowCreate(1024, 1024, window_title, &window_create_info);

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

    printf("How many glyphs should be rendered?");
    int free_glyph_count = 128;
    scanf("%d", &free_glyph_count);

    /* Initialize the random number generation seed with the current system time. */
    time_t t;
    srand((unsigned int)time(&t));

    /* Create the glyph info array. */
    FreeGlyph* free_glyphs = create_glyphs(free_glyph_count, window_width, window_height, glyph_pixel_dimensions);

    /* Create the batch (tile rendering data container) */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_FREE; // same as (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_FREE)
    TuiBatch batch = tuiBatchCreateFree(detail_mode, glyph_pixel_dimensions, glyph_pixel_dimensions, window_width, window_height, free_glyph_count, 0);

    /* Render initial clear color to window. */
    tuiWindowClearColor(window, 0, 0, 0, 255); //black

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

        /* Update the window's framebuffer and present it to the window. */
        tuiWindowClearColor(window, 0, 0, 0, 255); //black
        update_glyphs(free_glyphs, free_glyph_count, window_width, window_height, glyph_pixel_dimensions);
        update_batch(batch, free_glyphs, free_glyph_count);
        tuiWindowDrawBatch(window, atlas, palette, batch);
        tuiWindowFrame(window);
    }
    
    /* Free the glyph data array. */
    tuiFree(free_glyphs);
    free_glyphs = TUI_NULL;

    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window);
    window = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;

    /* Terminate the TUIC library. */
    tuiTerminate();
    
    return 0;
}
