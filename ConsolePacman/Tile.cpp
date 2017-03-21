#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile( TileType tileType )
{
    this->tileType = tileType;
    this->unit = NULL;
}

Tile::~Tile()
{

}

void Tile::SetTileType( TileType p_tileType, Unit* const p_unit )
{
    if ( p_tileType == tileType )
        return;

    if ( tileType == UnitType )
        unit = NULL;

    tileType = p_tileType;

    if ( tileType == UnitType )
        unit = p_unit;
}

char Tile::GetTileChar( WallFlag p_wallFlag )
{
    switch ( p_wallFlag )
    {
        case -1:
            return char( 158 ); // ₧
        case 0:
            return ' ';
        case WallRight:
        case WallLeft:
        case WallHorizontal:
            return (char)196; // ─ 
        case WallDown:
        case WallUp:
        case WallVertical:
            return (char)179; // │ 
        case WallLeftBottomCorner:
            return (char)192; // └ 
        case WallRightBottomCorner:
            return (char)217; // ┘
        case WallLeftUpCorner:
            return (char)218; // ┌
        case WallRightUpCorner:
            return (char)191; // ┐
        case WallHorizontalDown:
            return (char)194; // ┬ 
        case WallHorizontalUp:
            return (char)193; // ┴ 
        case WallVerticalRight:
            return (char)195; // ├ 
        case WallVerticalLeft:
            return (char)180; // ┤ 
        case WallCross:
            return (char)197; // ┼ 
    }
}
