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

	Move::Move(Chess* piece, std::string move);
    Move::Move(Chess* piece, Position* newPos_, bool takes, bool checks, bool mates);
    Move::~Move();

    bool Move::checkMove(std::string m);
};

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
        //push_back methods
    void push_back(Move& m);
    void push_back(Chess* piece);
    void clear();
};