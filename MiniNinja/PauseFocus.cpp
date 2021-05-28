#include "FocusStates.h"
#include "Input.h"
#include "Draw.h"
#include "Scene.h"

void HandleSwitchPause() {
	if (IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
		SetFocus(FOCUS_SCENE);
		return;
	}
}

void UpdatePause() {
	GetFocusScene()->Update();
}

void RenderPause() {
	GetFocusScene()->Render();
	SetDrawColor({ 255, 0, 0 });
	DrawLine({ 10, 10 }, { 50, 50 });
	DrawLine({ 50, 10 }, { 10, 50 });
	SetDrawColor({ 0, 0, 255 });
	DrawRect({ 10, 10, 41, 41 });
}