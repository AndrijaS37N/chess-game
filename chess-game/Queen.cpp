#include "Queen.h"

bool Queen::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, ChessPiece* boardMove[8][8])
{
	if (srcRow == destRow)
	{
		// make sure that all invervening squares are empty
		int colOffset = (destCol - srcCol > 0) ? 1 : -1;
		for (int checkCol = srcCol + colOffset; checkCol != destCol; checkCol = checkCol + colOffset)
		{
			if (boardMove[srcRow][checkCol] != 0)
				return false;
		}
		return true;
	}
	else if (destCol == srcCol)
	{
		// make sure that all invervening squares are empty
		int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
		for (int checkRow = srcRow + rowOffset; checkRow != destRow; checkRow = checkRow + rowOffset)
		{
			if (boardMove[checkRow][srcCol] != 0)
				return false;
		}
		return true;
	}
	else if ((destCol - srcCol == destRow - srcRow) || (destCol - srcCol == srcRow - destRow))
	{
		// make sure that all invervening squares are empty
		int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
		int colOffset = (destCol - srcCol > 0) ? 1 : -1;
		int checkRow;
		int checkCol;
		for (checkRow = srcRow + rowOffset, checkCol = srcCol + colOffset; checkRow != destRow;
             checkRow += rowOffset, checkCol += colOffset)
		{
			if (boardMove[checkRow][checkCol] != 0)
				return false;
		}
		return true;
	}
	return false;
}
