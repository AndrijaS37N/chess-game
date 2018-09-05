#pragma once
class CAPiece
{
public:
    CAPiece(char cColor) : mcColor(cColor) {}
    ~CAPiece() {}
    virtual char GetPiece() = 0;
    char GetColor();
    bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]);
    
private:
    virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8]) = 0;
    char mcColor;
};
