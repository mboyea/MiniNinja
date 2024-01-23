#ifndef COLLIDERS_H
#define COLLIDERS_H
#pragma once

#include <string>
#include "Collider.h"

unsigned int GetColliderTypeID(Collider* collider);
Collider* GetColliderByTypeID(unsigned int typeID);
bool IsColliderOfTypeID(Collider* collider, unsigned int typeID);
Collider* DeserializeLineToCollider(std::string line);

#endif // !COLLIDERS_H