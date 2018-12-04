#include "Pawn.h"

bool Pawn::areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* qpaaBoard[8][8])
{
	ChessPiece* qpDest = qpaaBoard[iDestRow][iDestCol];
	if (qpDest == 0)
	{
		// destination square is unoccupied
		if (iSrcCol == iDestCol)
		{
            if (getColor() == 'W')
			{
				if (iDestRow == iSrcRow + 1)
				{
					return true;
				}
			}
			else
			{
				if (iDestRow == iSrcRow - 1)
				{
					return true;
				}
			}
		}
	}
	else
	{
		// dest holds piece of opposite color
		if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1))
		{
            if (getColor() == 'W')
			{
				if (iDestRow == iSrcRow + 1)
				{
					return true;
				}
			}
			else
			{
				if (iDestRow == iSrcRow - 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}
