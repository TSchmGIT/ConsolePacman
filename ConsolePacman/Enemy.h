#pragma once
#include "Unit.h"

class Enemy : public Unit
{
public:
    Enemy();
    ~Enemy();

    virtual void FixedUpdate( Board* p_board );
    virtual char GetChar() const;
};

