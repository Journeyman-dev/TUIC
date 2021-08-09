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
#include <TUIC/debug.h>
#include <TUIC/types.h>

void tui_default_debug_callback(TuiErrorCode error_type, const char* str) {}

static tuiDebugErrorCallback sDebugCallback = tui_default_debug_callback;

void tuiSetDebugErrorCallback(tuiDebugErrorCallback callback)
{
	if (callback == TUI_NULL)
	{
		sDebugCallback = tui_default_debug_callback;
	}
	else
	{
		sDebugCallback = callback;
	}
}

void tuiDebugError(TuiErrorCode error_code, const char* msg)
{
	sDebugCallback(error_code, msg);
}