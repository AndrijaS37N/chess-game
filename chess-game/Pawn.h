#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(char cColor) : ChessPiece(cColor) {}
	~Pawn() {}
private:
	virtual char getPiece()
	{
		return 'P';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
};
