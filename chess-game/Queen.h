#pragma once
#include "ChessPieces.h"

class CQueen : public CAPiece
{
public:
	CQueen(char cColor) : CAPiece(cColor) {}
	~CQueen() {}
private:
	virtual char GetPiece() 
	{
		return 'Q';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
};
