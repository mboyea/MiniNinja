#ifndef TILEMAP_H
#define TIELMAP_H
#pragma once

#include "Sprite.h"
#include "Textures.h"

class Tilemap : public Sprite {
private:
protected:
	SDL_Rect GetTileTextureRect(const uint8_t& tile);
	SDL_Point tileCount;
	unsigned int tileCountX;
	std::vector<uint8_t> tileData;
public:
	Tilemap(std::string name = "", SDL_Point pos = { 0, 0 }, int8_t renderLayer = 0, bool saveAsModule = false, std::string textureKey = "", SDL_Point dim = { 0, 0 }, SDL_Point tileCount = { 2, 2 })
		: Sprite(name, pos, renderLayer, saveAsModule, textureKey, dim), tileCountX(tileCount.x) {
		tileData.reserve(tileCount.x * tileCount.y);
		tileData.resize(tileCount.x * tileCount.y, 0);
	}
	SDL_Point GetTilePos(int x, int y);
	uint8_t* GetTileData(unsigned int x, unsigned int y);
	virtual void Render() override;
	virtual std::ostream& Serialize(std::ostream& os) override;
	virtual std::istream& Deserialize(std::istream& is) override;
};

#endif // !TILEMAP_H