#include "Entity.h"

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

std::ostream& Entity::Serialize(std::ostream& os) {
	return os;
}
std::istream& Entity::Deserialize(std::istream& is) {
	return is;
}

bool Entity::operator<(const Entity& rhs) {
	return renderLayer < rhs.renderLayer;
}
