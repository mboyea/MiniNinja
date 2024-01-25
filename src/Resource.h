#ifndef RESOURCE_H
#define RESOURCE_H
#pragma once

#include <iostream>
#include <string>
#include <set>

enum ResourceType {
	RESOURCE_TEXTURE,
	RESOURCE_ANIMATION,
	RESOURCE_FONT,
	RESOURCE_AUDIO,
	MAX_RESOURCE_TYPES
};

struct Resource {
	std::string name;
	ResourceType type;

	Resource(std::string name, ResourceType type) : name(name), type(type) {}

	friend std::ostream& operator<<(std::ostream& os, const Resource& rhs);
	friend std::istream& operator>>(std::istream& is, Resource& rhs);
	std::string GetType();
	std::string GetFilePath(std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath, std::string audioFolderPath);
};
bool operator<(const Resource& lhs, const Resource& rhs);
bool LoadResource(Resource resource, std::string textureFolderPath = "Resources/Textures", std::string animationFolderPath = "Resources/Animations", std::string fontFolderPath = "Resources/Fonts", std::string audioFolderPath = "Resources/Audio");
bool LoadResources(std::set<Resource> resources, std::string textureFolderPath = "Resources/Textures", std::string animationFolderPath = "Resources/Animations", std::string fontFolderPath = "Resources/Fonts", std::string audioFolderPath = "Resources/Audio");

#endif // !RESOURCE_H