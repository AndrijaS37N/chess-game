#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(char cColor) : ChessPiece(cColor) {}
    ~King() {}
private:
    virtual char getPiece()
    {
        return 'K';
    }
    bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
};
