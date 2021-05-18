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
		if (IsKeyPressed(SDL_SCANCODE_LSHIFT)) {
			StopTextInput();
			SetFocus(FOCUS_EDITOR);
			return;
		}
		StopTextInput();
		SetFocus(FOCUS_SCENE);
		return;
	}
}

void UpdateDebug() {
	if (IsKeyPressed(SDL_SCANCODE_RETURN)) {
		InterpretConsoleInput();
	}
}

void RenderDebug() {
	// TODO: Remove Load Font
	TTF_Font* font = TTF_OpenFont("Fonts/m5x7.ttf", 16);
	if (!font) {
		Log("Font unable to load: " + (std::string)TTF_GetError(), WARNING);
		return;
	}

	GetCurrentScene()->Render();
	// Draw Console Background
	SetDrawColor(Colors::BLACK);
	DrawFilledRect({ 0, GetViewportDim().y - CONSOLE_HEIGHT, GetViewportDim().x, CONSOLE_HEIGHT });
	// Draw Console Input Text
	DrawFilledText(*Game::consoleInput, { 4, GetViewportDim().y - CONSOLE_HEIGHT }, font);
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
			//Game::fonts["m5x7_16"],
			font,
			log.GetColor()
		);
	}

	// TODO: Remove Unload Font
	TTF_CloseFont(font);
}