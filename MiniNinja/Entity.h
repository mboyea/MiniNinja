#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include <set>
#include <iostream>
#include "Colliders.h"
#include "Resource.h"
#include "Audio.h"

class Entity {
private:
	std::vector<std::string> loadChildren = {};
	std::vector<Entity*> entitiesCollided = {};
protected:
public:
	uint16_t typeID = __COUNTER__;
	/* TRANSFORM */
	SDL_Point pos;
	SDL_Point stepPos;
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
		: name(name), pos(pos), stepPos(pos), lastPos(pos), renderLayer(renderLayer), saveAsModule(saveAsModule) {}

	virtual void Update();
	virtual void Render();
	virtual void OnCollision(Entity* collisionEntity);
	void FlagEntitiesDidCollisionDetection(Entity* collisionEntity);
	bool DidCollisionDetection(Entity* collisionEntity);
	void ResetDidCollisionFlags();

	bool IsType(uint16_t typeID);
	template <typename T> bool IsType();
	template <typename T> T* GetAsType();

	// Push a list of required resources into resourcesOut
	virtual std::set<Resource>& GetRequiredResources(std::set<Resource>& resourcesOut);
	// Generate serialized text data for this entity into the stream
	virtual std::ostream& Serialize(std::ostream& os);
	// Populate this entity by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is);
	virtual void LateDeserialize();
};

#endif // !ENTITY_H