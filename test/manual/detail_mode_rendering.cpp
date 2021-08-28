/* Render test batches for every detail mode to a TuiWindow and save screenshots. */

#include <TUIC/tuic.h>

#include <stdio.h>
#include <string.h>

#define TEST_DIMENSIONS 128

TuiBatch GetTestPatternBatch(TuiDetailMode detail_mode)
{
	TuiBatch batch = TUI_NULL;
	TuiDetailFlag detail_flag = tuiDetailGetLayoutFlag(detail_mode);
	switch (detail_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		batch = tuiBatchCreateFull(detail_mode, TEST_DIMENSIONS, TEST_DIMENSIONS, 0);
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		batch = tuiBatchCreateSparse(detail_mode, TEST_DIMENSIONS, TEST_DIMENSIONS, TUI_TRUE, 0);
		break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
		batch = tuiBatchCreateFree(detail_mode, 8, 8, TEST_DIMENSIONS, TEST_DIMENSIONS, TEST_DIMENSIONS * TEST_DIMENSIONS, 0);
		break;
	default:
		break;
	}
	
	for (int x = 0; x < TEST_DIMENSIONS; x++)
	{
		for (int y = 0; y < TEST_DIMENSIONS; y++)
		{
			if (!tuiDetailHasFlag(detail_mode, TUI_DETAIL_FLAG_LAYOUT_SPARSE) == TUI_TRUE || (x % 2 == 0 && y % 2 == 0))
			{
				switch (detail_mode)
				{
				case TUI_DETAIL_MODE_G0_C8NBG_FULL:
					tuiBatchSetTile_G0_C8NBG_FULL(batch, x, y, x % 256);
					break;
				case TUI_DETAIL_MODE_G0_C24NBG_FULL:
					tuiBatchSetTile_G0_C24NBG_FULL(batch, x, y, x % 256, y % 256, x % 256);
					break;
				case TUI_DETAIL_MODE_G0_C32NBG_FULL:
					tuiBatchSetTile_G0_C32NBG_FULL(batch, x, y, y % 256, x % 128, y % 256, y);
					break;
				case TUI_DETAIL_MODE_G8_C0_FULL:
					tuiBatchSetTile_G8_C0_FULL(batch, x, y, x);
					break;
				case TUI_DETAIL_MODE_G8_C4_FULL:
					tuiBatchSetTile_G8_C4_FULL(batch, x, y, x, tuiClassicColorCombine(x % 16, y % 16));
					break;
				case TUI_DETAIL_MODE_G8_C8NBG_FULL:
					tuiBatchSetTile_G8_C8NBG_FULL(batch, x, y, x, x % 256);
					break;
				case TUI_DETAIL_MODE_G8_C8_FULL:
					tuiBatchSetTile_G8_C8_FULL(batch, x, y, x, x % 256, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C8NFG_FULL:
					tuiBatchSetTile_G8_C8NFG_FULL(batch, x, y, x, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C24_FULL:
					tuiBatchSetTile_G8_C24_FULL(batch, x, y, x, x % 256, y % 256, x % 256, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C24NBG_FULL:
					tuiBatchSetTile_G8_C24NBG_FULL(batch, x, y, x, x % 256, y % 256, x % 256);
					break;
				case TUI_DETAIL_MODE_G8_C24NFG_FULL:
					tuiBatchSetTile_G8_C24NFG_FULL(batch, x, y, x, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C32_FULL:
					tuiBatchSetTile_G8_C32_FULL(batch, x, y, x, y % 256, x % 128, y % 256, y, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G8_C32NBG_FULL:
					tuiBatchSetTile_G8_C32NBG_FULL(batch, x, y, x, y % 256, x % 128, y % 256, y);
					break;
				case TUI_DETAIL_MODE_G8_C32NFG_FULL:
					tuiBatchSetTile_G8_C32NFG_FULL(batch, x, y, x, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G16_C0_FULL:
					tuiBatchSetTile_G16_C0_FULL(batch, x, y, x);
					break;
				case TUI_DETAIL_MODE_G16_C4_FULL:
					tuiBatchSetTile_G16_C4_FULL(batch, x, y, x, tuiClassicColorCombine(x % 16, y % 16));
					break;
				case TUI_DETAIL_MODE_G16_C8NBG_FULL:
					tuiBatchSetTile_G16_C8NBG_FULL(batch, x, y, x, x % 256);
					break;
				case TUI_DETAIL_MODE_G16_C8_FULL:
					tuiBatchSetTile_G16_C8_FULL(batch, x, y, x, x % 256, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C8NFG_FULL:
					tuiBatchSetTile_G16_C8NFG_FULL(batch, x, y, x, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C24_FULL:
					tuiBatchSetTile_G16_C24_FULL(batch, x, y, x, x % 256, y % 256, x % 256, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C24NBG_FULL:
					tuiBatchSetTile_G16_C24NBG_FULL(batch, x, y, x, x % 256, y % 256, x % 256);
					break;
				case TUI_DETAIL_MODE_G16_C24NFG_FULL:
					tuiBatchSetTile_G16_C24NFG_FULL(batch, x, y, x, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C32_FULL:
					tuiBatchSetTile_G16_C32_FULL(batch, x, y, x, y % 256, x % 128, y % 256, y, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G16_C32NBG_FULL:
					tuiBatchSetTile_G16_C32NBG_FULL(batch, x, y, x, y % 256, x % 128, y % 256, y);
					break;
				case TUI_DETAIL_MODE_G16_C32NFG_FULL:
					tuiBatchSetTile_G16_C32NFG_FULL(batch, x, y, x, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G0_C8NBG_SPARSE:
					tuiBatchSetTile_G0_C8NBG_SPARSE(batch, x, y, x % 256);
					break;
				case TUI_DETAIL_MODE_G0_C24NBG_SPARSE:
					tuiBatchSetTile_G0_C24NBG_SPARSE(batch, x, y, x % 256, y % 256, x % 256);
					break;
				case TUI_DETAIL_MODE_G0_C32NBG_SPARSE:
					tuiBatchSetTile_G0_C32NBG_SPARSE(batch, x, y, y % 256, x % 128, y % 256, y);
					break;
				case TUI_DETAIL_MODE_G8_C0_SPARSE:
					tuiBatchSetTile_G8_C0_SPARSE(batch, x, y, x);
					break;
				case TUI_DETAIL_MODE_G8_C4_SPARSE:
					tuiBatchSetTile_G8_C4_SPARSE(batch, x, y, x, tuiClassicColorCombine(x % 16, y % 16));
					break;
				case TUI_DETAIL_MODE_G8_C8NBG_SPARSE:
					tuiBatchSetTile_G8_C8NBG_SPARSE(batch, x, y, x, x % 256);
					break;
				case TUI_DETAIL_MODE_G8_C8_SPARSE:
					tuiBatchSetTile_G8_C8_SPARSE(batch, x, y, x, x % 256, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C8NFG_SPARSE:
					tuiBatchSetTile_G8_C8NFG_SPARSE(batch, x, y, x, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C24_SPARSE:
					tuiBatchSetTile_G8_C24_SPARSE(batch, x, y, x, x % 256, y % 256, x % 256, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C24NBG_SPARSE:
					tuiBatchSetTile_G8_C24NBG_SPARSE(batch, x, y, x, x % 256, y % 256, x % 256);
					break;
				case TUI_DETAIL_MODE_G8_C24NFG_SPARSE:
					tuiBatchSetTile_G8_C24NFG_SPARSE(batch, x, y, x, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G8_C32_SPARSE:
					tuiBatchSetTile_G8_C32_SPARSE(batch, x, y, x, y % 256, x % 128, y % 256, y, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G8_C32NBG_SPARSE:
					tuiBatchSetTile_G8_C32NBG_SPARSE(batch, x, y, x, y % 256, x % 128, y % 256, y);
					break;
				case TUI_DETAIL_MODE_G8_C32NFG_SPARSE:
					tuiBatchSetTile_G8_C32NFG_SPARSE(batch, x, y, x, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G16_C0_SPARSE:
					tuiBatchSetTile_G16_C0_SPARSE(batch, x, y, x);
					break;
				case TUI_DETAIL_MODE_G16_C4_SPARSE:
					tuiBatchSetTile_G16_C4_SPARSE(batch, x, y, x, tuiClassicColorCombine(x % 16, y % 16));
					break;
				case TUI_DETAIL_MODE_G16_C8NBG_SPARSE:
					tuiBatchSetTile_G16_C8NBG_SPARSE(batch, x, y, x, x % 256);
					break;
				case TUI_DETAIL_MODE_G16_C8_SPARSE:
					tuiBatchSetTile_G16_C8_SPARSE(batch, x, y, x, x % 256, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C8NFG_SPARSE:
					tuiBatchSetTile_G16_C8NFG_SPARSE(batch, x, y, x, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C24_SPARSE:
					tuiBatchSetTile_G16_C24_SPARSE(batch, x, y, x, x % 256, y % 256, x % 256, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C24NBG_SPARSE:
					tuiBatchSetTile_G16_C24NBG_SPARSE(batch, x, y, x, x % 256, y % 256, x % 256);
					break;
				case TUI_DETAIL_MODE_G16_C24NFG_SPARSE:
					tuiBatchSetTile_G16_C24NFG_SPARSE(batch, x, y, x, y % 256, x % 128, y % 256);
					break;
				case TUI_DETAIL_MODE_G16_C32_SPARSE:
					tuiBatchSetTile_G16_C32_SPARSE(batch, x, y, x, y % 256, x % 128, y % 256, y, x % 256, y % 128, x % 256, x);
					break;
				case TUI_DETAIL_MODE_G16_C32NBG_SPARSE:
					tuiBatchSetTile_G16_C32NBG_SPARSE(batch, x, y, x, y % 256, x % 128, y % 256, y);
					break;
				case TUI_DETAIL_MODE_G16_C32NFG_SPARSE:
					tuiBatchSetTile_G16_C32NFG_SPARSE(batch, x, y, x, x % 256, y % 128, x % 256, x);
					break;
				}
			}
		}
	}
	return batch;
}

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
	while (sNextFrame == TUI_FALSE && tuiWindowShouldClose(window) == TUI_FALSE)
	{
		tuiWindowFrame(window);
		tuiPollEvents();
	}
}

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState state, TuiKeyboardMod mods)
{
	if (key == TUIK_SPACE && (  state == TUI_BUTTON_PRESS || state == TUI_BUTTON_REPEAT))
	{
		sNextFrame = TUI_TRUE;
	}
}

const TuiDetailMode kDetailModes[46] =
{
	TUI_DETAIL_MODE_G0_C8NBG_FULL,
	TUI_DETAIL_MODE_G0_C24NBG_FULL,
	TUI_DETAIL_MODE_G0_C32NBG_FULL,
	TUI_DETAIL_MODE_G8_C4_FULL,
	TUI_DETAIL_MODE_G8_C8_FULL,
	TUI_DETAIL_MODE_G8_C8NBG_FULL,
	TUI_DETAIL_MODE_G8_C8NFG_FULL,
	TUI_DETAIL_MODE_G8_C24_FULL,
	TUI_DETAIL_MODE_G8_C24NBG_FULL,
	TUI_DETAIL_MODE_G8_C24NFG_FULL,
	TUI_DETAIL_MODE_G8_C32_FULL,
	TUI_DETAIL_MODE_G8_C32NBG_FULL,
	TUI_DETAIL_MODE_G8_C32NFG_FULL,
	TUI_DETAIL_MODE_G16_C4_FULL,
	TUI_DETAIL_MODE_G16_C8_FULL,
	TUI_DETAIL_MODE_G16_C8NBG_FULL,
	TUI_DETAIL_MODE_G16_C8NFG_FULL,
	TUI_DETAIL_MODE_G16_C24_FULL,
	TUI_DETAIL_MODE_G16_C24NBG_FULL,
	TUI_DETAIL_MODE_G16_C24NFG_FULL,
	TUI_DETAIL_MODE_G16_C32_FULL,
	TUI_DETAIL_MODE_G16_C32NBG_FULL,
	TUI_DETAIL_MODE_G16_C32NFG_FULL,
	TUI_DETAIL_MODE_G0_C8NBG_SPARSE,
	TUI_DETAIL_MODE_G0_C24NBG_SPARSE,
	TUI_DETAIL_MODE_G0_C32NBG_SPARSE,
	TUI_DETAIL_MODE_G8_C4_SPARSE,
	TUI_DETAIL_MODE_G8_C8_SPARSE,
	TUI_DETAIL_MODE_G8_C8NBG_SPARSE,
	TUI_DETAIL_MODE_G8_C8NFG_SPARSE,
	TUI_DETAIL_MODE_G8_C24_SPARSE,
	TUI_DETAIL_MODE_G8_C24NBG_SPARSE,
	TUI_DETAIL_MODE_G8_C24NFG_SPARSE,
	TUI_DETAIL_MODE_G8_C32_SPARSE,
	TUI_DETAIL_MODE_G8_C32NBG_SPARSE,
	TUI_DETAIL_MODE_G8_C32NFG_SPARSE,
	TUI_DETAIL_MODE_G16_C4_SPARSE,
	TUI_DETAIL_MODE_G16_C8_SPARSE,
	TUI_DETAIL_MODE_G16_C8NBG_SPARSE,
	TUI_DETAIL_MODE_G16_C8NFG_SPARSE,
	TUI_DETAIL_MODE_G16_C24_SPARSE,
	TUI_DETAIL_MODE_G16_C24NBG_SPARSE,
	TUI_DETAIL_MODE_G16_C24NFG_SPARSE,
	TUI_DETAIL_MODE_G16_C32_SPARSE,
	TUI_DETAIL_MODE_G16_C32NBG_SPARSE,
	TUI_DETAIL_MODE_G16_C32NFG_SPARSE
};

int main()
{
	tuiSetDebugErrorCallback(message_callback);

	if (tuiInit() == TUI_FALSE)
	{
		printf("Failed to initialize TUIC.");
		return 1;
	}

	printf("Testing all detail modes by rendering test pattern batches. Press spacebar to render the next batch.\n");

	TuiImage image = tuiImageCreatePNG("cp_8x8_rgba_bg_alpha.png");
	TuiAtlas atlas = tuiAtlasCreateCodepageImage(image, TUI_BLEND_BG_ALPHA);
	tuiImageDestroy(image);
	image = TUI_NULL;

	TuiPalette palette = tuiPaletteCreateXterm(256);

	const int tile_pixel_dimensions = 8;
	TuiWindow window = tuiWindowCreate(TEST_DIMENSIONS * 8, TEST_DIMENSIONS * 8, "detail_mode_rendering", TUI_NULL);
	tuiWindowSetKeyboardKeyCallback(window, key_callback);

	for (size_t detail_mode_i = 0; detail_mode_i < 46; detail_mode_i++)
	{
		TuiDetailMode cur_detail_mode = kDetailModes[detail_mode_i];
		TuiBatch batch = GetTestPatternBatch(cur_detail_mode);
		tuiWindowClearColor(window, 0, 0, 0, 255);
		tuiWindowDrawBatch(window, atlas, palette, batch);
		const char* cur_detail_mode_name = tuiDetailModeToString(cur_detail_mode);
		printf("%s\n", cur_detail_mode_name);
		frame(window);
		tuiBatchDestroy(batch);
		batch = TUI_NULL;
		if (tuiWindowShouldClose(window) == TUI_TRUE)
		{
			break;
		}
	}
		
	tuiAtlasDestroy(atlas);
	atlas = TUI_NULL;
	tuiPaletteDestroy(palette);
	palette = TUI_NULL;
	tuiWindowDestroy(window);
	window = TUI_NULL;

	tuiTerminate();

	return 0;
}