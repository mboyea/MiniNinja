#ifndef ENTITIES_H
#define ENTITIES_H
#pragma once

#include "Entity.h"
#include <cstdint>
#include <string>

Entity* GetEntityOfType(uint16_t typeID);
Entity* DeserializeLineToEntity(std::string line);

#endif // !ENTITIES_H