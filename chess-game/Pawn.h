#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(char color) : ChessPiece(color) {}
	~Pawn() {}
private:
	virtual char getPiece()
	{
		return 'P';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
};
