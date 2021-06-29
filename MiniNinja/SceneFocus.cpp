#include "FocusStates.h"
#include "Input.h"
#include "Draw.h"
#include "Scene.h"
#include "Window.h"
#include "Log.h"

static Scene* currentScene = GetDefaultScene();

void HandleSwitchScene() {
	if (IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
		SetFocus(FOCUS_PAUSE);
		return;
	}
	else if (IsKeyPressed(SDL_SCANCODE_GRAVE)) {
		if (IsKeyDown(SDL_SCANCODE_LSHIFT)) {
			SetFocus(FOCUS_EDITOR);
			return;
		}
		SetFocus(FOCUS_DEBUG);
		return;
	}
}

void OnSwitchScene() {
	if (!currentScene) {
		currentScene = GetDefaultScene();
	}
}

void UpdateScene() {
	currentScene->Update();
}

void RenderScene() {
	SetDrawColor(currentScene->backgroundColor);
	Paint();
	currentScene->Render();
}

bool SetFocusScene(Scene* scene) {
	if (!scene) {
		Log("Failed to change active scene.", WARNING);
		return false;
	}
	currentScene = scene;
	SetRenderTarget(currentScene->camera);
	return true;
}

Scene* GetFocusScene() {
	return currentScene;
}