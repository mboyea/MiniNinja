#include "FocusStates.h"
#include "Input.h"

void HandleSwitchEditor() {
	if (IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
		SetFocus(FOCUS_SCENE);
		return;
	}
	else if (IsKeyPressed(SDL_SCANCODE_GRAVE)) {
		if (IsKeyDown(SDL_SCANCODE_LSHIFT)) {
			SetFocus(FOCUS_SCENE);
			return;
		}
		SetFocus(FOCUS_DEBUG);
		return;
	}
}

void UpdateEditor() {}

void RenderEditor() {}