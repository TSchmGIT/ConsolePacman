#pragma once

#include "Direction.h"

class Board;

class Unit
{
public:
    Unit();
    ~Unit();

    virtual char GetChar() const = 0;

    virtual void Update( Board* p_board );
    virtual void FixedUpdate( Board* p_board );

    inline void SetPos( size_t x, size_t y ) { this->x = x; this->y = y; }

    inline size_t GetX() const { return x; }
    inline size_t GetY() const { return y; }

    inline Direction GetDir() const { return dir; }
    inline void SetDir( Direction dir ) { this->dir = dir; }
protected:
    Direction dir;
    size_t x;
    size_t y;
};