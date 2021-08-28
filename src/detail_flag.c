/*
	Copyright (c) 2021 Daniel Valcour
	
	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <TUIC/detail_flag.h>
#include <TUIC/debug.h>
#include <TUIC/types.h>
#include <string.h>

#define TO_STRING(value) #value

const char* kTui_Detail_Flag_G0_Name = TO_STRING(TUI_DETAIL_FLAG_GLYPH_0);

const char* kTui_Detail_Flag_G8_Name = TO_STRING(TUI_DETAIL_FLAG_GLYPH_8);

const char* kTui_Detail_Flag_G16_Name = TO_STRING(TUI_DETAIL_FLAG_GLYPH_16);

const char* kTui_Detail_Flag_C0_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_0);

const char* kTui_Detail_Flag_C4_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_4);

const char* kTui_Detail_Flag_C8_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_8);

const char* kTui_Detail_Flag_C8NBG_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_8NBG);

const char* kTui_Detail_Flag_C8NFG_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_8NFG);

const char* kTui_Detail_Flag_C24_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_24);

const char* kTui_Detail_Flag_C24NBG_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_24NBG);

const char* kTui_Detail_Flag_C24NFG_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_24NFG);

const char* kTui_Detail_Flag_C32_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_32);

const char* kTui_Detail_Flag_C32NBG_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_32NBG);

const char* kTui_Detail_Flag_C32NFG_Name = TO_STRING(TUI_DETAIL_FLAG_COLOR_32NFG);

const char* kTui_Detail_Flag_Full_Name = TO_STRING(TUI_DETAIL_FLAG_LAYOUT_FULL);

const char* kTui_Detail_Flag_Sparse_Name = TO_STRING(TUI_DETAIL_FLAG_LAYOUT_SPARSE);

const char* kTui_Detail_Flag_Free_Name = TO_STRING(TUI_DETAIL_FLAG_LAYOUT_FREE);

TuiBoolean tuiDetailFlagIsValid(TuiDetailFlag detail_flag)
{
	return
		(detail_flag == TUI_DETAIL_FLAG_GLYPH_0) ||
		(detail_flag == TUI_DETAIL_FLAG_GLYPH_8) ||
		(detail_flag == TUI_DETAIL_FLAG_GLYPH_16) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_0) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_4) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_8) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_8NBG) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_8NFG) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_24) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_24NBG) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_24NFG) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_32) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_32NBG) ||
		(detail_flag == TUI_DETAIL_FLAG_COLOR_32NFG) ||
		(detail_flag == TUI_DETAIL_FLAG_LAYOUT_FULL) ||
		(detail_flag == TUI_DETAIL_FLAG_LAYOUT_SPARSE) ||
		(detail_flag == TUI_DETAIL_FLAG_LAYOUT_FREE);
}

const char* tuiDetailFlagToString(TuiDetailFlag detail_flag)
{
	switch (detail_flag)
	{
	case TUI_DETAIL_FLAG_GLYPH_0:
		return kTui_Detail_Flag_G0_Name;
	case TUI_DETAIL_FLAG_GLYPH_8:
		return kTui_Detail_Flag_G8_Name;
	case TUI_DETAIL_FLAG_GLYPH_16:
		return kTui_Detail_Flag_G16_Name;
	case TUI_DETAIL_FLAG_COLOR_0:
		return kTui_Detail_Flag_C0_Name;
	case TUI_DETAIL_FLAG_COLOR_4:
		return kTui_Detail_Flag_C4_Name;
	case TUI_DETAIL_FLAG_COLOR_8:
		return kTui_Detail_Flag_C8_Name;
	case TUI_DETAIL_FLAG_COLOR_8NBG:
		return kTui_Detail_Flag_C8NBG_Name;
	case TUI_DETAIL_FLAG_COLOR_8NFG:
		return kTui_Detail_Flag_C8NFG_Name;
	case TUI_DETAIL_FLAG_COLOR_24:
		return kTui_Detail_Flag_C24_Name;
	case TUI_DETAIL_FLAG_COLOR_24NBG:
		return kTui_Detail_Flag_C24NBG_Name;
	case TUI_DETAIL_FLAG_COLOR_24NFG:
		return kTui_Detail_Flag_C24NFG_Name;
	case TUI_DETAIL_FLAG_COLOR_32:
		return kTui_Detail_Flag_C32_Name;
	case TUI_DETAIL_FLAG_COLOR_32NBG:
		return kTui_Detail_Flag_C32NBG_Name;
	case TUI_DETAIL_FLAG_COLOR_32NFG:
		return kTui_Detail_Flag_C32NFG_Name;
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		return kTui_Detail_Flag_Full_Name;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		return kTui_Detail_Flag_Sparse_Name;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
		return kTui_Detail_Flag_Free_Name;
	default:
		return TUI_NULL;
	}
}

TuiDetailFlag tuiStringToDetailFlag(const char* string)
{
	if (strcmp(string, kTui_Detail_Flag_G0_Name) == 0)
	{
		return TUI_DETAIL_FLAG_GLYPH_0;
	}
	else if (strcmp(string, kTui_Detail_Flag_G8_Name) == 0)
	{
		return TUI_DETAIL_FLAG_GLYPH_8;
	}
	else if (strcmp(string, kTui_Detail_Flag_G16_Name) == 0)
	{
		return TUI_DETAIL_FLAG_GLYPH_16;
	}
	else if (strcmp(string, kTui_Detail_Flag_C0_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_0;
	}
	else if (strcmp(string, kTui_Detail_Flag_C4_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_4;
	}
	else if (strcmp(string, kTui_Detail_Flag_C8_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_8;
	}
	else if (strcmp(string, kTui_Detail_Flag_C8NBG_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_8NBG;
	}
	else if (strcmp(string, kTui_Detail_Flag_C8NFG_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_8NFG;
	}
	else if (strcmp(string, kTui_Detail_Flag_C24_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_24;
	}
	else if (strcmp(string, kTui_Detail_Flag_C24NBG_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_24NBG;
	}
	else if (strcmp(string, kTui_Detail_Flag_C24NFG_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_24NFG;
	}
	else if (strcmp(string, kTui_Detail_Flag_C32_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_32;
	}
	else if (strcmp(string, kTui_Detail_Flag_C32NBG_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_32NBG;
	}
	else if (strcmp(string, kTui_Detail_Flag_C32NFG_Name) == 0)
	{
		return TUI_DETAIL_FLAG_COLOR_32NFG;
	}
	else if (strcmp(string, kTui_Detail_Flag_Full_Name) == 0)
	{
		return TUI_DETAIL_FLAG_LAYOUT_FULL;
	}
	else if (strcmp(string, kTui_Detail_Flag_Sparse_Name) == 0)
	{
		return TUI_DETAIL_FLAG_LAYOUT_SPARSE;
	}
	else if (strcmp(string, kTui_Detail_Flag_Free_Name) == 0)
	{
		return TUI_DETAIL_FLAG_LAYOUT_FREE;
	}
	return TUI_DETAIL_FLAG_INVALID;
}