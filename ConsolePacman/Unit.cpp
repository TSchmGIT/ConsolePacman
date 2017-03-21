#include "stdafx.h"
#include "Unit.h"
#include "Board.h"

Unit::Unit()
{
    dir = Right;
    x = 0;
    y = 0;
}


Unit::~Unit()
{
}

void Unit::Update( Board * p_board )
{

}

void Unit::FixedUpdate( Board* p_board )
{
    p_board->AdvanceUnit( this );
}
