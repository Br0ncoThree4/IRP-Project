#include "basic.h"
#include <iostream>

using namespace std;
/*
	Class that holds the position
*/
class Position
{
	public:

	int rank;
	char file;

    Position::Position() : file('z'), rank(-1) {}
	Position::Position(char f, int r) : file(f), rank(r) {}
	Position::operator bool() {return 'a' <= file && 'h' >= file && 0 <= rank && 7 >= rank;} // NOTE: should be used as if(!pos) {bad stuff}
    Chess* Position::PosToPiece(Chess*** board) {return board[rank][file - '0'];}
};

class PositionVector
{
    globalEnums::chessColor color_;
	std::vector<Position*> vecPos_;

    public:

    
        //constructors
    PositionVector::PositionVector() : color_(globalEnums::NULL_COLOR) {}
    PositionVector::PositionVector(globalEnums::chessColor color) : color_(color) {}
        //getter methods
    globalEnums::chessColor PositionVector::GetColor() {return color_;}
    vector<Position*>& PositionVector::GetPositionVector() {return vecPos_;}
        /*
        * This function will either return true if the Position* is in vecPos_ or false if the Position* is not (could)
        */
    Position* PositionVector::getPosition(int index)
    {
        if(index == -1) {return NULL;}
        if(index > vecPos_.size()) {std::cout << "The index inputted is " << index << ", and the size of vecPos_ is " << vecPos_.size() << endl; return NULL;}
        return vecPos_[index];
    }

        /*
        * This function will return the vector for that Position*'s index in the vector, or -1 if the Position* is not in the vector
        */
    int PositionInVector(Position*& p)
    {
        std::vector<Position*>::iterator posIt; //creates an iterator: will be used to find the index of the position and therefore if it is in the list
        posIt = std::find(vecPos_.begin(), vecPos_.end(), p);
        if(posIt == vecPos_.end()) {return -1;} //Position* p is not in the vector
        //if it gets here, the Position* is in the vector
        return (posIt - vecPos_.begin()); //Position* p is in the vector
    }
        //push_back methods
    void push_back(Position* p) 
    {
        if(*(p)) //uses Position.bool() to make sure that the piece is on the board
        {vecPos_.push_back(p);} 
    }
    /*
    * Might have to be scrapped bc of the functionality: this would basically just use the previously created push_back in a slightly fancier way5
    */
    // void push_back(Chess* piece)
    // {
    //     for(Position*& p : piece->) //For Position that the piece can move to: add to posVec
    //     {
    //         this->push_back(p);
    //     }
    // }
    void clear() {vecPos_.clear();}
};

//globalEnums class does not have to be defined in this file because nothing is being added to it; that class just holds the Enums

//class globalFunctions
//{
        //taken out on 7/19 because of another use elsewhere: hard to define and use here when this is what the Chess class is built on, but this function relies on something created in a later class
    /*
    * breakDownMove takes the move in the form of a string, the color making the move, and 2 Position object aliases and type object alias
    * This function will make these aliases point to real objects, with the old position used to find the Chess piece and the type being a dummy check (can be deleted later)
    */

   //static void breakDownMove(std::string move, Position& pos, globalEnums::chessType& type, globalEnums::chessColor color)
    // void breakDownMove(std::string move, globalEnums::chessColor color, std::list<Move> listOfMoves, Position& oldPos, Position& newPos, globalEnums::chessType& type)
    // {
    //         //find the type and assign it
    //     char t = move[0];
    //     if(t > 'R') //If the char is a rank (lowercase) letter, then it would be greater than 'R', and therefore the type is a pawn  update char t
    //     {
    //         t = ' ';
    //     }
    //     else
    //     {
    //         move = move.substr(1); //gets rid of the first letter, unless the first letter is not a piece type
    //     }
    //     type = this->charToType[t]; //charToType takes the char and assigns the type of the piece to the alias, which should be blank before being given to the function

    //         //find the position and assign it
    //     if(move.length() == 2) // e.g. e4
    //     {
    //         newPos = Position(move[0], move[1] - '0');
    //     }
    //     else if (/* condition */)
    //     {
    //         /* code */
    //     }
        

    // }

    /*
    * charToType takes the char representing the type and returns the chessType for that piece
    */
//};
