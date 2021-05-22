#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace Game {
	inline SDL_Window* window = nullptr;
	inline SDL_Renderer* renderer = nullptr;
}

void InitWindow(std::string windowName = "Game", SDL_Point windowDimensions = { 400, 240 });
void HandleWindowEvents();

void PresentWindow();

void SetWindowTitle(std::string title);
void SetWindowIcon(std::string filePath);
void SetWindowSize(SDL_Point dimensions);
void SetRenderTarget(SDL_Texture* target);
SDL_Point GetViewportDim();
SDL_Texture* GetRenderTarget();

#endif // !WINDOW_H