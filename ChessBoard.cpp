#include <iostream>
#include <string>
#include <list>
#include "Chess.cpp"
using namespace std;

class Board {
    public:
        Chess
        Board(string, int, int);
    private:

    


    Board::Board(string, int r, int f) {//Creates the 2D array that is the board
        Chess theBoard[8][8];
        for (int row = 8; row > 0; row++) { //printing the names for each spot
            for (int col = 0; col < 8; col++) {
                std::cout << "abcdefgh"[row] << (col + 1);
                std::cout << "\t";
            }
            std::cout << endl;
        }

    }
}
