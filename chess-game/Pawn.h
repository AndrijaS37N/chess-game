#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(char color) : ChessPiece(color) {}
	~Pawn() {}
    
private:
	virtual char getPiece() { return 'P'; }
	bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]);
};
