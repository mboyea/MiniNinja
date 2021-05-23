#ifndef TEXTURES_H
#define TEXTURES_H
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>

void InitTextures();

bool SetDefaultTexture(SDL_Texture* texture);
SDL_Texture* GetDefaultTexture();

bool IsTexture(std::string key);
bool LoadTexture(std::string filePath);
void LoadTexturesFromDirectory(std::string folderPath);
bool UnloadTexture(std::string key);
void UnloadAllTextures();
SDL_Texture* GetTexture(std::string key);
std::string GetKey(SDL_Texture* texture);


#endif // !TEXTURES_H