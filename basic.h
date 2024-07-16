/*
	Header file that holds all the basic classes that the other classes will use
*/
#include <string>
#include <list>
#include <array>
#include <cstdlib>//includes rand() method
#include <unordered_map>
class Position
{
	public:
    char file;
    int rank;

	Position::Position(char f, int r);
	Position::operator bool();
};

enum chessColor
{
	White = 0,
	Black = 1,
	NO_COLOR = -1
};

enum chessType
{
    Pawn = 0,
    Rook = 1,
    Knight = 2,
    Bishop = 3,
    Queen = 4,
    King = 5,
    NO_TYPE = -1
};

class globalFunctions{
    void moveToType(string move, Position& pos, )
}
