#include "FocusState.h"

static const FocusState* currentFocus = nullptr;

void SetFocus(const FocusState* focus) {
	if (focus) {
		currentFocus = focus;
		currentFocus->OnSwitch();
	}
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