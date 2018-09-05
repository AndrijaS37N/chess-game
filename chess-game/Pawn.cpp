#include "Pawn.h"

bool CPawn::AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, CAPiece* qpaaBoard[8][8])
{
	CAPiece* qpDest = qpaaBoard[iDestRow][iDestCol];
	if (qpDest == 0)
	{
		// destination square is unoccupied
		if (iSrcCol == iDestCol)
		{
			if (GetColor() == 'W')
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
			if (GetColor() == 'W')
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
