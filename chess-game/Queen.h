#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(char color) : ChessPiece(color) {}
	~Queen() {}
private:
	virtual char getPiece() 
	{
		return 'Q';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
};
