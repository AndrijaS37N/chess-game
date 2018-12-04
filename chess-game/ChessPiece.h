#pragma once

#include <iostream>

class ChessPiece
{
public:
    ChessPiece(char color) : mcColor(color) {}
    virtual ~ChessPiece() {std::cout << "A piece was eaten!" << std::endl;}
    virtual char getPiece() = 0;
    char getColor();
    bool isLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]);
    
private:
    virtual bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8]) = 0;
    char mcColor;
};
