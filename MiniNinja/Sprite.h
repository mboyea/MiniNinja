#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include "Entity.h"
#include "Textures.h"
#include "Resource.h"

class Sprite : public Entity {
private:
protected:
	SDL_Point dim;
public:
	SDL_Texture* texture;

	Sprite(std::string name, SDL_Point pos = { 0, 0 }, int8_t renderLayer = 0, bool saveAsModule = false, std::string textureKey = "", SDL_Point dim = { 0, 0 })
		: Entity(name, pos, renderLayer, saveAsModule), texture(GetTexture(textureKey)) {
		typeID = __COUNTER__;
		if (dim.x == 0 || dim.y == 0) {
			SetDimensionsByTexture();
		} else SetDimensions(dim);
	};

	SDL_Point GetTextureDimensions();
	void SetDimensionsByTexture();
	void SetDimensions(SDL_Point dimensions);

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(Entity* collisionEntity) override;

	virtual std::set<Resource>& GetRequiredResources(std::set<Resource>& resourcesOut) override;
	// Generate serialized text data for this entity into the stream
	virtual std::ostream& Serialize(std::ostream& os) override;
	// Populate this entity by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is) override;
};

#endif // !SPRITE_H