#ifndef AABBCOLLIDER_H
#define AABBCOLLIDER_H
#pragma once

#include "Collider.h"

class AABBCollider : public Collider {
private:
protected:
	virtual bool IsNarrowPhaseColliding(Collider* collider) override;
public:
	AABBCollider(SDL_Rect rect = { 0, 0, 1, 1 })
		: Collider(rect) {}
	virtual bool IsColliding(Collider* collider) override;

	virtual void RenderNarrowCollider();

	// Generate serialized text data for this collider into the stream
	virtual std::ostream& Serialize(std::ostream& os) override;
	// Populate this collider by deserializing text data from the stream
	virtual std::istream& Deserialize(std::istream& is) override;
};

#endif // !AABBCOLLIDER_H