#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include <set>
#include <iostream>
#include "Collider.h"
#include "Resource.h"

class Entity {
private:
protected:
public:
	uint16_t typeID = __COUNTER__;
	/* TRANSFORM */
	SDL_Point pos;
	SDL_Point lastPos;
	std::vector<Entity*> children;
	/* RENDERING */
	int8_t renderLayer;
	/* COLLISION */
	std::vector<Collider*> colliders;
	/* SAVING */
	bool saveAsModule;
	std::string name;

	Entity(std::string name, SDL_Point pos = { 0, 0 }, int8_t renderLayer = 0, bool saveAsModule = false)
		: name(name), pos(pos), lastPos(pos), renderLayer(renderLayer), saveAsModule(saveAsModule) {}

	virtual void Update();
	virtual void Render();
	virtual void OnCollision(Entity* collisionEntity);

	bool IsType(uint16_t typeID);
	template <typename T> bool IsType();
	template <typename T> T* GetAsType();

	virtual std::set<Resource>& GetRequiredResources(std::set<Resource>& resourcesOut);
	// Generate serialized text data for this entity into the stream
	virtual std::ostream& Serialize(std::ostream& os);
	// Populate this entity by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is);
	bool operator<(const Entity& rhs);
};

#endif // !ENTITY_H