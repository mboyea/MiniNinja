#ifndef RESOURCE_H
#define RESOURCE_H
#pragma once

#include <iostream>
#include <string>

enum ResourceType {
	RESOURCE_MODULE,
	RESOURCE_TEXTURE,
	RESOURCE_ANIMATION,
	RESOURCE_FONT,
	MAX_RESOURCE_TYPES
};

struct Resource {
	std::string name;
	ResourceType type;

	Resource(std::string name, ResourceType type) : name(name), type(type) {}

	friend std::ostream& operator<<(std::ostream& os, const Resource& rhs);
	friend std::istream& operator>>(std::istream& is, Resource& rhs);
	bool operator<(const Resource& rhs);
};

#endif // !RESOURCE_H