/* Render batches to a TuiWindow to test 3 and 4 channel TuiPalette objects and save screenshots. */

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

const int kPaletteColorsCount = 256;

TuiPalette create_test_palette(int channels)
{
    uint8_t* palette_colors = (uint8_t*)tuiAllocate((size_t)channels * (size_t)kPaletteColorsCount);
    for (size_t color_i = 0; color_i < (size_t)kPaletteColorsCount; color_i++)
    {
        size_t index = color_i * (size_t)channels;
        palette_colors[index++] = 15 * (16 % (color_i + 1));
        palette_colors[index++] = 15 * (15 - (16 % (color_i + 1)));
        palette_colors[index] = 0;
        if (channels == 4)
        {
            palette_colors[++index] = 15 * (256 % (color_i + 1));
        }
    }
    TuiPalette palette = tuiPaletteCreateColors(channels, kPaletteColorsCount, palette_colors);
    tuiFree(palette_colors);
    return palette;
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

int main()
{
    tuiSetDebugErrorCallback(message_callback);

    if (tuiInit() == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return 1;
    }

    printf("Test rendering palettes of all channel counts.\n");

    TuiPalette* palettes = (TuiPalette*)tuiAllocate(sizeof(TuiPalette) * 2);
    palettes[0] = create_test_palette(3);
    palettes[1] = create_test_palette(4);

    TuiImage codepage = tuiImageCreatePNG("cp_8x8_rgba_bg_alpha.png");
    TuiAtlas atlas = tuiAtlasCreateCodepageImage(codepage, TUI_BLEND_BG_ALPHA);
    tuiImageDestroy(codepage);
    codepage = TUI_NULL;

    TuiBatch batch = tuiBatchCreateFull(TUI_DETAIL_MODE_G8_C4_FULL, 256, 256, 0);
    {
        uint8_t glyph_id = 0;
        for (int tile_y = 0; tile_y < 256; tile_y++)
        {
            for (int tile_x = 0; tile_x < 256; tile_x++)
            {
                uint8_t colors = tuiClassicColorCombine((uint8_t)tile_x, (uint8_t)tile_y);
                tuiBatchSetTile_G8_C4_FULL(batch, tile_x, tile_y, glyph_id++, colors);
            }
        }
    }

    TuiWindow window = tuiWindowCreate(256*8, 256*8, "palette_rendering", TUI_NULL);
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    for (size_t palette_i = 0; palette_i < 2; palette_i++)
    {
        TuiPalette cur_palette = palettes[palette_i];
        tuiWindowClearColor(window, 255, 0, 0, 255);
        tuiWindowDrawBatch(window, atlas, cur_palette, batch);
        printf("Rendering palette %d.\n", (int)palette_i);
        frame(window);
    }

    tuiPaletteDestroy(palettes[0]);
    tuiPaletteDestroy(palettes[1]);
    tuiFree(palettes);
    palettes = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;
    tuiWindowDestroy(window);
    window = TUI_NULL;

    tuiTerminate();
    return 0;
}