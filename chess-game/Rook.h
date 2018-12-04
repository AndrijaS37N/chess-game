#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(char color) : ChessPiece(color) {}
    ~Rook() {}
    
private:
    virtual char getPiece() { return 'R'; }
    bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]);
};
