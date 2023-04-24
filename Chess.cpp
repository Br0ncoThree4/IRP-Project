using namespace std;

#include <iostream>
#include <string>
#include <list>
//#ifndef NULL
//#define NULL 0
//#endif


class Chess
{
	private:
		string color;
		string type;
		int file;
		int rank;
		
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



		Chess()//default constructor (empty square)
			{
				color = "NULL Color";
				type = "NULL Type";
				file = -1; //-1 so that it doesnt interfere w the actual board
				rank = -1; //-1 so that it doesnt interfere w the actual board
			}

		Chess(const Chess& piece)//copy constructor
		{
			color = piece.color;
			type = piece.type;
			file = piece.file;
			rank = piece.rank;
		}

		Chess(string c, string t, string f, int r) //parameterized constructor
		{
			color = c;
			type = t;
			file = ChangeLetterToNumber(f);
			rank = r;
		}
		Chess(string loc) //Starting square constructor
		{
			
			rank = stoi(loc.substr(1, 1)) - 1;
			file = ChangeLetterToNumber(loc.substr(0, 1));

			if (rank == 0 || rank == 1) //White Starting ranks
			{
				color = "White";
				if(rank == 1) {//Starting White Pawn rank (rank 2)
					type = "Pawn";
					}
				else if (loc == "a1" || loc == "h1") { //Starting White Rook positions
					type = "Rook";
					}
				else if (loc == "b1" || loc == "g1") {//Starting White Knight positions
					type = "Knight";
					}
				else if (loc == "c1" || loc == "f1") {//Starting White Bishop positions
					type = "Bishop";
					}
				else if (loc == "d1") {//Starting White Queen position
					type = "Queen";
					}
				else if (loc == "e1") {//Starting White King position
					type = "King";
					}
				else {
					cout << "The non-starting position inputted was" << loc;
					color = "NULL Color";
					type = "NULL Type";
					file = -1;
					rank = -1;
					cout << "Must be out of bounds, as the piece should be in ranks 1 and 2, but isn't in the selected range - probably due to file number";
				}
			}
			else if (rank == 6 || rank == 7) //Black Starting ranks
			{
				color = "Black";
				if (rank == 6) { //Starting Black Pawn rank (rank 7)
					type = "Pawn";
				}
				else if (loc == "a8" || loc == "h8") { //Starting Black Rook positions
					type = "Rook";
				}
				else if (loc == "b8" || loc == "g8") {//Starting Black Knight positions
					type = "Knight";
				}
				else if (loc == "c8" || loc == "f8") {//Starting Black Bishop positions
					type = "Bishop";
				}
				else if (loc == "d8") {//Starting Black Queen positions
					type = "Queen";
				}
				else if (loc == "e8") {//Starting Black King positions
					type = "King";
				}
				else {
					cout << "The non-starting position inputted was " << loc;
					color = "NULL Color";
					type = "NULL Type";
					file = -1;
					rank = -1;
					cout << "Must be out of bounds, as the piece should be in ranks 7 or 8, but isn't in the selected range - probably due to file number";
				}
			}
			else {
				cout << "The non-starting position inputted was " << loc;
				color = "NULL Color";
				type = "NULL Type";
				file = -1;
				rank = -1;
			}
		}
	
	
	static int ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
		string str = "abcdefgh";
		return static_cast<int>(str.find_first_of(letter));
	}

	
	//Getter methods

	string GetColor() 
	{
		return color;
	}
	int GetFile() {
		return file;
	}
	int GetRank() {
		return rank;
	}
	string GetType() 
	{
		return type;
	}

	

	//Changing the position
	void SetPosition(string newPosition) {
		this->file = ChangeLetterToNumber(newPosition.substr(0, 1));
		this->rank = stoi(newPosition.substr(1, 1));
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
