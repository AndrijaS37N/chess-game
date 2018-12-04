#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(char cColor) : ChessPiece(cColor) {}
    ~Bishop() {}
private:
    virtual char getPiece()
    {
        return 'B';
    }
    bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
};
