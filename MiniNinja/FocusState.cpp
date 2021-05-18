#include "FocusState.h"
#include "DebugFocus.h"
#include "Console.h"
#include "Input.h"

static const FocusState* currentFocus = nullptr;

void SetFocus(const FocusState* focus) {
	if (focus == FOCUS_DEBUG) {
		StartTextInput(Game::consoleInput, '`');
	}
	currentFocus = focus;
}

const FocusState* GetFocus() {
	return currentFocus;
}

void UpdateFocus() {
	if (currentFocus) {
		currentFocus->Update();
	}
}

void RenderFocus() {
	if (currentFocus) {
		currentFocus->Render();
	}
}

void HandleFocusSwitching() {
	if (currentFocus) {
		currentFocus->HandleSwitch();
	}
}