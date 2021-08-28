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
#include <TUIC/tuic.h>
#include "objects.h"
#include <string.h>

TuiBatch tuiBatchCreateFull(TuiDetailMode detail_mode, int tiles_wide, int tiles_tall, size_t minimum_reserved_data_size)
{
	if (tiles_wide <= 0 || tiles_tall <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS, __func__);
		return TUI_NULL;
	}
	if (tuiDetailIsValid(detail_mode) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_DETAIL_MODE, __func__);
		return TUI_NULL;
	}
	if (tuiDetailGetLayoutFlag(detail_mode) != TUI_DETAIL_FLAG_LAYOUT_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return TUI_NULL;
	}

	TuiBatchFull_s* batch = tuiAllocate(sizeof(TuiBatchFull_s));

	batch->DetailMode = detail_mode;
	batch->TilesWide = tiles_wide;
	batch->TilesTall = tiles_tall;
	batch->BytesPerTile = tuiDetailGetTileByteSize(tuiDetailGetGlyphFlag(detail_mode), tuiDetailGetColorFlag(detail_mode));
	batch->UsedDataSize = batch->BytesPerTile * batch->TilesWide * batch->TilesTall;
	batch->ReservedDataSize = batch->UsedDataSize;
	if (batch->UsedDataSize < minimum_reserved_data_size)
	{
		batch->ReservedDataSize = minimum_reserved_data_size;
	}
	batch->Data = tuiAllocate(batch->ReservedDataSize);
	memset(batch->Data, 0, batch->ReservedDataSize);
	batch->TileCount = batch->TilesWide * batch->TilesTall;

	return batch;
}

TuiBatch tuiBatchCreateSparse(TuiDetailMode detail_mode, int tiles_wide, int tiles_tall, TuiBoolean use_stencil, size_t minimum_reserved_data_size)
{
	if (tiles_wide <= 0 || tiles_tall <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS, __func__);
		return TUI_NULL;
	}
	if (tuiDetailIsValid(detail_mode) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_DETAIL_MODE, __func__);
		return TUI_NULL;
	}
	if (tuiDetailGetLayoutFlag(detail_mode) != TUI_DETAIL_FLAG_LAYOUT_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return TUI_NULL;
	}

	TuiBatchSparse_s* batch = tuiAllocate(sizeof(TuiBatchSparse_s));

	batch->DetailMode = detail_mode;
	batch->TilesWide = tiles_wide;
	batch->TilesTall = tiles_tall;
	batch->BytesPerTile = tuiDetailGetTileByteSize(tuiDetailGetGlyphFlag(detail_mode), tuiDetailGetColorFlag(detail_mode));
	batch->TileCount = 0;
	batch->MaxTileCount = 0;
	batch->HasLargeXCoordinate = TUI_FALSE;
	batch->HasLargeYCoordinate = TUI_FALSE;
	batch->UseStencil = use_stencil;
	batch->StencilData = TUI_NULL;
	batch->StencilDataSize = 0;
	if (use_stencil == TUI_TRUE)
	{
		batch->StencilDataSize = batch->TilesWide * batch->TilesTall * sizeof(size_t);
		batch->StencilData = (size_t*)tuiAllocate(batch->StencilDataSize);
		memset(batch->StencilData, 0, batch->StencilDataSize);
	}
	batch->BytesPerTile += 2; //Sparse batches have at least two extra bytes per tile for the coordinates of each tile
	if (tiles_wide > 256) //if the width or the height is greater than 256, two bytes are needed for each respective coordinate to store values large enough
	{
		batch->HasLargeXCoordinate = TUI_TRUE;
		batch->BytesPerTile++;
	}
	if (tiles_tall > 256)
	{
		batch->HasLargeYCoordinate = TUI_TRUE;
		batch->BytesPerTile++;
	}
	batch->MaxTileCount = batch->TilesWide * batch->TilesTall;
	batch->UsedDataSize = batch->BytesPerTile * batch->MaxTileCount;
	batch->ReservedDataSize = batch->UsedDataSize;
	if (batch->UsedDataSize < minimum_reserved_data_size)
	{
		batch->ReservedDataSize = minimum_reserved_data_size;
	}
	batch->Data = tuiAllocate(batch->ReservedDataSize);
	memset(batch->Data, 0, batch->ReservedDataSize);

	return batch;
}

TuiBatch tuiBatchCreateFree(TuiDetailMode detail_mode, int tile_pixel_width, int tile_pixel_height, int draw_viewport_width, int draw_viewport_height, int maximum_tile_count, size_t minimum_reserved_data_size)
{
	if (tile_pixel_width <= 0 || tile_pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS, __func__);
		return TUI_NULL;
	}
	if (tuiDetailIsValid(detail_mode) == TUI_FALSE)
	{ 
		tuiDebugError(TUI_ERROR_INVALID_DETAIL_MODE, __func__);
		return TUI_NULL;
	}
	if (tuiDetailGetLayoutFlag(detail_mode) != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return TUI_NULL;
	}

	TuiBatchFree_s* batch = tuiAllocate(sizeof(TuiBatchFree_s));

	batch->DetailMode = detail_mode;
	batch->BytesPerTile = tuiDetailGetTileByteSize(tuiDetailGetGlyphFlag(detail_mode), tuiDetailGetColorFlag(detail_mode));
	batch->BytesPerTile += 4; //Free batches have 2 uint16_t for the x and y positions of each tile. Unlike with sparse batches, coordinates are never optimized to 1 bytes.
	batch->TilePixelWidth = tile_pixel_width;
	batch->TilePixelHeight = tile_pixel_height;
	batch->TileCount = 0;
	batch->DrawViewportWidth = draw_viewport_width;
	batch->DrawViewportHeight = draw_viewport_height;
	batch->MaxTileCount = maximum_tile_count;
	batch->UsedDataSize = batch->BytesPerTile * batch->MaxTileCount;
	batch->ReservedDataSize = batch->UsedDataSize;
	if (batch->UsedDataSize < minimum_reserved_data_size)
	{
		batch->ReservedDataSize = minimum_reserved_data_size;
	}
	batch->Data = tuiAllocate(batch->ReservedDataSize);
	memset(batch->Data, 0, batch->ReservedDataSize);

	return batch;
}

void tuiBatchDestroy(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);

	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		{
			TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
			tuiFree(batch_full->Data);
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		{
			TuiBatchSparse_s * batch_sparse = (TuiBatchSparse_s*)batch;
			if (batch_sparse->StencilData != TUI_NULL)
			{
				tuiFree(batch_sparse->StencilData);
			}
			tuiFree(batch_sparse->Data);
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
		{
			TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
			tuiFree(batch_free->Data);
		}
		break;
	}

	tuiFree(batch);
}

TuiDetailMode tuiBatchGetDetail(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return 0;
	}
	
	return batch->DetailMode;
}

void tuiBatchSetTileDimensions(TuiBatch batch, int tiles_wide, int tiles_tall, TuiBoolean reserve_extra)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (tiles_wide <= 0 || tiles_tall <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_TILE_DIMENSIONS, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag == TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		{
			TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
			batch_full->TilesWide = (size_t)tiles_wide;
			batch_full->TilesTall = (size_t)tiles_tall;
			batch_full->TileCount = batch_full->TilesWide * batch_full->TilesTall;
			batch_full->UsedDataSize = batch_full->BytesPerTile * batch_full->TileCount;
			if (reserve_extra == TUI_FALSE || batch_full->UsedDataSize > batch_full->ReservedDataSize)
			{
				batch_full->ReservedDataSize = batch_full->UsedDataSize;
				batch_full->Data = tuiReallocate(batch_full->Data, batch_full->ReservedDataSize);
			}
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		{
			TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
			batch_sparse->TilesWide = (size_t)tiles_wide;
			batch_sparse->TilesTall = (size_t)tiles_tall;
			batch_sparse->BytesPerTile = tuiDetailGetTileByteSize(tuiDetailGetGlyphFlag(batch->DetailMode), tuiDetailGetColorFlag(batch->DetailMode));
			batch_sparse->HasLargeXCoordinate = TUI_FALSE;
			batch_sparse->HasLargeYCoordinate = TUI_FALSE;
			batch_sparse->TileCount = 0;
			batch_sparse->BytesPerTile += 2;
			if (tiles_wide > 256)
			{
				batch_sparse->HasLargeXCoordinate = TUI_TRUE;
				batch_sparse->BytesPerTile++;
			}
			if (tiles_tall > 256)
			{
				batch_sparse->HasLargeYCoordinate = TUI_TRUE;
				batch_sparse->BytesPerTile++;
			}
			if (batch_sparse->UseStencil)
			{
				batch_sparse->StencilDataSize = batch_sparse->TilesWide * batch_sparse->TilesTall * sizeof(size_t);
				tuiReallocate(batch_sparse->StencilData, batch_sparse->StencilDataSize);
			}
			batch_sparse->UsedDataSize = batch_sparse->BytesPerTile * batch_sparse->TilesWide * batch_sparse->TilesTall;
			if (reserve_extra == TUI_FALSE || batch_sparse->UsedDataSize > batch_sparse->ReservedDataSize)
			{
				batch_sparse->ReservedDataSize = batch_sparse->UsedDataSize;
				batch_sparse->Data = tuiReallocate(batch_sparse->Data, batch_sparse->ReservedDataSize);
			}
		}
		break;
	}
}

void tuiBatchGetTileDimensions(TuiBatch batch, int* tiles_wide, int* tiles_tall)
{	
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag == TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		{
			TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
			if (tiles_wide != TUI_NULL)
			{
				*tiles_wide = batch_full->TilesWide;
			}
			if (tiles_tall != TUI_NULL)
			{
				*tiles_tall = batch_full->TilesTall;
			}
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		{
			TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
			if (tiles_wide != TUI_NULL)
			{
				*tiles_wide = batch_sparse->TilesWide;
			}
			if (tiles_tall != TUI_NULL)
			{
				*tiles_tall = batch_sparse->TilesTall;
			}
		}
		break;
	}
}

int tuiBatchGetTilesWide(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return 0;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag == TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return 0;
	}

	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		{
			TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
			return batch_full->TilesWide;
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		{
			TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
			return batch_sparse->TilesWide;
		}
		break;
	}
	return 0;
}

int tuiBatchGetTilesTall(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return 0;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag == TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return 0;
	}

	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		{
			TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
			return batch_full->TilesTall;
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		{
			TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
			return batch_sparse->TilesTall;
		}
		break;
	}
	return 0;
}

void tuiBatchSetViewportPixelDimensions(TuiBatch batch, int pixel_width, int pixel_height)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	batch_free->DrawViewportWidth = pixel_width;
	batch_free->DrawViewportHeight = pixel_height;
	batch_free->TileCount = 0;
}

void tuiBatchGetViewportPixelDimensions(TuiBatch batch, int* pixel_width, int* pixel_height)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	if (pixel_width != TUI_NULL)
	{
		*pixel_width = batch_free->DrawViewportWidth;
	}
	if (pixel_height != TUI_NULL)
	{
		*pixel_height = batch_free->DrawViewportHeight;
	}
}

int tuiBatchGetViewportPixelWidth(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	return batch_free->DrawViewportWidth;
}

int tuiBatchGetViewportPixelHeight(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	return batch_free->DrawViewportHeight;
}

void tuiBatchSetGlyphPixelDimensions(TuiBatch batch, int pixel_width, int pixel_height)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_PIXEL_DIMENSIONS, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	batch_free->TilePixelWidth = pixel_width;
	batch_free->TilePixelHeight = pixel_height;
	batch_free->TileCount = 0;
}

void tuiBatchGetGlyphPixelDimensions(TuiBatch batch, int* pixel_width, int* pixel_height)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	if (pixel_width != TUI_NULL)
	{
		*pixel_width = batch_free->TilePixelWidth;
	}
	if (pixel_height != TUI_NULL)
	{
		*pixel_height = batch_free->TilePixelHeight;
	}
}

int tuiBatchGetGlyphPixelWidth(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	return batch_free->TilePixelWidth;
}

int tuiBatchGetGlyphPixelHeight(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	if (layout_flag != TUI_DETAIL_FLAG_LAYOUT_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}

	TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
	return batch_free->TilePixelHeight;
}

int tuiBatchGetDataSize(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return 0;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
		{
			TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
			return batch_full->UsedDataSize;
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
		{
			TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
			return batch_sparse->UsedDataSize;
		}
		break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
		{
			TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
			return batch_free->UsedDataSize;
		}
		break;
	}
	return 0;
}

int tuiBatchGetReservedSize(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return 0;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
	{
		TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
		return batch_full->ReservedDataSize;
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
	{
		TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
		return batch_sparse->ReservedDataSize;
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
	{
		TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
		return batch_free->ReservedDataSize;
	}
	break;
	}
	return 0;
}

int tuiBatchGetTileCount(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return 0;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
	{
		TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
		return batch_full->TileCount;
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
	{
		TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
		return batch_sparse->TileCount;
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
	{
		TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
		return batch_free->TileCount;
	}
	break;
	}
	return 0;
}

const uint8_t* tuiBatchGetData(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return TUI_NULL;
	}

	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
	{
		TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
		return batch_full->Data;
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
	{
		TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
		return batch_sparse->Data;
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
	{
		TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
		return batch_free->Data;
	}
	break;
	}
	return TUI_NULL;

}

void tuiBatchClear(TuiBatch batch)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	
	TuiDetailFlag layout_flag = tuiDetailGetLayoutFlag(batch->DetailMode);
	switch (layout_flag)
	{
	case TUI_DETAIL_FLAG_LAYOUT_FULL:
	{
		TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
		memset(batch_full->Data, 0, batch_full->UsedDataSize);
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_SPARSE:
	{
		TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
		batch_sparse->TileCount = 0;
		if (batch_sparse->UseStencil)
		{
			memset(batch_sparse->StencilData, 0, batch_sparse->StencilDataSize);
		}
	}
	break;
	case TUI_DETAIL_FLAG_LAYOUT_FREE:
	{
		TuiBatchFree_s* batch_free = (TuiBatchFree_s*)batch;
		batch_free->TileCount = 0;
	}
	break;
	}
	return;
}

static inline TuiBoolean _PointOutOfBatchFull(TuiBatchFull_s* batch_full, size_t x, size_t y)
{
	return (x < 0 || y < 0 || x >= batch_full->TilesWide || y >= batch_full->TilesTall);
}

static inline size_t _BatchFullGetDataIndex(TuiBatchFull_s* batch_full, size_t x, size_t y)
{
	return (size_t)y * batch_full->TilesWide * batch_full->BytesPerTile
		+ (size_t)x * batch_full->BytesPerTile;
}

static inline void _BatchFullSet_8(TuiBatchFull_s* batch_full, size_t* data_index, uint8_t value)
{
	batch_full->Data[(*data_index)++] = value;
}

static inline void _BatchFullSet_16(TuiBatchFull_s* batch_full, size_t* data_index, uint16_t value)
{
	batch_full->Data[(*data_index)++] = (value) & 0xff; // first 8 bits
	batch_full->Data[(*data_index)++] = (value >> 8) & 0xff; // second 8 bits
}

static inline void _BatchFullSet_C24(TuiBatchFull_s* batch_full, size_t* data_index, uint8_t r, uint8_t g, uint8_t b)
{
	batch_full->Data[(*data_index)++] = r;
	batch_full->Data[(*data_index)++] = g;
	batch_full->Data[(*data_index)++] = b;
}

static inline void _BatchFullSet_C32(TuiBatchFull_s* batch_full, size_t* data_index, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	batch_full->Data[(*data_index)++] = r;
	batch_full->Data[(*data_index)++] = g;
	batch_full->Data[(*data_index)++] = b;
	batch_full->Data[(*data_index)++] = a;
}

void tuiBatchSetTile_G0_C8NBG_FULL(TuiBatch batch, int x, int y, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C8NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, fg);
}

void tuiBatchSetTile_G0_C24NBG_FULL(TuiBatch batch, int x, int y, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C24NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_C24(batch_full, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G0_C32NBG_FULL(TuiBatch batch, int x, int y, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C32NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_C32(batch_full, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G8_C0_FULL(TuiBatch batch, int x, int y, uint8_t glyph)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C0_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
}

void tuiBatchSetTile_G8_C4_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t colors)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C4_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, colors);
}

void tuiBatchSetTile_G8_C8_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y); 
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, fg);
	_BatchFullSet_8(batch_full, &data_index, bg);
}

void tuiBatchSetTile_G8_C8NBG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, fg);
}

void tuiBatchSetTile_G8_C8NFG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8NFG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, bg);
}

void tuiBatchSetTile_G8_C24_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_C24(batch_full, &data_index, fg_r, fg_g, fg_b);
	_BatchFullSet_C24(batch_full, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G8_C24NBG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_C24(batch_full, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G8_C24NFG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24NFG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_C24(batch_full, &data_index, bg_r, bg_g, bg_b);
}


void tuiBatchSetTile_G8_C32_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_C32(batch_full, &data_index, fg_r, fg_g, fg_b, fg_a);
	_BatchFullSet_C32(batch_full, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G8_C32NBG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_C32(batch_full, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G8_C32NFG_FULL(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32NFG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_8(batch_full, &data_index, glyph);
	_BatchFullSet_C32(batch_full, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G16_C0_FULL(TuiBatch batch, int x, int y, uint16_t glyph)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C0_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
}

void tuiBatchSetTile_G16_C4_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t colors)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C4_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, colors);
}

void tuiBatchSetTile_G16_C8_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, fg);
	_BatchFullSet_8(batch_full, &data_index, bg);
}

void tuiBatchSetTile_G16_C8NBG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, fg);
}

void tuiBatchSetTile_G16_C8NFG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8NFG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_8(batch_full, &data_index, bg);
}

void tuiBatchSetTile_G16_C24_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_C24(batch_full, &data_index, fg_r, fg_g, fg_b);
	_BatchFullSet_C24(batch_full, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G16_C24NBG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_C24(batch_full, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G16_C24NFG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24NFG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_C24(batch_full, &data_index, bg_r, bg_g, bg_b);
}


void tuiBatchSetTile_G16_C32_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_C32(batch_full, &data_index, fg_r, fg_g, fg_b, fg_a);
	_BatchFullSet_C32(batch_full, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G16_C32NBG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32NBG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_C32(batch_full, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G16_C32NFG_FULL(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32NFG_FULL)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFull_s* batch_full = (TuiBatchFull_s*)batch;
	if (_PointOutOfBatchFull(batch_full, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchFullGetDataIndex(batch_full, (size_t)x, (size_t)y);
	_BatchFullSet_16(batch_full, &data_index, glyph);
	_BatchFullSet_C32(batch_full, &data_index, bg_r, bg_g, bg_b, bg_a);
}

static inline TuiBoolean _PointOutOfBatchSparse(TuiBatchSparse_s* batch_sparse, size_t x, size_t y)
{
	return (x < 0 || y < 0 || x >= batch_sparse->TilesWide || y >= batch_sparse->TilesTall);
}

static inline TuiBoolean _BatchSparseTileOverflow(TuiBatchSparse_s* batch_sparse)
{
	if (!batch_sparse->UseStencil && batch_sparse->TileCount == batch_sparse->MaxTileCount)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}
static inline size_t _BatchSparseGetDataIndex(TuiBatchSparse_s* batch_sparse, size_t x, size_t y)
{
	size_t data_index;
	if (batch_sparse->UseStencil)
	{
 		size_t stencil_index = ((size_t)batch_sparse->TilesWide * y) + x;
		if (batch_sparse->StencilData[stencil_index] != 0)
		{
			data_index = batch_sparse->StencilData[stencil_index] - 1; // subtract 1 because added 1 when it was stored
			batch_sparse->TileCount++;
		}
		else //if (batch_sparse->StencilData[stencil_index] == 0)
		{
			data_index = batch_sparse->TileCount * batch_sparse->BytesPerTile;
			batch_sparse->StencilData[stencil_index] = data_index + 1; // value of 0 means no stencil, so add one so first tile is not 0
			batch_sparse->TileCount++;
		}
	}
	else //if (!batch_sparse->UseStencil)
	{
		data_index = batch_sparse->TileCount * batch_sparse->BytesPerTile;
		batch_sparse->TileCount++;
	}
	return data_index;
}

static inline void _BatchSparseSetCoordinate(TuiBatchSparse_s* batch_sparse, size_t* data_index, unsigned int x, unsigned int y)
{
	batch_sparse->Data[(*data_index)++] = x & 0xff; // first 8 bits
	if (batch_sparse->HasLargeXCoordinate)
	{
		batch_sparse->Data[(*data_index)++] = (x >> 8) & 0xff; // second 8 bits if large x coordinate
	}
	batch_sparse->Data[(*data_index)++] = y & 0xff; // first 8 bits
	if (batch_sparse->HasLargeYCoordinate)
	{
		batch_sparse->Data[(*data_index)++] = (y >> 8) & 0xff; // second 8 bits if large y coordinate
	}
}

static inline void _BatchSparseSet_8(TuiBatchSparse_s* batch_sparse, size_t* data_index, uint8_t value)
{
	batch_sparse->Data[(*data_index)++] = value;
}

static inline void _BatchSparseSet_16(TuiBatchSparse_s* batch_sparse, size_t* data_index, uint16_t value)
{
	batch_sparse->Data[(*data_index)++] = (value) & 0xff; // first 8 bits
	batch_sparse->Data[(*data_index)++] = (value >> 8) & 0xff; // second 8 bits
}

static inline void _BatchSparseSet_C24(TuiBatchSparse_s* batch_sparse, size_t* data_index, uint8_t r, uint8_t g, uint8_t b)
{
	batch_sparse->Data[(*data_index)++] = r;
	batch_sparse->Data[(*data_index)++] = g;
	batch_sparse->Data[(*data_index)++] = b;
}

static inline void _BatchSparseSet_C32(TuiBatchSparse_s* batch_sparse, size_t* data_index, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	batch_sparse->Data[(*data_index)++] = r;
	batch_sparse->Data[(*data_index)++] = g;
	batch_sparse->Data[(*data_index)++] = b;
	batch_sparse->Data[(*data_index)++] = a;
}

void tuiBatchSetTile_G0_C8NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t fg)
{
 	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C8NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, fg);
}

void tuiBatchSetTile_G0_C24NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C24NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_C24(batch_sparse, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G0_C32NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C32NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_C32(batch_sparse, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G8_C0_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C0_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
}

void tuiBatchSetTile_G8_C4_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t colors)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C4_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_8(batch_sparse, &data_index, colors);
}

void tuiBatchSetTile_G8_C8_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_8(batch_sparse, &data_index, fg);
	_BatchSparseSet_8(batch_sparse, &data_index, bg);
}

void tuiBatchSetTile_G8_C8NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_8(batch_sparse, &data_index, fg);
}

void tuiBatchSetTile_G8_C8NFG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8NFG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_8(batch_sparse, &data_index, bg);
}

void tuiBatchSetTile_G8_C24_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C24(batch_sparse, &data_index, fg_r, fg_g, fg_b);
	_BatchSparseSet_C24(batch_sparse, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G8_C24NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C24(batch_sparse, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G8_C24NFG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24NFG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C24(batch_sparse, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G8_C32_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C32(batch_sparse, &data_index, fg_r, fg_g, fg_b, fg_a);
	_BatchSparseSet_C32(batch_sparse, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G8_C32NBG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C32(batch_sparse, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G8_C32NFG_SPARSE(TuiBatch batch, int x, int y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32NFG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_8(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C32(batch_sparse, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G16_C0_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C0_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
}

void tuiBatchSetTile_G16_C4_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t colors)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C4_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_16(batch_sparse, &data_index, colors);
}

void tuiBatchSetTile_G16_C8_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_16(batch_sparse, &data_index, fg);
	_BatchSparseSet_16(batch_sparse, &data_index, bg);
}

void tuiBatchSetTile_G16_C8NBG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_16(batch_sparse, &data_index, fg);
}

void tuiBatchSetTile_G16_C8NFG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8NFG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_16(batch_sparse, &data_index, bg);
}

void tuiBatchSetTile_G16_C24_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C24(batch_sparse, &data_index, fg_r, fg_g, fg_b);
	_BatchSparseSet_C24(batch_sparse, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G16_C24NBG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C24(batch_sparse, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G16_C24NFG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24NFG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C24(batch_sparse, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G16_C32_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C32(batch_sparse, &data_index, fg_r, fg_g, fg_b, fg_a);
	_BatchSparseSet_C32(batch_sparse, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G16_C32NBG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32NBG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C32(batch_sparse, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G16_C32NFG_SPARSE(TuiBatch batch, int x, int y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32NFG_SPARSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchSparse_s* batch_sparse = (TuiBatchSparse_s*)batch;
	if (_BatchSparseTileOverflow(batch_sparse))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchSparse(batch_sparse, (size_t)x, (size_t)y))
	{
		return;
	}

	size_t data_index = _BatchSparseGetDataIndex(batch_sparse, (size_t)x, (size_t)y);
	_BatchSparseSetCoordinate(batch_sparse, &data_index, (unsigned int)x, (unsigned int)y);
	_BatchSparseSet_16(batch_sparse, &data_index, glyph);
	_BatchSparseSet_C32(batch_sparse, &data_index, bg_r, bg_g, bg_b, bg_a);
}

static inline TuiBoolean _PointOutOfBatchFree(TuiBatchFree_s* batch_free, int x, int y)
{
	return (x < -batch_free->TilePixelWidth || y < -batch_free->TilePixelHeight || x >= batch_free->DrawViewportWidth || y >= batch_free->DrawViewportHeight);
}

static inline TuiBoolean _BatchFreeTileOverflow(TuiBatchFree_s* batch_free)
{
	return batch_free->TileCount == batch_free->MaxTileCount;
}
static inline size_t _BatchFreeGetDataIndex(TuiBatchFree_s* batch_free)
{
	size_t data_index = batch_free->TileCount * batch_free->BytesPerTile;
	batch_free->TileCount++;
	return data_index;
}

static inline void _BatchFreeSetPosition(TuiBatchFree_s* batch_free, size_t* data_index, int pixel_x, int pixel_y)
{
	unsigned int unsigned_pixel_x = (unsigned int)(pixel_x + batch_free->TilePixelWidth);
	unsigned int unsigned_pixel_y = (unsigned int)(pixel_y + batch_free->TilePixelHeight);
	batch_free->Data[(*data_index)++] = unsigned_pixel_x & 0xff; // first 8 bits of x
	batch_free->Data[(*data_index)++] = (unsigned_pixel_x >> 8) & 0xff; // second 8 bits of x
	batch_free->Data[(*data_index)++] = unsigned_pixel_y & 0xff; // first 8 bits of x
	batch_free->Data[(*data_index)++] = (unsigned_pixel_y >> 8) & 0xff; // second 8 bits of y
}

static inline void _BatchFreeSet_8(TuiBatchFree_s* batch_free, size_t* data_index, uint8_t value)
{
	batch_free->Data[(*data_index)++] = value;
}

static inline void _BatchFreeSet_16(TuiBatchFree_s* batch_free, size_t* data_index, uint16_t value)
{
	batch_free->Data[(*data_index)++] = (value) & 0xff; // first 8 bits
	batch_free->Data[(*data_index)++] = (value >> 8) & 0xff; // second 8 bits
}

static inline void _BatchFreeSet_C24(TuiBatchFree_s* batch_free, size_t* data_index, uint8_t r, uint8_t g, uint8_t b)
{
	batch_free->Data[(*data_index)++] = r;
	batch_free->Data[(*data_index)++] = g;
	batch_free->Data[(*data_index)++] = b;
}

static inline void _BatchFreeSet_C32(TuiBatchFree_s* batch_free, size_t* data_index, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	batch_free->Data[(*data_index)++] = r;
	batch_free->Data[(*data_index)++] = g;
	batch_free->Data[(*data_index)++] = b;
	batch_free->Data[(*data_index)++] = a;
}

void tuiBatchSetTile_G0_C8NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C8NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, fg);
}

void tuiBatchSetTile_G0_C24NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C24NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_C24(batch_free, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G0_C32NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G0_C32NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_C32(batch_free, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G8_C0_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C0_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
}

void tuiBatchSetTile_G8_C4_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t colors)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C4_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, colors);
}

void tuiBatchSetTile_G8_C8_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t fg, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, fg);
	_BatchFreeSet_8(batch_free, &data_index, bg);
}

void tuiBatchSetTile_G8_C8NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, fg);
}

void tuiBatchSetTile_G8_C8NFG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C8NFG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, bg);
}

void tuiBatchSetTile_G8_C24_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_C24(batch_free, &data_index, fg_r, fg_g, fg_b);
	_BatchFreeSet_C24(batch_free, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G8_C24NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_C24(batch_free, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G8_C24NFG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C24NFG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_C24(batch_free, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G8_C32_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_C32(batch_free, &data_index, fg_r, fg_g, fg_b, fg_a);
	_BatchFreeSet_C32(batch_free, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G8_C32NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_C32(batch_free, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G8_C32NFG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint8_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G8_C32NFG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_8(batch_free, &data_index, glyph);
	_BatchFreeSet_C32(batch_free, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G16_C0_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C0_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
}

void tuiBatchSetTile_G16_C4_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t colors)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C4_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, colors);
}

void tuiBatchSetTile_G16_C8_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t fg, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, fg);
	_BatchFreeSet_8(batch_free, &data_index, bg);
}

void tuiBatchSetTile_G16_C8NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t fg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, fg);
}

void tuiBatchSetTile_G16_C8NFG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t bg)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C8NFG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_8(batch_free, &data_index, bg);
}

void tuiBatchSetTile_G16_C24_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_C24(batch_free, &data_index, fg_r, fg_g, fg_b);
	_BatchFreeSet_C24(batch_free, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G16_C24NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_C24(batch_free, &data_index, fg_r, fg_g, fg_b);
}

void tuiBatchSetTile_G16_C24NFG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C24NFG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_C24(batch_free, &data_index, bg_r, bg_g, bg_b);
}

void tuiBatchSetTile_G16_C32_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_C32(batch_free, &data_index, fg_r, fg_g, fg_b, fg_a);
	_BatchFreeSet_C32(batch_free, &data_index, bg_r, bg_g, bg_b, bg_a);
}

void tuiBatchSetTile_G16_C32NBG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t fg_r, uint8_t fg_g, uint8_t fg_b, uint8_t fg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32NBG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_C32(batch_free, &data_index, fg_r, fg_g, fg_b, fg_a);
}

void tuiBatchSetTile_G16_C32NFG_FREE(TuiBatch batch, int pixel_x, int pixel_y, uint16_t glyph, uint8_t bg_r, uint8_t bg_g, uint8_t bg_b, uint8_t bg_a)
{
	if (batch == TUI_NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (batch->DetailMode != TUI_DETAIL_MODE_G16_C32NFG_FREE)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_FUNCTION, __func__);
		return;
	}
	TuiBatchFree_s* batch_free = (TuiBatchSparse_s*)batch;
	if (_BatchFreeTileOverflow(batch_free))
	{
		tuiDebugError(TUI_ERROR_BATCH_OVERFLOW, __func__);
		return;
	}
	if (_PointOutOfBatchFree(batch_free, (size_t)pixel_x, (size_t)pixel_y))
	{
		return;
	}

	size_t data_index = _BatchFreeGetDataIndex(batch_free);
	_BatchFreeSetPosition(batch_free, &data_index, (unsigned int)pixel_x, (unsigned int)pixel_y);
	_BatchFreeSet_16(batch_free, &data_index, glyph);
	_BatchFreeSet_C32(batch_free, &data_index, bg_r, bg_g, bg_b, bg_a);
}