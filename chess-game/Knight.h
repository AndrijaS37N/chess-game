#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(char color) : ChessPiece(color) {}
	~Knight() {}
private:
	virtual char getPiece()
	{
		return 'N';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
};
