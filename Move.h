#include "Chess.h"

class Move
{
	/*
	* This class creates objects that can be used in the MoveList struct
	*/
	public:
	Chess* piece_;
    std::string pieceIdentifier;
	Position* oldPos_;
	Position* newPos_;
	bool deliversCheck;
	bool deliversMate;

	Move(Chess* piece, std::string move);
    Move(Chess* piece, Position* newPos_, bool takes, bool checks, bool mates);
    ~Move();

    //static void Move::checkMove(Chess** board[8], std::string m, globalEnums::chessColor color); //NOTE: issue with being static and trying to make it universal: by making it nonstatic, we can just add it to the constructor
    bool checkMove(Chess** board[8], Chess* piece, std::string move);
    bool checkMove(Chess** board[8], std::string m, globalEnums::chessColor color);
};

/*
* This class is used to create vectors of moves that can be used in order to hold the potential moves that pieces could make
* One object will be created for White and one for Black, and these objects will hold the moves that could be made
* These objects will be quite basic, holding just the color of the pieces and the vector for the moves, but will be used to check if a Move that the player wants to play is in the list
* * * * Further building: we could create a vector to hold the potential moves and potential LOS's that would exist after a move (i.e. check if the move adds control or space on the board or reduces it)
*/
class MoveVector
{
    globalEnums::chessColor color_;
	std::vector<Move> vecMove_;

    public:
        //constructor
    MoveVector(globalEnums::chessColor color);
        //getter methods
    globalEnums::chessColor GetColor();
    vector<Move>& GetMoveVector();
    int FindMove(Move& m);
    Move& Get(int index);
        //push_back methods
    void push_back(Move& m);
    void clear();
};