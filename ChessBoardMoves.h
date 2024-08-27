#include "Move.h"

using namespace std;
#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include <array>
#include <cstdlib>//includes rand() method
#include <unordered_map>
#include "Move.cpp"
#ifndef NULL
#define NULL 0
#endif

class ChessBoardMoves//doesn't need to be child class of Chess bc it inherits it
{
    private:
        ChessBoard board;
		string alphabet = "abcdefgh";
        bool MoveWentThrough;
        MoveVector possibleWhiteMoves;
        MoveVector possibleBlackMoves;
        globalEnums::chessColor colorToMove;

    public:
        ChessBoardMoves();
        ChessBoardMoves(list<Chess>);
        bool kingInCheck; //Checks if king is in check
		static string alphabet;
		//LegalMove(Chess, string);
		//Move(Chess, string);
		MoveVector FindMoves(Chess*);
		list<Move> StartingMoves();

        ChessBoardMoves::ChessBoardMoves();

        ChessBoardMoves::ChessBoardMoves(list<Chess*> pieceList);
        //we also need a printing method for the chess board
    //ChessMoves insert here

	void ChessBoardMoves::Move(Chess* piece, Position newPosition);

	bool ChessBoardMoves::IsBlockingCheck(Chess* piece); //will return true if the piece is blocking check or false if it is not

	bool IsInCheck(Chess king, list<string> possibleMoves); //See if king is in check (possibleMoves is the list of moves of the opposite color than the king)

	MoveVector checkKingMoves(Chess* piece); // will return K*file letter**rank number (as a string)*
	MoveVector checkQueenMoves(Chess* piece);
	MoveVector checkBishopMoves(Chess* piece); //will return B*file letter**rank number (as string)*
	MoveVector checkKnightMoves(Chess* piece); //Will return Ng1f3
	MoveVector checkRookMoves(Chess* piece);
	MoveVector checkPawnMoves(Chess* piece);

    PositionVector lineOfSight(Chess* piece);

    PositionVector lineOfSight(globalEnums::chessColor color);//intakes color, returns the squares that are getting watched by the other color(could be moved to by those pieces)

    bool SameFile(string move, string file);
    bool SameRank(string move, int rank);
    //MoveVector movesOutOfCheck(string color, list<string> possibleMoves); //if we want this, the function will need to be redone
	// list<string> FindMoves(Chess* piece);
	// list<string> TotalPossibleMoves(string color);

    void NormalPlay();
};
