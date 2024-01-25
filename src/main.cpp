#include "Game.h"

int WinMain(int argc, char** argv) {
	InitGame();
	while (true) {
		UpdateGame();
		RenderGame();
		PresentWindow();
		LimitFramerate(Game::targetFPS);
	}
	return 0;
}
