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
		enum chessColor _color;
		enum chessType _type;
		Position _pos;
		
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



		Chess::Chess()//default constructor (empty square)
		: _pos('z', -1)//, _color(-1), _type(-1) 
		{
			_color = NO_COLOR;
			_type = NO_TYPE;
		}

		Chess::Chess(const Chess& piece)//copy constructor
		: _pos(piece._pos), _color(piece._color), _type(piece._type) {}

		Chess::Chess(chessColor c, chessType t, char f, int r) //parameterized constructor
		: _color(c), _type(t), _pos(f, r) {}

		Chess::Chess(string loc) //Starting square constructor
		: _pos(loc[0], loc[1] - '0') //second argument should return an int that is the correct number of the rank
		{
			//if(loc.length() != 2) {cout << "the location is not 2 characters (file letter and rank number), so this doesn't work"; throw std::runtime_error("Chess(string loc) string error");}
				//this check got thrown out, could bring back using default Position constructor
			
			if (_pos.rank == 0 || _pos.rank == 1) //White Starting ranks
			{
				_color = White;
				if(_pos.rank == 1) {//Starting White Pawn rank (rank 2)
					_type = Pawn;
					}
				else if (loc == "a1" || loc == "h1") { //Starting White Rook positions
					_type = Rook;
					}
				else if (loc == "b1" || loc == "g1") {//Starting White Knight positions
					_type = Knight;
					}
				else if (loc == "c1" || loc == "f1") {//Starting White Bishop positions
					_type = Bishop;
					}
				else if (loc == "d1") {//Starting White Queen position
					_type = Queen;
					}
				else if (loc == "e1") {//Starting White King position
					_type = King;
					}
				else {
					cout << "The non-starting position inputted was" << loc;
					_color = -1;
					_type = -1;
					_pos = Position('z', -1);
					cout << "Must be out of bounds, as the piece should be in ranks 1 and 2, but isn't in the selected range - probably due to file number";
					cout << "Position check is " << _pos << endl; //pretty sure this inclusion of the Position will return a bool
				}
			}
			else if (_pos.rank == 6 || _pos.rank == 7) //Black Starting ranks
			{
				_color = Black;
				if (_pos.rank == 6) { //Starting Black Pawn rank (rank 7)
					_type = Pawn;
				}
				else if (loc == "a8" || loc == "h8") { //Starting Black Rook positions
					_type = Rook;
				}
				else if (loc == "b8" || loc == "g8") {//Starting Black Knight positions
					_type = Knight;
				}
				else if (loc == "c8" || loc == "f8") {//Starting Black Bishop positions
					_type = Bishop;
				}
				else if (loc == "d8") {//Starting Black Queen positions
					_type = Queen;
				}
				else if (loc == "e8") {//Starting Black King positions
					_type = King;
				}
				else {
					cout << "The non-starting position inputted was " << loc;
					_color = NO_COLOR;
					_type = NO_TYPE;
					_pos = Position('z', -1);
					cout << "Must be out of bounds, as the piece should be in ranks 7 or 8, but isn't in the selected range - probably due to file number";
					cout << "Position check is " << _pos << endl; //pretty sure this inclusion of the Position will return a bool
				}
			}
			else {
				cout << "The non-starting position inputted was " << loc;
				_color = NO_COLOR;
				_type = NO_TYPE;
				_pos = Position('z', -1);
				cout << "Position check is " << _pos << endl; //pretty sure this inclusion of the Position will return a bool
			}
		}
	
	
	static int ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
		string str = "abcdefgh";
		return static_cast<int>(str.find_first_of(letter));
	}

	
	//Getter methods

	chessColor GetColor() 
	{
		return _color;
	}
	int GetFile() {
		return _pos.file;
	}
	char GetRank() {
		return _pos.rank;
	}
	chessType GetType() 
	{
		return _type;
	}

	

	//Changing the position
	void SetPosition(string newPosition) {
		this->_pos.file = newPosition[0];
		this->_pos.rank = newPosition[1] - '0';
	}

	//Creating basic board
	static list<Chess> Setup()
	{
		list<Chess> pieceList;

		//White Pieces
		pieceList.push_back(Chess("a2"));
		pieceList.push_back(Chess("b2"));
		pieceList.push_back(Chess("c2"));
		pieceList.push_back(Chess("d2"));
		pieceList.push_back(Chess("e2"));
		pieceList.push_back(Chess("f2"));
		pieceList.push_back(Chess("g2"));
		pieceList.push_back(Chess("h2"));

		pieceList.push_back(Chess("a1"));
		pieceList.push_back(Chess("h1"));
		pieceList.push_back(Chess("b1"));
		pieceList.push_back(Chess("g1"));
		pieceList.push_back(Chess("c1"));
		pieceList.push_back(Chess("f1"));
		pieceList.push_back(Chess("d1"));
		pieceList.push_back(Chess("e1"));

		//Black Pieces
		pieceList.push_back(Chess("a7"));
		pieceList.push_back(Chess("b7"));
		pieceList.push_back(Chess("c7"));
		pieceList.push_back(Chess("d7"));
		pieceList.push_back(Chess("e7"));
		pieceList.push_back(Chess("f7"));
		pieceList.push_back(Chess("g7"));
		pieceList.push_back(Chess("h7"));

		pieceList.push_back(Chess("a8"));
		pieceList.push_back(Chess("h8"));
		pieceList.push_back(Chess("b8"));
		pieceList.push_back(Chess("g8"));
		pieceList.push_back(Chess("c8"));
		pieceList.push_back(Chess("f8"));
		pieceList.push_back(Chess("d8"));
		pieceList.push_back(Chess("e8"));

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
};
