#include "AABBCollider.h"

bool AABBCollider::IsNarrowPhaseColliding(Collider* collider) {
	return IsBroadPhaseColliding(collider);
}

bool AABBCollider::IsColliding(Collider* collider) {
	return IsBroadPhaseColliding(collider);
}

void AABBCollider::RenderNarrowCollider() {
	Collider::RenderBroadCollider();
}

std::ostream& AABBCollider::Serialize(std::ostream& os) {
	Collider::Serialize(os);
	return os;
}

std::istream& AABBCollider::Deserialize(std::istream& is) {
	Collider::Deserialize(is);
	return is;
}
