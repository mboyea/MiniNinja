#include "Entity.h"
#include "FileParameters.h"
#include "Scene.h"
#include "Log.h"

void Entity::Update() {}
void Entity::Render() {}
void Entity::OnCollision(Entity* collisionEntity) {}

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
	if (saveAsModule) {
		resourcesOut.insert(Resource(name, RESOURCE_MODULE));
	}
	return resourcesOut;
}

std::ostream& Entity::Serialize(std::ostream& os) {
	os << typeID << ' ' << pos.x << ' ' << pos.y << ' ' << std::to_string(renderLayer) << ' ';
	// Serialize Children
	os << LIST_START << ' ';
	if (GetActiveScene()) {
		for (unsigned int i = 0; i < children.size(); i++) {
			os << std::to_string(GetActiveScene()->EntityPointerToIndex(children[i]));
			os << ' ';
			if (i < children.size() - 1) {
				os << LIST_ITEM_END << ' ';
			}
		}
	}
	else {
		Log("Entity children could not be saved.", FAULT);
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
	std::string throwaway = "";
	is >> throwaway >> pos.x >> pos.y >> renderLayer;
	// Deserialize Children
	// TODO: store a list of indexes for each Entity within the active scene and once every Entity is loaded, set each Entity's children to the correct Entity* from the list of indexes
	// Deserialize Colliders

	return is;
}

bool Entity::operator<(const Entity& rhs) {
	return renderLayer < rhs.renderLayer;
}