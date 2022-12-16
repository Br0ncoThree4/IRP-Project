#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
using namespace std;

class ChessBoard {
    public:
        void Board(list<Chess>);
    private:

    


    void ChessBoard::Board(list<Chess> pieceList) {//Creates the 2D array that is the board, given the list of starting chess pieces
        Chess board[8][8];
        for()
        
        for (Chess piece : pieceList) {//putting each chess piece on their starting squares
            int rank = piece.GetRank();
            int file = piece.GetFile();
            theBoard[rank][file] = piece;
        }
        for (int row = 8; row > 0; row++) { //printing the board and its square number
            for (int col = 0; col < 8; col++) {
                if (theBoard[row][col] != 0) {
                    std::cout << theBoard[row][col].GetColor() << " " << theBoard[row][col].GetType();
                }
                else {
                    std::cout << "abcdefgh"[row] << (col + 1);
                    std::cout << "\t";
                }
            }
            std::cout << endl;
        }
    }
}
