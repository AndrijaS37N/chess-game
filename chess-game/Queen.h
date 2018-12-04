#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(char color) : ChessPiece(color) {}
	~Queen() {}
    
private:
	virtual char getPiece() { return 'Q'; }
	bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]);
};
