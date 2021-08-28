/* Test drawing things to a TuiPanel. */

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

int main()
{
    tuiSetDebugErrorCallback(message_callback);

    if (tuiInit() == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return 1;
    }

    printf("Test drawing every drawable object to TuiPanel.\n");

    TuiPanel panel = tuiPanelCreate(256, 256);
    TuiPanel subject_panel = tuiPanelCreate(256, 256);

    TuiImage codepage = tuiImageCreatePNG("cp_8x8_rgba_bg_alpha.png");
    TuiAtlas atlas = tuiAtlasCreateCodepageImage(codepage, TUI_BLEND_BG_ALPHA);
    tuiImageDestroy(codepage);
    codepage = TUI_NULL;

    TuiImage sushi = tuiImageCreatePNG("sushi.png");
    TuiTexture texture = tuiTextureCreateImage(sushi, TUI_FILTER_POINT);
    tuiImageDestroy(sushi);
    sushi = TUI_NULL;

    TuiPalette palette = tuiPaletteCreateXterm(256);

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

    TuiWindow window = tuiWindowCreate(256, 256, "panel_drawing", TUI_NULL);
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    tuiPanelClearColor(panel, 0, 0, 0, 0);
    tuiPanelDrawAtlas(panel, atlas);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiAtlas...\n");
    frame(window);

    tuiPanelClearColor(panel, 0, 0, 0, 0);
    tuiPanelDrawAtlasTransformed(panel, atlas, 0, 128, 0, 128);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiAtlas with transform...\n");
    frame(window);

    tuiPanelClearColor(panel, 255, 255, 255, 255);
    tuiPanelDrawTexture(panel, texture);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiTexture...\n");
    frame(window);

    tuiPanelClearColor(panel, 255, 255, 255, 255);
    tuiPanelDrawTextureTransformed(panel, texture, 0, 128, 0, 128);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiTexture with transform...\n");
    frame(window);

    tuiPanelClearColor(panel, 0, 0, 0, 0);
    tuiPanelDrawBatch(panel, atlas, palette, batch);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiBatch...\n");
    frame(window);

    tuiPanelClearColor(panel, 0, 0, 0, 0);
    tuiPanelDrawBatchTransformed(panel, atlas, palette, batch, 0, 128, 0, 128);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiBatch with transform...\n");
    frame(window);

    tuiPanelClearColor(panel, 0, 0, 0, 255);
    tuiPanelClearColor(subject_panel, 0, 255, 0, 255); //green clear color
    tuiPanelDrawPanel(panel, subject_panel);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiPanel...\n");
    frame(window);

    tuiPanelClearColor(panel, 0, 0, 0, 255);
    tuiPanelClearColor(subject_panel, 0, 255, 0, 255); //green clear color
    tuiPanelDrawPanelTransformed(panel, subject_panel, 0, 128, 0, 128);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiPanel with transform...\n");
    frame(window);

    tuiWindowClearColor(window, 255, 0, 255, 255); //fushia clear color
    tuiPanelClearColor(panel, 0, 0, 0, 255);
    tuiPanelDrawWindow(panel, window);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiWindow...\n");
    frame(window);

    tuiWindowClearColor(window, 255, 0, 255, 255); //fushia clear color
    tuiPanelClearColor(panel, 0, 0, 0, 255);
    tuiPanelDrawWindowTransformed(panel, window, 0, 128, 0, 128);
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiWindow transformed...\n");
    frame(window);

    tuiPanelDestroy(panel);
    panel = TUI_NULL;
    tuiPanelDestroy(subject_panel);
    subject_panel = TUI_NULL;
    tuiAtlasDestroy(atlas);
    atlas = TUI_NULL;
    tuiTextureDestroy(texture);
    texture = TUI_NULL;
    tuiPaletteDestroy(palette);
    palette = TUI_NULL;
    tuiBatchDestroy(batch);
    batch = TUI_NULL;
    tuiWindowDestroy(window);
    window = TUI_NULL;

    tuiTerminate();
    return 0;
}