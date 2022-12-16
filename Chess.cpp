#include <iostream>
#include <string>
#include <list>
using namespace std;

class Chess
{
	private:
		string color;
		string type;
		int file;
		int row;
		bool check;
		static Chess arr[8][8];
		//checkKingMoves(Chess);
		//checkRookMoves(Chess);
		//checkBishopMoves(Chess);
		//checkKnightMoves(Chess);
		//checkQueenMoves(Chess);
		//checkPawnMoves(Chess);
	public:
		Chess(string, string, string, int);
		Chess(string);
		string GetColor();
		int GetFile();
		int GetRank();
		string GetType();
		void SetFile(string);
		void SetRow(string);
		//Move(string);
		list<Chess> Setup();
		int ChangeLetterToNumber(string);






	static int Chess::ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
		string str = "abcdefgh";
		return str.find_first_of(letter) + 1;
	}
	Chess::Chess(string c, string t, string f, int r) //parameterized constructor
	{
		color = c;
		type = t;
		file = ChangeLetterToNumber(f);
		row = r;
	}
	Chess::Chess(string loc) //Starting square constructor
	{
		string type;
		string type;
		int row = stoi(loc.substr(1, 1));
		int file = ChangeLetterToNumber(loc.substr(0,1));
		//I found that there were a ton of errors if I didn't define the parameters' types here, but this causes errors when trying to 
		//actually create objects, along with the problem of the if/else statements not working (the errors on the stoi(loc.substr(1,1)) statements
		//after the first)
		if (row == 1 || row == 2) //White Starting rows
		{
			color = "White"
			if (row == 2) {//Starting White Pawn row (row 2)
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
				color = NULL;
				type = NULL;
				file = NULL;
				row = NULL;
				cout << "Must be out of bounds, as the piece should be in row A or B, but isn't in the selected range";
			}
		}
		else if (row == 7 || row == 8) //Black Starting rows
		{
			color = "Black";
			if (row == 7) { //Starting Black Pawn row (row 7)
				type = "Pawn";
				
			}
			else if (loc == "a8" || loc == "h8") { //Starting Black Rook positions
				type = "Rook";
				
			}
			else if (loc == "b8" || loc == "g8") {//Starting Black Knight positions
				type = "Knight";
				
			}
			else if (loc == "c8" || loc == "f8") {//Starting Black Bishop positions
				type = "Knight";
				
			}
			else if (loc == "d8") {//Starting Black Queen positions
				type = "Queen";
				
			}
			else if (loc == "e8") {//Starting Black King positions
				type = "King";
				
			}
			else {
				cout << "The non-starting position inputted was " << loc;
				color = NULL;
				type = NULL;
				file = NULL;
				row = NULL;
			}
		}
		Board.
		else {
			cout << "The non-starting position inputted was " << loc;
			color = NULL;
			type = NULL;
			file = NULL;
			row = NULL;

		}


	}
	//Getter methods

	string Chess::GetColor() {
		return color;
	}
	int Chess::GetFile() {
		return stoi(file);
	}
	int Chess::GetRow() {
		return row;
	}
	string Chess::GetType() {
		return type;
	}

	//Changing the position
	void Chess::SetPosition(string newPosition) {
		this->file = ChangeLetterToNumber(newPosition.substr(0, 1));
		this->row = stoi(newPosition.substr(1, 1));
	}

	//Creating basic board
	list<Chess> Chess::Setup()
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
	ostream& operator << (ostream& os, Chess piece)
	{
		if(null){
			return "This space is open";
		}
		else{
			return (os << "Piece Color: " << piece.GetColor() << ", Piece Name: " << piece.GetType() << ", Piece location: " << piece.GetFile() << piece.GetRank());
		}

	return 0;


	
}
