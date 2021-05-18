#include "Game.h"

int main(int argc, char** argv) {
	InitGame();
	while (true) {
		UpdateGame();
		RenderGame();
		PresentWindow();
		LimitFramerate(60);
	}
	return 0;
}