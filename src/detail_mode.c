#include <stddef.h>
#include <TUIC/detail_mode.h>
#include <TUIC/blend_mode.h>
#include <TUIC/debug.h>
#include <TUIC/boolean.h>

#define TO_STRING(value) #value

const size_t kTui_Detail_G8_C0_Size = 1;

const size_t kTui_Detail_G8_C4_Size = 2;

const size_t kTui_Detail_G8_C8_Size = 3;

const size_t kTui_Detail_G8_C8NBG_Size = 2;

const size_t kTui_Detail_G8_C8NFG_Size = 2;

const size_t kTui_Detail_G8_C24_Size = 7;

const size_t kTui_Detail_G8_C24NBG_Size = 4;

const size_t kTui_Detail_G8_C24NFG_Size = 4;

const size_t kTui_Detail_G8_C32_Size = 9;

const size_t kTui_Detail_G8_C32NBG_Size = 5;

const size_t kTui_Detail_G8_C32NFG_Size = 5;

const size_t kTui_Detail_G16_C0_Size = 2;

const size_t kTui_Detail_G16_C4_Size = 3;

const size_t kTui_Detail_G16_C8_Size = 4;

const size_t kTui_Detail_G16_C8NBG_Size = 3;

const size_t kTui_Detail_G16_C8NFG_Size = 3;

const size_t kTui_Detail_G16_C24_Size = 8;

const size_t kTui_Detail_G16_C24NBG_Size = 5;

const size_t kTui_Detail_G16_C24NFG_Size = 5;

const size_t kTui_Detail_G16_C32_Size = 10;

const size_t kTui_Detail_G16_C32NBG_Size = 6;

const size_t kTui_Detail_G16_C32NFG_Size = 6;

const char* kTui_Detail_G8_C0_Full_Name = TO_STRING(TUI_DETAIL_G8_C0_FULL);

const char* kTui_Detail_G8_C4_Full_Name = TO_STRING(TUI_DETAIL_G8_C4_FULL);

const char* kTui_Detail_G8_C8_Full_Name = TO_STRING(TUI_DETAIL_G8_C8_FULL);

const char* kTui_Detail_G8_C8NBG_Full_Name = TO_STRING(TUI_DETAIL_G8_C8NBG_FULL);

const char* kTui_Detail_G8_C8NFG_Full_Name = TO_STRING(TUI_DETAIL_G8_C8NFG_FULL);

const char* kTui_Detail_G8_C24_Full_Name = TO_STRING(TUI_DETAIL_G8_C24_FULL);

const char* kTui_Detail_G8_C24NBG_Full_Name = TO_STRING(TUI_DETAIL_G8_C24NBG_FULL);

const char* kTui_Detail_G8_C24NFG_Full_Name = TO_STRING(TUI_DETAIL_G8_C24NFG_FULL);

const char* kTui_Detail_G8_C32_Full_Name = TO_STRING(TUI_DETAIL_G8_C32_FULL);

const char* kTui_Detail_G8_C32NBG_Full_Name = TO_STRING(TUI_DETAIL_G8_C32NBG_FULL);

const char* kTui_Detail_G8_C32NFG_Full_Name = TO_STRING(TUI_DETAIL_G8_C32NFG_FULL);

const char* kTui_Detail_G16_C0_Full_Name = TO_STRING(TUI_DETAIL_G16_C0_FULL);

const char* kTui_Detail_G16_C4_Full_Name = TO_STRING(TUI_DETAIL_G16_C4_FULL);

const char* kTui_Detail_G16_C8_Full_Name = TO_STRING(TUI_DETAIL_G16_C8_FULL);

const char* kTui_Detail_G16_C8NBG_Full_Name = TO_STRING(TUI_DETAIL_G16_C8NBG_FULL);

const char* kTui_Detail_G16_C8NFG_Full_Name = TO_STRING(TUI_DETAIL_G16_C8NFG_FULL);

const char* kTui_Detail_G16_C24_Full_Name = TO_STRING(TUI_DETAIL_G16_C24_FULL);

const char* kTui_Detail_G16_C24NBG_Full_Name = TO_STRING(TUI_DETAIL_G16_C24NBG_FULL);

const char* kTui_Detail_G16_C24NFG_Full_Name = TO_STRING(TUI_DETAIL_G16_C24NFG_FULL);

const char* kTui_Detail_G16_C32_Full_Name = TO_STRING(TUI_DETAIL_G16_C32_FULL);

const char* kTui_Detail_G16_C32NBG_Full_Name = TO_STRING(TUI_DETAIL_G16_C32NBG_FULL);

const char* kTui_Detail_G16_C32NFG_Full_Name = TO_STRING(TUI_DETAIL_G16_C32NFG_FULL);

const char* kTui_Detail_G8_C0_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C0_SPARSE);

const char* kTui_Detail_G8_C4_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C4_SPARSE);

const char* kTui_Detail_G8_C8_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C8_SPARSE);

const char* kTui_Detail_G8_C8NBG_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C8NBG_SPARSE);

const char* kTui_Detail_G8_C8NFG_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C8NFG_SPARSE);

const char* kTui_Detail_G8_C24_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C24_SPARSE);

const char* kTui_Detail_G8_C24NBG_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C24NBG_SPARSE);

const char* kTui_Detail_G8_C24NFG_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C24NFG_SPARSE);

const char* kTui_Detail_G8_C32_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C32_SPARSE);

const char* kTui_Detail_G8_C32NBG_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C32NBG_SPARSE);

const char* kTui_Detail_G8_C32NFG_Sparse_Name = TO_STRING(TUI_DETAIL_G8_C32NFG_SPARSE);

const char* kTui_Detail_G16_C0_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C0_SPARSE);

const char* kTui_Detail_G16_C4_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C4_SPARSE);

const char* kTui_Detail_G16_C8_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C8_SPARSE);

const char* kTui_Detail_G16_C8NBG_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C8NBG_SPARSE);

const char* kTui_Detail_G16_C8NFG_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C8NFG_SPARSE);

const char* kTui_Detail_G16_C24_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C24_SPARSE);

const char* kTui_Detail_G16_C24NBG_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C24NBG_SPARSE);

const char* kTui_Detail_G16_C24NFG_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C24NFG_SPARSE);

const char* kTui_Detail_G16_C32_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C32_SPARSE);

const char* kTui_Detail_G16_C32NBG_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C32NBG_SPARSE);

const char* kTui_Detail_G16_C32NFG_Sparse_Name = TO_STRING(TUI_DETAIL_G16_C32NFG_SPARSE);

int tuiDetailIsValid(int detail_mode)
{
if (
	(detail_mode == TUI_DETAIL_G8_C0_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C4_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C8_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C8NBG_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C8NFG_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C24_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C24NBG_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C24NFG_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C32_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C32NBG_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C32NFG_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C0_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C4_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C8_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C8NBG_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C8NFG_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C24_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C24NBG_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C24NFG_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C32_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C32NBG_FULL) ||
	(detail_mode == TUI_DETAIL_G16_C32NFG_FULL) ||
	(detail_mode == TUI_DETAIL_G8_C0_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C4_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C8_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C8NBG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C8NFG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C24_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C24NBG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C24NFG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C32_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C32NBG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G8_C32NFG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C0_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C4_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C8_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C8NBG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C8NFG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C24_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C24NBG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C24NFG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C32_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C32NBG_SPARSE) ||
	(detail_mode == TUI_DETAIL_G16_C32NFG_SPARSE)
	)
{
	return TUI_TRUE;
}
return TUI_FALSE;
}

int tuiDetailHasFlag(int detail_mode, int detail_flag)
{
	if ((detail_mode & detail_flag) == detail_flag)
	{
		return TUI_TRUE;
	}
	else
	{
		return TUI_FALSE;
	}
}

int tuiDetailGetGlyphFlag(int detail_mode)
{
	return detail_mode & (
		TUI_GLYPH_FLAG_G8 |
		TUI_GLYPH_FLAG_G16);
}

int tuiDetailGetColorFlag(int detail_mode)
{
	return detail_mode & (
		TUI_COLOR_FLAG_C0 |
		TUI_COLOR_FLAG_C4 |
		TUI_COLOR_FLAG_C8 |
		TUI_COLOR_FLAG_C8NBG |
		TUI_COLOR_FLAG_C8NFG |
		TUI_COLOR_FLAG_C24 |
		TUI_COLOR_FLAG_C24NBG |
		TUI_COLOR_FLAG_C24NFG |
		TUI_COLOR_FLAG_C32 |
		TUI_COLOR_FLAG_C32NBG |
		TUI_COLOR_FLAG_C32NFG);
}

int tuiDetailGetLayoutFlag(int detail_mode)
{
	return detail_mode & (
		TUI_LAYOUT_FLAG_FULL |
		TUI_LAYOUT_FLAG_SPARSE);
}

size_t tuiDetailGetTileByteSize(int glyph_flag, int color_flag)
{
	switch (glyph_flag)
	{
	case TUI_GLYPH_FLAG_G8:
		switch (color_flag)
		{
		case TUI_COLOR_FLAG_C0:
			return kTui_Detail_G8_C0_Size;
		case TUI_COLOR_FLAG_C4:
			return kTui_Detail_G8_C4_Size;
		case TUI_COLOR_FLAG_C8:
			return kTui_Detail_G8_C8_Size;
		case TUI_COLOR_FLAG_C8NBG:
			return kTui_Detail_G8_C8NBG_Size;
		case TUI_COLOR_FLAG_C8NFG:
			return kTui_Detail_G8_C8NFG_Size;
		case TUI_COLOR_FLAG_C24:
			return kTui_Detail_G8_C24_Size;
		case TUI_COLOR_FLAG_C24NBG:
			return kTui_Detail_G8_C24NBG_Size;
		case TUI_COLOR_FLAG_C24NFG:
			return kTui_Detail_G8_C24NFG_Size;
		case TUI_COLOR_FLAG_C32:
			return kTui_Detail_G8_C32_Size;
		case TUI_COLOR_FLAG_C32NBG:
			return kTui_Detail_G8_C32NBG_Size;
		case TUI_COLOR_FLAG_C32NFG:
			return kTui_Detail_G8_C32NFG_Size;
		}
		break;
	case TUI_GLYPH_FLAG_G16:
		switch (color_flag)
		{
		case TUI_COLOR_FLAG_C0:
			return kTui_Detail_G16_C0_Size;
		case TUI_COLOR_FLAG_C4:
			return kTui_Detail_G16_C4_Size;
		case TUI_COLOR_FLAG_C8:
			return kTui_Detail_G16_C8_Size;
		case TUI_COLOR_FLAG_C8NBG:
			return kTui_Detail_G16_C8NBG_Size;
		case TUI_COLOR_FLAG_C8NFG:
			return kTui_Detail_G16_C8NFG_Size;
		case TUI_COLOR_FLAG_C24:
			return kTui_Detail_G16_C24_Size;
		case TUI_COLOR_FLAG_C24NBG:
			return kTui_Detail_G16_C24NBG_Size;
		case TUI_COLOR_FLAG_C24NFG:
			return kTui_Detail_G16_C24NFG_Size;
		case TUI_COLOR_FLAG_C32:
			return kTui_Detail_G16_C32_Size;
		case TUI_COLOR_FLAG_C32NBG:
			return kTui_Detail_G16_C32NBG_Size;
		case TUI_COLOR_FLAG_C32NFG:
			return kTui_Detail_G16_C32NFG_Size;
		}
		break;
	}
	return 0;
}

int tuiModesAreCompatible(int detail_mode, int blend_mode)
{
	if (blend_mode == TUI_BLEND_NORMAL)
	{
		if (tuiDetailHasFlag(detail_mode, TUI_COLOR_FLAG_C0) == TUI_TRUE)
		{
			return TUI_TRUE;
		}
		else
		{
			return TUI_FALSE;
		}
	}
	else if (tuiDetailHasFlag(detail_mode, TUI_COLOR_FLAG_C0) == TUI_TRUE)
	{
		return TUI_FALSE;
	}
	return TUI_TRUE;
}

int tuiDetailHasPalette(int detail_mode)
{
	if (tuiDetailHasFlag(detail_mode, TUI_COLOR_FLAG_C24) == TUI_FALSE && tuiDetailHasFlag(detail_mode, TUI_COLOR_FLAG_C0) == TUI_FALSE)
	{
		return TUI_TRUE;
	}
	else
	{
		return TUI_FALSE;
	}
}

const char* tuiDetailModeToString(int detail_mode)
{
	switch (detail_mode)
	{
	case TUI_DETAIL_G8_C0_FULL:
		return kTui_Detail_G8_C0_Full_Name;
	case TUI_DETAIL_G8_C4_FULL:
		return kTui_Detail_G8_C4_Full_Name;
	case TUI_DETAIL_G8_C8_FULL:
		return kTui_Detail_G8_C8_Full_Name;
	case TUI_DETAIL_G8_C8NBG_FULL:
		return kTui_Detail_G8_C8NBG_Full_Name;
	case TUI_DETAIL_G8_C8NFG_FULL:
		return kTui_Detail_G8_C8NFG_Full_Name;
	case TUI_DETAIL_G8_C24_FULL:
		return kTui_Detail_G8_C24_Full_Name;
	case TUI_DETAIL_G8_C24NBG_FULL:
		return kTui_Detail_G8_C24NBG_Full_Name;
	case TUI_DETAIL_G8_C24NFG_FULL:
		return kTui_Detail_G8_C24NFG_Full_Name;
	case TUI_DETAIL_G8_C32_FULL:
		return kTui_Detail_G8_C32_Full_Name;
	case TUI_DETAIL_G8_C32NBG_FULL:
		return kTui_Detail_G8_C32NBG_Full_Name;
	case TUI_DETAIL_G8_C32NFG_FULL:
		return kTui_Detail_G8_C32NFG_Full_Name;
	case TUI_DETAIL_G16_C0_FULL:
		return kTui_Detail_G16_C0_Full_Name;
	case TUI_DETAIL_G16_C4_FULL:
		return kTui_Detail_G16_C4_Full_Name;
	case TUI_DETAIL_G16_C8_FULL:
		return kTui_Detail_G16_C8_Full_Name;
	case TUI_DETAIL_G16_C8NBG_FULL:
		return kTui_Detail_G16_C8NBG_Full_Name;
	case TUI_DETAIL_G16_C8NFG_FULL:
		return kTui_Detail_G16_C8NFG_Full_Name;
	case TUI_DETAIL_G16_C24_FULL:
		return kTui_Detail_G16_C24_Full_Name;
	case TUI_DETAIL_G16_C24NBG_FULL:
		return kTui_Detail_G16_C24NBG_Full_Name;
	case TUI_DETAIL_G16_C24NFG_FULL:
		return kTui_Detail_G16_C24NFG_Full_Name;
	case TUI_DETAIL_G16_C32_FULL:
		return kTui_Detail_G16_C32_Full_Name;
	case TUI_DETAIL_G16_C32NBG_FULL:
		return kTui_Detail_G16_C32NBG_Full_Name;
	case TUI_DETAIL_G16_C32NFG_FULL:
		return kTui_Detail_G16_C32NFG_Full_Name;
	case TUI_DETAIL_G8_C0_SPARSE:
		return kTui_Detail_G8_C0_Sparse_Name;
	case TUI_DETAIL_G8_C4_SPARSE:
		return kTui_Detail_G8_C4_Sparse_Name;
	case TUI_DETAIL_G8_C8_SPARSE:
		return kTui_Detail_G8_C8_Sparse_Name;
	case TUI_DETAIL_G8_C8NBG_SPARSE:
		return kTui_Detail_G8_C8NBG_Sparse_Name;
	case TUI_DETAIL_G8_C8NFG_SPARSE:
		return kTui_Detail_G8_C8NFG_Sparse_Name;
	case TUI_DETAIL_G8_C24_SPARSE:
		return kTui_Detail_G8_C24_Sparse_Name;
	case TUI_DETAIL_G8_C24NBG_SPARSE:
		return kTui_Detail_G8_C24NBG_Sparse_Name;
	case TUI_DETAIL_G8_C24NFG_SPARSE:
		return kTui_Detail_G8_C24NFG_Sparse_Name;
	case TUI_DETAIL_G8_C32_SPARSE:
		return kTui_Detail_G8_C32_Sparse_Name;
	case TUI_DETAIL_G8_C32NBG_SPARSE:
		return kTui_Detail_G8_C32NBG_Sparse_Name;
	case TUI_DETAIL_G8_C32NFG_SPARSE:
		return kTui_Detail_G8_C32NFG_Sparse_Name;
	case TUI_DETAIL_G16_C0_SPARSE:
		return kTui_Detail_G16_C0_Sparse_Name;
	case TUI_DETAIL_G16_C4_SPARSE:
		return kTui_Detail_G16_C4_Sparse_Name;
	case TUI_DETAIL_G16_C8_SPARSE:
		return kTui_Detail_G16_C8_Sparse_Name;
	case TUI_DETAIL_G16_C8NBG_SPARSE:
		return kTui_Detail_G16_C8NBG_Sparse_Name;
	case TUI_DETAIL_G16_C8NFG_SPARSE:
		return kTui_Detail_G16_C8NFG_Sparse_Name;
	case TUI_DETAIL_G16_C24_SPARSE:
		return kTui_Detail_G16_C24_Sparse_Name;
	case TUI_DETAIL_G16_C24NBG_SPARSE:
		return kTui_Detail_G16_C24NBG_Sparse_Name;
	case TUI_DETAIL_G16_C24NFG_SPARSE:
		return kTui_Detail_G16_C24NFG_Sparse_Name;
	case TUI_DETAIL_G16_C32_SPARSE:
		return kTui_Detail_G16_C32_Sparse_Name;
	case TUI_DETAIL_G16_C32NBG_SPARSE:
		return kTui_Detail_G16_C32NBG_Sparse_Name;
	case TUI_DETAIL_G16_C32NFG_SPARSE:
		return kTui_Detail_G16_C32NFG_Sparse_Name;
	default:
		return NULL;
	}
}

int tuiStringToDetailMode(const char* string)
{
	if (strcmp(string, kTui_Detail_G8_C0_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C0_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C4_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C4_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C8_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C8_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C8NBG_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C8NBG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C8NFG_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C8NFG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C24_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C24_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C24NBG_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C24NBG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C24NFG_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C24NFG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C32_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C32_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C32NBG_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C32NBG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C32NFG_Full_Name) == 0)
	{
		return TUI_DETAIL_G8_C32NFG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C0_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C0_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C4_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C4_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C8_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C8_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C8NBG_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C8NBG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C8NFG_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C8NFG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C24_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C24_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C24NBG_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C24NBG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C24NFG_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C24NFG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C32_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C32_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C32NBG_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C32NBG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G16_C32NFG_Full_Name) == 0)
	{
		return TUI_DETAIL_G16_C32NFG_FULL;
	}
	else if (strcmp(string, kTui_Detail_G8_C0_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C0_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C4_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C4_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C8_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C8_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C8NBG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C8NBG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C8NFG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C8NFG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C24_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C24_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C24NBG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C24NBG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C24NFG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C24NFG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C32_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C32_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C32NBG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C32NBG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G8_C32NFG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G8_C32NFG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C0_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C0_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C4_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C4_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C8_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C8_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C8NBG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C8NBG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C8NFG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C8NFG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C24_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C24_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C24NBG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C24NBG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C24NFG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C24NFG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C32_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C32_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C32NBG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C32NBG_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_G16_C32NFG_Sparse_Name) == 0)
	{
		return TUI_DETAIL_G16_C32NFG_SPARSE;
	}
	return 0;
}
