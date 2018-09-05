#include <iostream>
#include "ChessGame.h"

int main() 
{
	CChess qGame;
	qGame.Start();
	delete(&qGame);
	return 0;
}
