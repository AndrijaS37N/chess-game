#pragma once

#include <iostream>

class ChessPiece
{
public:
    ChessPiece(char color) : pieceColor(color) {}
    virtual ~ChessPiece() {}
    virtual char getPiece() = 0;
    char getColor();
    bool isLegalMove(int, int, int, int, ChessPiece* boardMove[8][8]);
    
private:
    virtual bool areSquaresLegal(int, int, int, int, ChessPiece* boardMove[8][8]) = 0;
    char pieceColor;
};
