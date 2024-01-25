#ifndef FONTS_H
#define FONTS_H
#pragma once

#include <SDL_ttf.h>
#include <string>

bool InitFonts(std::string filePathDefault = "Resources/Fonts/m5x7.ttf", int sizeDefault = 16);

TTF_Font* GetDefaultFont();
bool LoadFont(std::string filePath, int size);
void LoadFontsFromDirectory(std::string folderPath, int size);
bool UnloadFont(std::string key);
bool UnloadFont(std::string key, int size);
void UnloadAllFonts();
bool IsFont(std::string key);
bool IsFont(std::string key, int size);
TTF_Font* GetFont(std::string key);
TTF_Font* GetFont(std::string key, int size);
std::string GetKey(TTF_Font* font);

#endif // !FONTS_H