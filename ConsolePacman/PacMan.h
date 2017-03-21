#pragma once
#include "Unit.h"

class PacMan : public Unit
{
public:
    PacMan();
    ~PacMan();

    virtual char GetChar() const;
    virtual void Update( Board* p_board );
    virtual void FixedUpdate( Board* p_board );
};

