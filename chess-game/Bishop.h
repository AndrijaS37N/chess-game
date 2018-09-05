#pragma once
#include "ChessPieces.h"

class CBishop : public CAPiece
{
public:
    CBishop(char cColor) : CAPiece(cColor) {}
    ~CBishop() {}
private:
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
    virtual char GetPiece()
    {
        return 'B';
    }
};
