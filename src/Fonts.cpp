#include <SDL.h>
#include "Fonts.h"
#include "Files.h"
#include "Log.h"
#include <unordered_map>
#include <unordered_set>

TTF_Font* defaultFont = nullptr;
inline std::unordered_map<std::string, TTF_Font*> fonts;

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
	if (!DoesPathExist(filePath)) {
		Log("File \"" + filePath + "\" does not exist.", WARNING);
		Log("Font load failed.", FAULT);
		return false;
	}
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);
	if (!font) {
		Log("Font \"" + filePath + "\" at size " + std::to_string(size) + " unable to load: " + (std::string)TTF_GetError(), WARNING);
		return false;
	}
	fonts[GetFileName(filePath) + '_' + std::to_string(size)] = font;
	return true;
}

void LoadFontsFromDirectory(std::string folderPath, int size) {
	std::set<std::string> files = GetFilesWithExtension(GetFilesInDirectory(folderPath), "ttf");
	for (std::string file : files) {
		LoadFont(file, size);
	}
}

bool UnloadFont(std::string key) {
	if (!IsFont(key)) {
		return false;
	}
	TTF_CloseFont(fonts[key]);
	fonts.erase(key);
	return true;
}

bool UnloadFont(std::string key, int size) {
	return UnloadFont(key + '_' + std::to_string(size));
}

void UnloadAllFonts() {
	for (std::pair<std::string, TTF_Font*> font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
}

bool IsFont(std::string key) {
	return fonts.find(key) != fonts.end();
}

bool IsFont(std::string key, int size) {
	return IsFont(key + '_' + std::to_string(size));
}

TTF_Font* GetFont(std::string key) {
	if (IsFont(key)) {
		return fonts[key];
	}
	return defaultFont;
}

TTF_Font* GetFont(std::string key, int size) {
	return GetFont(key + '_' + std::to_string(size));
}

std::string GetKey(TTF_Font* font) {
	for (auto it = fonts.begin(); it != fonts.end(); it++) {
		if (it->second == font) {
			return it->first;
		}
	}
	return "";
}
