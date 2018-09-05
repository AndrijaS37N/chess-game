#include "ChessPieces.h"

char CAPiece :: GetColor()
{
    return mcColor;
}
bool CAPiece :: IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8])
{
    CAPiece* qpDest = qpaaBoard[iDestRow][iDestCol];
    if ((qpDest == 0) || (mcColor != qpDest->GetColor()))
    {
        return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);
    }
    return false;
}
