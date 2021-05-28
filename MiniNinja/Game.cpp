#include "Game.h"
#include "FocusStates.h"

void SetGameFunctions();

#include "Sprite.h"

void InitGame() {
	InitWindow("MiniNinja");
	InitTextures();
	InitFonts();
	InitConsole();
	if (!SetFocusScene(LoadScene("Scenes/scene"))) {
		SetFocusScene(new Scene);
	}
	SetFocus(FOCUS_SCENE);
	SetGameFunctions();
	Log("Type \"help()\" for a list of functions.");

	// TEST TEST TEST:
	Sprite* sprite = new Sprite("", { 2, 2 });
	GetFocusScene()->entities.push_back(sprite);
	GetFocusScene()->camera.SetPos({ 0, 0 });
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