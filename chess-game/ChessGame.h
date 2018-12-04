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
    bool isGameOver();
    
protected:
	void getNextMove(ChessPiece* boardMove[8][8]);
	void alternateTurn();
    void printPlayers(std::string time);
    std::string nameA;
    std::string nameB;
    std::string getCurrentTime();
    struct tm* endTime;
    bool exitCode;
    
private:
	ChessBoard gameBoard;
	char turnOf;
};
