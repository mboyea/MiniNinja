#include "Resource.h"
#include "FileParameters.h"
#include "Files.h"
#include "Scene.h"
#include <fstream>
#include <sstream>
#include "Log.h"
#include "Audio.h"
#include "Textures.h"
#include "Fonts.h"

std::ostream& operator<<(std::ostream& os, const Resource& rhs) {
	return os << MakeSerializable(rhs.name);
}

std::istream& operator>>(std::istream& is, Resource& rhs) {
	rhs.name = DeserializeString(is);
	return is;
}

bool operator<(const Resource& lhs, const Resource& rhs) {
	return lhs.type < rhs.type || lhs.name < rhs.name;
}

std::string Resource::GetType() {
	switch (type) {
	case RESOURCE_TEXTURE:
		return "Texture";
	case RESOURCE_ANIMATION:
		return "Animation";
	case RESOURCE_FONT:
		return "Font";
	case RESOURCE_AUDIO:
		return "Audio";
	case MAX_RESOURCE_TYPES:
		return "MAX_RESOURCE_TYPES";
	default:
		return "Error";
	}
}

std::string Resource::GetFilePath(std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath, std::string audioFolderPath) {
	switch (type) {
	case RESOURCE_TEXTURE:
		return ForceFilePath(name, textureFolderPath, "png");
	case RESOURCE_ANIMATION:
		return ForceFilePath(name, animationFolderPath, "zanim");
	case RESOURCE_FONT:
		return ForceFilePath(name, fontFolderPath, "ttf");
	case RESOURCE_AUDIO:
		return ForceFilePath(name, audioFolderPath, "mp3");
	case MAX_RESOURCE_TYPES:
		return ForceFilePath(name, "Error", "resourceerror");
	default:
		return ForceFilePath(name, "Error", "resourceerror");
	}
}

bool LoadResource(Resource resource, std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath, std::string audioFolderPath) {
	std::string filePath = resource.GetFilePath(textureFolderPath, animationFolderPath, fontFolderPath, audioFolderPath);
	// Load Resource
	switch (resource.type) {
	case RESOURCE_TEXTURE:
		if (IsTexture(resource.name)) {
			return true;
		}
		return LoadTexture(filePath);
	case RESOURCE_ANIMATION:
		break; // TODO: return LoadAnimation(filePath)
	case RESOURCE_FONT: {
		// TODO: test this
		int index = -1;
		for (auto it = resource.name.crbegin(); it != resource.name.crend(); it++) {
			if (*it == '_') {
				index = filePath.size() - (it - filePath.crbegin()) - 1;
				break;
			}
		}
		int fontSize = 16;
		if (index > 0) {
			fontSize = std::stoi(resource.name.substr(index));
		}
		if (IsFont(filePath, fontSize)) {
			return true;
		}
		return LoadFont(filePath, fontSize);
	}
	case RESOURCE_AUDIO:
		return LoadAudio(filePath);
	default:
		return false;
	}
	return false;
}

bool LoadResources(std::set<Resource> resources, std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath, std::string audioFolderPath) {
	bool didSucceed = true;
	for (Resource resource : resources) {
		didSucceed = didSucceed && LoadResource(resource, textureFolderPath, animationFolderPath, fontFolderPath, audioFolderPath);
	}
	return didSucceed;
}