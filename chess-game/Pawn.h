#pragma once
#include "ChessPieces.h"

class CPawn : public CAPiece
{
public:
	CPawn(char cColor) : CAPiece(cColor) {}
	~CPawn() {}
private:
	virtual char GetPiece() 
	{
		return 'P';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
};
