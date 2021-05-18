#include "Draw.h"
#include "Window.h"
#include "Log.h"

void SetDrawColor(const SDL_Color& color) {
	if (SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a) < 0) {
		Log("Failed to set drawing color: " + (std::string)SDL_GetError(), FAULT);
	}
}

void Paint() {
	if (SDL_RenderClear(Game::renderer) < 0) {
		Log("Failed to paint window: " + (std::string)SDL_GetError(), FAULT);
	}
}

void PaintAlpha() {
	// TODO: paint viewport with transparency
}

bool DrawPixel(const SDL_Point& pos) {
	return SDL_RenderDrawPoint(Game::renderer, pos.x, pos.y) < 0;
}

void DrawLine(const SDL_Point& a, const SDL_Point& b) {
	if (SDL_RenderDrawLine(Game::renderer, a.x, a.y, b.x, b.y) < 0) {
		Log("Failed to draw line: " + (std::string)SDL_GetError(), FAULT);
	}
}

void DrawRect(const SDL_Rect& rect) {
	if (SDL_RenderDrawRect(Game::renderer, &rect) < 0) {
		Log("Failed to draw rectangle: " + (std::string)SDL_GetError(), FAULT);
	}
}

void DrawFilledRect(const SDL_Rect& rect) {
	if (SDL_RenderFillRect(Game::renderer, &rect) < 0) {
		Log("Failed to draw filled rectangle: " + (std::string)SDL_GetError(), FAULT);
	}
}

void DrawCircle(const SDL_Point& pos, const int& radius) {
	const int diameter = radius * 2;
	int x = (radius - 1), y = 0, tx = 1, ty = 1, error = (tx - diameter);

	while (x >= y) {
		//  Each of the following renders an octant of the circle
		if (DrawPixel({ pos.x + x, pos.y - y }) ||
			DrawPixel({ pos.x + x, pos.y + y }) ||
			DrawPixel({ pos.x - x, pos.y - y }) ||
			DrawPixel({ pos.x - x, pos.y + y }) ||
			DrawPixel({ pos.x + y, pos.y - x }) ||
			DrawPixel({ pos.x + y, pos.y + x }) ||
			DrawPixel({ pos.x - y, pos.y - x }) ||
			DrawPixel({ pos.x - y, pos.y + x })) {
			Log("Failed to draw a circle: " + (std::string)SDL_GetError(), FAULT);
			return;
		}

		if (error <= 0) {
			y++;
			error += ty;
			ty += 2;
		}
		if (error > 0) {
			x--;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void DrawTexture(SDL_Texture* texture, const SDL_Rect* rect) {
	if (SDL_RenderCopy(Game::renderer, texture, NULL, rect) < 0) {
		Log("Failed to draw texture: " + (std::string)SDL_GetError(), FAULT);
	}
}

void DrawTexture(SDL_Texture* texture, const SDL_RendererFlip& flip, const SDL_Point* pivot, const double& angle, const SDL_Rect* rect) {
	if (SDL_RenderCopyEx(Game::renderer, texture, NULL, rect, angle, pivot, flip) < 0) {
		Log("Failed to draw texture: " + (std::string)SDL_GetError(), FAULT);
	}
}

void DrawText(std::string text, SDL_Point pos, TTF_Font* font, SDL_Color textColor) {
	if (text == "") return;
	// Render Text to Texture
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	// Calculate Text Location
	SDL_Rect textRect = { pos.x, pos.y };
	TTF_SizeText(font, text.c_str(), &textRect.w, &textRect.h);
	// Render Text to Renderer
	if (SDL_RenderCopy(Game::renderer, textTexture, NULL, &textRect) < 0) {
		Log("Failed to draw unfilled text \"" + text + "\": " + (std::string)TTF_GetError(), FAULT);
	}
	// Delete Text Texture
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void DrawFilledText(std::string text, SDL_Point pos, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor) {
	if (text == "") return;
	// Render Text to Texture
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, text.c_str(), textColor, backgroundColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
	// Calculate Text Location
	SDL_Rect textRect = { pos.x, pos.y };
	TTF_SizeText(font, text.c_str(), &textRect.w, &textRect.h);
	// Render Text to Renderer
	if (SDL_RenderCopy(Game::renderer, textTexture, NULL, &textRect) < 0) {
		Log("Failed to draw filled text \"" + text + "\": " + (std::string)TTF_GetError(), FAULT);
	}
	// Delete Text Texture
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}