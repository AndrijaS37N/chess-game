#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook(char cColor) : ChessPiece(cColor) {}
	~Rook() {}
private:
	virtual char getPiece()
	{
		return 'R';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
};
