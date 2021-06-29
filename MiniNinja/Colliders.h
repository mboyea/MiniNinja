#ifndef COLLIDERS_H
#define COLLIDERS_H
#pragma once

#include <sstream>
#include "Collider.h"
#include "AABBCollider.h"
//	#include "OBBCollider.h"
//	#include "CircleCollider"

Collider* GetColliderOfType(uint16_t typeID);
Collider* DeserializeLineToCollider(std::string line);

#endif // !COLLIDERS_H