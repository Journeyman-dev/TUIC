#version 330 core
uniform ivec2 ScreenTileDimensions; //dimensions of the batch
uniform vec2 TileScreenspaceDimensions;
uniform ivec2 SheetTileDimensions;
uniform vec2 SheetTileUVDimensions;
uniform int GlyphMode; /* G0 = 0, G8 = 1, G16 = 2 */
uniform int ColorMode; /* C0 = 0, C4 = 1, C8 = 2, C8NBG = 3, C8NFG = 4, C24 = 5, C24NBG = 6, C24NFG = 7, C32 = 8, C32NBG = 9, C32NFG = 10 */
uniform int LayoutMode; /* Full = 0, Sparse = 1, Free = 2 */
uniform int AtlasType; // 0 = grid, 1 = coordinates
uniform int PaletteChannelCount; // 3 = RGB, 4 = RGBA (if no palette, ignore this)
uniform bool HasLargeXCoordinate; //if this is sparse and the x positions are two bytes instead of one
uniform bool HasLargeYCoordinate; //if this is sparse and the y positions ar etwo bytes instead of one
uniform int TileByteSize; //size of a single tile in the data array in bytes
uniform usamplerBuffer Data; //batch data buffer.
uniform samplerBuffer Fontmap; //the coordinate uv buffer if not uv grid
uniform usamplerBuffer Palette; //the palette colors
uniform mat4 Matrix; //transform matrix for entire batch
uniform uvec2 ViewportPixelDimensions; //the pixel dimensions of the viewport.
uniform uvec2 TilePixelDimensions; //the dimensions of each tile in pixels.
out vec2 UV; //uv texture position
out vec4 FG; //foreground color
out vec4 BG; //background color
vec2 getVertexUV_Grid(int ch, int tile_vertex)
{
	vec2 sheet_tile_coord;
	sheet_tile_coord.x = float(mod(ch, SheetTileDimensions.x)) / float(SheetTileDimensions.x);
	sheet_tile_coord.y = 1.0 - float(SheetTileDimensions.y - (ch / SheetTileDimensions.x)) / float(SheetTileDimensions.y);	
	vec4 uv_square = vec4(sheet_tile_coord.x, sheet_tile_coord.x + SheetTileUVDimensions.x, sheet_tile_coord.y + SheetTileUVDimensions.y, sheet_tile_coord.y);
	vec2 vert_uvs[6] = vec2[](uv_square.sp, uv_square.sq, uv_square.tq, uv_square.sp, uv_square.tq, uv_square.tp);
	vec2 uv = vert_uvs[tile_vertex];
	return uv;
}
vec2 getVertexUV_Coordinates(int ch, int tile_vertex)
{
	vec4 uv_square = texelFetch(Fontmap, ch);
	vec2 vert_uvs[6] = vec2[](uv_square.sp, uv_square.sq, uv_square.tq, uv_square.sp, uv_square.tq, uv_square.tp);
	vec2 uv = vert_uvs[tile_vertex];
	return uv;
}
vec4 getVertexPosition_Full(int tile, int tile_vertex)
{
	int tile_x = tile % ScreenTileDimensions.x;
	int tile_y = tile / ScreenTileDimensions.x;
	float tile_lx = float(tile_x) * TileScreenspaceDimensions.x;
	float tile_by = float(tile_y) * TileScreenspaceDimensions.y;
	float tile_rx = tile_lx + TileScreenspaceDimensions.x;
	float tile_ty = tile_by + TileScreenspaceDimensions.y;
	vec4 position_square = vec4(tile_lx, tile_rx, tile_ty, tile_by);
	vec2 vert_positions[6] = vec2[](position_square.sp, position_square.sq, position_square.tq, position_square.sp, position_square.tq, position_square.tp);
	vec2 position = vert_positions[tile_vertex];
	return vec4(position, 0.0, 1.0) * Matrix;
}
vec4 getVertexPosition_Sparse(int tile, int tile_vertex, inout int buffer_offset)
{
	uint tile_x = texelFetch(Data, buffer_offset).r;
	buffer_offset += 1;
	if (HasLargeXCoordinate)
	{
		tile_x += texelFetch(Data, buffer_offset).r * 256u;
		buffer_offset += 1;
	}
	uint tile_y = texelFetch(Data, buffer_offset).r;
	buffer_offset += 1;
	if (HasLargeYCoordinate)
	{
		tile_y += texelFetch(Data, buffer_offset).r * 256u;
		buffer_offset += 1;
	}
	float tile_lx = float(tile_x) * TileScreenspaceDimensions.x;
	float tile_by = float(tile_y) * TileScreenspaceDimensions.y;
	float tile_rx = tile_lx + TileScreenspaceDimensions.x;
	float tile_ty = tile_by + TileScreenspaceDimensions.y;
	vec4 position_square = vec4(tile_lx, tile_rx, tile_ty, tile_by);
	vec2 vert_positions[6] = vec2[](position_square.sp, position_square.sq, position_square.tq, position_square.sp, position_square.tq, position_square.tp);
	vec2 position = vert_positions[tile_vertex];
	return vec4(position, 0.0, 1.0) * Matrix;
}
vec4 getVertexPosition_Free(int tile, int tile_vertex, inout int buffer_offset)
{
	int tile_pixel_x = int(texelFetch(Data, buffer_offset).r);
	buffer_offset += 1;
	tile_pixel_x += int(texelFetch(Data, buffer_offset).r * 256u);
	buffer_offset += 1;
	int tile_pixel_y = int(texelFetch(Data, buffer_offset).r);
	buffer_offset += 1;
	tile_pixel_y += int(texelFetch(Data, buffer_offset).r * 256u);
	buffer_offset += 1;
	tile_pixel_x -= int(TilePixelDimensions.x);
	tile_pixel_y -= int(TilePixelDimensions.y); //To allow for tiles that go off screen on left an top, the dimensions are transformed by negative tile width and height
	float tile_pixel_lx = float(tile_pixel_x) / float(ViewportPixelDimensions.x);
	float tile_pixel_ty = float(tile_pixel_y) / float(ViewportPixelDimensions.y);
	float tile_pixel_rx = tile_pixel_lx + TileScreenspaceDimensions.x;
	float tile_pixel_by = tile_pixel_ty + TileScreenspaceDimensions.y;
	vec4 position_square = vec4(tile_pixel_lx, tile_pixel_rx, tile_pixel_ty, tile_pixel_by);
	vec2 vert_positions[6] = vec2[](position_square.sp, position_square.sq, position_square.tq, position_square.sp, position_square.tq, position_square.tp);
	vec2 position = vert_positions[tile_vertex];
	return vec4(position, 0.0, 1.0) * Matrix;
}
vec4 getPaletteColor(int index)
{
	index *= PaletteChannelCount;
	float r = float(texelFetch(Palette, index).r) / 255.0;
	float g = float(texelFetch(Palette, index + 1).r) / 255.0;
	float b = float(texelFetch(Palette, index + 2).r) / 255.0;
	float a = 1.0;
	if (PaletteChannelCount == 4)
	{
		a = float(texelFetch(Palette, index + 3).r) / 255.0;
	}
	return vec4(r, g, b, a);
}
vec4 getColor24(inout int buffer_offset)
{
	float r = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	float g = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	float b = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	return vec4(r, g, b, 1.0);	
}
vec4 getColor32(inout int buffer_offset)
{
	float r = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	float g = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	float b = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	float a = float(texelFetch(Data, buffer_offset).r) / 255.0;
	buffer_offset += 1;
	return vec4(r, g, b, 1);
}
int getGlyph8(inout int buffer_offset)
{
	int glyph = int(texelFetch(Data, buffer_offset).r);
	buffer_offset += 1;
	return glyph;
}
int getGlyph16(inout int buffer_offset)
{
	int glyph = int(texelFetch(Data, buffer_offset).r);
	buffer_offset += 1;
	glyph += int(texelFetch(Data, buffer_offset).r * 256u);
	buffer_offset += 1;
	return glyph;
}
ivec2 getColor4(inout int buffer_offset)
{
	int colors_combined = int(texelFetch(Data, buffer_offset).r);
	buffer_offset += 1;
	return ivec2(
		int(mod(colors_combined, 16)),
		colors_combined / 16
	);
}
int getColor8(inout int buffer_offset)
{
	int color = int(texelFetch(Data, buffer_offset).r);
	buffer_offset += 1;
	return color;
}
void main()
{
	int tile = gl_VertexID / 6;
	int tile_vertex = gl_VertexID % 6;
	int buffer_offset = TileByteSize * tile;
	
	if (LayoutMode == 0) //Full
	{
		gl_Position = getVertexPosition_Full(tile, tile_vertex); 
	}
	else if (LayoutMode == 1) //Sparse
	{
		gl_Position = getVertexPosition_Sparse(tile, tile_vertex, buffer_offset);
	}
	else if (LayoutMode == 2) //Free
	{
		gl_Position = getVertexPosition_Free(tile, tile_vertex, buffer_offset);
	}
	
	int glyph;
	if (GlyphMode == 0) //G0
	{
		glyph = -1;
	}
	if (GlyphMode == 1) //G8
	{
		glyph = getGlyph8(buffer_offset);
	}
	else if (GlyphMode == 2) //G16
	{
		glyph = getGlyph16(buffer_offset);
	}
	
	if (glyph == -1) //no glyph
	{
		UV = vec2(0.0f, 0.0f);
	}
	else if (AtlasType == 0) //Grid
	{
		UV = getVertexUV_Grid(glyph, tile_vertex);
	}
	else if (AtlasType == 1) //Coordinates
	{
		UV = getVertexUV_Coordinates(glyph, tile_vertex);
	}
	
	if (ColorMode == 0) //C0
	{
		FG = vec4(1.0, 1.0, 1.0, 1.0);
		BG = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else if (ColorMode == 1) //C4
	{
		ivec2 colors = getColor4(buffer_offset);
		FG = getPaletteColor(colors.x);
		BG = getPaletteColor(colors.y);
	}
	else if (ColorMode == 2) //C8
	{
		int fg_index = getColor8(buffer_offset);
		int bg_index = getColor8(buffer_offset);
		FG = getPaletteColor(fg_index);
		BG = getPaletteColor(bg_index);
	}
	else if (ColorMode == 3) //C8NBG
	{
		int fg_index = getColor8(buffer_offset);
		FG = getPaletteColor(fg_index);
		BG = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else if (ColorMode == 4) //C8NFG
	{
		int bg_index = getColor8(buffer_offset);
		FG = vec4(1.0, 1.0, 1.0, 1.0);
		BG = getPaletteColor(bg_index);
	}
	else if (ColorMode == 5) //C24
	{
		FG = getColor24(buffer_offset);
		BG = getColor24(buffer_offset);
	}
	else if (ColorMode == 6) //C24NBG
	{
		FG = getColor24(buffer_offset);
		BG = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else if (ColorMode == 7) //C24NFG
	{
		FG = vec4(1.0, 1.0, 1.0, 1.0);
		BG = getColor24(buffer_offset);
	}
	else if (ColorMode == 8) //C32
	{
		FG = getColor32(buffer_offset);
		BG = getColor32(buffer_offset);
	}
	else if (ColorMode == 9) //C32NBG
	{
		FG = getColor32(buffer_offset);
		BG = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else if (ColorMode == 10) //C32NFG
	{
		FG = vec4(1.0, 1.0, 1.0, 1.0);
		BG = getColor32(buffer_offset);
	}
}