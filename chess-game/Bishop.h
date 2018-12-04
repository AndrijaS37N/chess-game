#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(char color) : ChessPiece(color) {}
    ~Bishop() {}
private:
    
    virtual char getPiece() { return 'B'; }
    bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]);
};
