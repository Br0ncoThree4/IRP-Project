#include "basic.h"

class Chess
{
	private:
		chessColor _color;
		string _type;
		Position _pos;
		
		//checkKingMoves(Chess);
		//checkRookMoves(Chess);
		//checkBishopMoves(Chess);
		//checkKnightMoves(Chess);
		//checkQueenMoves(Chess);
		//checkPawnMoves(Chess);
	public:
		Chess(); //It is defined as being public, but it doesn't work, nor does the default constructor declaration here
		Chess(const Chess&);
		Chess(string, string, string, int);
		Chess(string);
		string GetColor();
		int GetFile();
		int GetRank();
		string GetType();
		void SetFile(string);
		void SetRank(string);
		//Move(string);
		list<Chess> Setup();
		int ChangeLetterToNumber(string);
};