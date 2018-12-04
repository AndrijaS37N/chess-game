#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(char color) : ChessPiece(color) {}
    ~Bishop() {}
private:
    virtual char getPiece()
    {
        return 'B';
    }
    bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
};
