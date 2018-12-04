#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(char color) : ChessPiece(color) {}
    ~King() {}
    
private:
    virtual char getPiece() { return 'K'; }
    bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]);
};
