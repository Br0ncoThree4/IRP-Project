using namespace std;
#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include <array>
#include <cstdlib>//includes rand() method
#ifndef NULL
#define NULL 0
#endif

class ChessBoardMoves//doesn't need to be child class of Chess bc it inherits it
{
    public:
        Chess board[8][8];
        bool whiteKingInCheck;
        bool blackKingInCheck;
		string alphabet;
        list<Chess> blackPieces;
        list<Chess> whitePieces;
        list<Chess> totalPieces;
        bool MoveWentThrough;
        list<string> previousWhiteMoves;
        list<string> previousBlackMoves;
        list<list<Chess>> boardList;
        Chess defaultChess;

        /**
         * ChessBoardMoves();
        ChessBoardMoves(list<Chess>);
        Chess board[8][8];
        bool kingInCheck; //Checks if king is in check
		static string alphabet;
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
         * 
         */
    

    ChessBoardMoves()//empty board
    {
        for (int r = 0; r < 8; r++)
        {
            for(int f = 0; f < 8; f++)
            {
                board[r][f] = Chess();
            }
        }
		alphabet = "abcdefgh";
        whiteKingInCheck = false;
        blackKingInCheck = false;
        whitePieces;
        blackPieces;
        totalPieces;
        MoveWentThrough = true;
        previousWhiteMoves;
        previousBlackMoves;
        boardList.push_back(totalPieces);
        defaultChess = Chess();
    }

    ChessBoardMoves(list<Chess> pieceList) {//Creates the 2D array that is the board, given the list of starting chess pieces
        defaultChess = Chess();
        int length = pieceList.size();
        list<Chess> tempPieceList = pieceList;
        for (int counter = 0; counter < length; counter++) //putting each chess piece on their starting squares
        {
            Chess piece = tempPieceList.front();
            tempPieceList.pop_front();
            int rank = piece.GetRank();
            int file = piece.GetFile();
            board[rank][file] = piece;
            totalPieces.push_back(piece);
            if(piece.GetColor() == "White")
            {
                whitePieces.push_back(piece);
            }
            else if(piece.GetColor() == "Black")
            {
                blackPieces.push_back(piece);
            }
        }
        for (int rank = 7; rank >= 0; rank--) { //printing the board and its square number
            for (int col = 0; col <= 7; col++) {
                if (board[rank][col].GetType() != defaultChess.GetType()) {
                    std::cout << board[rank][col].GetColor() << " " << board[rank][col].GetType() << "\t";
                }
                else {
                    std::cout << "\t"; //trying to space the board out so that even if theres nothing, the board still kind of keeps is square shape
                }
                std::cout << "(" << "abcdefgh"[col] << (rank + 1) << ")" << "\t";
                cout << "rank " << rank << ", col " << col << endl;
            }
            std::cout << endl;
        }

		alphabet = "abcdefgh";
        whiteKingInCheck = false;
        blackKingInCheck = false;
        MoveWentThrough = true;
        previousWhiteMoves = WhiteStartingMoves();
        previousBlackMoves = BlackStartingMoves();
        boardList.push_back(totalPieces);
    }
    //we also need a printing method for the chess board

    //ChessMoves insert here




	list<string> WhiteStartingMoves() //Returns starting moves for white (can be altered to make it for black, just need to change a few letters)
	{
		list<string> moves; //White Starting Moves
		//Pawn Moves
		for(int k = 0; k <= 7; k++){
			string file = alphabet.substr(k, 1);
			moves.push_back(file + "3");
			moves.push_back(file + "4");
		}
		//Knight Moves
		for(int k = 1; k <= 2; k++){
			int middleFile = k/2*5 + 1;//gets file to be either 1 or 6 (B or G)
			int startingRank = 1;
			for(int x = -1; x <= 1; x+= 2){
				string newFile = alphabet.substr(middleFile + x, 1);
				moves.push_back(newFile + to_string(startingRank + 2));
			}
		}
		return moves;
	}

    list<string> BlackStartingMoves()
    {
        list<string> moves;
        //Pawn Moves
        for(int k = 0; k <= 7; k++)
        {
            string file = to_string(alphabet[k]);
            moves.push_back(file + "6");
            moves.push_back(file + "5");
        }
        //Knight Moves
        for(int k = 1; k <= 2; k++)
        {
            int middleFile = k/2*5 + 1;//file is either 1 or 6 (B or G)
            int startingRank = 8;
            for(int x = -1; x <= 1; x += 2)
            {
                string newFile = alphabet.substr(middleFile + x, 1);
                moves.push_back(newFile + to_string(startingRank - 2));
            }
        }
        return moves;
    }

	void Move(Chess piece, string newPosition) 
    {
		string block = IsBlockingCheck(piece);//stores piece type and location (such as Ke1) or ""
        if(block != "")
        {
            cout << "This piece is blocking check from " + block + ", so it can't move";
        }
        else
        {
		    int newRank = ChangeLetterToNumber(newPosition.substr(0, 1));
		    int newFile = stoi(newPosition.substr(1, 1));

            //move the piece
            board[piece.GetRank()][piece.GetFile()] = Chess();
            board[newRank][newFile] = piece;
            
            piece.SetPosition(newPosition);//set position for the piece's instance variables 
        }
	}

    void Move(string color, string move)
    {
        string type = move.substr(0, 1);
        int newRank;
        int newFile;
        Chess piece;
        string newPosition;

        if(move.find("x") != -1)//if the x exists in the move
        {
            move = move.substr(0, move.find("x")) + move.substr(move.find("x"), 2);
            if(color == "Black")
            {
                int length = blackPieces.size();
                list<Chess> tempPieceArray = blackPieces;
                list<Chess> goodPieces;
                for(int counter = 0; counter < length; counter++)
                {
                    Chess possibleTakenPiece = tempPieceArray.front();
                    tempPieceArray.pop_front();
                    if(possibleTakenPiece.GetFile() == alphabet.find(move.substr(move.length() - 2, 1)) && possibleTakenPiece.GetRank() == stoi(move.substr(move.length() - 1, 1)))
                    {
                        //blackPieces.remove(possibleTakenPiece);
                    }
                    else
                    {
                        goodPieces.push_back(possibleTakenPiece);
                    }
                }
                blackPieces = goodPieces;
            }
            else if(color == "White")//just in case another color comes through
            {
                int length = whitePieces.size();
                list<Chess> tempPieceArray = whitePieces;
                list<Chess> goodPieces;
                for(int counter = 0; counter < length; counter++)
                {
                    Chess possibleTakenPiece = tempPieceArray.front();
                    tempPieceArray.pop_front();
                    if(possibleTakenPiece.GetFile() == alphabet.find(move.substr(move.length() - 2, 1)) && possibleTakenPiece.GetRank() == stoi(move.substr(move.length() - 1, 1)))
                    {
                        //whitePieces.remove(possibleTakenPiece);
                    }
                    else
                    {
                        goodPieces.push_back(possibleTakenPiece);
                    }
                }
                whitePieces = goodPieces;
            }
        }
        if(move.find("+") != -1)//note that the king is in check?
        {
            move = move.substr(0, move.find("+"));//would be at the end, so this would just cut it off
        }
        if(move.find("#") != -1)//end method?
        {
            move = move.substr(0, move.find("#"));//would be at the end, so this could just cut off the method (if it was true)
        }

        newPosition = move.substr(move.length() - 2, 2);

        //check for break methods
        if(move == "BOARD")
        {
            //print method of board lists
            list<list<Chess>> tempBoardList = boardList;
            for(int counter = 1; counter < boardList.size(); counter++)
            {
                list<Chess> tempBoard = tempBoardList.front();//board as a list of its pieces
                int length = tempBoard.size();
                Chess theBoard[8][8];
                for(int number = 0; number < length; number++)
                {
                    Chess piece = tempBoard.front();
                    tempBoard.pop_front();
                    int rank = piece.GetRank();
                    int file = piece.GetFile();
                    theBoard[rank][file] = piece;
                }

                tempBoardList.pop_front();
                cout << "Board number " << counter << ":";
                for(int r = 7; r >= 0; r--)//goes through the board like this so it starts at a1 and ends at h8 (bottom left is [0][0], aka a1, so that should be printed last)
                {
                    for(int c = 0; c <= 7; c++)
                    {
                        if(theBoard[r][c].GetColor() != defaultChess.GetColor())
                        {
                            Chess piece = theBoard[r][c];
                            cout << piece.GetColor() + " " << piece.GetType() << " " << alphabet.substr(piece.GetFile(), 1) << " " << piece.GetRank() << " ";
                        }
                        cout << "endl";
                    }
                }
                cout << "\n\n";
            }
        }
        else if(move == "PIECELIST")
        {
            cout << "WHITE PIECE LIST";
            int whiteLength = whitePieces.size();
            list<Chess> whiteTempList = whitePieces;
            for(int counter = 0; counter < whiteLength; counter++)
            {
                Chess piece = whiteTempList.front();
                whiteTempList.pop_front();
                cout << "White " << piece.GetType() + " " << piece.GetType() << " " << alphabet.substr(piece.GetFile(), 1) << " " + piece.GetRank() << " ";
            }
            cout << "endl";

            cout << "BLACK PIECE LIST";
            int blackLength = blackPieces.size();
            list<Chess> blackTempList = blackPieces;
            for(int counter = 0; counter < blackLength; counter++)
            {
                Chess piece = blackTempList.front();
                blackTempList.pop_front();
                cout << "Black " << piece.GetType() << " " + piece.GetType() << " " << alphabet.substr(piece.GetFile(), 1) << " " << piece.GetRank() + " ";
            }
        }

        //need to find piece that is gonna be moved (if it's a normal move)
        else if(color == "White")
        {
            list<Chess> pieces;
            list<Chess> tempPieces = whitePieces;
            int length = whitePieces.size();
            for(int counter = 0; counter < length; counter++)
            {
                Chess piece = tempPieces.front();
                tempPieces.pop_front();
                if(piece.GetType().substr(0, 1) == type || (piece.GetType() == "Knight" && type == "N"))
                {
                    pieces.push_back(piece);
                    cout << piece.GetColor() << " " << piece.GetType() << endl;
                }
            }
            if(pieces.size() == 1)
            {
                piece = pieces.front();
            }
            else
            {
                int length = pieces.size();
                list<Chess> tempPieces = pieces;
                for(int counter = 0; counter < length; counter++)
                {
                    Chess possiblePiece = tempPieces.front();
                    tempPieces.pop_front();
                    if(move.length() == 3)//Re1 (can't use anything to find location)
                    {
                        list<string> possibleMoves = FindMoves(possiblePiece);
                        for(string possibleMove : possibleMoves)
                        {
                            if(possibleMove == move.substr(1, 2))//if possibleMove = the move
                            {
                                piece = possiblePiece;
                            }
                        }
                    }
                    else if(move.length() == 4)//Ree1 or R1e1
                    {
                        int file;
                        int rank;
                        if(alphabet.find(move.substr(1, 1)) == -1)//second character isn't a file (second character is a rank number)
                        {
                            rank = stoi(move.substr(1, 1));
                            if(possiblePiece.GetRank() == rank)
                            {
                                //piece = possiblePiece;
                            }
                        }
                        else//second character is a letter (second character is a file letter)
                        {
                            file = alphabet.find(move.substr(1, 1));
                            if(possiblePiece.GetFile() == file)
                            {
                                //piece = possiblePiece;
                            }
                        }   
                    }
                    else if(move.length() == 5)//Re1e2
                    {
                        int rank = stoi(move.substr(2, 1));
                        int file = alphabet.find(move.substr(1, 1));
                        piece = board[rank][file];
                    }
                }
            }
        }
        else//color == black
        {
            list<Chess> pieces;
            list<Chess> tempPieces = blackPieces;
            int length = blackPieces.size();
            for(int counter = 0; counter < length; counter++)
            {
                Chess piece = tempPieces.front();
                tempPieces.pop_front();
                if(piece.GetType().substr(0, 1) == type || (piece.GetType() == "Knight" && type == "N"))
                {
                    pieces.push_back(piece);
                    cout << piece.GetColor() << " " << piece.GetType() << endl;
                }
            }
            if(pieces.size() == 1)
            {
                piece = pieces.front();
            }
            else
            {
                if(move.length() == 5)//Re1e2
                {
                    int rank = stoi(move.substr(2, 1));
                    int file = alphabet.find(move.substr(1, 1));
                    piece = board[rank - 1][file];
                    cout << "rank is " << rank << ", file is " << file << ", the piece is a " << piece.GetColor() << " " << piece.GetType() << endl;
                }
                else
                {
                    list<Chess> tempPieces = pieces;
                    int length = pieces.size();
                    for(int counter = 0; counter < length; counter++)
                    {
                        Chess possiblePiece = tempPieces.front();
                        tempPieces.pop_front();
                        if(move.length() == 3)//Re1 (can't use anything to find location)
                        {
                            list<string> possibleMoves = FindMoves(possiblePiece);
                            for(string possibleMove : possibleMoves)
                            {
                                if(possibleMove == move.substr(1, 2))//if possibleMove = the move
                                {
                                    piece = possiblePiece;
                                }
                            }
                        }
                        else if(move.length() == 4)//Ree1 or R1e1
                        {
                            int file;
                            int rank;
                            if(alphabet.find(move.substr(1, 1)) == -1)//second character isn't a file (second character is a rank number)
                            {
                                rank = stoi(move.substr(1, 1)) - 1;
                                if(possiblePiece.GetRank() == rank)
                                {
                                    //piece = possiblePiece;
                                }
                            }
                            else//second character is a letter (second character is a file letter)
                            {
                                file = alphabet.find(move.substr(1, 1));
                                if(possiblePiece.GetFile() == file)
                                {
                                    //piece = possiblePiece;
                                }
                            }   
                        }
                    }
                }
            }
            //cout << piece.GetColor() << " piece found at rank = " << piece.GetRank() << " and file = " << piece.GetFile() << endl;
            cout << piece.GetColor() << " " << piece.GetType() << " found at rank " << piece.GetRank() << " and file " << piece.GetFile() << endl;
        }

        //make sure piece isn't pinned
        string block = IsBlockingCheck(piece);//stores piece type and location (such as Qd1) or ""
        if(block != "")
        {
            cout << "This piece is blocking check from " + block + ", so it can't move";
        }
        else//if not pinned, we can move it
        {
		    cout << "This piece is not blocking a check" << endl;
            int newRank = stoi(newPosition.substr(1, 1)) - 1;//ranks 1-8 converted to ranks 0-7
		    int newFile = alphabet.find(newPosition.substr(0, 1));

            //move the piece
            cout << "the piece was moved from " << alphabet.substr(piece.GetFile(), 1) << (piece.GetRank() + 1) << " to " << alphabet.substr(newFile, 1) << (newRank + 1) << endl;
            
            if(color == "White")
            {
                //whitePieces.remove(piece);
                int length = whitePieces.size();
                cout << "Old length: " << length << endl;
                list<Chess> tempPieces = whitePieces;
                list<Chess> newPieces;
                for(int counter = 0; counter < length; counter++)
                {
                    Chess tempPiece = tempPieces.front();
                    tempPieces.pop_front();
                    if(!(tempPiece.GetType() == piece.GetType()) || !(tempPiece.GetFile() == piece.GetFile()) || !(tempPiece.GetRank() == piece.GetRank()))
                    {
                        newPieces.push_front(tempPiece);
                    }
                }
                whitePieces = newPieces;
                cout << "New length: " << whitePieces.size() << endl;
            }
            else
            {
                //blackPieces.remove(piece);
                int length = blackPieces.size();
                cout << "Old length: " << length << endl;
                list<Chess> tempPieces = blackPieces;
                list<Chess> newPieces;
                for(int counter = 0; counter < length; counter++)
                {
                    Chess tempPiece = tempPieces.front();
                    tempPieces.pop_front();
                    if(!(tempPiece.GetType() == piece.GetType()) || !(tempPiece.GetFile() == piece.GetFile()) || !(tempPiece.GetRank() == piece.GetRank()))
                    {
                        newPieces.push_front(tempPiece);
                    }
                }
                blackPieces = newPieces;
                cout << "New length: " << blackPieces.size() << endl;
            }
            cout << "The piece has been removed from its list" << endl;
            board[piece.GetRank()][piece.GetFile()] = Chess();
            board[newRank][newFile] = piece;
            
            piece.SetPosition(newPosition);//set position for the piece's instance variables 

            cout << "New Position of piece: " << alphabet.substr(piece.GetFile(), 1) << (piece.GetRank() + 1) << endl;
            if(color == "White")
            {
                whitePieces.push_back(piece);
                cout << "Newer Length: " << whitePieces.size() << endl;
                list<Chess> tempPieces = whitePieces;
                cout << "whitePieces" << endl;
                for(int counter = 0; counter < whitePieces.size(); counter++)
                {
                    Chess tempPiece = tempPieces.front();
                    tempPieces.pop_front();
                    cout << tempPiece.GetColor() << " " << tempPiece.GetType() << " " << alphabet.substr(tempPiece.GetFile(), 1) << tempPiece.GetRank() + 1 << "\t";
                }
                cout << endl;
            }
            else
            {
                blackPieces.push_back(piece);
                cout << "Newer Length: " << blackPieces.size() << endl;
                list<Chess> tempPieces = blackPieces;
                cout << "blackPieces" << endl;
                for(int counter = 0; counter < blackPieces.size(); counter++)
                {
                    Chess tempPiece = tempPieces.front();
                    tempPieces.pop_front();
                    cout << tempPiece.GetColor() << " " << tempPiece.GetType() << " " << alphabet.substr(tempPiece.GetFile(), 1) << tempPiece.GetRank() + 1 << "\t";
                }
                cout << endl;
            }
        }
    }


	string IsBlockingCheck(Chess piece)//will return piece type and location that is getting blocked or will return ""
	{
        bool isBlockingDiagonalCheck = false;
        bool isBlockingLineCheck = false;
        int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank);
        string pieceGettingBlocked;
        string areaBlocking;
        
        //If king is in open sight of piece (need to check all diagonals and lines)

        //If the piece is blocking a bishop/queen on diagonals or rook/queen on files, it should keep the threatening piece's position

        int kingFile;
        int kingRank;
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                Chess possibleKing = board[row][col];
                if(possibleKing.GetType() == "King" && possibleKing.GetColor() == piece.GetColor())//piece is the correct king
                {
                    kingFile = possibleKing.GetFile();
                    kingRank = possibleKing.GetRank();
                }
            }
        }
        
        //diagonals check
        int counter = 1;
        if((kingFile - kingRank) == (currentFile - currentRank))//on bottom left to top right diagonal
        {
            bool isBlockingCheck = true;
            bool isToRightAndAbove = kingFile > currentFile;//if kingFile > currentFile, king is to the right of currentPiece, so king is also above currentPiece
            bool checkToLeftAndBelow;
            for(int diff = abs(kingFile - currentFile) - 1; diff > 0; diff++)//diff is the difference btwn current position and king position (kingFile != currentFile if the conditional runs)
            {
                if(isToRightAndAbove)//king is to the right of current piece
                {
                    checkToLeftAndBelow = true;
                    if(board[kingRank - diff][kingFile - diff].GetColor() == "White" || board[kingRank - diff][kingFile - diff].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
                else//king is to the left of current piece
                {
                    checkToLeftAndBelow = false;//check to the right of currentPiece
                    if(board[kingRank + diff][kingFile + diff].GetColor() == "White" || board[kingRank + diff][kingFile + diff].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
            }
            isBlockingDiagonalCheck = isBlockingCheck;//if the line of sight is there, set iBDC to true; if not, make it false
            //need to check if there's an opposite queen or bishop on the diagonal
            if(isBlockingDiagonalCheck)
            {
                if(checkToLeftAndBelow)//check below and to the left of currentPiece for queen/bishop
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank - x, currentFile - x))
                        {
                            Chess possibleBlocker = board[currentRank - x][currentFile + x];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //increment, square is empty
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//is piece of the same color, can't be checking the king
                            }
                            else//possibleBlocker is other color
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Bishop")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop is it isn't on board, can return "" because there's nothing else that could be trying to check the king
                        }
                    }
                }
                else//check above and to the right of currentPiece for queen/bishop
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank + x, currentFile + x))
                        {
                            Chess possibleBlocker = board[currentRank][currentFile + x];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //square is empty, keep looking (this just ends this iteration of the for loop and allows x to increment)
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//ends loop: same color, can't be blocking check, can return ""
                            }
                            else
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Bishop")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop, can return ""
                        }
                    }
                }
            }
        }
        else if((kingFile + kingRank) == (currentFile + currentRank))//top left to bottom right diagonal
        {
            bool isBlockingCheck = true;
            bool kingToLeftAndAbove = kingFile < currentFile;//if king is to the left of currentPiece, he will also be above it, or neither are true
            bool checkToRightAndBelow;
            for(int diff = abs(kingFile - currentFile) - 1; diff > 0; diff++)
            {
                if(kingToLeftAndAbove)//king is to the left (and above) the current piece
                {
                    checkToRightAndBelow = true;
                    if(board[kingFile - diff][kingRank + diff].GetColor() == "White" || board[kingFile - diff][kingRank + diff].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
                else//king is to the right (and below) the current piece
                {
                    checkToRightAndBelow = false;
                    if(board[kingFile + diff][kingRank - diff].GetColor() == "White" || board[kingFile + diff][kingRank - diff].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
            }
            isBlockingDiagonalCheck = isBlockingCheck;
            //need to check if there's an opposite queen or bishop on the diagonal
            if(isBlockingDiagonalCheck)
            {
                if(checkToRightAndBelow)//check below and to the right of currentPiece for queen/bishop
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank - x, currentFile + x))
                        {
                            Chess possibleBlocker = board[currentRank - x][currentFile + x];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //increment, square is empty
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//is piece of the same color, can't be checking the king
                            }
                            else//possibleBlocker is other color
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Bishop")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop is it isn't on board, can return "" because there's nothing else that could be trying to check the king
                        }
                    }
                }
                else//check above and to the left currentPiece for queen/bishop
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank + x, currentFile - x))
                        {
                            Chess possibleBlocker = board[currentRank][currentFile + x];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //square is empty, keep looking (this just ends this iteration of the for loop and allows x to increment)
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//ends loop: same color, can't be blocking check, can return ""
                            }
                            else
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Rook")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop, can return ""
                        }
                    }
                }
            }
        }
        //line checks
        else if(kingFile == currentFile)
        {
            bool isBlockingCheck = true;
            bool kingIsAbove = kingRank > currentRank;
            bool belowCheck;//belowCheck is false = check above the currentPiece (only used if piece is blocking check)
            for(int diff = abs(kingRank - currentRank) - 1; diff > 0; diff++)
            {
                if(kingIsAbove)//king is above the currentpiece
                {
                    belowCheck = true;
                    if(board[kingFile][kingRank - diff].GetColor() != defaultChess.GetColor())
                    {
                        isBlockingCheck = false;
                    }
                }
                else//king is below the currentPiece
                {
                    belowCheck = false;
                    if(board[kingFile][currentRank + diff].GetColor() == "White" || board[kingFile][currentRank + diff].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
            }

            isBlockingLineCheck = isBlockingCheck;
            //need to do check for rook/queen on file pinching currentPiece to king if isBlockingCheck is true
            if(isBlockingLineCheck)
            {
                if(belowCheck)//check below the currentPiece for queen/rook
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank - x, currentFile))
                        {
                            Chess possibleBlocker = board[currentRank - x][currentFile];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //increment
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//is piece of the same color, can't be checking the king
                            }
                            else//possibleBlocker is other color
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Rook")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop is it isn't on board, can return "" because there's nothing else that could be trying to check the king
                        }
                    }
                }
                else//check above the currentPiece for queen/rook
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank + x, currentFile))
                        {
                            Chess possibleBlocker = board[currentRank + x][currentFile];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //square is empty, keep looking (this just ends this iteration of the for loop and allows x to increment)
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//ends loop: same color, can't be blocking check, can return ""
                            }
                            else
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Rook")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else//if not on board
                        {
                            return "";//ends the loop, can return ""
                        }
                    }
                }
            }
        }
        else if(kingRank == currentRank)
        {
            bool isBlockingCheck = true;
            bool kingToRight = kingFile > currentFile;
            bool leftCheck;//rightCheck is false = check to the right of the currentPiece (only used if piece is blocking check)
            for(int diff = abs(kingFile - currentFile) - 1; diff > 0; diff++)
            {
                if(kingToRight)//king is to the right of the currentPiece
                {
                    leftCheck = true;
                    if(board[kingFile - diff][kingRank].GetColor() == "White" || board[kingFile - diff][kingRank].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
                else//king is to the left of the currentPiece
                {
                    leftCheck = false;
                    if(board[kingFile + diff][kingRank].GetColor() == "White" || board[kingFile + diff][kingRank].GetColor() == "Black")
                    {
                        isBlockingCheck = false;
                    }
                }
            }
            isBlockingLineCheck = isBlockingCheck;
            //need to do check for rook/queen on file pinching currentPiece to king if isBlockingCheck is true
            if(isBlockingLineCheck)
            {
                if(leftCheck)//check to the left of currentPiece for queen/rook
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank, currentFile - x))
                        {
                            Chess possibleBlocker = board[currentRank][currentFile - x];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //increment
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//is piece of the same color, can't be checking the king
                            }
                            else//possibleBlocker is other color
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Rook")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop is it isn't on board, can return "" because there's nothing else that could be trying to check the king
                        }
                    }
                }
                else//check to the right of currentPiece for queen/rook
                {
                    for(int x = 1; x <= 6; x++)
                    {
                        if(IsOnBoard(currentRank, currentFile + x))
                        {
                            Chess possibleBlocker = board[currentRank][currentFile + x];
                            if(possibleBlocker.GetColor() == Chess().GetColor())
                            {
                                //square is empty, keep looking (this just ends this iteration of the for loop and allows x to increment)
                            }
                            else if(possibleBlocker.GetColor() == piece.GetColor())
                            {
                                return "";//ends loop: same color, can't be blocking check, can return ""
                            }
                            else
                            {
                                if(possibleBlocker.GetType() == "Queen" || possibleBlocker.GetType() == "Rook")
                                {
                                    pieceGettingBlocked = possibleBlocker.GetType().substr(0, 1) + alphabet.substr(possibleBlocker.GetFile(), 1) + to_string(possibleBlocker.GetRank() + 1);//square has piece that is threatening a check, cannot move this piece
                                    return pieceGettingBlocked; //returns piece type and location (Ke1)
                                }
                                else
                                {
                                    return "";//piece won't check King
                                }
                            }
                        }
                        else
                        {
                            return "";//ends the loop, can return ""
                        }
                    }
                }
            }
        }

        return "";//Only gets run if there's no diagonal/line getting blocked, so there's no check getting blocked
        
	}

	bool IsInCheck(Chess king, list<string> possibleMoves)//See if king is in check (possibleMoves is the list of moves of the opposite color than the king)
	{
		string position = alphabet.substr(king.GetFile(), 1) + to_string(king.GetRank() + 1);
		for(string move: possibleMoves)
		{
			if(move == position)
			{
				return true;
			}
		}
		return false;
	}

	static bool IsOnBoard(string position)
	{
		int rank = ChangeLetterToNumber(position.substr(0, 1));
		int file = stoi(position.substr(1, 1));
		if((rank > -1 && rank < 8) && (file > -1 && file < 8))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static bool IsOnBoard(int rank, int file)
	{
		
		if((rank > -1 && rank < 8) && (file > -1 && file < 8))
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	list<string> checkKingMoves(Chess piece) // will return K*file letter**rank number (as a string)*
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
		string type = "K";

		if("King" != piece.GetType())
		{
			cout << "Your piece is a " << piece.GetType() << ", not a King, as was expected by the checkKingMoves method";
			return possibleMoves;
		}

		
		if(IsOnBoard(currentRank + 1, currentFile) && board[currentRank + 1][currentFile].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile) && board[currentRank - 1][currentFile].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 1, currentFile + 1) && board[currentRank + 1][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile + 1) && board[currentRank - 1][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank - 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 1, currentFile - 1) && board[currentRank + 1][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile - 1) && board[currentRank - 1][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank - 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank, currentFile + 1) && board[currentRank][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank, currentFile - 1) && board[currentRank][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 1);
			possibleMoves.push_back(position);
		}
		
		return possibleMoves;
	}

	list<string> checkQueenMoves(Chess piece)
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
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
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank + counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank + counter][currentFile + counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank - counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank - counter][currentFile - counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank - counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank - counter][currentFile + counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank + counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank + counter][currentFile - counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank + counter][currentFile].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank - counter][currentFile].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank][currentFile + counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank][currentFile - counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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

	list<string> checkBishopMoves(Chess piece) //will return B*file letter**rank number (as string)*
	{
		std::list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
		string type = "B";

		if(type != piece.GetType().substr(0,1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Bishop, as was expected by the checkBishopMoves method";
			return possibleMoves;
		}

        //bishop moves
        int counter = 1;
        do{
            if(IsOnBoard(currentRank + counter, currentFile + counter))
            {
                if(board[currentRank + counter][currentFile + counter].GetColor() != piece.GetColor())//square is open or can be taken
                {
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank + counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank + counter][currentFile + counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank - counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank - counter][currentFile - counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank - counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank - counter][currentFile + counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank + counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank + counter][currentFile - counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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

	list<string> checkKnightMoves(Chess piece) //Will return Ng1f3
	{
		list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
		string type = "N";

		if("Knight" != piece.GetType())
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Knight, as was expected by the checkKnightMoves method";
			return possibleMoves;
		}

		if(IsOnBoard(currentRank + 1, currentFile + 2) && board[currentRank + 1][currentFile + 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 2, 1) + to_string(currentRank + 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile + 2) && board[currentRank - 1][currentFile + 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 2, 1) + to_string(currentRank - 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 1, currentFile - 2) && board[currentRank + 1][currentFile - 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 2, 1) + to_string(currentRank + 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 1, currentFile - 2) && board[currentRank - 1][currentFile - 2].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 2, 1) + to_string(currentRank - 1 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 2, currentFile + 1) && board[currentRank + 2][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 2 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank + 2, currentFile - 1) && board[currentRank + 2][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 2 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 2, currentFile + 1) && board[currentRank - 2][currentFile + 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank - 2 + 1);
			possibleMoves.push_back(position);
		}
		if(IsOnBoard(currentRank - 2, currentFile - 1) && board[currentRank - 2][currentFile - 1].GetColor() != piece.GetColor())
		{
			string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank - 2 + 1);
			possibleMoves.push_back(position);
		}

		return possibleMoves;
	}

	list<string> checkRookMoves(Chess piece)
	{
		list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
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
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank + counter][currentFile].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - counter + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank - counter][currentFile].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile + counter, 1) + to_string(currentRank + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank][currentFile + counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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
                    string position = type + currentPosition + alphabet.substr(currentFile - counter, 1) + to_string(currentRank + 1);
                    possibleMoves.push_back(position);
                    if(board[currentRank][currentFile - counter].GetColor() == defaultChess.GetColor())
                    {
                        counter++;
                    }
                    else//"position" is taking the a piece
                    {
                        counter = 8;
                    }
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

	list<string> checkPawnMoves(Chess piece)
	{
		list<string> possibleMoves;
		int currentFile = piece.GetFile();
		int currentRank = piece.GetRank();
        string currentPosition = alphabet.substr(currentFile, 1) + to_string(currentRank + 1);
		string type = "P";

		if(type != piece.GetType().substr(0, 1))
		{
			cout << "Your piece is a " << piece.GetType() << ", not a Pawn, as was expected by the checkPawnMoves method";
			return possibleMoves;
		}

        if(piece.GetColor() == "White")
        {
            if(IsOnBoard(currentRank + 1, currentFile) && board[currentRank + 1][currentFile].GetColor() == defaultChess.GetColor())
            {
                string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + 1 + 1);
                possibleMoves.push_back(position);
            }
            if(IsOnBoard(currentRank + 1, currentFile + 1) && (board[currentRank + 1][currentFile + 1].GetColor() != piece.GetColor() && board[currentRank + 1][currentFile + 1].GetColor() != defaultChess.GetColor()))
            {
                string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank + 1 + 1);
                possibleMoves.push_back(position);
            }
            if(IsOnBoard(currentRank + 1, currentFile - 1) && (board[currentRank + 1][currentFile - 1].GetColor() != piece.GetColor() && board[currentRank + 1][currentFile - 1].GetColor() != defaultChess.GetColor()))
            {
                string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank + 1 + 1);
                possibleMoves.push_back(position);
            }
            if(IsOnBoard(currentRank + 2, currentFile) && board[currentRank + 2][currentFile].GetColor() == defaultChess.GetColor() && currentRank == 1)
            {
                string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank + 2 + 1);
                possibleMoves.push_back(position);
            }
        }
        else
        {
            if(IsOnBoard(currentRank - 1, currentFile) && board[currentRank - 1][currentFile].GetColor() == defaultChess.GetColor())
            {
                string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - 1 + 1);
                possibleMoves.push_back(position);
            }
            if(IsOnBoard(currentRank - 1, currentFile + 1) && (board[currentRank - 1][currentFile + 1].GetColor() != piece.GetColor() && board[currentRank - 1][currentFile + 1].GetColor() != defaultChess.GetColor()))
            {
                string position = type + currentPosition + alphabet.substr(currentFile + 1, 1) + to_string(currentRank - 1 + 1);
                possibleMoves.push_back(position);
            }
            if(IsOnBoard(currentRank - 1, currentFile - 1) && (board[currentRank - 1][currentFile - 1].GetColor() != piece.GetColor() && board[currentRank - 1][currentFile - 1].GetColor() != defaultChess.GetColor()))
            {
                string position = type + currentPosition + alphabet.substr(currentFile - 1, 1) + to_string(currentRank - 1 + 1);
                possibleMoves.push_back(position);
            }
            if(IsOnBoard(currentRank - 2, currentFile) && board[currentRank - 2][currentFile].GetColor() == defaultChess.GetColor() && currentRank == 6)
            {
                string position = type + currentPosition + alphabet.substr(currentFile, 1) + to_string(currentRank - 2 + 1);
                possibleMoves.push_back(position);
            }
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

    list<string> lineOfSight(string color)//intakes color, returns the squares that are getting watched by the other color(could be moved to by those pieces)
    {
        list<Chess> piecesOfColor;
        list<string> coveredSquares;
        if(color == "White")
        {
            piecesOfColor = blackPieces;
        }
        else
        {
            piecesOfColor = whitePieces;
        }
        
        list<Chess> tempPiecesOfColor = piecesOfColor;
        for(int counter = 0; counter < piecesOfColor.size(); counter++)
        {
            Chess piece = tempPiecesOfColor.front();
            tempPiecesOfColor.pop_front();
            list<string> moves = FindMoves(piece);
            for(int num = 0; num < moves.size(); num++)
            {
                string move = moves.front();
                moves.pop_front();
                coveredSquares.push_back(move);
            }
        }

        return coveredSquares;
    }

    bool SameFile(string move, string file)
    {
        return (file == move.substr(3, 1));
    }

    bool SameRank(string move, int rank)
    {
        return (rank == stoi(move.substr(4, 1)));
    }

    list<string> movesOutOfCheck(string color, list<string> possibleMoves)
    {
        list<Chess> piecesOfColor;
        list<Chess> piecesOfOtherColor;
        list<string> otherColorMoves;
        list<Chess> piecesCheckingKing;
        Chess king;
        string kingPosition;
        if(color == "White")
        {
            piecesOfColor = whitePieces;
            piecesOfOtherColor = blackPieces;
        }
        else
        {
            piecesOfColor = blackPieces;
            piecesOfOtherColor = whitePieces;
        }

        //find king and its location
         list<Chess> tempPiecesOfColor = piecesOfColor;
        for(int counter = 0; counter < piecesOfColor.size(); counter++)
        {
            Chess piece = tempPiecesOfColor.front();
            tempPiecesOfColor.pop_front();
            if(piece.GetType() == "King")
            {
                king = piece;
                kingPosition = alphabet.substr(king.GetRank(), 1) + to_string(king.GetFile());
            }
        }

        //find pieces checking the king (in case there's a double attack)
        otherColorMoves = lineOfSight(color);
        for(string move : otherColorMoves)
        {
            if(move.substr(3, 2) == kingPosition)
            {
                piecesCheckingKing.push_back(board[stoi(move.substr(1, 1))][stoi(move.substr(2, 1))]);
            }
        }

        if(piecesCheckingKing.size() == 1)//can block, take, or move away
        {
            Chess checkingPiece = piecesCheckingKing.front();
            for(string move : possibleMoves)
            {
                if(checkingPiece.GetType() == "Rook")
                {
                    if(checkingPiece.GetFile() == king.GetFile())//same file: only allow king moves off file and moves blocking file
                    {
                        if(move.substr(0, 1) == "K")//king: move off file
                        {
                            if(move.substr(3, 1) == kingPosition.substr(0, 1))
                            {
                                possibleMoves.remove(move); //remove king move if it's on the same file that it is already on
                            }
                        }
                        else if(move.substr(3, 1) != kingPosition.substr(0, 1))//not king and not same file (this move can't be blocking check, remove it)
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is same file, could be blocking check (move must be btwn king and checkingPiece, including checkingPiece's square)
                        {
                            int cPRank = checkingPiece.GetRank();
                            int moveRank = stoi(move.substr(4, 1));
                            int kingRank = king.GetRank();
                            if(kingRank > cPRank)//king is above checkingPiece
                            {
                                if(moveRank > kingRank)//move is above king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank < cPRank)//move is below checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else//king is below checkingPiece
                            {
                                if(moveRank < kingRank)//move is below king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank > cPRank)//move is above checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                    else//same rank: only allow king moves off rank and moves blocking rank
                    {
                    
                        if(move.substr(0, 1) == "K")//king: move off rank
                        {
                            if(move.substr(4, 1) == kingPosition.substr(1, 1))
                            {
                                possibleMoves.remove(move); //remove king move if it's on the same rank that it is already on
                            }
                        }
                        else if(move.substr(4, 1) != kingPosition.substr(1, 1))//not king and not same rank (this move can't be blocking check, remove it)
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is same rank, could be blocking check (move must be btwn king and checkingPiece, including checkingPiece's square)
                        {
                            int cPFile = checkingPiece.GetFile();
                            int moveFile = stoi(move.substr(3, 1));
                            int kingFile = king.GetFile();
                            if(kingFile > cPFile)//king is above checkingPiece
                            {
                                if(moveFile > kingFile)//move is above king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveFile < cPFile)//move is below checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else//king is below checkingPiece
                            {
                                if(moveFile < kingFile)//move is below king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveFile > cPFile)//move is above checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                }
            
                else if(checkingPiece.GetType() == "Bishop")//allow moves on diagonal that block check or take
                {
                    if((checkingPiece.GetFile() - king.GetFile()) == (checkingPiece.GetRank() - king.GetRank()))//bottom left to top right diagonal
                    {
                        if(move.substr(0, 1) == "K")//king: move off diagonal
                        {
                            if(alphabet.find(move.substr(3, 1)) - king.GetFile() == stoi(move.substr(4, 1)) - king.GetRank())
                            {
                                possibleMoves.remove(move);
                            }
                        }
                        else if(alphabet.find(move.substr(3, 1)) - checkingPiece.GetFile() != stoi(move.substr(4, 1)) - checkingPiece.GetRank())//piece isn't king and move isn't on diagonal
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is on diagonal (can check file or rank to find relative location of pieces, will do rank bc it's a number)
                        {
                            int cPRank = checkingPiece.GetRank();
                            int kingRank = king.GetRank();
                            int moveRank = stoi(move.substr(4, 1));
                            if(kingRank > cPRank)//king is above the checkingPiece
                            {
                                if(moveRank > kingRank)//move is above the King
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank < cPRank)//move is below the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else //kingRank < cPRank; king is below the checkingPiece
                            {
                                if(moveRank < kingRank)//move is below the king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank > cPRank)//move is above the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                    else //top left to bottom right diagonal (file - x = rank + x for positive or negative values of x)()
                    {
                        if(move.substr(0, 1) == "K")//king: move off diagonal
                        {
                            if((king.GetFile() + king.GetRank()) == (alphabet.find(move.substr(3, 1)) + stoi(move.substr(4, 1))))
                            {
                                possibleMoves.remove(move);
                            }
                        }
                        else if((checkingPiece.GetRank() + checkingPiece.GetFile()) != (stoi(move.substr(4, 1)) + alphabet.find(move.substr(3, 1))))//piece isn't king and move isn't on diagonal
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is on diagonal (can check file or rank to find relative location of pieces, will do rank bc it's a number)
                        {
                            int cPRank = checkingPiece.GetRank();
                            int kingRank = king.GetRank();
                            int moveRank = stoi(move.substr(4, 1));
                            if(kingRank > cPRank)//king is above the checkingPiece
                            {
                                if(moveRank > kingRank)//move is above the King
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank < cPRank)//move is below the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else //kingRank < cPRank; king is to the left the checkingPiece
                            {
                                if(moveRank < kingRank)//move is below the king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank > cPRank)//move is above the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                }

                else if(checkingPiece.GetType() == "Queen")//find out whether it's diagonal or line check, do rook or bishop checks
                {
                    
                    //rook ones
                    if(checkingPiece.GetFile() == king.GetFile())//same file: only allow king moves off file and moves blocking file
                    {
                        if(move.substr(0, 1) == "K")//king: move off file
                        {
                            if(move.substr(3, 1) == kingPosition.substr(0, 1))
                            {
                                possibleMoves.remove(move); //remove king move if it's on the same file that it is already on
                            }
                        }
                        else if(move.substr(3, 1) != kingPosition.substr(0, 1))//not king and not same file (this move can't be blocking check, remove it)
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is same file, could be blocking check (move must be btwn king and checkingPiece, including checkingPiece's square)
                        {
                            int cPRank = checkingPiece.GetRank();
                            int moveRank = stoi(move.substr(4, 1));
                            int kingRank = king.GetRank();
                            if(kingRank > cPRank)//king is above checkingPiece
                            {
                                if(moveRank > kingRank)//move is above king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank < cPRank)//move is below checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else//king is below checkingPiece
                            {
                                if(moveRank < kingRank)//move is below king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank > cPRank)//move is above checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                    else if (king.GetRank() == stoi(move.substr(4, 1)))//same rank: only allow king moves off rank and moves blocking rank
                    {
                    
                        if(move.substr(0, 1) == "K")//king: move off rank
                        {
                            if(stoi(move.substr(4, 1)) == king.GetRank())
                            {
                                possibleMoves.remove(move); //remove king move if it's on the same rank that it is already on
                            }
                        }
                        else if(move.substr(4, 1) != kingPosition.substr(1, 1))//not king and not same rank (this move can't be blocking check, remove it)
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is same rank, could be blocking check (move must be btwn king and checkingPiece, including checkingPiece's square)
                        {
                            int cPFile = checkingPiece.GetFile();
                            int moveFile = stoi(move.substr(3, 1));
                            int kingFile = king.GetFile();
                            if(kingFile > cPFile)//king is above checkingPiece
                            {
                                if(moveFile > kingFile)//move is above king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveFile < cPFile)//move is below checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else//king is below checkingPiece
                            {
                                if(moveFile < kingFile)//move is below king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveFile > cPFile)//move is above checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }

                    //bishop ones
                    else if((checkingPiece.GetFile() - king.GetFile()) == (checkingPiece.GetRank() - king.GetRank()))//bottom left to top right diagonal
                    {
                        if(move.substr(0, 1) == "K")//king: move off diagonal
                        {
                            if(alphabet.find(move.substr(3, 1)) - king.GetFile() == stoi(move.substr(4, 1)) - king.GetRank())
                            {
                                possibleMoves.remove(move);
                            }
                        }
                        else if(alphabet.find(move.substr(3, 1)) - checkingPiece.GetFile() != stoi(move.substr(4, 1)) - checkingPiece.GetRank())//piece isn't king and move isn't on diagonal
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is on diagonal (can check file or rank to find relative location of pieces, will do rank bc it's a number)
                        {
                            int cPRank = checkingPiece.GetRank();
                            int kingRank = king.GetRank();
                            int moveRank = stoi(move.substr(4, 1));
                            if(kingRank > cPRank)//king is above the checkingPiece
                            {
                                if(moveRank > kingRank)//move is above the King
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank < cPRank)//move is below the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else //kingRank < cPRank; king is below the checkingPiece
                            {
                                if(moveRank < kingRank)//move is below the king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank > cPRank)//move is above the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                    else //top left to bottom right diagonal (file - x = rank + x for positive or negative values of x)()
                    {
                        if(move.substr(0, 1) == "K")//king: move off diagonal
                        {
                            if((king.GetFile() + king.GetRank()) == (alphabet.find(move.substr(3, 1)) + stoi(move.substr(4, 1))))
                            {
                                possibleMoves.remove(move);
                            }
                        }
                        else if((checkingPiece.GetRank() + checkingPiece.GetFile()) != (stoi(move.substr(4, 1)) + alphabet.find(move.substr(3, 1))))//piece isn't king and move isn't on diagonal
                        {
                            possibleMoves.remove(move);
                        }
                        else//move is on diagonal (can check file or rank to find relative location of pieces, will do rank bc it's a number)
                        {
                            int cPRank = checkingPiece.GetRank();
                            int kingRank = king.GetRank();
                            int moveRank = stoi(move.substr(4, 1));
                            if(kingRank > cPRank)//king is above the checkingPiece
                            {
                                if(moveRank > kingRank)//move is above the King
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank < cPRank)//move is below the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                            else //kingRank < cPRank; king is to the left the checkingPiece
                            {
                                if(moveRank < kingRank)//move is below the king
                                {
                                    possibleMoves.remove(move);
                                }
                                else if(moveRank > cPRank)//move is above the checkingPiece
                                {
                                    possibleMoves.remove(move);
                                }
                                //move would block check, keep it in
                            }
                        }
                    }
                }

                else if(checkingPiece.GetType() == "Knight")//piece must be taken or king move out of the way
                {
                    if(move.substr(0, 1) == "K")//king: must move out of way of knight
                    {
                        list<string> knightMoves = FindMoves(checkingPiece);
                        for(string kMove : knightMoves)
                        {
                            if(move == kMove)
                            {
                                possibleMoves.remove(move);
                            }
                            //move is king move out of way of king: its good
                        }
                    }
                    else//piece must be taken
                    {
                        if(move.substr(3, 2) != alphabet.substr(checkingPiece.GetFile(), 1) + to_string(checkingPiece.GetRank()))//move != cP's position
                        {
                            possibleMoves.remove(move);
                        }
                    }
                }
            }
        }


        else if(piecesCheckingKing.size() > 1)//must move king
        {
            possibleMoves = FindMoves(king);
            for(string move : possibleMoves)
            {
                for(string pMove : otherColorMoves)
                {
                    if(move == pMove)//check if new square is covered by another piece
                    {
                        possibleMoves.remove(move);
                    }
                }
            }
        }

        return possibleMoves;
    }

	void LegalMove(Chess piece, string newPosition)//Make sure move isn't out of bounds or creating a check
	{
		string type = piece.GetType();
		list<string> possibleMoves;
		//Finding list of legal moves, depending on each piece
		possibleMoves = FindMoves(piece);

        //editing list if piece is blocking check
        

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

	list<string> FindMoves(Chess piece)
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

	list<string> TotalPossibleMoves(string color)
	{
		list<Chess> piecesOfColor;
		list<string> possibleMoves;
		

		if(color == "White")
        {
            piecesOfColor = whitePieces;
        }
        else
        {
            piecesOfColor = blackPieces;
        }

        //find possible moves

        int length = piecesOfColor.size();
        list<Chess> chessPieces = piecesOfColor;
		for(int counter = 0; counter < length; counter++)
		{
            Chess piece = chessPieces.front();
            chessPieces.pop_front();
			list<string> newMoves = FindMoves(piece);
			possibleMoves.splice(possibleMoves.begin(), newMoves);
		}

		return possibleMoves;
	}

    list<string> TotalLegalMoves(string color, list<string> possibleMoves)
    {
        list<string> moves;
        
        //check if king is in check and refine possibleMoves if it is
        if(color == "White")
        {
            if(whiteKingInCheck)//only allow moves that would move out of check, block check, or remove checkingPiece
            {
                moves = movesOutOfCheck(color, possibleMoves);
                cout << "The White King is in check" << endl;
                return moves;
            }
        }
        else//Color is black
        {
            if(blackKingInCheck)
            {
                cout << "The Black King is in check" << endl;
                moves = movesOutOfCheck(color, possibleMoves);//only allow moves that would move out of check, block check, or remove checkingPiece
                return moves;
            }
        }

        cout << "The king is not in check" << endl;
        //will only get here if the king isn't in check (list has had no change, so possibleMoves = the legal moves)
        cout << "possibleMoves.size(): " << possibleMoves.size() << endl;
        return possibleMoves;
    }

	static int ChangeLetterToNumber(string letter) { //Method that changes letter into a number (used for the file to be chnaged from a letter to a number)
		string str = "abcdefgh";
		return str.find_first_of(letter) + 1;
	}

    string WhiteMove(Chess king, list<string> blackPossibleMoves)//computer is white and makes a move (takes other color's moves to make sure it's not in check)
    {
        cout << "WhiteMove has started" << endl;
        string whiteMove;
        cout << "old previousWhiteMoves.size(): " << previousWhiteMoves.size() << endl;
        cout << "TotalPossibleMoves('White').size() "  << TotalPossibleMoves("White").size() << endl;
        previousWhiteMoves = TotalLegalMoves("White", TotalPossibleMoves("White"));//gets legal moves
        cout << "new previousWhiteMoves.size(): " << previousWhiteMoves.size() << endl;
        list<string> whitePossibleMoves = previousWhiteMoves;
        for(string move : whitePossibleMoves)
        {
            cout << move << " ";
        }
        cout << endl;
        bool kingIsInCheck = IsInCheck(king, blackPossibleMoves);
        cout << "kingIsInCheck:" << kingIsInCheck << endl;
        cout << "The variables have been initialized" << endl;
        if(kingIsInCheck)
        {
            whitePossibleMoves = movesOutOfCheck("White", whitePossibleMoves);
            cout << "The king is in check" << endl;
        }
        cout << endl;


        cout << "The algorithm is starting" << endl;
        //algorithm goes here
        int moveIndex = 5;//rand() % whitePossibleMoves.size();
        cout << "moveIndex is " << moveIndex << endl;
        int currentIndex = 0;
        cout << "currentIndex is " << currentIndex << endl;
        if(whitePossibleMoves.size() == 0)
        {
            cout << "CHECKMATE, Black wins" << endl;
            return "CHECKMATE, Black wins";
        }
        for(string move : whitePossibleMoves)//algorithm
        {
            if(currentIndex = moveIndex)
            {
                currentIndex++;
                whiteMove = move;
                cout << "whiteMove is " << whiteMove << endl;
                break;
            }
            else
            {
                currentIndex++;
            }
        }

        
        cout << "I (the computer) played " << whiteMove << endl;
        return whiteMove;

    }

    string BlackMove(Chess king, list<string> whitePossibleMoves)//computer is black and makes a move (takes other color's moves to make sure it's not in check)
    {
        cout << "BlackMove has started" << endl;
        string blackMove;
        cout << "old previousBlackMoves.size(): " << previousBlackMoves.size() << endl;
        cout << "TotalPossibleMoves('Black').size() "  << TotalPossibleMoves("Black").size() << endl;
        previousBlackMoves = TotalLegalMoves("Black",TotalPossibleMoves("Black"));//gets legal moves
        cout << "new previousBlackMoves.size(): " << previousBlackMoves.size() << endl;
        list<string> blackPossibleMoves = previousBlackMoves;
        for(string move : blackPossibleMoves)
        {
            cout << move << " ";
        }
        cout << endl;
        bool kingIsInCheck = IsInCheck(king, whitePossibleMoves);
        cout << "kingIsInCheck: " << kingIsInCheck << endl;
        cout << "The variables have been initialized" << endl;
        if(kingIsInCheck)
        {
            blackPossibleMoves = movesOutOfCheck("Black", blackPossibleMoves);
            previousBlackMoves = blackPossibleMoves;
        }

        cout << "The algorithm is starting" << endl;
        //algorithm goes here
        int moveIndex = rand() % blackPossibleMoves.size();
        int currentIndex = 0;
        if(whitePossibleMoves.size() == 0)
        {
            cout << "CHECKMATE, White wins" << endl;
            return "CHECKMATE, White wins";
        }
        for(string move : blackPossibleMoves)
        {
            if(currentIndex = moveIndex)
            {
                currentIndex++;
                blackMove = move;
                cout << "blackMove is " << blackMove << endl;
                break;
            }
            else
            {
                currentIndex++;
            }
        }
        cout << "blackMove is about to get played" << endl;
        Move("Black", blackMove);

        cout << "I (the computer) played " << blackMove << endl;
        return blackMove;
    }

    void NormalPlay()
    {
        bool checkmate = false;
        int whitePieceCounter = 0;
        int blackPieceCounter = 0;
        list<Chess> findingWhitePieces;
        list<Chess> findingBlackPieces;
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                Chess piece = board[row][col];
                cout << piece.GetColor() << " " << piece.GetType() << endl;
                if(piece.GetColor() == "White")
                {

                    findingWhitePieces.push_back(piece);
                    whitePieceCounter++;
                    cout << "whitePieceCounter: " << whitePieceCounter << endl;

                }
                else if(piece.GetColor() == "Black")
                {
                    findingBlackPieces.push_back(piece);
                    blackPieceCounter++;
                    cout << "blackPieceCounter: " << blackPieceCounter << endl;
                }
                //else: square is empty
            }
            whitePieces = findingWhitePieces;
            blackPieces = findingBlackPieces;
            cout << "whitePieces length: " << whitePieces.size() << endl;
            cout << "blackPieces length: " << blackPieces.size() << endl;
            cout << "\n\n\n" << endl;
        }
        //starting the game
        string color;
        cout << "What color would you like? (Black or White)" << endl;
        cin >> color;
        cout << "your color is " << color << endl;
        while(color != "Black" && color != "White")
        {
            cout << "Your chosen color wasn't 'Black' or 'White', please input one of those colors to continue ";
            cin >> color;
        }

        string computerColor;
        if(color == "White")
        {
            computerColor = "Black";
        }
        else//color has to be black (the previous check was already done to make sure)
        {
            computerColor = "White";
        }

        
        if(color == "White")
        {
            cout << "for loop for White pieces has started" << endl;
            while(checkmate != true)//whitePlay
            {
                string move;
                cout << "What move would you like to play as white?    " << endl;//should be in form (*Letter**Position**New Position)
                cin >> move;
                do{
                    if(MoveWentThrough == false)
                    {
                        cout << "Your previous move did not go through, please try again" << endl;
                        cin >> move;
                        cout << "\n";
                    }
                    cout << "Move is about to run" << endl;
                    Move("White", move);
                }while(MoveWentThrough == false);//once it's true, break the loop and let someone else play (will do the first time regardless)

                cout << "Time for the computer to move";
                //BlackMove (Computer)
                Chess king;//black's king
                for(int rank = 0; rank < 8; rank++)
                {
                    for(int file = 0; file < 8; file++)
                    {
                        Chess p = board[rank][file];
                        if(p.GetType() == "King" && p.GetColor() == computerColor)
                        {
                            king = p;
                            cout << "Black's king has been found" << endl;
                        }
                    }
                }

                BlackMove(king, previousWhiteMoves);
            }
            cout << "congratulations, you have bested me as white" << endl;
        }
        else//color == "Black"
        {
            //WhiteMove (Computer)
            cout << "Black for loop is starting" << endl;
            while(checkmate != true)//blackPlay
            {
                Chess king;//white's king
                for(int rank = 0; rank < 8; rank++)
                {
                    for(int file = 0; file < 8; file++)
                    {
                        Chess p = board[rank][file];
                        if(p.GetType() == "King" && p.GetColor() == computerColor)
                        {
                            king = p;
                            cout << "Black's king has been found" << endl;
                        }
                    }
                }
                cout << "White is about to move" << endl;
                WhiteMove(king, previousBlackMoves);
                
                if(checkmate == false)
                {
                    //Human Play
                    //list<string> possibleWhiteMoves = WhiteStartingMoves(); *Why is this here*
                    cout << "What move would you like to play as black?" << endl;//should be in form (*Letter**New Position)
                    string move; 
                    cin >> move;
                    do{
                        if(MoveWentThrough == false)
                        {
                            cout << "Your previous move did not go through, please try again";
                            cin >> move; 
                        }
                        cout << "Move is about to run" << endl;
                        Move("Black", move);
                    }while(MoveWentThrough == false);//once it's true, break the loop and let someone else play (will do the first time regardless)
                }
                
                
            }
        }

        cout << "Checkmate has been played, good game";
    }
};
