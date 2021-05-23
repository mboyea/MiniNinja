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

std::vector<Resource*> Entity::GetRequiredResources() {
	std::vector<Resource*> resources;
	// TODO: outline required modules, fonts, textures, and animations
	return resources;
}

std::ostream& Entity::Serialize(std::ostream& os) {
	os << typeID << ' ' << pos.x << ' ' << pos.y << ' ' << renderLayer << ' ';
	// Serialize Children
	os << LIST_START << ' ';
	if (GetCurrentSavingScene()) {
		for (unsigned int i = 0; i < children.size(); i++) {
			os << std::to_string(GetCurrentSavingScene()->EntityPointerToIndex(children[i]));
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

	// Deserialize Colliders

	return is;
}

bool Entity::operator<(const Entity& rhs) {
	return renderLayer < rhs.renderLayer;
}