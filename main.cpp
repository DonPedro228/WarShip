#include <windows.h>
#include "Game.h"


int main() {
	SetConsoleOutputCP(65001);

	Game game;
	game.start();

	system("pause");
	return 0;
}