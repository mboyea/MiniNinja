#include "Game.h"
#include "FocusStates.h"

void InitGame() {
	InitWindow("MiniNinja");
	if (!SetCurrentScene(LoadScene(""))) {
		SetCurrentScene(new Scene);
	}
	SetFocus(FOCUS_SCENE);
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