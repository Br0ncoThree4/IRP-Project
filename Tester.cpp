using namespace std;

#include <iostream>
#include <string>
#include <list>
//#include "Chess.cpp" : don't need this bc it's included for ChessBoardMoves & throws class redefinition error if it's in
#include "ChessBoardMoves.cpp"
#ifndef NULL
#define NULL 0
#endif

class Tester : public ChessBoardMoves
{

};

//want to play chess here, import all other files and game
    int main()
    {
        std::cout.flush();
        std::cout << "running 1 .." << std::endl;
        
        Chess obj = Chess();
        std::cout << "1" << std::endl;
        list<Chess> pieceList = obj.Setup();
        std::cout << "2" << std::endl;
        ChessBoardMoves board;
        board = ChessBoardMoves(pieceList);//sets up board w starting pieces
        board.NormalPlay();
        

        return 0;
    }