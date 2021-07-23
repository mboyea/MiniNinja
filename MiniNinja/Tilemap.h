#ifndef TILEMAP_H
#define TIELMAP_H
#pragma once

#include "Sprite.h"
#include "Textures.h"

class Tilemap : public Sprite {
private:
protected:
public:

	Tilemap(std::string name, SDL_Point pos = { 0, 0 }, int8_t renderLayer = 0, bool saveAsModule = false, std::string textureKey = "", SDL_Point dim = { 0, 0 }, SDL_Point tileDim = { 0, 0 })
		: Sprite(name, pos, renderLayer, saveAsModule, textureKey, dim) {
		typeID = __COUNTER__;
		if (tileDim.x == 0 || tileDim.y == 0) {
			this->tileDim = dim;
		}
		else this->tileDim = tileDim;
	}

	virtual void Render() override;
	virtual std::ostream& Serialize(std::ostream& os) override;
	virtual std::istream& Deserialize(std::istream& is) override;
};

#endif // !TILEMAP_H