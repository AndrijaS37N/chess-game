#pragma once
#include "ChessPieces.h"

class CKing : public CAPiece
{
public:
    CKing(char cColor) : CAPiece(cColor) {}
    ~CKing() {}
private:
    virtual char GetPiece()
    {
        return 'K';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
};
