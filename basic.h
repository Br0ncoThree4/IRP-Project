/*
	Header file that holds all the basic classes that the other classes will use
*/
#include <string>
#include <list>
#include <array>
#include <cstdlib>//includes rand() method
#include <unordered_map>
#include <vector>
#include <algorithm> //includes find() function for the vector


class Position
{
	public:
    char file;
    int rank;

    Position::Position();
	Position::Position(char f, int r);
	Position::operator bool();
    Chess* Position::PosToPiece(Chess*** board);
};

class PositionVector
{
    globalEnums::chessColor color_;
	std::vector<Position*> vecPos_;

    public:

    
        //constructors
    PositionVector();
    PositionVector(globalEnums::chessColor color);
        //getter methods
    globalEnums::chessColor GetColor();
    vector<Position*>& GetPositionVector();
    Position* PositionVector::getPosition(int index);
    int PositionInVector(Position*& p);
        //push_back methods
    void push_back(Position* p);
    void clear();
};

class globalEnums{
    public:
    enum chessColor
    {
	    White = 1,
	    Black = 2,
        BLANK_COLOR = 0,
	    NULL_COLOR = -1
    };

    enum chessType
    {
        Pawn = 1,
        Rook = 2,
        Knight = 3,
        Bishop = 4,
        Queen = 5,
        King = 6,
        BLANK_TYPE = 0,
        NULL_TYPE = -1
    };

    enum direction
    {
        vertical = 0,
        diagonalURBL = 1,
        horizontal = 2,
        diagonalBRUL = 3
    };

    std::unordered_map <char, globalEnums::chessType> charToType = {{'N' , globalEnums::Knight}, 
                                                                    {'B' , globalEnums::Bishop}, 
                                                                    {'R' , globalEnums::Rook}, 
                                                                    {'Q' , globalEnums::Queen}, 
                                                                    {'K' , globalEnums::King}, 
                                                                    {' ' , globalEnums::Pawn}};
};
