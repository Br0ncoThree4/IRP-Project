using namespace std;

#include <iostream>
#include "Chess.h"
#include "basic.cpp"
//#ifndef NULL
//#define NULL 0
//#endif

//board[file][rank] - might want to go back and check on this later/change it so that it's _board[1] being the second rank
	//Going through and changing everything to board[rank][file], following standard 2d array syntax
class Chess
{
	protected:
		globalEnums::chessColor _color;
		globalEnums::chessType _type;
		Position* _pos;
		std::unordered_map <char, globalEnums::chessType> charToType; //defined in "Chess.h", can redefine here if necessary (if uses throw errors)
		PositionVector _primaryLOS;
		unordered_map<Position*, Chess*> _secondaryLOS;
		
		//checkKingMoves(Chess);
		//checkRookMoves(Chess);
		//checkBishopMoves(Chess);
		//checkKnightMoves(Chess);
		//checkQueenMoves(Chess);
		//checkPawnMoves(Chess);
	public:
		
		/*
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
		*/


		Chess::Chess()//default constructor (null square)
		: _primaryLOS(globalEnums::NULL_COLOR)
		{
			_color = globalEnums::NULL_COLOR;
			_type = globalEnums::NULL_TYPE;
			_pos = new Position(); //meant to throw errors, as this square does not have a position and is therefore not real
									//default Position returns a file of 'z' and a rank of -1
			_secondaryLOS;
		}

		Chess::Chess(const Chess& piece)//copy constructor
		: _pos(piece._pos), _color(piece._color), _type(piece._type), _primaryLOS(piece._color) {_secondaryLOS;}

		Chess::Chess(globalEnums::chessColor c, globalEnums::chessType t, char f, int r) //parameterized constructor
		: _color(c), _type(t), _primaryLOS(c) {_pos = new Position(f, r); _secondaryLOS;}

		Chess::Chess(string loc) //Starting square constructor - e.g. Chess("e2");
		: _primaryLOS()
		{
			_pos = new Position(loc[0], loc[1] - '0');//second argument should return an int that is the correct number of the rank
			//if(loc.length() != 2) {std::cout << "the location is not 2 characters (file letter and rank number), so this doesn't work"; throw std::runtime_error("Chess(string loc) string error");}
				//this check got thrown out, could bring back using default Position constructor
			
			if (_pos->rank == 0 || _pos->rank == 1) //White Starting ranks
			{
				_color = globalEnums::White;
				if(_pos->rank == 1) {//Starting White Pawn rank (rank 2)
					_type = globalEnums::Pawn;
					}
				else if (loc == "a1" || loc == "h1") { //Starting White Rook positions
					_type = globalEnums::Rook;
					}
				else if (loc == "b1" || loc == "g1") {//Starting White Knight positions
					_type = globalEnums::Knight;
					}
				else if (loc == "c1" || loc == "f1") {//Starting White Bishop positions
					_type = globalEnums::Bishop;
					}
				else if (loc == "d1") {//Starting White Queen position
						_type = globalEnums::Queen;
					}
				else if (loc == "e1") {//Starting White King position
					_type = globalEnums::King;
					}
				else {
					std::cout << "The non-starting position inputted was" << loc;
					_color = globalEnums::NULL_COLOR;
					_type = globalEnums::NULL_TYPE;
					delete _pos;
					_pos = new Position();
					std::cout << "Must be out of bounds, as the piece should be in ranks 1 and 2, but isn't in the selected range - probably due to file number";
					std::cout << "Position check is " << *(_pos) << endl; //pretty sure this inclusion of the Position will return a bool
				}
			}
			else if (_pos->rank == 6 || _pos->rank == 7) //Black Starting ranks
			{
				_color = globalEnums::Black;
				if (_pos->rank == 6) { //Starting Black Pawn rank (rank 7)
					_type = globalEnums::Pawn;
				}
				else if (loc == "a8" || loc == "h8") { //Starting Black Rook positions
					_type = globalEnums::Rook;
				}
				else if (loc == "b8" || loc == "g8") {//Starting Black Knight positions
					_type = globalEnums::Knight;
				}
				else if (loc == "c8" || loc == "f8") {//Starting Black Bishop positions
					_type = globalEnums::Bishop;
				}
				else if (loc == "d8") {//Starting Black Queen positions
					_type = globalEnums::Queen;
				}
				else if (loc == "e8") {//Starting Black King positions
					_type = globalEnums::King;
				}
				else {
					std::cout << "The non-starting position inputted was " << loc;
					_color = globalEnums::NULL_COLOR;
					_type = globalEnums::NULL_TYPE;
					delete _pos;
					_pos = new Position();
					std::cout << "Must be out of bounds, as the piece should be in ranks 7 or 8, but isn't in the selected range - probably due to file number";
					std::cout << "Position check is " << *(_pos) << endl; //pretty sure this inclusion of the Position will return a bool
				}
			}
			else if (*(_pos) == true) //blank square -> Position.bool() == true
			{
				std::cout << "This is an empty square";
				_color = globalEnums::BLANK_COLOR;
				_type = globalEnums::BLANK_TYPE;
				//_pos is good, as it holds the position of where that blank square is
				std::cout << " at " << GetFile() << GetRank() << endl;
				std::cout << "Position check for this blank square is " << *(_pos) << endl;
			}
			else{
				std::cout << "The non-starting position inputted was " << loc;
				_color = globalEnums::NULL_COLOR;
				_type = globalEnums::NULL_TYPE;
				delete _pos;
				_pos = new Position();
				std::cout << "Position check is " << *(_pos) << endl; //pretty sure this inclusion of the Position will return a bool
			}
		}
		//Taken out on 7/19 because of moveToType and no other reason to require this function
	// static int Chess::ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
	// 	string str = "abcdefgh";
	// 	return static_cast<int>(str.find_first_of(letter));
	// }

	
	//Getter methods

	globalEnums::chessColor Chess::GetColor() 
	{
		return _color;
	}
	globalEnums::chessType Chess::GetType() 
	{
		return _type;
	}
	char Chess::GetFile() {
		return _pos->file;
	}
	int Chess::GetRank() {
		return _pos->rank;
	}
	Position* Chess::GetPosition() {
		return _pos;
	}
	PositionVector& Chess::GetPrimaryLOS()
	{
		return _primaryLOS;
	}
	unordered_map<Position*, Chess*>& Chess::GetSecondaryLOS()
	{
		return _secondaryLOS;
	}
	globalEnums::chessColor Chess::GetConstColor() const {return _color;}
	globalEnums::chessType Chess::GetConstType() const {return _type;}
	char Chess::GetConstFile() const {return _pos->file;}
	int Chess::GetConstRank() const {return _pos->rank;}
	Position* Chess::GetConstPosition() const {return _pos;}

	

	/*
	* Function to change the position
	* doesn't check whether or not the move can be made
	* Changes the board
	*/
	/* Function Chess::SetPosition got changed on 8/22 because the ChessSquare and ChessBoar classes can handle moving the piece in a more streamlined manner
	void Chess::SetPosition(ChessSquare** boar, Position* newPosition) {
		boar[newPosition->rank][newPosition->file] = this; //update the boar with the move
		delete boar[_pos->rank][_pos->file]; //delete the pointer to this in the old position on the boar
		boar[_pos->rank][_pos->file] = new Chess(globalEnums::BLANK_COLOR, globalEnums::BLANK_TYPE, _pos->file, _pos->rank); //update the old position with its new state (blank)
		_pos = newPosition; //update the variable inside the Chess piece for its location
	}
		*/

	//Creating basic board
	static list<Chess*> Chess::Setup()
	{
		list<Chess*> pieceList;

		//White Pieces
		pieceList.push_back(new Chess("a2"));
		pieceList.push_back(new Chess("b2"));
		pieceList.push_back(new Chess("c2"));
		pieceList.push_back(new Chess("d2"));
		pieceList.push_back(new Chess("e2"));
		pieceList.push_back(new Chess("f2"));
		pieceList.push_back(new Chess("g2"));
		pieceList.push_back(new Chess("h2"));

		pieceList.push_back(new Chess("a1"));
		pieceList.push_back(new Chess("h1"));
		pieceList.push_back(new Chess("b1"));
		pieceList.push_back(new Chess("g1"));
		pieceList.push_back(new Chess("c1"));
		pieceList.push_back(new Chess("f1"));
		pieceList.push_back(new Chess("d1"));
		pieceList.push_back(new Chess("e1"));

		//Black Pieces
		pieceList.push_back(new Chess("a7"));
		pieceList.push_back(new Chess("b7"));
		pieceList.push_back(new Chess("c7"));
		pieceList.push_back(new Chess("d7"));
		pieceList.push_back(new Chess("e7"));
		pieceList.push_back(new Chess("f7"));
		pieceList.push_back(new Chess("g7"));
		pieceList.push_back(new Chess("h7"));

		pieceList.push_back(new Chess("a8"));
		pieceList.push_back(new Chess("h8"));
		pieceList.push_back(new Chess("b8"));
		pieceList.push_back(new Chess("g8"));
		pieceList.push_back(new Chess("c8"));
		pieceList.push_back(new Chess("f8"));
		pieceList.push_back(new Chess("d8"));
		pieceList.push_back(new Chess("e8"));

		//blank squares (added to the piece list so that the pointers can be saved in ChessBoardMoves)
		pieceList.push_back(new Chess("a3"));
		pieceList.push_back(new Chess("b3"));
		pieceList.push_back(new Chess("c3"));
		pieceList.push_back(new Chess("d3"));
		pieceList.push_back(new Chess("e3"));
		pieceList.push_back(new Chess("f3"));
		pieceList.push_back(new Chess("g3"));
		pieceList.push_back(new Chess("h3"));

		pieceList.push_back(new Chess("a4"));
		pieceList.push_back(new Chess("b4"));
		pieceList.push_back(new Chess("c4"));
		pieceList.push_back(new Chess("d4"));
		pieceList.push_back(new Chess("e4"));
		pieceList.push_back(new Chess("f4"));
		pieceList.push_back(new Chess("g4"));
		pieceList.push_back(new Chess("h4"));

		pieceList.push_back(new Chess("a5"));
		pieceList.push_back(new Chess("b5"));
		pieceList.push_back(new Chess("c5"));
		pieceList.push_back(new Chess("d5"));
		pieceList.push_back(new Chess("e5"));
		pieceList.push_back(new Chess("f5"));
		pieceList.push_back(new Chess("g5"));
		pieceList.push_back(new Chess("h5"));

		pieceList.push_back(new Chess("a6"));
		pieceList.push_back(new Chess("b6"));
		pieceList.push_back(new Chess("c6"));
		pieceList.push_back(new Chess("d6"));
		pieceList.push_back(new Chess("e6"));
		pieceList.push_back(new Chess("f6"));
		pieceList.push_back(new Chess("g6"));
		pieceList.push_back(new Chess("h6"));
		
		return pieceList;
	}


	//toString-like method
	/**
	 * ostream& operator << (ostream& os, Chess piece)
	{
		if (NULL) {
			return "This space is open";
		}
		else {
			return (os << "Piece Color: " << piece.GetColor() << ", Piece Name: " << piece.GetType() << ", Piece location: " << piece.GetFile() << piece.GetRank());
		}
	}
	 */

	friend std::ostream& operator<<(ostream& os, Chess* piece)
	{
		piece->PrintOut(os);
		return os;
	}

	virtual void Chess::PrintOut(ostream& os)
	{
		os << GetColor() << " " << GetType() << ", " << GetPosition()->file << GetPosition()->rank << endl;
	}

	~Chess()
	{
		delete _pos;
	}
};

class ChessSquare
{
    private:
    Position pos_;
    Chess* piece_; //will be NULL if not occupied, point to smth if it is - therefore we don't need a bool for occupied, just check if it's NULL

    public:
        //constructors
    ChessSquare::ChessSquare() : piece_(NULL), pos_('z', -1) {} //default constructor
    ChessSquare::ChessSquare(string s) //string s in form "e4" - can't do it before the constructor because we're creating pointers
    {
        piece_ = new Chess(s);
        pos_ = *(piece_->GetPosition());
        if(piece_->GetColor() == globalEnums::BLANK_COLOR) //if the square is blank
            delete piece_;
    }
    ChessSquare::ChessSquare(const ChessSquare& s) : pos_(s.pos_), piece_(s.piece_) {} //copy constructor
    ChessSquare::ChessSquare(Chess* piece) : pos_(*(piece->GetPosition())), piece_(piece) {} //constrtor to be used for custom positions - piece gets created and then added to the square, regardless of where that piece "should" be based off the typical setup of the board
    ChessSquare::~ChessSquare() {delete piece_;} //destructor: delete all pointers for no memory leak
        //getter methods
    Position ChessSquare::GetPos() {return pos_;}
    Chess* ChessSquare::GetPiece() {return piece_;}
    ChessSquare::operator bool() {return piece_ != NULL;} //Returns true if the Square has a piece on it (points to a non-NULL object), and false if it does not (points to NULL)
        //action methods
    void ChessSquare::ChangePiece(Chess* newPiece) //NOTE: doesn't take the piece out of a piece list if that happens
    {
        if(piece_ == newPiece) {cout << "You just tried to move a piece from where it is to where it is" << endl; return;} //don't want the program to do extra work or delete the pointer if the piece is somehow repeated
        delete piece_; 
        piece_ = newPiece;
    } 
};

class ChessRank
{
	private: 
	ChessSquare rank_[8];
	int rankNumber_; //number from 1 to 8

	public:
	ChessRank::ChessRank() : rankNumber_(-1)
	{
		//ChessSquares get created using the default constructor
	}
	ChessRank::ChessRank(int rn) : rankNumber_(rn)
	{
		//ChessSquares get created using the default constructor
	}
	//changing methods
	void ChessRank::ChangePiece(Chess* piece)
	{
		if(piece->GetRank() != rankNumber_) {cout << "A piece tried to get added on a rank that it is not on" << endl; return;} //check to make sure the rank is correct
		rank_[piece->GetFile() - 'a'].ChangePiece(piece); //change the ChessSquare to have the piece on it
	}
	ChessSquare& ChessRank::operator[](int index)
	{
		if(1 <= index && index <= 8) {return rank_[index-1];}
		cout << "You gave me a bad index of " << index << ", which is not within the range of 1-8;; Returning first piece at position [" << rankNumber_ << "][0]:" << endl;
		return rank_[0];
	}
	
};

class ChessList
{
	private:
	std::list<Chess*> chessList_;

	public:
		//constructor
	ChessList::ChessList() {}
		//getter method
	list<Chess*> ChessList::GetChessList() {return chessList_;}
		//action method
	void addChessPiece(Chess* piece) {chessList_.push_back(piece);}
};

class LineOfSight
{
    globalEnums::chessColor color_;
    std::unordered_map<ChessSquare&, ChessList&> primaryLOS_; //for a given chess square, it will return the piece(s) that can see it (not necessarily move there, just see)
        //secondaryLOS really only has to worry about the king, as the primaryLOS worries about what can see the king right now
        //however, we can change the pieces to have pinned directional checks so that with each piece, you only have to check moves when they are not pinned 
    public:
        //constructors
    LineOfSight::LineOfSight() : color_(globalEnums::NULL_COLOR), primaryLOS_(0) {} //primaryLOS_(0) should be able to initialize the unordered_map as an empty map
    LineOfSight::LineOfSight(globalEnums::chessColor color) : color_(color), primaryLOS_(0) {}
        //getter methods
    globalEnums::chessColor LineOfSight::GetColor() {return color_;}
    unordered_map<ChessSquare&, ChessList&> LineOfSight::GetLineOfSight() {return primaryLOS_;}
};

class ChessBoard
{
	protected:
	ChessRank _board[8]; //the chess board: 2D array of Chess Squares that have a Position and a pointer to a Chess piece if that piece exists or NULL if it does not
	bool whiteKingInCheck;
    bool blackKingInCheck;
	list<Chess*> blackPieces;
    list<Chess*> whitePieces;
	PositionVector _whitePrimaryLOS; //the positions that white pieces can see/move to
	PositionVector _blackPrimaryLOS; //the positions that white pieces can see/move to
	unordered_map<Position*, Chess*> _whiteSecondaryLOS; //the positions that could be seen/moved to if the Chess* moves
	unordered_map<Position*, Chess*> _blackSecondaryLOS; //the positions that could be seen/moved to if the Chess* moves
		//these LOS's will be changed when it comes time to look at what moves are legal

	public:
		//constructors
	ChessBoard::ChessBoard() : whiteKingInCheck(false), blackKingInCheck(false)
	{
		for(int rank = 1; rank <= 8; rank++)
		{
			_board[rank - 1] = ChessRank(rank);
			for(char file = 'a'; file <= 'h'; file++)
			{
				_board[rank - 1][file - 'a'] = ChessSquare("" + file + rank);
				if(_board[rank - 1][file - 'a']) //if there is actually a piece on this square
				{
					//NOTE: we could also try and add moves at this time, but we would have to make sure that it accounts for the fact that more pieces are getting added
					if(_board[rank - 1][file - 'a'].GetPiece()->GetColor() == globalEnums::White)
					{
						whitePieces.push_back(_board[rank - 1][file - 'a'].GetPiece());
					}
					else
					{
						blackPieces.push_back(_board[rank - 1][file - 'a'].GetPiece());
					}
				}
				cout << endl;
			}
		}
	}
		//NEED TO FINISH - find the piece's positions and add them to those squares; leave the other squares empty
	ChessBoard::ChessBoard(list<Chess*> pieceList) 
	{
		for(int rank = 1; rank <= 8; rank++)
		{
			_board[rank - 1] = ChessRank(rank); //creates all blank ranks
		}
		for(Chess* piecePointer : pieceList)
		{
			_board[piecePointer->GetRank() - 1].ChangePiece(piecePointer); // adds each chessPiece to the board, making the ChessSquare piece pointers not null if the piece is on that square and the rest of the squares staying NULL
			if(piecePointer->GetColor() == globalEnums::White)
			{
				whitePieces.push_back(piecePointer);
			}
			else if(piecePointer->GetColor() == globalEnums::Black)
			{
				blackPieces.push_back(piecePointer);
			}
			else
			{
				cout << "Piece had a color of " << piecePointer->GetColor() << ", which is not either globalEnums::White or globalEnums::Black" << endl;
			}
		}
	}
		//destructor
	ChessBoard::~ChessBoard()
	{
		delete [] _board; //should only need this to delete the array, as it is an array of pointers and the 'delete []' function deletes the array of pointers
		while(blackPieces.size() > 0)
		{
			blackPieces.pop_front(); //NOTE: Could be something that could causes a memory leak for not deleting the Chess
		}
		while(whitePieces.size() > 0)
		{
			whitePieces.pop_front(); //NOTE: Could be something that causes a memory leak for not deleting the Chess pointers
		}
	}
		//getter methods
	ChessSquare** ChessBoard::GetBoard() {return _board;} //returns the board
	PositionVector& ChessBoard::GetWhitePLOS() {return _whitePrimaryLOS;} 
	PositionVector& ChessBoard::GetBlackPLOS() {return _blackPrimaryLOS;} 
	unordered_map<Position*, Chess*>& ChessBoard::GetWhiteSLOS() {return _whiteSecondaryLOS;} 
	unordered_map<Position*, Chess*>& ChessBoard::GetBlackSLOS() {return _blackSecondaryLOS;} 
		//other useful methods
	bool ChessBoard::IsSquareBlank(ChessSquare& cs) {return cs;} //returns true if the square is blank and returns false if the square is not blank
	void ChessBoard::AddPiece(Chess* piece) 
	{
		if(piece->GetColor() == globalEnums::White)
		{
			whitePieces.push_back(piece);
		}
		else if(piece->GetColor() == globalEnums::Black)
		{
			blackPieces.push_back(piece);
		}
	}

	ChessRank& ChessBoard::operator[](int index)
	{
		if(1 <= index && index <= 8) {return _board[index-1];}
		cout << "You gave me a bad index of " << index << ", which is not within the range of 1-8;; Returning first rank:" << endl;
		return _board[0];
	}

	ChessRank& ChessBoard::Get(Position& pos)
	{

	}
};