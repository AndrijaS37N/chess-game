#include "ChessBoard.h"
#include <iostream>

CBoard::CBoard()
{
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			mqpaaBoard[iRow][iCol] = 0;
		}
	}
    
	// allocate and place black pieces
	for (int iCol = 0; iCol < 8; ++iCol)
	{
		mqpaaBoard[6][iCol] = new CPawn('B');
	}
	mqpaaBoard[7][0] = new CRook('B');
	mqpaaBoard[7][1] = new CKnight('B');
	mqpaaBoard[7][2] = new CBishop('B');
	mqpaaBoard[7][3] = new CKing('B');
	mqpaaBoard[7][4] = new CQueen('B');
	mqpaaBoard[7][5] = new CBishop('B');
	mqpaaBoard[7][6] = new CKnight('B');
	mqpaaBoard[7][7] = new CRook('B');
	
    // allocate and place white pieces
	for (int iCol = 0; iCol < 8; ++iCol)
	{
		mqpaaBoard[1][iCol] = new CPawn('W');
	}
	mqpaaBoard[0][0] = new CRook('W');
	mqpaaBoard[0][1] = new CKnight('W');
	mqpaaBoard[0][2] = new CBishop('W');
	mqpaaBoard[0][3] = new CKing('W');
	mqpaaBoard[0][4] = new CQueen('W');
	mqpaaBoard[0][5] = new CBishop('W');
	mqpaaBoard[0][6] = new CKnight('W');
	mqpaaBoard[0][7] = new CRook('W');
}

CBoard::~CBoard()
{
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			delete mqpaaBoard[iRow][iCol];
			mqpaaBoard[iRow][iCol] = 0;
		}
	}
}

void CBoard::Print()
{
	using namespace std;
	const int kiSquareWidth = 4;
	const int kiSquareHeight = 3;
	for (int iRow = 0; iRow < 8 * kiSquareHeight; ++iRow)
	{
		int iSquareRow = iRow / kiSquareHeight;
		// print side border with numbering
		if (iRow % 3 == 1)
		{
			cout << '-' << (char)('1' + 7 - iSquareRow) << '-';
		}
		else
		{
			cout << "---";
		}
		// print the chess board
		for (int iCol = 0; iCol < 8 * kiSquareWidth; ++iCol)
		{
			int iSquareCol = iCol / kiSquareWidth;
			if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && mqpaaBoard[7 - iSquareRow][iSquareCol] != 0)
			{
				if ((iCol % 4) == 1)
				{
					cout << mqpaaBoard[7 - iSquareRow][iSquareCol]->GetColor();
				}
				else
				{
					cout << mqpaaBoard[7 - iSquareRow][iSquareCol]->GetPiece();
				}
			}
			else
			{
				if ((iSquareRow + iSquareCol) % 2 == 1)
				{
					cout << '*';
				}
				else
				{
					cout << ' ';
				}
			}
		}
		cout << endl;
	}
	// print the bottom border with numbers
	for (int iRow = 0; iRow < kiSquareHeight; ++iRow)
	{
		if (iRow % 3 == 1)
		{
			cout << "---";
			for (int iCol = 0; iCol < 8 * kiSquareWidth; ++iCol)
			{
				int iSquareCol = iCol / kiSquareWidth;
				if ((iCol % 4) == 1)
				{
					cout << (iSquareCol + 1);
				}
				else
				{
					cout << '-';
				}
			}
			cout << endl;
		}
		else
		{
			for (int iCol = 1; iCol < 9 * kiSquareWidth; ++iCol)
			{
				cout << '-';
			}
			cout << endl;
		}
	}
}

bool CBoard::IsInCheck(char cColor)
{
	// find the king
	int iKingRow;
	int iKingCol;
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			if (mqpaaBoard[iRow][iCol] != 0)
			{
				if (mqpaaBoard[iRow][iCol]->GetColor() == cColor)
				{
					if (mqpaaBoard[iRow][iCol]->GetPiece() == 'K')
					{
						iKingRow = iRow;
						iKingCol = iCol;
					}
				}
			}
		}
	}
    
	// run through the opponent's pieces and see if any can take the king
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			if (mqpaaBoard[iRow][iCol] != 0)
			{
				if (mqpaaBoard[iRow][iCol]->GetColor() != cColor)
				{
					if (mqpaaBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, mqpaaBoard))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool CBoard::CanMove(char cColor)
{
	// run through all pieces
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			if (mqpaaBoard[iRow][iCol] != 0)
			{
				// if it is a piece of the current player, see if it has a legal move
				if (mqpaaBoard[iRow][iCol]->GetColor() == cColor)
				{
					for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow)
					{
						for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol)
						{
							if (mqpaaBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, mqpaaBoard))
							{
								// make move and check whether king is in check
								CAPiece* qpTemp = mqpaaBoard[iMoveRow][iMoveCol];
								mqpaaBoard[iMoveRow][iMoveCol] = mqpaaBoard[iRow][iCol];
								mqpaaBoard[iRow][iCol] = 0;
								bool bCanMove = !IsInCheck(cColor);
                                
								// undo the move
								mqpaaBoard[iRow][iCol] = mqpaaBoard[iMoveRow][iMoveCol];
								mqpaaBoard[iMoveRow][iMoveCol] = qpTemp;
                                
								if (bCanMove)
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}
