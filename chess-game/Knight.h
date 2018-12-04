#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(char color) : ChessPiece(color) {}
	~Knight() {}
    
private:
	virtual char getPiece() { return 'N'; }
	bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]);
};
