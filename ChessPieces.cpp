#include "ChessPieces.h"
#include "Move.cpp"
#include <iostream>

class Pieces : public Chess
{
    protected:
    MoveVector _moves;
    std::list<globalEnums::direction> _pinnedDirections; //starts off empty, only will get changed by other pieces whenever they pin this piece to the king
        //_pinnedDirections will start empty and stay that way until a piece pins the piece to the king
    
    public:
    //constructors
    Pieces::Pieces() : Chess(), _moves(globalEnums::NULL_COLOR) {}
    Pieces::Pieces(const Pieces& p) : Chess(p), _moves(p._color) {}
    Pieces::Pieces(globalEnums::chessColor color, globalEnums::chessType type, char f, int r) : Chess(color, type, f, r), _moves(color) {}
	Pieces::Pieces(std::string pos) : Chess(pos), _moves(this->GetColor()) {}
    
    //rest of the class are pure virtual functions: can't be defined here
};

class Pawn : public Pieces
{
	protected:
		bool hasNotMoved_; //important for move list
        bool enPassantAble = false;
	
	public:
	//constructors
		Pawn::Pawn() : Pieces()
		{
			hasNotMoved_ = true;
		}
		Pawn::Pawn(const Pawn& p) : Pieces(p), hasNotMoved_(p.hasNotMoved_) {}
		Pawn::Pawn(globalEnums::chessColor color, globalEnums::chessType type, char f, int r) : Pieces(color, type, f, r), hasNotMoved_(true) {};
		Pawn::Pawn(std::string pos) : Pieces(pos), hasNotMoved_(true) {}
	        //destructor not needed

    //method to find the primaryLOS: what the piece sees (where the King cannot be) - this also highly overlaps with where a piece can move, but especially for Pawns, the two do not overlap
        void Pawn::FindLOS(const Chess** board[8])
        {
            _primaryLOS.clear();
            _primaryLOS.push_back(board[this->GetFile() - 'a' + 1][this->GetRank() + 1]->GetConstPosition());
            _primaryLOS.push_back(board[this->GetFile() - 'a' - 1][this->GetRank() + 1]->GetConstPosition());
        }

/*
* * * * * NOTE: these next 2 methods need to be smart, taking into account checks, discovered attacks, etc before adding moves to the MoveVector
*/
    //method to find the vector of moves that are possible by each piece (empty vector if no moves)
        MoveVector& Pawn::FindMoves(MoveVector& otherColorMoves) //the color is found using either _moves or the Pawn itself
        {
            //member variable: MoveVector _moves;
            if(_pinnedDirections.size() == 0)
            {
                
            }
            _moves.push_back(); //NEED TO FINISH (requires check for an empty square: should be a function)
            return _moves;
        }
    //method to find the checks that this piece can make and return it (empty vector if no checks)
        virtual MoveVector& FindChecks()
};