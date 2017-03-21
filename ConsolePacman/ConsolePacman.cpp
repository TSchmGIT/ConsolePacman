// ConsolePacman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <chrono>
#include "ConsolePacman.h"
#include <conio.h>
#include <Windows.h>


using namespace std;

unsigned char* ReadBMP( char* filename )
{
    int i;
    FILE* f = fopen( filename, "rb" );
    unsigned char info[ 54 ];
    fread( info, sizeof( unsigned char ), 54, f ); // read the 54-byte header

                                                   // extract image height and width from header
    int width = *(int*)&info[ 18 ];
    int height = *(int*)&info[ 22 ];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[ size ]; // allocate 3 bytes per pixel
    fread( data, sizeof( unsigned char ), size, f ); // read the rest of the data at once
    fclose( f );

    for ( i = 0; i < size; i += 3 )
    {
        unsigned char tmp = data[ i ];
        data[ i ] = data[ i + 2 ];
        data[ i + 2 ] = tmp;
    }

    return data;
}

int main()
{
    srand( time( NULL ) );
    HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo( consoleHandle, &info );

    cout << "||----------------------------||" << endl;
    cout << "|| Welcome to Console Pacman! ||" << endl;
    cout << "|/----------------------------\\|" << endl;
    cout << endl;

    do
    {
        string _input;
        cout << endl;
        cout << "Do you want to start a new game? (Y/N)" << endl;
        cin >> _input;

        if ( _input == "N" )
            break;
        else if ( _input == "Y" )
        {
            // Start game
            Board _board( 60, 20 );
            _board.Fill();
            _board.Draw();

            std::chrono::microseconds _milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() );

            while ( true )
            {
                _board.Update();

                if ( ( std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() ) - _milliseconds ).count() > 100000 )
                {
                    _board.FixedUpdate();
                    _board.Draw();

                    _milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() );
                }
            }
        }
    } while ( true );

    return 0;
}

