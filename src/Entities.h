#ifndef ENTITIES_H
#define ENTITIES_H
#pragma once

#include <string>
#include "Entity.h"

unsigned int GetEntityTypeID(Entity* entity);
Entity* GetEntityByTypeID(unsigned int typeID);
bool IsEntityOfTypeID(Entity* entity, unsigned int typeID);
Entity* DeserializeLineToEntity(std::string line);

#endif // !ENTITIES_H