#include "Collider.h"
#include "Draw.h"
#include "FileParameters.h"
#include "Scene.h"

bool Collider::IsBroadPhaseColliding(Collider* collider) {
	return rect.x < collider->rect.x + collider->rect.w
		&& rect.x + rect.w > collider->rect.x
		&& rect.y < collider->rect.y + collider->rect.h
		&& rect.y + rect.h > collider->rect.y;
}

bool Collider::IsNarrowPhaseColliding(Collider* collider) {
	return true;
}

void Collider::RecalculateAABB() {}

bool Collider::IsColliding(Collider* collider) {
	return false;
}

void Collider::RenderBroadCollider() {
	DrawRect(SceneToViewport(rect, GetActiveScene()));
}

void Collider::RenderNarrowCollider() {}

void Collider::SetPosition(SDL_Point pos) {
	rect.x = pos.x;
	rect.y = pos.y;
}

SDL_Point Collider::GetPosition() {
	return { rect.x, rect.y };
}

SDL_Point Collider::GetBoundingDimensions() {
	return { rect.w, rect.h };
}

SDL_Rect Collider::GetBoundingRect() {
	return rect;
}

bool Collider::IsType(uint16_t typeID) {
	return this->typeID == typeID;
}

template<typename T> bool Collider::IsType() {
	return dynamic_cast<T*>(this) != nullptr;
}

template<typename T> T* Collider::GetAsType() {
	return dynamic_cast<T*>(this);
}

std::ostream& Collider::Serialize(std::ostream& os) {
	return os << typeID << ' ' << rect.x << ' ' << rect.y << ' ' << rect.w << ' ' << rect.h;
}

std::istream& Collider::Deserialize(std::istream& is) {
	std::string throwaway = "";
	is >> throwaway >> rect.x >> rect.y >> rect.w >> rect.h;
	return is;
}