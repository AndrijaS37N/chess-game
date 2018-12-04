#include <iostream>
#include "ChessGame.h"

int main() 
{
    // yep, this is basically the game
    ChessGame game;
    game.start();
    // this is not needed -> delete(&game);
	return 0;
}

