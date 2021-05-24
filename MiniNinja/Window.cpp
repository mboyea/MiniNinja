#include "Window.h"
#include <vector>
#include <cstdint>
#include <cmath>
#include "Colors.h"
#include "Log.h"
#include "Draw.h"

static SDL_Point windowDim;
static SDL_Point viewportDim;
static SDL_Texture* renderTarget;
static SDL_Rect viewportRect;

void RecalculateViewportRect() {
	SDL_QueryTexture(renderTarget, NULL, NULL, &viewportDim.x, &viewportDim.y);
	float scale = std::min((float)windowDim.x / viewportDim.x, (float)windowDim.y / viewportDim.y);
	SDL_Point scaledDim = { (int)(viewportDim.x * scale), (int)(viewportDim.y * scale) };
	viewportRect = {
		std::max(0, (windowDim.x - scaledDim.x) / 2),
		std::max(0, (windowDim.y - scaledDim.y) / 2),
		scaledDim.x,
		scaledDim.y
	};
}

void InitWindow(std::string windowName, SDL_Point dim) {
	windowDim = dim;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Log("Unable to initialize SDL: " + *SDL_GetError(), FAULT);
		exit(1);
	}

	// Create Window
	Game::window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowDim.x, windowDim.y, SDL_WINDOW_RESIZABLE);
	if (!Game::window) {
		// TODO: Log("Unable to open " + std::to_string(dimensions.x) + "x" + std::to_string(dimensions.y) + " window " + windowName + ": " + *SDL_GetError(), FAULT);
		exit(1);
	}

	// Create Renderer
	Game::renderer = SDL_CreateRenderer(Game::window, -1, SDL_RENDERER_ACCELERATED);
	if (!Game::renderer) {
		// TODO: Log("Unable to create renderer: " + *SDL_GetError(), FAULT);
		exit(1);
	}
}

void HandleWindowEvents() {
	std::vector<SDL_Event> eventsIgnored;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				windowDim = { event.window.data1, event.window.data2 };
				RecalculateViewportRect();
			}
			break;
		default:
			// ignore all other events
			eventsIgnored.push_back(event);
			break;
		}
	}
	for (SDL_Event event : eventsIgnored) {
		SDL_PushEvent(&event);
	}
}

void PresentWindow() {
	// Set Render Target to Window
	SDL_SetRenderTarget(Game::renderer, NULL);

	// Draw Viewport to Window
	DrawTexture(renderTarget, &viewportRect);

	// Present Window
	SDL_RenderPresent(Game::renderer);

	// Return Render Target to Viewport
	SDL_SetRenderTarget(Game::renderer, renderTarget);
}

void SetWindowTitle(std::string title) {
	SDL_SetWindowTitle(Game::window, title.c_str());
}

void SetWindowIcon(std::string filePath) {
	SDL_Surface* icon = IMG_Load(filePath.c_str());
	if (!icon) {
		Log("Unable to load icon image " + filePath + ": " + IMG_GetError(), FAULT);
		return;
	}
	SDL_SetWindowIcon(Game::window, icon);
	SDL_FreeSurface(icon);
}

void SetWindowSize(SDL_Point dimensions) {
	windowDim = dimensions;
	SDL_SetWindowSize(Game::window, dimensions.x, dimensions.y);
	// TODO: paint letterbox color
}

void SetRenderTarget(SDL_Texture* target) {
	renderTarget = target;
	RecalculateViewportRect();
	SDL_SetRenderTarget(Game::renderer, renderTarget);
}

SDL_Point GetViewportDim() {
	return viewportDim;
}

SDL_Texture* GetRenderTarget() {
	return renderTarget;
}