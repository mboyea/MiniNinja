#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <iostream>
#include <vector>
#include <set>
#include "Entity.h"
#include "Camera.h"
#include "Resource.h"

#define SCENE_VERSION "0.0.0"

struct Scene {
	std::vector<Entity*> entities;
	Camera camera;

	Scene()
		: entities({}), camera(Camera()) {}
	~Scene();

	void Update();
	void Render();
	int EntityPointerToIndex(Entity* entity);

	std::set<Resource> GetRequiredResources();
	bool LoadModule(std::string filePath, std::string moduleFolderPath = "Resources/Modules");
	// Generate serialized text data for this scene into the stream
	std::ostream& Serialize(std::ostream& os, std::string moduleFolderPath = "Resources/Modules");
	// Populate this scene by deserializing text data from the stream
	bool Deserialize(std::istream& is, std::string moduleFolderPath = "Resources/Modules", std::string textureFolderPath = "Resources/Textures", std::string animationFolderPath = "Resources/Animations", std::string fontFolderPath = "Resources/Fonts");
};

// Return the Scene which is currently calling Update(), Render(), SaveScene(), or LoadScene(); otherwise, return nullptr.
Scene* GetActiveScene();
bool SaveScene(Scene* scene, std::string filePath, std::string moduleFolderPath = "Resources/Modules");
Scene* LoadScene(std::string filePath, std::string moduleFolderPath = "Resources/Modules", std::string textureFolderPath = "Resources/Textures", std::string animationFolderPath = "Resources/Animations", std::string fontFolderPath = "Resources/Fonts");

SDL_Point SceneToViewport(SDL_Point pos, Scene* scene);
SDL_Rect SceneToViewport(SDL_Rect rect, Scene* scene);

#endif // !SCENE_H