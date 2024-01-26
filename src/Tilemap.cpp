#include "Tilemap.h"
#include "Draw.h"
#include "Scene.h"
#include "FileParameters.h"
#include "Log.h"

SDL_Point Tilemap::GetTilePos(int x, int y) {
	return { pos.x + (x * dim.x), pos.y + (y * dim.y) };
}

uint8_t* Tilemap::GetTileData(unsigned int x, unsigned int y) {
	return &tileData[x + (y * tileCountX)];
}

SDL_Rect Tilemap::GetTileTextureRect(const uint8_t& tile) {
	SDL_Point textureSize = GetTextureDimensions();
	SDL_Rect rect = {((tile - 1) * dim.x) % textureSize.x, (((tile - 1) * dim.x) / textureSize.x) * dim.y, dim.x, dim.y };
	return rect;
}

void Tilemap::Render() {
	int i = 0;
	for (uint8_t tile : tileData) {
		if (tile > 0) {
			SDL_Point tilePos = GetTilePos(i % tileCountX, i / tileCountX);
			SDL_Rect rect = SceneToViewport({ tilePos.x, tilePos.y, dim.x, dim.y }, GetActiveScene());
			SDL_Rect textureRect = GetTileTextureRect(tile);
			DrawTexture(texture, &rect, &textureRect);
		}
		i++;
	}
}

std::ostream& Tilemap::Serialize(std::ostream& os) {
	Sprite::Serialize(os);
	os << ' ' << tileCountX << ' ' << tileData.size() / tileCountX << ' ' << LIST_START << ' ';
	int i = 1;
	for (uint8_t tile : tileData) {
		os << std::to_string(tile) << ' ';
		if (i % tileData.size() != 0) {
			os << LIST_ITEM_END << ' ';
		}
		i++;
	}
	return os << LIST_END;;
}

std::istream& Tilemap::Deserialize(std::istream& is) {
	Sprite::Deserialize(is);
	unsigned int tileCountY;
	is >> tileCountX >> tileCountY;
	char listStart;
	is >> listStart;
	if (listStart != LIST_START) {
		Log("Tried to deserialize data into a vector that did not begin with " + LIST_START, WARNING);
		return is;
	}
	tileData.clear();
	tileData.reserve(tileCount.x * tileCount.y);
	std::string listItem;
	while (is >> listItem) {
		if (is.eof() || listItem[0] == LIST_END) {
			break;
		}
		if (listItem[0] == LIST_ITEM_END) {
			continue;
		}
		tileData.push_back(std::stoi(listItem));
	}
	return is;
}
