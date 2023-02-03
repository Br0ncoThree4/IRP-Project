#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
#include <array>
#ifndef NULL
#define NULL 0
#endif
using namespace std;

class ChessBoard : public ChessMoves
{
    public:
        static void Board(list<Chess>);
    private:

    


    static void ChessBoard::Board(list<Chess> pieceList) {//Creates the 2D array that is the board, given the list of starting chess pieces
        Chess board[8][8];
        
        for (Chess piece : pieceList) {//putting each chess piece on their starting squares
            int rank = piece.GetRank();
            int file = piece.GetFile();
            board[rank][file] = piece;
        }
        for (int row = 8; row > 0; row++) { //printing the board and its square number
            for (int col = 0; col < 8; col++) {
                if (board[row][col].GetFile() != NULL) {
                    std::cout << board[row][col].GetColor() << " " << board[row][col].GetType();
                }
                else {
                    std::cout << "\t \t \t \t"; //trying to space the board out so that even if theres nothing, the board still kind of keeps is square shape
                }

                    std::cout << "(" << "abcdefgh"[row] << (col + 1) << ")" << "\t";
            }
            std::cout << endl;
        }
    }
    //we also need a printing method for the chess board
};;
