#include "Rook.h"

bool Rook::areSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, ChessPiece* boardMove[8][8])
{
	if (iSrcRow == iDestRow)
	{
		// make sure that all invervening squares are empty
		int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
		for (int iCheckCol = iSrcCol + iColOffset; iCheckCol != iDestCol; iCheckCol = iCheckCol + iColOffset)
		{
			if (boardMove[iSrcRow][iCheckCol] != 0)
			{
				return false;
			}
		}
		return true;
	}
	else if (iDestCol == iSrcCol)
	{
		// make sure that all invervening squares are empty
		int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
		for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow != iDestRow; iCheckRow = iCheckRow + iRowOffset)
		{
			if (boardMove[iCheckRow][iSrcCol] != 0)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
