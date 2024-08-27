#include "Move.h"

class Pieces : public Chess
{
    protected:

    std::list<globalEnums::direction> _pinnedDirections; //starts off empty, only will get changed by other pieces whenever they pin this piece to the king
    MoveVector _moves;

    public:
        //constructors
    Pieces();
    Pieces(const Pieces&);
    Pieces(globalEnums::chessColor color, globalEnums::chessType type, char f, int r);
	Pieces(std::string pos);
        //print function
    virtual void PrintOut(ostream& os); //used in the print function
        //pure virtual functions
    virtual void FindLOS() = 0; //create the LOS's
    virtual MoveVector& FindMoves() = 0; //find the moves that this piece can make and return it (empty list if no moves)
    virtual MoveVector& FindChecks() = 0; //find the checks that this piece can make and return it (empty list if no checks)
        /* NOTE: these functions must be smart, searching for pins, if the king is checked, etc and take that into consideration for finding what moves/checks the piece can make (e.g. blocking move that opens a discovered check on the other king should be found) */
};

class Pawn : public Chess
{
	protected:
		bool hasNotMoved_;
        bool enPassantAble = false;
	
	public:
	//constructors
		Pawn();
		Pawn(const Pawn& p);
		Pawn(globalEnums::chessColor color, globalEnums::chessType type, char f, int r);
		Pawn(std::string pos);
	//destructor not needed
        virtual void FindLOS(); //create the LOS's
        virtual MoveVector& FindMoves(); //find the moves that this piece can make and return it (empty list if no moves)
        virtual MoveVector& FindChecks(); //find the checks that this piece can make and return it (empty list if no checks)
};