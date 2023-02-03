#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include "ChessBoard.cpp"
#include "ChessMoves.cpp"
#ifndef NULL
#define NULL 0
#endif
using namespace std;

class Tester : public ChessBoard
{


//want to play chess here: import all other files and game
int main()
{
    std::list<Chess> startingPieces = Chess.Setup();
    std::ChessBoard.Board(startingPieces); //creates board, printing out array of chess piece color and type or the square number, if the square is empty
};

};;