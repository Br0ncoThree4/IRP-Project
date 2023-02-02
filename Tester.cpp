#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include "ChessBoard.cpp"
#include "ChessMoves.cpp"
using namespace std;

//want to play chess here: import all other files and game
int main()
{
    ChessBoard.Board(Chess.Setup()); //creates board, printing out array of chess piece color and type or the square number, if the square is empty
};