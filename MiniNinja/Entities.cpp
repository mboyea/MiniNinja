#include "Entities.h"
#include "FileParameters.h"
#include <sstream>

#include "Entity.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Particle.h"

Entity* GetEntityOfType(uint16_t typeID) {
	Entity* entity = new Entity("");
	if (entity->IsType(typeID)) {
		return entity;
	}
	delete entity;
	Sprite* sprite = new Sprite("");
	if (sprite->IsType(typeID)) {
		return sprite;
	}
	delete sprite;
	Tilemap* tilemap = new Tilemap("");
	if (tilemap->IsType(typeID)) {
		return tilemap;
	}
	delete tilemap;
	return nullptr;
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
	Entity* entity = GetEntityOfType(typeID);
	if (entity) {
		entity->Deserialize(is);
	}
	return entity;
}