#ifndef TEXTURES_H
#define TEXTURES_H
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

namespace Game {
	inline std::unordered_map<std::string, SDL_Texture*> textures;
}

void InitTextures();

bool SetDefaultTexture(SDL_Texture* texture);
SDL_Texture* GetDefaultTexture();

bool IsTexture(std::string key);
bool LoadTexture(std::string filePath);
void LoadTexturesFromDirectory(std::string folderPath);
bool UnloadTexture(std::string key);
void UnloadAllTextures();

#endif // !TEXTURES_H