#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include "Entity.h"
#include "Textures.h"
#include "Resource.h"

class Sprite : public Entity {
private:
protected:
public:
	SDL_Texture* texture;

	Sprite(SDL_Point pos = { 0, 0 }, int8_t renderLayer = 0, bool saveAsModule = false, std::string textureKey = "")
		: Entity(pos, renderLayer, saveAsModule), texture(GetTexture(textureKey)) {
		typeID = __COUNTER__;
	};

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(Entity* collisionEntity) override;

	virtual std::vector<Resource*> GetRequiredResources() override;
	// Generate serialized text data for this entity into the stream
	virtual std::ostream& Serialize(std::ostream& os) override;
	// Populate this entity by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is) override;
};

#endif // !SPRITE_H