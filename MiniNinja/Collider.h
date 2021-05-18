#ifndef COLLIDER_H
#define COLLIDER_H
#pragma once

#include <SDL.h>
#include <cstdint>
#include <iostream>

class Collider {
private:
protected:
	uint16_t typeID = __COUNTER__;
	SDL_Rect rect;

	bool IsBroadPhaseColliding(Collider* collider);
	virtual bool IsNarrowPhaseColliding(Collider* collider);

	virtual void RecalculateAABB();
public:

	Collider(SDL_Rect rect = { 0, 0, 1, 1 })
		: rect(rect) {}

	virtual bool IsColliding(Collider* collider);

	void RenderBroadCollider();
	virtual void RenderNarrowCollider();

	SDL_Point GetPosition();
	SDL_Point GetBoundingDimensions();
	SDL_Rect GetBoundingRect();

	bool IsType(uint16_t typeID);
	template <typename T> bool IsType();
	template <typename T> T* GetAsType();

	// Generate serialized text data for this collider into the stream
	virtual std::ostream& Serialize(std::ostream& os);
	// Populate this collider by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is);
};

#endif // !COLLIDER_H