#ifndef FONTS_H
#define FONTS_H
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>

namespace Game {
	inline std::unordered_map<std::string, TTF_Font*> fonts;
}

bool InitFonts(std::string filePathDefault = "Resources/Fonts/m5x7.ttf", int sizeDefault = 16);

TTF_Font* GetDefaultFont();
bool LoadFont(std::string filePath, int size);
bool UnloadFont(std::string key);
bool UnloadFont(std::string key, int size);
void UnloadAllFonts();
bool IsFont(std::string key);
bool IsFont(std::string key, int size);

#endif // !FONTS_H