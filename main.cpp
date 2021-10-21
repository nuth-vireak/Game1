#include <iostream>
#include "Game.h"

//-------------------------------------------------------------------------------------------------------------
// Program main entry point
//-------------------------------------------------------------------------------------------------------------
int main()
{
	std::srand(static_cast<unsigned>(time(NULL))); // Init srand

	Game game; // Init game engine

	// Main game Loop
	while (game.running() && !game.getEndGame())
	{
		game.update();	// Update
		game.render(); // Render
	}

	//End of application
	return 0;
}