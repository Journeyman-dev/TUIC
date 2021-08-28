#include <TUIC/tuic.h>

#include <stdio.h>
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

const int kTileSizeMultiplier = 1;
const int kTilePixelWidth = 8;
const int kTilePixelHeight = 8;
const uint8_t kTrailHeadColor[3] = { 0, 255, 0 };
const uint8_t kBackColor[3] = { 0, 10, 0 };
const int kTrailLength = 15;
const int kTrailLenghtMultiplierMax = 1;
const int kTrailCreateChance = 20;
const double kUpdateDelta = 0.01;

typedef struct MatrixTrail
{
    TuiBoolean active;
    int head_y;
    int length;
} MatrixTrail;

typedef struct WindowUserPointer
{
    TuiBatch batch;
    TuiAtlas atlas;
    TuiPalette palette;
    uint8_t* glyphs;
    int monitor_width;
    int monitor_height;
    int extra_pixels_wide;
    int extra_pixels_tall;
    int tiles_wide;
    int tiles_tall;
} WindowUserPointer;

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState button_state, TuiKeyboardMod mod)
{
    if (key == TUIK_F && button_state == TUI_BUTTON_PRESS)
    {
        if (tuiWindowGetIsFullscreen(window) == TUI_FALSE)
        {
            tuiWindowSetFullscreen(window, tuiGetPrimaryMonitor());
        }
        else
        {
            tuiWindowSetWindowed(window);
        }
    }
}

int main()
{
    if (tuiInit() == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    TuiMonitor monitor = tuiGetPrimaryMonitor();
    int monitor_width = tuiMonitorGetPixelWidth(monitor);
    int monitor_height = tuiMonitorGetPixelHeight(monitor);
    int tiles_wide = monitor_width / (kTilePixelWidth * kTileSizeMultiplier);
    int tiles_tall = monitor_height / (kTilePixelHeight * kTileSizeMultiplier);
    int extra_pixels_wide = monitor_width - (tiles_wide * kTilePixelWidth * kTileSizeMultiplier);
    int extra_pixels_tall = monitor_height - (tiles_tall * kTilePixelWidth * kTileSizeMultiplier);

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Create the window. */
    TuiWindowCreateInfo create_info = tuiWindowCreateInfo();
    create_info.framebuffer_match_viewport_size = TUI_FALSE;
    const char* window_title = "Example 4";
    TuiWindow window = tuiWindowCreate(monitor_width, monitor_height, window_title, &create_info);

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
    int palette_channel_count = 3;
    uint8_t palette_colors[16 * 3];
    palette_colors[0] = kBackColor[0];
    palette_colors[1] = kBackColor[1];
    palette_colors[2] = kBackColor[2];
    for (size_t color_i = 1; color_i < palette_color_count; color_i++)
    {
        for (size_t channel_i = 0; channel_i < palette_channel_count; channel_i++)
        {
            float channel_color_max = ((float)kTrailHeadColor[channel_i]);
            float channel_color_min = ((float)kBackColor[channel_i]);
            float interpolation_percent = ((float)color_i) / ((float)kTrailLength);
            float interpolated_channel_color = channel_color_min + (interpolation_percent * (channel_color_max - channel_color_min));
            palette_colors[(color_i * 3) + channel_i] = ((uint8_t)(interpolated_channel_color));
        }
    }
    TuiPalette palette = tuiPaletteCreateColors(palette_channel_count, palette_color_count, palette_colors);

    /* Create the batch (tile rendering data container) */
    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_SPARSE; // same as (TUI_DETAIL_FLAG_GLYPH_8 | TUI_DETAIL_FLAG_COLOR_4 | TUI_DETAIL_FLAG_LAYOUT_SPARSE)
    TuiBatch batch = tuiBatchCreateSparse(detail_mode, tiles_wide, tiles_tall, TUI_FALSE, 0);

    /* Render initial clear color to window. */
    tuiWindowClearColor(window, 0, 0, 0, 255); //black

    /* Print prompt to console */
    printf("Enjoy the TUI matrix rain animation with codepage atlas and 16 color palette. Press F to toggle fulscreen.\n");

    /* init data */
    double last_frame = 0.0;
    double total_time = 0.0f;
    uint8_t* glyphs = tuiAllocate((size_t)tiles_wide * tiles_tall);
    memset(glyphs, 0, (size_t)tiles_wide * tiles_tall);
    MatrixTrail* trails = tuiAllocate(tiles_wide * sizeof(MatrixTrail));
    memset(trails, 0, tiles_wide * sizeof(MatrixTrail));
    size_t active_trails = 0;

    /* Setup the window user pointer */
    WindowUserPointer window_user_pointer;
    window_user_pointer.batch = batch;
    window_user_pointer.atlas = atlas;
    window_user_pointer.palette = palette;
    window_user_pointer.tiles_wide = tiles_wide;
    window_user_pointer.tiles_tall = tiles_tall;
    window_user_pointer.monitor_width = monitor_width;
    window_user_pointer.monitor_height = monitor_height;
    window_user_pointer.extra_pixels_wide = extra_pixels_wide;
    window_user_pointer.extra_pixels_tall = extra_pixels_tall;
    window_user_pointer.glyphs = glyphs;
    tuiWindowSetUserPointer(window, &window_user_pointer);

    /* Set the window callbacks. */
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    /* fps tracking setup */
    double last_time = 0;
    int nbFrame = 0;

    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback functions

        /* Print fps to console */
        double current_time = tuiGetTime();
        double second_delta = current_time - last_time;
        nbFrame++;
        if (second_delta >= 1.0) { // If last fps print was more than 1 sec ago

            double fps = nbFrame / second_delta;
            printf("%f FPS\n", fps);
            nbFrame = 0;
            last_time = current_time;
        }

        double delta = current_time - last_frame;
        last_frame = current_time;
        total_time += delta;
        if (total_time > kUpdateDelta)
        {
            total_time = 0.0;

            //If not max trails active, try to create new trail.
            if (active_trails < tiles_wide)
            {
                if (rand() % 100 <= kTrailCreateChance)
                {
                    int new_trail_i = 0;
                    for (int trail_i = rand() % tiles_wide; trail_i < tiles_wide; trail_i++)
                    {
                        if (trails[trail_i].active == 0)
                        {
                            new_trail_i = trail_i;
                            break;
                        }
                    }
                    trails[new_trail_i].active = 1;
                    trails[new_trail_i].head_y = 0;
                    trails[new_trail_i].length = ((rand() % kTrailLenghtMultiplierMax) + 1) * kTrailLength;
                    glyphs[new_trail_i] = (rand() % 255) + 1;
                    active_trails++;
                }
            }

            tuiBatchClear(batch);

            //loop through trails and move active ones down. create random glyph at new head, then render all tiles of trail at colors and deactivate trails that go offscreen.
            for (int trail_i = 0; trail_i < tiles_wide; trail_i++)
            {
                if (trails[trail_i].active == 1)
                {
                    trails[trail_i].head_y++;
                    int length = kTrailLength * trails[trail_i].length;
                    if (trails[trail_i].head_y >= tiles_wide + length)
                    {
                        trails[trail_i].active = 0;
                        active_trails--;
                        continue;
                    }
                    if (trails[trail_i].head_y < tiles_tall)
                    {
                        glyphs[trail_i + trails[trail_i].head_y * tiles_wide] = (rand() % 255) + 1;
                    }

                    for (int part_i = 0; part_i < length; part_i++)
                    {
                        int part_y = trails[trail_i].head_y - part_i;
                        if (part_y < tiles_tall)
                        {
                            uint8_t color = tuiClassicColorCombine(15 - (part_i / kTrailLength), 0);
                            tuiBatchSetTile_G8_C4_SPARSE(batch, trail_i, part_y, glyphs[trail_i + part_y * tiles_wide], color);
                        }
                    }
                }
            }
        }

        tuiWindowDrawBatchTransformed(window, atlas, palette, batch, 0, monitor_width - extra_pixels_wide, 0, monitor_height - extra_pixels_tall);

        tuiWindowFrame(window); //draw the next frame from the window framebuffer
    }

    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window);
    window = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;

    /* Free data arrays */
    tuiFree(glyphs);
    tuiFree(trails);

    tuiTerminate();
    return 0;
}
