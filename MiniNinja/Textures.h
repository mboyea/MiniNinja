#ifndef TEXTURES_H
#define TEXTURES_H
#pragma once

#include <SDL_image.h>
#include <string>

void InitTextures(std::string filePathDefault = "");

SDL_Texture* GetDefaultTexture();
bool LoadTexture(std::string filePath);
void LoadTexturesFromDirectory(std::string folderPath);
bool UnloadTexture(std::string key);
void UnloadAllTextures();
bool IsTexture(std::string key);
SDL_Texture* GetTexture(std::string key);
std::string GetKey(SDL_Texture* texture);

#endif // !TEXTURES_H