#include "Entities.h"
#include <sstream>
#include "FileParameters.h"
#include "Log.h"

#include "Entity.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Particle.h"

Entity* (*getNewEntity[])() = {
	[]()->Entity* { return new Entity(); },
	[]()->Entity* { return new Sprite(); },
	[]()->Entity* { return new Tilemap(); }
};

const unsigned int ENTITY_LIST_LENGTH = sizeof(getNewEntity) / sizeof(getNewEntity[0]);

unsigned int GetEntityTypeID(Entity* entity) {
	for (unsigned int i = 0; i < ENTITY_LIST_LENGTH; i++) {
		Entity* newEntity = getNewEntity[i]();
		if (typeid(*entity) == typeid(*newEntity)) {
			delete newEntity;
			return i;
		}
		delete newEntity;
	}
	Log("Failed to resolve the type ID of entity " + entity->name, WARNING);
	return 0;
}

Entity* GetEntityByTypeID(unsigned int typeID) {
	if (typeID < ENTITY_LIST_LENGTH) {
		return getNewEntity[typeID]();
	}
	Log("Failed to create Entity of type ID " + std::to_string(typeID), WARNING);
	return new Entity();
}

bool IsEntityOfTypeID(Entity* entity, unsigned int typeID) {
	Entity* newEntity = getNewEntity[typeID]();
	if (typeid(*entity) == typeid(*newEntity)) {
		delete newEntity;
		return true;
	}
	delete newEntity;
	return false;
}

Entity* DeserializeLineToEntity(std::string line) {
	// Get TypeID
	std::string strTypeID = "";
	for (unsigned int i = 0; line[i] != ' ' && i < line.size(); i++) {
		strTypeID += line[i];
	}
	uint16_t typeID = std::stoi(strTypeID);
	// Deserialize Entity of type TypeID
	std::istringstream is(line);
	Entity* entity = GetEntityByTypeID(typeID);
	if (entity) {
		entity->Deserialize(is);
	}
	return entity;
}