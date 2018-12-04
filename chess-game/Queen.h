#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen(char cColor) : ChessPiece(cColor) {}
	~Queen() {}
private:
	virtual char getPiece() 
	{
		return 'Q';
	}
	bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
};
