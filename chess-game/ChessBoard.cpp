#include "ChessBoard.h"
#include <iostream>

ChessBoard::ChessBoard()
{
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			boardMove[iRow][iCol] = 0;
		}
	}
    
	// allocate and place black pieces
	for (int iCol = 0; iCol < 8; ++iCol)
	{
		boardMove[6][iCol] = new Pawn('B');
	}
	boardMove[7][0] = new Rook('B');
	boardMove[7][1] = new Knight('B');
	boardMove[7][2] = new Bishop('B');
	boardMove[7][3] = new Queen('B');
	boardMove[7][4] = new King('B');
	boardMove[7][5] = new Bishop('B');
	boardMove[7][6] = new Knight('B');
	boardMove[7][7] = new Rook('B');
	
    // allocate and place white pieces
	for (int iCol = 0; iCol < 8; ++iCol)
	{
		boardMove[1][iCol] = new Pawn('W');
	}
	boardMove[0][0] = new Rook('W');
	boardMove[0][1] = new Knight('W');
	boardMove[0][2] = new Bishop('W');
	boardMove[0][3] = new Queen('W');
	boardMove[0][4] = new King('W');
	boardMove[0][5] = new Bishop('W');
	boardMove[0][6] = new Knight('W');
	boardMove[0][7] = new Rook('W');
}

ChessBoard::~ChessBoard()
{
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			delete boardMove[iRow][iCol];
			boardMove[iRow][iCol] = 0;
		}
	}
}

void ChessBoard::print()
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
			if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && boardMove[7 - iSquareRow][iSquareCol] != 0)
			{
				if ((iCol % 4) == 1)
				{
                    cout << boardMove[7 - iSquareRow][iSquareCol]->getColor();
				}
				else
				{
                    cout << boardMove[7 - iSquareRow][iSquareCol]->getPiece();
				}
			}
			else
			{
				if ((iSquareRow + iSquareCol) % 2 == 1)
				{
					cout << ' ';
				}
				else
				{
					cout << '*';
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

bool ChessBoard::isInCheck(char cColor)
{
	// find the king
    int iKingRow = 0;
    int iKingCol = 0;
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			if (boardMove[iRow][iCol] != 0)
			{
                if (boardMove[iRow][iCol]->getColor() == cColor)
				{
                    if (boardMove[iRow][iCol]->getPiece() == 'K')
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
			if (boardMove[iRow][iCol] != 0)
			{
				if (boardMove[iRow][iCol]->getColor() != cColor)
				{
					if (boardMove[iRow][iCol]->isLegalMove(iRow, iCol, iKingRow, iKingCol, boardMove))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool ChessBoard::canMove(char cColor)
{
	// run through all pieces
	for (int iRow = 0; iRow < 8; ++iRow)
	{
		for (int iCol = 0; iCol < 8; ++iCol)
		{
			if (boardMove[iRow][iCol] != 0)
			{
				// if it is a piece of the current player, see if it has a legal move
                if (boardMove[iRow][iCol]->getColor() == cColor)
				{
					for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow)
					{
						for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol)
						{
                            if (boardMove[iRow][iCol]->isLegalMove(iRow, iCol, iMoveRow, iMoveCol, boardMove))
							{
								// make move and check whether king is in check
								ChessPiece* qpTemp = boardMove[iMoveRow][iMoveCol];
								boardMove[iMoveRow][iMoveCol] = boardMove[iRow][iCol];
								boardMove[iRow][iCol] = 0;
                                bool bCanMove = !isInCheck(cColor);
                                
								// undo the move
								boardMove[iRow][iCol] = boardMove[iMoveRow][iMoveCol];
								boardMove[iMoveRow][iMoveCol] = qpTemp;
                                
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
