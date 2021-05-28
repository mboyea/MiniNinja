#include "Fonts.h"
#include "Files.h"
#include "Log.h"

TTF_Font* defaultFont = nullptr;

bool SetDefaultFont(TTF_Font* font) {
	if (!font) {
		Log("Default font unable to load: " + (std::string)TTF_GetError(), WARNING);
		return false;
	}
	defaultFont = font;
	return true;
}

bool InitFonts(std::string filePathDefault, int sizeDefault) {
	TTF_Init();

	return SetDefaultFont(TTF_OpenFont(filePathDefault.c_str(), sizeDefault));
}

TTF_Font* GetDefaultFont() {
	return defaultFont;
}

bool LoadFont(std::string filePath, int size) {
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);
	if (!font) {
		Log("Font \"" + filePath + "\" at size " + std::to_string(size) + " unable to load: " + (std::string)TTF_GetError(), WARNING);
		return false;
	}
	Game::fonts[GetFileName(filePath) + '_' + std::to_string(size)] = font;
	return true;
}

bool UnloadFont(std::string key) {
	if (!IsFont(key)) {
		return false;
	}
	TTF_CloseFont(Game::fonts[key]);
	Game::fonts.erase(key);
	return true;
}

bool UnloadFont(std::string key, int size) {
	return UnloadFont(key + '_' + std::to_string(size));
}

void UnloadAllFonts() {
	for (std::pair<std::string, TTF_Font*> font : Game::fonts) {
		TTF_CloseFont(font.second);
	}
	Game::fonts.clear();
}

bool IsFont(std::string key) {
	return Game::fonts.find(key) != Game::fonts.end();
}

bool IsFont(std::string key, int size) {
	return IsFont(key + '_' + std::to_string(size));
}