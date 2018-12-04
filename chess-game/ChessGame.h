#pragma once

#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"

class ChessGame
{
public:
	ChessGame() : turnOf('W') {}
	~ChessGame() {}
	void enterNames();
	void start();
	void getNextMove(ChessPiece* boardMove[8][8]);
	void alternateTurn();
	bool isGameOver();
    void printPlayers(std::string time);
    std::string nameA;
    std::string nameB;
	int beginHours;
	int beginMinutes;
	int beginSeconds;
	int endHours;
	int endMinutes;
	int endSeconds;
	struct tm* end;
    bool exitCode;
private:
	ChessBoard gameBoard;
	char turnOf;
};
