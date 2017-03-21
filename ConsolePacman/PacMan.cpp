#include "stdafx.h"
#include "PacMan.h"
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

PacMan::PacMan() : Unit()
{

}


PacMan::~PacMan()
{
}

char PacMan::GetChar() const
{
    return char( 224 ); // α 
}

void PacMan::Update( Board * p_board )
{
    // Base class
    Unit::Update( p_board );

    // Key checking
    if ( _kbhit() )
        switch ( _getch() )
        {
            case KEY_UP:
                SetDir( Up );
                break;
            case KEY_DOWN:
                SetDir( Down );
                break;
            case KEY_LEFT:
                SetDir( Left );
                break;
            case KEY_RIGHT:
                SetDir( Right );
                break;
            default:
                break;
        }
}

void PacMan::FixedUpdate( Board* p_board )
{
    Unit::FixedUpdate( p_board );
}
