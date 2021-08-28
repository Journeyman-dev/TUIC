/* Test creating TuiAtlas objects with each creation function. */

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

    printf("Testing all atlas creation functions in order they are listed in the atlas.h header file by rendering then with batch data. Press spacebar to test the next creation function. The output should look like a codepage glyph atlas with black background and white foreground colors for every creation function.\n");

    const char* image_path = "cp_8x8_rgba_bg_alpha.png";
    TuiImage atlas_image = tuiImageCreatePNG(image_path);
    int image_width, image_height, image_channel_count;
    tuiImageGetPixelDimensions(atlas_image, &image_width, &image_height, &image_channel_count);
    uint8_t* image_pixels = tuiImageGetPixels(atlas_image);

    TuiBlendMode blend_mode = TUI_BLEND_BG_ALPHA;

    const int tiles_wide = 16;
    const int tiles_tall = 16;
    const int glyph_count = tiles_wide * tiles_tall;
    const int tile_pixel_dimensions = 8;

    uint16_t* pixel_bounding_boxes = (uint16_t*)tuiAllocate(16 * 16 * 4 * sizeof(uint16_t));
    {
        const size_t coords_per_tile = 4;
        
        for (size_t tile_y = 0; tile_y < (size_t)tiles_tall; tile_y++)
        {
            for (size_t tile_x = 0; tile_x < (size_t)tiles_wide; tile_x++)
            {
                size_t index = (size_t)((tile_x * coords_per_tile) + (tile_y * tiles_wide * coords_per_tile));
                
                //left
                pixel_bounding_boxes[index++] = (uint16_t)(tile_x * tile_pixel_dimensions);
                //right
                pixel_bounding_boxes[index++] = (uint16_t)((tile_x + 1) * tile_pixel_dimensions);
                //bottom
                pixel_bounding_boxes[index++] = (uint16_t)((tile_y + 1) * tile_pixel_dimensions);
                //top
                pixel_bounding_boxes[index] = (uint16_t)(tile_y * tile_pixel_dimensions);
            }
        }
    }

    float* raw_uvs = tuiGenerateUVCoordinatesFromPixelCooordinates(glyph_count, pixel_bounding_boxes, image_width, image_height, TUI_NULL);

    TuiAtlas* atlases = (TuiAtlas*)tuiAllocate(sizeof(TuiAtlas) * 8);
    atlases[0] = tuiAtlasCreateCoordinateImagePixelBoundingBoxes(atlas_image, glyph_count, pixel_bounding_boxes, blend_mode);
    atlases[1] = tuiAtlasCreateCoordinateRawPixelsPixelBoundingBoxes(image_width, image_height, image_channel_count, image_pixels, glyph_count, pixel_bounding_boxes, blend_mode);
    atlases[2] = tuiAtlasCreateCoordinateImageRawUVs(atlas_image, glyph_count, raw_uvs, blend_mode);
    atlases[3] = tuiAtlasCreateCoordinateRawPixelsRawUVs(image_width, image_height, image_channel_count, image_pixels, glyph_count, raw_uvs, blend_mode);
    atlases[4] = tuiAtlasCreateGridImage(atlas_image, tile_pixel_dimensions, tile_pixel_dimensions, blend_mode);
    atlases[5] = tuiAtlasCreateGridRawPixels(image_width, image_height, image_channel_count, image_pixels, tile_pixel_dimensions, tile_pixel_dimensions, blend_mode);
    atlases[6] = tuiAtlasCreateCodepageImage(atlas_image, blend_mode);
    atlases[7] = tuiAtlasCreateCodepageRawPixels(image_width, image_height, image_channel_count, image_pixels, blend_mode);
    
    tuiImageDestroy(atlas_image);
    atlas_image = TUI_NULL;

    tuiFree(raw_uvs);
    raw_uvs = TUI_NULL;
    tuiFree(pixel_bounding_boxes);
    pixel_bounding_boxes = TUI_NULL;

    const int palette_color_count = 16;
    TuiPalette palette = tuiPaletteCreateXterm(palette_color_count);

    TuiDetailMode detail_mode = TUI_DETAIL_MODE_G8_C4_FULL;
    const int batch_tiles_wide = 16;
    const int batch_tiles_tall = 16;
    TuiBatch batch = tuiBatchCreateFull(detail_mode, batch_tiles_wide, batch_tiles_tall, 0);
    {
        uint8_t glyph_id = 0;
        uint8_t foreground_color = 15;
        uint8_t background_color = 0;
        uint8_t two_color_byte = tuiClassicColorCombine(foreground_color, background_color);
        for (int tile_y = 0; tile_y < batch_tiles_tall; tile_y++)
        {
            for (int tile_x = 0; tile_x < batch_tiles_wide; tile_x++)
            {
                tuiBatchSetTile_G8_C4_FULL(batch, tile_x, tile_y, glyph_id++, two_color_byte);
            }
        }
    }

    TuiWindow window = tuiWindowCreate(256, 256, "atlas_creation", TUI_NULL);
    tuiWindowSetKeyboardKeyCallback(window, key_callback);

    TuiImage screenshot_image = TUI_NULL;
    tuiWindowDrawBatch(window, atlases[0], palette, batch);
    screenshot_image = tuiWindowGetImage(window);
    tuiImageSavePNG(screenshot_image, "ATLAS_0.png");
    printf("ATLAS_0\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[1], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_1.png");
    printf("ATLAS_1\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[2], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_2.png");
    printf("ATLAS_2\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[3], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_3.png");
    printf("ATLAS_3\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[4], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_4.png");
    printf("ATLAS_4\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[5], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_5.png");
    printf("ATLAS_5\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[6], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_6.png");
    printf("ATLAS_6\n");
    frame(window);

    tuiWindowClearColor(window, 0, 0, 0, 1);
    tuiWindowDrawBatch(window, atlases[7], palette, batch);
    tuiWindowWriteImage(window, screenshot_image);
    tuiImageSavePNG(screenshot_image, "ATLAS_7.png");
    printf("ATLAS_7\n");
    frame(window);

    tuiImageDestroy(screenshot_image);
    screenshot_image = TUI_NULL;

    tuiWindowDestroy(window);
    window = TUI_NULL;

    for (size_t atlas_i = 0; atlas_i < 8; atlas_i++)
    {
        tuiAtlasDestroy(atlases[atlas_i]);
        atlases[atlas_i] = TUI_NULL;
    }
    tuiFree(atlases);
    atlases = TUI_NULL;

    tuiPaletteDestroy(palette);
    palette = TUI_NULL;

    tuiBatchDestroy(batch);
    batch = TUI_NULL;

    tuiTerminate();
	return 0;
}