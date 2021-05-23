#include "Textures.h"
#include "Window.h"
#include "Draw.h"
#include "Files.h"
#include "Log.h"

static SDL_Texture* defaultTexture = nullptr;
static std::unordered_map<std::string, SDL_Texture*> textures;

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
		defaultTexture = texture;
		textures[""] = texture;
		return true;
	}
	return false;
}

SDL_Texture* GetDefaultTexture() {
	return defaultTexture;
}

bool IsTexture(std::string key) {
	return textures.find(key) != textures.end();
}

bool LoadTexture(std::string filePath) {
	SDL_Surface* surf = IMG_Load(filePath.c_str());
	if (surf == nullptr) {
		Log("Image \"" + filePath + "\" unable to load: " + (std::string)IMG_GetError(), WARNING);
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	if (texture == nullptr) {
		Log("Texture unable to load: " + (std::string)SDL_GetError(), WARNING);
		return false;
	}
	SDL_FreeSurface(surf);
	textures[RemoveFileExtension(RemoveFilePath(filePath))] = texture;
    return true;
}

void LoadTexturesFromDirectory(std::string folderPath) {
	std::vector<std::string> files = GetFilesWithExtension(GetFilesInDirectory(folderPath), "png");
	for (auto file : files) {
		LoadTexture(file);
	}
}

bool UnloadTexture(std::string key) {
	if (key != "" && IsTexture(key)) {
		SDL_DestroyTexture(textures[key]);
		textures.erase(key);
		return true;
	}
	return false;
}

void UnloadAllTextures() {
	for (std::pair<std::string, SDL_Texture*> texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
	textures[""] = defaultTexture;
}

SDL_Texture* GetTexture(std::string key) {
	if (IsTexture(key)) {
		return textures[key];
	}
	return nullptr;
}

std::string GetKey(SDL_Texture* texture) {
	for (auto it = textures.begin(); it != textures.end(); it++) {
		if (it->second == texture) {
			return it->first;
		}
	}
	return "";
}