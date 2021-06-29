#include "Game.h"
#include "FocusStates.h"
#include "Files.h"

void SetGameFunctions();

#include "Sprite.h"

void InitGame() {
	InitWindow("MiniNinja");
	InitTextures();
	InitFonts();
	InitConsole();
	if (!SetFocusScene(LoadScene("Scenes/asdf"))) {
		Log("Default scene failed to load.", FAULT);
	}
	SaveScene(GetFocusScene(), "Scenes/save.zscne");
	// TODO: bugfix: this LoadScene call destroys the ability to serialize textures; if LoadScene is called again, the issue is fixed; but when this pause screen is loaded, it messes up the SDL_Renderer & overwrites Textures' std::set.
	// I assume that this is an issue because the Renderer is the same between the two scenes and overwrites the Textures std::set with new textures.
	// The Focus Scene is still able to hold onto the textures it has - they're not deleted - but the named references to them are overwritten.
	if (!SetPauseScene(LoadScene("Scenes/pausescreen"))) {
		Log("Pause scene failed to load.", FAULT);
	}
	SetFocus(FOCUS_SCENE);
	SetGameFunctions();
	Log("Type \"help()\" for a list of functions.");
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
		return std::to_string(GetWindowSize().x) + ", " + std::to_string(GetWindowSize().y);
		}, "getwindowsize"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 2 && IsInteger(args[0]) && IsInteger(args[1])) {
			SetWindowSize({ std::stoi(args[0]), std::stoi(args[1]) });
			return true;
		}
		return false;
		}, "setwindowsize"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1) {
			SetWindowTitle(args[0]);
			return true;
		}
		return false;
		}, "setwindowtitle"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1) {
			return SaveScene(GetFocusScene(), ForceFileDirectory(args[0], "Scenes"));
		}
		return false;
		}, "savescene"
	);
	SetFunction([](std::vector<std::string> args) {
		if (args.size() == 1) {
			Scene* oldScene = GetFocusScene();
			if (SetFocusScene(LoadScene(ForceFileDirectory(args[0], "Scenes")))) {
				delete oldScene;
				return true;
			}
		}
		return false;
		}, "loadscene"
	);
}