#ifndef GAME_H
#define GAME_H
#pragma once

#include "Window.h"
#include "Textures.h"
#include "Fonts.h"
#include "Console.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "Log.h"

namespace Game {
	inline int targetFPS = 60;
}

void InitGame();
void UpdateGame();
void RenderGame();

#endif // !GAME_H.