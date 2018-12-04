#include "ChessBoard.h"
#include <iostream>
#include <stdio.h>

ChessBoard::ChessBoard()
{
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
			boardMove[row][col] = 0;
	}
    
	// allocate and place black pieces
	for (int col = 0; col < 8; ++col)
	{
		boardMove[6][col] = new Pawn('B');
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
	for (int col = 0; col < 8; ++col)
	{
		boardMove[1][col] = new Pawn('W');
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
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			delete boardMove[row][col];
			boardMove[row][col] = 0;
		}
	}
}

void ChessBoard::printBoard()
{
    // and let's try this here
	using namespace std;
    
	const int squareHeight = 3;
    const int squareWidth = 4;
    
	for (int row = 0; row < 8 * squareHeight; ++row)
	{
		int squareRow = row / squareHeight;
		// print side border with numbering
		if (row % 3 == 1)
		{
			cout << '-' << (char)('1' + 7 - squareRow) << '-';
		}
		else
		{
			cout << "---";
		}
		// print the chess board
		for (int col = 0; col < 8 * squareWidth; ++col)
		{
			int squareCol = col / squareWidth;
			if (((row % 3) == 1) && ((col % 4) == 1 || (col % 4) == 2) && boardMove[7 - squareRow][squareCol] != 0)
			{
				if ((col % 4) == 1)
				{
                    cout << boardMove[7 - squareRow][squareCol]->getColor();
				}
				else
				{
                    cout << boardMove[7 - squareRow][squareCol]->getPiece();
				}
			}
			else
			{
				if ((squareRow + squareCol) % 2 == 1)
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
	for (int row = 0; row < squareHeight; ++row)
	{
		if (row % 3 == 1)
		{
			cout << "---";
			for (int col = 0; col < 8 * squareWidth; ++col)
			{
				int squareCol = col / squareWidth;
				if ((col % 4) == 1)
				{
					cout << (squareCol + 1);
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
			for (int col = 1; col < 9 * squareWidth; ++col)
			{
				cout << '-';
			}
			cout << endl;
		}
	}
}

bool ChessBoard::isInCheck(char color)
{
	// find the king
    int kingRow = 0;
    int kingCol = 0;
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (boardMove[row][col] != 0)
			{
                if (boardMove[row][col]->getColor() == color)
				{
                    if (boardMove[row][col]->getPiece() == 'K')
					{
						kingRow = row;
						kingCol = col;
					}
				}
			}
		}
	}
    
	// run through the opponent's pieces and see if any can take the king
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (boardMove[row][col] != 0)
			{
				if (boardMove[row][col]->getColor() != color)
				{
					if (boardMove[row][col]->isLegalMove(row, col, kingRow, kingCol, boardMove))
						return true;
				}
			}
		}
	}

	return false;
}

bool ChessBoard::canMove(char color)
{
	// run through all pieces
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (boardMove[row][col] != 0)
			{
				// if it is a piece of the current player, see if it has a legal move
                if (boardMove[row][col]->getColor() == color)
				{
					for (int moveRow = 0; moveRow < 8; ++moveRow)
					{
						for (int moveCol = 0; moveCol < 8; ++moveCol)
						{
                            if (boardMove[row][col]->isLegalMove(row, col, moveRow, moveCol, boardMove))
							{
								// make move and check whether king is in check
								ChessPiece* temp = boardMove[moveRow][moveCol];
								boardMove[moveRow][moveCol] = boardMove[row][col];
								boardMove[row][col] = 0;
                                bool boolCanMove = !isInCheck(color);
                                
								// undo the move
								boardMove[row][col] = boardMove[moveRow][moveCol];
								boardMove[moveRow][moveCol] = temp;
                                
								if (boolCanMove)
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
