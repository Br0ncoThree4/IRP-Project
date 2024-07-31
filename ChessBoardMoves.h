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
        Chess* board[8][8];
        bool whiteKingInCheck;
        bool blackKingInCheck;
		string alphabet = "abcdefgh";
        list<Chess*> blackPieces;
        list<Chess*> whitePieces;
        list<Chess*> blankSquares;
        bool MoveWentThrough;
        MoveVector possibleWhiteMoves;
        MoveVector possibleBlackMoves;

    public:
        ChessBoardMoves();
        ChessBoardMoves(list<Chess>);
        Chess* board[8][8];
        bool kingInCheck; //Checks if king is in check
		static string alphabet;
		list<string> checkKingMoves(Chess);
		list<string> checkRookMoves(Chess);
		list<string> checkBishopMoves(Chess);
		list<string> checkKnightMoves(Chess);
		list<string> checkQueenMoves(Chess);
		list<string> checkPawnMoves(Chess);
		//LegalMove(Chess, string);
		//Move(Chess, string);
		bool IsOnBoard(string);
		MoveVector FindMoves(Chess*);
		list<Move> StartingMoves();

        ChessBoardMoves::ChessBoardMoves();

        ChessBoardMoves::ChessBoardMoves(list<Chess*> pieceList);
        //we also need a printing method for the chess board
    //ChessMoves insert here

	void ChessBoardMoves::Move(Chess* piece, Position newPosition);

	bool ChessBoardMoves::IsBlockingCheck(Chess* piece); //will return true if the piece is blocking check or false if it is not

	bool IsInCheck(Chess king, list<string> possibleMoves); //See if king is in check (possibleMoves is the list of moves of the opposite color than the king)

	static bool IsOnBoard(string position);
	static bool IsOnBoard(int rank, int file);

	list<string> checkKingMoves(Chess* piece); // will return K*file letter**rank number (as a string)*
	list<string> checkQueenMoves(Chess* piece);
	list<string> checkBishopMoves(Chess* piece); //will return B*file letter**rank number (as string)*
	list<string> checkKnightMoves(Chess* piece); //Will return Ng1f3
	list<string> checkRookMoves(Chess* piece);
	list<string> checkPawnMoves(Chess* piece);

	/**
	 * void ChessBoardMoves::LegalMove(Chess piece, string newPosition)//Make sure move isn't out of bounds or creating a check
	{
		///Finding list of legal moves, depending on each piece
		if (type == "King")
		{
			list<string> possibleMoves(checkKingMoves(this));
			
		}
		else if (type == "Queen")
		{
			list<string> possibleMoves(checkQueenMoves(this));

		}
		else if (type == "Bishop")
		{
			list<string> possibleMoves(checkBishopMoves(this));

		}
		else if (type == "Knight")
		{
			list<string> possibleMoves(checkKnightMoves(this));

		}
		else if (type == "Rook")
		{
			list<string> possibleMoves(checkRookMoves(this));

		}
		else if (type == "Pawn")
		{
			list<string> possibleMoves(checkPawnMoves(this));

		}


		while (true) {
			for (int k = 0; k < possibleMoves.size(), k++) {
				if (possibleMoves[k] == newPosition)
				{
					piece.SetPosition(newPosition);
					"Your move " << piece.GetType() << newPosition << " was played";
					break;
				}
			}
		}

	}


	//other legalMove method--

	void ChessMoves::legalMove(Chess piece, string loc)
	{
		if (piece.GetType() == "King") {
			//checkKingMoves(piece);
			//if() //Make sure king isn't in check after move
		}
		else if (piece.GetType() == "Queen") {
			//checkQueenMoves(piece);
		}
		else if (piece.GetType() == "Bishop") {
			//checkBishopMoves(piece);
		}
		else if (piece.GetType() == "Knight") {
			//checkKnightMoves(piece);
		}
		else if (piece.GetType() == "Rook") {
			//checkRookMoves(piece);
		}
		else if (piece.GetType() == "Pawn") {
			//checkPawnMoves(piece);
		}
		
	}
	 * 
	 */

    PositionVector lineOfSight(Chess* piece);

    PositionVector lineOfSight(globalEnums::chessColor color);//intakes color, returns the squares that are getting watched by the other color(could be moved to by those pieces)

    bool SameFile(string move, string file);
    bool SameRank(string move, int rank);
    list<string> movesOutOfCheck(string color, list<string> possibleMoves);
	void LegalMove(Chess* piece, string newPosition); //Make sure move isn't out of bounds or creating a check
	list<string> FindMoves(Chess* piece);
	list<string> TotalPossibleMoves(string color);
	static int ChangeLetterToNumber(string letter); //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)

    string WhiteMove(Chess king, list<string> blackPossibleMoves); //computer is white and makes a move (takes other color's moves to make sure it's not in check)
    string BlackMove(Chess king, list<string> whitePossibleMoves); //computer is black and makes a move (takes other color's moves to make sure it's not in check)
    void NormalPlay();
};
