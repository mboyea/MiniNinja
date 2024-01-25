#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include "Entity.h"
#include "Textures.h"

class Sprite : public Entity {
private:
protected:
public:
	SDL_Texture* texture;
	SDL_Point dim;

	Sprite(std::string name = "", SDL_Point pos = { 0, 0 }, int8_t renderLayer = 0, bool saveAsModule = false, std::string textureKey = "", SDL_Point dim = { 0, 0 })
		: Entity(name, pos, renderLayer, saveAsModule), texture(GetTexture(textureKey)) {
		if (dim.x == 0 || dim.y == 0) {
			this->dim = GetTextureDimensions();
		} else this->dim = dim;
	};

	SDL_Point GetTextureDimensions();

	virtual void Render() override;
	virtual std::set<Resource>& GetRequiredResources(std::set<Resource>& resourcesOut) override;
	virtual std::ostream& Serialize(std::ostream& os) override;
	virtual std::istream& Deserialize(std::istream& is) override;
};

#endif // !SPRITE_H