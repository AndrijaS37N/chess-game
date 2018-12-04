#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight(char cColor) : ChessPiece(cColor) {}
	~Knight() {}
private:
	virtual char getPiece()
	{
		return 'N';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
};
