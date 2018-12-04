#include "ChessPiece.h"

char ChessPiece :: getColor()
{
    return mcColor;
}
bool ChessPiece :: isLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8])
{
    ChessPiece* dest = boardMove[iDestRow][iDestCol];
    if ((dest == 0) || (mcColor != dest->getColor()))
        return areSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, boardMove);
    
    return false;
}
