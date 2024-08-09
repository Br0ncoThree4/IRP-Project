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
		PositionVector& GetPrimaryLOS();
		unordered_map<Position*, Chess*>& GetSecondaryLOS();
			//changed out for SetPosition
		// void SetFile(char);
		// void SetRank(int);
		//Move(std::string);
			//useful methods
		list<Chess*> Setup(); //NOTE: could move this to the ChessBoard class
		// int ChangeLetterToNumber(std::string);
		void SetPosition(Chess** board[8], Chess* blankPiece, Position* newPosition);
};

class ChessBoard
{
	Chess* _board[8][8]; //the chess board: 2D array
	bool whiteKingInCheck;
    bool blackKingInCheck;
	list<Chess*> blackPieces;
    list<Chess*> whitePieces;
	PositionVector _whitePrimaryLOS; //the positions that white pieces can see/move to
	PositionVector _blackPrimaryLOS; //the positions that white pieces can see/move to
	unordered_map<Position*, Chess*> _whiteSecondaryLOS; //the positions that could be seen/moved to if the Chess* moves
	unordered_map<Position*, Chess*> _blackSecondaryLOS; //the positions that could be seen/moved to if the Chess* moves

	public:
		//getter methods
	Chess*** GetBoard(); //returns the board
	PositionVector& GetWhitePLOS(); //returns _whitePrimaryLOS
	PositionVector& GetBlackPLOS(); //returns _blackPrimaryLOS
	unordered_map<Position*, Chess*> GetWhiteSLOS(); //returns _whiteSecondaryLOS
	unordered_map<Position*, Chess*> GetBlackSLOS(); //returns _blackSecondaryLOS
		//other useful methods
};