#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <fstream>

#define right(x) (x + 1) % width
#define left(x) (x - 1 + width) % width
#define up(y) (y - 1 + height) % height
#define down(y) (y + 1) % height

using namespace std;

Board::Board( size_t width, size_t height )
{
    this->width = width;
    this->height = height;

    tiles = make_unique<Tile[]>( width * height );

    for ( size_t x = 0; x < width; ++x )
        for ( size_t y = 0; y < height; ++y )
            tiles.get()[ x + y * width ] = Tile( Wall );

    // Units
    pacMan = PacMan();
    enemy1 = Enemy();
    enemy2 = Enemy();
}

Board::~Board()
{

}

inline Tile* Board::GetTileAt( size_t x, size_t y ) const
{
    return &tiles.get()[ x + y * width ];
}

WallFlag Board::GetWallFlag( size_t x, size_t y ) const
{
    if ( GetTileAt( x, y )->GetTileType() == Free )
        return (WallFlag)0;
    if ( GetTileAt( x, y )->GetTileType() == Orb )
        return (WallFlag)( -1 );

    int _flags = 0;

    // Left
    if ( x > 0 && GetTileAt( x - 1, y )->GetTileType() == Wall )
        _flags |= WallLeft;

    // Right
    if ( x < width - 1 && GetTileAt( x + 1, y )->GetTileType() == Wall )
        _flags |= WallRight;

    // Up
    if ( y > 0 && GetTileAt( x, y - 1 )->GetTileType() == Wall )
        _flags |= WallUp;

    // Down
    if ( y < height - 1 && GetTileAt( x, y + 1 )->GetTileType() == Wall )
        _flags |= WallDown;

    return (WallFlag)_flags;
}

bool Board::IsEmptyAt( size_t x, size_t y ) const
{
    return !GetTileAt( x, y )->GetTileType() == Free;
}

void Board::SetUnit( Unit* unit, size_t x, size_t y )
{
    // Free old tile
    GetTileAt( unit->GetX(), unit->GetY() )->SetTileType( Free, NULL );

    // Update pos of unit
    unit->SetPos( x, y );

    // Occupy new tile
    GetTileAt( x, y )->SetTileType( UnitType, unit );
}

void Board::Fill()
{
    // Random walk
    int _dir = 0;
    int x = 0;
    int y = 0;
    for ( uint8_t i = 0; i < 20; i++ )
    {
        _dir = ( rand() % 2 ) + 2 * ( i % 2 );

        int _dist = 8 + ( rand() % 8 );
        for ( uint8_t j = 0; j < _dist; j++ )
        {
            GetTileAt( x, y )->SetTileType( Free, NULL );

            switch ( _dir )
            {
                case Direction::Right: // Right
                    x = Right( x );
                    break;
                case Direction::Left: // Left
                    x = Left( x );
                    break;
                case Direction::Down: // Down
                    y = Down( y );
                    break;
                case Direction::Up: // Up
                    y = Up( y );
                    break;
                default:
                    break;
            }
        }
    }

    SetUnit( &enemy1, 0, 0 );
    SetUnit( &enemy2, 0, 0 );
    SetUnit( &pacMan, 1, 0 );
}

void Board::Draw() const
{
    // Clear screen
    COORD cur = { 0, 0 };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), cur );

    string _string( ( width + 1 ) * height, ' ' );

    for ( size_t y = 0; y < height; y++ )
    {
        for ( size_t x = 0; x < width; x++ )
        {
            if ( GetTileAt( x, y )->GetTileType() == UnitType )
                _string[ x + y * ( width + 1 ) ] = GetTileAt( x, y )->unit->GetChar();
            else
                _string[ x + y * ( width + 1 ) ] = Tile::GetTileChar( GetWallFlag( x, y ) );
        }

        _string[ width + y * ( width + 1 ) ] = '\n';
    }

    cout << _string << endl;
}

void Board::Update()
{
    pacMan.Update( this );
    enemy1.Update( this );
    enemy2.Update( this );
}

void Board::FixedUpdate()
{
    pacMan.FixedUpdate( this );
    enemy1.FixedUpdate( this );
    enemy2.FixedUpdate( this );
}

void Board::AdvanceUnit( Unit* p_unit )
{
    switch ( p_unit->GetDir() )
    {
        case Direction::Right:
            if ( GetTileAt( Right( p_unit->GetX() ), p_unit->GetY() )->GetTileType() != Wall )
                MoveUnitRight( p_unit );
            break;
        case Direction::Left:
            if ( GetTileAt( Left( p_unit->GetX() ), p_unit->GetY() )->GetTileType() != Wall )
                MoveUnitLeft( p_unit );
            break;
        case Direction::Down:
            if ( GetTileAt( p_unit->GetX(), Down( p_unit->GetY() ) )->GetTileType() != Wall )
                MoveUnitDown( p_unit );
            break;
        case Direction::Up:
            if ( GetTileAt( p_unit->GetX(), Up( p_unit->GetY() ) )->GetTileType() != Wall )
                MoveUnitUp( p_unit );
            break;
    }
}