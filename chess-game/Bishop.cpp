#include "Bishop.h"

bool Bishop::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, ChessPiece* boardMove[8][8])
{
	if ((destCol - srcCol == destRow - srcRow) || (destCol - srcCol == srcRow - destRow))
	{
		// make sure that all invervening squares are empty
		int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
		int colOffset = (destCol - srcCol > 0) ? 1 : -1;
		int checkRow;
		int checkCol;
		for (checkRow = srcRow + rowOffset, checkCol = srcCol + colOffset;
             checkRow != destRow;
             checkRow += rowOffset, checkCol += colOffset)
		{
			if (boardMove[checkRow][checkCol] != 0)
				return false;
		}
		return true;
	}
	return false;
}
