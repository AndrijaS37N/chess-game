#include <iostream>
#include "ChessGame.h"

int main() 
{
    // yep, this is basically the game
	ChessGame game;
    game.start();
	delete(&game);
	return 0;
}
