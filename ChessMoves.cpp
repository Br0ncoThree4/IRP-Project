#include <iostream>
#include <string>
#include "Chess.cpp"
using namespace std;

class ChessMoves
{
	private:
		bool kingInCheck;
	public:
		//checkKingMoves(Chess);
		//checkRookMoves(Chess);
		//checkBishopMoves(Chess);
		//checkKnightMoves(Chess);
		//checkQueenMoves(Chess);
		//checkPawnMoves(Chess);
		//legalMove(Chess, string);
		//Move(Chess, string);
		list<string> StartingMoves();






	list<string> ChessMoves::StartingMoves() //Returns starting moves for white (can be altered to make it for black, just need to change a few latters)
	{
		list<string> moves; //White Starting Moves
		//Pawn Moves
		for(int k = 1; k <= 8; k++){
			string file = "abcdefgh"[k-1];
			moves.push_back(k + "3");
			moves.push_back(k + "4");
		}
		//Knight Moves
		for(int k = 1; k <= 2; k++){
			int startingFile = k/2*5 + 1;//gets file to be either 1 or 6 (B or G)
			int startingRow = 1;
			for(int x = -1; x <= 1; x+= 2){
				string newFile = "abcdefghijk"[startingFile + x];
				moves.push_back(k + "3");
			}
		}
		return moves;
	}


	void ChessMoves::legalMove(Chess piece, string loc)
	{
		if (piece.GetType() == "King") {
			//checkKingMoves(piece);
			if() //Make sure king isn't in check after move
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


	static void ChessMoves::Move(Chess piece, string newPosition) {
		int newFile = ChangeLetterToNumber(newPosition.substr(0, 1));
		int newFile = int(newPosition.substr(1, 1));

		//Check for legal move depending on piece and making sure they don't create a check on their own king by doing so

		file = newFile;
		rank = newRank;
	}

	bool ChessMoves::IsInCheck(Chess King)//See if king is in check
	{
		string colorOfKing = King.GetColor();
		if (colorOfKing == "White") {
			if()
		}
	}

	list<string> ChessMoves::checkKingMoves(Chess piece)
	{
		int currentFile = piece.GetFile();
		int currentRow = piece.GetRow();

		std::list<string> possibleMoves();
		
		
	}

	list<string> ChessMoves::checkQueenMoves(Chess piece)
	{
		if (piece.GetType() != "Queen") {
			cout << "Your piece is not a Queen, like the computer thought it was, the piece is a " << piece.GetType() << ".";
			break;
		}
		std::list<string> possibleMoves();
		
		
	}

	/**
	 * void ChessMoves::LegalMove(Chess piece, string newPosition)//Make sure move isn't out of bounds or creating a check
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
	 * 
	 */

	static int ChessMoves::ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
		string str = "abcdefgh";
		return str.find_first_of(letter) + 1;
};
