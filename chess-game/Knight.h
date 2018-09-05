#pragma once
#include "ChessPieces.h"

class CKnight : public CAPiece
{
public:
	CKnight(char cColor) : CAPiece(cColor) {}
	~CKnight() {}
private:
	virtual char GetPiece()
	{
		return 'N';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
};
