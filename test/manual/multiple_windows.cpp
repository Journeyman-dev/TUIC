/* Test rendering every renderable object across multiple windows. */

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

    TuiImage sushi = tuiImageCreatePNG("sushi.png");
    TuiImage codepage = tuiImageCreatePNG("cp_8x8_rgba_bg_alpha.png");

    TuiTexture texture = tuiTextureCreateImage(sushi, TUI_FILTER_POINT);

    TuiAtlas atlas = tuiAtlasCreateCodepageImage(codepage, TUI_BLEND_BG_ALPHA);

    TuiPalette palette = tuiPaletteCreateXterm(16);

    TuiPanel panel = tuiPanelCreate(256, 256);
    tuiPanelClearColor(panel, 255, 0, 0, 255); //red clear color

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

    TuiWindow texture_window = tuiWindowCreate(256, 256, "Texture", TUI_NULL);
    TuiWindow atlas_window = tuiWindowCreate(256, 256, "Atlas", TUI_NULL);
    TuiWindow batch_window = tuiWindowCreate(256, 256, "Batch", TUI_NULL);
    TuiWindow panel_window = tuiWindowCreate(256, 256, "Panel", TUI_NULL);

    while (
        tuiWindowShouldClose(texture_window) == TUI_FALSE &&
        tuiWindowShouldClose(atlas_window) == TUI_FALSE &&
        tuiWindowShouldClose(batch_window) == TUI_FALSE &&
        tuiWindowShouldClose(panel_window) == TUI_FALSE)
    {
        tuiPollEvents();

        tuiWindowClearColor(texture_window, 255, 255, 255, 255); //white clear color
        tuiWindowDrawTexture(texture_window, texture);
        tuiWindowFrame(texture_window);

        tuiWindowDrawAtlas(atlas_window, atlas);
        tuiWindowFrame(atlas_window);

        tuiWindowDrawBatch(batch_window, atlas, palette, batch);
        tuiWindowFrame(batch_window);

        tuiWindowDrawPanel(panel_window, panel);
        tuiWindowFrame(panel_window);
    }

    tuiImageDestroy(sushi);
    sushi = TUI_NULL;
    tuiImageDestroy(codepage);
    codepage = TUI_NULL;

    tuiTextureDestroy(texture);
    texture = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiPanelDestroy(panel);
    panel = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    tuiWindowDestroy(texture_window);
    texture_window = TUI_NULL;
    tuiWindowDestroy(atlas_window);
    atlas_window = TUI_NULL;
    tuiWindowDestroy(batch_window);
    batch_window = TUI_NULL;
    tuiWindowDestroy(panel_window);
    panel_window = TUI_NULL;

    tuiTerminate();
    return 0;
}