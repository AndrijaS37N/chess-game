#pragma once

#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"

class ChessBoard
{
public:
	ChessBoard();
	~ChessBoard();
	void printBoard();
	bool isInCheck(char color);
	bool canMove(char color);
	ChessPiece* boardMove[8][8];
};
