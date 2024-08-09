using namespace std;

#include <iostream>
#include "Chess.h"
#include "basic.cpp"
//#ifndef NULL
//#define NULL 0
//#endif

class Chess
{
	private:
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

	

	/*
	* Function to change the position
	* doesn't check whether or not the move can be made
	* Changes the board
	*/
	void Chess::SetPosition(Chess** board[8], Position* newPosition) {
		board[newPosition->file][newPosition->rank] = this; //update the board with the move
		delete board[_pos->file][_pos->rank]; //delete the pointer to this in the old position on the board
		board[_pos->file][_pos->rank] = new Chess(globalEnums::BLANK_COLOR, globalEnums::BLANK_TYPE, _pos->file, _pos->rank); //update the old position with its new state (blank)
		_pos = newPosition; //update the variable inside the Chess piece for its location
	}

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
	~Chess()
	{
		delete _pos;
	}
};