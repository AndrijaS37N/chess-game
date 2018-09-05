#pragma once
#include <iostream>
#include "ChessBoard.h"
#include "ChessPieces.h"
using namespace std;

class CChess
{
public:
	CChess() : mcPlayerTurn('W') {}
	~CChess() {}
	void EnterNames();
	void Start();
	void GetNextMove(CAPiece* qpaaBoard[8][8]);
	void AlternateTurn();
	bool IsGameOver();
    void PrintPlayers(string time);
	string nameA;
	string nameB;
	int beginHours;
	int beginMinutes;
	int beginSeconds;
	int endHours;
	int endMinutes;
	int endSeconds;
	struct tm* end;
    bool exitCode;
private:
	CBoard mqGameBoard;
	char mcPlayerTurn;
};
