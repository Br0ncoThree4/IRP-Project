#include "basic.h"

class Chess
{
	private:
		globalEnums::chessColor _color;
		globalEnums::chessType _type;
		Position* _pos;
		static const Position* blankPosition;
		std::unordered_map <char, globalEnums::chessType> charToType = 
		{{'N' , globalEnums::Knight}, 
        {'B' , globalEnums::Bishop}, 
        {'R' , globalEnums::Rook}, 
        {'Q' , globalEnums::Queen}, 
        {'K' , globalEnums::King}, 
    	{' ' , globalEnums::Pawn}};
		PositionVector _primaryLOS;
		unordered_map<Position*, Chess*> _secondaryLOS;
		
		//checkKingMoves(Chess);
		//checkRookMoves(Chess);
		//checkBishopMoves(Chess);
		//checkKnightMoves(Chess);
		//checkQueenMoves(Chess);
		//checkPawnMoves(Chess);
	public:
			//constructors and destructor
		Chess(); //It is defined as being public, but it doesn't work, nor does the default constructor declaration here
		Chess(const Chess&);
		Chess(globalEnums::chessColor, globalEnums::chessType, char, int);
		Chess(std::string);
		~Chess(); //made at the end of the class
			//getter methods
		globalEnums::chessColor GetColor();
		globalEnums::chessType GetType();
		char GetFile();
		int GetRank();
		Position* GetPosition();
			//changed out for SetPosition
		// void SetFile(char);
		// void SetRank(int);
		//Move(std::string);
			//useful methods
		list<Chess*> Setup();
		// int ChangeLetterToNumber(std::string);
		void SetPosition(Chess** board[8], Chess* blankPiece, Position* newPosition);
};