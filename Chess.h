#include "basic.h"

class Chess
{
	protected:
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
		PositionVector _primaryLOS; //holds the info of what the pieces can see (where the King cannot be)
		unordered_map<Position*, Chess*> _secondaryLOS; //holds the info of what the pieces could see if a piece moved
		
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
		// Chess(char f, int r);
		~Chess(); //made at the end of the class
			//getter methods
		globalEnums::chessColor GetColor();
		globalEnums::chessType GetType();
		char GetFile();
		int GetRank();
		Position* GetPosition();
		PositionVector& GetPrimaryLOS();
		unordered_map<Position*, Chess*>& GetSecondaryLOS();
		globalEnums::chessColor GetConstColor() const;
		globalEnums::chessType GetConstType() const;
		char GetConstFile() const;
		int GetConstRank() const;
		Position* GetConstPosition() const;
			//changed out for SetPosition
		// void SetFile(char);
		// void SetRank(int);
		//Move(std::string);
			//useful methods
		list<Chess*> Setup(); //NOTE: could move this to the ChessBoard class
		// int ChangeLetterToNumber(std::string);
		// void SetPosition(ChessSquare** board, Chess* blankPiece, Position* newPosition);
		friend std::ostream& operator<<(ostream& os, const Chess* piece); //NOTE: should be implemented in ChessPieces
			//we can implement the operator<< function later using this pure virtual function
		virtual void PrintOut() const;
};

class ChessSquare
{
    private:
    Position pos_; //Position object, as this will not be changing for the square and therefore is unnecessary to be a pointer
    Chess* piece; //will be NULL if not occupied, point to smth if it is - therefore we don't need a bool for occupied, just check if it's NULL

    public:
        //constructors
    ChessSquare::ChessSquare();
    ChessSquare::ChessSquare(string s);
    ChessSquare::ChessSquare(const ChessSquare& s);
    ChessSquare::ChessSquare(Chess* piece);
    ChessSquare::~ChessSquare();
        //getter methods
    Position ChessSquare::GetPos();
    Chess* ChessSquare::GetPiece();
    ChessSquare::operator bool(); //instead of GetOccupied, this makes it a little easier by just inputting the Square 
        //action methods
    void ChessSquare::ChangePiece(Chess* newPiece);

};

class ChessRank //dumb class, just holds the stuff in a rank so that you can go thorugh and make the array
{
	private: 
	ChessSquare rank[8];

	public:
	ChessRank::ChessRank(int RankNumber);
	void ChessRank::ChangePiece(Chess* piece);	
};

class ChessList
{
	private:
	std::list<Chess*> chessList;

	public:
		//constructor
	ChessList();
		//getter method
	list<Chess*> GetChessList();
		//action method
	void addChessPiece(Chess* piece);
};

class LineOfSight
{
    globalEnums::chessColor color_;
    std::unordered_map<ChessSquare&, std::vector<Chess*> > primaryLOS_; //for a given chess square, it will return the piece(s) that can see it (not necessarily move there, just see)
        //secondaryLOS really only has to worry about the king, as the primaryLOS worries about what can see the king right now
        //however, we can change the pieces to have pinned directional checks so that with each piece, you only have to check moves when they are not pinned 
    public:
        //constructors
    LineOfSight();
    LineOfSight(globalEnums::chessColor color);
        //getter methods
    globalEnums::chessColor GetColor();
    unordered_map<ChessSquare&, list<Chess*> > GetLineOfSight();
};

class ChessBoard
{
	private: 
	ChessSquare** _board; //the chess board: 2D array of Chess Squares that have a Position and a pointer to a Chess piece if that piece exists or NULL if it does not
		/* NOTE: Since the board is a 2D array, and that could not be passed easily, we will have to understand the size is 8x8 */
	bool whiteKingInCheck;
    bool blackKingInCheck;
	list<Chess*> blackPieces;
    list<Chess*> whitePieces;
	PositionVector _whitePrimaryLOS; //the positions that white pieces can see/move to
	PositionVector _blackPrimaryLOS; //the positions that white pieces can see/move to
	unordered_map<Position*, Chess*> _whiteSecondaryLOS; //the positions that could be seen/moved to if the Chess* moves
	unordered_map<Position*, Chess*> _blackSecondaryLOS; //the positions that could be seen/moved to if the Chess* moves

	public:
		//constructors
	ChessBoard::ChessBoard();
	ChessBoard::ChessBoard(list<Chess*> pieceList);
		//destructor
	ChessBoard::~ChessBoard();
		//getter methods
	ChessSquare** ChessBoard::GetBoard(); //returns the board
	PositionVector& ChessBoard::GetWhitePLOS(); //returns _whitePrimaryLOS
	PositionVector& ChessBoard::GetBlackPLOS(); //returns _blackPrimaryLOS
	unordered_map<Position*, Chess*>& ChessBoard::GetWhiteSLOS(); //returns _whiteSecondaryLOS
	unordered_map<Position*, Chess*>& ChessBoard::GetBlackSLOS(); //returns _blackSecondaryLOS
		//other useful methods
	bool ChessBoard::IsSquareBlank(ChessSquare& cs); //returns true if the square is blank and returns false if the square is not blank
	void ChessBoard::AddWhitePiece(Chess* piece);
	void ChessBoard::AddBlackPiece(Chess* piece);
		//accessor methods
	ChessRank& ChessBoard::operator[](int index);
	ChessRank& ChessBoard::Get(Position& pos);
};


