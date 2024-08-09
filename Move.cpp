using namespace std;

#include "Move.h"
#include "Chess.cpp"
#include <iostream>

class Move
{
    public:
	Chess* piece_;
	Position* oldPos_;
	Position* newPos_;
    std::string pieceIdentifier;
	bool deliversCheck;
	bool deliversMate;
    bool takes;
    bool VALIDMOVE_;

	/*
	* This constructor is only being used internally and therefore does not check if the move is legal or not
	* this constructor makes the Move object that will be added to the list in the MoveList struct in order to create the list of possible moves that one side has
	* This constructor will create the Move (that is known to be valid because of a previous check), which will then be added to a MoveList object, which will be passed to a later Play function and check for the player's move in that list
	*/
	Move::Move(Chess*** board, Chess* piece, std::string move)
	: piece_(piece), oldPos_(piece->GetPosition()), newPos_(), VALIDMOVE_(true)
	{
        std::string tempMove = move;
		//this stuff is pretty simple: could be changed in the future to include the check to ensure the move is valid before accepting it
        //takes out the extra chars besides move-specific information and updates the bool info
        if(piece->GetType() != globalEnums::Pawn) //not a pawn move (e.g. Nf3)
        {
            tempMove = tempMove.substr(1); //remove the piece type from the move (e.g. f3)
        }
        //else: pawn move means that there is no piece type in the move, and therefore should be skipped
        if(tempMove.find("x") != -1) //e.g. Nfxd5 -> fxd5
        {
            takes = true;
            tempMove = tempMove.substr(0, tempMove.find("x")) + tempMove.substr(tempMove.find("x") + 1); //adds the part before takes to the part after takes: shouldn't run an error because of the 0 length substr if there is no pieceIdentifier, but NOTE that could be an issue
                //e.g. fxd5 -> fd5
        }
		if(tempMove.find("#") != -1)
		{
			deliversMate = true;
            tempMove = tempMove.substr(0, tempMove.length() - 1); //removes the last letter
		}
		else
		{
			deliversMate = false;
			if(tempMove.find("+") != -1)
			{
				deliversCheck = true;
                tempMove = tempMove.substr(0, tempMove.length() - 1); //removes the last letter
			}
			else
			{
				deliversCheck = false;
			}
		}

		delete newPos_; //must be set using the move, so the default Position that is created before the constructor starts must be destroyed (can't get around that, must be created and then deleted)

        std::string newPosString;
        newPosString = tempMove.substr(tempMove.length() - 2, 2);
        if(tempMove.length() != 2) {
            pieceIdentifier = tempMove.substr(0, tempMove.length() - 2); // e.g. exd5 -> ed5: pieceIdentifier = "e", newPosString = "d5", takes = true
        }
            //NOTE: Position is created here, so all of these positions must be destroyed after they are done being used - done in Move destructor
        newPos_ = new Position(tempMove[0], tempMove[1] - '0');

            //check to make sure that the move is valid: done after the Move has been created because we want the extra info to help us with the function
        if(this->checkMove(board, piece, move) == false) 
        {
            VALIDMOVE_ = false;
            delete piece_; piece_ = NULL; 
            delete oldPos_; oldPos_ = NULL;
            delete newPos_; newPos_ = NULL;
            std::cout << "This Move " << move << " is not valid" << endl;
            std::cout << "tempMove value: " << tempMove << endl;
            std::cout << "takes, deliversCheck, and deliversMate values:: " << takes << ", " << deliversCheck << ", " << deliversMate << endl;
        }
	}

    /*
    * this function will check if the move string is legal
    * this function needs access to the board in order to check if the piece is in the position it wants to be, access to the board to make sure the piece is in the right position and 
    */
    bool Move::checkMove(Chess** board[8], Chess* piece, std::string move)
    {
            //check if the piece pointer and the pointer at the piece's position are not the same: false move (i.e. the piece thinks it's somewhere that the board thinks it is not)
        if(piece != board[piece->GetPosition()->file - 'a'][piece->GetPosition()->rank]) {return false;} //NOTE: this board check should work, getting the index with Position.file (-char-) - 'a' and Position.file
            //check if the piece's Line Of Sight has the new position in it
        if(piece->GetPrimaryLOS().PositionInVector(newPos_) == false) {return false;}

            //If we get here: the piece could move to this spot: now we need to check if the piece is able to
        //need to check if the piece is pinned
        
    }


    /*
    * Destructor must be created so that there is not a memory leak from these memory locations being kept and possibly used with the Move
    */
    Move::~Move()
    {
        delete newPos_;
        delete oldPos_;
        delete piece_;
    }
};

//2 MoveVectors will be created at the beginning of the game (one for each color), and will be cleared and remade every turn
class MoveVector
{
        //both of these will be private and returned through the getter methods
	globalEnums::chessColor color_; //color_ will be given when the MoveVector is created and cannot be changed from then
	std::vector<Move> vecMove_; //this is created with a size of 0 with the color constructor, and will just be added to using push_back

    public:

        //constructor
    MoveVector::MoveVector(globalEnums::chessColor color) : color_(color) {}
        //getter methods
    globalEnums::chessColor MoveVector::GetColor() {return color_;}
    vector<Move>& MoveVector::GetMoveVector() {return vecMove_;} 
    int MoveVector::FindMove(Move& m) {
        std::vector<Move>::iterator vecIt; //iterator goes thru based on the algorithm you use and can get the index that something is stored at
        vecIt = std::find(vecMove_.begin(), vecMove_.end(), m);
        if(vecIt != vecMove_.end()) {return (vecIt - vecMove_.begin());}
        else {return -1;} 
    }
        //push_back methods
    void MoveVector::push_back(Move& m) {vecMove_.push_back(m);}
    void MoveVector::push_back(Chess* piece)
    {
        for(Move& m : vecMove_)
        {
            this->push_back(m);
        }
    }
    //other changing methods
    void MoveVector::clear() {vecMove_.clear();}
};