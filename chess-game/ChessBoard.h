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
	void print();
	bool isInCheck(char cColor);
	bool canMove(char cColor);
	ChessPiece* boardMove[8][8];
};
