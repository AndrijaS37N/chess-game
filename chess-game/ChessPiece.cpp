#include "ChessPiece.h"

char ChessPiece :: getColor()
{
    return mcColor;
}
bool ChessPiece :: isLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8])
{
    ChessPiece* qpDest = qpaaBoard[iDestRow][iDestCol];
    if ((qpDest == 0) || (mcColor != qpDest->getColor()))
    {
        return areSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);
    }
    return false;
}
