#pragma once
#include "ChessPieces.h"

class CRook : public CAPiece
{
public:
	CRook(char cColor) : CAPiece(cColor) {}
	~CRook() {}
private:
	virtual char GetPiece()
	{
		return 'R';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
};
