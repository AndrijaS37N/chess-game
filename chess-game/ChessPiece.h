#pragma once

class ChessPiece
{
public:
    ChessPiece(char cColor) : mcColor(cColor) {}
    ~ChessPiece() {}
    virtual char getPiece() = 0;
    char getColor();
    bool isLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]);
    
private:
    virtual bool areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8]) = 0;
    char mcColor;
};
