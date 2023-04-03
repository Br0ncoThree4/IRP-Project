using namespace std;

#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include <array>
#ifndef NULL
#define NULL 0
#endif

class ChessBoardMoves : public Chess
{
    public:
        ChessBoardMoves();
        ChessBoardMoves(list<Chess>);
        Chess board[8][8];
        bool kingInCheck; //Checks if king is in check
		static string alphabet;
	public:
		list<string> checkKingMoves(Chess);
		list<string> checkRookMoves(Chess);
		list<string> checkBishopMoves(Chess);
		list<string> checkKnightMoves(Chess);
		list<string> checkQueenMoves(Chess);
		list<string> checkPawnMoves(Chess);
		//LegalMove(Chess, string);
		//Move(Chess, string);
		bool IsOnBoard(string);
		list<string> FindMoves(Chess);
		list<string> StartingMoves();

    

    ChessBoardMoves::ChessBoardMoves()
    {
        for (int r = 0; r < 8; r++)
        {
            for(int c = 0; c < 8; c++)
            {
                board[r][c] = Chess();
            }
        }
		alphabet = "abcdefgh";
    }

    ChessBoardMoves::ChessBoardMoves(list<Chess> pieceList) {//Creates the 2D array that is the board, given the list of starting chess pieces
        Chess Board[8][8];
        
        for (Chess piece : pieceList) {//putting each chess piece on their starting squares
            int rank = piece.GetRank();
            int file = piece.GetFile();
            board[rank][file] = piece;
        }
        for (int row = 8; row > 0; row++) { //printing the board and its square number
            for (int col = 0; col < 8; col++) {
                if (board[row][col].GetType() != "NULL") {
                    std::cout << board[row][col].GetColor() << " " << board[row][col].GetType();
                }
                else {
                    std::cout << "\t \t \t \t"; //trying to space the board out so that even if theres nothing, the board still kind of keeps is square shape
                }

                    std::cout << "(" << "abcdefgh"[row] << (col + 1) << ")" << "\t";
            }
            std::cout << endl;
        }

		alphabet = "abcdefgh";
    }
    //we also need a printing method for the chess board

    //ChessMoves insert here




	list<string> ChessBoardMoves::StartingMoves() //Returns starting moves for white (can be altered to make it for black, just need to change a few letters)
	{
		list<string> moves; //White Starting Moves
		//Pawn Moves
		for(int k = 1; k <= 8; k++){
			string file = to_string("abcdefgh"[k-1]);
			moves.push_back(file + "3");
			moves.push_back(file + "4");
		}
		//Knight Moves
		for(int k = 1; k <= 2; k++){
			int startingFile = k/2*5 + 1;//gets file to be either 1 or 6 (B or G)
			int startingRank = 1;
			for(int x = -1; x <= 1; x+= 2){
				string newFile = to_string("abcdefghijk"[startingFile + x]);
				moves.push_back(newFile + to_string(startingRank + 2));
			}
		}
		return moves;
	}

	void ChessBoardMoves::Move(Chess piece, string newPosition) {
		
        if(IsBlockingCheck(piece))
        {
            cout << "This piece is blocking check, so it can't move";
        }
        else{

        

		int newRank = ChangeLetterToNumber(newPosition.substr(0, 1));
		int newFile = stoi(newPosition.substr(1, 1));

        //move the piece
        board[piece.GetRank()][piece.GetFile()] = Chess();
        board[newRank][newFile] = piece;
            
        piece.SetPosition(newPosition);//set position for the piece's instance variables 
        }
	}


	bool ChessBoardMoves::IsBlockingCheck(Chess piece)
	{
        bool isBlockingDiagonalCheck = false;
        bool isBlockingLineCheck = false;
        int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank);
        
        //If king is in open sight of piece (need to check all diagonals and lines)
        //diagonals check
        int counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile + counter))
            {
                if(board[currentRank + counter][currentFile + counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank + counter][currentFile + counter].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank + counter][currentFile + counter].GetType() == "King")
                    {
                        isBlockingDiagonalCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile - counter))
            {
                if(board[currentRank - counter][currentFile - counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank - counter][currentFile - counter].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank - counter][currentFile - counter].GetType() == "King")
                    {
                        isBlockingDiagonalCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile + counter))
            {
                if(board[currentRank - counter][currentFile + counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank - counter][currentFile + counter].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank - counter][currentFile + counter].GetType() == "King")
                    {
                        isBlockingDiagonalCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile - counter))
            {
                if(board[currentRank + counter][currentFile - counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank + counter][currentFile - counter].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank + counter][currentFile - counter].GetType() == "King")
                    {
                        isBlockingDiagonalCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        //rook moves
        counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile))
            {
                if(board[currentRank + counter][currentFile].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank + counter][currentFile].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank + counter][currentFile].GetType() == "King")//piece of same color is blocking king
                    {
                        isBlockingLineCheck = true;
                    }
                    else//piece of same color isn't king
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile))
            {
                if(board[currentRank - counter][currentFile].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank - counter][currentFile].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank - counter][currentFile].GetType() == "King")
                    {
                        isBlockingLineCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank, currentFile + counter))
            {
                if(board[currentRank][currentFile + counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank][currentFile + counter].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank][currentFile + counter].GetType() == "King")
                    {
                        isBlockingLineCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank, currentFile - counter))
            {
                if(board[currentRank][currentFile - counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    if(board[currentRank][currentFile - counter].GetColor() == "NULL") //square is empty: keep looking
                    {
                        counter++;
                    }
                    else //square has other color's piece
                    {
                        counter = 8;
                    }
                }
                else//square is the same color
                {
                    if(board[currentRank][currentFile - counter].GetType() == "King")
                    {
                        isBlockingLineCheck = true;
                    }
                    else
                    {
                        counter = 8;
                    }
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        if(isBlockingDiagonalCheck == false & isBlockingLineCheck == false)//Is the piece blocking check
        {
            return false;
        }

        //piece must be blocking check
        if(isBlockingDiagonalCheck)
        {

        }
        else//isBlockingLineCheck
        {
            
        }

	}
	bool ChessBoardMoves::IsInCheck(Chess king, list<string> possibleMoves)//See if king is in check (possibleMoves is the list of moves of the opposite color than the king)
	{
		string position = alphabet.substr(king.GetFile(), 1) + to_string(king.GetRank());
		for(string move: possibleMoves)
		{
			if(move == position)
			{
				return true;
			}
		}
		return false;
	}

	static bool ChessBoardMoves::IsOnBoard(string position)
	{
		int rank = ChangeLetterToNumber(position.substr(0, 1));
		int file = stoi(position.substr(1, 1));
		if((rank > 0 & rank < 9) & (file > 0 & file < 9))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static bool ChessBoardMoves::IsOnBoard(int rank, int file)
	{
		
		if((rank > 0 & rank < 9) & (file > 0 & file < 9))
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	list<string> ChessBoardMoves::checkKingMoves(Chess piece) // will return K*file letter**rank number (as a string)*
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile) + to_string(currentRank);
		string type = "K";

		if(type != piece.GetType().substr(0, 1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a King, as was expected by the checkKingMoves method";
			return possibleMoves;
		}

		
		if(IsOnBoard(currentRank + 1, currentFile) & board[currentRank + 1][currentFile].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile) & board[currentRank - 1][currentFile].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 1, currentFile + 1) & board[currentRank + 1][currentFile + 1].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile + 1) & board[currentRank - 1][currentFile + 1].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank - 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 1, currentFile - 1) & board[currentRank + 1][currentFile - 1].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile - 1) & board[currentRank - 1][currentFile - 1].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank - 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank, currentFile + 1) & board[currentRank][currentFile + 1].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank, currentFile - 1) & board[currentRank][currentFile - 1].GetType() != piece.GetType())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank);
			possibleMoves.push_back(position);
		}
		
		return possibleMoves;
	}

	list<string> ChessBoardMoves::checkQueenMoves(Chess piece)
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile) + to_string(currentRank);
		string type = "Q";

		if(type != piece.GetType().substr(0,1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Queen, as was expected by the checkQueenMoves method";
			return possibleMoves;
		}

        //bishop moves
        int counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile + counter))
            {
                if(board[currentRank + counter][currentFile + counter].GetColor() != piece.GetColor())//square is open or can be taken
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank + counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is occupied by same color piece
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile - counter))
            {
                if(board[currentRank - counter][currentFile - counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank - counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile + counter))
            {
                if(board[currentRank - counter][currentFile + counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank - counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile - counter))
            {
                if(board[currentRank + counter][currentFile - counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank + counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        //rook moves
        counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile))
            {
                if(board[currentRank + counter][currentFile].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile))
            {
                if(board[currentRank - counter][currentFile].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank, currentFile + counter))
            {
                if(board[currentRank][currentFile + counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank, currentFile - counter))
            {
                if(board[currentRank][currentFile - counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        return possibleMoves;
	}

	list<string> ChessBoardMoves::checkBishopMoves(Chess piece) //will return B*file letter**rank number (as string)*
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile) + to_string(currentRank);
		string type = "B";

		if(type != piece.GetType().substr(0,1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Bishop, as was expected by the checkBishopMoves method";
			return possibleMoves;
		}

        int counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile + counter))
            {
                if(board[currentRank + counter][currentFile + counter].GetColor() != piece.GetColor())//square is open or can be taken
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank + counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is occupied by same color piece
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile - counter))
            {
                if(board[currentRank - counter][currentFile - counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank - counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile + counter))
            {
                if(board[currentRank - counter][currentFile + counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank - counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile - counter))
            {
                if(board[currentRank + counter][currentFile - counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank + counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        return possibleMoves;
	}

	list<string> ChessBoardMoves::checkKnightMoves(Chess piece) //Will return N
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile) + to_string(currentRank);
		string type = "N";

		if("K" != piece.GetType().substr(0, 1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Knight, as was expected by the checkKnightMoves method";
			return possibleMoves;
		}

		if(IsOnBoard(currentRank + 1, currentFile + 2) & board[currentRank + 1][currentFile + 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 2, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile + 2) & board[currentRank - 1][currentFile + 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 2, 1) + to_string(currentRank - 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 1, currentFile - 2) & board[currentRank + 1][currentFile - 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 2, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile - 2) & board[currentRank - 1][currentFile - 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 2, 1) + to_string(currentRank - 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 2, currentFile + 1) & board[currentRank + 2][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 2);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 2, currentFile - 1) & board[currentRank + 2][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 2);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 2, currentFile + 1) & board[currentRank - 2][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank - 2);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 2, currentFile - 1) & board[currentRank - 2][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank - 2);
			possibleMoves.push_back(position);
		}

		return possibleMoves;
	}

	list<string> ChessBoardMoves::checkRookMoves(Chess piece)
	{
		list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile) + to_string(currentRank);
		string type = "R";

		if(type != piece.GetType().substr(0, 1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Rook, as was expected by the checkRookMoves method";
			return possibleMoves;
		}

        int counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile))
            {
                if(board[currentRank + counter][currentFile].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank - counter, currentFile))
            {
                if(board[currentRank - counter][currentFile].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - counter);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank, currentFile + counter))
            {
                if(board[currentRank][currentFile + counter].GetColor() != piece.GetColor())//either null or other color)
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        counter = 1;
        do{
            if(IsOnBoard(currentRank, currentFile - counter))
            {
                if(board[currentRank][currentFile - counter].GetColor() != piece.GetColor())//either null or other color
                {
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank);
                    possibleMoves.push_back(position);
                    counter++;
                }
                else//square is the same color
                {
                    counter = 8;
                }
            }
            else//"square" is off the board
            {
                counter = 8;
            }
        }while(counter <= 7);

        return possibleMoves;
	}

	list<string> ChessBoardMoves::checkPawnMoves(Chess piece)
	{
		list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile) + to_string(currentRank);
		string type = "P";

		if(type != piece.GetType().substr(0, 1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Pawn, as was expected by the checkPawnMoves method";
			return possibleMoves;
		}

        if(IsOnBoard(currentRank + 1, currentFile) & board[currentRank + 1][currentFile].GetColor() != piece.GetColor())
        {
            string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
            possibleMoves.push_back(position);
        }
        if(IsOnBoard(currentRank + 1, currentFile + 1) & board[currentRank + 1][currentFile + 1].GetColor() != piece.GetColor())
        {
            string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 1);
            possibleMoves.push_back(position);
        }
        if(IsOnBoard(currentRank + 1, currentFile - 1) & board[currentRank + 1][currentFile - 1].GetColor() != piece.GetColor())
        {
            string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 1);
            possibleMoves.push_back(position);
        }
        //Add en passant moves??

        return possibleMoves;
	}

	/**
	 * void ChessBoardMoves::LegalMove(Chess piece, string newPosition)//Make sure move isn't out of bounds or creating a check
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


	//other legalMove method--

	void ChessMoves::legalMove(Chess piece, string loc)
	{
		if (piece.GetType() == "King") {
			//checkKingMoves(piece);
			//if() //Make sure king isn't in check after move
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
	 * 
	 */

	void ChessBoardMoves::LegalMove(Chess piece, string newPosition)//Make sure move isn't out of bounds or creating a check
	{
		string type = piece.GetType();
		list<string> possibleMoves;
		//Finding list of legal moves, depending on each piece
		possibleMoves = FindMoves(piece);

		while (true) {//Check if new square is part of legal moves for that piece
			for (string move : possibleMoves)
			{
				if (move == newPosition) //If true, move
				{
					piece.SetPosition(newPosition);
					cout << "Your move " << piece.GetType() << " to " << newPosition << " was played";
					break;
				}
			}
			//Only gets here is the hopeful move is not a part of the legal moves
			std::cout<<"Your desired move was not legal, please try again"; //If false, return error
		}

	}

	list<string> ChessBoardMoves::FindMoves(Chess piece)
	{
		list<string> possibleMoves;
		string type = piece.GetType();

		if(type == "King")
		{
			possibleMoves = checkKingMoves(piece);
			
		}
		else if(type == "Queen")
		{
			possibleMoves = checkQueenMoves(piece);

		}
		else if(type == "Bishop")
		{
			possibleMoves = checkBishopMoves(piece);

		}
		else if(type == "Knight")
		{
			possibleMoves = checkKnightMoves(piece);

		}
		else if(type == "Rook")
		{
			possibleMoves = checkRookMoves(piece);

		}
		else if(type == "Pawn")
		{
			possibleMoves = checkPawnMoves(piece);

		}
		else
		{
			std::cout<<"Your type of piece is " << type << ", and that is not in the list of chess pieces";
		}

		return possibleMoves;
	}

	list<string> ChessBoardMoves::TotalPossibleMoves(string color)
	{
		list<Chess> piecesOfColor;
		list<string> possibleMoves;
		

		for(int r = 0; r < 8; r++)
		{
			for(int f = 0; f < 8; f++)
			{
				if(board[r][f].GetColor() == color)
				{
					piecesOfColor.push_back(board[r][f]);
				}
			}
		}

		for(Chess piece : piecesOfColor)
		{
			list<string> newMoves = FindMoves(piece);
			newMoves.splice(newMoves.end(), possibleMoves);
		}

		return possibleMoves;
	}

	static int ChessBoardMoves::ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
		string str = "abcdefgh";
		return str.find_first_of(letter) + 1;
	}



    int main(){
        Chess baseObj;
        ChessBoardMoves obj;
        std::list<Chess> pieceList = baseObj.Setup();
        obj = ChessBoardMoves(pieceList);
    }
};
