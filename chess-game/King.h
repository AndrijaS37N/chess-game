#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(char color) : ChessPiece(color) {}
    ~King() {}
private:
    virtual char getPiece()
    {
        return 'K';
    }
    bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
};
