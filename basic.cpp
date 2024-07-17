#include "basic.h"
#include <iostream>

using namespace std;
/*
	Class that holds the position
*/
class Position
{
	public:

	int rank;
	char file;

	Position::Position(char f, int r) : file(f), rank(r) {}
	Position::operator bool() {return 'a' <= file && 'h' >= file && 0 <= rank && 7 >= rank;} // NOTE: should be used as if(!pos) {bad stuff}
};

class globalFunctions
{


    void breakDownMove(std::string move, Position& pos, globalEnums::chessType& type, globalEnums::chessColor color)
    {
        char t = move[0];
        if(t < 'A') //If the char is a number, then it would be less than 'A', and therefore the type is a pawn
        {
            type = globalEnums::chessType::Pawn;
        }
        else
        {
            type = charToChessType[t]; //charToChessType is equal to moveToType
        }

        Position newPosition()
    }

    std::unordered_map <char, globalEnums::chessType> moveToType = {{'N' , globalEnums::Knight}, 
                {'B' , globalEnums::Bishop}, 
                {'R' , globalEnums::Rook}, 
                {'Q' , globalEnums::Queen}, 
                {'K' , globalEnums::King}, 
                {' ' , globalEnums::Pawn}};
};