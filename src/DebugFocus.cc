#include "FocusStates.h"
#include "Input.h"
#include "Draw.h"
#include "Window.h"
#include "Console.h"
#include "Log.h"
#include "Fonts.h"

const int CONSOLE_HEIGHT = 15;

void HandleSwitchDebug() {
	if (IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
		StopTextInput();
		SetFocus(FOCUS_SCENE);
		return;
	}
	else if (IsKeyPressed(SDL_SCANCODE_GRAVE)) {
		if (IsKeyDown(SDL_SCANCODE_LSHIFT)) {
			StopTextInput();
			SetFocus(FOCUS_EDITOR);
			return;
		}
		StopTextInput();
		SetFocus(FOCUS_SCENE);
		return;
	}
}

void OnSwitchDebug() {
	StartTextInput(Game::consoleInput, '`');
}

void UpdateDebug() {
	if (IsKeyPressed(SDL_SCANCODE_RETURN)) {
		InterpretConsoleCommand();
	}
}

void RenderDebug() {
	if (HasTextInputUpdated() || HasLogUpdated()) {
		GetFocusScene()->Render();
		// Draw Console Background
		SetDrawColor(Colors::BLACK);
		DrawFilledRect({ 0, GetViewportDim().y - CONSOLE_HEIGHT, GetViewportDim().x, CONSOLE_HEIGHT });
		// Draw Console Input Text
		DrawFilledText(*Game::consoleInput, { 4, GetViewportDim().y - CONSOLE_HEIGHT }, GetDefaultFont());
		// Draw Console Border
		SetDrawColor(Colors::WHITE);
		DrawRect({ 0, GetViewportDim().y - CONSOLE_HEIGHT, GetViewportDim().x, CONSOLE_HEIGHT });
		// Draw Recent Logs
		unsigned int logsToRender = (GetViewportDim().y - CONSOLE_HEIGHT) / 13;
		for (unsigned int i = 1; i <= Game::logs.size() && i <= logsToRender; i++) {
			GameLog& log = Game::logs[Game::logs.size() - i];

			DrawFilledText(
				log.AsText(),
				{ 0, GetViewportDim().y - CONSOLE_HEIGHT - (int)(13 * i) },
				GetDefaultFont(),
				log.GetColor()
			);
		}
		SetTextInputUpdated(false);
		SetLogUpdated(false);
	}
}