#pragma once
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"

class CBoard
{
public:
	CBoard();
	~CBoard();
	void Print();
	bool IsInCheck(char cColor);
	bool CanMove(char cColor);
	CAPiece* mqpaaBoard[8][8];
};
