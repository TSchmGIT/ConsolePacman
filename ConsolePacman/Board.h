#pragma once

#include <vector>
#include <memory>
#include "PacMan.h"
#include "Enemy.h"
#include "Direction.h"
#include "Tile.h"

class Board
{
public:
    Board( size_t width, size_t height );
    ~Board();

    void Fill();
    void Draw() const;

    void Update();
    void FixedUpdate();
    void AdvanceUnit( Unit* unit );

    inline Tile* GetTileAt( size_t x, size_t y ) const;

    inline void MoveUnitRight( Unit* unit ) { SetUnit( unit, Right( unit->GetX() ), unit->GetY() ); }
    inline void MoveUnitLeft( Unit* unit ) { SetUnit( unit, Left( unit->GetX() ), unit->GetY() ); }
    inline void MoveUnitUp( Unit* unit ) { SetUnit( unit, unit->GetX(), Up( unit->GetY() ) ); }
    inline void MoveUnitDown( Unit* unit ) { SetUnit( unit, unit->GetX(), Down( unit->GetY() ) ); }

    inline size_t Right( size_t x ) { return ( x + 1 ) % width; }
    inline size_t Left( size_t x ) { return ( x - 1 + width ) % width; }
    inline size_t Up( size_t y ) { return ( y - 1 + height ) % height; }
    inline size_t Down( size_t y ) { return ( y + 1 ) % height; }

    PacMan pacMan;
    Enemy enemy1;
    Enemy enemy2;
private:
    std::unique_ptr<Tile[]> tiles;

    size_t width;
    size_t height;

    WallFlag GetWallFlag( size_t x, size_t y ) const;
    bool IsEmptyAt( size_t x, size_t y ) const;
    void SetUnit( Unit* unit, size_t x, size_t y );

};

