/* Test drawing things to a TuiWindow. */

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

    printf("Test drawing every drawable object to TuiWindow.\n");

    TuiPanel panel = tuiPanelCreate(256, 256);

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

    TuiWindow window = tuiWindowCreate(256, 256, "window_drawing", TUI_NULL);
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawAtlas(window, atlas);
    printf("drawing TuiAtlas...\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawAtlasTransformed(window, atlas, 0, 128, 0, 128);
    printf("drawing TuiAtlas with transform...\n");
    frame(window);

    tuiWindowClearColor(window, 255, 255, 255, 255);
    tuiWindowDrawTexture(window, texture);
    printf("drawing TuiTexture...\n");
    frame(window);

    tuiWindowClearColor(window, 255, 255, 255, 255);
    tuiWindowDrawTextureTransformed(window, texture, 0, 128, 0, 128);
    printf("drawing TuiTexture with transform...\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawBatch(window, atlas, palette, batch);
    printf("drawing TuiBatch...\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawBatchTransformed(window, atlas, palette, batch, 0, 128, 0, 128);
    printf("drawing TuiBatch with transform...\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiPanelClearColor(panel, 0, 255, 0, 255); //green clear color
    tuiWindowDrawPanel(window, panel);
    printf("drawing TuiPanel...\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiPanelClearColor(panel, 0, 255, 0, 255); //green clear color
    tuiWindowDrawPanelTransformed(window, panel, 0, 128, 0, 128);
    printf("drawing TuiPanel with transform...\n");
    frame(window);

    TuiWindowCreateInfo subject_window_create_info = tuiWindowCreateInfo();
    subject_window_create_info.hidden = TUI_TRUE;
    TuiWindow subject_window = tuiWindowCreate(256, 256, "subject_window", &subject_window_create_info);
    tuiWindowHide(subject_window);
    tuiWindowFocus(window);

    tuiWindowClearColor(subject_window, 255, 0, 255, 255); //fushia clear color
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawWindow(window, subject_window);
    printf("drawing TuiWindow...\n");
    frame(window);

    tuiWindowClearColor(subject_window, 255, 0, 255, 255); //fushia clear color
    tuiWindowClearColor(window, 0, 0, 0, 255);
    tuiWindowDrawWindowTransformed(window, subject_window, 0, 128, 0, 128);
    printf("drawing TuiWindow transformed...\n");
    frame(window);

    tuiPanelDestroy(panel);
    panel = TUI_NULL;
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
    tuiWindowDestroy(subject_window);
    subject_window = TUI_NULL;

    tuiTerminate();
    return 0;
}