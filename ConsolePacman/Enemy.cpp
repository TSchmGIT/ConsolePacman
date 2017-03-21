#include "stdafx.h"
#include "Enemy.h"
#include "Board.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::FixedUpdate( Board* p_board )
{
    Unit::FixedUpdate( p_board );

    switch ( dir )
    {
        case Right:
            if ( p_board->GetTileAt( p_board->Right( GetX() ), GetY() )->GetTileType() == Wall )
                dir = (Direction)( rand() % 4 );
            break;
        case Left:
            if ( p_board->GetTileAt( p_board->Left( GetX() ), GetY() )->GetTileType() == Wall )
                dir = (Direction)( rand() % 4 );
            break;
        case Down:
            if ( p_board->GetTileAt( GetX(), p_board->Down( GetY() ) )->GetTileType() == Wall )
                dir = (Direction)( rand() % 4 );
            break;
        case Up:
            if ( p_board->GetTileAt( GetX(), p_board->Up( GetY() ) )->GetTileType() == Wall )
                dir = (Direction)( rand() % 4 );
            break;
        default:
            break;
    }
}

char Enemy::GetChar() const
{
    return char( 228 ); // Σ
}
