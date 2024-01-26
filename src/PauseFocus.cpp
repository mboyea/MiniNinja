#include "FocusStates.h"
#include "Input.h"
#include "Draw.h"
#include "Scene.h"
#include "Log.h"

static Scene* currentScene = GetDefaultScene();

void HandleSwitchPause() {
	if (IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
		SetFocus(FOCUS_SCENE);
		return;
	}
}

void OnSwitchPause() {
	if (!currentScene) {
		currentScene = GetDefaultScene();
	}
}

void UpdatePause() {
	currentScene->Update();
}

void RenderPause() {
	SetDrawColor(GetFocusScene()->backgroundColor);
	Paint();
	GetFocusScene()->Render();
	SetDrawColor(currentScene->backgroundColor);
	PaintAlpha();
	currentScene->Render();
}

bool SetPauseScene(Scene* scene) {
	if (!scene) {
		Log("Failed to change active scene.", WARNING);
		return false;
	}
	currentScene = scene;
	currentScene->camera = GetFocusScene()->camera;
	return true;
}

Scene* GetPauseScene() {
	return currentScene;
}