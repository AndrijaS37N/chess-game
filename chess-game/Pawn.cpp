#include "Pawn.h"

bool Pawn::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, ChessPiece* boardMove[8][8])
{
	ChessPiece* dest = boardMove[destRow][destCol];
	if (dest == 0)
	{
		// destination square is unoccupied
		if (srcCol == destCol)
		{
            if (getColor() == 'W')
			{
				if (destRow == srcRow + 1)
					return true;
			}
			else
			{
				if (destRow == srcRow - 1)
					return true;
			}
		}
	}
	else
	{
		// dest holds piece of opposite color
		if ((srcCol == destCol + 1) || (srcCol == destCol - 1))
		{
            if (getColor() == 'W')
			{
				if (destRow == srcRow + 1)
					return true;
			}
			else
			{
				if (destRow == srcRow - 1)
					return true;
			}
		}
	}
	return false;
}
