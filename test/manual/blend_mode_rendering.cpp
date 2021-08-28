/* Render test batches for every blend mode to a TuiWindow and save screenshots. */

#include <TUIC/tuic.h>

#include <stdio.h>
#include <string.h>

void message_callback(TuiErrorCode error_code, const char* msg)
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

static int sNextFrame = TUI_FALSE;

void frame(TuiWindow window)
{
    tuiWindowFrame(window);
    tuiPollEvents();
    sNextFrame = TUI_FALSE;
    while (sNextFrame == TUI_FALSE)
    {
        tuiWindowFrame(window);
        tuiPollEvents();
    }
}

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState state, TuiKeyboardMod mods)
{
    if (key == TUIK_SPACE && state == TUI_BUTTON_PRESS)
    {
        sNextFrame = TUI_TRUE;
    }
}

const char* const kAtlasImagePaths[9] =
{
    "cp_8x8_rgba_bg_alpha.png",
    "cp_8x8_rgb_fg_red.png",
    "cp_8x8_rgb_fg_green.png",
    "cp_8x8_rgb_fg_blue.png",
    "cp_8x8_rgba_fg_alpha.png",
    "cp_8x8_rgb_bg_red.png",
    "cp_8x8_rgb_bg_green.png",
    "cp_8x8_rgb_bg_blue.png",
    "cp_8x8_rgba_bg_alpha.png"
};

int main()
{
    tuiSetDebugErrorCallback(message_callback);

    if (tuiInit() == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return 1;
    }

    printf("Testing each blend mode by rendering a batch to a window. Press spacebar to test the next blend mode. The output should look like a codepage glyph atlas with black background and white foreground colors for every blend mode.\n");

    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_FULL;
    const int tiles_wide = 16;
    const int tiles_tall = 16;
    TuiBatch batch = tuiBatchCreateFull(detail_mode, tiles_wide, tiles_tall, 0);
    {
        uint8_t glyph_id = 0;
        uint8_t foreground_color = 15;
        uint8_t background_color = 0;
        uint8_t two_color_byte = tuiClassicColorCombine(foreground_color, background_color);
        for (int tile_y = 0; tile_y < tiles_tall; tile_y++)
        {
            for (int tile_x = 0; tile_x < tiles_wide; tile_x++)
            {
                tuiBatchSetTile_G8_C4_FULL(batch, tile_x, tile_y, glyph_id++, two_color_byte);
            }
        }
    }

    TuiAtlas* atlases = (TuiAtlas*)tuiAllocate(sizeof(TuiAtlas) * 9);
    for (size_t atlas_i = 0; atlas_i < 9; atlas_i++)
    {
        TuiBlendMode cur_blend_mode = (TuiBlendMode)(atlas_i + 1);
        TuiImage atlas_image = tuiImageCreatePNG(kAtlasImagePaths[atlas_i]);
        atlases[atlas_i] = tuiAtlasCreateCodepageImage(atlas_image, cur_blend_mode);
        tuiImageDestroy(atlas_image);
        atlas_image = TUI_NULL;
    }

    const int palette_color_count = 16;
    TuiPalette palette = tuiPaletteCreateXterm(palette_color_count);

    const int tile_pixel_dimensions = 8;
    TuiWindow window = tuiWindowCreate(256, 256, "blend_mode_rendering", TUI_NULL);
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    for (size_t blend_i = TUI_BLEND_FIRST; blend_i <= TUI_BLEND_LAST; blend_i++)
    {
        const char* blend_name = tuiBlendModeToString((TuiBlendMode)blend_i);
        tuiWindowClearColor(window, 0, 0, 0, 1);
        tuiWindowDrawBatch(window, atlases[blend_i - 1], palette, batch);
        printf("%s\n", blend_name);
        frame(window);
    }

    for (size_t atlas_i = 0; atlas_i < 9; atlas_i++)
    {
        tuiAtlasDestroy(atlases[atlas_i]);
        atlases[atlas_i] = TUI_NULL;
    }
    tuiFree(atlases);
    atlases = TUI_NULL;

    tuiWindowDestroy(window);
    window = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    tuiTerminate();

    return 0;
}