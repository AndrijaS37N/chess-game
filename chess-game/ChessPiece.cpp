#include "ChessPiece.h"

char ChessPiece::getColor()
{
    return pieceColor;
}
bool ChessPiece::isLegalMove(int srcRow, int srcCol, int destRow, int destCol, ChessPiece* boardMove[8][8])
{
    ChessPiece* dest = boardMove[destRow][destCol];
    if ((dest == 0) || (pieceColor != dest->getColor()))
        return areSquaresLegal(srcRow, srcCol, destRow, destCol, boardMove);
    
    return false;
}
