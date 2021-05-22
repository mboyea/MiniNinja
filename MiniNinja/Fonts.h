#ifndef FONTS_H
#define FONTS_H
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>

namespace Game {
	inline std::unordered_map<std::string, TTF_Font*> fonts;
}

bool LoadFont(std::string filePath, int size);

#endif // !FONTS_H