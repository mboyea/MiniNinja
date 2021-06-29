#include "Colliders.h"

Collider* GetColliderOfType(uint16_t typeID) {
	Collider* collider = new Collider();
	if (collider->IsType(typeID)) {
		return collider;
	}
	delete collider;
	AABBCollider* aabbCollider = new AABBCollider();
	if (aabbCollider->IsType(typeID)) {
		return aabbCollider;
	}
	delete aabbCollider;
	return nullptr;
}

Collider* DeserializeLineToCollider(std::string line) {
	// Get TypeID
	std::string strTypeID = "";
	for (unsigned int i = 0; line[i] != ' ' && i < line.size(); i++) {
		strTypeID += line[i];
	}
	uint16_t typeID = std::stoi(strTypeID);
	// Deserialize Collider of type TypeID
	std::istringstream is(line);
	Collider* collider = GetColliderOfType(typeID);
	if (collider) {
		collider->Deserialize(is);
	}
	return collider;
}