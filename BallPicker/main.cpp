#include "Game.h"


int main()
{
	// Inicjalizacja generatora liczb losowych
	srand(static_cast<unsigned>(time(0)));

	// Inicjalizacja gry
	Game game;
	
	
	// Pêtla gry
	while (game.is_open())
	{
		game.update();
		game.render();
	}

	// Koniec programu
	return 0;
}