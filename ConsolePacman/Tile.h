#pragma once

#include "stdafx.h"
#include "Unit.h"

enum WallFlag
{
    WallRight = 1 << 0,
    WallLeft = 1 << 1,
    WallDown = 1 << 2,
    WallUp = 1 << 3,

    WallHorizontal = WallRight | WallLeft,
    WallVertical = WallDown | WallUp,

    WallLeftBottomCorner = WallUp | WallRight,
    WallRightBottomCorner = WallUp | WallLeft,
    WallLeftUpCorner = WallDown | WallRight,
    WallRightUpCorner = WallDown | WallLeft,

    WallHorizontalDown = WallHorizontal | WallDown,
    WallHorizontalUp = WallHorizontal | WallUp,

    WallVerticalRight = WallVertical | WallRight,
    WallVerticalLeft = WallVertical | WallLeft,

    WallCross = WallRight | WallLeft | WallDown | WallUp
};

enum TileType
{
    Free,
    Orb,
    UnitType,
    Wall
};

class Tile
{
public:
    Tile();
    Tile( TileType tileType );
    ~Tile();

    const Unit* unit;

    inline TileType GetTileType() const { return tileType; }
    void SetTileType( TileType p_tileType, Unit* p_unit );

    static char GetTileChar( WallFlag WallRight );

private:
    TileType tileType;
};

