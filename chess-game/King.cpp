#include "King.h"

bool King::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, ChessPiece* boardMove[8][8])
{
	int calcRow = destRow - srcRow;
	int calcDest = destCol - srcCol;
	if (((calcRow >= -1) && (calcRow <= 1)) &&
		((calcDest >= -1) && (calcDest <= 1)))
	{
		return true;
	}
	return false;
}
