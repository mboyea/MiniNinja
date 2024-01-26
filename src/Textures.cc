#include <SDL.h>
#include "Textures.h"
#include "Window.h"
#include "Draw.h"
#include "Files.h"
#include "Log.h"
#include <unordered_map>
#include <unordered_set>

static SDL_Texture* defaultTexture = nullptr;
static std::unordered_map<std::string, SDL_Texture*> textures;

bool SetDefaultTexture(SDL_Texture* texture) {
	if (texture) {
		defaultTexture = texture;
		textures[""] = texture;
		return true;
	}
	return false;
}

void InitTextures(std::string filePathDefault) {
	// enable .png loading
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	// turn off texture blurring
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	// set the default texture
	if (filePathDefault == "") {
	GENERATE_DEFAULT_TEXTURE:
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
	else {
		if (!DoesPathExist(filePathDefault)) {
			Log("File \"" + filePathDefault + "\" does not exist.", WARNING);
			Log("Unable to load custom default texture.", WARNING);
			goto GENERATE_DEFAULT_TEXTURE;
		}
		SDL_Surface* surf = IMG_Load(filePathDefault.c_str());
		if (surf == nullptr) {
			Log("Image \"" + filePathDefault + "\" unable to load: " + (std::string)IMG_GetError(), WARNING);
			Log("Unable to load custom default texture.", WARNING);
			SDL_FreeSurface(surf);
			goto GENERATE_DEFAULT_TEXTURE;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		if (texture == nullptr) {
			Log("Texture unable to load: " + (std::string)SDL_GetError(), WARNING);
			Log("Unable to load custom default texture.", WARNING);
			SDL_FreeSurface(surf);
			SDL_DestroyTexture(texture);
			goto GENERATE_DEFAULT_TEXTURE;
		}
		SDL_FreeSurface(surf);
		SetDefaultTexture(texture);
	}
}

SDL_Texture* GetDefaultTexture() {
	return defaultTexture;
}

bool LoadTexture(std::string filePath) {
	if (!DoesPathExist(filePath)) {
		Log("File \"" + filePath + "\" does not exist.", WARNING);
		Log("Texture load failed.", FAULT);
		return false;
	}
	SDL_Surface* surf = IMG_Load(filePath.c_str());
	if (surf == nullptr) {
		Log("Image \"" + filePath + "\" unable to load: " + (std::string)IMG_GetError(), WARNING);
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	if (texture == nullptr) {
		Log("Texture unable to load: " + (std::string)SDL_GetError(), WARNING);
		SDL_FreeSurface(surf);
		return false;
	}
	SDL_FreeSurface(surf);
	textures[GetFileName(filePath)] = texture;
    return true;
}

void LoadTexturesFromDirectory(std::string folderPath) {
	std::set<std::string> files = GetFilesWithExtension(GetFilesInDirectory(folderPath), "png");
	for (std::string file : files) {
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
		if (texture.first != "") {
			SDL_DestroyTexture(texture.second);
		}
	}
	textures.clear();
	textures[""] = defaultTexture;
}

bool IsTexture(std::string key) {
	return textures.find(key) != textures.end();
}

SDL_Texture* GetTexture(std::string key) {
	if (IsTexture(key)) {
		return textures[key];
	}
	return defaultTexture;
}

std::string GetKey(SDL_Texture* texture) {
	for (auto it = textures.begin(); it != textures.end(); it++) {
		if (it->second == texture) {
			return it->first;
		}
	}
	return "";
}