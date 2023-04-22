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
int main(){
        Chess baseObj;
        ChessBoardMoves board;
        std::list<Chess> pieceList = baseObj.Setup();
        board = ChessBoardMoves(pieceList);//sets up board w starting pieces
        NormalPlay();








        return 0;
    }

};;