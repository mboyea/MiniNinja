#include "Textures.h"
#include "Window.h"
#include "Draw.h"

void InitTextures() {
	// enable .png loading
	IMG_Init(IMG_INIT_PNG);

	// turn off texture blurring
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	// generate default texture
	SDL_Texture* defaultTexture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32, 32);
	SDL_SetRenderTarget(Game::renderer, defaultTexture);

	SetDrawColor(Colors::BLACK);
	DrawRect({ 0, 0, 32, 32 });
	SetDrawColor(Colors::MAGENTA);
	DrawFilledRect({ 0, 0, 16, 16 });
	DrawFilledRect({ 16, 16, 16, 16 });

	SDL_SetRenderTarget(Game::renderer, GetRenderTarget());
	SetDefaultTexture(defaultTexture);
}

bool SetDefaultTexture(SDL_Texture* texture) {
	if (texture) {
		Game::defaultTexture = texture;
		return true;
	}
	return false;
}

bool IsTexture(std::string key) {
	return Game::textures.find(key) != Game::textures.end();
}

bool LoadTexture(std::string filePath) {
	// TODO: LoadTexture
    return false;
}

void LoadTexturesFromDirectory(std::string folderPath) {
	// TODO: LoadTexturesFromDirectory
}

bool UnloadTexture(std::string key) {
	if (IsTexture(key)) {
		SDL_DestroyTexture(Game::textures[key]);
		Game::textures.erase(key);
		return true;
	}
	return false;
}

void UnloadAllTextures() {
	for (std::pair<std::string, SDL_Texture*> texture : Game::textures) {
		SDL_DestroyTexture(texture.second);
	}
	Game::textures.clear();
}