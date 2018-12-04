#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook(char color) : ChessPiece(color) {}
	~Rook() {}
private:
	virtual char getPiece()
	{
		return 'R';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
};
