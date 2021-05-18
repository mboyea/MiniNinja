#ifndef DRAW_H
#define DRAW_H
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Colors.h"

// Set the current draw color
void SetDrawColor(const SDL_Color& color);
// Fill the current render target
void Paint();
// Fill the current render target with a transparent draw color
void PaintAlpha();
// Draw a pixel on the current render target, return true if it fails
bool DrawPixel(const SDL_Point& pos);
// Draw a line on the current render target
void DrawLine(const SDL_Point& a, const SDL_Point& b);
// Draw a rectangle on the current render target
void DrawRect(const SDL_Rect& rectangle);
// Draw a filled rectangle on the current render target
void DrawFilledRect(const SDL_Rect& rectangle);
// Draw a circle on the current render target
void DrawCircle(const SDL_Point& pos, const int& radius);
// Draw a texture on the current render target
void DrawTexture(SDL_Texture* texture, const SDL_Rect* rect = NULL);
// Draw a texture on the current render target
void DrawTexture(SDL_Texture* texture, const SDL_RendererFlip& flip, const SDL_Point* pivot = NULL, const double& angle = 0, const SDL_Rect* rect = NULL);
// Draw text with a transparent background on the current render target
void DrawText(std::string text, SDL_Point pos, TTF_Font* font, SDL_Color textColor = Colors::WHITE);
// Draw text with an opaque background on the current render target
void DrawFilledText(std::string text, SDL_Point pos, TTF_Font* font, SDL_Color textColor = Colors::WHITE, SDL_Color backgroundColor = Colors::BLACK);

#endif // !DRAW_H