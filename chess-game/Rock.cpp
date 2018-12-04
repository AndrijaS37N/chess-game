#include "Rook.h"

bool Rook::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, ChessPiece* boardMove[8][8])
{
	if (srcRow == destRow)
	{
		// make sure that all invervening squares are empty I
		int colOffset = (destCol - srcCol > 0) ? 1 : -1;
		for (int checkCol = srcCol + colOffset;
             checkCol != destCol;
             checkCol += colOffset)
		{
			if (boardMove[srcRow][checkCol] != 0)
				return false;
		}
		return true;
	}
	else if (destCol == srcCol)
	{
		// make sure that all invervening squares are empty II
		int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
		for (int checkRow = srcRow + rowOffset; checkRow != destRow; checkRow += rowOffset)
		{
			if (boardMove[checkRow][srcCol] != 0)
				return false;
		}
		return true;
	}
	return false;
}
