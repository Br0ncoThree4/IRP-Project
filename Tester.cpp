using namespace std;

#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include "ChessBoardMoves.cpp"
#include "ChessMoves.cpp"
#ifndef NULL
#define NULL 0
#endif

class Tester : public ChessBoardMoves
{


//want to play chess here: import all other files and game
int TheMain()
{
    std::list<Chess> startingPieces = Setup();
    std::Board(startingPieces); //creates board, printing out array of chess piece color and type or the square number, if the square is empty
};

};;