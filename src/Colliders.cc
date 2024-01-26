#include "Colliders.h"
#include <sstream>
#include "FileParameters.h"
#include "Log.h"

#include "Collider.h"
#include "AABBCollider.h"
// #include "OBBCollider.h"
// #include "CircleCollider.h"

Collider* (*getNewCollider[])() = {
	[]()->Collider* { return new Collider(); },
	[]()->Collider* { return new AABBCollider(); }
};

const unsigned int COLLIDER_LIST_LENGTH = sizeof(getNewCollider) / sizeof(getNewCollider[0]);

unsigned int GetColliderTypeID(Collider* collider) {
	for (unsigned int i = 0; i < COLLIDER_LIST_LENGTH; i++) {
		Collider* newCollider = getNewCollider[i]();
		if (typeid(*collider) == typeid(*newCollider)) {
			delete newCollider;
			return i;
		}
		delete newCollider;
	}
	Log("Failed to resolve the type ID of collider", WARNING);
	return 0;
}

Collider* GetColliderByTypeID(unsigned int typeID) {
	if (typeID < COLLIDER_LIST_LENGTH) {
		return getNewCollider[typeID]();
	}
	Log("Failed to create Collider of type ID " + std::to_string(typeID), WARNING);
	return new Collider();
}

bool IsColliderOfTypeID(Collider* collider, unsigned int typeID) {
	Collider* newCollider = getNewCollider[typeID]();
	if (typeid(*collider) == typeid(*newCollider)) {
		delete newCollider;
		return true;
	}
	delete newCollider;
	return false;
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
	Collider* collider = GetColliderByTypeID(typeID);
	if (collider) {
		collider->Deserialize(is);
	}
	return collider;
}