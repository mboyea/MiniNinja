#include "Game.h"
#include "FocusStates.h"

void SetGameFunctions() {
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1 && IsInteger(args[0])) {
			Game::targetFPS = std::stoi(args[0]);
			return true;
		}
		return false;
		}, "setfps"
	);
	SetFunction([](std::vector<std::string> args) {
		return std::to_string(Game::targetFPS);
		}, "getfps"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1) {
			SetWindowTitle(args[0]);
			return true;
		}
		return false;
		}, "setwindowtitle"
	);
}

void InitGame() {
	InitWindow("MiniNinja");
	InitTextures();
	InitFonts();
	InitConsole();
	if (!SetCurrentScene(LoadScene("Scenes/scene"))) {
		SetCurrentScene(new Scene);
	}
	SetFocus(FOCUS_SCENE);
	Log("Type \"help()\" for a list of functions.");
	SetGameFunctions();
}

void UpdateGame() {
	HandleWindowEvents();
	HandleInputEvents();

	HandleFocusSwitching();
	UpdateFocus();
}

void RenderGame() {
	RenderFocus();
}