#include "Entity.h"
#include "FileParameters.h"
#include "Scene.h"
#include "Log.h"

void Entity::Update() {}
void Entity::Render() {}
void Entity::OnCollision(Entity* collisionEntity) {}

void Entity::FlagEntitiesDidCollisionDetection(Entity* collisionEntity) {
	entitiesCollided.push_back(collisionEntity);
}

bool Entity::DidCollisionDetection(Entity* collisionEntity) {
	for (Entity* entity : entitiesCollided) {
		if (collisionEntity == entity) return true;
	}
	return false;
}

void Entity::ResetDidCollisionFlags() {
	entitiesCollided.clear();
}

bool Entity::IsType(uint16_t typeID) {
	return this->typeID == typeID;
}
template<typename T> bool Entity::IsType() {
	return dynamic_cast<T*>(this) != nullptr;
}
template <typename T> T* Entity::GetAsType() {
	return dynamic_cast<T*>(this);
}

std::set<Resource>& Entity::GetRequiredResources(std::set<Resource>& resourcesOut) {
	return resourcesOut;
}

std::ostream& Entity::Serialize(std::ostream& os) {
	os << typeID << ' ' << pos.x << ' ' << pos.y << ' ' << std::to_string(renderLayer) << ' ';
	// Serialize Children
	os << LIST_START << ' ';
	// if is module
	if (saveAsModule) {
		// for each child
		for (unsigned int i = 0; i < children.size(); i++) {
			// if the child is a module
			if (children[i]->saveAsModule) {
				// state the name of the module
				os << MakeSerializable(children[i]->name) << ' ';
				// TOOD: fix bug where if the next child is not a module, it ruins the rest of the save file.
				// it's casued by outputting LIST_ITEM_END + ' ' when the next element is the last child in the array and the next element is not a module (it isn't valid)
				if (i < children.size() - 1) {
					os << LIST_ITEM_END << ' ';
				}
			}
			// otherwise the child is not a module & cannot be serialized
			else {
				Log("Module child not a module, failed to save child.", WARNING);
				Log("Due to a bug, this made the save file invalid - fix this bug.", FAULT);
			}
		}
	}
	else {
		// state the children by index in the scene
		for (unsigned int i = 0; i < children.size(); i++) {
			os << std::to_string(GetActiveScene()->EntityPointerToIndex(children[i]));
			os << ' ';
			if (i < children.size() - 1) {
				os << LIST_ITEM_END << ' ';
			}
		}
	}
	os << LIST_END << ' ';
	// Serialize Colliders
	os << LIST_START << ' ';
	for (unsigned int i = 0; i < colliders.size(); i++) {
		colliders[i]->Serialize(os);
		os << ' ';
		if (i < colliders.size() - 1) {
			os << LIST_ITEM_END << ' ';
		}
	}
	os << LIST_END;
	return os;
}
std::istream& Entity::Deserialize(std::istream& is) {
	std::string str = "";
	is >> str >> pos.x >> pos.y >> str;
	renderLayer = std::stoi(str);
	{ // Deserialize Children
		char listStart;
		is >> listStart;
		if (listStart != LIST_START) {
			Log("Tried to deserialize data into a vector that did not begin with " + LIST_START, WARNING);
			return is;
		}
		bool isParsingList = true;
		while (isParsingList) {
			std::string element;
			while (true) {
				std::string elementItem;
				is >> elementItem;
				if (elementItem[0] == LIST_END || is.eof()) {
					isParsingList = false;
					break;
				}
				if (elementItem[0] == LIST_ITEM_END) {
					break;
				}
				if (element != "") {
					element += ' ';
				}
				element += elementItem;
			}
			if (element != "") {
				// add the element to the loadChildren list, which will be converted into Entity* in LateDeserialize
				loadChildren.push_back(element);
			}
		}
	}
	{ // Deserialize Colliders
		char listStart;
		is >> listStart;
		if (listStart != LIST_START) {
			Log("Tried to deserialize data into a vector that did not begin with " + LIST_START, WARNING);
			return is;
		}
		bool isParsingList = true;
		while (isParsingList) {
			std::string element;
			while (true) {
				std::string subElement;
				is >> subElement;
				if (subElement[0] == LIST_END || is.eof()) {
					isParsingList = false;
					break;
				}
				if (subElement[0] == LIST_ITEM_END) {
					break;
				}
				if (element != "") {
					element += ' ';
				}
				element += subElement;
			}
			if (element != "") {
				Collider* collider = DeserializeLineToCollider(element);
				if (collider) {
					colliders.push_back(collider);
				}
				else {
					Log("Collider failed to deserialize.", FAULT);
				}
			}
		}
	}
	return is;
}

void Entity::LateDeserialize() {
	// Load Children
	for (std::string childName : loadChildren) {
		if (childName[0] == '{') {
			bool found = false;
			for (Entity* entity : GetActiveScene()->entities) {
				if (entity->saveAsModule && entity->name == DeserializeString(childName)) {
					children.push_back(entity);
					found = true;
					break;
				}
			}
			if (!found) {
				Log("Child module " + DeserializeString(childName) + " was not found in the scene.");
			}
		}
		else children.push_back(GetActiveScene()->entities[std::stoi(childName)]);
	}
	loadChildren.clear();
	loadChildren.shrink_to_fit();
}