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
	for (unsigned int i = 0; i < children.size(); i++) {
		os << std::to_string(GetActiveScene()->EntityPointerToIndex(children[i]));
		os << ' ';
		if (i < children.size() - 1) {
			os << LIST_ITEM_END << ' ';
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
				// TODO: store a list of indexes for each Entity within the active scene and once every Entity is loaded, set each Entity's children to the correct Entity* from the list of indexes
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