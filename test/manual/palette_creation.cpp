/* Test creating TuiPalette objects with each creation function. */

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

int main()
{
    tuiSetDebugErrorCallback(message_callback);

    if (tuiInit() == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return 1;
    }

    TuiPalette palette_1 = tuiPaletteCreateColors(3, 256, kTuiXtermPalette);

    TuiPalette palette_2 = tuiPaletteCreateXterm(256);

    TuiImage codepage = tuiImageCreatePNG("cp_8x8_rgba_bg_alpha.png");
    TuiAtlas atlas = tuiAtlasCreateCodepageImage(codepage, TUI_BLEND_BG_ALPHA);
    tuiImageDestroy(codepage);
    codepage = TUI_NULL;

    TuiBatch batch = tuiBatchCreateFull(TUI_DETAIL_MODE_G8_C4_FULL, 16, 16, 0);
    {
        uint8_t glyph_id = 0;
        for (int tile_y = 0; tile_y < 16; tile_y++)
        {
            for (int tile_x = 0; tile_x < 16; tile_x++)
            {
                uint8_t colors = tuiClassicColorCombine((uint8_t)tile_x, (uint8_t)tile_y);
                tuiBatchSetTile_G8_C4_FULL(batch, tile_x, tile_y, glyph_id++, colors);
            }
        }
    }

    TuiWindow window_1 = tuiWindowCreate(256, 256, "palette_1", TUI_NULL);
    TuiWindow window_2 = tuiWindowCreate(256, 256, "palette_2", TUI_NULL);

    while (tuiWindowShouldClose(window_1) == TUI_FALSE && tuiWindowShouldClose(window_2) == TUI_FALSE)
    {
        tuiPollEvents();
        tuiWindowDrawBatch(window_1, atlas, palette_1, batch);
        tuiWindowFrame(window_1);
        tuiWindowDrawBatch(window_2, atlas, palette_2, batch);
        tuiWindowFrame(window_2);        
    }

    tuiPaletteDestroy(palette_1);
    palette_1 = TUI_NULL;
    tuiPaletteDestroy(palette_2);
    palette_2 = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;
    tuiWindowDestroy(window_1);
    window_1 = TUI_NULL;
    tuiWindowDestroy(window_2);
    window_2 = TUI_NULL;

    tuiTerminate();
    return 0;
}